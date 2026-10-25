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
#ifndef CREATEGEOPANWGT_H
#define CREATEGEOPANWGT_H

#include <QWidget>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QVector3D>

#include "NctiBaseDialog.h"
#include "ncti_base.h"

namespace NCTI {
class NctiDocument;
class NctiDisplayObject;
class NctiVector;

/**
 * @brief 创建几何平移窗口类
 * @details 用于创建和设置几何平移参数的对话框窗口
 */
class CreateGeoPanWgt : public NctiBaseDialog
{
	Q_OBJECT

public:
	/**
	 * @brief 构造函数
	 * @param i_pDocument 文档指针
	 * @param parent 父窗口指针
	 */
	explicit CreateGeoPanWgt(NctiDocument* i_pDocument, QWidget* parent = nullptr);
	
	/**
	 * @brief 析构函数
	 */
	~CreateGeoPanWgt();

	/**
	 * @brief 设置向量
	 * @param pVector 向量参数
	 */
	void SetVector(NctiVector pVector);
	
	/**
	 * @brief 获取实例
	 * @return 实例指针
	 */
	static CreateGeoPanWgt* instance();
	
	/**
	 * @brief 设置实例
	 * @param pDlg 窗口实例指针
	 */
	static void SetInstance(CreateGeoPanWgt* pDlg);
	
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
	QLabel* vectorLab;              ///< 向量标签
	QLineEdit* z_VecLineEdit;       ///< Z向量编辑框
	QLineEdit* y_VecLineEdit;       ///< Y向量编辑框
	QLineEdit* x_VecLineEdit;       ///< X向量编辑框
	QLabel* bodyLabel;              ///< 体标签
	QLabel* selBodyLabel;           ///< 选择体标签
	QPushButton* selBtn;            ///< 选择按钮
	QLabel* distanceLable;          ///< 距离标签
	QLineEdit* distanceLineEdit;    ///< 距离编辑框
	QPushButton* previewBtn;        ///< 预览按钮
	QPushButton* cancelBtn;         ///< 取消按钮
	QPushButton* confrimBtn;        ///< 确认按钮

private:
	NctiDocument* m_Document;                      ///< 文档指针
	std::vector<NctiDisplayObject*> m_SelObjVec;   ///< 选择的对象列表
	QVector3D m_Vector;                            ///< 向量
	static CreateGeoPanWgt* m_Instance;            ///< 单例实例指针
};
}
#endif