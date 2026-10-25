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

#ifndef AI_FEATURE_RECOGNIZER_H
#define AI_FEATURE_RECOGNIZER_H

#pragma once

#include "MainWindowModules.h"

namespace NCTI {

	/**
	 * @brief AI特征识别器类
	 * @details 负责处理AI特征识别相关的操作，包括孔识别、圆角识别等
	 */
	class AIFeatureRecognizer : public MainWindowModule
	{
		Q_OBJECT

	public:
		/**
		 * @brief 构造函数
		 * @param mainWindow 主窗口指针
		 */
		explicit AIFeatureRecognizer(MainWindow* mainWindow);

		/**
		 * @brief 模块初始化，在这里处理主窗口的信号
		 */
		void initialize() override;

	private Q_SLOTS:
		/**
		 * @brief AI识别槽函数
		 */
		void onAiRecognition();
		
		/**
		 * @brief 选择特征面槽函数
		 */
		void onSelFeatureFace();
		
		/**
		 * @brief 搜索循环槽函数
		 */
		void onSearchLoop();
		
		/**
		 * @brief 搜索连接槽函数
		 */
		void onSearchConnect();
		
		/**
		 * @brief 搜索相同连接槽函数
		 */
		void onSearchSameConnect();
		
		/**
		 * @brief 搜索无平面连接槽函数
		 */
		void onSearchNoPlaneConnect();

		/**
		 * @brief 特征标识槽函数
		 */
		void onFeatureIdentifier();
		
		/**
		 * @brief 特征列表槽函数
		 */
		void onFeatureList();

		/**
		 * @brief 圆角标识槽函数
		 */
		void onFilletIdentifier();
		
		/**
		 * @brief 孔标识槽函数
		 */
		void onHoleIdentifier();
		
		/**
		 * @brief Logo标识槽函数
		 */
		void onLogoIdentifier();

		/**
		 * @brief 圆角提取槽函数
		 */
		void onFilletExtract();
		
		/**
		 * @brief 孔提取槽函数
		 */
		void onHoleExtract();
		
		/**
		 * @brief Logo提取槽函数
		 */
		void onLogoExtract();

		/**
		 * @brief 拓扑结构槽函数
		 */
		void onTopoStructure();
		
		/**
		 * @brief 边属性槽函数
		 */
		void onEdgeAttribute();
		
		/**
		 * @brief 面属性槽函数
		 */
		void onFaceAttribute();
		
		/**
		 * @brief UV网格槽函数
		 */
		void onUVGrid();
		
		/**
		 * @brief 导出链接面槽函数
		 */
		void onExportLinkFace();

		/**
		 * @brief 圆角识别槽函数
		 */
		void onRoundRecognition();

		/**
		 * @brief 倒角识别槽函数
		 */
		void onChamferRecognition();
		
		/**
		 * @brief 孔识别槽函数
		 */
		void onThroughHoleRecognition();
	};

} // namespace NCTI

#endif // AI_FEATURE_RECOGNIZER_H