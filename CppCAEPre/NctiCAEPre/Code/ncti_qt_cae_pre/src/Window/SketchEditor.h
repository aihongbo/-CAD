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

#ifndef SKETCH_EDITOR_H
#define SKETCH_EDITOR_H

#pragma once

#include "MainWindowModules.h"

namespace NCTI {

	class NctiWindowPlatform;
	
	/**
	 * @brief 草图编辑器类
	 * @details 负责处理草图编辑相关的操作
	 */
	class SketchEditor : public MainWindowModule
	{
		Q_OBJECT

	public:
		/**
		 * @brief 构造函数
		 * @param mainWindow 主窗口指针
		 */
		explicit SketchEditor(MainWindow* mainWindow);

		/**
		 * @brief 模块初始化，在这里处理主窗口的信号
		 */
		void initialize() override;

	private Q_SLOTS:
		/**
		 * @brief 新建草图槽函数
		 */
		void onDraftNew();
		
		/**
		 * @brief 编辑草图槽函数
		 */
		void onDraftEdit();
		
		/**
		 * @brief 草图坐标槽函数
		 */
		void onDraftCoord();
		
		/**
		 * @brief 删除草图槽函数
		 */
		void onDeleteDraft();

		/**
		 * @brief 草图矩形槽函数
		 */
		void onDraftRectangle();
		
		/**
		 * @brief 草图圆槽函数
		 */
		void onDraftCircle();
		
		/**
		 * @brief 草图多边形槽函数
		 */
		void onDraftPolygon();
		
		/**
		 * @brief 草图椭圆槽函数
		 */
		void onDraftEllipse();
		
		/**
		 * @brief 草图圆到圆槽函数
		 */
		void onDraftCircleToCircle();
		
		/**
		 * @brief 草图线槽函数
		 */
		void onDraftLine();
		
		/**
		 * @brief 草图圆弧槽函数
		 */
		void onDraftArc();
		
		/**
		 * @brief 草图线框槽函数
		 */
		void onDraftWire();
		
		/**
		 * @brief 草图B样条槽函数
		 */
		void onDraftBspline();
		
		/**
		 * @brief 草图中心线槽函数
		 */
		void onDraftCenterline();
		
		/**
		 * @brief 草图点槽函数
		 */
		void onDraftPoint();

		/**
		 * @brief 草图移到顶层槽函数
		 */
		void onDraftMoveToTop();
		
		/**
		 * @brief 草图移到底层槽函数
		 */
		void onDraftMoveToBottom();
		
		/**
		 * @brief 草图上移槽函数
		 */
		void onDraftUpside();
		
		/**
		 * @brief 草图下移槽函数
		 */
		void onDraftDownside();
		
		/**
		 * @brief 草图并集槽函数
		 */
		void onDraftUnit();
		
		/**
		 * @brief 草图差集槽函数
		 */
		void onDraftCut();
		
		/**
		 * @brief 草图内爆槽函数
		 */
		void onDraftImplode();
		
		/**
		 * @brief 草图外爆槽函数
		 */
		void onDraftExplode();

		/**
		 * @brief 草图重置视图槽函数
		 */
		void onDraftResetView();
		
		/**
		 * @brief 草图退出槽函数
		 */
		void onDraftExit();

		/**
		 * @brief 草图拉伸槽函数
		 */
		void onDraftExtrude();
		
		/**
		 * @brief 草图旋转槽函数
		 */
		void onDraftRotate();
		
		/**
		 * @brief 草图布尔运算槽函数
		 */
		void onDraftFeatureBoolean();

		/**
		 * @brief 草图重建槽函数
		 */
		void onDraftRebuild();
		
		/**
		 * @brief 草图模型化槽函数
		 */
		void onDraftModelization();

		/**
		 * @brief 草图平行约束
		 */
		void onDraftParallel();

		/**
		 * @brief 草图垂直约束
		 */
		void onDraftPerpendicular();

		/**
		 * @brief 草图相切约束
		 */
		void onDraftTangent();

		/**
		 * @brief 草图固定约束
		 */
		void onDraftFix();

		/**
		 * @brief 草图重合约束
		 */
		void onDraftCoincident();

		/**
		 * @brief 草图同心约束
		 */
		void onDraftConcentric();

		/**
		 * @brief 草图等半径约束
		 */
		void onDraftEqualRadius();

		/**
		 * @brief 草图对称约束
		 */
		void onDraftSymmetric();

		/**
		 * @brief 草图距离约束
		 */
		void onDraftDistance();

		/**
		 * @brief 草图角度约束
		 */
		void onDraftAngle();

		/**
		 * @brief 草图半径约束
		 */
		void onDraftRadius();
	};

} // namespace NCTI

#endif // SKETCH_EDITOR_H