#include "NctiRegComDemoPrintEdgeMid.h"

#include "NctiArgumentObject.h"
#include "NctiDisplayModelBody.h"
#include "NctiTestSystemObject.h"
#include "NctiComDefine.h"
#include "NctiDisplayDocCustomContainer.h"
#include "NctiGeometryFunction.h"
#include "NctiDocElementPubFun.h"

using namespace NCTI;
NCTI_COMMAND_DEF(NctiRegComDemoPrintEdgeMid, NctiRegComBase, "cmd_ncti_demo_print_edge_mid")
NCTI_COMMAND_REGISTRATION(NctiRegComDemoPrintEdgeMid)
NCTI_COMMAND_ADD_DO(NctiRegComDemoPrintEdgeMid, NctiRegComDemoPrintEdgeMid)

NCTI::NctiRegComDemoPrintEdgeMid::NctiRegComDemoPrintEdgeMid()
{
    NCTI_COMMAND_TITLE("NctiRegComDemoPrintEdgeMid");
    m_IsCancel    = false;
    m_bViewActive = true;
}

NCTI::NctiRegComDemoPrintEdgeMid::~NctiRegComDemoPrintEdgeMid()
{
    NCTI_DELETE_CHAR(m_cpCommandTitle);
    end_default_tool();
}

EnumNctiResult NCTI::NctiRegComDemoPrintEdgeMid::Activate(NctiDisplayObject* i_pDoTarget)
{
    if (NctiRegComBase::Activate(i_pDoTarget) == NCTI_FAILED)
        return NCTI_FAILED;

    PyObject* pArg                = nullptr;
    Ncti_Boolean bOK              = true;
    NctiBaseModel* pBaseModel     = m_pCommandManager->GetBaseModel();
    NctiSelectionManager* pSelMan = NctiSelectionManager::GetSelectionManager(pBaseModel);
    pSelMan->ResetSelection();

    if (i_pDoTarget && i_pDoTarget->IsTypeName(NctiArgumentObject::ID)) {
        NctiArgumentObject* pNctiArgumentObject = (NctiArgumentObject*)i_pDoTarget;
        pArg                                    = pNctiArgumentObject->GetPyObject();
        bOK                                     = pArg ? AnalizePyArgsss(pArg) : AnalizeUIArgsss(pNctiArgumentObject);
        bOK                                     = bOK ? AnalizePyAndUI(pArg) : false;
    }
    if (!bOK) {
        if (pArg)
            PRINT_INVALID_ARGUMENTS(NctiRegComDemoPrintEdgeMid::ID)
        RequestTermination();
        m_IsCancel = true;
        return NCTI_FAILED;
    }

    NctiDocViewManager* pDocView = NctiDocViewManager::GetDocViewManager(m_pCommandManager);
    NctiHistoryManager* pHisMan  = NctiHistoryManager::GetHistoryManager(m_pCommandManager);
    NctiDisplayDocCustomContainer* pSDDisplayDocCustomContainer = nullptr;
    NctiDisplayDocElement* pActiveDoc                           = pDocView->GetActiveDocElement()->GetFirstDescendant();
    if (pActiveDoc->IsTypeName(NctiDisplayDocCustomContainer::ID)) {
        pSDDisplayDocCustomContainer = (NctiDisplayDocCustomContainer*)pActiveDoc;
    }
    if (pSDDisplayDocCustomContainer == nullptr
        && pActiveDoc->GetFirstDescendant()->IsTypeName(NctiDisplayDocCustomContainer::ID)) {
        pSDDisplayDocCustomContainer = (NctiDisplayDocCustomContainer*)pActiveDoc->GetFirstDescendant();
    }

    if (pHisMan->GetActive()) {
        int iDepth = 0;
        pHisMan->StartState(NctiRegComDemoPrintEdgeMid::ID, iDepth);
    }

    NctiDisplayModelBody* pModelBody       = (NctiDisplayModelBody*)m_object;
    NctiDisplayDocCustomContainer* pCusDoc = (NctiDisplayDocCustomContainer*)pModelBody->GetDocContainer();

    NctiPosition o_pt;
    NCTI_MODEL_TAG ModelEdge = nullptr;
    pCusDoc->get_void_from_tag(pModelBody, ModelEdge, m_edgeIndex);
    NctiGeometryResult ModelFunctionResult
        = NctiGeometryFunction::get_edge_mid_point(pCusDoc, pModelBody->GetNctiBody(), ModelEdge, o_pt);
    NctiDocElementPubFun::TestSystemAddResult(pBaseModel, &ModelFunctionResult);
    if (ModelFunctionResult.GetResult() == false) {
        PRINT_GEOMETRY_FUNCTION(NctiRegComDemoPrintEdgeMid::ID)
        RequestTermination();
        m_IsCancel = true;
        return NCTI_FAILED;
    }
    else {
        Ncti_Char ch[256];
        NctiString::LocaleSprintf(ch,
                                  "print(\"edge mid: NCTI.Point(%s,%s,%s)\")",
                                  NctiString::double_to_string(o_pt.x(), 15).c_str(),
                                  NctiString::double_to_string(o_pt.y(), 15).c_str(),
                                  NctiString::double_to_string(o_pt.z(), 15).c_str());
        NctiPythonTool::RunPythonString(ch);
    }

    RequestTermination();
    return NCTI_SUCCEEDED;
}

EnumNctiResult NCTI::NctiRegComDemoPrintEdgeMid::DeActivate()
{
    NCTI_COM_DEACTIVATE();
}

Ncti_Boolean NCTI::NctiRegComDemoPrintEdgeMid::check_status_executable()
{
    return true;
}

Ncti_Boolean NCTI::NctiRegComDemoPrintEdgeMid::AnalizePyArgsss(PyObject* i_PyArgsss)
{
    NctiBaseModel* pBaseModel               = m_pCommandManager->GetBaseModel();
    NctiTestSystemObject* pTestSystemObject = NctiDocElementPubFun::GetTestSystemObject(pBaseModel);
    NctiPyErrorInfo* errorInfo              = pTestSystemObject->GetPyErrorInfo();
    NctiPyArgList arglist(i_PyArgsss, errorInfo);
    int num_argsss = arglist.Size();
    if (num_argsss != 3) {
        errorInfo->m_ErrorCode = PY_ARGUMENT_NUM_ERROR;
        errorInfo->m_CorrectNumber.push_back(3);
        return false;
    }

    if (!arglist.GetStr(1, m_ObjectName)) {
        return false;
    }
    if (!arglist.GetLong(2, m_edgeIndex)) {
        return false;
    }
    return true;
}
Ncti_Boolean NCTI::NctiRegComDemoPrintEdgeMid::AnalizeUIArgsss(NctiArgumentObject* i_Argsss)
{
    m_ObjectName = i_Argsss->getChar();
    m_edgeIndex  = i_Argsss->GetIntValue();
    return true;
}

Ncti_Boolean NCTI::NctiRegComDemoPrintEdgeMid::AnalizePyAndUI(PyObject* i_PyArgsss)
{
    if (i_PyArgsss) {
        NCTI_COM_OBJ_NOT_EXIST(m_ObjectName, NctiRegComDemoPrintEdgeMid::ID, NctiDisplayModelBody::ID, m_object)
        std::vector<NCTI_MODEL_TAG> m_EdgeVec;
        std::vector<Ncti_Long> m_EdgeIndexVec;
        m_EdgeIndexVec.push_back(m_edgeIndex);
        NCTI_COM_SUB_OBJS_NOT_EXIST((NctiDisplayModelBody*)m_object, m_EdgeVec, m_EdgeIndexVec)
    }
    return true;
}
