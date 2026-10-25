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

#pragma once

#include "dcl_ncti_qt_script_edit.h"
#include <QObject>

namespace NCTI
{
	/**
	 * @brief Qt脚本执行器类
	 * @details 负责执行脚本代码并处理执行结果
	 */
	class NCTI_QT_SCRIPT_EDIT NctiQtScriptExecutor : public QObject
	{
		Q_OBJECT
	public:
		/**
		 * @brief 构造函数
		 * @param parent 父对象
		 */
		explicit NctiQtScriptExecutor(QObject *parent = nullptr);
		
		/**
		 * @brief 析构函数
		 */
		virtual ~NctiQtScriptExecutor();

		/**
		 * @brief 执行命令
		 * @param content 命令内容
		 * @param re 是否重新执行
		 */
		virtual void excuteCommand(const QString& content, bool re=false);

		/**
		 * @brief 消息类型枚举
		 */
		enum MessageType
		{
			MessageTypeLog,      ///< 日志消息
			MessageTypeCode,     ///< 代码消息
			MessageTypeError,    ///< 错误消息
			MessageTypeNewLine,  ///< 换行消息
		};

		/**
		 * @brief 执行状态枚举
		 */
		enum ExecuteState {
			ExecuteStateStopped,  ///< 已停止
			ExecuteStateRunning,  ///< 正在运行
		};

		/**
		 * @brief 状态改变信号
		 * @param state 执行状态
		 */
		Q_SIGNAL void sigStateChanged(int state);
		
		/**
		 * @brief 消息信号
		 * @param message 消息内容
		 * @param type 消息类型
		 */
		Q_SIGNAL void signalMessage(QString message, int type= MessageTypeLog);
		
		/**
		 * @brief 清空信号
		 */
		Q_SIGNAL void signalClear();
		
		/**
		 * @brief 缩放信号
		 */
		Q_SIGNAL void signalZoom();

		/**
		 * @brief 获取标准输出消息
		 * @return 标准输出消息
		 */
		const QString& getStdoutMessage() const { return m_stdoutMessage; }
		
		/**
		 * @brief 获取错误输出消息
		 * @return 错误输出消息
		 */
		const QString& getStderrtMessage() const { return m_stderrMessage; }

	protected:
		/**
		 * @brief 执行脚本
		 * @param content 脚本内容
		 */
		virtual void excuteScript(const QString& content);
		
		/**
		 * @brief 设置执行状态
		 * @param state 执行状态
		 */
		void setState(ExecuteState state);
		
		/**
		 * @brief 获取执行状态
		 * @return 执行状态
		 */
		ExecuteState getState() const;

	private:
		ExecuteState m_state;          ///< 执行状态
		QString m_stdoutMessage;       ///< 标准输出消息
		QString m_stderrMessage;       ///< 错误输出消息
	};
};