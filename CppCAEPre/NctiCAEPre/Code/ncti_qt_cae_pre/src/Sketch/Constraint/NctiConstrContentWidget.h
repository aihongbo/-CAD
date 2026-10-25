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

#ifndef NctiConstrContentWidget_H
#define NctiConstrContentWidget_H

#include "ncti_base.h"
#include "dcl_ncti_qt_pubfun.h"
#include "NctiSketchConstrSolver.h"
#include "NctiDCMDef.h"
#include <QWidget>

namespace NCTI {
    class NctiDocument;
    class NctiSketchConstrManager;
    class NctiConstrContentWidget : public QWidget
    {
        Q_OBJECT
    public:
        /**
         * @brief 构造函数
         * @param i_parent 父窗口指针
         */
        NctiConstrContentWidget(NctiDocument* i_doc, ncti_DCM_d_type i_dt, QWidget* i_parent = nullptr);
        
        /**
         * @brief 析构函数
         */
        ~NctiConstrContentWidget();

    public:
        virtual bool apply() = 0;

    public:
        NctiDocument* getDoc() const;
        ncti_DCM_d_type getConstrType() const;
        NctiSketchConstrSolver* getSolver() const;
    private:
        NctiDocument* m_doc;
        NctiSketchConstrSolver* m_solver;
        ncti_DCM_d_type m_constrType;
    };
}

#endif // !NctiConstrContentWidget_H