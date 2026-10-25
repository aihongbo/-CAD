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

#include <QComboBox>
#include <QPushButton>
#include <QCheckBox>
#include <QLineEdit>

#include "NctiBaseDialog.h"

namespace NCTI
{
	class NctiBaseModel;
	
	/**
	 * @brief 旋转对话框类
	 * @details 用于处理几何旋转操作的参数设置和预览的对话框
	 */
    class RevolveDlg : public NctiBaseDialog
    {
        Q_OBJECT
    public:
		/**
		 * @brief 构造函数
		 * @param pBaseModel 基础模型指针
		 * @param parent 父窗口指针
		 */
        explicit RevolveDlg(NctiBaseModel* pBaseModel, QWidget* parent = nullptr);
        
        /**
         * @brief 析构函数
         */
        ~RevolveDlg();
		
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
		 * @return RevolveDlg实例指针
		 */
		static RevolveDlg* instance();
		
		/**
		 * @brief 设置实例
		 * @param pRevolveDlg RevolveDlg实例指针
		 */
		static void SetInstance(RevolveDlg* pRevolveDlg);
		
		/**
		 * @brief 显示对话框
		 * @param pBaseModel 基础模型指针
		 * @param bUseAngle 是否使用角度
		 * @param dStartAngle 起始角度
		 * @param dEndAngle 结束角度
		 * @param bRemove 是否移除材料
		 * @param bReverse 是否反向
		 * @param parent 父窗口指针
		 */
		static void ShowDialog(NctiBaseModel* pBaseModel, bool bUseAngle, double dStartAngle, double dEndAngle, int bRemove, int bReverse, QWidget* parent = nullptr);
		
		/**
		 * @brief 删除对话框
		 */
		static void DeleteDialog();
		
		/**
		 * @brief 设置旋转数据
		 * @param bUseAngle 是否使用角度
		 * @param dStartAngle 起始角度
		 * @param dEndAngle 结束角度
		 * @param bRemove 是否移除材料
		 * @param bReverse 是否反向
		 */
		static void SetRevolveData(bool bUseAngle, double dStartAngle, double dEndAngle, int bRemove, int bReverse);
		
		/**
		 * @brief 获取旋转数据
		 * @param[out] iUseAngle 是否使用角度
		 * @param[out] dStartAngle 起始角度
		 * @param[out] dEndAngle 结束角度
		 * @param[out] iRemove 是否移除材料
		 * @param[out] iReverse 是否反向
		 */
		static void GetRevolveData(int& iUseAngle, double& dStartAngle, double& dEndAngle, int& iRemove, int& iReverse);
		
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
		
	public:
		/**
		 * @brief 预览结果
		 */
		void PreResult();
		
	private:
		static RevolveDlg* mInstance;      ///< 单例实例指针
		NctiBaseModel* m_pBaseModel;        ///< 基础模型指针
		QPushButton* m_BtnOK;               ///< 确定按钮
		QPushButton* m_BtnCancel;           ///< 取消按钮
		QPushButton* m_BtnPreview;          ///< 预览按钮

		QCheckBox* m_Angle;                 ///< 角度复选框
		QLineEdit* m_AngleS;                ///< 起始角度输入框
		QLineEdit* m_AngleE;                ///< 结束角度输入框
		QCheckBox* m_Remove;                ///< 移除材料复选框
		QCheckBox* m_Reverse;               ///< 反向复选框

		bool m_bUseAngle;                   ///< 使用角度标志
		double m_dStartAngle;               ///< 起始角度
		double m_dEndAngle;                 ///< 结束角度
		int m_bRemove;                      ///< 移除材料标志
		int m_bReverse;                     ///< 反向标志
    };
}