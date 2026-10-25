#include "NctiRegComDemoCancel.h"

#include "NctiArgumentObject.h"
#include "NctiDisplayModelBody.h"
#include "NctiTestSystemObject.h"
#include "NctiComDefine.h"

using namespace NCTI;
NCTI_COMMAND_DEF(NctiRegDemoComCancel, NctiRegComBase, "cmd_ncti_demo_cancel")
NCTI_COMMAND_REGISTRATION(NctiRegDemoComCancel)
NCTI_COMMAND_ADD_DO(NctiRegDemoComCancel, NctiRegDemoComCancel)

NctiRegDemoComCancel::NctiRegDemoComCancel()
{
    NCTI_COMMAND_TITLE("NctiRegDemoComCancel");
    m_IsCancel    = false;
    m_bViewActive = true;
}

NCTI::NctiRegDemoComCancel::~NctiRegDemoComCancel()
{
    NCTI_DELETE_CHAR(m_cpCommandTitle);
    end_default_tool();
}

EnumNctiResult NCTI::NctiRegDemoComCancel::Activate(NctiDisplayObject* i_pDoTarget)
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
            PRINT_INVALID_ARGUMENTS(NctiRegDemoComCancel::ID)
        }
        RequestTermination();
        m_IsCancel = true; //命令的取消
        return NCTI_FAILED;
    }

    Ncti_Char ch[256];
    NctiString::LocaleSprintf(ch, "print(\"not cancel\")");
    NctiPythonTool::RunPythonString(ch);

    NctiHistoryManager* pHisMan = NctiHistoryManager::GetHistoryManager(m_pCommandManager);
    if (pHisMan->GetActive()) {
        int iDepth = 0;
        pHisMan->StartState(NctiRegDemoComCancel::ID, iDepth);
    }

    RequestTermination();
    return NCTI_SUCCEEDED;
}

EnumNctiResult NCTI::NctiRegDemoComCancel::DeActivate()
{
    NCTI_COM_DEACTIVATE();
}

Ncti_Boolean NCTI::NctiRegDemoComCancel::check_status_executable()
{
    return true;
}

Ncti_Boolean NctiRegDemoComCancel::on_command_record_infor()
{
    COMMAND_RECORD_INFOR()
    return true;
}

Ncti_Boolean NCTI::NctiRegDemoComCancel::AnalizePyArgsss(PyObject* i_PyArgsss)
{
    return false; //故意返回false,命令取消
}

bool NCTI::NctiRegDemoComCancel::AnalizeUIArgsss(NctiArgumentObject* pArgument)
{
    return true;
}

Ncti_Boolean NCTI::NctiRegDemoComCancel::AnalizePyAndUI(PyObject* i_PyArgsss)
{
    return true;
}
