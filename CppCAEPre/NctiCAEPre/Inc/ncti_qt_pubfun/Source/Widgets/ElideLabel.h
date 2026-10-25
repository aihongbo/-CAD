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

#include <QLabel>
#include <QPainter>

namespace NCTI
{
	/**
	 * @brief 省略标签类
	 * @details 支持文本省略显示的标签控件，当文本过长时自动显示省略号
	 */
	class ElideLabel : public QLabel
	{
	public:
		/**
		 * @brief 构造函数
		 * @param parent 父窗口指针
		 */
		explicit ElideLabel(QWidget* parent = nullptr);
		
		/**
		 * @brief 析构函数
		 */
		virtual ~ElideLabel();

		/**
		 * @brief 设置省略
		 * @param enable 是否启用省略
		 */
		void setElide(bool enable);
		
		/**
		 * @brief 跳过省略
		 * @param prefix 前缀文本
		 */
		void skipElide(const QString prefix);

		/**
		 * @brief 获取文本
		 * @return 文本内容
		 */
		QString text() const;
		
		/**
		 * @brief 设置文本
		 * @param text 文本内容
		 */
		void setText(const QString& text);

	private:
		/**
		 * @brief 修复文本
		 */
		void fixtext();
		
		/**
		 * @brief 调整大小事件处理
		 * @param event 调整大小事件指针
		 */
		void resizeEvent(QResizeEvent* event) override;
		
		/**
		 * @brief 绘制事件处理
		 * @param event 绘制事件指针
		 */
		void paintEvent(QPaintEvent* event) override;

	private:
		bool m_bElide;              ///< 是否省略
		QString m_skipPrefix;       ///< 跳过前缀
		QString m_text;             ///< 文本内容
		QString m_textFixed;        ///< 固定宽度文本
	};
};