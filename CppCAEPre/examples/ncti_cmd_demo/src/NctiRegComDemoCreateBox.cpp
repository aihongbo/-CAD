#include "NctiRegComDemoCreateBox.h"

#include "NctiArgumentObject.h"
#include "NctiDisplayModelBody.h"
#include "NctiTestSystemObject.h"
#include "NctiComDefine.h"
#include "NctiDisplayDocCustomContainer.h"
#include "NctiDisplayObjectLifeCycleManager.h"
#include "NctiDocElementPubFun.h"

#include "GeometryFunctionDemo.h"
#include "NctiGeometryFunctionInterface.h"
using namespace NCTI;
NCTI_COMMAND_DEF(NctiRegComDemoCreateBox, NctiRegComBase, "cmd_ncti_demo_create_box")
NCTI_COMMAND_REGISTRATION(NctiRegComDemoCreateBox)
NCTI_COMMAND_ADD_DO(NctiRegComDemoCreateBox, NctiRegComDemoCreateBox)

NctiRegComDemoCreateBox::NctiRegComDemoCreateBox()
{
    NCTI_COMMAND_TITLE("NctiRegComDemoCreateBox");
    m_IsCancel    = false;
    m_bViewActive = true;
}

NCTI::NctiRegComDemoCreateBox::~NctiRegComDemoCreateBox()
{
    NCTI_DELETE_CHAR(m_cpCommandTitle);
    end_default_tool();
}

EnumNctiResult NCTI::NctiRegComDemoCreateBox::Activate(NctiDisplayObject* i_pDoTarget)
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
            PRINT_INVALID_ARGUMENTS(NctiRegComDemoCreateBox::ID)
        }
        RequestTermination();
        m_IsCancel = true;
        return NCTI_FAILED;
    }

    NctiBaseModel* pBaseModel     = m_pCommandManager->GetBaseModel();
    NctiSelectionManager* pSelMan = NctiSelectionManager::GetSelectionManager(pBaseModel);
    pSelMan->ResetSelection();

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
        pHisMan->StartState(NctiRegComDemoCreateBox::ID, iDepth);
    }

    NCTI_MODEL_TAG pModelBody = nullptr;
    NctiGeometryResult ModelFunctionResult;

    //命令中新增对象 调用中间层接口创建长方体
    NctiPosition pos(0, 0, 0);
    ModelFunctionResult
        = GeometryFunctionDemo::create_box_demo(pSDDisplayDocCustomContainer, pos, 10, 20, 30, pModelBody);

    NctiDisplayModelBody* pDisplayModelBody = nullptr;
    NctiDocElementPubFun::TestSystemAddResult(pBaseModel, &ModelFunctionResult);
    if (ModelFunctionResult.GetResult() == false) {
        PRINT_GEOMETRY_FUNCTION(NctiRegComDemoCreateBox::ID)
        RequestTermination();
        m_IsCancel = true;
        return NCTI_FAILED;
    }

    NCTI_API_BEGIN(pHisMan)
    if (ModelFunctionResult.GetResult() == true) {
        ModelFunctionResult.GetTime();
        pDisplayModelBody = (NctiDisplayModelBody*)LCM_GenerateDisplayObject(NctiDisplayModelBody::ID, pBaseModel);
        pDisplayModelBody->Init();
        pDisplayModelBody->SetObjName("box");
        Ncti_Char ch[256];
        NctiString::LocaleSprintf(ch, "print(\"create box name : box\")");
        NctiPythonTool::RunPythonString(ch);
        pDisplayModelBody->UpdateDisplay(pSDDisplayDocCustomContainer, pModelBody);
    }
    NCTI_API_END
    if (pDisplayModelBody) {
        if (pHisMan->GetActive()) {
            pHisMan->NewDoList(pSDDisplayDocCustomContainer, pDisplayModelBody);
        }
        else {
            pDocView->AddDisplayObject(pSDDisplayDocCustomContainer, pDisplayModelBody);
        }
    }
    RequestTermination();
    return NCTI_SUCCEEDED;
}

EnumNctiResult NCTI::NctiRegComDemoCreateBox::DeActivate()
{
    NCTI_COM_DEACTIVATE();
}

Ncti_Boolean NCTI::NctiRegComDemoCreateBox::check_status_executable()
{
    return true;
}

Ncti_Boolean NctiRegComDemoCreateBox::on_command_record_infor()
{
    COMMAND_RECORD_INFOR()
    return true;
}

Ncti_Boolean NCTI::NctiRegComDemoCreateBox::AnalizePyArgsss(PyObject* i_PyArgsss)
{
    return true;
}

bool NCTI::NctiRegComDemoCreateBox::AnalizeUIArgsss(NctiArgumentObject* pArgument)
{
    return true;
}

Ncti_Boolean NCTI::NctiRegComDemoCreateBox::AnalizePyAndUI(PyObject* i_PyArgsss)
{
    return true;
}
