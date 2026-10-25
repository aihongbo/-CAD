#include "NctiRegComDemoGetSelList.h"

#include "NctiArgumentObject.h"
#include "NctiDisplayModelBody.h"
#include "NctiTestSystemObject.h"
#include "NctiComDefine.h"
#include "NctiDisplayDocCustomContainer.h"
#include "NctiDisplayObjectLifeCycleManager.h"
#include "NctiDocElementPubFun.h"

using namespace NCTI;
NCTI_COMMAND_DEF(NctiRegComDemoGetSelList, NctiRegComBase, "cmd_ncti_demo_get_sel_list")
NCTI_COMMAND_REGISTRATION(NctiRegComDemoGetSelList)
NCTI_COMMAND_ADD_DO(NctiRegComDemoGetSelList, NctiRegComDemoGetSelList)

NctiRegComDemoGetSelList::NctiRegComDemoGetSelList()
{
    NCTI_COMMAND_TITLE("NctiRegComDemoGetSelList");
    m_IsCancel    = false;
    m_bViewActive = true;
}

NCTI::NctiRegComDemoGetSelList::~NctiRegComDemoGetSelList()
{
    NCTI_DELETE_CHAR(m_cpCommandTitle);
    end_default_tool();
}

EnumNctiResult NCTI::NctiRegComDemoGetSelList::Activate(NctiDisplayObject* i_pDoTarget)
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
            PRINT_INVALID_ARGUMENTS(NctiRegComDemoGetSelList::ID)
        }
        RequestTermination();
        m_IsCancel = true;
        return NCTI_FAILED;
    }

    NctiBaseModel* pBaseModel     = m_pCommandManager->GetBaseModel();
    NctiSelectionManager* pSelMan = NctiSelectionManager::GetSelectionManager(pBaseModel);
    NctiSelectionDataList listSelected;
    pSelMan->GetSelected(listSelected, NctiSelKeyDo::ID);
    listSelected.Init();
    NctiSelKeyDo* pSelKeyDo = nullptr;
    while ((pSelKeyDo = (NctiSelKeyDo*)listSelected.Next()) != nullptr) {
        pSelKeyDo->GetKey();
        NctiDisplayObject* pDo = pSelKeyDo->GetDoOriginal();
        if (pDo && pDo->IsTypeName(NctiDisplayModelBody::ID)) {
            const char* objName = pDo->GetObjName();
            Ncti_Char ch[256];
            NctiString::LocaleSprintf(ch, "print(\"selected entity name:%s\")", objName);
            NctiPythonTool::RunPythonString(ch);
        }
    }

    NctiHistoryManager* pHisMan = NctiHistoryManager::GetHistoryManager(m_pCommandManager);
    if (pHisMan->GetActive()) {
        int iDepth = 0;
        pHisMan->StartState(NctiRegComDemoGetSelList::ID, iDepth);
    }

    RequestTermination();
    return NCTI_SUCCEEDED;
}

EnumNctiResult NCTI::NctiRegComDemoGetSelList::DeActivate()
{
    NCTI_COM_DEACTIVATE();
}

Ncti_Boolean NCTI::NctiRegComDemoGetSelList::check_status_executable()
{
    return true;
}

Ncti_Boolean NctiRegComDemoGetSelList::on_command_record_infor()
{
    COMMAND_RECORD_INFOR()
    return true;
}

Ncti_Boolean NCTI::NctiRegComDemoGetSelList::AnalizePyArgsss(PyObject* i_PyArgsss)
{
    return true;
}

bool NCTI::NctiRegComDemoGetSelList::AnalizeUIArgsss(NctiArgumentObject* pArgument)
{
    return true;
}

Ncti_Boolean NCTI::NctiRegComDemoGetSelList::AnalizePyAndUI(PyObject* i_PyArgsss)
{
    return true;
}
