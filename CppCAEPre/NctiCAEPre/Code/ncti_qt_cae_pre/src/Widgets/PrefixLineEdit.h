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

#include <QLineEdit>

namespace NCTI {
	/**
	 * @brief 前缀行编辑控件类
	 * @details 支持显示前缀文本的行编辑控件
	 */
	class PrefixLineEdit : public QLineEdit
	{
	public:
		/**
		 * @brief 构造函数
		 * @param parent 父控件指针
		 */
		explicit PrefixLineEdit(QWidget *parent = nullptr);
		
		/**
		 * @brief 析构函数
		 */
		~PrefixLineEdit();

		/**
		 * @brief 设置前缀
		 * @param prefix 前缀文本
		 * @param color 前缀颜色
		 */
		void setPrefix(const QString &prefix, const QColor &color = QColor());

	protected:
		/**
		 * @brief 绘制事件处理
		 * @param event 绘制事件指针
		 */
		void paintEvent(QPaintEvent* event) override;

	private:
		QString m_prefix;      ///< 前缀文本
		QColor m_prefixColor;  ///< 前缀颜色
	};
};