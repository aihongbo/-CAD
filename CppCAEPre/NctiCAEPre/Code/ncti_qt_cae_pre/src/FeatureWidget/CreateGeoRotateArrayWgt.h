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
#ifndef CREATEGEOROTATEARRAYWGT
#define CREATEGEOROTATEARRAYWGT

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
class NctiPosition;
class NctiVector;

/**
 * @brief 创建几何旋转阵列窗口类
 * @details 用于创建和设置几何旋转阵列参数的对话框窗口
 */
class CreateGeoRotateArrayWgt : public NctiBaseDialog
{
	Q_OBJECT

public:
	/**
	 * @brief 构造函数
	 * @param i_pDocument 文档指针
	 * @param parent 父窗口指针
	 */
	explicit CreateGeoRotateArrayWgt(NctiDocument* i_pDocument, QWidget* parent = nullptr);

    ~CreateGeoRotateArrayWgt();

	/**
	 * @brief 设置位置
	 * @param Point 位置点
	 */
	void SetPosition(NctiPosition Point);
	
	/**
	 * @brief 设置向量
	 * @param pVector 向量参数
	 */
	void SetVector(NctiVector pVector);
	
	/**
	 * @brief 获取实例
	 * @return 实例指针
	 */
	static CreateGeoRotateArrayWgt* instance();
	
	/**
	 * @brief 设置实例
	 * @param pDlg 窗口实例指针
	 */
	static void SetInstance(CreateGeoRotateArrayWgt* pDlg);
	
	/**
	 * @brief 获取位置回调函数
	 * @param Point 位置点
	 */
	static void GetPositionFun(NctiPosition Point);
	
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
	QLabel* selectLabel;              ///< 选择标签
	QLabel* selectBodyLabel;          ///< 选择体标签
	QLabel* pointLabel;               ///< 点标签
	QLabel* vecLabel;                 ///< 向量标签
	QLabel* newQuantityLabel;         ///< 新增数量标签
	QLabel* rotateAngleLabel;         ///< 旋转角度标签
	QLineEdit* xLineEdit;             ///< X坐标输入框
	QLineEdit* yLineEdit;             ///< Y坐标输入框
	QLineEdit* zLineEdit;             ///< Z坐标输入框
	QLineEdit* xVecLineEdit;          ///< X向量输入框
	QLineEdit* yVecLineEdit;          ///< Y向量输入框
	QLineEdit* zVecLineEdit;          ///< Z向量输入框
	QLineEdit* newQuantityLineEdit;   ///< 新建对象数量输入框
	QLineEdit* rotateAngleLineEdit;   ///< 旋转角度输入框
	QPushButton* selBodyBtn;          ///< 选择体按钮
	QPushButton* previewBtn;          ///< 预览按钮
	QPushButton* cancelBtn;           ///< 取消按钮
	QPushButton* confrimBtn;          ///< 确认按钮

private:
	NctiDocument* m_Document;                      ///< 当前文档指针
	std::vector<NctiDisplayObject*> m_SelObjVec;   ///< 已选择的显示对象列表
	static CreateGeoRotateArrayWgt* m_Instance;     ///< 单例实例指针

	double px;           ///< 点的X坐标
	double py;           ///< 点的Y坐标
	double pz;           ///< 点的Z坐标
	int newQuantity;     ///< 新建对象的数量
	double rotateAngle;  ///< 旋转角度
	QVector3D m_Vector; ///< 旋转方向向量
};
}

#endif // !CREATEGEOROTATEARRAYWGT