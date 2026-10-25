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

#ifndef NctiDCM3BaseWidget_H
#define NctiDCM3BaseWidget_H

#include "ncti_base.h"
#include "dcl_ncti_qt_pubfun.h"
#include <QWidget>

namespace NCTI {
    class NctiDisplayModelBody;
    class NctiDocument;

    /**
     * @brief 添加材料对话框类
     * @details 用于添加材料属性的对话框
     */
    class DECL_NCTI_QT_PUBFUN NctiDCM3BaseWidget : public QWidget
    {
        Q_OBJECT
    public:
        /**
         * @brief 构造函数
         * @param i_parent 父窗口指针
         */
        NctiDCM3BaseWidget(NctiDocument* i_pDoc, QWidget* i_parent = nullptr);
        
        /**
         * @brief 析构函数
         */
        ~NctiDCM3BaseWidget();

        void setDimensionType(int i_dimType);
        virtual void execute() = 0;
    protected:
        NctiDocument* m_pDocument;
        Ncti_Integer m_dimType;
    };
}

#endif // !NctiDCM3BaseWidget_H