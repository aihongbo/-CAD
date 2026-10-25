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

#include "SimulationController.h"
#include "UIOptionManager.h"
#include "ObjectTreeManager.h"
#include "UserInteractionManager.h"

#include "MeshAddForceView.h"
#include "MeshAddSpcView.h"
#include "MeshAddMatView.h"
#include "MeshSettingView.h"
#include "MeshQualitySettingView.h"
#include "MeshQuickSelect.h"

#include "NctiQTPubFun.h"
#include "NctiCommandManager.h"
#include "NctiDocument.h"
#include "NctiRenderUnstructureItem.h"
#include "NctiDocViewManager.h"
#include "NctiDocElementPubFun.h"
#include "NctiDisplayDocCustomContainer.h"
#include "NctiArgumentObject.h"
#include "NctiDisplayGridMeshPub.h"
#include "NctiDisplayGridMesh.h"

#include "LoadingSpinnerWidget.h"
#include "MeshModifyMeshTypeView.h"


namespace NCTI {

SimulationController::SimulationController(MainWindow* mainWindow)
    : MainWindowModule(mainWindow)
{
}

void SimulationController::initialize()
{
    connect(m_mainWindow->Signals(), &MainWindowSignals::meshAddForce, this, &SimulationController::onMeshAddForce);
    connect(m_mainWindow->Signals(), &MainWindowSignals::meshAddSpc, this, &SimulationController::onMeshAddSpc);
    connect(m_mainWindow->Signals(), &MainWindowSignals::meshAddMat, this, &SimulationController::onMeshAddMat);
    connect(m_mainWindow->Signals(), &MainWindowSignals::meshFromSurface, this, &SimulationController::onMeshFromSurface);
    connect(m_mainWindow->Signals(), &MainWindowSignals::meshFromVolume, this, &SimulationController::onMeshFromVolume);
    connect(m_mainWindow->Signals(), &MainWindowSignals::meshShowMeshQuality, this, &SimulationController::onMeshShowMeshQuality);
    connect(m_mainWindow->Signals(), &MainWindowSignals::meshGridSelect, this, &SimulationController::onSelectMode);
	connect(m_mainWindow->Signals(), &MainWindowSignals::meshQuickSelect, this, &SimulationController::onQuickSelect);
	connect(m_mainWindow->Signals(), &MainWindowSignals::meshModifyMeshType, this, &SimulationController::onModifyMeshType);
}

int SimulationController::getMeshType()
{
    int m_meshType                    = -1;
    NctiDocument* pDoc                = m_mainWindow->getCurrentViewDocment();
    NctiDocViewManager* pDocView      = NctiDocViewManager::GetDocViewManager(pDoc->GetBaseModel());
    NctiDisplayDocElement* pActiveDoc = pDocView->GetActiveDocElement();
    NctiDisplayDocCustomContainer* pDisplayDocCustomContainer = nullptr;
    pDisplayDocCustomContainer = (NctiDisplayDocCustomContainer*)pActiveDoc->GetFirstDescendant();
    const char* strMeshType    = pDisplayDocCustomContainer->GetMeshDocType();
    QString qType              = QString::fromUtf8(strMeshType);
    if (qType == "ncti_doc_gmsh_type") {
        m_meshType = 1;
	}
	if (qType == "ncti_doc_meshgems_type") {
		m_meshType = 2;
	}
    return m_meshType;
}

void SimulationController::onMeshAddForce()
{
    NctiDocument* i_pDocument = NctiQTPubFun::GetCurrentViewDocment(m_mainWindow->getWindowPlatform());
    if (!i_pDocument) {
        return;
    }

    MeshAddForceView* view = new MeshAddForceView(
        i_pDocument, m_mainWindow->getUserInteractionMgr()->getScriptExecutor(), m_mainWindow);
    view->setAttribute(Qt::WA_DeleteOnClose);
    view->show();
}

void SimulationController::onMeshAddSpc()
{
    NctiDocument* i_pDocument = NctiQTPubFun::GetCurrentViewDocment(m_mainWindow->getWindowPlatform());
    if (!i_pDocument) {
        return;
    }

    MeshAddSpcView* view = new MeshAddSpcView(
        i_pDocument, m_mainWindow->getUserInteractionMgr()->getScriptExecutor(), m_mainWindow);
    view->setAttribute(Qt::WA_DeleteOnClose);
    view->show();
}

void SimulationController::onMeshAddMat()
{
    NctiDocument* i_pDocument = NctiQTPubFun::GetCurrentViewDocment(m_mainWindow->getWindowPlatform());
    if (!i_pDocument) {
        return;
    }

    MeshAddMatView* view = new MeshAddMatView(
        i_pDocument, m_mainWindow->getUserInteractionMgr()->getScriptExecutor(), m_mainWindow);
    view->setAttribute(Qt::WA_DeleteOnClose);
    view->show();
}

void SimulationController::onMeshFromSurface()
{
    NctiDocument* i_pDocument = NctiQTPubFun::GetCurrentViewDocment(m_mainWindow->getWindowPlatform());
    if (!i_pDocument) {
        return;
    }

    static Ncti_Mesh_Option s_option;
    int m_meshType        = getMeshType();
    MeshSettingView* view = new MeshSettingView(s_option, i_pDocument, m_mainWindow, true, m_meshType);
    view->setAttribute(Qt::WA_DeleteOnClose);
    view->show();
    connect(view, &NctiBaseDialog::finish, [this, i_pDocument, view]() {
        NctiCommandManager* pComMgr = NctiCommandManager::GetCommandManager(i_pDocument->GetBaseModel());
        if (!pComMgr) {
            return;
        }
        m_mainWindow->getObjectTreeMgr()->SetUIWait(true);

        LoadingSpinnerWidget::showLoading(m_mainWindow, [=, this]() {
            NctiArgumentObject pArgumentObject;
            pArgumentObject.SetDisplayObjectVec(view->getObjects());
            pArgumentObject.SetmeshOption(view->getMeshOption());
            s_option = view->getMeshOption();
            EnumNctiResult result = pComMgr->RunCommand("cmd_ncti_create_surface_mesh", &pArgumentObject);
            if (result == EnumNctiResult::NCTI_SUCCEEDED) {
                //NctiPrintf("onMeshFromSurface: run cmd_ncti_create_surface_mesh Success");
            }
            m_mainWindow->getObjectTreeMgr()->SetUIWait(false);
            m_mainWindow->getObjectTreeMgr()->SetTreeIsModify(true);
            //UI 操作必须保证在主线程执行
            QMetaObject::invokeMethod(
                m_mainWindow, [this]() { m_mainWindow->getObjectTreeMgr()->UpdateTree(); }, Qt::QueuedConnection);
        });
    });
}

void SimulationController::onMeshFromVolume()
{
    NctiDocument* i_pDocument = NctiQTPubFun::GetCurrentViewDocment(m_mainWindow->getWindowPlatform());
    if (!i_pDocument) {
        return;
    }

    static Ncti_Mesh_Option s_option;
    int m_meshType        = getMeshType();
    MeshSettingView* view = new MeshSettingView(s_option, i_pDocument, m_mainWindow, true, m_meshType);
    view->setAttribute(Qt::WA_DeleteOnClose);
    view->show();
    connect(view, &NctiBaseDialog::finish, [this, i_pDocument, view]() {
        NctiCommandManager* pComMgr = NctiCommandManager::GetCommandManager(i_pDocument->GetBaseModel());
        if (pComMgr) {
            m_mainWindow->getObjectTreeMgr()->SetUIWait(true);
            LoadingSpinnerWidget::showLoading(m_mainWindow, [=, this]() {
                NctiArgumentObject pArgumentObject;
                pArgumentObject.SetDisplayObjectVec(view->getObjects());
                pArgumentObject.SetmeshOption(view->getMeshOption());
                s_option              = view->getMeshOption();
                EnumNctiResult result = pComMgr->RunCommand("cmd_ncti_create_volume_mesh", &pArgumentObject);
                if (result == EnumNctiResult::NCTI_SUCCEEDED) {
                    //qDebug() << "onMeshFromVolume: run cmd_ncti_create_volume_mesh Success";
                }
                m_mainWindow->getObjectTreeMgr()->SetUIWait(false);
                m_mainWindow->getObjectTreeMgr()->SetTreeIsModify(true);
                //UI 操作必须保证在主线程执行
                QMetaObject::invokeMethod(
                    m_mainWindow, [this]() { m_mainWindow->getObjectTreeMgr()->UpdateTree(); }, Qt::QueuedConnection);
            });
        }
    });
}

void SimulationController::onMeshShowMeshQuality()
{
    NctiDocument* i_pDocument = NctiQTPubFun::GetCurrentViewDocment(m_mainWindow->getWindowPlatform());
    if (!i_pDocument) {
        return;
    }

    static Ncti_Mesh_Option s_option;
    MeshQualitySettingView* view = new MeshQualitySettingView(i_pDocument, m_mainWindow, true);
    view->setAttribute(Qt::WA_DeleteOnClose);
    view->show();
    connect(view, &NctiBaseDialog::finish, [this, i_pDocument, view]() {
        NctiDisplayObject* obj = view->getObject();
        if (obj->IsTypeName(NctiDisplayGridMesh::ID)) {
            NctiDisplayGridMesh* pSurfaceMesh = (NctiDisplayGridMesh*)obj;
            int nMode = view->getMode();
            std::vector<Ncti_UInteger> allElements;
            std::vector<double> dValueVec;
            pSurfaceMesh->GetGeomtry()->HoldGridColor();
            auto body = pSurfaceMesh->GetMeshBody();
            NctiDisplayGridMeshPub(body).GetMeshValue(nMode, allElements, dValueVec);
            NctiDisplayGridMeshPub(body).ShowMeshClassifyColor(allElements, dValueVec);
            std::vector<std::string> textShowList = NctiDisplayGridMeshPub(body).GetMeshShowText(nMode, allElements);
            std::function<void()> funcPtr         = std::bind(&NctiRenderUnstructureItem::RestorGridColor, pSurfaceMesh->GetGeomtry());
            NctiQTPubFun::ShowMeshQualistyDlg(nMode, textShowList, dValueVec, funcPtr, m_mainWindow);
        }
    });
}

void SimulationController::onSelectMode(const QString& objectName)
{
    auto gridRadioBtns = m_mainWindow->getUIOptionMgr()->getGridRadioButtons();

    if (!gridRadioBtns[objectName]->isChecked())
        return;
    
    auto doc = NctiQTPubFun::GetCurrentViewDocment(m_mainWindow->getWindowPlatform());
    if (!doc)
        return;
    
    if (objectName == "grid_geo") {
        NctiDocElementPubFun::SetSelectTool(doc, NctiSelectType::ELEM_Entity);
    }
    else if (objectName == "grid_node") {
        NctiDocElementPubFun::SetSelectTool(doc, NctiSelectType::ELEM_Vertex);
    }
    else if (objectName == "grid_unit") {
        NctiDocElementPubFun::SetSelectTool(doc, NctiSelectType::ELEM_Cell);
    }
    else if (objectName == "grid_unit_face") {
        NctiDocElementPubFun::SetSelectTool(doc, NctiSelectType::ELEM_Face);
    }
    else if (objectName == "grid_unit_edge") {
        NctiDocElementPubFun::SetSelectTool(doc, NctiSelectType::ELEM_Edge);
    }
}

void SimulationController::onQuickSelect()
{
    NctiDocument* i_pDocument = NctiQTPubFun::GetCurrentViewDocment(m_mainWindow->getWindowPlatform());
    if (!i_pDocument) {
        return;
    }

    MeshQuickSelect* dlg = new MeshQuickSelect(
        i_pDocument, m_mainWindow->getUserInteractionMgr()->getScriptExecutor(), m_mainWindow);
    dlg->setAttribute(Qt::WA_DeleteOnClose);
    dlg->show();
}

void SimulationController::onModifyMeshType()
{
	NctiDocument* i_pDocument = NctiQTPubFun::GetCurrentViewDocment(m_mainWindow->getWindowPlatform());
	if (!i_pDocument) {
		return;
	}

    MeshModifyMeshTypeView* dlg = new MeshModifyMeshTypeView(
		i_pDocument, m_mainWindow);
	dlg->setAttribute(Qt::WA_DeleteOnClose);
	dlg->show();
}

} // namespace NCTI