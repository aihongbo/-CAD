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

#ifndef PREFERENCE_SETTINGS_H
#define PREFERENCE_SETTINGS_H

#pragma once

#include "MainWindowModules.h"


namespace NCTI {
	/**
	 * @brief 偏好设置类
	 * @details 负责处理用户偏好设置，包括主题、语言、颜色等配置
	 */

	class PreferenceSettings : public MainWindowModule
	{
		Q_OBJECT

	public:
		/**
		 * @brief 构造函数
		 * @param mainWindow 主窗口指针
		 */
		explicit PreferenceSettings(MainWindow* mainWindow);

		/**
		 * @brief 模块初始化，在这里处理主窗口的信号
		 */
		void initialize() override;

		/**
		 * @brief 初始化选择视觉模式
		 */
		void initSelVisualMode();
		
		/**
		 * @brief 处理背景颜色设置
		 * @param topColor 顶部颜色
		 * @param bottomColor 底部颜色
		 */
		void handleBackgroundColorSetting(QColor topColor, QColor bottomColor);
		
		/**
		 * @brief 处理模型颜色设置
		 * @param faceColor 面颜色
		 * @param edgeColor 边颜色
		 * @param vertexColor 点颜色
		 */
		void handleModelColorSetting(QColor faceColor, QColor edgeColor, QColor vertexColor);
		
		/**
		 * @brief 处理对象显示模式
		 * @param faceState 面状态
		 * @param edgeState 边状态
		 * @param vertexState 点状态
		 */
		void handleObjectDisplayMode(bool faceState, bool edgeState, bool vertexState);

		/**
		 * @brief 处理备份设置
		 * @param openState 开启状态
		 * @param path 备份路径
		 * @param time 时间间隔
		 */
		static void handleBackups(bool openState, const std::string& path, int time);


        /**
         * @brief 基于JSON加载UI配置槽函数
         */
        static void LoadingUIBasedOnJson(MainWindow* mainWindow);

        /**
         * @brief 应用配置
         */
        static std::string getConfigDir();
        static std::string getConfigFile();
        static void initDefaultCAE();

	public Q_SLOTS:
        /**
         * @brief 打开选项卡
         */
        void openOptions();
	};

} // namespace NCTI

#endif // PREFERENCE_SETTINGS_H