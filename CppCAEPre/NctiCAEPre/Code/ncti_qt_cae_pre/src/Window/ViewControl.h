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

#ifndef VIEW_CONTROL_H
#define VIEW_CONTROL_H

#pragma once

#include "MainWindowModules.h"

namespace NCTI {

	/**
	 * @brief 视图控制类
	 * @details 负责处理视图相关的操作，如视角控制、显示控制等
	 */
	class ViewControl : public MainWindowModule
	{
		Q_OBJECT

	public:
		/**
		 * @brief 构造函数
		 * @param mainWindow 主窗口指针
		 */
		explicit ViewControl(MainWindow* mainWindow);

		/**
		 * @brief 模块初始化，在这里处理主窗口的信号
		 */
        void initialize() override;

        /**
		 * @brief 更新对象显示模式
		 */
        void updateDisplayMode(bool face, bool edge, bool vertex);

	public Q_SLOTS:
		/**
		 * @brief 等轴测视图槽函数
		 */
		void onIsometricView();
		
		/**
		 * @brief 缩放所有槽函数
		 */
		void onZoomAll();
		
		/**
		 * @brief 最大视图槽函数
		 */
		void onMaxView();
		
		/**
		 * @brief 显示所有槽函数
		 */
		void onShowAll();
		
		/**
		 * @brief 隐藏选择槽函数
		 */
		void onHideSel();
		
		/**
		 * @brief 显示选择槽函数
		 */
		void onShowSel();
		
		/**
		 * @brief 设置视图槽函数
		 * @param objName 对象名称
		 */
		void onSetView(const QString& objName);
		
		/**
		 * @brief 全选槽函数
		 */
		void onSelectAll();

		/**
		 * @brief 添加VTK视图槽函数
		 */
		void onAddVtkView();
		
		/**
		 * @brief 添加Vulkan视图槽函数
		 */
		void onAddVulkanView();

		/**
		 * @brief 选择模式槽函数
		 * @param objName 对象名称
		 */
		void onSelectMode(const QString& objName);
		
		/**
		 * @brief 显示模式槽函数
		 * @param objName 对象名称
		 */
		void onVisualMode(const QString& objName);

	private:
		/**
		 * @brief 更新选择模式
		 * @param bBody 体选择状态
		 * @param bFace 面选择状态
		 * @param bEdge 边选择状态
		 * @param bVertex 点选择状态
		 */
		void updateSelMode(bool bBody, bool bFace, bool bEdge, bool bVertex);
	};

} // namespace NCTI

#endif // VIEW_CONTROL_H