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

#include "ViewControl.h"

#include "UIOptionManager.h"
#include "ObjectTreeManager.h"

#include "NctiQTPubFun.h"
#include "NctiDocElementPubFun.h"
#include "NctiWindowViewManager.h"
#include "NctiDocument.h"
#include "NctiWindowPlatform.h"

namespace NCTI {

ViewControl::ViewControl(MainWindow* mainWindow)
    : MainWindowModule(mainWindow)
{
}

void ViewControl::initialize()
{
    connect(m_mainWindow->Signals(), &MainWindowSignals::isometricView, this, &ViewControl::onIsometricView);
    connect(m_mainWindow->Signals(), &MainWindowSignals::zoomAll, this, &ViewControl::onZoomAll);
    connect(m_mainWindow->Signals(), &MainWindowSignals::maxView, this, &ViewControl::onMaxView);

    connect(m_mainWindow->Signals(), &MainWindowSignals::showAll, this, &ViewControl::onShowAll);
    connect(m_mainWindow->Signals(), &MainWindowSignals::hideSel, this, &ViewControl::onHideSel);
    connect(m_mainWindow->Signals(), &MainWindowSignals::showSel, this, &ViewControl::onShowSel);

    connect(m_mainWindow->Signals(), &MainWindowSignals::setView, this, &ViewControl::onSetView);

    connect(m_mainWindow->Signals(), &MainWindowSignals::addVtkView, this, &ViewControl::onAddVtkView);
    connect(m_mainWindow->Signals(), &MainWindowSignals::addVulkanView, this, &ViewControl::onAddVulkanView);

    connect(m_mainWindow->Signals(), &MainWindowSignals::selectMode, this, &ViewControl::onSelectMode);
    connect(m_mainWindow->Signals(), &MainWindowSignals::visualMode, this, &ViewControl::onVisualMode);
    connect(m_mainWindow->Signals(), &MainWindowSignals::selectAll, this, &ViewControl::onSelectAll);
}

void ViewControl::updateDisplayMode(bool face, bool edge, bool vertex)
{
    auto uiOptMgr = m_mainWindow->getUIOptionMgr();
    if (!uiOptMgr) {
        return;
    }
    auto checkBoxs = uiOptMgr->getVisualCheckBoxs();
    
    if (checkBoxs["visual_face"])   { checkBoxs["visual_face"]->setChecked(face); }
    if (checkBoxs["visual_edge"])   { checkBoxs["visual_edge"]->setChecked(edge); }
    if (checkBoxs["visual_vertex"]) { checkBoxs["visual_vertex"]->setChecked(vertex); }
    if (checkBoxs["visual_body"])   { checkBoxs["visual_body"]->setChecked(face && edge && vertex); }

    NctiQTPubFun::SetVisualMode(m_mainWindow->getWindowPlatform(), face, edge, vertex);
}

void ViewControl::onShowAll()
{
    NctiQTPubFun::ShowAll(m_mainWindow->getWindowPlatform());
}

void ViewControl::onHideSel()
{
    NctiQTPubFun::HideSel(m_mainWindow->getWindowPlatform());
}

void ViewControl::onShowSel()
{
    NctiQTPubFun::OnlySelShow(m_mainWindow->getWindowPlatform());
}

void ViewControl::onIsometricView()
{
    NctiQTPubFun::SetView(m_mainWindow->getWindowPlatform(), EnumNctiViewMode::NCTI_VIEW_MODE_ISO);
}

void ViewControl::onZoomAll()
{
    auto platform = m_mainWindow->getWindowPlatform();
    if (!platform || !platform->GetCurrentViewManager())
        return;

    auto doc = platform->GetCurrentViewManager()->GetDocument();
    NctiDocElementPubFun::SetFocusBySel(doc);
}

void ViewControl::onMaxView()
{
    NctiQTPubFun::MaxView(m_mainWindow->getWindowPlatform());
}

void ViewControl::onSetView(const QString& objName)
{
    if (objName == "xplus") {
        return NctiQTPubFun::SetView(m_mainWindow->getWindowPlatform(), EnumNctiViewMode::NCTI_VIEW_MODE_XPLUS);
    }

    if (objName == "xminus") {
        return NctiQTPubFun::SetView(m_mainWindow->getWindowPlatform(), EnumNctiViewMode::NCTI_VIEW_MODE_XMINUS);
    }

    if (objName == "yplus") {
        return NctiQTPubFun::SetView(m_mainWindow->getWindowPlatform(), EnumNctiViewMode::NCTI_VIEW_MODE_YPLUS);
    }

    if (objName == "yminus") {
        return NctiQTPubFun::SetView(m_mainWindow->getWindowPlatform(), EnumNctiViewMode::NCTI_VIEW_MODE_YMINUS);
    }

    if (objName == "zplus") {
        return NctiQTPubFun::SetView(m_mainWindow->getWindowPlatform(), EnumNctiViewMode::NCTI_VIEW_MODE_ZPLUS);
    }

    if (objName == "zminus") {
        return NctiQTPubFun::SetView(m_mainWindow->getWindowPlatform(), EnumNctiViewMode::NCTI_VIEW_MODE_ZMINUS);
    }
}

void ViewControl::onSelectAll()
{
    NctiDocument* i_pDocument = NctiQTPubFun::GetCurrentViewDocment(m_mainWindow->getWindowPlatform());
    if (!i_pDocument) {
        return;
    }
    NctiQTPubFun::SelectAll(i_pDocument, m_mainWindow);
}

void ViewControl::onAddVtkView()
{
    NctiWindowPlatform* platform = m_mainWindow->getWindowPlatform();
    if (!platform || !platform->GetCurrentViewManager() || !platform->GetCurrentViewManager()->GetDocument()) {
        return;
    }
    NctiQTPubFun::AddRenderView(platform->GetCurrentViewManager(), NCTI_RENDER_VTK);
    m_mainWindow->getObjectTreeMgr()->SetTreeModified();
}

void ViewControl::onAddVulkanView()
{
    auto doc = NctiQTPubFun::GetCurrentViewDocment(m_mainWindow->getWindowPlatform());
    NctiWindowPlatform* platform = m_mainWindow->getWindowPlatform();
    if (!doc)
        return;

    NctiQTPubFun::AddRenderView(platform->GetCurrentViewManager(), NCTI_RENDER_VULKAN);
    m_mainWindow->getObjectTreeMgr()->SetTreeModified();
}

void ViewControl::onSelectMode(const QString& objName)
{
    auto selCheckBoxs = m_mainWindow->getUIOptionMgr()->getSelCheckBoxs();

    bool bChecked = selCheckBoxs[objName]->isChecked();
    if (objName == "select_body") {
        //选择体
        if (bChecked) {
            selCheckBoxs["select_face"]->setChecked(true);
            selCheckBoxs["select_edge"]->setChecked(true);
            selCheckBoxs["select_vertex"]->setChecked(true);
        }
    }
    else {
        if (!bChecked) {
            selCheckBoxs["select_body"]->setChecked(false);
        }
    }

    updateSelMode(selCheckBoxs["select_body"]->isChecked(),
                  selCheckBoxs["select_face"]->isChecked(),
                  selCheckBoxs["select_edge"]->isChecked(),
                  selCheckBoxs["select_vertex"]->isChecked());
}

void ViewControl::updateSelMode(bool bBody, bool bFace, bool bEdge, bool bVertex)
{
    NctiWindowPlatform* platform = m_mainWindow->getWindowPlatform();
    if (platform) {
        NctiQTPubFun::SelBody(platform, bBody);
        NctiQTPubFun::SelFace(platform, bFace);
        NctiQTPubFun::SelEdge(platform, bEdge);
        NctiQTPubFun::SelVertex(platform, bVertex);
    }
}

void ViewControl::onVisualMode(const QString& objName)
{
    auto visualCheckBoxs = m_mainWindow->getUIOptionMgr()->getVisualCheckBoxs();
    if (objName == "visual_body") {
        //显示体
        bool bChecked = visualCheckBoxs[objName]->isChecked();
        for (auto& act : visualCheckBoxs) {
            if (act->objectName() != objName) {
                if (bChecked) {
                    act->setChecked(true);
                }
                act->setEnabled(!bChecked);
            }
        }
    }

    bool face = visualCheckBoxs["visual_face"]->isChecked();
    bool edge = visualCheckBoxs["visual_edge"]->isChecked();
    bool vertex = visualCheckBoxs["visual_vertex"]->isChecked();
    NctiQTPubFun::SetVisualMode(m_mainWindow->getWindowPlatform(), face, edge, vertex);
}

} // namespace NCTI