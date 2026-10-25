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

#include "NctiCallbackCommandWorkplane.h"
#include "NctiDisplayWorkPlane.h"
#include "NctiDocViewManager.h"
#include "NctiWCS.h"
#include "NctiToolCreateWorkPlane.h"
#include "NctiDisplayObjectLifeCycleManager.h"
#include "NctiCommandManager.h"
#include "NctiCommand.h"
#include "NctiHistoryManager.h"
#include "NctiBaseModel.h"
#include "NctiUtilityEx.h"
#include "WorkPlaneDlg.h"
#include "NctiDisplayGrid.h"

using namespace NCTI;

NCTI_DEF_CALLBACK(SetCreateWorkplaneDialogCallback, void, CreateWorkplaneDialog);

void CreateWorkplaneDialog(NctiBaseModel* pBaseModel)
{
    WorkPlaneDlg::ShowDialog(pBaseModel);
    //cb_CreateWorkplaneDialog( );
}

NCTI_DEF_CALLBACK(SetDeleteWorkplaneDialogCallback, void, DeleteWorkplaneDialog);

void DeleteWorkplaneDialog()
{
    WorkPlaneDlg::DeleteDialog();
    //cb_DeleteWorkplaneDialog( );
}

NCTI_DEF_CALLBACK(SetWorkplaneSetCoordinateCallback,
                  void,
                  SetWorkplaneCoordinate,
                  double cOriginX,
                  double cOriginY,
                  double cOriginZ,
                  int iEulerAxisId,
                  double dAngleZ0,
                  double dAngleY,
                  double dAngleZ1);

void SetWorkplaneCoordinate(double cOriginX,
                            double cOriginY,
                            double cOriginZ,
                            int iEulerAxisId,
                            double dAngleZ0,
                            double dAngleY,
                            double dAngleZ1)
{
    WorkPlaneDlg::SetCoordinate(cOriginX, cOriginY, cOriginZ, dAngleZ0, dAngleY, dAngleZ1);
    //cb_SetWorkplaneCoordinate( cOriginX, cOriginY, cOriginZ, iEulerAxisId,  dAngleZ0, dAngleY, dAngleZ1 );
}

NCTI_DEF_CALLBACK(SetWorkplaneGetCoordinateCallback,
                  void,
                  GetWorkplaneCoordinate,
                  double& cOriginX,
                  double& cOriginY,
                  double& cOriginZ,
                  int& iEulerAxisId,
                  double& dAngleZ0,
                  double& dAngleY,
                  double& dAngleZ1);

void GetWorkplaneCoordinate(double& cOriginX,
                            double& cOriginY,
                            double& cOriginZ,
                            int& iEulerAxisId,
                            double& dAngleZ0,
                            double& dAngleY,
                            double& dAngleZ1)
{
    iEulerAxisId = 0;
    WorkPlaneDlg::GetCoordinate(cOriginX, cOriginY, cOriginZ, dAngleZ0, dAngleY, dAngleZ1);
    //cb_GetWorkplaneCoordinate( cOriginX, cOriginY, cOriginZ, iEulerAxisId, dAngleZ0, dAngleY, dAngleZ1 );
}

/////////////////////////////////////////////////////////////////////////////////////////
NCTI_COMMAND_DEF(NctiCallbackCommandWorkplane, NctiCommandWorkPlane, _NctiCommandWorkPlane_ID_)

NCTI_COMMAND_REGISTRATION(NctiCallbackCommandWorkplane)
/////////////////////////////////////////////////////////////////////////////////////////

NctiCallbackCommandWorkplane::NctiCallbackCommandWorkplane()
{
    m_eEulerAxis           = NCTI_EURER_XYZ;
    m_bHistoryActiveBackup = false;
}

NctiCallbackCommandWorkplane::~NctiCallbackCommandWorkplane()
{
}

EnumNctiResult NctiCallbackCommandWorkplane::Activate(NctiDisplayObject* pDoInstance)
{
    if (NctiCommandWorkPlane::Activate(pDoInstance) != NCTI_SUCCEEDED) {
        return NCTI_FAILED;
    }

    //Don't create history while executing this command.
    NctiHistoryManager* pHisMan = NctiHistoryManager::GetHistoryManager(m_pCommandManager);
    if (pHisMan != NULL) {
        m_bHistoryActiveBackup = pHisMan->GetActive();
        pHisMan->SetActive(false);
    }
    //////////////////////////////////////////////
    // Try to get parameters from Work Plane
    //////////////////////////////////////////////
    NctiPosition m_cOldOrigin(0, 0, 0);
    NctiUnitVector m_cOldXAxis(0, 0, 0);
    NctiUnitVector m_cOldYAxis(0, 0, 0);

    NctiDisplayObject* pDo = GetTriggerDoOriginal();
    if (pDo != NULL && pDo->IsTypeName(NctiDisplayWorkPlane::ID)) {
        m_pDoWorkPlane = (NctiDisplayWorkPlane*)pDo;
    }

    // If there is no WorkPlane, ask Tool if user specified WorkPlane
    if (m_pDoWorkPlane == NULL && m_pTool != NULL) {
        m_pDoWorkPlane = ((NctiToolCreateWorkPlane*)m_pTool)->GetDisplayWorkPlane();
    }

    if (m_pDoWorkPlane != NULL) {
        m_pDoWorkPlane->GetCoordinate(m_cOldOrigin, m_cOldXAxis, m_cOldYAxis);
        //If value of WorkPlane is zero, set values that indicates x-y plane as the default.
        if (m_cOldXAxis.len() == 0 || m_cOldYAxis.len() == 0) {
            NCTI_API_BEGIN(pHisMan)
            m_pDoWorkPlane->SetCoordinate(NctiPosition(0, 0, 0), NctiUnitVector(1, 0, 0), NctiUnitVector(0, 1, 0));
            m_pDoWorkPlane->UpdateDisplay();
            NCTI_API_END
            m_pDoWorkPlane->GetCoordinate(m_cOldOrigin, m_cOldXAxis, m_cOldYAxis);
        }

        CreateWorkplaneDialog(pHisMan->GetBaseModel());

        NctiPosition cXAxis(m_cOldOrigin + m_cOldXAxis);
        NctiPosition cYAxis(m_cOldOrigin + m_cOldYAxis);

        NctiWCS wcs(m_cOldOrigin, m_cOldOrigin + m_cOldXAxis, m_cOldOrigin + m_cOldYAxis);
        NctiTransf trans = wcs.ToModel();

        double dAngle1 = 0;
        double dAngle2 = 0;
        double dAngle3 = 0;

        ConvertTransfToEuler(trans, m_eEulerAxis, dAngle1, dAngle2, dAngle3);

        SetWorkplaneCoordinate(
            m_cOldOrigin.x(), m_cOldOrigin.y(), m_cOldOrigin.z(), m_eEulerAxis, dAngle1, dAngle2, dAngle3);
    }

    return NCTI_SUCCEEDED;
}

EnumNctiResult NctiCallbackCommandWorkplane::DeActivate()
{
    EnumNctiResult retval = NCTI_FAILED;

    retval = NctiCommandWorkPlane::DeActivate();

    DeleteWorkplaneDialog();

    return retval;
}

bool NctiCallbackCommandWorkplane::check_dlg_value()
{
    bool bValid = true;

    // Get Dialog Value
    NctiPosition cOrig, cXPos, cYPos;

    double originx, originy, originz;
    int iEulerAxis;
    double dAngle1, dAngle2, dAngle3;

    GetWorkplaneCoordinate(originx, originy, originz, iEulerAxis, dAngle1, dAngle2, dAngle3);

    NctiTransf transf;
    ConvertEulerToTransf((EnumNctiEuler)iEulerAxis, dAngle1, dAngle2, dAngle3, transf);

    cOrig = NctiPosition(originx, originy, originz);
    cXPos = cOrig + (NctiUnitVector(1, 0, 0) * transf);
    cYPos = cOrig + (NctiUnitVector(0, 1, 0) * transf);

    // Check Value
    bValid = check_value(cOrig, cXPos, cYPos);

    return bValid;
}

void NctiCallbackCommandWorkplane::ProcessOkButton()
{
    bool bValid = true;

    bValid = check_dlg_value();

    if (bValid && m_pDoWorkPlane) {
        // Get Dialog Value
        NctiPosition cOrig, cXPos, cYPos;

        double originx, originy, originz;
        int iEulerAxis;
        double dAngle1, dAngle2, dAngle3;

        GetWorkplaneCoordinate(originx, originy, originz, iEulerAxis, dAngle1, dAngle2, dAngle3);

        NctiTransf transf;
        ConvertEulerToTransf((EnumNctiEuler)iEulerAxis, dAngle1, dAngle2, dAngle3, transf);

        cOrig = NctiPosition(originx, originy, originz);
        cXPos = cOrig + NctiVector(1, 0, 0) * transf;
        cYPos = cOrig + NctiVector(0, 1, 0) * transf;

        // Compute Axis
        NctiUnitVector cUDir, cVDir;
        compute_axis(cOrig, cXPos, cYPos, cUDir, cVDir);

        //value of WorkPlane reverts to create history that has old values and new values.
        m_pDoWorkPlane->SetCoordinate(m_cOld_Origin, m_cOld_U_Axis, m_cOld_V_Axis);
        m_pDoWorkPlane->UpdateDisplay();
        // Update the parameter of work plane
        NctiHistoryManager* pHisMan = NctiHistoryManager::GetHistoryManager(m_pCommandManager);
        if (pHisMan != NULL) {
            pHisMan->SetActive(m_bHistoryActiveBackup);
            if (pHisMan->GetActive()) {
                int iDepth = 0;
                pHisMan->StartState("determine coordinate", iDepth, m_pDoWorkPlane, NCTI_DO_CALLBACK_REDRAW);
            }
        }

        NCTI_API_BEGIN(pHisMan)
        m_pDoWorkPlane->SetCoordinate(cOrig, cUDir, cVDir);
        m_pDoWorkPlane->UpdateDisplay();
        NCTI_API_END;

        if (pHisMan != NULL && pHisMan->GetActive()) {
            int iDepth = 0;
            pHisMan->NoteState(NCTI_SUCCEEDED, iDepth);
        }

        // Exit command
        m_pCommandManager->RequestTermination(this);
    }
}

void NctiCallbackCommandWorkplane::ProcessUpdate()
{
    bool bDragging = false;

    if (m_pDoWorkPlane != NULL) {
        bDragging = m_pDoWorkPlane->IsDragging();

        if (!bDragging) {
            // Get Dialog Value
            NctiPosition cOrig, cXPos, cYPos;

            double originx, originy, originz;
            int iEulerAxis;
            double dAngle1, dAngle2, dAngle3;

            GetWorkplaneCoordinate(originx, originy, originz, iEulerAxis, dAngle1, dAngle2, dAngle3);

            //If Euler Axis is changed on Dialog, compute angles and refresh dialog.
            if (m_eEulerAxis != iEulerAxis) {
                NctiPosition posOrigin;
                NctiUnitVector uvecU, uvecV;
                NctiTransf trans = ncti_identity_transform;
                m_pDoWorkPlane->GetCoordinate(posOrigin, uvecU, uvecV);

                NctiWCS wcs(posOrigin, posOrigin + uvecU, posOrigin + uvecV);
                trans = wcs.ToModel();
                ConvertTransfToEuler(trans, (EnumNctiEuler)iEulerAxis, dAngle1, dAngle2, dAngle3);
                m_eEulerAxis = (EnumNctiEuler)iEulerAxis;
                SetWorkplaneCoordinate(
                    posOrigin.x(), posOrigin.y(), posOrigin.z(), m_eEulerAxis, dAngle1, dAngle2, dAngle3);
            }
            else {
                NctiTransf transf;

                ConvertEulerToTransf((EnumNctiEuler)iEulerAxis, dAngle1, dAngle2, dAngle3, transf);

                cOrig = NctiPosition(originx, originy, originz);
                cXPos = cOrig + NctiVector(1, 0, 0) * transf;
                cYPos = cOrig + NctiVector(0, 1, 0) * transf;

                // Compute Axis
                NctiUnitVector cUDir, cVDir;

                if (((NctiToolCreateWorkPlane*)m_pTool)->GetWorkPlaneByFace(cOrig, cUDir, cVDir)) {
                    // Reset for next pick
                    ((NctiToolCreateWorkPlane*)m_pTool)->ResetWorkPlaneByFace();

                    NctiPosition cXAxis(cOrig + cUDir);
                    NctiPosition cYAxis(cOrig + cVDir);
                    NctiWCS wcs(cOrig, cXAxis, cYAxis);
                    NctiTransf trans = wcs.ToModel();

                    double dAngle1 = 0;
                    double dAngle2 = 0;
                    double dAngle3 = 0;

                    ConvertTransfToEuler(trans, (EnumNctiEuler)iEulerAxis, dAngle1, dAngle2, dAngle3);

                    SetWorkplaneCoordinate(
                        cOrig.x(), cOrig.y(), cOrig.z(), (EnumNctiEuler)iEulerAxis, dAngle1, dAngle2, dAngle3);
                }
                else {
                    compute_axis(cOrig, cXPos, cYPos, cUDir, cVDir);
                }

                m_pDoWorkPlane->SetCoordinate(cOrig, cUDir, cVDir);
                m_pDoWorkPlane->UpdateDisplay();
            }
        }
        else {
            NctiPosition cOrig;
            NctiUnitVector cXAxis;
            NctiUnitVector cYAxis;

            m_pDoWorkPlane->GetCoordinate(cOrig, cXAxis, cYAxis);

            NctiPosition cUDir = cOrig + cXAxis;
            NctiPosition cVDir = cOrig + cYAxis;

            NctiWCS wcs(cOrig, cUDir, cVDir);
            NctiTransf trans = wcs.ToModel();

            double dAngle1 = 0;
            double dAngle2 = 0;
            double dAngle3 = 0;

            ConvertTransfToEuler(trans, m_eEulerAxis, dAngle1, dAngle2, dAngle3);

            SetWorkplaneCoordinate(cOrig.x(), cOrig.y(), cOrig.z(), m_eEulerAxis, dAngle1, dAngle2, dAngle3);
        }
    }

    if (!bDragging) {
        update_sketch();
    }

    NctiDocViewManager* pDocViewMan = NctiDocViewManager::GetDocViewManager(m_pCommandManager);
    if (pDocViewMan != NULL) {
        pDocViewMan->RequestUpdateInstance(m_pDoWorkPlane);
    }

    NctiBaseModel* pBaseModel = m_pCommandManager->GetBaseModel();
    if (pBaseModel != NULL) {
        pBaseModel->RefreshViews();
    }
}

void NctiCallbackCommandWorkplane::ProcessPickPosition(NctiPosition& cPickPos)
{
}

void NctiCallbackCommandWorkplane::ProcessUndo()
{
    update_dialog();
}

void NctiCallbackCommandWorkplane::ProcessRedo()
{
    update_dialog();
}

void NctiCallbackCommandWorkplane::ProcessCancel()
{
    NctiCommandWorkPlane::ProcessCancel();

    //Revert value of WorkPlane and status of history.
    if (m_pDoWorkPlane != NULL) {
        // Compute Axis
        m_pDoWorkPlane->SetCoordinate(m_cOld_Origin, m_cOld_U_Axis, m_cOld_V_Axis);
        m_pDoWorkPlane->UpdateDisplay();
        NctiHistoryManager* pHisMan = NctiHistoryManager::GetHistoryManager(m_pCommandManager);
        if (pHisMan != NULL) {
            pHisMan->SetActive(m_bHistoryActiveBackup);
        }
    }
}

void NctiCallbackCommandWorkplane::update_dialog()
{
    NctiPosition cOrig;
    NctiUnitVector cXAxis;
    NctiUnitVector cYAxis;

    m_pDoWorkPlane->GetCoordinate(cOrig, cXAxis, cYAxis);

    NctiPosition cUDir(cOrig + cXAxis);
    NctiPosition cVDir(cOrig + cYAxis);
    NctiWCS wcs(cOrig, cUDir, cVDir);
    NctiTransf trans = wcs.ToModel();

    double dAngle1 = 0;
    double dAngle2 = 0;
    double dAngle3 = 0;

    ConvertTransfToEuler(trans, m_eEulerAxis, dAngle1, dAngle2, dAngle3);

    SetWorkplaneCoordinate(cOrig.x(), cOrig.y(), cOrig.z(), m_eEulerAxis, dAngle1, dAngle2, dAngle3);
}