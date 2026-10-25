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

#include "FileFilterTreeDelegate.h"
#include <QApplication>
#include <QPainterPath>

namespace NCTI {
    FileFilterTreeDelegate::FileFilterTreeDelegate(QObject* parent)
        : QStyledItemDelegate(parent) 
    {
    }

    void FileFilterTreeDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const
    {
        QStyleOptionViewItem opt = option;
        initStyleOption(&opt, index);

        // 绘制圆角背景（选中与非选中状态）
        painter->save();
        painter->setRenderHint(QPainter::Antialiasing);
        QRect rect = opt.rect.adjusted(2, 2, -2, -2);
        QPainterPath path;
        path.addRoundedRect(rect, 4, 4);
        painter->fillPath(path, opt.state & QStyle::State_Selected ? QColor("#E5F1FF") : Qt::white);
        painter->restore();

        // 绘制左侧图标
        QIcon leftIcon = index.data(Qt::DecorationRole).value<QIcon>();
        if (!leftIcon.isNull()) {
            QRect iconRect = rect.adjusted(8, 8, -8, -8);
            leftIcon.paint(painter, iconRect, Qt::AlignLeft | Qt::AlignVCenter);
        }

        // 绘制文本
        QPalette palette = opt.palette;
        palette.setColor(QPalette::Text, opt.state & QStyle::State_Selected ? QColor("#1C72F3") : QColor("#52555A"));
        opt.palette = palette;

        QRect textRect = rect.adjusted(36, 0, -40, 0); 
        QApplication::style()->drawItemText(painter, textRect, Qt::AlignLeft | Qt::AlignVCenter, palette, true, opt.text);

        // 绘制右侧选中图标
        if (opt.state & QStyle::State_Selected) {
            QIcon checkedIcon(":/recentpage/tree_item_selected.svg");
            QSize iconSize = checkedIcon.actualSize(QSize(4, 20));
            QRect checkRect(rect.right() - iconSize.width() - 10, rect.y(), iconSize.width(), rect.height());
            checkedIcon.paint(painter, checkRect, Qt::AlignRight | Qt::AlignVCenter);
        }
    }

    QSize FileFilterTreeDelegate::sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const
    {
        return QSize(276, 46);
    }
}
