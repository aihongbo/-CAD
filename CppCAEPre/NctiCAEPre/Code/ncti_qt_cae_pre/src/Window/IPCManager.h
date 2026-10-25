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

#ifndef IPC_MANAGER_H
#define IPC_MANAGER_H

#pragma once

#include "MainWindowModules.h"

#include <QLocalSocket>

namespace NCTI {

	/**
	 * @brief 任务信息结构体
	 * @details 存储任务相关的信息
	 */
	struct TaskInfo
	{
		QString type;        ///< 任务类型
		QString filePath;    ///< 文件路径
		int geometry   = -1; ///< 几何类型
		int constraint = -1; ///< 约束类型
		int mesh       = -1; ///< 网格类型
	};

	class MessageData;
	
	/**
	 * @brief IPC管理器类
	 * @details 负责处理进程间通信相关的操作
	 */
	class IPCManager : public MainWindowModule
	{
		Q_OBJECT

	public:
		/**
		 * @brief 构造函数
		 * @param mainWindow 主窗口指针
		 */
		explicit IPCManager(MainWindow* mainWindow);

		/**
		 * @brief 模块初始化，在这里处理主窗口的信号
		 */
		void initialize() override;

	public:
		/**
		 * @brief 运行任务
		 */
		void runTask();
		
		/**
		 * @brief 初始化任务信息
		 * @param t 任务类型
		 * @param f 文件路径
		 * @param g 几何类型
		 * @param c 约束类型
		 * @param m 网格类型
		 */
		void initTaskInfo(const QString& t, const QString& f, int g, int c, int m);
		
		/**
		 * @brief 获取任务信息
		 * @return 任务信息指针
		 */
		TaskInfo* GetTaskInfo();
		
		/**
		 * @brief 获取窗口ID
		 * @return 窗口ID
		 */
		int64_t getWindowId();
		
		/**
		 * @brief 创建本地套接字
		 * @param socketName 套接字名称
		 * @return 创建成功返回true，否则返回false
		 */
		bool createLocalSocket(const QString& socketName);
		
		/**
		 * @brief 连接成功槽函数
		 */
		void onConnected();
		
		/**
		 * @brief 准备读取槽函数
		 */
		void onReadyRead();
		
		/**
		 * @brief 断开连接槽函数
		 */
		void onDisconnected();
		
		/**
		 * @brief 发送消息数据
		 * @param data 消息数据
		 */
		void sendMessageData(const MessageData& data);
		
		/**
		 * @brief 处理退出消息类型
		 * @param data 消息数据
		 */
		void onMsgTypeExit(const MessageData& data);
		
		/**
		 * @brief 处理退出保存消息类型
		 * @param data 消息数据
		 */
		void onMsgTypeExitSave(const MessageData& data);
		
		/**
		 * @brief 处理文档脏消息类型
		 * @param data 消息数据
		 */
		void onMsgTypeDocDirty(const MessageData& data);
		
		/**
		 * @brief 处理文档刷新消息类型
		 * @param data 消息数据
		 */
        void onMsgTypeDocRefresh(const MessageData& data);

		/**
		 * @brief 处理运行任务消息类型
		 * @param msgData 消息数据
		 */
        void onMsgTypeRunTask(const MessageData& msgData);
		
		/**
		 * @brief 更新NCTI文件信息到服务器
		 * @param fileName 文件名
		 * @param filePath 文件路径
		 */
		void UpdateNctiFileInfoToServer(const QString& fileName, const QString& filePath);

		/**
		 * @brief 发送任务请求
		*/
        void sendTaskRequest();
	private:
		std::unique_ptr<QLocalSocket> m_socket;    ///< 本地套接字
		std::unique_ptr<TaskInfo> m_taskInfo;      ///< 任务信息
		QByteArray m_messageBuffer;                ///< 消息缓冲区，用于处理连续的JSON消息
	};

} // namespace NCTI

#endif // IPC_MANAGER_H