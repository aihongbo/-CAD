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

#ifndef NctiRegComFillLoop_H
#define NctiRegComFillLoop_H

#include "ncti_base.h"
#include "NctiBaseSelectObjectDlg.h"
#include "ui_NctiFillLoop.h"
#include "dcl_ncti_qt_pubfun.h"
#include <string>

namespace NCTI
{
	class NctiDisplayObject;
	class NctiDocument;
	
	/**
	 * @brief 填充内环面对话框类
	 * @details 用于填充内环面操作的对话框
	 */
	class DECL_NCTI_QT_PUBFUN NctiFillLoopDlg : public NctiBaseSelectObjectDlg
	{
		Q_OBJECT
	public:
		/**
		 * @brief 构造函数
		 * @param i_pDocument 文档指针
		 * @param i_parent 父窗口指针
		 */
		NctiFillLoopDlg(NctiDocument* i_pDocument, QWidget* i_parent);
		
		/**
		 * @brief 析构函数
		 */
		~NctiFillLoopDlg();

	private:
		Ui::NctiFillLoop* m_ui;                  ///< UI界面指针
		
	private Q_SLOTS:
		/**
		 * @brief 确定按钮槽函数
		 */
		void onOK();

		/**
		 * @brief 获取选择槽函数
		 */
		void GetSelection();
		
	private:
		std::vector<NctiDisplayObject*> m_displayobj;  ///< 显示对象列表
		std::vector<NCTI_MODEL_TAG> m_cells;           ///< 单元标签列表
	};
}
#endif