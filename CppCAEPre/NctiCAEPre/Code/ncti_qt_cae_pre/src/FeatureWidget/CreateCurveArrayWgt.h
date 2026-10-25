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
#ifndef CREATECURVEARRAYWGT
#define CREATECURVEARRAYWGT

#include "NctiBaseDialog.h"
#include "ncti_base.h"

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>

namespace NCTI
{
class NctiDocument;
class NctiDisplayObject;
class NctiPosition;
class NctiVector;

/**
 * @brief 创建曲线阵列窗口类
 * @details 用于创建和设置曲线阵列参数的对话框窗口
 */
class CreateCurveArrayWgt : public NctiBaseDialog
{
	Q_OBJECT
public:
	/**
	 * @brief 构造函数
	 * @param i_pDocument 文档指针
	 * @param parent 父窗口指针
	 */
	explicit CreateCurveArrayWgt(NctiDocument* i_pDocument, QWidget* parent = nullptr);

private:
	/**
	 * @brief 初始化UI界面
	 */
	void initUI();
	
	/**
	 * @brief 更新数据
	 * @return 更新成功返回true，否则返回false
	 */
	bool UpDate();

private Q_SLOTS:
	/**
	 * @brief 确定按钮槽函数
	 */
	void onOK();
	
	/**
	 * @brief 取消按钮槽函数
	 */
	void onCanle();
	
	/**
	 * @brief 选择第一个对象槽函数
	 */
	void onSelectObject1();
	
	/**
	 * @brief 选择第二个对象槽函数
	 */
	void onSelectObject2();
	
	/**
	 * @brief 预览按钮槽函数
	 */
	void onPreview();

public:
	QLabel* selectCurveLab;        ///< 选择曲线标签
	QLabel* curveSelectedLab;      ///< 曲线选择状态标签
	QLabel* selectBodyLab;         ///< 选择体标签
	QLabel* bodySelectedLab;       ///< 体选择状态标签
	QLabel* newQuantityLab;        ///< 新数量标签
	QPushButton* selectCurveBtn;   ///< 选择曲线按钮
	QPushButton* selectBodyBtn;    ///< 选择体按钮
	QPushButton* previewBtn;       ///< 预览按钮
	QPushButton* cancelBtn;        ///< 取消按钮
	QPushButton* confrimBtn;       ///< 确认按钮
	QLineEdit* newQuantityEdit;    ///< 新数量编辑框

private:
	NctiDocument* m_pDocument;           ///< 文档指针
	NctiDisplayObject* m_DisplayObject1; ///< 第一个显示对象
	NctiDisplayObject* m_DisplayObject2; ///< 第二个显示对象
	int newQuantity;                     ///< 新数量
	double curveLength;                  ///< 曲线长度
	std::vector<NctiPosition> o_points;  ///< 点列表
	std::vector<NctiVector> o_tangents;  ///< 切线列表
};

}
#endif // !CREATECURVEARRAYWGT