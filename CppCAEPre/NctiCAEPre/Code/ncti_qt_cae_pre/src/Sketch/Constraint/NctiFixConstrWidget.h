/*
 * Copyright (c) 2026 粤港澳大湾区（广东）国创中心
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

#ifndef NctiFixConstrWidget_H
#define NctiFixConstrWidget_H

#include "ncti_base.h"
#include "dcl_ncti_qt_pubfun.h"
#include "NctiDCMDef.h"
#include "NctiConstrContentWidget.h"

namespace NCTI {
    class NctiDocument;
    class NctiDisplaySketchObject;
    class NctiFixConstrWidget : public NctiConstrContentWidget
    {
        Q_OBJECT
    public:
        /**
         * @brief 构造函数
         * @param i_parent 父窗口指针
         */
        NctiFixConstrWidget(NctiDocument* i_doc, QWidget* i_parent = nullptr);
        
        /**
         * @brief 析构函数
         */
        ~NctiFixConstrWidget();

    public:
        virtual bool apply() override; 

    private Q_SLOTS:
        void selGeometry();

    private:
        void init();

    private:
        NctiDisplaySketchObject* m_selGeom;
    };
}

#endif // !NctiFixConstrWidget_H