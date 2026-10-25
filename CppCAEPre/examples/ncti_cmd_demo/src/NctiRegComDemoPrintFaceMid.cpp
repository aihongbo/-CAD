#include "NctiRegComDemoPrintFaceMid.h"

#include "NctiArgumentObject.h"
#include "NctiDisplayModelBody.h"
#include "NctiTestSystemObject.h"
#include "NctiComDefine.h"
#include "NctiDisplayDocCustomContainer.h"
#include "NctiGeometryFunction.h"
#include "NctiDocElementPubFun.h"

using namespace NCTI;
NCTI_COMMAND_DEF(NctiRegComDemoPrintFaceMid, NctiRegComBase, "cmd_ncti_demo_print_face_mid")
NCTI_COMMAND_REGISTRATION(NctiRegComDemoPrintFaceMid)
NCTI_COMMAND_ADD_DO(NctiRegComDemoPrintFaceMid, NctiRegComDemoPrintFaceMid)

NCTI::NctiRegComDemoPrintFaceMid::NctiRegComDemoPrintFaceMid()
{
    NCTI_COMMAND_TITLE("NctiRegComDemoPrintFaceMid");
    m_IsCancel    = false;
    m_bViewActive = true;
}

NCTI::NctiRegComDemoPrintFaceMid::~NctiRegComDemoPrintFaceMid()
{
    NCTI_DELETE_CHAR(m_cpCommandTitle);
    end_default_tool();
}

EnumNctiResult NCTI::NctiRegComDemoPrintFaceMid::Activate(NctiDisplayObject* i_pDoTarget)
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
            PRINT_INVALID_ARGUMENTS(NctiRegComDemoPrintFaceMid::ID)
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
        pHisMan->StartState(NctiRegComDemoPrintFaceMid::ID, iDepth);
    }

    NctiDisplayModelBody* pModelBody       = (NctiDisplayModelBody*)m_object;
    NctiDisplayDocCustomContainer* pCusDoc = (NctiDisplayDocCustomContainer*)pModelBody->GetDocContainer();
    std::vector<NCTI_MODEL_TAG> ModelFaceVec;
    NctiGeometryResult bres = NctiGeometryFunction::find_all_face(pCusDoc, pModelBody->GetNctiBody(), ModelFaceVec);
    std::vector<Ncti_Long> o_CellIDVec;
    for (Ncti_Size i = 0; i < ModelFaceVec.size(); i++) {
        Ncti_Long CellID = -1;
        pCusDoc->get_persistent_tag(pModelBody, ModelFaceVec[i], CellID);
        o_CellIDVec.push_back(CellID);
    }
    if (o_CellIDVec.empty()) {
        PRINT_GEOMETRY_FUNCTION(NctiRegComDemoPrintFaceMid::ID)
        RequestTermination();
        m_IsCancel = true;
        return NCTI_FAILED;
    }

    NctiPosition o_pt;
    NCTI_MODEL_TAG ModelFace = nullptr;
    pCusDoc->get_void_from_tag(pModelBody, ModelFace, o_CellIDVec[0]);
    NctiGeometryResult ModelFunctionResult
        = NctiGeometryFunction::get_point_on_face_by_uv(pCusDoc, pModelBody->GetNctiBody(), ModelFace, 0.5, 0.5, o_pt);

    NctiDocElementPubFun::TestSystemAddResult(pBaseModel, &ModelFunctionResult);
    if (ModelFunctionResult.GetResult() == false) {
        PRINT_GEOMETRY_FUNCTION(NctiRegComDemoPrintFaceMid::ID)
        RequestTermination();
        m_IsCancel = true;
        return NCTI_FAILED;
    }
    else {
        Ncti_Char ch[256];
        NctiString::LocaleSprintf(ch,
                                  "print(\"first face mid: NCTI.Point(%s,%s,%s)\")",
                                  NctiString::double_to_string(o_pt.x(), 15).c_str(),
                                  NctiString::double_to_string(o_pt.y(), 15).c_str(),
                                  NctiString::double_to_string(o_pt.z(), 15).c_str());
        NctiPythonTool::RunPythonString(ch);
    }

    RequestTermination();
    return NCTI_SUCCEEDED;
}

EnumNctiResult NCTI::NctiRegComDemoPrintFaceMid::DeActivate()
{
    NCTI_COM_DEACTIVATE();
}

Ncti_Boolean NCTI::NctiRegComDemoPrintFaceMid::check_status_executable()
{
    return true;
}

Ncti_Boolean NCTI::NctiRegComDemoPrintFaceMid::AnalizePyArgsss(PyObject* i_PyArgsss)
{
    return true;
}
Ncti_Boolean NCTI::NctiRegComDemoPrintFaceMid::AnalizeUIArgsss(NctiArgumentObject* i_Argsss)
{
    return true;
}

Ncti_Boolean NCTI::NctiRegComDemoPrintFaceMid::AnalizePyAndUI(PyObject* i_PyArgsss)
{
    if (i_PyArgsss) {
        NCTI_COM_OBJ_NOT_EXIST("box", NctiRegComDemoPrintFaceMid::ID, NctiDisplayModelBody::ID, m_object)

        //NCTI_COM_SUB_OBJS_NOT_EXIST((NctiDisplayModelBody*)m_DisplayObject, m_FaceVec, m_FaceIndexVec)
    }
    return true;
}
