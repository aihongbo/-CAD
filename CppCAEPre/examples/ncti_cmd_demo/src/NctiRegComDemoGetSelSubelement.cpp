#include "NctiRegComDemoGetSelSubelement.h"

#include "NctiArgumentObject.h"
#include "NctiDisplayModelBody.h"
#include "NctiTestSystemObject.h"
#include "NctiComDefine.h"
#include "NctiDisplayDocCustomContainer.h"
#include "NctiDisplayObjectLifeCycleManager.h"
#include "NctiGeometryFunction.h"

using namespace NCTI;
NCTI_COMMAND_DEF(NctiRegComDemoGetSelSubelement, NctiRegComBase, "cmd_ncti_demo_get_sel_subelement")
NCTI_COMMAND_REGISTRATION(NctiRegComDemoGetSelSubelement)
NCTI_COMMAND_ADD_DO(NctiRegComDemoGetSelSubelement, NctiRegComDemoGetSelSubelement)

NctiRegComDemoGetSelSubelement::NctiRegComDemoGetSelSubelement()
{
    NCTI_COMMAND_TITLE("NctiRegComDemoGetSelSubelement");
    m_IsCancel    = false;
    m_bViewActive = true;
}

NCTI::NctiRegComDemoGetSelSubelement::~NctiRegComDemoGetSelSubelement()
{
    NCTI_DELETE_CHAR(m_cpCommandTitle);
    end_default_tool();
}

EnumNctiResult NCTI::NctiRegComDemoGetSelSubelement::Activate(NctiDisplayObject* i_pDoTarget)
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
            PRINT_INVALID_ARGUMENTS(NctiRegComDemoGetSelSubelement::ID)
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
    bool bHaveSel           = false;
    while ((pSelKeyDo = (NctiSelKeyDo*)listSelected.Next()) != nullptr) {
        pSelKeyDo->GetKey();
        NctiDisplayObject* pDo = pSelKeyDo->GetDoOriginal();
        if (pDo && pDo->IsTypeName(NctiDisplayModelBody::ID)) {
            bHaveSel             = true;
            const char* objName  = pDo->GetObjName();
            std::string strPrint = std::string("name:") + objName + std::string("\\n");

            NctiDisplayModelBody* pModelBody       = (NctiDisplayModelBody*)pDo;
            NctiDisplayDocCustomContainer* pCusDoc = (NctiDisplayDocCustomContainer*)pModelBody->GetDocContainer();

            strPrint += std::string("vertex:[");
            std::vector<NCTI_MODEL_TAG> ModelVertexVec;
            NctiGeometryResult bres
                = NctiGeometryFunction::find_all_vertex(pCusDoc, pModelBody->GetNctiBody(), ModelVertexVec);
            for (Ncti_Size i = 0; i < ModelVertexVec.size(); i++) {
                Ncti_Long CellID = -1;
                pCusDoc->get_persistent_tag(pModelBody, ModelVertexVec[i], CellID);
                if (i < ModelVertexVec.size() - 1)
                    strPrint += NctiString::int_to_string(CellID) + std::string(",");
                else
                    strPrint += NctiString::int_to_string(CellID);
            }
            strPrint += std::string("]\\n");

            strPrint += std::string("edge:[");
            std::vector<NCTI_MODEL_TAG> ModelEdgeVec;
            bres = NctiGeometryFunction::find_all_edge(pCusDoc, pModelBody->GetNctiBody(), ModelEdgeVec);
            for (Ncti_Size i = 0; i < ModelEdgeVec.size(); i++) {
                Ncti_Long CellID = -1;
                pCusDoc->get_persistent_tag(pModelBody, ModelEdgeVec[i], CellID);
                if (i < ModelEdgeVec.size() - 1)
                    strPrint += NctiString::int_to_string(CellID) + std::string(",");
                else
                    strPrint += NctiString::int_to_string(CellID);
            }
            strPrint += std::string("]\\n");

            strPrint += std::string("face:[");
            std::vector<NCTI_MODEL_TAG> ModelFaceVec;
            bres = NctiGeometryFunction::find_all_face(pCusDoc, pModelBody->GetNctiBody(), ModelFaceVec);
            for (Ncti_Size i = 0; i < ModelFaceVec.size(); i++) {
                Ncti_Long CellID = -1;
                pCusDoc->get_persistent_tag(pModelBody, ModelFaceVec[i], CellID);
                if (i < ModelFaceVec.size() - 1)
                    strPrint += NctiString::int_to_string(CellID) + std::string(",");
                else
                    strPrint += NctiString::int_to_string(CellID);
            }
            strPrint += std::string("]");

            Ncti_Char ch[64536];
            NctiString::LocaleSprintf(ch, "print(\"%s\")", strPrint.c_str());
            NctiPythonTool::RunPythonString(ch);
        }
    }
    if (!bHaveSel) {
        Ncti_Char ch[64536];
        NctiString::LocaleSprintf(ch, "print(\"No entity selected!\")");
        NctiPythonTool::RunPythonString(ch);

        RequestTermination();
        m_IsCancel = true;
        return NCTI_FAILED;
    }

    NctiHistoryManager* pHisMan = NctiHistoryManager::GetHistoryManager(m_pCommandManager);
    if (pHisMan->GetActive()) {
        int iDepth = 0;
        pHisMan->StartState(NctiRegComDemoGetSelSubelement::ID, iDepth);
    }

    RequestTermination();
    return NCTI_SUCCEEDED;
}

EnumNctiResult NCTI::NctiRegComDemoGetSelSubelement::DeActivate()
{
    NCTI_COM_DEACTIVATE();
}

Ncti_Boolean NCTI::NctiRegComDemoGetSelSubelement::check_status_executable()
{
    return true;
}

Ncti_Boolean NctiRegComDemoGetSelSubelement::on_command_record_infor()
{
    COMMAND_RECORD_INFOR()
    return true;
}

Ncti_Boolean NCTI::NctiRegComDemoGetSelSubelement::AnalizePyArgsss(PyObject* i_PyArgsss)
{
    return true;
}

bool NCTI::NctiRegComDemoGetSelSubelement::AnalizeUIArgsss(NctiArgumentObject* pArgument)
{
    return true;
}

Ncti_Boolean NCTI::NctiRegComDemoGetSelSubelement::AnalizePyAndUI(PyObject* i_PyArgsss)
{
    return true;
}
