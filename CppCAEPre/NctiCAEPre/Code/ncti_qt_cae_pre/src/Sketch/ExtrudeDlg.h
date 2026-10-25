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

#ifndef ExtrudeDlg_H
#define ExtrudeDlg_H
#include <QPushButton>
#include <QCheckBox>
#include <QLineEdit>
#include "ncti_base.h"
#include "NctiBaseDialog.h"

namespace NCTI
{
	class NctiBaseModel;
	
	/**
	 * @brief 拉伸对话框类
	 * @details 用于处理几何拉伸操作的参数设置和预览的对话框
	 */
    class ExtrudeDlg : public NctiBaseDialog
	{
		Q_OBJECT
	public:
		/**
		 * @brief 构造函数
		 * @param pBaseModel 基础模型指针
		 * @param parent 父窗口指针
		 */
		explicit ExtrudeDlg(NctiBaseModel* pBaseModel, QWidget* parent = nullptr);
		
		/**
		 * @brief 析构函数
		 */
		~ExtrudeDlg();
		
		/**
		 * @brief 初始化界面
		 */
		void init();
		
		/**
		 * @brief 初始化数据
		 */
		void initData();
		
		/**
		 * @brief 刷新界面状态
		 */
		void Refresh();

		/**
		 * @brief 获取实例
		 * @return ExtrudeDlg实例指针
		 */
		static ExtrudeDlg* instance();
		
		/**
		 * @brief 设置实例
		 * @param pExtrudeDlg ExtrudeDlg实例指针
		 */
		static void SetInstance(ExtrudeDlg* pExtrudeDlg);
		
		/**
		 * @brief 显示对话框
		 * @param pBaseModel 基础模型指针
		 * @param dHeight 拉伸高度
		 * @param bReverse 是否反转
		 * @param bRemove 是否移除材料
		 * @param bBothSide 是否两边拉伸
		 * @param bUseAngle 是否使用角度
		 * @param dAngle 拔模角度
		 * @param parent 父窗口指针
		 */
		static void ShowDialog(NctiBaseModel* pBaseModel, double dHeight, int bReverse, int bRemove, int bBothSide, int bUseAngle, double dAngle, QWidget* parent = nullptr);
		
		/**
		 * @brief 删除对话框
		 */
		static void DeleteDialog();
		
		/**
		 * @brief 获取拉伸数据
		 * @param[out] dHeight 拉伸高度
		 * @param[out] bReverse 是否反转
		 * @param[out] bRemove 是否移除材料
		 * @param[out] bBothSide 是否两边拉伸
		 * @param[out] bUseAngle 是否使用角度
		 * @param[out] dAngle 拔模角度
		 */
		static void GetExtrudeData(double& dHeight, int& bReverse, int& bRemove, int& bBothSide, int& bUseAngle, double& dAngle);
		
		/**
		 * @brief 设置拉伸数据
		 * @param dHeight 拉伸高度
		 * @param bReverse 是否反转
		 * @param bRemove 是否移除材料
		 * @param bBothSide 是否两边拉伸
		 * @param bUseAngle 是否使用角度
		 * @param dAngle 拔模角度
		 */
		static void SetExtrudeData(double dHeight, int bReverse, int bRemove, int bBothSide, int bUseAngle, double dAngle);

	private Q_SLOTS:
		/**
		 * @brief 点击确定按钮槽函数
		 * @param boo 按钮状态
		 */
		void ClickOk(bool boo);
		
		/**
		 * @brief 点击取消按钮槽函数
		 * @param boo 按钮状态
		 */
		void ClickCancel(bool boo);
		
		/**
		 * @brief 点击预览按钮槽函数
		 * @param boo 按钮状态
		 */
		void ClickPreview(bool boo);
		
		/**
		 * @brief 点击角度复选框槽函数
		 * @param boo 复选框状态
		 */
		void ClickAngle(bool boo);

	private:
		static ExtrudeDlg* mInstance;      ///< 单例实例指针
		NctiBaseModel* m_pBaseModel;        ///< 基础模型指针
		QPushButton* m_BtnOK;               ///< 确定按钮
		QPushButton* m_BtnCancel;           ///< 取消按钮
		QPushButton* m_BtnPreview;          ///< 预览按钮
		QLineEdit* m_Height;                ///< 高度输入框
		QCheckBox* m_RemoveMaterial;        ///< 移除材料复选框
		QCheckBox* m_Reverse;               ///< 反转复选框
		QCheckBox* m_BothSide;              ///< 两边复选框
		QCheckBox* m_Angle;                 ///< 角度复选框
		QLineEdit* m_UseAngle;              ///< 角度输入框

		double m_dHeight;                   ///< 拉伸高度
		int m_bReverse;                     ///< 是否反转标志
		int m_bRemove;                      ///< 移除材料标志
		int m_bBothSide;                    ///< 两边拉伸标志
		int m_bUseAngle;                    ///< 使用角度标志
		double m_dAngle;                    ///< 拔模角度

	public:
		/**
		 * @brief 预览结果
		 */
		void PreResult();
		
	public:
		/**
		 * @brief 获取长度回调函数
		 * @param i_dbl 长度值
		 */
		static void GetLengthFun(Ncti_Double i_dbl);
	};
}
#endif