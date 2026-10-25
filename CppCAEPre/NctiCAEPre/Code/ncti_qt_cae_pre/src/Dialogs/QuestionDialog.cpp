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

#include "QuestionDialog.h"
#include <QLabel>
#include "ui_DialogButtonGroup.h"

namespace NCTI {
QuestionDialog::QuestionDialog(QWidget* parent)
    : Dialog(parent)
{
    addByWidget("content", new QLabel(this));
    addDefaultCancelAndConfire();
}

int QuestionDialog::exec(const QString& title, const QString& message)
{
    if (!title.isNull()) {
        setTitle(title);
    }
    if (!message.isNull()) {
        auto content = qobject_cast<QLabel*>(getWidget("content"));
        if (content) {
            content->setText(message);
        }
    }
    return Dialog::exec();
}
} // namespace NCTI
