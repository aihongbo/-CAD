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

#include "IPCManager.h"

#include "NctiWindowPlatform.h"
#include "NctiSaveFileManager.h"
#include "NctiWindowViewManager.h"
#include "NctiDocument.h"

#include "NctiQTPubFun.h"

#include "IPCData.h"
#include "FileOperations.h"

#include <QLocalSocket>
#include <QFileInfo>

namespace NCTI {

static std::string toString(const QString& qstr)
{
    QByteArray ba = qstr.toUtf8();
    return ba.toStdString();
}

static EnumModelDoc getGeoType(std::string geoType)
{
    if (geoType == "OCC") { return EnumModelDoc::NCTI_GEOM_OCC; }
    else if (geoType == "PK") { return EnumModelDoc::NCTI_GEOM_PK; }
    else if (geoType == "OD") { return EnumModelDoc::NCTI_GEOM_OD; }
    else if (geoType == "PS") { return EnumModelDoc::NCTI_GEOM_PS; }
    return EnumModelDoc::NCTI_GEOM_OCC;
}

static EnumGCSDoc getDCMType(std::string dcmType)
{
    if (dcmType == "DCM") { return EnumGCSDoc::NCTI_GCS_DCM; }
    else if (dcmType == "PSCS") { return EnumGCSDoc::NCTI_GCS_PSCS; }
    else if (dcmType == "HTGC") { return EnumGCSDoc::NCTI_GCS_HTGC; }
    return EnumGCSDoc::NCTI_GCS_DCM;
}

static EnumMeshDoc getMeshType(std::string meshType)
{
    if (meshType == "GMSH") { return EnumMeshDoc::NCTI_MESH_GMSH; }
    else if(meshType == "MESHGEMS") { return EnumMeshDoc::NCTI_MESH_MESHGEMS; }
    else if (meshType == "PANAMESH") { return EnumMeshDoc::NCTI_MESH_PANAMESH; }
    else if (meshType == "NETGEN") { return EnumMeshDoc::NCTI_MESH_NETGEN; }
    return EnumMeshDoc::NCTI_MESH_GMSH;
}

IPCManager::IPCManager(MainWindow* mainWindow)
    : MainWindowModule(mainWindow)
{
}

void IPCManager::initialize()
{
}

void IPCManager::runTask()
{
    if (!m_taskInfo || m_taskInfo->type.isEmpty()) {
        return;
    }

    auto mFileOpt = m_mainWindow->getFileOperations();

    if (mFileOpt) {
        if (m_taskInfo->type == "new_part") {
            mFileOpt->onNewPart();
        }
        else if (m_taskInfo->type == "new_assembly") {
            mFileOpt->onNewAssembly();
        }
        else if (m_taskInfo->type == "open_file") {
            mFileOpt->onOpenNcti(m_taskInfo->filePath);
        }
    }

    // 重置taskInfo
    m_taskInfo.reset();
}

void IPCManager::initTaskInfo(const QString& t, const QString& f, int g, int c, int m)
{
    m_taskInfo = std::make_unique<TaskInfo>(t, f, g, c, m);
}

TaskInfo* IPCManager::GetTaskInfo()
{
    return m_taskInfo.get();
}

int64_t IPCManager::getWindowId()
{
    QString windowIdStr = QString::number(m_mainWindow->winId());
    return windowIdStr.toLongLong();
}

bool IPCManager::createLocalSocket(const QString& s)
{
    if (s.isEmpty()) {
        return false;
    }

    // 连接到主进程
    m_socket = std::make_unique<QLocalSocket>();
    connect(m_socket.get(), &QLocalSocket::connected, this, &IPCManager::onConnected);
    connect(m_socket.get(), &QLocalSocket::readyRead, this, &IPCManager::onReadyRead);
    connect(m_socket.get(), &QLocalSocket::disconnected, this, &IPCManager::onDisconnected);
    m_socket->connectToServer(s);

    if (!m_socket->waitForConnected(1000)) {
        qWarning() << "Failed to connect to main process server";
        return false;
    }
    return true;
}

void IPCManager::onConnected()
{
    if (m_socket) {
        // 发送窗口句柄到主进程
        MessageData sendData;
        sendData.msg_type = MT_WINDOW_ID;
        sendData.window_id = getWindowId();
        if (m_taskInfo) {
            QFileInfo fileInfo(m_taskInfo->filePath);
            sendData.file_name = toString(fileInfo.completeBaseName());
            sendData.file_path = toString(m_taskInfo->filePath);
        }
        sendMessageData(sendData);

        runTask();
    }
}

void IPCManager::onReadyRead()
{
    // 将新收到的数据追加到缓冲区
    m_messageBuffer.append(m_socket->readAll());
    if (m_messageBuffer.isEmpty()) {
        return;
    }

    // 处理缓冲区中的所有完整JSON消息
    int pos = 0;
    while (pos < m_messageBuffer.size()) {
        // 跳过空白
        while (pos < m_messageBuffer.size() && 
               (m_messageBuffer[pos] == ' ' || 
                m_messageBuffer[pos] == '\n' || 
                m_messageBuffer[pos] == '\r' || 
                m_messageBuffer[pos] == '\t')) {
            ++pos;
        }
        if (pos >= m_messageBuffer.size()) {
            break; // 没有更多数据
        }
        if (m_messageBuffer[pos] != '{') {
            // 不是有效的JSON对象开始，跳过这个字符
            ++pos;
            continue;
        }

        // 查找匹配的结束大括号
        int braceCount = 1;
        int endPos = pos + 1;
        while (endPos < m_messageBuffer.size() && braceCount > 0) {
            char c = m_messageBuffer[endPos]; 
            if (c == '{') {
                ++braceCount;
            } else if (c == '}') {
                --braceCount;
            } else if (c == '"') {
                // 跳过字符串中的内容
                ++endPos;
                while (endPos < m_messageBuffer.size() && m_messageBuffer[endPos] != '"') {
                    if (m_messageBuffer[endPos] == '\\') {
                        // 跳过转义字符
                        ++endPos;
                    }
                    ++endPos;
                }
            }
            ++endPos;
        }

        if (braceCount == 0) {
            // 找到了完整的JSON对象
            QByteArray jsonData = m_messageBuffer.mid(pos, endPos - pos);
            QString message = QString::fromUtf8(jsonData);
            //qDebug() << "Received JSON message:" << message;
            try {
                json j = json::parse(message.toStdString());
                MessageData fromData = j;
                if (fromData.msg_type == MT_EXIT) {
                    onMsgTypeExit(fromData);
                } else if (fromData.msg_type == MT_EXIT_SAVE) {
                    onMsgTypeExitSave(fromData);
                } else if (fromData.msg_type == MT_DOC_DIRTY) {
                    onMsgTypeDocDirty(fromData);
                } else if (fromData.msg_type == MT_DOC_REFRESH) {
                    onMsgTypeDocRefresh(fromData);
                } else if (fromData.msg_type == MT_TASK_DETAIL) {
                    onMsgTypeRunTask(fromData);
                }
            } catch (const json::exception& e) {
                qDebug() << "JSON parse error:" << e.what();
            }
            pos = endPos;
        } else {
            // 没有找到匹配的结束大括号，等待更多数据
            break;
        }
    }

    // 保留未处理的数据在缓冲区中
    if (pos < m_messageBuffer.size()) {
        m_messageBuffer = m_messageBuffer.mid(pos);
    } else {
        m_messageBuffer.clear();
    }
}

void IPCManager::onDisconnected()
{
}

void IPCManager::sendMessageData(const MessageData& msgData)
{
    if (!m_socket)
        return;

    try {
        json j = msgData;
        m_socket->write(j.dump().c_str());
        m_socket->flush();
    }
    catch (const json::exception& e) {
        qDebug() << "JSON parse error:" << e.what();
    }
}

void IPCManager::onMsgTypeDocDirty(const MessageData& msgData)
{
    if (getWindowId() != msgData.window_id) {
        return;
    }
    MessageData sendData;
    sendData.msg_type = MT_DOC_DIRTY;
    sendData.window_id = msgData.window_id;
    sendData.file_name = msgData.file_name;

    auto windowPlatform = m_mainWindow->getWindowPlatform();
    if (!windowPlatform) {
        sendData.traversed = true;
        sendMessageData(sendData);
        return;
    }

    auto saveFileManager = NctiSaveFileManager::instance();
    if (windowPlatform && saveFileManager) {
        auto pDoc = windowPlatform->GetCurrentViewManager()->GetDocument();
        NCTI_SaveFileData fileData = saveFileManager->GetDocument(pDoc);
        if (fileData.IsValid() == true) {
            //文件路径已存在
            sendData.file_path = fileData.GetManualPath();
            if (pDoc->GetManualModified()) {
                // 文件有修改
                sendData.dirty = true;
            }
        }
    }
    sendMessageData(sendData);
}

void IPCManager::onMsgTypeDocRefresh(const MessageData& msgData)
{
    if (getWindowId() != msgData.window_id) {
        return;
    }

    auto windowPlatform = m_mainWindow->getWindowPlatform();
    if (windowPlatform) {
        NctiQTPubFun::RefreshViews(windowPlatform);
    }
}

void IPCManager::onMsgTypeRunTask(const MessageData& msgData)
{
    if(getWindowId() != msgData.window_id || msgData.task_type.empty()) {
        return;
    }

    auto mFileOpt = m_mainWindow->getFileOperations();
    if (mFileOpt) {
        if (msgData.task_type == "open_file") {
            return mFileOpt->onOpenNcti(QString::fromUtf8(msgData.file_path.c_str()));
        }

        EnumModelDoc geo = getGeoType(msgData.geometry);
        EnumGCSDoc cs    = getDCMType(msgData.constraint);
        EnumMeshDoc mesh = getMeshType(msgData.mesh);
        if (msgData.task_type == "new_part") {
            return mFileOpt->newPart(geo, cs, mesh);
        }
        if (msgData.task_type == "new_assembly") {
            return mFileOpt->newAssembly(geo, cs, mesh);
        }
    }
}

void IPCManager::onMsgTypeExit(const MessageData& msgData)
{
    if (getWindowId() != msgData.window_id) {
        return;
    }
    m_mainWindow->close();
}

void IPCManager::onMsgTypeExitSave(const MessageData& msgData)
{
    if (getWindowId() != msgData.window_id) {
        return;
    }

    auto windowPlatform = m_mainWindow->getWindowPlatform();
    if (!windowPlatform) {
        m_mainWindow->close();
        return;
    }

    QString savedPath;
    auto pDoc = windowPlatform->GetCurrentViewManager()->GetDocument();
    auto saveFileManager = NctiSaveFileManager::instance();
    if (pDoc && saveFileManager) {
        NCTI_SaveFileData fileData = saveFileManager->GetDocument(pDoc);
        if (fileData.IsValid()) {
            savedPath = QString::fromUtf8(fileData.GetManualPath().c_str());
        }
    }

    if (savedPath.isEmpty() && !msgData.file_path.empty()) {
        savedPath = QString::fromUtf8(msgData.file_path.c_str());
    }

    if (savedPath.isEmpty()) {
        m_mainWindow->close();
        return;
    }

    NctiQTPubFun::SaveAsNctiFile(windowPlatform, savedPath);

    QFileInfo fileInfo(savedPath);

    MessageData sendData;
    sendData.msg_type = MT_EXIT_SAVE;
    sendData.window_id = msgData.window_id;
    sendData.file_name = toString(fileInfo.completeBaseName());
    sendData.file_path = toString(savedPath);
    if (m_taskInfo) {
        sendData.project_type = toString(m_taskInfo->type);
    }
    sendMessageData(sendData);
    m_mainWindow->close();
}

void IPCManager::UpdateNctiFileInfoToServer(const QString& fileName, const QString& filePath)
{
    MessageData sendData;
    sendData.msg_type = MT_UPDATE;
    sendData.file_name = toString(fileName);
    sendData.file_path = toString(filePath);
    sendData.window_id = getWindowId();
    sendMessageData(sendData);
}

void IPCManager::sendTaskRequest()
{
    MessageData sendData;
    sendData.msg_type  = MT_TASK_DETAIL;
    sendData.window_id = getWindowId();
    sendMessageData(sendData);
}

} // namespace NCTI