/*
 * Copyright (c) 2025 粤港澳大湾区（广东）国创中心
 *
 * This file is a part of NctiCAEPre.
 *
 * NctiCAEPre is licensed under Mulan PSL v2.
 * You can use this software according to the terms and conditions of the Mulan PSL v2.
 * You may obtain a copy of Mulan PSL v2 at:
 *          http://license.coscl.org.cn/MulanPSL2
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
 * EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
 * MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
 * See the Mulan PSL v2 for more details.
 *
 */

#include "IPCServerManager.h"
#include <QApplication>
#include <QDebug>

namespace NCTI {

    static std::string toString(const QString& qstr) 
    {
        QByteArray ba = qstr.toUtf8();
        return ba.toStdString();
    }

    IPCServerManager::IPCServerManager(QObject* parent) : QObject(parent)
    {
        startLocalServer();
    }

    IPCServerManager::~IPCServerManager()
    {
        stopLocalServer();
    }

    bool IPCServerManager::startLocalServer()
    {
        if (mServer) {
            qWarning() << "Local server already exists";
            return false;
        }

        mServer = std::make_unique<QLocalServer>(this);

        // 移除可能存在的旧连接
        QString serverName = QStringLiteral("ncti_qt_launcher_%1").arg(QApplication::applicationPid());
        QLocalServer::removeServer(serverName);

        // 监听连接
        if (!mServer->listen(serverName)) {
            qWarning() << "Failed to start local server:" << mServer->errorString();
            mServer.reset();
            return false;
        }

        connect(mServer.get(), &QLocalServer::newConnection, this, &IPCServerManager::handleNewConnection);

        qDebug() << "Local server started:" << serverName;
        return true;
    }

    void IPCServerManager::stopLocalServer()
    {
        if (mServer) {
            mServer->close();
            mServer.reset();
        }
        mServerName.clear();
    }

    void IPCServerManager::handleNewConnection()
    {
        QLocalSocket* socket = mServer->nextPendingConnection();
        if (!socket) {
            qWarning() << "Failed to get next pending connection";
            return;
        }

        connect(socket, &QLocalSocket::readyRead, this, &IPCServerManager::readSocketData);

        connect(socket, &QLocalSocket::disconnected, [this, socket]() {
            qDebug() << "Socket disconnected";
            Q_EMIT sigSocketDisconnected(socket);
            removeEmbeddedWindow(socket);
            socket->deleteLater();
            });

        // 自动清理无效连接
#if QT_VERSION_MAJOR >= 6
        connect(socket, &QLocalSocket::errorOccurred, this,
            [socket](QLocalSocket::LocalSocketError error) {
                qDebug() << "Socket error:" << error;
                socket->deleteLater();
            });
#else
        connect(socket, QOverload<QLocalSocket::LocalSocketError>::of(&QLocalSocket::error), this,
            [socket](QLocalSocket::LocalSocketError error) {
                qDebug() << "Socket error:" << error;
                socket->deleteLater();
            });
#endif
    }

    void IPCServerManager::readSocketData()
    {
        QLocalSocket* socket = qobject_cast<QLocalSocket*>(sender());
        if (!socket) { return; }

        QByteArray data = socket->readAll();
        QString message(data);

        try {
            json j = json::parse(message.toStdString());
            MessageData fromData = j;

            if (fromData.msg_type == MessageType::MT_INVALID) {
                qWarning() << "Invalid message type received";
                return;
            }

            // 根据消息类型分发到不同的信号
            if (fromData.msg_type == MessageType::MT_WINDOW_ID) {
                Q_EMIT sigWindowIdMessage(socket, fromData);
            }
            else if (fromData.msg_type == MessageType::MT_TASK_DETAIL) {
                Q_EMIT sigTaskDetailMessage(fromData);
            }
            else if (fromData.msg_type == MessageType::MT_EXIT_SAVE) {
                Q_EMIT sigExitSaveMessage(fromData);
            }
            else if (fromData.msg_type == MessageType::MT_DOC_DIRTY) {
                Q_EMIT sigDocDirtyMessage(fromData);
            }
            else if (fromData.msg_type == MessageType::MT_UPDATE) {
                Q_EMIT sigDataUpdateMessage(fromData);
            }
        }
        catch (const json::exception& e) {
            qWarning() << "IPCManager::readSocketData(), JSON parse error:" << e.what();
        }
    }

    bool IPCServerManager::sendDocDirtyMessage(int64_t windowId, const QString& text)
    {
        MessageData sendData;
        sendData.msg_type = MessageType::MT_DOC_DIRTY;
        sendData.window_id = windowId;
        sendData.file_name = toString(text);
        return sendMessageData(sendData);
    }

    void IPCServerManager::sendExitMessageToAllClient()
    {
        // 创建窗口ID的副本，避免在遍历过程中修改mEmbeddedWindowData
        std::vector<int64_t> windowIds;
        for (const auto& pair : mEmbeddedWindowData) {
            const auto& embedded = pair.second;
            if (embedded.windowId > 0 && embedded.windowId != MAIN_PAGE_ID) {
                windowIds.push_back(embedded.windowId);
            }
        }
        
        // 遍历窗口ID副本发送退出消息
        for (auto windowId : windowIds) {
            MessageData sendData;
            sendData.msg_type = MessageType::MT_EXIT;
            sendData.window_id = windowId;
            sendMessageData(sendData);
        }
    }

    void IPCServerManager::sendExitMessage(int64_t windowId)
    {
        MessageData sendData;
        sendData.msg_type = MessageType::MT_EXIT;
        sendData.window_id = windowId;
        sendMessageData(sendData);
    }

    void IPCServerManager::sendExitSaveMessage(int64_t windowId, const QString& savePath)
    {
        if (savePath.isEmpty()) { return; }

        MessageData sendData;
        sendData.msg_type = MessageType::MT_EXIT_SAVE;
        sendData.window_id = windowId;
        sendData.file_path = toString(savePath);
        sendMessageData(sendData);
    }

    void IPCServerManager::sendDocRefreshMessage(int64_t windowId)
    {
        MessageData sendData;
        sendData.msg_type = MessageType::MT_DOC_REFRESH;
        sendData.window_id = windowId;
        sendMessageData(sendData);
    }

    void IPCServerManager::sendRunTaskMessage(int64_t windowId, const TaskDetail& msgData)
    {
        MessageData sendData;
        sendData.msg_type = MessageType::MT_TASK_DETAIL;
        sendData.window_id = windowId;
        sendData.task_type = msgData.type;
        sendData.file_path = msgData.file_path;
        sendData.geometry = msgData.geometry;
        sendData.constraint = msgData.constraint;
        sendData.mesh = msgData.mesh;
        sendMessageData(sendData);
    }

    bool IPCServerManager::sendMessageData(const MessageData& d)
    {
        auto it = mEmbeddedWindowData.find(d.window_id);
        if (it == mEmbeddedWindowData.end()) {
            //qWarning() << "Window with ID" << d.window_id << "not found";
            return false;
        }
        
        QLocalSocket* socket = it->second.socket;
        if (!socket) {
            //qWarning() << "Socket is null for window ID" << d.window_id;
            return false;
        }
        
        if (socket->state() != QLocalSocket::ConnectedState) {
            //qWarning() << "Socket is not connected for window ID" << d.window_id << "state:" << socket->state();
            return false;
        }

        try {
            json j = d;
            socket->write(QString::fromStdString(j.dump()).toUtf8());
            socket->flush();
        } catch (const json::exception& e) {
            //qWarning() << "IPCManager::sendMessageData(), JSON parse error:" << e.what();
            return false;
        } catch (const std::exception& e) {
            //qWarning() << "IPCManager::sendMessageData(), exception:" << e.what();
            return false;
        }

        return true;
    }

    void IPCServerManager::addEmbeddedWindow(int64_t windowId, QWidget* widget, QLocalSocket* socket)
    {
        EmbeddedWndData data;
        data.widget = widget;
        data.socket = socket;
        data.windowId = windowId;
        mEmbeddedWindowData[windowId] = data;
    }

    EmbeddedWndData IPCServerManager::removeEmbeddedWindow(int windowId)
    {
        EmbeddedWndData data;
        auto it = mEmbeddedWindowData.find(windowId);
        if (it != mEmbeddedWindowData.end()) {
            data = it->second;
            mEmbeddedWindowData.erase(it);
        }
        return data;
    }

    EmbeddedWndData IPCServerManager::removeEmbeddedWindow(QLocalSocket* socket)
    {
        EmbeddedWndData data;
        for (auto it = mEmbeddedWindowData.begin(); it != mEmbeddedWindowData.end(); ++it) {
            if (it->second.socket == socket) {
                data = it->second;
                mEmbeddedWindowData.erase(it);
                break;
            }
        }
        return data;
    }

    EmbeddedWndData IPCServerManager::getEmbeddedWindow(int windowId)
    {
        EmbeddedWndData data;
        auto it = mEmbeddedWindowData.find(windowId);
        if (it != mEmbeddedWindowData.end()) {
            data = it->second;
        }
        return data;
    }

    int IPCServerManager::getEmbeddedWindowCount() const
    {
        return mEmbeddedWindowData.size();
    }

    void IPCServerManager::refreshDocView(QWidget* widget)
    {
        for (const auto& pair : mEmbeddedWindowData) {
            const auto& embedded = pair.second;
            if (embedded.windowId > 0 && widget == embedded.widget) {
                sendDocRefreshMessage(embedded.windowId);
                break;
            }
        }
    }
    
    QString IPCServerManager::getFullServerName()
    {
        if (mServer) {
            return mServer->fullServerName();
        }
        return QString();
    }
}