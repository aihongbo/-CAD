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

#ifndef IPC_SERVER_MANAGER_H
#define IPC_SERVER_MANAGER_H

#include "IPCData.h"

#include <QObject>
#include <QLocalServer>
#include <QLocalSocket>
#include <QMutex>

#include <memory>

namespace NCTI {

    //标签页ID
    static constexpr int MAIN_PAGE_ID = 1001;
    static constexpr int NEW_PAGE_ID = 1002;

    struct EmbeddedWndData
    {
        QWidget* widget{ nullptr };      ///< 窗口控件指针
        QLocalSocket* socket{ nullptr }; ///< 本地套接字指针
        int64_t windowId{ 0 };           ///< 窗口ID
    };

    class IPCServerManager : public QObject
    {
        Q_OBJECT
    public:
        explicit IPCServerManager(QObject* parent = nullptr);
        ~IPCServerManager();

        bool startLocalServer();
        void stopLocalServer();
        void addEmbeddedWindow(int64_t windowId, QWidget* widget, QLocalSocket* socket);

        EmbeddedWndData removeEmbeddedWindow(int windowId);
        EmbeddedWndData removeEmbeddedWindow(QLocalSocket* socket);
        EmbeddedWndData getEmbeddedWindow(int windowId);

        int getEmbeddedWindowCount() const;

        void refreshDocView(QWidget* widget);

        QString getFullServerName();

        // 发送消息数据
        void sendDocRefreshMessage(int64_t windowId);
        bool sendDocDirtyMessage(int64_t windowId, const QString& text);
        void sendExitMessageToAllClient();
        void sendExitMessage(int64_t windowId);
        void sendExitSaveMessage(int64_t windowId, const QString& savePath);
        void sendRunTaskMessage(int64_t windowId, const TaskDetail& msgData);
        bool sendMessageData(const MessageData& msgData);

    private Q_SLOTS:
        // 处理新连接
        void handleNewConnection();

        // 读取Socket数据
        void readSocketData();

    Q_SIGNALS:
        // Socket断开连接信号
        void sigSocketDisconnected(QLocalSocket* socket);

        // 窗口ID消息信号
        void sigWindowIdMessage(QLocalSocket* socket, const MessageData& msgData);

        // 任务详情信号
        void sigTaskDetailMessage(const MessageData& msgData);

        // 退出保存消息信号
        void sigExitSaveMessage(const MessageData& msgData);

        // 文档更新信号
        void sigDocDirtyMessage(const MessageData& msgData);

        // 数据更新消息信号
        void sigDataUpdateMessage(const MessageData& msgData);

    private:
        QString mServerName; // 服务器名称
        std::unique_ptr<QLocalServer> mServer; // 本地服务器
        std::unordered_map<int64_t, EmbeddedWndData> mEmbeddedWindowData; // 嵌入窗口数据
    };

}

#endif // IPC_SERVER_MANAGER_H