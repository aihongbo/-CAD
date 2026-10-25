#include "NctiRegComDemoPan.h"

#include "NctiArgumentObject.h"
#include "NctiDisplayModelBody.h"
#include "NctiTestSystemObject.h"
#include "NctiComDefine.h"
#include "NctiDisplayDocCustomContainer.h"
#include "NctiGeometryFunction.h"
#include "NctiDocElementPubFun.h"

using namespace NCTI;
NCTI_COMMAND_DEF(NctiRegComDemoPan, NctiRegComBase, "cmd_ncti_demo_pan")
NCTI_COMMAND_REGISTRATION(NctiRegComDemoPan)
NCTI_COMMAND_ADD_DO(NctiRegComDemoPan, NctiRegComDemoPan)

NCTI::NctiRegComDemoPan::NctiRegComDemoPan()
{
    NCTI_COMMAND_TITLE("NctiRegComDemoPan");
    m_IsCancel    = false;
    m_bViewActive = true;
}

NCTI::NctiRegComDemoPan::~NctiRegComDemoPan()
{
    NCTI_DELETE_CHAR(m_cpCommandTitle);
    end_default_tool();
}

EnumNctiResult NCTI::NctiRegComDemoPan::Activate(NctiDisplayObject* i_pDoTarget)
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
            PRINT_INVALID_ARGUMENTS(NctiRegComDemoPan::ID)
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
        pHisMan->StartState(NctiRegComDemoPan::ID, iDepth);
    }

    NctiDisplayModelBody* pModelObj = (NctiDisplayModelBody*)m_object;
    NCTI_MODEL_TAG pModelBody       = pModelObj->GetNctiBody();
    //命令中修改对象,调用中间层接口将对象进行平移
    NctiGeometryResult ModelFunctionResult
        = NctiGeometryFunction::pan_object(pSDDisplayDocCustomContainer, 10, 0, 0, pModelBody);
    NctiDocElementPubFun::TestSystemAddResult(pBaseModel, &ModelFunctionResult);
    if (ModelFunctionResult.GetResult() == false) {
        PRINT_GEOMETRY_FUNCTION(NctiRegComDemoPan::ID)
        RequestTermination();
        m_IsCancel = true;
        return NCTI_FAILED;
    }
    else {
        NCTI_API_BEGIN(pHisMan)
        ModelFunctionResult.GetTime();
        pModelObj->UpdateDisplay(pSDDisplayDocCustomContainer, pModelBody);
        NCTI_API_END
    }

    RequestTermination();
    return NCTI_SUCCEEDED;
}

EnumNctiResult NCTI::NctiRegComDemoPan::DeActivate()
{
    NCTI_COM_DEACTIVATE();
}

Ncti_Boolean NCTI::NctiRegComDemoPan::check_status_executable()
{
    return true;
}

Ncti_Boolean NCTI::NctiRegComDemoPan::AnalizePyArgsss(PyObject* i_PyArgsss)
{
    return true;
}
Ncti_Boolean NCTI::NctiRegComDemoPan::AnalizeUIArgsss(NctiArgumentObject* i_Argsss)
{
    return true;
}

Ncti_Boolean NCTI::NctiRegComDemoPan::AnalizePyAndUI(PyObject* i_PyArgsss)
{
    if (i_PyArgsss) {
        NCTI_COM_OBJ_NOT_EXIST("box", NctiRegComDemoPan::ID, NctiDisplayModelBody::ID, m_object)
    }
    return true;
}
