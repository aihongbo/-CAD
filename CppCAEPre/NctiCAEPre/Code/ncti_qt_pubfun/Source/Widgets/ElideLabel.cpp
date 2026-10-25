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

#include "ElideLabel.h"

namespace NCTI {

ElideLabel::ElideLabel(QWidget* parent)
    : QLabel(parent)
    , m_bElide(true)
{
}
ElideLabel::~ElideLabel()
{
}

void ElideLabel::setElide(bool enable)
{
    m_bElide = enable;
    if (m_bElide) {
        fixtext();
        repaint();
    }
}
void ElideLabel::skipElide(const QString prefix)
{
    m_skipPrefix = prefix;
}

QString ElideLabel::text() const
{
    return m_text;
}
void ElideLabel::setText(const QString& text)
{
    m_text = text;
    if (m_bElide) {
        fixtext();
        repaint();
    }
    else {
        QLabel::setText(text);
    }
}

void ElideLabel::fixtext()
{
    auto content         = m_text.right(m_text.length() - m_skipPrefix.length());
    auto fm              = fontMetrics();
    qsizetype maskLength = 3;
    auto contentWidth    = contentsRect().width();

    m_textFixed = m_text;
    if ((!m_skipPrefix.isEmpty() && !m_text.startsWith(m_skipPrefix)) || content.length() <= maskLength + 8
        || fm.horizontalAdvance(m_text) < contentWidth) {
        return;
    }

    while (content.length() > maskLength + 8) {
        auto midIndex      = content.length() / 2;
        auto& contentFixed = content;
        contentFixed.replace(midIndex - maskLength / 2, maskLength, "...");
        auto textWidth = fm.horizontalAdvance(m_skipPrefix + contentFixed);
        if (textWidth < contentWidth) {
            m_textFixed = m_skipPrefix + contentFixed;
            break;
        }
        ++maskLength;
    }
}
void ElideLabel::resizeEvent(QResizeEvent* event)
{
    if (m_bElide) {
        fixtext();
    }
    QLabel::resizeEvent(event);
}
void ElideLabel::paintEvent(QPaintEvent* event)
{
    QLabel::paintEvent(event);
    if (m_bElide) {
        QPainter painter(this);
        painter.setFont(font());
        painter.drawText(contentsRect(), Qt::AlignVCenter | Qt::AlignLeft, m_textFixed);
    }
}
}; // namespace NCTI
