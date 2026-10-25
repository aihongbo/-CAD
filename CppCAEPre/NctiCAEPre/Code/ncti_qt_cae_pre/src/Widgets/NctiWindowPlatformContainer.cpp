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

#include "NctiWindowPlatformContainer.h"
#include "NctiWindowPlatform.h"
#include "NctiQTPubFun.h"

#include <QMoveEvent>
#include <QPoint>
#include <QTimer>
#include <QWindow>
#include <QApplication>

#ifdef Q_OS_WIN
#include <Windows.h>
#endif

namespace NCTI {
NctiWindowPlatformContainer::NctiWindowPlatformContainer(QWidget* i_pParent)
    : QWidget(i_pParent)
    , m_lastPos(QPoint())
    , m_updateTimer(new QTimer(this))
{
    m_updateTimer->setSingleShot(true);
    connect(m_updateTimer, &QTimer::timeout, this, &NctiWindowPlatformContainer::updatePlatform);
}

NctiWindowPlatformContainer::~NctiWindowPlatformContainer()
{
    ClosePlatform();

    if (m_updateTimer) {
        m_updateTimer->stop();
        delete m_updateTimer;
        m_updateTimer = nullptr;
    }
}

void NctiWindowPlatformContainer::CreatePlatform()
{
    if (nullptr == m_platform) {
        m_platform = NctiQTPubFun::CreateNctiViewWindow(this);
    }
    Q_EMIT updatePlatform();
}

NctiWindowPlatform* NctiWindowPlatformContainer::GetPlatform() const
{
    return m_platform;
}

void NctiWindowPlatformContainer::ClosePlatform()
{
    if (m_platform) {
        delete m_platform;
        m_platform = nullptr;
    }
}

NctiDocument* NctiWindowPlatformContainer::GetCurrentViewDocument()
{
    return NctiQTPubFun::GetCurrentViewDocment(m_platform);
}

void NctiWindowPlatformContainer::resizeEvent(QResizeEvent* event)
{
    QWidget::resizeEvent(event);

    // 定义一个阈值，用于判断尺寸变化是否显著
    const int threshold = 1;
    QSize newSize       = event->size();
    if (qAbs(newSize.width() - m_lastSize.width()) > threshold
        || qAbs(newSize.height() - m_lastSize.height()) > threshold) {
        m_updateTimer->start(10);
        m_lastSize = newSize;
    }
}

void NctiWindowPlatformContainer::moveEvent(QMoveEvent* event)
{
    QWidget::moveEvent(event);

    // 定义一个阈值，用于判断位置变化是否显著
    const int threshold = 1;
    QPoint newPos       = event->pos();
    if (qAbs(newPos.x() - m_lastPos.x()) > threshold 
        || qAbs(newPos.y() - m_lastPos.y()) > threshold) {
        m_updateTimer->start(10);
        m_lastPos = newPos;
    }
}

} // namespace NCTI
