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

#include "dcl_ncti_qt_pubfun.h"
#include <QStyledItemDelegate>

namespace NCTI {
    /**
     * @brief 树视图委托类
     * @details 用于自定义树视图项的绘制和编辑方式，继承自QStyledItemDelegate
     */
    class DECL_NCTI_QT_PUBFUN NctiTreeViewDelegate : public QStyledItemDelegate
    {
        Q_OBJECT
    public:
        /**
         * @brief 构造函数
         * @param parent 父窗口指针
         */
        explicit NctiTreeViewDelegate(QWidget* parent = 0);

        /**
         * @brief 绘制函数
         * @param painter 绘图设备指针
         * @param option 样式选项
         * @param index 模型索引
         */
        void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const override;
    };
}