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
#include <QStackedWidget>

namespace NCTI {

    /**
     * @brief 树侧边面板类
     * @details 用于管理树形控件侧边面板的界面控件，继承自QStackedWidget
     */
    class DECL_NCTI_QT_PUBFUN NctiTreeSidePanel : public QStackedWidget
    {
        Q_OBJECT
            NCTI_QT_PUBFUNC_DECLARE_PRIVATE(NctiTreeSidePanel)
    public:
        /**
         * @brief 构造函数
         * @param parent 父窗口指针
         */
        explicit NctiTreeSidePanel(QWidget* parent = nullptr);
        
        /**
         * @brief 析构函数
         */
        virtual ~NctiTreeSidePanel();

    public:
        /**
         * @brief 显示内容页面
         * @param index 索引
         */
        void showContentPage(int index);
        
    protected:

    };
}