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

#include <QObject>
#include "dcl_ncti_qt_script_edit.h"

namespace NCTI
{
	class NctiQtScriptExecutor;
	
	/**
	 * @brief Qt脚本调试器类
	 * @details 提供脚本调试功能，包括断点管理、单步执行等
	 */
	class NCTI_QT_SCRIPT_EDIT NctiQtScriptDebugger : public QObject
	{
		Q_OBJECT
	public:
		/**
		 * @brief 构造函数
		 * @param parent 父对象
		 */
		explicit NctiQtScriptDebugger(QObject *parent = nullptr);
		
		/**
		 * @brief 析构函数
		 */
		virtual ~NctiQtScriptDebugger();

		/**
		 * @brief 设置脚本执行器
		 * @param script 脚本执行器指针
		 */
		void setExecutor(NctiQtScriptExecutor* script);
		
		/**
		 * @brief 获取脚本执行器
		 * @return 脚本执行器指针
		 */
		NctiQtScriptExecutor* getExecutor() const;

		/**
		 * @brief 设置脚本内容
		 * @tparam T 内容类型
		 * @param content 脚本内容
		 */
		template <typename T>
		void setContent(T&& content)
		{
			m_content = std::forward<T>(content);
			setCurrentBreakpointBlockNumber(-1);
		}
		
		/**
		 * @brief 获取脚本内容
		 * @return 脚本内容
		 */
		const QString& getContent() const;

		/**
		 * @brief 检查是否包含断点
		 * @param blockNumber 块编号
		 * @return true表示包含断点，false表示不包含
		 */
		bool containsBreakpoint(int blockNumber) const;
		
		/**
		 * @brief 添加断点
		 * @param blockNumber 块编号
		 * @param enable 是否启用
		 */
		void addBreakpoint(int blockNumber, bool enable = true);
		
		/**
		 * @brief 移除断点
		 * @param blockNumber 块编号
		 */
		void removeBreakpoint(int blockNumber);
		
		/**
		 * @brief 移除所有断点
		 */
		void removeAllBreakpoint();
		
		/**
		 * @brief 启用/禁用断点
		 * @param blockNumber 块编号
		 * @param enable 是否启用
		 */
		void enableBreakpoint(int blockNumber, bool enable);
		
		/**
		 * @brief 启用/禁用所有断点
		 * @param enable 是否启用
		 */
		void enableAllBreakpoint(bool enable);
		
		/**
		 * @brief 检查断点是否启用
		 * @param blockNumber 块编号
		 * @return true表示启用，false表示禁用
		 */
		bool isEnableBreakpoint(int blockNumber);

		/**
		 * @brief 运行到下一个断点
		 */
		void runNextBreakpoint();
		
		/**
		 * @brief 单步执行下一步
		 */
		void runNextStep();
		
		/**
		 * @brief 停止执行
		 */
		void stop();

		/**
		 * @brief 设置当前断点块编号
		 * @param blockNumber 块编号
		 */
		void setCurrentBreakpointBlockNumber(int blockNumber);
		
		/**
		 * @brief 获取当前断点块编号
		 * @return 块编号
		 */
		int getCurrentBreakpointBlockNumber() const;

		/**
		 * @brief 当前断点改变信号
		 * @param previous 上一个断点
		 * @param current 当前断点
		 */
		Q_SIGNAL void sigCurrentBreakpointChanged(int previous, int current);
		
		/**
		 * @brief 断点状态改变信号
		 * @param blockNumber 块编号
		 * @param enable 是否启用
		 */
		Q_SIGNAL void sigBreakpointStateChanged(int blockNumber, int enable);
		
		/**
		 * @brief 断点添加信号
		 * @param blockNumber 块编号
		 * @param enable 是否启用
		 */
		Q_SIGNAL void sigBreakpointAdded(int blockNumber, bool enable);
		
		/**
		 * @brief 断点移除信号
		 * @param blockNumber 块编号
		 */
		Q_SIGNAL void sigBreakpointRemoved(int blockNumber);

		/**
		 * @brief 执行状态枚举
		 */
		enum ExecuteState
		{
			ExecuteStateRunning,  ///< 正在运行
			ExecuteStateStopped,  ///< 已停止
		};
		
		/**
		 * @brief 执行状态改变信号
		 * @param state 执行状态
		 */
		Q_SIGNAL void sigExecuteStateChanged(int state);

	private:
		/**
		 * @brief 断点结构体
		 */
		struct Breakpoint
		{
			int blockNumber;  ///< 块编号
			bool enable;      ///< 是否启用
		};
		
		/**
		 * @brief 查找断点
		 * @param blockNumber 块编号
		 * @return 断点迭代器
		 */
		QList<Breakpoint>::Iterator findBreakpoint(int blockNumber);
		
		/**
		 * @brief 设置执行状态
		 * @param state 执行状态
		 */
		void setState(ExecuteState state);

	private:
		Q_DISABLE_COPY_MOVE(NctiQtScriptDebugger);  ///< 禁用拷贝和移动
		NctiQtScriptExecutor* m_executor;           ///< 脚本执行器
		QString m_content;                          ///< 脚本内容
		QList<Breakpoint> m_breakpointList;         ///< 断点列表
		int m_currentBreakpointBlockNumber;         ///< 当前断点块编号
		ExecuteState m_executeState;                ///< 执行状态
	};
};