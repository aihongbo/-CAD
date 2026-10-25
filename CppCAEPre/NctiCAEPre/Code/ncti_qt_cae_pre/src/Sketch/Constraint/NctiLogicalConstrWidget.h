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

#ifndef NctiLogicalConstrWidget_H
#define NctiLogicalConstrWidget_H

#include "ncti_base.h"
#include "dcl_ncti_qt_pubfun.h"
#include "NctiDCMDef.h"
#include "NctiConstrContentWidget.h"

namespace NCTI {
    class NctiDocument;
    class NctiDisplaySketchObject;
    class NctiLogicalConstrWidget : public NctiConstrContentWidget
    {
        Q_OBJECT
    public:
        /**
         * @brief 构造函数
         * @param i_parent 父窗口指针
         */
        NctiLogicalConstrWidget(NctiDocument* i_doc, ncti_DCM_d_type i_dt, QWidget* i_parent = nullptr);
        
        /**
         * @brief 析构函数
         */
        ~NctiLogicalConstrWidget();

    public:
        virtual bool apply() override; 

    private Q_SLOTS:
        void selCurve1();
        void selCurve2();

    private:
        void init();

    private:
        NctiDisplaySketchObject* m_selCurve1;
        NctiDisplaySketchObject* m_selCurve2;
    };
}

#endif // !NctiLogicalConstrWidget_H