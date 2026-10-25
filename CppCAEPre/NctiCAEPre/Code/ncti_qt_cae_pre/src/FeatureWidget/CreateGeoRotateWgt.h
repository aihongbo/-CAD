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
#ifndef CREATEGEOROTATEWGT_H
#define CREATEGEOROTATEWGT_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QVector3D>

#include "NctiBaseDialog.h"
#include "ncti_base.h"

namespace NCTI
{
class NctiDocument;
class NctiDisplayObject;
class NctiWindowPlatform;
class NctiPosition;
class NctiVector;

/**
 * @brief 创建几何旋转窗口类
 * @details 用于创建和设置几何旋转参数的对话框窗口
 */
class CreateGeoRotateWgt : public NctiBaseDialog
{
	Q_OBJECT

public:
	/**
	 * @brief 构造函数
	 * @param i_pDocument 文档指针
	 * @param parent 父窗口指针
	 */
	explicit CreateGeoRotateWgt(NctiDocument* i_pDocument, QWidget* parent = nullptr);
	
	/**
	 * @brief 析构函数
	 */
	~CreateGeoRotateWgt();

	/**
	 * @brief 设置位置
	 * @param pt 位置坐标
	 */
	void SetPosition(NctiPosition pt);
	
	/**
	 * @brief 设置向量
	 * @param pVector 向量参数
	 */
	void SetVector(NctiVector pVector);
	
	/**
	 * @brief 获取实例
	 * @return 实例指针
	 */
	static CreateGeoRotateWgt* instance();
	
	/**
	 * @brief 设置实例
	 * @param pDlg 窗口实例指针
	 */
	static void SetInstance(CreateGeoRotateWgt* pDlg);
	
	/**
	 * @brief 获取位置回调函数
	 * @param pt 位置坐标
	 */
	static void GetPositionFun(NctiPosition pt);
	
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
     * @brief 确认用户输入并执行旋转操作
     * 
     * 当用户点击“确定”按钮时，该槽函数负责获取输入的参数并执行几何旋转操作。
     */
    void onOk();

    /**
     * @brief 处理对象选择操作
     *
     * 当用户点击“选择体”按钮时，该槽函数负责弹出对象选择对话框并更新选择的对象。
     */
    void onSelObject();

    /**
     * @brief 取消当前操作并关闭窗口
     *
     * 当用户点击“取消”按钮时，该槽函数负责关闭当前窗口并放弃所有未保存的更改。
     */
    void onCanle();

    /**
     * @brief 预览当前设置的旋转效果
     *
     * 当用户点击“预览”按钮时，该槽函数负责根据当前设置的参数预览旋转效果。
     */
    void onPreview();

public:
    QLabel* selectLabel;              ///< 显示“选择”文本的标签
    QLabel* selectBodyLabel;          ///< 显示“选择体”文本的标签
    QLabel* pointLabel;               ///< 显示“点”文本的标签
    QLabel* vectorLabel;              ///< 显示“向量”文本的标签
    QLabel* angleLabel;               ///< 显示“角度”文本的标签
    QPushButton* selectBodyBtn;       ///< 用于选择几何体的按钮
    QPushButton* previewBtn;          ///< 用于预览旋转效果的按钮
    QPushButton* cancelBtn;           ///< 用于取消操作并关闭窗口的按钮
    QPushButton* confrimBtn;          ///< 用于确认并应用旋转操作的按钮
    QLineEdit* x_pLineEdit;           ///< 用于输入点坐标的X值的编辑框
    QLineEdit* y_pLineEdit;           ///< 用于输入点坐标的Y值的编辑框
    QLineEdit* z_pLineEdit;           ///< 用于输入点坐标的Z值的编辑框
    QLineEdit* x_vecLineEdit;         ///< 用于输入向量的X分量的编辑框
    QLineEdit* y_vecLineEdit;         ///< 用于输入向量的Y分量的编辑框
    QLineEdit* z_vecLineEdit;         ///< 用于输入向量的Z分量的编辑框
    QLineEdit* angleLineEdit;         ///< 用于输入旋转角度的编辑框
	
private:
    NctiDocument* m_Document;                      ///< 指向当前文档的指针，用于操作文档数据
    std::vector<NctiDisplayObject*> m_SelObjVec;   ///< 存储用户选择的显示对象的列表
    double px;                                     ///< 存储点的X坐标值
    double py;                                     ///< 存储点的Y坐标值
    double pz;                                     ///< 存储点的Z坐标值
    QVector3D m_Vector;                            ///< 存储旋转轴向量
    double m_Angle;                                ///< 存储旋转角度值
    static CreateGeoRotateWgt* m_Instance;         ///< 指向当前类单例实例的指针
};
}

#endif // !CREATEGEOROTATEWGT_H