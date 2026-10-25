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

#ifndef AssemblyOperations_H
#define AssemblyOperations_H

#pragma once

#include "MainWindowModules.h"

namespace NCTI {

	
	/**
	 * @brief 装配操作类
	 * @details 负责处理装配相关的操作
	 */
	class AssemblyOperations : public MainWindowModule
	{
		Q_OBJECT

	public:
		/**
		 * @brief 构造函数
		 * @param mainWindow 主窗口指针
		 */
		explicit AssemblyOperations(MainWindow* mainWindow);

		/**
		 * @brief 模块初始化，在这里处理主窗口的信号
		 */
		void initialize() override;

	private Q_SLOTS:
		/**
		 * @brief 固定约束槽函数
		 */
		void onConsFix();
		
		/**
		 * @brief 重合约束槽函数
		 */
		void onConsCoincident();

		/**
		 * @brief 平行约束槽函数
		 */
		void onConsParallel();

		/**
		 * @brief 同心约束槽函数
		 */
		void onConsConcentric();

		/**
		 * @brief 垂直约束槽函数
		 */
		void onConsPerpendicular();

		/**
		 * @brief 距离约束槽函数
		 */
		void onConsDistance();

		/**
		 * @brief 角度约束槽函数
		 */
		void onConsAngle();

		/**
		 * @brief 角度约束槽函数
		 */
		void onConsEqualDistance();

		/**
		 * @brief 导出装配约束脚本槽函数
		 */
		void onAssExport();
	};

} // namespace NCTI

#endif // AssemblyOperations_H