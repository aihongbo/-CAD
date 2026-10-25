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

#include "CustomDelegate.h"

CustomDelegate::CustomDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
{
}

void CustomDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QStyledItemDelegate::paint(painter, option, index); // 先绘制默认的背景和文字

    if (option.state & QStyle::State_Selected) { // 检查项是否被选中
        QPixmap pixmap(":/Option/CAEOptionsTest.png"); 
        QIcon icon(pixmap);
        QPixmap scaledPixmap = icon.pixmap(QSize(pixmap.size())); // 根据需要调整图标大小
        //QRect iconRect = option.rect.adjusted(option.rect.width() - 4, 0, 0, 0); // 在项的右侧绘制图标

        // 图标与项的上边距为1px，下边距为1px，右边距为2px
        int topMargin = 1;
        int bottomMargin = 1;
        int rightMargin = 10;

        // 图标的宽度和高度
        int iconWidth = scaledPixmap.width();
        int iconHeight = scaledPixmap.height();

        // 计算图标的起始x坐标（基于项的宽度和右边距）
        int x = option.rect.width() - iconWidth - rightMargin;

        // 计算图标的起始y坐标（基于项的高度、上边距和下边距，确保图标垂直居中）
        int y = option.rect.top() + (option.rect.height() - iconHeight - topMargin - bottomMargin) / 2 + topMargin;

        // 创建图标的矩形区域
        QRect iconRect(x, y, iconWidth, iconHeight);

        painter->drawPixmap(iconRect, scaledPixmap);
    }
}


