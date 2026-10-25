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

#ifndef NctiQtCreateBoxDlg_H
#define NctiQtCreateBoxDlg_H
#include "dcl_ncti_qt_pubfun.h"
#include <QWidget>
#include "ui_CreateBox.h"
#include "ncti_base.h"

namespace NCTI
{
	class NctiDocument;
	
	/**
	 * @brief 创建长方体对话框类
	 * @details 用于创建长方体几何体的对话框
	 */
	class DECL_NCTI_QT_PUBFUN NctiQtCreateBoxDlg : public QWidget
	{
		Q_OBJECT
	public:
		/**
		 * @brief 构造函数
		 * @param i_pDocument 文档指针
		 * @param i_parent 父窗口指针
		 */
		NctiQtCreateBoxDlg(NctiDocument* i_pDocument, QWidget* i_parent);
		
		/**
		 * @brief 析构函数
		 */
		~NctiQtCreateBoxDlg();
		
	private:
		Ui::NctiQtCreateBox* m_ui;   ///< UI界面指针
		NctiDocument* m_Document;       ///< 文档指针
		
	private Q_SLOTS:
		/**
		 * @brief 确定按钮槽函数
		 */
		void onOk();
		
		/**
		 * @brief 取消按钮槽函数
		 */
		void onCanle();
	};
}
#endif