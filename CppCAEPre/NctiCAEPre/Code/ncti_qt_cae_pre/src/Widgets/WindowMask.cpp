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

#include "WindowMask.h"
#include <QtEvents>
#include <QApplication>

namespace NCTI {

    WindowMask::WindowMask(QWidget* parent)
        : QWidget(parent)
        , m_topWidget(parent)
    {
        init();
    }

    void WindowMask::init()
    {
        setWindowFlags(Qt::FramelessWindowHint | Qt::Tool);
        setAttribute(Qt::WA_TransparentForMouseEvents, true);
        setMaskColor(QColor(194, 194, 196), 0.4f);
    }

    void WindowMask::addWidget(QWidget* widget)
    {
        if (widget && widget != this) {
            widget->installEventFilter(this);
            m_widget = widget;
            connect(m_widget, &QWidget::destroyed, this, [this]() {
                m_widget = nullptr; 
            });
        }
    }

    void WindowMask::setMaskColor(const QColor& color, float opacity)
    {
        if (!color.isValid()) { return; }
        QPalette palette = this->palette();
        palette.setColor(QPalette::Window, color);
        this->setPalette(palette);

        setWindowOpacity(opacity);
    }

    void WindowMask::setTopWidget(QWidget* widget)
    {
        if (widget) {
            m_topWidget = widget;
        }
    }

    void WindowMask::showEvent(QShowEvent* event)
    {
        Q_UNUSED(event);
        this->setGeometry(m_topWidget->geometry());
    }

    bool WindowMask::eventFilter(QObject* watched, QEvent* event)
    {
        if (watched == m_widget) {
            switch (event->type()) {
            case QEvent::Show:
                this->show();
                break;
            case QEvent::Hide:
                this->hide();
                break;
            default:
                break;
            }
        }
        return QObject::eventFilter(watched, event);
    }
}
