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

#ifndef WorkPlaneDlg_H
#define WorkPlaneDlg_H
#include <QComboBox>

#include "NctiBaseDialog.h"

namespace NCTI
{
	class NctiBaseModel;
	class NctiPosition;
	
	/**
	 * @brief 工作平面对话框类
	 * @details 用于设置和调整工作平面参数的对话框
	 */
    class WorkPlaneDlg : public NctiBaseDialog
	{
		Q_OBJECT
	public:
		/**
		 * @brief 构造函数
		 * @param pBaseModel 基础模型指针
		 * @param parent 父窗口指针
		 */
		explicit WorkPlaneDlg(NctiBaseModel* pBaseModel, QWidget* parent = nullptr);
		
		/**
		 * @brief 析构函数
		 */
		~WorkPlaneDlg();
		
		/**
		 * @brief 初始化界面
		 */
		void init();
		
		/**
		 * @brief 初始化数据
		 */
		void initData();

		/**
		 * @brief 获取实例
		 * @return WorkPlaneDlg实例指针
		 */
		static WorkPlaneDlg* instance();
		
		/**
		 * @brief 设置实例
		 * @param pWorkPlaneDlg WorkPlaneDlg实例指针
		 */
		static void SetInstance(WorkPlaneDlg* pWorkPlaneDlg);
		
		/**
		 * @brief 显示对话框
		 * @param pBaseModel 基础模型指针
		 * @param parent 父窗口指针
		 */
		static void ShowDialog(NctiBaseModel* pBaseModel, QWidget* parent = nullptr);
		
		/**
		 * @brief 删除对话框
		 */
		static void DeleteDialog();
		
		/**
		 * @brief 设置坐标参数
		 * @param dOriginX 原点X坐标
		 * @param dOriginY 原点Y坐标
		 * @param dOriginZ 原点Z坐标
		 * @param dAngleX 旋转X角度
		 * @param dAngleY 旋转Y角度
		 * @param dAngleZ 旋转Z角度
		 */
		static void SetCoordinate(double dOriginX, double dOriginY, double dOriginZ, double dAngleX, double dAngleY, double dAngleZ);
		
		/**
		 * @brief 获取坐标参数
		 * @param[out] dOriginX 原点X坐标
		 * @param[out] dOriginY 原点Y坐标
		 * @param[out] dOriginZ 原点Z坐标
		 * @param[out] dAngleX 旋转X角度
		 * @param[out] dAngleY 旋转Y角度
		 * @param[out] dAngleZ 旋转Z角度
		 */
		static void GetCoordinate(double& dOriginX, double& dOriginY, double& dOriginZ, double& dAngleX, double& dAngleY, double& dAngleZ);

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
		void ClickPre(bool boo);
		
	private:
		static WorkPlaneDlg* mInstance;    ///< 单例实例指针
		NctiBaseModel* m_pBaseModel;        ///< 基础模型指针
		QPushButton* m_BtnOK;               ///< 确定按钮
		QPushButton* m_BtnPre;              ///< 预览按钮
		QPushButton* m_BtnCancel;           ///< 取消按钮
		QLineEdit* m_EditOX;                ///< 原点X坐标输入框
		QLineEdit* m_EditOY;                ///< 原点Y坐标输入框
		QLineEdit* m_EditOZ;                ///< 原点Z坐标输入框
		QLineEdit* m_EditRX;                ///< 旋转X角度输入框
		QLineEdit* m_EditRY;                ///< 旋转Y角度输入框
		QLineEdit* m_EditRZ;                ///< 旋转Z角度输入框
		double m_OriginX;                   ///< 原点X坐标
		double m_OriginY;                   ///< 原点Y坐标
		double m_OriginZ;                   ///< 原点Z坐标

		double m_dAngleX;                   ///< 旋转X角度
		double m_dAngleY;                   ///< 旋转Y角度
		double m_dAngleZ;                   ///< 旋转Z角度
		
	public:
		/**
		 * @brief 预览结果
		 */
		void PreResult();
		
	public:
		/**
		 * @brief 获取位置回调函数
		 * @param i_pt 位置坐标
		 */
		static void GetPositionFun(const NctiPosition& i_pt);
	};
}
#endif