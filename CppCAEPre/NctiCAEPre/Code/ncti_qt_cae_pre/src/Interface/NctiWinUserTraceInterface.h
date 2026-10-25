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

#ifndef NctiWinUserTraceInterface_H
#define NctiWinUserTraceInterface_H

#include "NctiSPUserTraceInterface.h"

namespace NCTI
{
	class NctiBaseView;
	class NctiRenderOperator;
	class NctiWindowPlatform;

	class NctiPCDeformationCage;
	class NctiPCDeformationCageMouse;
	class NctiObjectTree;
	class MainWindow;
	
	/**
	 * @brief 窗口用户跟踪接口类
	 * @details 实现用户操作跟踪功能的接口类，继承自NctiSPUserTraceInterface
	 */
	class NctiWinUserTraceInterface : public NctiSPUserTraceInterface
	{
	public:
		/**
		 * @brief 构造函数
		 * @param i_pMain 主窗口指针
		 */
		NctiWinUserTraceInterface(MainWindow* i_pMain);
		
		/**
		 * @brief 析构函数
		 */
		~NctiWinUserTraceInterface();

	public:
		/**
		 * @brief 通知选择数据改变
		 */
		void NotifySelectionDataChanged() override;
		
		/**
		 * @brief 历史记录成功结束
		 */
		void HistoryIsEndBySucceeded() override;
		
		/**
		 * @brief 历史记录失败结束
		 */
		void HistoryIsEndByFailed() override;
		
		/**
		 * @brief 撤销重做开始
		 */
		void UndoAndRedoStart() override;
		
		/**
		 * @brief 撤销重做结束
		 */
		void UndoAndRedoEnd() override;
		
		/**
		 * @brief 元素树改变
		 * @param pDocView 文档视图管理器指针
		 */
		void ElementTreeIsChanged(NctiDocViewManager* pDocView) override;

	public:
		MainWindow* m_MainWindow;  ///< 主窗口指针
	};
}

#endif