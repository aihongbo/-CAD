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

#ifndef CUSTOMDELEGATE_H
#define CUSTOMDELEGATE_H

#include <QStyledItemDelegate>
#include <QPainter>

/**
 * @brief 自定义委托类
 * @details 用于在视图项中绘制自定义图标和内容的委托类
 */
class CustomDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    /**
     * @brief 构造函数
     * @param parent 父对象指针
     */
    explicit CustomDelegate(QObject *parent = nullptr);

    /**
     * @brief 绘制函数
     * @param painter 绘图器指针
     * @param option 视图项选项
     * @param index 模型索引
     */
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
};

#endif // CUSTOMDELEGATE_H