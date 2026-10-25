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

#include "dcl_ncti_qt_pubfun.h"
#include <QFrame>
#include <QLabel>
#include <QPushButton>

namespace NCTI
{
	class ElideLabel;
	
	/**
	 * @brief 停靠标题栏类
	 * @details 用于创建可停靠窗口的标题栏，包含标题显示、关闭按钮和帮助按钮
	 */
	class DECL_NCTI_QT_PUBFUN DockTitleBar : public QFrame
	{
		Q_OBJECT
	public:
		/**
		 * @brief 构造函数
		 * @param parent 父窗口指针
		 * @param bShowCloseBtn 是否显示关闭按钮
		 * @param bElideTitle 是否省略标题
		 */
		explicit DockTitleBar(QWidget *parent = nullptr, bool bShowCloseBtn = true, bool bElideTitle = false);
		
		/**
		 * @brief 析构函数
		 */
		~DockTitleBar();

		/**
		 * @brief 设置标题
		 * @param title 标题文本
		 */
		void setTitle(const QString& title);
		
		/**
		 * @brief 跳过省略标题
		 * @param prefix 前缀文本
		 */
		void skipEliedTitle(const QString& prefix);

	Q_SIGNALS:
		/**
		 * @brief 信号关闭
		 */
		void signalClose();
		
		/**
		 * @brief 信号问题
		 */
		void signalQuestion();

	private:
		/**
		 * @brief 设置界面
		 */
		void setup();

	private:
		ElideLabel* m_titleLabel{ nullptr };        ///< 标题标签指针
		QPushButton* m_closeButton{ nullptr };      ///< 关闭按钮指针
		QPushButton* m_questionButton{ nullptr };   ///< 问题按钮指针
        bool m_bShowCloseBtn{ true };              ///< 是否显示关闭按钮
		bool m_bElideTitle{ false };               ///< 是否省略标题
	};
};