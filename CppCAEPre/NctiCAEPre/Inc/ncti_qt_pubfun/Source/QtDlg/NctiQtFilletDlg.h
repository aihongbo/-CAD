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

#ifndef NctiQtFilletDlg_H
#define NctiQtFilletDlg_H

#include "dcl_ncti_qt_pubfun.h"
#include <QWidget>
#include "ui_NctiFillet.h"
#include "ncti_base.h"

namespace NCTI
{
	class NctiDocument;
	class NctiDisplayObject;
	
	/**
	 * @brief 倒圆角对话框类
	 * @details 用于对模型进行倒圆角操作的对话框
	 */
	class DECL_NCTI_QT_PUBFUN NctiQtFilletDlg : public QWidget
	{
		Q_OBJECT
	public:
		/**
		 * @brief 构造函数
		 * @param i_pDocument 文档指针
		 * @param i_parent 父窗口指针
		 */
		NctiQtFilletDlg(NctiDocument* i_pDocument, QWidget* i_parent);
		
		/**
		 * @brief 析构函数
		 */
		~NctiQtFilletDlg();
		
	private:
		Ui::Fillet* m_ui;                          ///< UI界面指针
		NctiDocument* m_Document;                    ///< 文档指针
		std::vector<NCTI_MODEL_TAG> m_SelectCells;    ///< 选择的单元列表
		std::vector<NctiDisplayObject*> m_SelObjVec;  ///< 选择的对象列表
		
	private Q_SLOTS:
		/**
		 * @brief 确定按钮槽函数
		 */
		void onOk();
		
		/**
		 * @brief 选择边槽函数
		 */
		void onSelEdge();
		
		/**
		 * @brief 取消按钮槽函数
		 */
		void onCanle();
	};
}
#endif