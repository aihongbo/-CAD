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

#pragma once

#include <QStyledItemDelegate>
#include <QPainter>
#include <QStyleOptionViewItem>

namespace NCTI {
    /**
     * @brief 文件过滤树委托类
     * @details 自定义QTreeWidget的项绘制样式
     */
    class FileFilterTreeDelegate : public QStyledItemDelegate
    {
    public:
        /**
         * @brief 构造函数
         * @param parent 父对象指针
         */
        FileFilterTreeDelegate(QObject* parent = nullptr);
        
        /**
         * @brief 获取项大小提示
         * @param option 样式选项
         * @param index 模型索引
         * @return 项的大小
         */
        QSize sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const override;
        
        /**
         * @brief 绘制项
         * @param painter 绘图设备
         * @param option 样式选项
         * @param index 模型索引
         */
        void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const override;
    };

}