#include "NctiRegComDemoJoinSel.h"

#include "NctiArgumentObject.h"
#include "NctiDisplayModelBody.h"
#include "NctiTestSystemObject.h"
#include "NctiComDefine.h"
#include "NctiBaseModel.h"
#include "NctiBaseView.h"
#include "NctiGeometryFunction.h"
#include "NctiDocElementPubFun.h"

using namespace NCTI;
NCTI_COMMAND_DEF(NctiRegComDemoJoinSel, NctiRegComBase, "cmd_ncti_demo_join_sel")
NCTI_COMMAND_REGISTRATION(NctiRegComDemoJoinSel)
NCTI_COMMAND_ADD_DO(NctiRegComDemoJoinSel, NctiRegComDemoJoinSel)

NctiRegComDemoJoinSel::NctiRegComDemoJoinSel()
{
    NCTI_COMMAND_TITLE("NctiRegComDemoJoinSel");
    m_IsCancel    = false;
    m_bViewActive = true;
}

NCTI::NctiRegComDemoJoinSel::~NctiRegComDemoJoinSel()
{
    NCTI_DELETE_CHAR(m_cpCommandTitle);
    end_default_tool();
}

EnumNctiResult NCTI::NctiRegComDemoJoinSel::Activate(NctiDisplayObject* i_pDoTarget)
{
    if (NctiRegComBase::Activate(i_pDoTarget) == NCTI_FAILED)
        return NCTI_FAILED;
    PyObject* pArg   = nullptr;
    Ncti_Boolean bOK = true;
    if (i_pDoTarget && i_pDoTarget->IsTypeName(NctiArgumentObject::ID)) {
        NctiArgumentObject* pArgumentObject = (NctiArgumentObject*)i_pDoTarget;
        pArg                                = pArgumentObject->GetPyObject();
        bOK                                 = pArg ? AnalizePyArgsss(pArg) : AnalizeUIArgsss(pArgumentObject);
        bOK                                 = bOK ? AnalizePyAndUI(pArg) : false;
    }
    if (!bOK) {
        if (pArg) {
            PRINT_INVALID_ARGUMENTS(NctiRegComDemoJoinSel::ID)
        }
        RequestTermination();
        m_IsCancel = true;
        return NCTI_FAILED;
    }
    NctiHistoryManager* pHisMan = NctiHistoryManager::GetHistoryManager(m_pCommandManager);
    if (pHisMan->GetActive()) {
        int iDepth = 0;
        pHisMan->StartState(NctiRegComDemoJoinSel::ID, iDepth);
    }

    NctiBaseModel* pBaseModel     = m_pCommandManager->GetBaseModel();
    NctiSelectionManager* pSelMan = NctiSelectionManager::GetSelectionManager(pBaseModel);
    pSelMan->ResetSelection(false);
    for (int i = 0; i < m_DisplayObjectVec.size(); i++) {
        NctiDisplayObject* pDisObj = m_DisplayObjectVec[i];
        std::vector<NctiDisplayObject*> InstanceVec;
        pDisObj->GetInstance(pBaseModel->GetActiveBaseView(), InstanceVec);
        //NctiDisplayObject* pInstanceObj = pBaseModel->GetActiveBaseView()->GetInstanceFromOriginal(pDisObj);
        for (Ncti_Size i = 0; i < InstanceVec.size(); i++) {
            NctiDisplayObject* pInstanceObj = InstanceVec[i];
            if (pInstanceObj) {
                NctiSelKeyDo cSelData(nullptr, pDisObj, pInstanceObj);
                pSelMan->SetSelected(&cSelData, NCTI_SELECT_NO_MOUSE, false);
                //pInstanceObj->Callback(pBaseModel->GetActiveBaseView(), NCTI_DO_CALLBACK_SHOW_CONTEXT_MENU, nullptr);
            }
        }
    }
    pBaseModel->GetActiveBaseView()->Update();

    RequestTermination();
    return NCTI_SUCCEEDED;
}

EnumNctiResult NCTI::NctiRegComDemoJoinSel::DeActivate()
{
    NCTI_COM_DEACTIVATE();
}

Ncti_Boolean NCTI::NctiRegComDemoJoinSel::check_status_executable()
{
    return true;
}

Ncti_Boolean NctiRegComDemoJoinSel::on_command_record_infor()
{
    COMMAND_RECORD_INFOR()
    return true;
}

Ncti_Boolean NCTI::NctiRegComDemoJoinSel::AnalizePyArgsss(PyObject* i_PyArgsss)
{
    NctiBaseModel* pBaseModel               = m_pCommandManager->GetBaseModel();
    NctiTestSystemObject* pTestSystemObject = NctiDocElementPubFun::GetTestSystemObject(pBaseModel);
    NctiPyErrorInfo* errorInfo              = pTestSystemObject->GetPyErrorInfo();
    NctiPyArgList arglist(i_PyArgsss, errorInfo);
    Ncti_Integer num_argsss = arglist.Size();
    if (2 != num_argsss) {
        errorInfo->m_ErrorCode = PY_ARGUMENT_NUM_ERROR;
        errorInfo->m_CorrectNumber.push_back(2);
        return false;
    }

    if (!arglist.GetStrList(1, m_objNameVec))
        return false;
    if (m_objNameVec.empty())
        return false;
    return true;
}

bool NCTI::NctiRegComDemoJoinSel::AnalizeUIArgsss(NctiArgumentObject* pArgument)
{
    return true;
}

Ncti_Boolean NCTI::NctiRegComDemoJoinSel::AnalizePyAndUI(PyObject* i_PyArgsss)
{
    if (i_PyArgsss) {
        NCTI_COM_OBJS_NOT_EXIST(m_objNameVec, NctiRegComDemoJoinSel::ID, NctiDisplayModelBody::ID, m_DisplayObjectVec)
    }
    return true;
}
