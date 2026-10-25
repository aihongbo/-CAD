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

#include "LoadingSpinnerWidget.h"

#include <cmath>
#include <algorithm>

#include <QPainter>
#include <QTimer>
#include <QDebug>
#include <QThreadPool>
#include "CallbackInterfaces.h"

namespace NCTI {

// 使用QRunnable适配器类来兼容Qt5
class LoadingCallbackRunnable : public QRunnable
{
public:
    LoadingCallbackRunnable(FuncCallback cb, FuncCallback doneCb, LoadingSpinnerWidget* spinnerWidget, void* pyState)
        : m_callback(cb)
        , m_finishCallback(doneCb)
		, m_spinner(spinnerWidget)
    {
        setAutoDelete(true);
    }

    void run() override
    {
        try {
            m_callback();
        }
        catch (...) {
            qWarning("Error occurred during callback running.");
        }

        QMetaObject::invokeMethod(
            m_spinner,
            [spinner = m_spinner, finishCb = m_finishCallback]() {
                if (spinner) {
                    spinner->stop();
                    spinner->deleteLater();
                }

                if (finishCb) {
                    finishCb();
                }
            },
            Qt::QueuedConnection);
    }

private:
    FuncCallback m_callback;
    FuncCallback m_finishCallback;
	LoadingSpinnerWidget* m_spinner;
};

LoadingSpinnerWidget::LoadingSpinnerWidget(QWidget* parent, bool centerOnParent, bool disableParentWhenSpinning)
    : QWidget(parent)
    , m_centerOnParent(centerOnParent)
    , m_disableParentWhenSpinning(disableParentWhenSpinning)
{
    initialize();
}

LoadingSpinnerWidget::LoadingSpinnerWidget(Qt::WindowModality modality,
                                           QWidget* parent,
                                           bool centerOnParent,
                                           bool disableParentWhenSpinning)
    : LoadingSpinnerWidget(parent, centerOnParent, disableParentWhenSpinning)
{
    setWindowModality(modality);
    setAttribute(Qt::WA_TranslucentBackground);
    setWindowFlags(windowFlags() | Qt::Dialog | Qt::FramelessWindowHint);
}

LoadingSpinnerWidget::~LoadingSpinnerWidget()
{
    if (NctiPyInstance->HasCallbacks() && m_pyState) {
        NctiPyCB.PyRestoreThread(m_pyState);
    }
}

void LoadingSpinnerWidget::initialize()
{
    m_timer.reset(new QTimer(this));
    connect(m_timer.get(), &QTimer::timeout, this, &LoadingSpinnerWidget::rotate);
    updateSize();
    updateTimer();
    hide();
}

void LoadingSpinnerWidget::showLoading(QWidget* parent,
                                       FuncCallback callback,
                                       FuncCallback finishCb,
                                       QPoint pt,
                                       QColor clr)
{
    void* pState = nullptr;
    if(NctiPyInstance->HasCallbacks())
        pState = NctiPyCB.PySaveThread();
    
    auto spinner = new LoadingSpinnerWidget(Qt::WindowModality::ApplicationModal, parent, true, false);
    if (!pt.isNull()) {
        spinner->setCenterOnParent(false);
        spinner->move(pt);
    }

    if (clr.isValid()) { spinner->setColor(clr); }

    spinner->start();

    spinner->setPyState(pState);

    QThreadPool::globalInstance()->start(new LoadingCallbackRunnable(callback, finishCb, spinner, pState));
}

void LoadingSpinnerWidget::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    if (m_currentCounter >= m_numberOfLines) { m_currentCounter = 0; }

    painter.setPen(Qt::NoPen);
    for (int i = 0; i < m_numberOfLines; ++i) {
        drawLine(&painter, i);
    }

    if (!m_text.isEmpty()) {
        painter.save();
        painter.setPen(m_color);
        painter.drawText(rect(), Qt::AlignCenter, m_text);
        painter.restore();
    }
}

void LoadingSpinnerWidget::drawLine(QPainter* painter, int index) const
{
    painter->save();

    painter->translate(m_innerRadius + m_lineLength, m_innerRadius + m_lineLength);
    painter->rotate(index * 360.0 / m_numberOfLines);
    painter->translate(m_innerRadius, 0);

    int distance = lineCountDistanceFromPrimary(index, m_currentCounter, m_numberOfLines);
    QColor color = currentLineColor(distance, m_numberOfLines, m_trailFadePercentage, m_minTrailOpacity, m_color);

    painter->setBrush(color);

    // TODO improve the way rounded rect is painted
    painter->drawRoundedRect(
        QRect(0, -m_lineWidth / 2, m_lineLength, m_lineWidth), m_roundness, m_roundness, Qt::RelativeSize);

    painter->restore();
}

void LoadingSpinnerWidget::start()
{
    updatePosition();

    m_isSpinning = true;
    show();

    if (m_disableParentWhenSpinning && parentWidget()) { parentWidget()->setEnabled(false); }

    if (!m_timer->isActive()) {
        m_timer->start();
        m_currentCounter = 0;
    }
}

void LoadingSpinnerWidget::stop()
{
    m_isSpinning = false;
    hide();

    if (m_disableParentWhenSpinning && parentWidget()) { parentWidget()->setEnabled(true); }

    if (m_timer->isActive()) {
        m_timer->stop();
        m_currentCounter = 0;
    }
}

void LoadingSpinnerWidget::setNumberOfLines(int lines)
{
    m_numberOfLines  = lines;
    m_currentCounter = 0;
    updateTimer();
}

void LoadingSpinnerWidget::setLineLength(int length)
{
    m_lineLength = length;
    updateSize();
}

void LoadingSpinnerWidget::setLineWidth(int width)
{
    m_lineWidth = width;
    updateSize();
}

void LoadingSpinnerWidget::setInnerRadius(int radius)
{
    if (radius <= 0) {
        qWarning() << "Invalid inner radius value:" << radius;
        return;
    }
    m_innerRadius = radius;
    updateSize();
}

void LoadingSpinnerWidget::setText(QString text)
{
    m_text = text;
    update();
}

QColor LoadingSpinnerWidget::color()
{
    return m_color;
}

qreal LoadingSpinnerWidget::roundness() const
{
    return m_roundness;
}

qreal LoadingSpinnerWidget::minimumTrailOpacity() const
{
    return m_minTrailOpacity;
}

qreal LoadingSpinnerWidget::trailFadePercentage() const
{
    return m_trailFadePercentage;
}

qreal LoadingSpinnerWidget::revolutionsPerSecond() const
{
    return m_revolutionsPerSecond;
}

int LoadingSpinnerWidget::numberOfLines() const
{
    return m_numberOfLines;
}

int LoadingSpinnerWidget::lineLength() const
{
    return m_lineLength;
}

int LoadingSpinnerWidget::lineWidth() const
{
    return m_lineWidth;
}

int LoadingSpinnerWidget::innerRadius() const
{
    return m_innerRadius;
}

bool LoadingSpinnerWidget::isSpinning() const
{
    return m_isSpinning;
}

void LoadingSpinnerWidget::setCenterOnParent(bool bCenter)
{
    m_centerOnParent = bCenter;
}

void LoadingSpinnerWidget::setPyState(void* state)
{
    m_pyState = state;
}

void LoadingSpinnerWidget::setRoundness(qreal roundness)
{
    m_roundness = std::max(0.0, std::min(100.0, roundness));
}

void LoadingSpinnerWidget::setColor(QColor color)
{
    m_color = color;
}

void LoadingSpinnerWidget::setRevolutionsPerSecond(qreal revolutionsPerSecond)
{
    m_revolutionsPerSecond = revolutionsPerSecond;
    updateTimer();
}

void LoadingSpinnerWidget::setTrailFadePercentage(qreal trail)
{
    m_trailFadePercentage = trail;
}

void LoadingSpinnerWidget::setMinimumTrailOpacity(qreal minimumTrailOpacity)
{
    m_minTrailOpacity = minimumTrailOpacity;
}

void LoadingSpinnerWidget::rotate()
{
    ++m_currentCounter;
    if (m_currentCounter >= m_numberOfLines) { m_currentCounter = 0; }
    update();
}

void LoadingSpinnerWidget::updateSize()
{
    int size = (m_innerRadius + m_lineLength) * 2;
    setFixedSize(size, size);
}

void LoadingSpinnerWidget::updateTimer()
{
    m_timer->setInterval(1000 / (m_numberOfLines * m_revolutionsPerSecond));
}

void LoadingSpinnerWidget::updatePosition()
{
    QWidget* parent = parentWidget();
    if (!parent || !m_centerOnParent) { return; }

    ensurePolished();

    int x      = parent->width() / 2 - width() / 2;
    int y      = parent->height() / 2 - height() / 2;
    QPoint pos = parent->mapToGlobal(QPoint(x, y));
    move(pos);
}

int LoadingSpinnerWidget::lineCountDistanceFromPrimary(int current, int primary, int totalNrOfLines)
{
    int distance = primary - current;
    if (distance < 0) { distance += totalNrOfLines; }
    return distance;
}

QColor LoadingSpinnerWidget::currentLineColor(int countDistance,
                                              int totalNrOfLines,
                                              qreal trailFadePerc,
                                              qreal minOpacity,
                                              QColor color)
{
    if (countDistance == 0) { return color; }
    const qreal minAlphaF = minOpacity / 100.0;
    int distanceThreshold = static_cast<int>(ceil((totalNrOfLines - 1) * trailFadePerc / 100.0));
    if (countDistance > distanceThreshold) { 
        color.setAlphaF(minAlphaF); 
    }
    else {
        qreal alphaDiff   = color.alphaF() - minAlphaF;
        qreal gradient    = alphaDiff / static_cast<qreal>(distanceThreshold + 1);
        qreal resultAlpha = color.alphaF() - gradient * countDistance;

        // If alpha is out of bounds, clip it.
        resultAlpha = std::min(1.0, std::max(0.0, resultAlpha));
        color.setAlphaF(resultAlpha);
    }
    return color;
}

} // namespace NCTI
