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
#ifndef CREATEGEOZOOMWGT_H
#define CREATEGEOZOOMWGT_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include "NctiBaseDialog.h"
#include "ncti_base.h"

namespace NCTI
{
class NctiDocument;
class NctiDisplayObject;
class NctiWindowPlatform;
class NctiPosition;

/**
 * @brief 创建几何缩放窗口类
 * @details 用于创建和设置几何缩放参数的对话框窗口
 */
class CreateGeoZoomWgt : public NctiBaseDialog
{
	Q_OBJECT

public:
	/**
	 * @brief 构造函数
	 * @param i_pDocument 文档指针
	 * @param parent 父窗口指针
	 */
	explicit CreateGeoZoomWgt(NctiDocument* i_pDocument, QWidget* parent = nullptr);
	
	/**
	 * @brief 析构函数
	 */
	~CreateGeoZoomWgt();

	/**
	 * @brief 设置位置
	 * @param pt 位置坐标
	 */
	void SetPosition(NctiPosition pt);
	
	/**
	 * @brief 获取实例
	 * @return 实例指针
	 */
	static CreateGeoZoomWgt* instance();
	
	/**
	 * @brief 设置实例
	 * @param pDlg 窗口实例指针
	 */
	static void SetInstance(CreateGeoZoomWgt* pDlg);
	
	/**
	 * @brief 获取位置回调函数
	 * @param pt 位置坐标
	 */
	static void GetPositionFun(NctiPosition pt);

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
	void onOk();
	
	/**
	 * @brief 选择对象槽函数
	 */
	void onSelObject();
	
	/**
	 * @brief 取消按钮槽函数
	 */
	void onCanle();
	
	/**
	 * @brief 预览按钮槽函数
	 */
	void onPreview();

public:
	QLabel* bodyLabel;                    ///< 体标签
	QLabel* selBodyLabel;                 ///< 选择体标签
	QLabel* pointLabel;                   ///< 点标签
	QLabel* proportionalScalingLabel;     ///< 比例缩放标签
	QLabel* proportionLabel;              ///< 比例标签
	QPushButton* selBodyBtn;              ///< 选择体按钮
	QLineEdit* x_pointLineEdit;           ///< X点编辑框
	QLineEdit* y_pointLineEdit;           ///< Y点编辑框
	QLineEdit* z_pointLineEdit;           ///< Z点编辑框
	QLineEdit* proportionLineEdit;        ///< 比例编辑框
	QPushButton* previewBtn;              ///< 预览按钮
	QPushButton* cancelBtn;               ///< 取消按钮
	QPushButton* confrimBtn;              ///< 确认按钮

private:
	NctiDocument* m_Document;                      ///< 文档指针
	std::vector<NctiDisplayObject*> m_SelObjVec;   ///< 选择的对象列表
	double px;                                     ///< X坐标
	double py;                                     ///< Y坐标
	double pz;                                     ///< Z坐标
	double scaleProportion;                        ///< 缩放比例
	static CreateGeoZoomWgt* m_Instance;           ///< 单例实例指针
};
}
#endif // !CREATEGEOZOOMWGT_H