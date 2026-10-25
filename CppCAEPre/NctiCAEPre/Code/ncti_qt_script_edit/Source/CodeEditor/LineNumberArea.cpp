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

// QCodeEditor
#include "LineNumberArea.h"
#include "CodeEditor.h"
#include <QSyntaxStyle>

// Qt
#include <QTextEdit>
#include <QPainter>
#include <QTextBlock>
#include <QScrollBar>
#include <QAbstractTextDocumentLayout>

using namespace NCTI;

#define INDICATOR_WIDTH 3
#define WIDTH_FIX 5

LineNumberArea::LineNumberArea(CodeEditor* parent) :
    QWidget(parent),
    m_syntaxStyle(nullptr),
    m_codeEditParent(parent),
    m_currentBlockNumber(-1)
{

}

QSize LineNumberArea::sizeHint() const
{
    if (m_codeEditParent == nullptr)
    {
        return QWidget::sizeHint();
    }

    // Calculating width
    int digits = 1;
    int max = qMax(1, m_codeEditParent->document()->blockCount());
    while (max >= 10) {
        max /= 10;
        ++digits;
    }

#if QT_VERSION >= 0x050B00
    int space = 13 + WIDTH_FIX + INDICATOR_WIDTH + m_codeEditParent->fontMetrics().horizontalAdvance(QLatin1Char('9')) * digits;
#else
    int space = 13 + WIDTH_FIX + INDICATOR_WIDTH + m_codeEditParent->fontMetrics().width(QLatin1Char('9')) * digits;
#endif

    return { space, 0 };
}

void LineNumberArea::setSyntaxStyle(QSyntaxStyle* style)
{
    m_syntaxStyle = style;
}

QSyntaxStyle* LineNumberArea::syntaxStyle() const
{
    return m_syntaxStyle;
}

void LineNumberArea::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);

    // Clearing rect to update

    auto background = m_syntaxStyle->getFormat("Text").background();
    if (m_syntaxStyle->getFormat("LineNumber").background() != QBrush()) {
        background = m_syntaxStyle->getFormat("LineNumber").background().color();
    }
    painter.fillRect(
        event->rect(),
        background
    );

    auto blockNumber = m_codeEditParent->getFirstVisibleBlock();
    auto block = m_codeEditParent->document()->findBlockByNumber(blockNumber);
    auto top = (int)m_codeEditParent->document()->documentLayout()->blockBoundingRect(block).translated(0, -m_codeEditParent->verticalScrollBar()->value()).top();
    auto bottom = top + (int)m_codeEditParent->document()->documentLayout()->blockBoundingRect(block).height();

    auto currentLine = m_syntaxStyle->getFormat("CurrentLineNumber").foreground().color();
    QColor currentLineIndicator;
    do {
        QTextCharFormat format = m_syntaxStyle->getFormat("CurrentLineNumberIndicator");
        if (format == QTextCharFormat()) {
            break;
        }

        currentLineIndicator = format.background().color();
    } while (0);
    auto otherLines = m_syntaxStyle->getFormat("LineNumber").foreground().color();

    painter.setFont(m_codeEditParent->font());
    auto currentBlockNumber = m_codeEditParent->textCursor().blockNumber();
    if (m_currentBlockNumber!= currentBlockNumber) {
        setCurrentBlockNumber(currentBlockNumber);
        return;
    }

    while (block.isValid() && top <= event->rect().bottom())
    {
        if (block.isVisible() && bottom >= event->rect().top())
        {
            QString number = QString::number(blockNumber + 1);

            auto isCurrentLine = m_currentBlockNumber == blockNumber;
            painter.setPen(isCurrentLine ? currentLine : otherLines);

            painter.drawText(
                -5,
                top,
                // -INDICATOR_WIDTH: 预留空间给当前行组件
                sizeHint().width()- INDICATOR_WIDTH,
                m_codeEditParent->fontMetrics().height(),
                Qt::AlignRight,
                number
            );

            // 当前行组件
            if (isCurrentLine && currentLineIndicator.isValid()) {
                painter.setBrush(currentLineIndicator);
                painter.setPen(Qt::NoPen);
                painter.drawRect(sizeHint().width() - INDICATOR_WIDTH, top, INDICATOR_WIDTH, m_codeEditParent->fontMetrics().height());
            }
        }

        block = block.next();
        top = bottom;
        bottom = top + (int)m_codeEditParent->document()->documentLayout()->blockBoundingRect(block).height();
        ++blockNumber;
    }
}

void LineNumberArea::setCurrentBlockNumber(int number)
{
    if (m_currentBlockNumber == number) {
        return;
    }
    m_currentBlockNumber = number;
    update();
}
