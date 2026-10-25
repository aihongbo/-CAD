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
#ifndef CREATELINEARARRAYWGT_H
#define CREATELINEARARRAYWGT_H

#include "NctiBaseDialog.h"
#include "ncti_base.h"

#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVector3D>

namespace NCTI
{
class NctiDocument;
class NctiDisplayObject;
class NctiVector;

/**
 * @brief 创建线性阵列窗口类
 * @details 用于创建和设置线性阵列参数的对话框窗口
 */
class CreateLinearArrayWgt : public NctiBaseDialog
{
	Q_OBJECT
public:
	/**
	 * @brief 构造函数
	 * @param i_pDocument 文档指针
	 * @param parent 父窗口指针
	 */
	explicit CreateLinearArrayWgt(NctiDocument* i_pDocument, QWidget* parent = nullptr);

    ~CreateLinearArrayWgt();

	/**
	 * @brief 设置向量
	 * @param pVector 向量参数
	 */
	void SetVector(NctiVector pVector);
	
	/**
	 * @brief 获取实例
	 * @return 实例指针
	 */
	static CreateLinearArrayWgt* instance();
	
	/**
	 * @brief 设置实例
	 * @param pDlg 窗口实例指针
	 */
	static void SetInstance(CreateLinearArrayWgt* pDlg);
	
	/**
	 * @brief 获取向量回调函数
	 * @param pVector 向量参数
	 */
	static void GetVectorFun(NctiVector pVector);

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
	QLabel* selectLabel;           ///< 选择标签
	QLabel* selectBodyLabel;       ///< 选择体标签
	QLabel* directionLabel;        ///< 方向标签
	QLabel* offsetRangeLabel;      ///< 偏移范围标签
	QLabel* cropRangeLabel;        ///< 裁剪范围标签
	QLabel* newQuantityLabel;      ///< 新数量标签
	QLineEdit* X_directionEdit;    ///< X方向编辑框
	QLineEdit* Y_directionEdit;    ///< Y方向编辑框
	QLineEdit* Z_directionEdit;    ///< Z方向编辑框
	QLineEdit* offsetRangeEdit;    ///< 偏移范围编辑框
	QLineEdit* cropRangeEdit;      ///< 裁剪范围编辑框
	QLineEdit* newQuantityEdit;    ///< 新数量编辑框
	QPushButton* selBodyBtn;       ///< 选择体按钮
	QPushButton* previewBtn;       ///< 预览按钮
	QPushButton* cancelBtn;        ///< 取消按钮
	QPushButton* confrimBtn;       ///< 确认按钮

private:
	NctiDocument* m_Document;                      ///< 文档指针
	std::vector<NctiDisplayObject*> m_SelObjVec;   ///< 选择的对象列表
	QVector3D m_Vector;                            ///< 向量
	static CreateLinearArrayWgt* m_Instance;       ///< 单例实例指针

	double offsetRange;    ///< 偏移范围
	double cropRange;      ///< 裁剪范围
	int newQuantity;       ///< 新数量
};


}
#endif // !CREATELINEARARRAYWGT_H