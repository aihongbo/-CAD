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

#include "BreakpointArea.h"
#include "CodeEditor.h"
#include <QSyntaxStyle>

// Qt
#include <QTextEdit>
#include <QPainter>
#include <QTextBlock>
#include <QScrollBar>
#include <QAbstractTextDocumentLayout>
#include <QDebug>

using namespace NCTI;

#define INDICATOR_MARGIN 4

BreakpointArea::BreakpointArea(CodeEditor* parent) :
    QWidget(parent),
    m_syntaxStyle(nullptr),
    m_codeEditParent(parent),
    m_currentBlockNumber(-1),
    m_hoverBlockNumber(-1)
{
    setMouseTracking(true);
}

QSize BreakpointArea::sizeHint() const
{
    if (m_codeEditParent == nullptr)
    {
        return QWidget::sizeHint();
    }

    int space = m_codeEditParent->fontMetrics().height();
    return { space, 0 };
}

void BreakpointArea::setSyntaxStyle(QSyntaxStyle* style)
{
    m_syntaxStyle = style;
}
QSyntaxStyle* BreakpointArea::syntaxStyle() const
{
    return m_syntaxStyle;
}

void BreakpointArea::setCurrentBlockNumber(int number)
{
    m_currentBlockNumber = number;
    update();
}
bool BreakpointArea::containsBreakpoint(int blockNumber) const
{
    for (auto iter = m_breakpointList.begin(); iter != m_breakpointList.end(); iter++) {
        if (iter->blockNumber == blockNumber) {
            return true;
        }
    }
    return false;
}
void BreakpointArea::addBreakpoint(int blockNumber, bool enable)
{
    if (containsBreakpoint(blockNumber)) {
        return;
    }

    Breakpoint bp;
    bp.blockNumber = blockNumber;
    bp.enable = enable;
    m_breakpointList.append(std::move(bp));
    update();
}
void BreakpointArea::removeBreakpoint(int blockNumber)
{
    auto iter = findBreakpoint(blockNumber);
    if (iter == m_breakpointList.end()) {
        return;
    }
    m_breakpointList.erase(iter);
    update();
}
void BreakpointArea::clearBreakpoint()
{
    m_breakpointList.clear();
    update();
}
void BreakpointArea::enableBreakpoint(int blockNumber, bool enable)
{
    auto iter = findBreakpoint(blockNumber);
    if (iter == m_breakpointList.end() || iter->enable == enable) {
        return;
    }

    iter->enable = enable;
    update();
}
void BreakpointArea::enableAllBreakpoint(bool enable)
{
    for (auto iter = m_breakpointList.begin(); iter != m_breakpointList.end(); iter++)
    {
        if (iter->enable == enable) {
            continue;
        }
        iter->enable = enable;
    }
    update();
}
bool BreakpointArea::isEnableBreakpoint(int lineNumber)
{
    return findBreakpoint(lineNumber)->enable;
}

void BreakpointArea::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true); // 对矢量图形启用抗锯齿
    painter.setRenderHint(QPainter::TextAntialiasing, true); // 对文本启用抗锯齿
    painter.setRenderHint(QPainter::SmoothPixmapTransform, true); // 对位图变换启用平滑处理

    if (!m_syntaxStyle->getFormat("Breakpoint").isEmpty() && m_syntaxStyle->getFormat("Breakpoint").background().color().isValid()) {
       painter.fillRect(
           event->rect(),
           m_syntaxStyle->getFormat("Breakpoint").background().color()
       );
    }
    else
    {
        painter.fillRect(
            event->rect(),
            m_syntaxStyle->getFormat("Text").background().color()
        );
    }

    auto blockNumber = m_codeEditParent->getFirstVisibleBlock();
    auto block = m_codeEditParent->document()->findBlockByNumber(blockNumber);
    auto top = (int)m_codeEditParent->document()->documentLayout()->blockBoundingRect(block).translated(0, -m_codeEditParent->verticalScrollBar()->value()).top();
    auto bottom = top + (int)m_codeEditParent->document()->documentLayout()->blockBoundingRect(block).height();

    auto currentLine = m_syntaxStyle->getFormat("CurrentLineNumber").foreground().color();
    auto currentLineIndicator = m_syntaxStyle->getFormat("CurrentLineNumberIndicator").background().color();
    auto otherLines = m_syntaxStyle->getFormat("LineNumber").foreground().color();

    auto size = m_codeEditParent->fontMetrics().height();
    while (block.isValid() && top <= event->rect().bottom())
    {
        if (block.isVisible() && bottom >= event->rect().top())
        {
            // 命中
            auto isCurrentLine = m_currentBlockNumber == blockNumber;
            // 悬浮
            auto isHoverLine = m_hoverBlockNumber == blockNumber;
            // 标记
            auto isBreakpointLine = false;
            // 使能
            auto isEnable = false;

            auto iter = findBreakpoint(blockNumber);
            if (iter != m_breakpointList.end())
            {
                isBreakpointLine = true;
                isEnable = iter->enable;
            }

            painter.setPen(Qt::NoPen);
            painter.setBrush(Qt::NoBrush);

            if (isCurrentLine)
            {
                painter.setBrush(QColor(211, 36, 23));
                //auto pointRect = QRect(INDICATOR_MARGIN+1, top + INDICATOR_MARGIN+1, size - 2 * (INDICATOR_MARGIN+1), size - 2 * (INDICATOR_MARGIN+1));
                auto pointRect = QRect(INDICATOR_MARGIN, top + INDICATOR_MARGIN, size - 2 * INDICATOR_MARGIN, size - 2 * INDICATOR_MARGIN);
                painter.drawRoundedRect(
                    pointRect,
                    pointRect.width() / 2.0,
                    pointRect.width() / 2.0
                );

                auto rect = QRect(1, top+1, size-2, size-2);
                QPen pen;
                pen.setWidth(1);
                pen.setJoinStyle(Qt::RoundJoin);
                pen.setStyle(Qt::SolidLine);
                pen.setCapStyle(Qt::RoundCap);
                pen.setColor(QColor(255, 211, 44));
                painter.setPen(pen);
                painter.setBrush(Qt::NoBrush);
                painter.drawRoundedRect(rect, 2, 2);
            }
            else if (isBreakpointLine || isHoverLine)
            {

                if (isBreakpointLine)
                {
                    if (isEnable) {
                        painter.setBrush(QColor(211, 36, 23));
                    }
                    else {
                        painter.setBrush(QColor(131, 131, 131));
                    }
                }
                else if (isHoverLine) 
                {
                    painter.setBrush(QColor(93, 29, 24));
                }
                else{
                }

                auto pointRect = QRect(INDICATOR_MARGIN, top + INDICATOR_MARGIN, size - 2 * INDICATOR_MARGIN, size - 2 * INDICATOR_MARGIN);
                painter.drawRoundedRect(
                    pointRect,
                    pointRect.width() / 2.0,
                    pointRect.width() / 2.0
                );
            }
            else {

            }            
        }

        block = block.next();
        top = bottom;
        bottom = top + (int)m_codeEditParent->document()->documentLayout()->blockBoundingRect(block).height();
        ++blockNumber;
    }
}
void BreakpointArea::mouseMoveEvent(QMouseEvent* event)
{
    auto blockNumber = m_codeEditParent->getFirstVisibleBlock();
    auto block = m_codeEditParent->document()->findBlockByNumber(blockNumber);
    auto top = (int)m_codeEditParent->document()->documentLayout()->blockBoundingRect(block).translated(0, -m_codeEditParent->verticalScrollBar()->value()).top();
    auto bottom = top + (int)m_codeEditParent->document()->documentLayout()->blockBoundingRect(block).height();

    auto currentLine = m_syntaxStyle->getFormat("CurrentLineNumber").foreground().color();
    auto currentLineIndicator = m_syntaxStyle->getFormat("CurrentLineNumberIndicator").background().color();
    auto otherLines = m_syntaxStyle->getFormat("LineNumber").foreground().color();

    auto point = event->pos();
    auto hoverNumber = -1;
    while (block.isValid() && top <= rect().bottom())
    {
        auto blockBottom = top + (int)m_codeEditParent->document()->documentLayout()->blockBoundingRect(block).height();
        if (block.isVisible() && bottom >= rect().top() && (point.y() > top && point.y() < blockBottom))
        {
            hoverNumber = blockNumber;
            break;
        }

        block = block.next();
        top = bottom;
        bottom = top + (int)m_codeEditParent->document()->documentLayout()->blockBoundingRect(block).height();
        ++blockNumber;
    }

    setHoverBlockNumber(hoverNumber);
    QWidget::mouseMoveEvent(event);

}
void BreakpointArea::mousePressEvent(QMouseEvent* event)
{
    if (m_hoverBlockNumber >= 0) {
        Q_EMIT sigClicked(m_hoverBlockNumber, event->button());

        /*if (m_breakpointList.contains(m_hoverBlockNumber)) {
            removeBreakpoint(m_hoverBlockNumber);
            if (m_currentBlockNumber == m_hoverBlockNumber) {
                setCurrentBlockNumber(-1);
            }
            if (m_breakpointList.count()>0 && m_breakpointList.count() % 5 == 0) {
                setCurrentBlockNumber(m_breakpointList.last());
            }
        }
        else {
            addBreakpoint(m_hoverBlockNumber);
            if(m_breakpointList.count()%5==0){
                setCurrentBlockNumber(m_breakpointList.last());
            }
        }*/
    }
    QWidget::mousePressEvent(event);
}

#if QT_VERSION_MAJOR >= 6
void BreakpointArea::enterEvent(QEnterEvent* event)
{
    QWidget::setCursor(Qt::PointingHandCursor);
    QWidget::enterEvent(event);
}
#else
void BreakpointArea::enterEvent(QEvent* event)
{
    QWidget::setCursor(Qt::PointingHandCursor);
    QWidget::enterEvent(event);
}
#endif

void BreakpointArea::leaveEvent(QEvent* event)
{
    setHoverBlockNumber(-1);
    QWidget::setCursor(Qt::ArrowCursor);
    QWidget::leaveEvent(event);
}

void BreakpointArea::setHoverBlockNumber(int number)
{
    m_hoverBlockNumber = number;
    update();
}

QList<BreakpointArea::Breakpoint>::Iterator BreakpointArea::findBreakpoint(int blockNumber)
{
    for (auto iter = m_breakpointList.begin(); iter != m_breakpointList.end(); iter++) {
        if (iter->blockNumber == blockNumber) {
            return iter;
        }
    }
    return m_breakpointList.end();
}