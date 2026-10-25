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

#include "ColorLineEdit.h"

#include <QKeyEvent>
#include <QDebug>

ColorLineEdit::ColorLineEdit(QWidget* parent)
    : QLineEdit(parent)
{
    setAttribute(Qt::WA_StyledBackground, true);
}

void ColorLineEdit::keyPressEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter) {
        // 在这里处理回车键事件
        qDebug() << "Enter key pressed!";
        Q_EMIT updateColor();

        return;
    }
    else {
        // 对于其他按键，调用基类的实现
        QLineEdit::keyPressEvent(event);
    }
}
