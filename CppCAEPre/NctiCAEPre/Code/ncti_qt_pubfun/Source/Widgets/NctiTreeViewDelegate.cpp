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

#include "NctiTreeViewDelegate.h"

#include <QPainter>

namespace NCTI {
    static int iconSize = 16;
    static int margin = 2;
    NctiTreeViewDelegate::NctiTreeViewDelegate(QWidget* parent)
        : QStyledItemDelegate(parent)
    {
    }

    void NctiTreeViewDelegate::paint(
        QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const
    {
        QStyledItemDelegate::paint(painter, option, index);

        if (option.state & QStyle::State_Selected) {
            static QIcon icon;
            if (icon.isNull()) {
                icon = QIcon(":/Tree/selected.svg");
            }
            QRect rect(option.rect.right() - iconSize, option.rect.center().y() - iconSize / 2, iconSize, iconSize);
            icon.paint(painter, rect);
        }
    }
}
