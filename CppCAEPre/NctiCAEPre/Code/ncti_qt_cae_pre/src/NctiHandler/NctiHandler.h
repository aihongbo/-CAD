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

#include <QWidget>
#include "ncti_base.h"

namespace NCTI
{
	class NctiWindowPlatform;
	class NctiDocument;
	
	/**
	 * @brief NCTI处理器类
	 * @details 提供各种NCTI功能的静态方法集合
	 */
	class NctiHandler
	{
	public: 
		/**
		 * @brief 开始宏录制
		 */
		static void StartRecord();

		/**
		 * @brief 结束宏录制
		 * @param filePath 文件路径
		 */
		static void EndRecord(const QString &filePath = QString());

		/**
		 * @brief AI识别
		 * @param i_pPlatform 窗口平台指针
		 */
		static void AiRecognition(NctiWindowPlatform* i_pPlatform);

		/**
		 * @brief 孔识别
		 * @param i_pPlatform 窗口平台指针
		 */
		static void HoleRecognition(NctiWindowPlatform* i_pPlatform);
		
		/**
		 * @brief 选择特征面
		 * @param i_pPlatform 窗口平台指针
		 */
		static void SelFeatureFace(NctiWindowPlatform* i_pPlatform);

		/**
		 * @brief 导出链接面
		 * @param i_pPlatform 窗口平台指针
		 * @param i_filePath 文件路径
		 */
		static void ExportLinkFace(NctiWindowPlatform* i_pPlatform, const QString& i_filePath);

		/**
		 * @brief 拓扑结构显示
		 * @param i_pPlatform 窗口平台指针
		 */
		static void TopoStructureDisplay(NctiWindowPlatform* i_pPlatform);
		
		/**
		 * @brief UV网格显示
		 * @param i_pPlatform 窗口平台指针
		 */
		static void UVGridDisplay(NctiWindowPlatform* i_pPlatform);

#pragma region 草图
		/**
		 * @brief 新建草图
		 * @param i_pPlatform 窗口平台指针
		 * @return 操作结果
		 */
		static Ncti_Boolean SketchNew(NctiWindowPlatform* i_pPlatform);
		
		/**
		 * @brief 删除草图
		 * @param i_pPlatform 窗口平台指针
		 * @return 操作结果
		 */
		static Ncti_Boolean SketchDelete(NctiWindowPlatform* i_pPlatform);
		
		/**
		 * @brief 草图坐标
		 * @param i_pPlatform 窗口平台指针
		 * @return 操作结果
		 */
		static Ncti_Boolean SketchCoord(NctiWindowPlatform* i_pPlatform);
		
		/**
		 * @brief 草图矩形
		 * @param i_pPlatform 窗口平台指针
		 * @return 操作结果
		 */
		static Ncti_Boolean SketchRectangle(NctiWindowPlatform* i_pPlatform);
		
		/**
		 * @brief 草图圆
		 * @param i_pPlatform 窗口平台指针
		 * @return 操作结果
		 */
		static Ncti_Boolean SketchCircle(NctiWindowPlatform* i_pPlatform);
		
		/**
		 * @brief 草图多边形
		 * @param i_pPlatform 窗口平台指针
		 * @return 操作结果
		 */
		static Ncti_Boolean SketchPolygon(NctiWindowPlatform* i_pPlatform);
		
		/**
		 * @brief 草图椭圆
		 * @param i_pPlatform 窗口平台指针
		 * @return 操作结果
		 */
		static Ncti_Boolean SketchEllipse(NctiWindowPlatform* i_pPlatform);
		
		/**
		 * @brief 草图圆到圆
		 * @param i_pPlatform 窗口平台指针
		 * @return 操作结果
		 */
		static Ncti_Boolean SketchCircleToCircle(NctiWindowPlatform* i_pPlatform);
		
		/**
		 * @brief 草图线
		 * @param i_pPlatform 窗口平台指针
		 * @return 操作结果
		 */
		static Ncti_Boolean SketchLine(NctiWindowPlatform* i_pPlatform);
		
		/**
		 * @brief 草图圆弧
		 * @param i_pPlatform 窗口平台指针
		 * @return 操作结果
		 */
		static Ncti_Boolean SketchArc(NctiWindowPlatform* i_pPlatform);
		
		/**
		 * @brief 草图线框
		 * @param i_pPlatform 窗口平台指针
		 * @return 操作结果
		 */
		static Ncti_Boolean SketchWire(NctiWindowPlatform* i_pPlatform);
		
		/**
		 * @brief 草图B样条
		 * @param i_pPlatform 窗口平台指针
		 * @return 操作结果
		 */
		static Ncti_Boolean SketchBspline(NctiWindowPlatform* i_pPlatform);
		
		/**
		 * @brief 草图中心线
		 * @param i_pPlatform 窗口平台指针
		 * @return 操作结果
		 */
		static Ncti_Boolean SketchCenterline(NctiWindowPlatform* i_pPlatform);
		
		/**
		 * @brief 草图点
		 * @param i_pPlatform 窗口平台指针
		 * @return 操作结果
		 */
		static Ncti_Boolean SketchPoint(NctiWindowPlatform* i_pPlatform);
		
		/**
		 * @brief 草图重置视图
		 * @param i_pPlatform 窗口平台指针
		 * @return 操作结果
		 */
		static Ncti_Boolean SketchResetView(NctiWindowPlatform* i_pPlatform);
		
		/**
		 * @brief 草图退出
		 * @param i_pPlatform 窗口平台指针
		 * @return 操作结果
		 */
		static Ncti_Boolean SketchExit(NctiWindowPlatform* i_pPlatform);
		
		/**
		 * @brief 草图拉伸
		 * @param i_pPlatform 窗口平台指针
		 * @return 操作结果
		 */
		static Ncti_Boolean SketchPrism(NctiWindowPlatform* i_pPlatform);
		
		/**
		 * @brief 草图旋转
		 * @param i_pPlatform 窗口平台指针
		 * @return 操作结果
		 */
		static Ncti_Boolean SketchRotate(NctiWindowPlatform* i_pPlatform); 
		
		/**
		 * @brief 草图布尔运算
		 * @param i_pPlatform 窗口平台指针
		 * @return 操作结果
		 */
		static Ncti_Boolean onDraftFeatureBoolean(NctiWindowPlatform* i_pPlatform);
		
		/**
		 * @brief 草图编辑
		 * @param i_pPlatform 窗口平台指针
		 * @return 操作结果
		 */
		static Ncti_Boolean SketchEdit(NctiWindowPlatform* i_pPlatform);
		
		/**
		 * @brief 草图模型化
		 * @param i_pPlatform 窗口平台指针
		 * @return 操作结果
		 */
		static Ncti_Boolean SketchModelization(NctiWindowPlatform* i_pPlatform);
		
		/**
		 * @brief 草图重建
		 * @param i_pPlatform 窗口平台指针
		 * @return 操作结果
		 */
		static Ncti_Boolean SketchRebuild(NctiWindowPlatform* i_pPlatform);
		
		/**
		 * @brief 草图移到顶层
		 * @param i_pPlatform 窗口平台指针
		 * @return 操作结果
		 */
		static Ncti_Boolean SketchMoveToTop(NctiWindowPlatform* i_pPlatform);
		
		/**
		 * @brief 草图移到底层
		 * @param i_pPlatform 窗口平台指针
		 * @return 操作结果
		 */
		static Ncti_Boolean SketchMoveToBottom(NctiWindowPlatform* i_pPlatform);
		
		/**
		 * @brief 草图上移
		 * @param i_pPlatform 窗口平台指针
		 * @return 操作结果
		 */
		static Ncti_Boolean SketchUpside(NctiWindowPlatform* i_pPlatform);
		
		/**
		 * @brief 草图下移
		 * @param i_pPlatform 窗口平台指针
		 * @return 操作结果
		 */
		static Ncti_Boolean SketchDownside(NctiWindowPlatform* i_pPlatform);
		
		/**
		 * @brief 草图并集
		 * @param i_pPlatform 窗口平台指针
		 * @return 操作结果
		 */
		static Ncti_Boolean SketchUnit(NctiWindowPlatform* i_pPlatform);
		
		/**
		 * @brief 草图差集
		 * @param i_pPlatform 窗口平台指针
		 * @return 操作结果
		 */
		static Ncti_Boolean SketchCut(NctiWindowPlatform* i_pPlatform);
		
		/**
		 * @brief 草图内爆
		 * @param i_pPlatform 窗口平台指针
		 * @return 操作结果
		 */
		static Ncti_Boolean SketchImplode(NctiWindowPlatform* i_pPlatform);
		
		/**
		 * @brief 草图外爆
		 * @param i_pPlatform 窗口平台指针
		 * @return 操作结果
		 */
		static Ncti_Boolean SketchExplode(NctiWindowPlatform* i_pPlatform);

		/**
		 * @brief 草图平行约束
		 * @param i_pPlatform 窗口平台指针
		 * @return 操作结果
		 */
		static Ncti_Boolean SketchParallel(NctiWindowPlatform* i_pPlatform);

		/**
		 * @brief 草图垂直约束
		 * @param i_pPlatform 窗口平台指针
		 * @return 操作结果
		 */
		static Ncti_Boolean SketchPerpendicular(NctiWindowPlatform* i_pPlatform);

		/**
		 * @brief 草图相切约束
		 * @param i_pPlatform 窗口平台指针
		 * @return 操作结果
		 */
		static Ncti_Boolean SketchTangent(NctiWindowPlatform* i_pPlatform);

		/**
		 * @brief 草图等半径约束
		 * @param i_pPlatform 窗口平台指针
		 * @return 操作结果
		 */
		static Ncti_Boolean SketchEqualRadius(NctiWindowPlatform* i_pPlatform);

		/**
		 * @brief 草图同心约束
		 * @param i_pPlatform 窗口平台指针
		 * @return 操作结果
		 */
		static Ncti_Boolean SketchConcentric(NctiWindowPlatform* i_pPlatform);

		/**
		 * @brief 草图固定约束
		 * @param i_pPlatform 窗口平台指针
		 * @return 操作结果
		 */
		static Ncti_Boolean SketchFix(NctiWindowPlatform* i_pPlatform);

		/**
		 * @brief 草图距离约束
		 * @param i_pPlatform 窗口平台指针
		 * @return 操作结果
		 */
		static Ncti_Boolean SketchDistance(NctiWindowPlatform* i_pPlatform);

#pragma endregion 草图

#pragma region Assembly
		/**
		 * @brief 固定约束
		 * @param i_pPlatform 窗口平台指针
		 * @return 操作结果
		 */
		static Ncti_Boolean AssFix(NctiWindowPlatform* i_pPlatform);

		/**
		 * @brief 重合约束
		 * @param i_pPlatform 窗口平台指针
		 * @return 操作结果
		 */
		static Ncti_Boolean AssCoincident(NctiWindowPlatform* i_pPlatform);

		/**
		 * @brief 平行约束
		 * @param i_pPlatform 窗口平台指针
		 * @return 操作结果
		 */
		static Ncti_Boolean AssParallel(NctiWindowPlatform* i_pPlatform);

		/**
		 * @brief 同心约束
		 * @param i_pPlatform 窗口平台指针
		 * @return 操作结果
		 */
		static Ncti_Boolean AssConcentric(NctiWindowPlatform* i_pPlatform);

		/**
		 * @brief 垂直约束
		 * @param i_pPlatform 窗口平台指针
		 * @return 操作结果
		 */
		static Ncti_Boolean AssPerpendicular(NctiWindowPlatform* i_pPlatform);

		/**
		 * @brief 距离约束
		 * @param i_pPlatform 窗口平台指针
		 * @return 操作结果
		 */
		static Ncti_Boolean AssDistance(NctiWindowPlatform* i_pPlatform);

		/**
		 * @brief 角度约束
		 * @param i_pPlatform 窗口平台指针
		 * @return 操作结果
		 */
		static Ncti_Boolean AssAngle(NctiWindowPlatform* i_pPlatform);

		/**
		 * @brief 角度约束
		 * @param i_pPlatform 窗口平台指针
		 * @return 操作结果
		 */
		static Ncti_Boolean AssEqualDistance(NctiWindowPlatform* i_pPlatform);

		/**
		 * @brief 导出装配约束脚本
		 * @param i_pPlatform 窗口平台指针
		 * @return 操作结果
		 */
		static Ncti_Boolean AssExport(NctiWindowPlatform* i_pPlatform);

#pragma endregion Assembly 
	};
}