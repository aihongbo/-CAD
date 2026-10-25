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

#include "GeometryBuilder.h"

#include "NctiQTPubFun.h"
#include "NctiDocument.h"
#include "NctiDocElementPubFun.h"
#include "NctiDisplayDocElement.h"
#include "NctiArgumentObject.h"
#include "NctiCommandManager.h"
#include "NctiString.h"
#include "NctiDeleteTool.h"

#include "CreateCuboidWgt.h"
#include "CreateCylinderWgt.h"
#include "CreateBooleanWgt.h"
#include "CreateFilletWgt.h"
#include "CreateChamferWgt.h"
#include "CreateGeoPanWgt.h"
#include "RemoveFeatureWgt.h"
#include "CreateFillLoopWgt.h"
#include "CreateGeoZoomWgt.h"
#include "CreateGeoRotateWgt.h"
#include "CreateLinearArrayWgt.h"
#include "CreateGeoRotateArrayWgt.h"
#include "CreateCurveArrayWgt.h"
#include "CreateCurveOffsetWgt.h"

#include "LoadingSpinnerWidget.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QUuid>
namespace NCTI {

GeometryBuilder::GeometryBuilder(MainWindow* mainWindow)
    : MainWindowModule(mainWindow)
{
}

void GeometryBuilder::initialize()
{
    connect(m_mainWindow->Signals(), &MainWindowSignals::executeBox, this, &GeometryBuilder::onExecuteBox);
    connect(m_mainWindow->Signals(), &MainWindowSignals::executeCylinder, this, &GeometryBuilder::onExecuteCylinder);
    connect(m_mainWindow->Signals(), &MainWindowSignals::executeBoolean, this, &GeometryBuilder::onExecuteBoolean);
    connect(m_mainWindow->Signals(), &MainWindowSignals::executeFillet, this, &GeometryBuilder::onExecuteFillet);
    connect(m_mainWindow->Signals(), &MainWindowSignals::executeChamfer, this, &GeometryBuilder::onExecuteChamfer);
    connect(m_mainWindow->Signals(), &MainWindowSignals::geoPan, this, &GeometryBuilder::onGeoPan);
    connect(m_mainWindow->Signals(), &MainWindowSignals::geoZoom, this, &GeometryBuilder::onGeoZoom);
    connect(m_mainWindow->Signals(), &MainWindowSignals::geoRotate, this, &GeometryBuilder::onGeoRotate);
    connect(m_mainWindow->Signals(), &MainWindowSignals::removeFeature, this, &GeometryBuilder::onRemoveFeature);
    connect(m_mainWindow->Signals(), &MainWindowSignals::removeFace, this, &GeometryBuilder::onRemoveFace);
    connect(m_mainWindow->Signals(), &MainWindowSignals::executeExtractSubObj, this, &GeometryBuilder::onExecuteExtractSubObj);
    connect(m_mainWindow->Signals(), &MainWindowSignals::executeFillLoop, this, &GeometryBuilder::onExecuteFillLoop);
    connect(m_mainWindow->Signals(), &MainWindowSignals::executeCompound, this, &GeometryBuilder::onExecuteCompound);
    connect(m_mainWindow->Signals(), &MainWindowSignals::executeExplodeBody, this, &GeometryBuilder::onExecuteExplodeBody);
    connect(m_mainWindow->Signals(), &MainWindowSignals::executeSewing, this, &GeometryBuilder::onExecuteSewing);
    connect(m_mainWindow->Signals(), &MainWindowSignals::executeSeparatFace, this, &GeometryBuilder::onExecuteSeparatFace);
    connect(m_mainWindow->Signals(), &MainWindowSignals::createExtendFace, this, &GeometryBuilder::onCreateExtendFace);
    connect(m_mainWindow->Signals(), &MainWindowSignals::linearArray, this, &GeometryBuilder::onLinearArray);
    connect(m_mainWindow->Signals(), &MainWindowSignals::rotateArray, this, &GeometryBuilder::onRotateArray);
    connect(m_mainWindow->Signals(), &MainWindowSignals::curveArray, this, &GeometryBuilder::onCurveArray);
    connect(m_mainWindow->Signals(), &MainWindowSignals::curveOffset, this, &GeometryBuilder::onCurveOffset);
}

void GeometryBuilder::onExecuteBox()
{
    NctiDocument* i_pDocument = NctiQTPubFun::GetCurrentViewDocment(m_mainWindow->getWindowPlatform());
    if (!i_pDocument) {
        return;
    }

    if (NctiDocElementPubFun::IsHaveRunCommand(i_pDocument))
        return;
    if (m_mainWindow->activeDoc(i_pDocument->GetBaseModel()) == nullptr) {
        QMessageBox::warning(m_mainWindow, "Command", "Command execution failure");
        return;
    }
   
    CreateCuboidWgt* dlg = new CreateCuboidWgt(i_pDocument, m_mainWindow);
    CreateCuboidWgt::SetInstance(dlg);
    dlg->setAttribute(Qt::WA_DeleteOnClose);
    dlg->show();
}

void GeometryBuilder::onExecuteCylinder()
{
    NctiDocument* i_pDocument = NctiQTPubFun::GetCurrentViewDocment(m_mainWindow->getWindowPlatform());
    if (!i_pDocument) {
        return;
    }
    if (m_mainWindow->activeDoc(i_pDocument->GetBaseModel()) == nullptr) {
        QMessageBox::warning(m_mainWindow, "Command", "Command execution failure");
        return;
    }
    CreateCylinderWgt* dlg = new CreateCylinderWgt(i_pDocument, m_mainWindow);
    dlg->setAttribute(Qt::WA_DeleteOnClose);
    dlg->show();
}

void GeometryBuilder::onExecuteBoolean()
{
    NctiDocument* i_pDocument = NctiQTPubFun::GetCurrentViewDocment(m_mainWindow->getWindowPlatform());
    if (!i_pDocument) {
        return;
    }

    if (NctiDocElementPubFun::IsHaveRunCommand(i_pDocument))
        return;
    if (m_mainWindow->activeDoc(i_pDocument->GetBaseModel()) == nullptr) {
        QMessageBox::warning(m_mainWindow, "Command", "Command execution failure");
        return;
    }
    CreateBooleanWgt* dlg = new CreateBooleanWgt(i_pDocument, m_mainWindow);
    dlg->show();
}

void GeometryBuilder::onExecuteFillet()
{
    NctiDocument* i_pDocument = NctiQTPubFun::GetCurrentViewDocment(m_mainWindow->getWindowPlatform());
    if (!i_pDocument) {
        return;
    }
    if (m_mainWindow->activeDoc(i_pDocument->GetBaseModel()) == nullptr) {
        QMessageBox::warning(m_mainWindow, "Command", "Command execution failure");
        return;
    }

    CreateFilletWgt* fillWgt = new CreateFilletWgt(i_pDocument, m_mainWindow);
    fillWgt->show();
}

void GeometryBuilder::onExecuteChamfer()
{
    NctiDocument* i_pDocument = NctiQTPubFun::GetCurrentViewDocment(m_mainWindow->getWindowPlatform());
    if (!i_pDocument) {
        return;
    }
    if (m_mainWindow->activeDoc(i_pDocument->GetBaseModel()) == nullptr) {
        QMessageBox::warning(m_mainWindow, "Command", "Command execution failure");
        return;
    }

    CreateChamferWgt* chamferWgt = new CreateChamferWgt(i_pDocument, m_mainWindow);
    chamferWgt->show();
}

void GeometryBuilder::onGeoPan()
{
    NctiDocument* i_pDocument = NctiQTPubFun::GetCurrentViewDocment(m_mainWindow->getWindowPlatform());
    if (!i_pDocument) {
        return;
    }
    if (m_mainWindow->activeDoc(i_pDocument->GetBaseModel()) == nullptr) {
        QMessageBox::warning(m_mainWindow, "Command", "Command execution failure");
        return;
    }

    CreateGeoPanWgt* dlg = new CreateGeoPanWgt(i_pDocument, m_mainWindow);
    CreateGeoPanWgt::SetInstance(dlg);
    dlg->show();
}

void GeometryBuilder::onGeoZoom()
{
    NctiDocument* i_pDocument = NctiQTPubFun::GetCurrentViewDocment(m_mainWindow->getWindowPlatform());
    if (!i_pDocument) {
        return;
    }
    if (m_mainWindow->activeDoc(i_pDocument->GetBaseModel()) == nullptr) {
        QMessageBox::warning(m_mainWindow, "Command", "Command execution failure");
        return;
    }

    CreateGeoZoomWgt* dlg = new CreateGeoZoomWgt(i_pDocument, m_mainWindow);
    CreateGeoZoomWgt::SetInstance(dlg);
    dlg->show();
}

void GeometryBuilder::onGeoRotate()
{
    NctiDocument* i_pDocument = NctiQTPubFun::GetCurrentViewDocment(m_mainWindow->getWindowPlatform());
    if (!i_pDocument) {
        return;
    }
    if (m_mainWindow->activeDoc(i_pDocument->GetBaseModel()) == nullptr) {
        QMessageBox::warning(m_mainWindow, "Command", "Command execution failure");
        return;
    }

    CreateGeoRotateWgt* dlg = new CreateGeoRotateWgt(i_pDocument, m_mainWindow);
    CreateGeoRotateWgt::SetInstance(dlg);
    dlg->show();
}

void GeometryBuilder::onRemoveFeature()
{
    NctiDocument* i_pDocument = NctiQTPubFun::GetCurrentViewDocment(m_mainWindow->getWindowPlatform());
    if (!i_pDocument) {
        return;
    }

    LoadingSpinnerWidget::showLoading(m_mainWindow,
                                      [=]() { NctiDeleteTool::RemoveFeature(i_pDocument->GetBaseModel()); });
}

void GeometryBuilder::onRemoveFace()
{
    NctiDocument* i_pDocument = NctiQTPubFun::GetCurrentViewDocment(m_mainWindow->getWindowPlatform());
    if (!i_pDocument) {
        return;
    }
    NctiQTPubFun::ShowRemoveFacesDlg(i_pDocument, m_mainWindow);
}

void GeometryBuilder::onExecuteExtractSubObj()
{
    NctiDocument* i_pDocument = NctiQTPubFun::GetCurrentViewDocment(m_mainWindow->getWindowPlatform());
    if (!i_pDocument) {
        return;
    }
    NctiDocElementPubFun::ExtractSubobject(i_pDocument);
}

void GeometryBuilder::onExecuteFillLoop()
{
    NctiDocument* i_pDocument = NctiQTPubFun::GetCurrentViewDocment(m_mainWindow->getWindowPlatform());
    if (!i_pDocument) {
        return;
    }

    CreateFillLoopWgt* dlg = new CreateFillLoopWgt(i_pDocument, m_mainWindow);
    dlg->show();
}

void GeometryBuilder::onExecuteCompound()
{
    onExecuteModeling("cmd_ncti_create_compound");
}

void GeometryBuilder::onExecuteExplodeBody()
{
    onExecuteModeling("cmd_ncti_explode_body");
}

void GeometryBuilder::onExecuteSewing()
{
    onExecuteModeling("cmd_ncti_sewing_bodies");
}

void GeometryBuilder::onExecuteSeparatFace()
{
    NctiDocument* i_pDocument = NctiQTPubFun::GetCurrentViewDocment(m_mainWindow->getWindowPlatform());
    if (!i_pDocument) {
        return;
    }

    RemoveFeatureWgt* dlg = new RemoveFeatureWgt(i_pDocument, 2, 2, m_mainWindow);
    dlg->show();
}

void GeometryBuilder::onCreateExtendFace()
{
    NctiDocument* i_pDocument = NctiQTPubFun::GetCurrentViewDocment(m_mainWindow->getWindowPlatform());
    if (!i_pDocument) {
        return;
    }

    NctiQTPubFun::ShowExtendFace(i_pDocument, m_mainWindow);
}

void GeometryBuilder::onLinearArray()
{
    NctiDocument* i_pDocument = NctiQTPubFun::GetCurrentViewDocment(m_mainWindow->getWindowPlatform());
    if (!i_pDocument) {
        return;
    }
    if (m_mainWindow->activeDoc(i_pDocument->GetBaseModel()) == nullptr) {
        QMessageBox::warning(m_mainWindow, "Command", "Command execution failure");
        return;
    }

    CreateLinearArrayWgt* dlg = new CreateLinearArrayWgt(i_pDocument, m_mainWindow);
    CreateLinearArrayWgt::SetInstance(dlg);
    dlg->show();
}

void GeometryBuilder::onRotateArray()
{
    NctiDocument* i_pDocument = NctiQTPubFun::GetCurrentViewDocment(m_mainWindow->getWindowPlatform());
    if (!i_pDocument) {
        return;
    }
    if (m_mainWindow->activeDoc(i_pDocument->GetBaseModel()) == nullptr) {
        QMessageBox::warning(m_mainWindow, "Command", "Command execution failure");
        return;
    }

    CreateGeoRotateArrayWgt* dlg = new CreateGeoRotateArrayWgt(i_pDocument, m_mainWindow);
    CreateGeoRotateArrayWgt::SetInstance(dlg);
    dlg->show();
}

void GeometryBuilder::onCurveArray()
{
    NctiDocument* i_pDocument = NctiQTPubFun::GetCurrentViewDocment(m_mainWindow->getWindowPlatform());
    if (!i_pDocument) {
        return;
    }
    if (m_mainWindow->activeDoc(i_pDocument->GetBaseModel()) == nullptr) {
        QMessageBox::warning(m_mainWindow, "Command", "Command execution failure");
        return;
    }

    CreateCurveArrayWgt* dlg = new CreateCurveArrayWgt(i_pDocument, m_mainWindow);
    dlg->show();
}

void GeometryBuilder::onCurveOffset()
{
    NctiDocument* i_pDocument = NctiQTPubFun::GetCurrentViewDocment(m_mainWindow->getWindowPlatform());
    if (!i_pDocument) {
        return;
    }
    if (m_mainWindow->activeDoc(i_pDocument->GetBaseModel()) == nullptr) {
        QMessageBox::warning(m_mainWindow, "Command", "Command execution failure");
        return;
    }

    CreateCurveOffsetWgt* dlg = new CreateCurveOffsetWgt(i_pDocument, m_mainWindow);
    CreateCurveOffsetWgt::SetInstance(dlg);
    dlg->show();
}

void GeometryBuilder::onExecuteModeling(const char* command)
{
    NctiDocument* i_pDocument = NctiQTPubFun::GetCurrentViewDocment(m_mainWindow->getWindowPlatform());
    if (!i_pDocument) {
        return;
    }

    std::vector<NctiDisplayObject*> objectVec;

    const char* cExplode = "cmd_ncti_explode_body";
    NctiDocElementPubFun::GetDisplayObjectFromSelManager(i_pDocument, objectVec);
    if ((!NctiString::same(command, cExplode) && objectVec.size() < 2)
        || (NctiString::same(command, cExplode) && objectVec.size() != 1)) {
        return;
    }

    NctiBaseModel* pBaseModel = i_pDocument->GetBaseModel();
    if (pBaseModel == nullptr)
        return;

    NctiCommandManager* pComMan = NctiCommandManager::GetCommandManager(pBaseModel);
    if (pComMan) {
        NctiArgumentObject argumentObject;
        NctiString::same(command, cExplode) ? argumentObject.SetDisplayObject1(objectVec[0])
                                            : argumentObject.SetDisplayObjectVec(objectVec);
        /*EnumNctiResult result = */ pComMan->RunCommand(command, &argumentObject);
    }
}

void GeometryBuilder::onExecuteUnitExport()
{
    NctiDocument* i_pDocment = NctiQTPubFun::GetCurrentViewDocment(m_mainWindow->getWindowPlatform());
    if (i_pDocment == nullptr)
        return;
    NctiCommandManager* pCmdMgr = NctiCommandManager::GetCommandManager(i_pDocment->GetBaseModel());
    if (pCmdMgr == nullptr)
        return;
    NctiBaseModel* pBaseModel = i_pDocment->GetBaseModel();
    if (pBaseModel == nullptr)
        return;

    if (m_mainWindow->activeDoc(i_pDocment->GetBaseModel()) == nullptr) {
        QMessageBox::warning(m_mainWindow, "Command", "Command execution failure");
        return;
    }

    std::vector<NctiDisplayObject*> objVec;
    std::vector<std::vector<NCTI_MODEL_TAG>> vCellVecVec;
    NctiDocElementPubFun::GetDisplayObjectFromSelManager(i_pDocment, objVec, vCellVecVec);
    if (objVec.empty()) {
        QMessageBox::warning(m_mainWindow, "Command", "No entity selected");
        return;
    }

    QString filePath = QFileDialog::getSaveFileName(
        nullptr, 
        QStringLiteral("选择导出路径"), 
        "", 
        tr("Save File(*.stp)"));

    if (filePath.isEmpty()) {
        return;
    }

    QString unitName1 = QUuid::createUuid().toString();
    NctiArgumentObject pArgumentObject;
    pArgumentObject.SetDisplayObjectVec(objVec);
    pArgumentObject.SetChar(unitName1.toStdString().c_str());

    EnumNctiResult result = pCmdMgr->RunCommand("cmd_ncti_multi_boolean_unit", &pArgumentObject);
    if (result != EnumNctiResult::NCTI_SUCCEEDED) {
        QMessageBox::warning(m_mainWindow, "Command", "cmd_ncti_multi_boolean_unit failure");
        return;
    }

    QString unitName2 = QUuid::createUuid().toString();
    NctiArgumentObject pArgumentObject2;
    pArgumentObject2.SetFilePath(unitName1.toStdString().c_str());
    pArgumentObject2.SetChar(unitName2.toStdString().c_str());
    result = pCmdMgr->RunCommand("cmd_ncti_simplify_topo", &pArgumentObject2);
    if (result != EnumNctiResult::NCTI_SUCCEEDED) {
        QMessageBox::warning(m_mainWindow, "Command", "cmd_ncti_simplify_topo failure");
        return;
    }

    NctiArgumentObject pArgumentObject3;
    pArgumentObject3.SetFilePath(filePath.toStdString().c_str());
    std::vector<std::string> i_ListVec;
    i_ListVec.push_back(unitName2.toStdString());
    pArgumentObject3.SetCommandArgumentVec(i_ListVec);
    pArgumentObject3.SetIntValue(1);
    result = pCmdMgr->RunCommand("cmd_ncti_export_file", &pArgumentObject3);
    if (result != EnumNctiResult::NCTI_SUCCEEDED) {
        QMessageBox::warning(m_mainWindow, "Command", "cmd_ncti_export_file failure");
        return;
    }

    std::vector<NctiDisplayObject*> pObjList;
    NctiDisplayObject* pObj1 = nullptr;
    NctiDocElementPubFun::GetObjectListByName(pBaseModel, unitName1.toStdString().c_str(), pObj1);
    NctiDisplayObject* pObj2 = nullptr;
    NctiDocElementPubFun::GetObjectListByName(pBaseModel, unitName2.toStdString().c_str(), pObj2);

    if (pObj1)
        pObjList.push_back(pObj1);
    if (pObj2)
        pObjList.push_back(pObj2);
    NctiArgumentObject argumentObject;
    argumentObject.SetDisplayObjectVec(pObjList);
    pCmdMgr->RunCommand("cmd_ncti_delete", &argumentObject);

    QMessageBox::information(m_mainWindow, "Command", "export success");
}


} // namespace NCTI