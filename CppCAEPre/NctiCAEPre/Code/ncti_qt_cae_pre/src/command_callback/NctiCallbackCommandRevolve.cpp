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

#include "NctiCallbackCommandRevolve.h"
#include "NctiDisplayGRevolve.h"
#include "NctiToolCreateRevolve.h"
#include "NctiDisplayObjectLifeCycleManager.h"
#include "NctiCommandManager.h"
#include "NctiCommand.h"
#include "NctiHistoryManager.h"
#include "NctiBaseModel.h"
#include "NctiUtilityEx.h"
#include "RevolveDlg.h"
using namespace NCTI;

NCTI_DEF_CALLBACK(SetCreateRevolveDialogCallback,
                  void,
                  CreateRevolveDialog,
                  bool bUseAngle,
                  double dStartAngle,
                  double dEndAngle,
                  int bRemove,
                  int bReverse);

void CreateRevolveDialog(NctiBaseModel* pBaseModel,
                         bool bUseAngle,
                         double dStartAngle,
                         double dEndAngle,
                         int bRemove,
                         int bReverse)
{
    RevolveDlg::ShowDialog(pBaseModel, bUseAngle, dStartAngle, dEndAngle, bRemove, bReverse);
    //cb_CreateRevolveDialog( bUseAngle, dStartAngle, dEndAngle, bRemove, bReverse );
}

NCTI_DEF_CALLBACK(SetDeleteRevolveDialogCallback, void, DeleteRevolveDialog);

void DeleteRevolveDialog()
{
    RevolveDlg::DeleteDialog();
    //cb_DeleteRevolveDialog();
}

NCTI_DEF_CALLBACK(SetRevolveSetValueCallback,
                  void,
                  SetRevolveValue,
                  bool bUseAngle,
                  double dStartAngle,
                  double dEndAngle,
                  int bRemove,
                  int bReverse);

void SetRevolveValue(bool bUseAngle, double dStartAngle, double dEndAngle, int bRemove, int bReverse)
{
    RevolveDlg::SetRevolveData(bUseAngle, dStartAngle, dEndAngle, bRemove, bReverse);
    //cb_SetRevolveValue( bUseAngle, dStartAngle, dEndAngle, bRemove, bReverse );
}

NCTI_DEF_CALLBACK(SetRevolveGetValueCallback,
                  void,
                  GetRevolveValue,
                  int& iUseAngle,
                  double& dStartAngle,
                  double& dEndAngle,
                  int& iRemove,
                  int& iReverse);

void GetRevolveValue(int& iUseAngle, double& dStartAngle, double& dEndAngle, int& iRemove, int& iReverse)
{
    RevolveDlg::GetRevolveData(iUseAngle, dStartAngle, dEndAngle, iRemove, iReverse);
    //cb_GetRevolveValue( iUseAngle, dStartAngle, dEndAngle, iRemove, iReverse );
}

NCTI_COMMAND_DEF(NctiCallbackCommandRevolve, NctiCommandRevolve, _NctiCommandRevolve_ID_)
NCTI_COMMAND_REGISTRATION(NctiCallbackCommandRevolve)

NctiCallbackCommandRevolve::NctiCallbackCommandRevolve()
{
}

NctiCallbackCommandRevolve::~NctiCallbackCommandRevolve()
{
}

EnumNctiResult NctiCallbackCommandRevolve::Activate(NctiDisplayObject* pDoInstance)
{
    if (NctiCommandRevolve::Activate(pDoInstance) != NCTI_SUCCEEDED) {
        return NCTI_FAILED;
    }

    //////////////////////////////////////////////
    // Try to get parameters from Revolve Feature
    //////////////////////////////////////////////
    bool bUseAngle     = false;
    double dStartAngle = 0.0;
    double dEndAngle   = 45.0;
    int bReverse       = 0;
    int bRemove        = 0;

    NctiDisplayObject* pDo = GetTriggerDoOriginal();
    if (pDo != NULL && pDo->IsTypeName(NctiDisplayGRevolve::ID)) {
        m_pDoGRevolve = (NctiDisplayGRevolve*)pDo;
    }

    if (m_pDoGRevolve != NULL) {
        bUseAngle = m_pDoGRevolve->GetUseAngle();
        m_pDoGRevolve->GetAngle(dStartAngle, dEndAngle);
        bReverse = m_pDoGRevolve->GetReverse() ? 1 : 0;

        EnumNctiFeatureBooleanMode eBoolType = NCTI_FEATURE_BOOLEAN_UNITE;
        m_pDoGRevolve->GetBooleanMode(eBoolType);
        bRemove = (eBoolType == NCTI_FEATURE_BOOLEAN_UNITE) ? 0 : 1;
    }

    // Set Parameters to the Dialog
    CreateRevolveDialog(m_pCommandManager->GetBaseModel(), bUseAngle, dStartAngle, dEndAngle, bRemove, bReverse);

    return NCTI_SUCCEEDED;
}

EnumNctiResult NctiCallbackCommandRevolve::DeActivate()
{
    EnumNctiResult retval = NCTI_FAILED;

    // 09/23/2017 Spatial - add: We treat 'Exit Command' as if OK button is pushed
    if (m_bOkProcessed == false && m_bCancelProcessed == false) {
        if (m_pDoGRevolve != NULL) {
            // Set Valid
            m_pDoGRevolve->SetValid();
        }
    }

    retval = NctiCommandRevolve::DeActivate();

    DeleteRevolveDialog();

    return retval;
}

void NctiCallbackCommandRevolve::ProcessOkButton()
{
    if (m_pDoGRevolve != NULL) {
        // Set Valid
        m_pDoGRevolve->SetValid();
    }

    m_pCommandManager->RequestTermination(this);
    if (m_pCommandManager != NULL) {
        m_pCommandManager->CheckTermination();
    }
}

void NctiCallbackCommandRevolve::ProcessUpdate()
{
    if (m_pDoGRevolve != NULL) {
        bool bCurUseAngle     = m_pDoGRevolve->GetUseAngle();
        double dCurStartAngle = 0.0;
        double dCurEndAngle   = 0.0;
        m_pDoGRevolve->GetAngle(dCurStartAngle, dCurEndAngle);
        bool dCurReverse = m_pDoGRevolve->GetReverse();
        EnumNctiFeatureBooleanMode eBoolMode;
        m_pDoGRevolve->GetBooleanMode(eBoolMode);
        bool bCurRemove = (eBoolMode == NCTI_FEATURE_BOOLEAN_SUBTRACT) ? true : false;

        bool bNewUseAngle     = false;
        double dNewStartAngle = 0.0;
        double dNewEndAngle   = 0.0;
        bool bNewReverse      = false;
        bool bNewRemove       = false;
        int iNewUseAngle      = 0;
        int iNewReverse       = 0;
        int iNewRemove        = 0;
        GetRevolveValue(iNewUseAngle, dNewStartAngle, dNewEndAngle, iNewRemove, iNewReverse);

        bNewUseAngle = iNewUseAngle == 1 ? true : false;
        bNewReverse  = iNewReverse == 1 ? true : false;
        bNewRemove   = iNewRemove == 1 ? true : false;
        if (bCurUseAngle != bNewUseAngle || dCurStartAngle != dNewStartAngle || dCurEndAngle != dNewEndAngle
            || dCurReverse != bNewReverse || bCurRemove != bNewRemove) {
            NctiHistoryManager* pHisMan = NctiHistoryManager::GetHistoryManager(m_pCommandManager);
            if (pHisMan != NULL && pHisMan->GetActive()) {
                int iDepth = 0;
                pHisMan->StartState("MSG: Change value", iDepth);
            }

            NCTI_API_BEGIN(pHisMan)
            m_pDoGRevolve->SetUseAngle(bNewUseAngle);
            m_pDoGRevolve->SetAngle(dNewStartAngle, dNewEndAngle);
            m_pDoGRevolve->SetReverse(bNewReverse);
            m_pDoGRevolve->SetBooleanMode(bNewRemove ? NCTI_FEATURE_BOOLEAN_SUBTRACT : NCTI_FEATURE_BOOLEAN_UNITE);
            NCTI_API_END
            if (pHisMan != NULL && pHisMan->GetActive()) {
                int iDepth = 0;
                pHisMan->NoteState(NCTI_SUCCEEDED, iDepth);
            }
        }

        if (m_pTool != NULL) {
            ((NctiToolCreateRevolve*)m_pTool)
                ->RedrawRubberband(bNewUseAngle, dNewStartAngle, dNewEndAngle, bNewReverse);
        }
    }

    NctiBaseModel* pBaseModel = m_pCommandManager->GetBaseModel();
    if (pBaseModel != NULL) {
        pBaseModel->RefreshViews();
    }
}

void NctiCallbackCommandRevolve::ProcessUndo()
{
    UpdateDialog();
}

void NctiCallbackCommandRevolve::ProcessRedo()
{
    UpdateDialog();
}

void NctiCallbackCommandRevolve::UpdateDialog()
{
    if (m_pDoGRevolve != NULL) {
        bool bUseAngle     = m_pDoGRevolve->GetUseAngle();
        double dStartAngle = 0.0;
        double dEndAngle   = 0.0;
        m_pDoGRevolve->GetAngle(dStartAngle, dEndAngle);
        bool bReverse = m_pDoGRevolve->GetReverse() ? 1 : 0;
        EnumNctiFeatureBooleanMode eBoolMode;
        m_pDoGRevolve->GetBooleanMode(eBoolMode);
        bool bRemove = (eBoolMode == NCTI_FEATURE_BOOLEAN_SUBTRACT) ? 1 : 0;

        SetRevolveValue(bUseAngle, dStartAngle, dEndAngle, bRemove, bReverse);
    }
}
