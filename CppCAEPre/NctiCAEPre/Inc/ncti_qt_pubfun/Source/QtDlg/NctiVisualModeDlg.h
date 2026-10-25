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

#ifndef NctiVisualModeDlg_H
#define NctiVisualModeDlg_H
#include "ncti_base.h"
#include "ui_NctiVisualMode.h"
#include "dcl_ncti_qt_pubfun.h"

namespace NCTI
{
	class NctiDocument;
	
	/**
	 * @brief 显示模式对话框类
	 * @details 用于设置显示模式的对话框
	 */
	class DECL_NCTI_QT_PUBFUN NctiVisualModeDlg : public QWidget
	{
		Q_OBJECT
	public:
		/**
		 * @brief 构造函数
		 * @param i_pDocument 文档指针
		 * @param i_parent 父窗口指针
		 */
		NctiVisualModeDlg(NctiDocument* i_pDocument, QWidget* i_parent);
		
		/**
		 * @brief 析构函数
		 */
		virtual ~NctiVisualModeDlg();
		
	public Q_SLOTS:
		/**
		 * @brief 显示槽函数
		 */
		void show();
		
	private:
		Ui::NctiVisualModeDlg* m_ui;  ///< UI界面指针
		NctiDocument* m_Document;     ///< 文档指针
		
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
		 * @brief 更新控件槽函数
		 */
		void onUpdateCtl();

	private:
		bool m_visual_all;     ///< 全部显示状态
		bool m_visual_face;    ///< 面显示状态
		bool m_visual_line;    ///< 线显示状态
		bool m_visual_marker;  ///< 标记显示状态
		
		/**
		 * @brief 获取当前显示模式
		 */
		void GetCurrentVisualMode();
		
		/**
		 * @brief 更新控件
		 */
		void UpdateCtl();
		
		/**
		 * @brief 是否全部显示
		 * @return 全部显示返回true，否则返回false
		 */
		bool visual_all();
	};
}
#endif