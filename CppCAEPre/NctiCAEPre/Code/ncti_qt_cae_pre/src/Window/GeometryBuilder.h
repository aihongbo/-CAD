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

#ifndef GEOMETRY_BUILDER_H
#define GEOMETRY_BUILDER_H

#pragma once

#include "MainWindowModules.h"

namespace NCTI {

	/**
	 * @brief 几何构建器类
	 * @details 负责处理几何建模相关的操作，包括基本体创建、布尔运算、特征操作等
	 */
	class GeometryBuilder : public MainWindowModule
	{
		Q_OBJECT

	public:
		/**
		 * @brief 构造函数
		 * @param mainWindow 主窗口指针
		 */
		explicit GeometryBuilder(MainWindow* mainWindow);

		/**
		 * @brief 模块初始化，在这里处理主窗口的信号
		 */
		void initialize() override;

	private Q_SLOTS:
		/**
		 * @brief 执行长方体命令槽函数
		 */
		void onExecuteBox();
		
		/**
		 * @brief 执行圆柱体命令槽函数
		 */
		void onExecuteCylinder();

		/**
		 * @brief 执行布尔运算命令槽函数
		 */
		void onExecuteBoolean();
		
		/**
		 * @brief 执行圆角命令槽函数
		 */
		void onExecuteFillet();
		
		/**
		 * @brief 执行倒角命令槽函数
		 */
		void onExecuteChamfer();
		
		/**
		 * @brief 几何平移槽函数
		 */
		void onGeoPan();
		
		/**
		 * @brief 几何缩放槽函数
		 */
		void onGeoZoom();
		
		/**
		 * @brief 几何旋转槽函数
		 */
		void onGeoRotate();

		/**
		 * @brief 移除特征槽函数
		 */
		void onRemoveFeature();
		
		/**
		 * @brief 移除面槽函数
		 */
		void onRemoveFace();
		
		/**
		 * @brief 执行抽取子对象命令槽函数
		 */
		void onExecuteExtractSubObj();
		
		/**
		 * @brief 执行填充内环命令槽函数
		 */
		void onExecuteFillLoop();
		
		/**
		 * @brief 执行组合命令槽函数
		 */
		void onExecuteCompound();
		
		/**
		 * @brief 执行爆炸体命令槽函数
		 */
		void onExecuteExplodeBody();
		
		/**
		 * @brief 执行缝合命令槽函数
		 */
		void onExecuteSewing();
		
		/**
		 * @brief 执行分离面命令槽函数
		 */
		void onExecuteSeparatFace();
		
		/**
		 * @brief 创建延伸面槽函数
		 */
		void onCreateExtendFace();
		
		/**
		 * @brief 线性阵列槽函数
		 */
		void onLinearArray();
		
		/**
		 * @brief 旋转阵列槽函数
		 */
		void onRotateArray();
		
		/**
		 * @brief 曲线阵列槽函数
		 */
		void onCurveArray();
		
		/**
		 * @brief 曲线偏移槽函数
		 */
		void onCurveOffset();
		
		/**
		 * @brief 执行建模命令槽函数
		 * @param command 命令名称
		 */
		void onExecuteModeling(const char* command);
		
		/**
		 * @brief 执行单位导出命令槽函数
		 */
		void onExecuteUnitExport();

	};

} // namespace NCTI

#endif // GEOMETRY_BUILDER_H