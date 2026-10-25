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

#ifndef MEASUREMENT_TOOLS_H
#define MEASUREMENT_TOOLS_H

#pragma once

#include "MainWindowModules.h"

namespace NCTI {

	/**
	 * @brief 测量工具类
	 * @details 负责处理各种测量操作，包括点、长度、角度等测量
	 */
	class MeasurementTools : public MainWindowModule
	{
		Q_OBJECT

	public:
		/**
		 * @brief 构造函数
		 * @param mainWindow 主窗口指针
		 */
		explicit MeasurementTools(MainWindow* mainWindow);

		/**
		 * @brief 模块初始化，在这里处理主窗口的信号
		 */
		void initialize() override;

	private Q_SLOTS:
		/**
		 * @brief 测量点槽函数
		 */
		void onMeasuringPt();
		
		/**
		 * @brief 测量长度槽函数
		 */
		void onMeasuringLen();
		
		/**
		 * @brief 测量中点槽函数
		 */
		void onMeasuringMid();
		
		/**
		 * @brief 测量中心槽函数
		 */
		void onMeasuringCenter();
		
		/**
		 * @brief 测量半径槽函数
		 */
		void onMeasuringRadius();
		
		/**
		 * @brief 测量向量槽函数
		 */
		void onMeasuringVector();
		
		/**
		 * @brief 测量角度槽函数
		 */
		void onMeasuringAngle();
	};

} // namespace NCTI

#endif // MEASUREMENT_TOOLS_H