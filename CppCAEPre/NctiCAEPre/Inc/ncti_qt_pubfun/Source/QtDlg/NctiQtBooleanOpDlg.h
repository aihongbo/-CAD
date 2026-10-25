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

#ifndef NctiQtBooleanOpDlg_H
#define NctiQtBooleanOpDlg_H
#include "dcl_ncti_qt_pubfun.h"
#include <QWidget>
#include "ui_NctiBooleanOp.h"
#include "ncti_base.h"

namespace NCTI
{
	class NctiDocument;
	class NctiDisplayObject;
	
	/**
	 * @brief 布尔操作对话框类
	 * @details 用于执行布尔操作（并集、差集、交集）的对话框
	 */
	class DECL_NCTI_QT_PUBFUN NctiQtBooleanOpDlg : public QWidget
	{
		Q_OBJECT
	public:
		/**
		 * @brief 构造函数
		 * @param i_pDocument 文档指针
		 * @param i_dlgType 对话框类型
		 * @param i_parent 父窗口指针
		 */
		NctiQtBooleanOpDlg(NctiDocument* i_pDocument, Ncti_Integer i_dlgType, QWidget* i_parent);
		
		/**
		 * @brief 析构函数
		 */
		~NctiQtBooleanOpDlg();
		
	private:
		Ui::BooleanOpDlg* m_ui;            ///< UI界面指针
		NctiDocument* m_Document;            ///< 文档指针
		NctiDisplayObject* m_DisplayObject1;  ///< 显示对象1指针
		NctiDisplayObject* m_DisplayObject2;  ///< 显示对象2指针
		
		/**
		 * @brief 对话框类型枚举
		 * 0:unit 并集
		 * 1:cut 差集
		 * 2:common 交集
		 */
		Ncti_Integer m_DlgType;              ///< 对话框类型
		
	private Q_SLOTS:
		/**
		 * @brief 确定按钮槽函数
		 */
		void onOk();
		
		/**
		 * @brief 取消按钮槽函数
		 */
		void onCanle();
		
		/**
		 * @brief 选择对象1槽函数
		 */
		void onSelect1();
		
		/**
		 * @brief 选择对象2槽函数
		 */
		void onSelect2();
	};
}
#endif