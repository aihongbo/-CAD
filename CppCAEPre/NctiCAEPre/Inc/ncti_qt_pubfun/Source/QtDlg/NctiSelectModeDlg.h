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

#ifndef NctiSelectModeDlg_H
#define NctiSelectModeDlg_H
#include "ncti_base.h"
#include "ui_NctiSelectMode.h"
#include "dcl_ncti_qt_pubfun.h"

namespace NCTI
{
	class NctiDocument;
	
	/**
	 * @brief 选择模式对话框类
	 * @details 用于设置选择模式的对话框
	 */
	class DECL_NCTI_QT_PUBFUN NctiSelectModeDlg : public QWidget
	{
		Q_OBJECT
	public:
		/**
		 * @brief 构造函数
		 * @param i_pDocument 文档指针
		 * @param i_parent 父窗口指针
		 */
		NctiSelectModeDlg(NctiDocument* i_pDocument, QWidget* i_parent);
		
		/**
		 * @brief 析构函数
		 */
		virtual ~NctiSelectModeDlg();
		
	public Q_SLOTS:
		/**
		 * @brief 显示槽函数
		 */
		void show();
		
	private:
		Ui::NctiSelectModeDlg* m_ui;  ///< UI界面指针
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
		bool m_sel_body;     ///< 体选择状态
		bool m_sel_face;     ///< 面选择状态
		bool m_sel_line;     ///< 线选择状态
		bool m_sel_marker;   ///< 标记选择状态
		
		/**
		 * @brief 获取当前选择模式
		 */
		void GetCurrentSelMode();
		
		/**
		 * @brief 更新控件
		 */
		void UpdateCtl();
	};
}
#endif