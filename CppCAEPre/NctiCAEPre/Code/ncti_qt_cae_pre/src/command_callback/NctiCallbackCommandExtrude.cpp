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

#include "NctiCallbackCommandExtrude.h"
#include "NctiDisplayWorkPlane.h"
#include "NctiDisplayGExtrude.h"
#include "NctiToolCreateExtrude.h"
#include "NctiDisplayObjectLifeCycleManager.h"
#include "NctiCommandManager.h"
#include "NctiCommand.h"
#include "NctiHistoryManager.h"
#include "NctiBaseModel.h"
#include "NctiUtilityEx.h"
#include "ExtrudeDlg.h"

using namespace NCTI;

NCTI_DEF_CALLBACK(SetCreateExtrudeDialogCallback,
                  void,
                  CreateExtrudeDialog,
                  double dHeight,
                  int bReverse,
                  int bRemove,
                  int bBothSide,
                  int bUseAngle,
                  double dAngle);

void CreateExtrudeDialog(NctiBaseModel* pBaseModel,
                         double dHeight,
                         int bReverse,
                         int bRemove,
                         int bBothSide,
                         int bUseAngle,
                         double dAngle)
{
    ExtrudeDlg::ShowDialog(pBaseModel, dHeight, bReverse, bRemove, bBothSide, bUseAngle, dAngle);
    //cb_CreateExtrudeDialog( dHeight, bReverse, bRemove, bBothSide, bUseAngle, dAngle );
}

NCTI_DEF_CALLBACK(SetDeleteExtrudeDialogCallback, void, DeleteExtrudeDialog);

void DeleteExtrudeDialog()
{
    ExtrudeDlg::DeleteDialog();
    //cb_DeleteExtrudeDialog();
}

NCTI_DEF_CALLBACK(SetExtrudeSetValueCallback,
                  void,
                  SetExtrudeValue,
                  double dHeight,
                  int bReverse,
                  int bRemove,
                  int bBothSide,
                  int bUseAngle,
                  double dAngle);

void SetExtrudeValue(double dHeight, int bReverse, int bRemove, int bBothSide, int bUseAngle, double dAngle)
{
    ExtrudeDlg::SetExtrudeData(dHeight, bReverse, bRemove, bBothSide, bUseAngle, dAngle);
    //cb_SetExtrudeValue( dHeight, bReverse, bRemove, bBothSide, bUseAngle, dAngle );
}

NCTI_DEF_CALLBACK(SetExtrudeGetValueCallback,
                  void,
                  GetExtrudeValue,
                  double& dHeight,
                  int& bReverse,
                  int& bRemove,
                  int& bBothSide,
                  int& bUseAngle,
                  double& dAngle);

void GetExtrudeValue(double& dHeight, int& bReverse, int& bRemove, int& bBothSide, int& bUseAngle, double& dAngle)
{
    ExtrudeDlg::GetExtrudeData(dHeight, bReverse, bRemove, bBothSide, bUseAngle, dAngle);
    //cb_GetExtrudeValue( dHeight, bReverse, bRemove, bBothSide, bUseAngle, dAngle );
}

/////////////////////////////////////////////////////////////////////////////////////////
NCTI_COMMAND_DEF(NctiCallbackCommandExtrude, NctiCommandExtrude, _NctiCommandExtrude_ID_)

NCTI_COMMAND_REGISTRATION(NctiCallbackCommandExtrude)
/////////////////////////////////////////////////////////////////////////////////////////
NctiCallbackCommandExtrude::NctiCallbackCommandExtrude()
{
}

NctiCallbackCommandExtrude::~NctiCallbackCommandExtrude()
{
}

EnumNctiResult NctiCallbackCommandExtrude::Activate(NctiDisplayObject* pDoInstance)
{
    if (NctiCommandExtrude::Activate(pDoInstance) != NCTI_SUCCEEDED) {
        return NCTI_FAILED;
    }

    int iOldReverse  = m_bOldReverse ? 1 : 0;
    int iOldRemove   = m_bOldRemove ? 1 : 0;
    int iOldBothSide = m_bOldBothSide ? 1 : 0;
    int iOldUseAngle = m_bOldUseAngle ? 1 : 0;

    CreateExtrudeDialog(m_pCommandManager->GetBaseModel(),
                        m_dOldHeight,
                        iOldReverse,
                        iOldRemove,
                        iOldBothSide,
                        iOldUseAngle,
                        m_dOldAngle);

    return NCTI_SUCCEEDED;
}

EnumNctiResult NctiCallbackCommandExtrude::DeActivate()
{
    EnumNctiResult retval = NCTI_FAILED;

    // 09/23/2017 Spatial - add: We treat 'Exit Command' as if OK button is pushed
    if (m_bOkProcessed == false && m_bCancelProcessed == false) {
        bool bOK = modify_extrude();
        if (bOK) {
            ProcessOk();
        }
        else {
            ProcessCancelButton();
        }
    }

    retval = NctiCommandExtrude::DeActivate();

    DeleteExtrudeDialog();

    return retval;
}

void NctiCallbackCommandExtrude::ProcessOkButton()
{
    bool bOK = false;

    bOK = modify_extrude();
    if (bOK) {
        ProcessOk();
    }
    else {
        ProcessCancelButton();
    }
    m_pCommandManager->RequestTermination(this);
}

void NctiCallbackCommandExtrude::ProcessUpdate()
{
    if (m_pDoGExtrude != NULL) {
        double dCurrentHeight = m_pDoGExtrude->GetHeight();
        bool bCurrentReverse  = m_pDoGExtrude->GetReverse();
        EnumNctiFeatureBooleanMode eBoolMode;
        m_pDoGExtrude->GetBooleanMode(eBoolMode);
        bool bCurrentRemove   = (eBoolMode == NCTI_FEATURE_BOOLEAN_SUBTRACT) ? true : false;
        bool bCurrentBothSide = m_pDoGExtrude->GetBothSide();
        bool bCurrentUseAngle = m_pDoGExtrude->GetUseAngle();
        double dCurrentAngle  = m_pDoGExtrude->GetAngle();

        if (!m_pDoGExtrude->IsMoveHandle()) {
            double dNewHeight = 0.0;
            bool bNewReverse  = false;
            bool bNewRemove   = false;
            bool bNewBothSide = false;
            bool bNewUseAngle = false;
            double dNewAngle  = 0.0;

            int iNewReverse  = 0;
            int iNewRemove   = 0;
            int iNewBothSide = 0;
            int iNewUseAngle = 0;

            GetExtrudeValue(dNewHeight, iNewReverse, iNewRemove, iNewBothSide, iNewUseAngle, dNewAngle);

            bNewReverse  = iNewReverse == 1 ? true : false;
            bNewRemove   = iNewRemove == 1 ? true : false;
            bNewBothSide = iNewBothSide == 1 ? true : false;
            bNewUseAngle = iNewUseAngle == 1 ? true : false;

            if (dCurrentHeight != dNewHeight || bCurrentReverse != bNewReverse || bCurrentRemove != bNewRemove
                || bCurrentBothSide != bNewBothSide || bCurrentUseAngle != bNewUseAngle || dCurrentAngle != dNewAngle) {
                NctiHistoryManager* pHisMan = NctiHistoryManager::GetHistoryManager(m_pCommandManager);
                if (pHisMan != NULL && pHisMan->GetActive()) {
                    int iDepth = 0;
                    pHisMan->StartState("MSG: Change value", iDepth);
                }

                NCTI_API_BEGIN(pHisMan)
                m_pDoGExtrude->SetHeight(dNewHeight);
                m_pDoGExtrude->SetReverse(bNewReverse);
                m_pDoGExtrude->SetBooleanMode(bNewRemove ? NCTI_FEATURE_BOOLEAN_SUBTRACT : NCTI_FEATURE_BOOLEAN_UNITE);
                m_pDoGExtrude->SetBothSide(bNewBothSide);
                m_pDoGExtrude->SetUseAngle(bNewUseAngle);
                m_pDoGExtrude->SetAngle(dNewAngle);
                NCTI_API_END

                m_pDoGExtrude->Callback(
                    m_pCommandManager->GetBaseModel()->GetActiveBaseView(), NCTI_DO_CALLBACK_REDRAW, NULL);

                if (pHisMan != NULL && pHisMan->GetActive()) {
                    int iDepth = 0;
                    pHisMan->NoteState(NCTI_SUCCEEDED, iDepth);
                }
            }

            if (m_pTool != NULL) {
                ((NctiToolCreateExtrude*)m_pTool)
                    ->RedrawRubberband(dNewHeight, bNewReverse, bNewBothSide, bNewUseAngle, dNewAngle);
            }
        }
        else {
            update_dialog();

            if (m_pTool != NULL) {
                ((NctiToolCreateExtrude*)m_pTool)
                    ->RedrawRubberband(
                        dCurrentHeight, bCurrentReverse, bCurrentBothSide, bCurrentUseAngle, dCurrentAngle);
            }
        }
    }

    NctiBaseModel* pBaseModel = m_pCommandManager->GetBaseModel();
    if (pBaseModel != NULL) {
        pBaseModel->RefreshViews();
    }
}

void NctiCallbackCommandExtrude::ProcessUndo()
{
    update_dialog();
}

void NctiCallbackCommandExtrude::ProcessRedo()
{
    update_dialog();
}

void NctiCallbackCommandExtrude::update_dialog()
{
    if (m_pDoGExtrude != NULL) {
        double dHeight = m_pDoGExtrude->GetHeight();
        bool bReverse  = m_pDoGExtrude->GetReverse();
        EnumNctiFeatureBooleanMode eBoolMode;
        m_pDoGExtrude->GetBooleanMode(eBoolMode);
        bool bRemove   = (eBoolMode == NCTI_FEATURE_BOOLEAN_SUBTRACT) ? true : false;
        bool bBothSide = m_pDoGExtrude->GetBothSide();
        bool bUseAngle = m_pDoGExtrude->GetUseAngle();
        double dAngle  = m_pDoGExtrude->GetAngle();

        int iReverse  = bReverse ? 1 : 0;
        int iRemove   = bRemove ? 1 : 0;
        int iBothSide = bBothSide ? 1 : 0;
        int iUseAngle = bUseAngle ? 1 : 0;

        SetExtrudeValue(dHeight, iReverse, iRemove, iBothSide, iUseAngle, dAngle);
    }
}

void NctiCallbackCommandExtrude::ProcessPickPosition(NctiPosition& cPickPos)
{
    if (m_pDoGExtrude != NULL) {
        NctiDisplayGSketch* pDoSketch = m_pDoGExtrude->GetDoSketch();
        if (pDoSketch != NULL) {
            NctiDisplayWorkPlane* pDoWorkPlane = NULL;
            pDoSketch->GetWorkPlane(pDoWorkPlane);

            if (pDoWorkPlane != NULL) {
                double dHeight = pDoWorkPlane->ComputeDistanceToPoint(cPickPos);

                if (m_pDoGExtrude->GetBothSide()) {
                    dHeight *= 2.0;
                }
                else {
                    NctiPosition posLocal = cPickPos * pDoSketch->GetTransform().inverse();
                    if (posLocal.z() < 0) {
                        dHeight *= -1.0;
                    }

                    if (m_pDoGExtrude->GetReverse()) {
                        dHeight *= -1.0;
                    }
                }

                bool bReverse = m_pDoGExtrude->GetReverse();
                EnumNctiFeatureBooleanMode eBoolMode;
                m_pDoGExtrude->GetBooleanMode(eBoolMode);
                bool bRemove   = (eBoolMode == NCTI_FEATURE_BOOLEAN_SUBTRACT) ? true : false;
                bool bBothSide = m_pDoGExtrude->GetBothSide();
                bool bUseAngle = m_pDoGExtrude->GetUseAngle();
                double dAngle  = m_pDoGExtrude->GetAngle();

                int iReverse  = bReverse ? 1 : 0;
                int iRemove   = bRemove ? 1 : 0;
                int iBothSide = bBothSide ? 1 : 0;
                int iUseAngle = bUseAngle ? 1 : 0;

                SetExtrudeValue(dHeight, iReverse, iRemove, iBothSide, iUseAngle, dAngle);

                NctiCommandManager* pComMan = NctiCommandManager::GetCommandManager(m_pCommandManager);
                if (pComMan != NULL) {
                    pComMan->ProcessUpdate();
                }
            }
        }
    }
}

bool NctiCallbackCommandExtrude::modify_extrude()
{
    bool retval = false;

    if (m_pDoGExtrude != NULL) {
        // if new value is same as old it and command mode is edit, call ProcessCancelButton() to not create CS.
        double dNewHeight = 0.0;
        bool bNewReverse  = false;
        bool bNewRemove   = false;
        bool bNewBothSide = false;
        bool bNewUseAngle = false;
        double dNewAngle  = 0.0;

        int iNewReverse  = 0;
        int iNewRemove   = 0;
        int iNewBothSide = 0;
        int iNewUseAngle = 0;

        GetExtrudeValue(dNewHeight, iNewReverse, iNewRemove, iNewBothSide, iNewUseAngle, dNewAngle);

        bNewReverse  = iNewReverse == 1 ? true : false;
        bNewRemove   = iNewRemove == 1 ? true : false;
        bNewBothSide = iNewBothSide == 1 ? true : false;
        bNewUseAngle = iNewUseAngle == 1 ? true : false;

        if (dNewHeight != 0) {
            if (!(m_pDoGExtrude->IsValid() 
                  && m_dOldHeight == dNewHeight 
                  && m_bOldReverse == bNewReverse
                  && m_bOldRemove == bNewRemove 
                  && m_bOldBothSide == bNewBothSide 
                  && m_bOldUseAngle == bNewUseAngle
                  && m_dOldAngle == dNewAngle)) {
                m_pDoGExtrude->SetValid();
                retval = true;
            }
        }
    }

    return retval;
}
