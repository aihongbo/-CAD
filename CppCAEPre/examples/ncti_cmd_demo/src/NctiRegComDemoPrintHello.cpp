#include "NctiRegComDemoPrintHello.h"

#include "NctiArgumentObject.h"
#include "NctiDisplayModelBody.h"
#include "NctiTestSystemObject.h"
#include "NctiComDefine.h"

using namespace NCTI;
NCTI_COMMAND_DEF(NctiRegComDemoPrintHello, NctiRegComBase, "cmd_ncti_demo_print_hello") //注册新命令
NCTI_COMMAND_REGISTRATION(NctiRegComDemoPrintHello)
NCTI_COMMAND_ADD_DO(NctiRegComDemoPrintHello, NctiRegComDemoPrintHello)

NctiRegComDemoPrintHello::NctiRegComDemoPrintHello()
{
    NCTI_COMMAND_TITLE("NctiRegComDemoPrintHello");
    m_IsCancel    = false;
    m_bViewActive = true;
}

NCTI::NctiRegComDemoPrintHello::~NctiRegComDemoPrintHello()
{
    NCTI_DELETE_CHAR(m_cpCommandTitle);
    end_default_tool();
}

EnumNctiResult NCTI::NctiRegComDemoPrintHello::Activate(NctiDisplayObject* i_pDoTarget)
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
            PRINT_INVALID_ARGUMENTS(NctiRegComDemoPrintHello::ID)
        }
        RequestTermination();
        m_IsCancel = true;
        return NCTI_FAILED;
    }

    Ncti_Char ch[256] = "print(\"hello!\")";
    NctiPythonTool::RunPythonString(ch);

    NctiHistoryManager* pHisMan = NctiHistoryManager::GetHistoryManager(m_pCommandManager);
    if (pHisMan->GetActive()) {
        int iDepth = 0;
        pHisMan->StartState(NctiRegComDemoPrintHello::ID, iDepth);
    }

    RequestTermination();
    return NCTI_SUCCEEDED;
}

EnumNctiResult NCTI::NctiRegComDemoPrintHello::DeActivate()
{
    NCTI_COM_DEACTIVATE();
}

Ncti_Boolean NCTI::NctiRegComDemoPrintHello::check_status_executable()
{
    return true;
}

Ncti_Boolean NctiRegComDemoPrintHello::on_command_record_infor()
{
    COMMAND_RECORD_INFOR()
    return true;
}

Ncti_Boolean NCTI::NctiRegComDemoPrintHello::AnalizePyArgsss(PyObject* i_PyArgsss)
{
    return true;
}

bool NCTI::NctiRegComDemoPrintHello::AnalizeUIArgsss(NctiArgumentObject* pArgument)
{
    return true;
}

Ncti_Boolean NCTI::NctiRegComDemoPrintHello::AnalizePyAndUI(PyObject* i_PyArgsss)
{
    return true;
}
