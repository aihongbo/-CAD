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

#include "NctiTreeSidePannel.h"

#include <QtEvents>

namespace NCTI {

    class NctiTreeSidePanel::PrivateData
    {
        NCTI_QT_PUBFUNC_DECLARE_PUBLIC(NctiTreeSidePanel)
    public:
        PrivateData(NctiTreeSidePanel* parent) : q_ptr(parent) {}
        void init();
    public:
    };

    void NctiTreeSidePanel::PrivateData::init()
    {
    }

    //==============================================================
    // NctiTreeSidePanel
    //==============================================================
    NctiTreeSidePanel::NctiTreeSidePanel(QWidget* parent)
        : QStackedWidget(parent)
        , d_ptr(new PrivateData(this))
    {

    }

    NctiTreeSidePanel::~NctiTreeSidePanel()
    {
    }

    void NctiTreeSidePanel::showContentPage(int index)
    {
        if (index < 0 || index >= count())
            return;
        setCurrentIndex(index);
    }
}
