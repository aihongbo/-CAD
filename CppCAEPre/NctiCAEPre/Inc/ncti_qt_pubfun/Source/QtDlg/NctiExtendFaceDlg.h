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

#ifndef NctiExtendFace_H
#define NctiExtendFace_H

#include "ncti_base.h"
#include "NctiBaseSelectObjectDlg.h"
#include "dcl_ncti_qt_pubfun.h"
#include <QWidget>
#include "ui_NctiExtendFace.h"

namespace NCTI {

	class NctiVector;
	
	/**
	 * @brief 拉伸面对话框类
	 * @details 用于拉伸面操作的对话框
	 */
	class DECL_NCTI_QT_PUBFUN NctiExtendFaceDlg : public NctiBaseSelectObjectDlg
	{
		Q_OBJECT
	public:
		/**
		 * @brief 构造函数
		 * @param i_pDocument 文档指针
		 * @param i_parent 父窗口指针
		 */
		NctiExtendFaceDlg(NctiDocument* i_pDocument, QWidget* i_parent);
		
		/**
		 * @brief 析构函数
		 */
		~NctiExtendFaceDlg();

	private Q_SLOTS:
		/**
		 * @brief 确定按钮槽函数
		 */
		void onOk();
		
		/**
		 * @brief 获取面法向量槽函数
		 */
		void onGetFaceNormal();

	private:
		Ui::NctiExtendFace* m_ui;      ///< UI界面指针
		NctiVector* m_NormalVec;        ///< 法向量指针
	};
}

#endif // !NctiExtendFace_H