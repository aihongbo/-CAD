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

#include "PrefixLineEdit.h"
#include <QFontMetrics>
#include <QPainter>
#include <QPalette>

namespace NCTI {

	PrefixLineEdit::PrefixLineEdit(QWidget* parent)
		: QLineEdit(parent)
	{}
	PrefixLineEdit::~PrefixLineEdit()
	{}

	void PrefixLineEdit::setPrefix(const QString& prefix, const QColor& color)
	{
		m_prefix = prefix;
		m_prefixColor = color;
		update();
	}

	void PrefixLineEdit::paintEvent(QPaintEvent* event)
	{
		QLineEdit::paintEvent(event);
		QPainter painter(this);
		int prefixWidth = QFontMetrics(font()).horizontalAdvance(m_prefix);
		QRect rect(contentsRect().x(), contentsRect().y(), prefixWidth, contentsRect().height());
		QPalette pal = palette();
		painter.setPen(m_prefixColor.isValid() ? m_prefixColor : pal.text().color());
		painter.drawText(rect, Qt::AlignCenter, m_prefix);
	}
}
