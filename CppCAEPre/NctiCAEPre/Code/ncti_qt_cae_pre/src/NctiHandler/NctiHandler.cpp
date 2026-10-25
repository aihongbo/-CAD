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

#include "NctiHandler.h"

#ifndef __GNUC__
#include <Windows.h>
#endif
#include <QDebug>

#include "NctiQTPubFun.h"
#include "NctiDocument.h"
#include "NctiDocElementPubFun.h"
#include "NctiCommandManager.h"
#include "NctiDocViewManager.h"
#include "NctiArgumentObject.h"

//sketch
#include "NctiDisplayDocSketch.h"
#include "NctiFile.h"
#include "NctiString.h"
#include "NctiPythonTool.h"
#include "NctiExecuteDCM3CommandTool.h"

#include "NctSketchConstrDlg.h"
#include "NctiLogicalConstrWidget.h"
#include "NctiDimensionConstrWidget.h"
#include "NctiFixConstrWidget.h"
namespace NCTI {

// 草图执行命令函数
static Ncti_Boolean ExecuteSketchCommand(NctiWindowPlatform* i_pPlatform, const char* commandId)
{
    NctiDocument* pDocument = NctiQTPubFun::GetCurrentViewDocment(i_pPlatform);
    if (!pDocument) { return false; }

    NctiCommandManager* pComMan  = NctiCommandManager::GetCommandManager(pDocument->GetBaseModel());
    NctiTypeCommandStatus status = pComMan->QuerryCommandStatus(commandId);
    if (status & NCTI_COMMAND_STATUS_EXECUTABLE) {
        EnumNctiResult res = pComMan->RunCommand(commandId);
        if (res == NCTI_SUCCEEDED) return true;
    }
    return false;
}

// 草图选择对象执行命令函数
static Ncti_Boolean ExecuteSketchObjectCommand(NctiWindowPlatform* i_pPlatform, const char* commandId)
{
    NctiDocument* pDocument = NctiQTPubFun::GetCurrentViewDocment(i_pPlatform);
    if (!pDocument) { return false; }

    NctiCommandManager* pComMan = NctiCommandManager::GetCommandManager(pDocument->GetBaseModel());
    std::vector<NctiDisplayObject*> ObjVec;
    std::vector<NCTI_MODEL_TAG> CellVec;
    NctiDocElementPubFun::GetDisplayObjectFromSelManager(pDocument, ObjVec, CellVec);
    if (ObjVec.size() == 1) {
        NctiArgumentObject argument;
        argument.SetDisplayObject1(ObjVec[0]);
        EnumNctiResult res = pComMan->RunCommand(commandId, &argument);
        if (res == NCTI_SUCCEEDED) return true;
    }
    return false;
}

void NctiHandler::StartRecord()
{
    char NewCh[256];
    NctiString::LocaleSprintf(NewCh, "doc.StartRecord()");
    NctiPythonTool::RunPythonString(NewCh);
}

void NctiHandler::EndRecord(const QString& filePath)
{
    char NewCh[256];
    if (filePath.isEmpty()) { NctiString::LocaleSprintf(NewCh, "doc.EndRecord()"); }
    else {
        auto&& bytes = filePath.toUtf8();
        NctiString::LocaleSprintf(NewCh, "doc.EndRecord(\"%s\")", bytes.constData());
    }
    NctiPythonTool::RunPythonString(NewCh);
}

void NctiHandler::AiRecognition(NctiWindowPlatform* i_pPlatform)
{
    NctiDocument* pDocument = NctiQTPubFun::GetCurrentViewDocment(i_pPlatform);
    if (pDocument) { NctiQTPubFun::FeatureRecognition(i_pPlatform); }
}

void NctiHandler::HoleRecognition(NctiWindowPlatform* i_pPlatform)
{
    NctiDocument* pDocument = NctiQTPubFun::GetCurrentViewDocment(i_pPlatform);
    if (pDocument) { NctiQTPubFun::HoleRecognition(i_pPlatform); }
}

void NctiHandler::SelFeatureFace(NctiWindowPlatform* i_pPlatform)
{
    NctiDocument* pDocument = NctiQTPubFun::GetCurrentViewDocment(i_pPlatform);
    if (pDocument) {
        //TODO
    }
}

void NctiHandler::ExportLinkFace(NctiWindowPlatform* i_pPlatform, const QString& i_filePath)
{
    NctiDocument* pDocument = NctiQTPubFun::GetCurrentViewDocment(i_pPlatform);
    if (pDocument) { NctiQTPubFun::ExportLinkFace(i_pPlatform, i_filePath); }
}

void NctiHandler::TopoStructureDisplay(NctiWindowPlatform* i_pPlatform)
{
    NctiDocument* pDocument = NctiQTPubFun::GetCurrentViewDocment(i_pPlatform);
    if (!pDocument) { return; }

    std::vector<std::string> o_ObjNameVec;
    std::vector<Ncti_Long> o_CellIDVec;
    std::vector<NctiTopoCell*> o_GECellVec;
    NctiDocElementPubFun::GetNameFromSelManager(pDocument, o_ObjNameVec, o_CellIDVec, o_GECellVec);

    char chpy[2048];
    if (o_ObjNameVec.size() == 0) {
        NctiString::LocaleSprintf(chpy, "doc.RunCommand(\"cmd_ncti_ai_attr_topo_display\")");
    }
    else {
        NctiString::LocaleSprintf(
            chpy, "doc.RunCommand(\"cmd_ncti_ai_attr_topo_display\", \"%s\", ai)", o_ObjNameVec[0].c_str());
    }
    NctiPythonTool::RunPythonString(chpy);
}

void NctiHandler::UVGridDisplay(NctiWindowPlatform* i_pPlatform)
{
    NctiDocument* pDocument = NctiQTPubFun::GetCurrentViewDocment(i_pPlatform);
    if (!pDocument) { return; }

    std::vector<std::string> o_ObjNameVec;
    std::vector<Ncti_Long> o_CellIDVec;
    std::vector<NctiTopoCell*> o_GECellVec;
    NctiDocElementPubFun::GetNameFromSelManager(pDocument, o_ObjNameVec, o_CellIDVec, o_GECellVec);

    char chpy[2048];
    if (o_ObjNameVec.size() == 0) {
        NctiString::LocaleSprintf(chpy, "doc.RunCommand(\"cmd_ncti_ai_uv_point_display\")");
    }
    else {
        NctiString::LocaleSprintf(
            chpy, "doc.RunCommand(\"cmd_ncti_ai_uv_point_display\", \"%s\", ai)", o_ObjNameVec[0].c_str());
    }
    NctiPythonTool::RunPythonString(chpy);
}

#pragma region 草图
Ncti_Boolean NctiHandler::SketchNew(NctiWindowPlatform* i_pPlatform)
{
    return ExecuteSketchCommand(i_pPlatform, _NctiCommandCreateDocSketch_ID_);
}

Ncti_Boolean NctiHandler::SketchDelete(NctiWindowPlatform* i_pPlatform)
{
    return ExecuteSketchCommand(i_pPlatform, _NctiCommandDeleteDocSketch_ID_);
}

Ncti_Boolean NctiHandler::SketchCoord(NctiWindowPlatform* i_pPlatform)
{
    return ExecuteSketchCommand(i_pPlatform, _NctiCommandWorkPlane_ID_);
}

Ncti_Boolean NctiHandler::SketchRectangle(NctiWindowPlatform* i_pPlatform)
{
    return ExecuteSketchCommand(i_pPlatform, _NctiCommandCreateSketchRect_ID_);
}

Ncti_Boolean NctiHandler::SketchCircle(NctiWindowPlatform* i_pPlatform)
{
    return ExecuteSketchCommand(i_pPlatform, _NctiCommandCreateSketchCircle_ID_);
}

Ncti_Boolean NctiHandler::SketchPolygon(NctiWindowPlatform* i_pPlatform)
{
    return ExecuteSketchCommand(i_pPlatform, _NctiCommandCreateSketchPolygon_ID_);
}

Ncti_Boolean NctiHandler::SketchEllipse(NctiWindowPlatform* i_pPlatform)
{
    return ExecuteSketchCommand(i_pPlatform, _NctiCommandCreateSketchEllipse_ID_);
}

Ncti_Boolean NctiHandler::SketchCircleToCircle(NctiWindowPlatform* i_pPlatform)
{
    return ExecuteSketchCommand(i_pPlatform, _NctiCommandCreateSketchTan2Circles_ID_);
}

Ncti_Boolean NctiHandler::SketchLine(NctiWindowPlatform* i_pPlatform)
{
    return ExecuteSketchCommand(i_pPlatform, _NctiCommandCreateSketchLine_ID_);
}

Ncti_Boolean NctiHandler::SketchArc(NctiWindowPlatform* i_pPlatform)
{
    return ExecuteSketchCommand(i_pPlatform, _NctiCommandCreateSketchArc_ID_);
}

Ncti_Boolean NctiHandler::SketchWire(NctiWindowPlatform* i_pPlatform)
{
    return ExecuteSketchCommand(i_pPlatform, _NctiCommandCreateSketchPolyline_ID_);
}

Ncti_Boolean NctiHandler::SketchBspline(NctiWindowPlatform* i_pPlatform)
{
    return ExecuteSketchCommand(i_pPlatform, _NctiCommandCreateSketchSpline_ID_);
}

Ncti_Boolean NctiHandler::SketchCenterline(NctiWindowPlatform* i_pPlatform)
{
    return ExecuteSketchCommand(i_pPlatform, _NctiCommandCreateSketchCenterLine_ID_);
}

Ncti_Boolean NctiHandler::SketchPoint(NctiWindowPlatform* i_pPlatform)
{
    return ExecuteSketchCommand(i_pPlatform, _NctiCommandCreateSketchDot_ID_);
}

Ncti_Boolean NctiHandler::SketchResetView(NctiWindowPlatform* i_pPlatform)
{
    NctiDocument* pDocument = NctiQTPubFun::GetCurrentViewDocment(i_pPlatform);
    if (!pDocument) { return false; }

    //TODO
    return true;
}

Ncti_Boolean NctiHandler::SketchExit(NctiWindowPlatform* i_pPlatform)
{
    NctiDocument* pDocument = NctiQTPubFun::GetCurrentViewDocment(i_pPlatform);
    if (!pDocument) { return false; }

    NctiDocViewManager* pDocView = NctiDocViewManager::GetDocViewManager(pDocument->GetBaseModel());
    if (!pDocView) { return false; }

    NctiCommandManager* pComMan = NctiCommandManager::GetCommandManager(pDocView);
    if (!pComMan) { return false; }

    pComMan->ExitCommand();
    return true;
}

Ncti_Boolean NctiHandler::SketchPrism(NctiWindowPlatform* i_pPlatform)
{
    return ExecuteSketchObjectCommand(i_pPlatform, _NctiCommandExtrude_ID_);
}

Ncti_Boolean NctiHandler::SketchRotate(NctiWindowPlatform* i_pPlatform)
{
    return ExecuteSketchObjectCommand(i_pPlatform, _NctiCommandRevolve_ID_);
}

Ncti_Boolean NctiHandler::onDraftFeatureBoolean(NctiWindowPlatform* i_pPlatform)
{
    return ExecuteSketchCommand(i_pPlatform, _NctiCommandChangeFeatureBoolMode_ID_);
}

Ncti_Boolean NctiHandler::SketchEdit(NctiWindowPlatform* i_pPlatform)
{
    NctiDocument* pDocument = NctiQTPubFun::GetCurrentViewDocment(i_pPlatform);
    if (!pDocument) { return false; }

    NctiCommandManager* pComMan = NctiCommandManager::GetCommandManager(pDocument->GetBaseModel());
    std::vector<NctiDisplayObject*> ObjVec;
    std::vector<NCTI_MODEL_TAG> CellVec;
    NctiDocElementPubFun::GetDisplayObjectFromSelManager(pDocument, ObjVec, CellVec);
    if (ObjVec.size() == 1 && ObjVec[0]->IsTypeName(NctiDisplayWorkPlane::ID)) {
        NctiArgumentObject argument;
        argument.SetDisplayObject1(ObjVec[0]);
        if (pComMan) {
            EnumNctiResult res = pComMan->RunCommand(_NctiCommandSketch_ID_, &argument);
            if (res == NCTI_SUCCEEDED) { return true; }
        }
    }
    return false;
}

Ncti_Boolean NctiHandler::SketchModelization(NctiWindowPlatform* i_pPlatform)
{
    NctiDocument* pDocument = NctiQTPubFun::GetCurrentViewDocment(i_pPlatform);
    if (!pDocument) { return false; }

    NctiDocViewManager* pDocView     = NctiDocViewManager::GetDocViewManager(pDocument->GetBaseModel());
    NctiCommandManager* pComMan      = NctiCommandManager::GetCommandManager(pDocView);
    NctiDisplayDocSketch* pActiveDoc = (NctiDisplayDocSketch*)pDocView->GetActiveDocSketch();
    if (pActiveDoc) {
        NctiArgumentObject argument;
        argument.SetDisplayObject1(pActiveDoc);
        EnumNctiResult res = pComMan->RunCommand(_NctiCommandFixSketchModel_ID_, &argument);
        if (res == NCTI_SUCCEEDED) return true;
    }
    return false;
}

Ncti_Boolean NctiHandler::SketchRebuild(NctiWindowPlatform* i_pPlatform)
{
    NctiDocument* pDocument = NctiQTPubFun::GetCurrentViewDocment(i_pPlatform);
    if (!pDocument) { return false; }

    NctiDocViewManager* pDocView      = NctiDocViewManager::GetDocViewManager(pDocument->GetBaseModel());
    NctiCommandManager* pComMan       = NctiCommandManager::GetCommandManager(pDocView);
    NctiDisplayDocElement* pActiveDoc = (NctiDisplayDocElement*)pDocView->GetActiveDocSketch();
    if (pActiveDoc == nullptr) return false;
    if (pActiveDoc->IsTypeName(NctiDisplayDocSketch::ID)) {
        NctiDisplayDocSketch* pDocSketch = (NctiDisplayDocSketch*)pActiveDoc;
        NctiArgumentObject argument;
        argument.SetDisplayObject1(pDocSketch);
        EnumNctiResult res = pComMan->RunCommand(_NctiCommandRebuildSketch_ID_, &argument);
        if (res == NCTI_SUCCEEDED) return true;
    }
    return false;
}

Ncti_Boolean NctiHandler::SketchMoveToTop(NctiWindowPlatform* i_pPlatform)
{
    return ExecuteSketchCommand(i_pPlatform, _NctiCommandMoveSketchObjTop_ID_);
}

Ncti_Boolean NctiHandler::SketchMoveToBottom(NctiWindowPlatform* i_pPlatform)
{
    return ExecuteSketchCommand(i_pPlatform, _NctiCommandMoveSketchObjEnd_ID_);
}

Ncti_Boolean NctiHandler::SketchUpside(NctiWindowPlatform* i_pPlatform)
{
    return ExecuteSketchCommand(i_pPlatform, _NctiCommandMoveSketchObjUp_ID_);
}

Ncti_Boolean NctiHandler::SketchDownside(NctiWindowPlatform* i_pPlatform)
{
    return ExecuteSketchCommand(i_pPlatform, _NctiCommandMoveSketchObjDown_ID_);
}

Ncti_Boolean NctiHandler::SketchUnit(NctiWindowPlatform* i_pPlatform)
{
    NctiDocument* pDocument = NctiQTPubFun::GetCurrentViewDocment(i_pPlatform);
    if (!pDocument) { return false; }

    NctiCommandManager* pComMan = NctiCommandManager::GetCommandManager(pDocument->GetBaseModel());
    std::vector<NctiDisplayObject*> ObjVec;
    std::vector<NCTI_MODEL_TAG> CellVec;
    NctiDocElementPubFun::GetDisplayObjectFromSelManager(pDocument, ObjVec, CellVec);
    if (ObjVec.size() == 1) {
        NctiArgumentObject argument;
        argument.SetDisplayObject1(ObjVec[0]);
        EnumNctiResult res = pComMan->RunCommand(_NctiCommandChangeSketchObjBoolMode_ID_, &argument);
        if (res == NCTI_SUCCEEDED) return true;
    }
    return false;
}

Ncti_Boolean NctiHandler::SketchCut(NctiWindowPlatform* i_pPlatform)
{
    NctiDocument* pDocument = NctiQTPubFun::GetCurrentViewDocment(i_pPlatform);
    if (!pDocument) { return false; }

    NctiCommandManager* pComMan = NctiCommandManager::GetCommandManager(pDocument->GetBaseModel());
    std::vector<NctiDisplayObject*> ObjVec;
    std::vector<NCTI_MODEL_TAG> CellVec;
    NctiDocElementPubFun::GetDisplayObjectFromSelManager(pDocument, ObjVec, CellVec);
    if (ObjVec.size() == 1) {
        NctiArgumentObject argument;
        argument.SetDisplayObject1(ObjVec[0]);
        EnumNctiResult res = pComMan->RunCommand(_NctiCommandChangeSketchObjBoolMode_ID_, &argument);
        if (res == NCTI_SUCCEEDED) { return true; }
    }
    return false;
}

Ncti_Boolean NctiHandler::SketchImplode(NctiWindowPlatform* i_pPlatform)
{
    return ExecuteSketchCommand(i_pPlatform, _NctiCommandSketchGroup_ID_);
}

Ncti_Boolean NctiHandler::SketchExplode(NctiWindowPlatform* i_pPlatform)
{
    return ExecuteSketchCommand(i_pPlatform, _NctiCommandSketchGroup_ID_);
}
Ncti_Boolean NctiHandler::SketchParallel(NctiWindowPlatform* i_pPlatform)
{
    NctiDocument* pDocument = NctiQTPubFun::GetCurrentViewDocment(i_pPlatform);
    if (!pDocument) { return false; }

    NctSketchConstrDlg* dlg = new NctSketchConstrDlg;
    dlg->setTitle("平行约束");
    NctiLogicalConstrWidget* widget = new NctiLogicalConstrWidget(pDocument, NCTI_DCM_PARALLEL);
    dlg->setContent(widget);
    dlg->show();
    return true;   
}
Ncti_Boolean NctiHandler::SketchPerpendicular(NctiWindowPlatform* i_pPlatform)
{
    NctiDocument* pDocument = NctiQTPubFun::GetCurrentViewDocment(i_pPlatform);
    if (!pDocument) { return false; }

    NctSketchConstrDlg* dlg = new NctSketchConstrDlg;
    dlg->setTitle("垂直约束");
    NctiLogicalConstrWidget* widget = new NctiLogicalConstrWidget(pDocument, NCTI_DCM_PERPENDICULAR);
    dlg->setContent(widget);
    dlg->show();
    return true;
}
Ncti_Boolean NctiHandler::SketchTangent(NctiWindowPlatform* i_pPlatform)
{
    NctiDocument* pDocument = NctiQTPubFun::GetCurrentViewDocment(i_pPlatform);
    if (!pDocument) { return false; }
    
    NctSketchConstrDlg* dlg = new NctSketchConstrDlg;
    dlg->setTitle("相切约束");
    NctiLogicalConstrWidget* widget = new NctiLogicalConstrWidget(pDocument, NCTI_DCM_TANGENT);
    dlg->setContent(widget);
    dlg->show();
    return true;
}
Ncti_Boolean NctiHandler::SketchEqualRadius(NctiWindowPlatform* i_pPlatform)
{
    NctiDocument* pDocument = NctiQTPubFun::GetCurrentViewDocment(i_pPlatform);
    if (!pDocument) { return false; }

    NctSketchConstrDlg* dlg = new NctSketchConstrDlg;
    dlg->setTitle("等半径约束");
    NctiLogicalConstrWidget* widget = new NctiLogicalConstrWidget(pDocument, NCTI_DCM_EQUAL_RADIUS);
    dlg->setContent(widget);
    dlg->show();
    return true;
}
Ncti_Boolean NctiHandler::SketchConcentric(NctiWindowPlatform* i_pPlatform)
{
    NctiDocument* pDocument = NctiQTPubFun::GetCurrentViewDocment(i_pPlatform);
    if (!pDocument) { return false; }

    NctSketchConstrDlg* dlg = new NctSketchConstrDlg;
    dlg->setTitle("同心约束");
    NctiLogicalConstrWidget* widget = new NctiLogicalConstrWidget(pDocument, NCTI_DCM_CONCENTRIC);
    dlg->setContent(widget);
    dlg->show();
    return true;
}
Ncti_Boolean NctiHandler::SketchFix(NctiWindowPlatform* i_pPlatform)
{
    NctiDocument* pDocument = NctiQTPubFun::GetCurrentViewDocment(i_pPlatform);
    if (!pDocument) { return false; }

    NctSketchConstrDlg* dlg = new NctSketchConstrDlg;
    dlg->setTitle("固定约束");
    NctiFixConstrWidget* widget = new NctiFixConstrWidget(pDocument);
    dlg->setContent(widget);
    dlg->show();
    return true;
}
Ncti_Boolean NctiHandler::SketchDistance(NctiWindowPlatform* i_pPlatform)
{
    NctiDocument* pDocument = NctiQTPubFun::GetCurrentViewDocment(i_pPlatform);
    if (!pDocument) { return false; }

    NctSketchConstrDlg* dlg = new NctSketchConstrDlg;
    dlg->setTitle("距离尺寸");
    NctiDimensionConstrWidget* widget = new NctiDimensionConstrWidget(pDocument, NCTI_DCM_DISTANCE);
    dlg->setContent(widget);
    dlg->show();
    return true;
}
Ncti_Boolean NctiHandler::AssFix(NctiWindowPlatform* i_pPlatform)
{
    return NctiPythonTool::RunAssemblyConsDialog(NctiQTPubFun::GetCurrentViewDocment(i_pPlatform)->GetID(), -1);
}
Ncti_Boolean NctiHandler::AssCoincident(NctiWindowPlatform* i_pPlatform)
{
    return NctiPythonTool::RunAssemblyConsDialog(NctiQTPubFun::GetCurrentViewDocment(i_pPlatform)->GetID(), NCTI_DCM3_COINCIDENT);
}
Ncti_Boolean NctiHandler::AssParallel(NctiWindowPlatform* i_pPlatform)
{
    return NctiPythonTool::RunAssemblyConsDialog(NctiQTPubFun::GetCurrentViewDocment(i_pPlatform)->GetID(), NCTI_DCM3_PARALLEL);
}
Ncti_Boolean NctiHandler::AssConcentric(NctiWindowPlatform* i_pPlatform)
{
    return NctiPythonTool::RunAssemblyConsDialog(NctiQTPubFun::GetCurrentViewDocment(i_pPlatform)->GetID(), NCTI_DCM3_CONCENTRIC);
}
Ncti_Boolean NctiHandler::AssPerpendicular(NctiWindowPlatform* i_pPlatform)
{
    return NctiPythonTool::RunAssemblyConsDialog(NctiQTPubFun::GetCurrentViewDocment(i_pPlatform)->GetID(), NCTI_DCM3_PERPENDICULAR);
}
Ncti_Boolean NctiHandler::AssDistance(NctiWindowPlatform* i_pPlatform)
{
    return NctiPythonTool::RunAssemblyConsDialog(NctiQTPubFun::GetCurrentViewDocment(i_pPlatform)->GetID(), NCTI_DCM3_DISTANCE);
}
Ncti_Boolean NctiHandler::AssAngle(NctiWindowPlatform* i_pPlatform)
{
    return NctiPythonTool::RunAssemblyConsDialog(NctiQTPubFun::GetCurrentViewDocment(i_pPlatform)->GetID(), NCTI_DCM3_ANGLE);
}
Ncti_Boolean NctiHandler::AssEqualDistance(NctiWindowPlatform* i_pPlatform)
{
    return false;
}
Ncti_Boolean NctiHandler::AssExport(NctiWindowPlatform* i_pPlatform)
{
    QString filename;
    if (!NctiQTPubFun::ShowSaveDialog(nullptr, QStringLiteral("导出装配脚本"), "Files(*.py)", filename))
        return false;
    NctiDocument* pDocument = NctiQTPubFun::GetCurrentViewDocment(i_pPlatform);
    NctiCommandManager* pComMan = NctiCommandManager::GetCommandManager(pDocument->GetBaseModel());
    return NctiExecuteDCM3CommandTool::ExecuteExportAssemblyScriptCommand(pComMan, qUtf8Printable(filename));
}
#pragma endregion 草图
} // namespace NCTI