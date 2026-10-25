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

#ifndef SIMULATION_CONTROLLER_H
#define SIMULATION_CONTROLLER_H

#pragma once

#include "MainWindowModules.h"

namespace NCTI {

	/**
	 * @brief 仿真控制器类
	 * @details 负责处理仿真相关的操作，包括网格生成、边界条件设置等
	 */
	class SimulationController : public MainWindowModule
	{
		Q_OBJECT

	public:
		/**
		 * @brief 构造函数
		 * @param mainWindow 主窗口指针
		 */
		explicit SimulationController(MainWindow* mainWindow);

		/**
		 * @brief 模块初始化，在这里处理主窗口的信号
		 */
		void initialize() override;

	private:
		/**
		 * @brief 获取网格类型
		 * @return 网格类型
		 */
		int getMeshType();

	private Q_SLOTS:
		/**
		 * @brief 添加力边界条件槽函数
		 */
		void onMeshAddForce();
		
		/**
		 * @brief 添加位移边界条件槽函数
		 */
		void onMeshAddSpc();
		
		/**
		 * @brief 添加材料属性槽函数
		 */
		void onMeshAddMat();
		
		/**
		 * @brief 从表面生成网格槽函数
		 */
		void onMeshFromSurface();
		
		/**
		 * @brief 从体生成网格槽函数
		 */
		void onMeshFromVolume();
		
		/**
		 * @brief 显示网格质量槽函数
		 */
		void onMeshShowMeshQuality();

		/**
		 * @brief 选择模式槽函数
		 * @param objectName 对象名称
		 */
		void onSelectMode(const QString& objectName);

        /**
         * @brief 快速选择
         */
        void onQuickSelect();

        /**
         * @brief 切换网格引擎
         */
        void onModifyMeshType();

	};

} // namespace NCTI

#endif // SIMULATION_CONTROLLER_H