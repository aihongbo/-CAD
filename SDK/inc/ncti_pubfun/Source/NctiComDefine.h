#ifndef NctiComDefine_H
#define NctiComDefine_H
#include "NctiString.h"
#include <memory>
#include "NctiTestSystemObject.h"
#include "NctiPythonTool.h"
#define NCTI_COM_DEACTIVATE()\
if (!m_bActivated)\
{\
	return NCTI_FAILED;\
}\
NctiHistoryManager* pHisMan = NctiHistoryManager::GetHistoryManager(m_pCommandManager);\
if (pHisMan != nullptr && pHisMan->GetActive())\
{\
	int iDepth = 0;\
	if (m_IsCancel == true)\
	{\
		pHisMan->NoteState(NCTI_FAILED, iDepth);\
	}\
	else\
	{\
        command_record_infor();\
		pHisMan->NoteState(NCTI_SUCCEEDED, iDepth);\
	}\
}else if (pHisMan != nullptr )\
{\
	int iDepth = 0;\
	if (m_IsCancel == true)\
	{\
		pHisMan->NoteState(NCTI_FAILED, iDepth);\
	}\
	else\
	{\
        command_record_infor();\
		pHisMan->NoteState(NCTI_SUCCEEDED, iDepth);\
	}\
}\
return NctiRegComBase::DeActivate();

#define NCTI_COM_OBJ_TEST(c_OBJNAME,c_OBJTYPE,DISPLAY_OBJECT)\
{\
	NctiBaseModel* P_BASEMODEL = m_pCommandManager->GetBaseModel(); \
	NctiTestSystemObject* P_TESTSTSTEM = NctiDocElementPubFun::GetTestSystemObject(P_BASEMODEL);\
	P_TESTSTSTEM->ResetComErrorInfo();\
	NctiDocElementPubFun::GetObjectListByName(P_BASEMODEL, c_OBJTYPE, c_OBJNAME, DISPLAY_OBJECT);\
}

#define NCTI_COM_OBJ_EXIST(c_OBJNAME,c_CMDID,c_OBJTYPE)\
{\
	NctiDisplayObject* P_DISPLAY_OBJECT = nullptr;\
	NctiBaseModel* P_BASEMODEL = m_pCommandManager->GetBaseModel();\
	NctiTestSystemObject* P_TESTSTSTEM = NctiDocElementPubFun::GetTestSystemObject(P_BASEMODEL);\
	P_TESTSTSTEM->ResetComErrorInfo();\
	NctiDocElementPubFun::GetObjectListByName(P_BASEMODEL, c_OBJTYPE, c_OBJNAME, P_DISPLAY_OBJECT);\
	if (P_DISPLAY_OBJECT)\
	{\
		PRINT_VARIABLE_NAME_EXIST(c_OBJNAME,c_CMDID)\
        Ncti_Char* newString = new Ncti_Char[100];\
		strcpy(newString, c_OBJNAME);\
		NctiComErrorInfo* P_COMERRORINFO = P_TESTSTSTEM->GetComErrorInfo();\
		P_COMERRORINFO->m_ErrorCode = NCTI_COM_OBJECT_EXIST;\
		P_COMERRORINFO->m_ObjectName = newString;\
		return false; \
	}\
}
#define NCTI_COM_OBJ_NOT_EXIST(c_OBJNAME,c_CMDID,c_OBJTYPE,DISPLAY_OBJECT)\
{\
	NctiBaseModel* P_BASEMODEL = m_pCommandManager->GetBaseModel(); \
	NctiTestSystemObject* P_TESTSTSTEM = NctiDocElementPubFun::GetTestSystemObject(P_BASEMODEL);\
	P_TESTSTSTEM->ResetComErrorInfo();\
	NctiDocElementPubFun::GetObjectListByName(P_BASEMODEL, c_OBJTYPE, c_OBJNAME, DISPLAY_OBJECT); \
	if (!DISPLAY_OBJECT)\
	{\
		PRINT_VARIABLE_NAME_NO_EXIST(c_OBJNAME, c_CMDID)\
        Ncti_Char* newString = new Ncti_Char[100];\
		strcpy(newString, c_OBJNAME);\
		NctiComErrorInfo* P_COMERRORINFO = P_TESTSTSTEM->GetComErrorInfo();\
		P_COMERRORINFO->m_ErrorCode = NCTI_COM_OBJECT_NOT_EXIST;\
		P_COMERRORINFO->m_ObjectName = newString;\
		return false; \
	}\
}
#define NCTI_COM_OBJS_NOT_EXIST(c_OBJNAMES,c_CMDID,c_OBJTYPE,DISPLAY_OBJECTS)\
{\
	NctiBaseModel* P_BASEMODEL = m_pCommandManager->GetBaseModel(); \
	NctiTestSystemObject* P_TESTSTSTEM = NctiDocElementPubFun::GetTestSystemObject(P_BASEMODEL);\
	P_TESTSTSTEM->ResetComErrorInfo();\
	for (size_t i = 0; i < c_OBJNAMES.size(); i++)\
	{\
		NctiDisplayObject* pDisplayObj = nullptr;\
		const char* c_Name = c_OBJNAMES[i].c_str();\
		NctiDocElementPubFun::GetObjectListByName(P_BASEMODEL, c_OBJTYPE, c_Name, pDisplayObj); \
		if (!pDisplayObj)\
		{\
			Ncti_Char* newString = new Ncti_Char[100];\
			strcpy(newString, c_Name);\
			PRINT_VARIABLE_NAME_NO_EXIST(newString, c_CMDID)\
			NctiComErrorInfo* P_COMERRORINFO = P_TESTSTSTEM->GetComErrorInfo();\
			P_COMERRORINFO->m_ErrorCode = NCTI_COM_OBJECT_NOT_EXIST;\
			P_COMERRORINFO->m_ObjectName = newString;\
			return false; \
		}\
		else{\
			DISPLAY_OBJECTS.push_back(pDisplayObj);\
		}\
	}\
}

#define NCTI_COM_SUB_OBJ_NOT_EXIST(PARENT_OBJ,CELL_TAG, CELL_ID)\
{\
	NctiBaseModel* P_BASEMODEL = m_pCommandManager->GetBaseModel();\
	NctiTestSystemObject* P_TESTSTSTEM = NctiDocElementPubFun::GetTestSystemObject(P_BASEMODEL);\
	P_TESTSTSTEM->ResetComErrorInfo();\
	NctiDisplayDocCustomContainer* P_CONTAINER = NctiDocElementPubFun::GetCurrenDocCustom(P_BASEMODEL);\
	P_CONTAINER->get_void_from_tag(PARENT_OBJ, CELL_TAG, CELL_ID);\
	if(!CELL_TAG)\
	{\
		Ncti_Char ch[256];\
		NctiString::LocaleSprintf(ch, "print(\"Cell id \"%d\" is not exist!\")", CELL_ID);\
		NctiPythonTool::RunPythonString(ch);\
		NctiComErrorInfo* P_COMERRORINFO = P_TESTSTSTEM->GetComErrorInfo();\
		P_COMERRORINFO->m_ErrorCode = NCTI_COM_SUB_OBJECT_NOT_EXIST;\
		P_COMERRORINFO->m_CellID = CELL_ID;\
		return false; \
	}\
}

#define NCTI_COM_SUB_OBJS_NOT_EXIST(PARENT_OBJ,CELL_TAGS, CELL_IDS)\
{\
	NctiBaseModel* P_BASEMODEL = m_pCommandManager->GetBaseModel();\
	NctiTestSystemObject* P_TESTSTSTEM = NctiDocElementPubFun::GetTestSystemObject(P_BASEMODEL);\
	P_TESTSTSTEM->ResetComErrorInfo();\
	NctiDisplayDocCustomContainer* P_CONTAINER = NctiDocElementPubFun::GetCurrenDocCustom(P_BASEMODEL);\
	for (size_t i = 0; i < CELL_IDS.size(); i++)\
	{\
		NCTI_MODEL_TAG CELL_TAG;\
		P_CONTAINER->get_void_from_tag(PARENT_OBJ, CELL_TAG, CELL_IDS[i]); \
		if (!CELL_TAG)\
		{\
			Ncti_Char ch[256]; \
			NctiString::LocaleSprintf(ch, "print(\"Cell id \"%d\" is not exist!\")", CELL_IDS[i]); \
			NctiPythonTool::RunPythonString(ch); \
			NctiComErrorInfo* P_COMERRORINFO = P_TESTSTSTEM->GetComErrorInfo(); \
			P_COMERRORINFO->m_ErrorCode = NCTI_COM_SUB_OBJECT_NOT_EXIST; \
			P_COMERRORINFO->m_CellID = CELL_IDS[i]; \
			return false; \
		}\
		CELL_TAGS.push_back(CELL_TAG);\
	}\
}
#define NCTI_COM_LIST_IS_EMPTY(LIST)\
{\
	if(LIST.size() == 0)\
	{\
		NctiBaseModel* P_BASEMODEL = m_pCommandManager->GetBaseModel();\
		NctiTestSystemObject* P_TESTSTSTEM = NctiDocElementPubFun::GetTestSystemObject(P_BASEMODEL);\
		P_TESTSTSTEM->ResetComErrorInfo();\
		NctiComErrorInfo* P_COMERRORINFO = P_TESTSTSTEM->GetComErrorInfo();\
		P_COMERRORINFO->m_ErrorCode = NCTI_COM_LIST_EMPTY;\
		return false; \
	}\
}
#define NCTI_COM_OBJ_INVALID(P_OBJECT,C_TYPE)\
{\
	NctiBaseModel* P_BASEMODEL = m_pCommandManager->GetBaseModel();\
	NctiTestSystemObject* P_TESTSTSTEM = NctiDocElementPubFun::GetTestSystemObject(P_BASEMODEL);\
	P_TESTSTSTEM->ResetComErrorInfo();\
	NctiComErrorInfo* P_COMERRORINFO = P_TESTSTSTEM->GetComErrorInfo();\
	if(!P_OBJECT)\
	{\
		P_COMERRORINFO->m_ErrorCode = NCTI_COM_OBJECT_NULL;\
		return false; \
	}\
	else if(!P_OBJECT->IsTypeName(C_TYPE)){\
		P_COMERRORINFO->m_ErrorCode = NCTI_COM_OBJECT_TYPE_ERROR;\
		return false;\
	}\
}
#define NCTI_COM_OBJ_EXIST_IN_TYPES(c_OBJNAME,c_CMDID,c_OBJTYPES)\
{\
	NctiDisplayObject* P_DISPLAY_OBJECT = nullptr; \
	NctiBaseModel* P_BASEMODEL = m_pCommandManager->GetBaseModel(); \
	NctiTestSystemObject* P_TESTSTSTEM = NctiDocElementPubFun::GetTestSystemObject(P_BASEMODEL); \
	P_TESTSTSTEM->ResetComErrorInfo(); \
	bool isExist = false;\
	for (size_t i = 0; i < c_OBJTYPES.size(); i++)\
	{\
		NctiDocElementPubFun::GetObjectListByName(P_BASEMODEL, c_OBJTYPES[i], c_OBJNAME, P_DISPLAY_OBJECT); \
		if (P_DISPLAY_OBJECT)\
		{\
			isExist = true;\
			break;\
		}\
	}\
	if(isExist)\
	{\
		PRINT_VARIABLE_NAME_NO_EXIST(c_OBJNAME, c_CMDID)\
		Ncti_Char* newString = new Ncti_Char[100];\
		strcpy(newString, c_OBJNAME);\
		NctiComErrorInfo* P_COMERRORINFO = P_TESTSTSTEM->GetComErrorInfo();\
		P_COMERRORINFO->m_ErrorCode = NCTI_COM_OBJECT_EXIST;\
		P_COMERRORINFO->m_ObjectName = newString;\
		return false; \
	}\
}
#define NCTI_COM_OBJ_NOT_EXIST_IN_TYPES(c_OBJNAME,c_CMDID,c_OBJTYPES,DISPLAY_OBJECT)\
{\
	NctiBaseModel* P_BASEMODEL = m_pCommandManager->GetBaseModel(); \
	NctiTestSystemObject* P_TESTSTSTEM = NctiDocElementPubFun::GetTestSystemObject(P_BASEMODEL);\
	P_TESTSTSTEM->ResetComErrorInfo();\
	bool isExist = false;\
	for (size_t i = 0; i < c_OBJTYPES.size(); i++)\
	{\
		NctiDocElementPubFun::GetObjectListByName(P_BASEMODEL, c_OBJTYPES[i], c_OBJNAME, DISPLAY_OBJECT); \
		if (DISPLAY_OBJECT)\
		{\
			isExist = true;\
			break;\
		}\
	}\
	if(!isExist)\
	{\
		PRINT_VARIABLE_NAME_NO_EXIST(c_OBJNAME, c_CMDID)\
		Ncti_Char* newString = new Ncti_Char[100];\
		strcpy(newString, c_OBJNAME);\
		NctiComErrorInfo* P_COMERRORINFO = P_TESTSTSTEM->GetComErrorInfo();\
		P_COMERRORINFO->m_ErrorCode = NCTI_COM_OBJECT_NOT_EXIST;\
		P_COMERRORINFO->m_ObjectName = newString;\
		return false; \
	}\
}

#define PRINT_COMMAND_NAME(c_CMD,c_CMDID)\
Ncti_Char ch[256];\
NctiString::LocaleSprintf(ch, "print(\"%s = %s\")", c_CMD, c_CMDID);\
NctiPythonTool::RunPythonString(ch);

#define PRINT_INVALID_ARGUMENTS(i_NctiObjectID)\
{\
Ncti_Char ch[256];\
NctiString::LocaleSprintf(ch, "print(\"%s: invalid arguments\")", i_NctiObjectID);\
NctiPythonTool::RunPythonString(ch);\
}

#define PRINT_INVALID_ARGUMENT(i_NctiObjectID,i_Argument)\
{\
Ncti_Char ch[256];\
NctiString::LocaleSprintf(ch, "print(\"%s: invalid argument %s\")", i_NctiObjectID, i_Argument);\
NctiPythonTool::RunPythonString(ch);\
}

#define PRINT_VARIABLE_NAME_EXIST(i_varName, i_NctiObjectID)\
{\
Ncti_Char ch[256];\
NctiString::LocaleSprintf(ch, "print('%s:\"%s\" variable name already exists ')", i_NctiObjectID, i_varName);\
NctiPythonTool::RunPythonString(ch);\
}

#define PRINT_VARIABLE_NAME_NO_EXIST(i_varName, i_NctiObjectID)\
Ncti_Char ch[256];\
NctiString::LocaleSprintf(ch, "print('%s:\"%s\" variable name does not exist. ')", i_NctiObjectID, i_varName);\
NctiPythonTool::RunPythonString(ch);


#define PRINT_ARGUMENTS_TYPE(i_NctiObjectID)\
Ncti_Char ch[256];\
NctiString::LocaleSprintf(ch, "print(\"%s: arguments type error\")", i_NctiObjectID);\
NctiPythonTool::RunPythonString(ch);

#define PRINT_GEOMETRY_FUNCTION(i_NctiObjectID)\
Ncti_Char ch[256];\
NctiString::LocaleSprintf(ch, "print(\"%s: geometry function error\")", i_NctiObjectID);\
NctiPythonTool::RunPythonString(ch);

#define PRINT_NO_OBJECT(i_NctiObjectID)\
Ncti_Char ch[256];\
NctiString::LocaleSprintf(ch,"print(\"%s: No Edges Selected Or No Edges specified.\")",i_NctiObjectID);\
NctiPythonTool::RunPythonString(ch);

#define PRINT_ERROR_FUNCTION_IMPLEMENT(i_NctiObjectID)\
Ncti_Char ch[256];\
NctiString::LocaleSprintf(ch,"print(\"%s: Function Implementation is error\")",i_NctiObjectID);\
NctiPythonTool::RunPythonString(ch);

#define PYCHECK_NUMBER(i_Argsss)\
(PyFloat_Check(i_Argsss) || PyLong_Check(i_Argsss))

#define COMMAND_RECORD_INFOR()\
if (NctiRegComBase::on_command_record_infor() == false)\
      return false;

#define NCTI_COM_DCM3_OBJ_TYPE_INVALID(i_NctiDisplayDCM3Geometry,i_ValidTypeList)\
{\
	Ncti_Boolean valid = false; \
	for (auto type: i_ValidTypeList) { \
		if ((i_NctiDisplayDCM3Geometry)->identify() == type) { \
			valid = true; \
			break;\
		} \
	}\
	if(!valid){\
		NctiDisplayObject* P_DISPLAY_OBJECT = nullptr; \
		NctiBaseModel* baseModel = m_pCommandManager->GetBaseModel(); \
		NctiTestSystemObject* testSystem = NctiDocElementPubFun::GetTestSystemObject(baseModel); \
		testSystem->ResetComErrorInfo(); \
		Ncti_Char* newString = new Ncti_Char[100]; \
		strcpy(newString, (i_NctiDisplayDCM3Geometry)->GetObjName()); \
		NctiComErrorInfo* errorInfo = testSystem->GetComErrorInfo(); \
		errorInfo->m_ErrorCode = NCTI_COM_OBJECT_TYPE_ERROR; \
		errorInfo->m_ObjectName = newString; \
		return false; \
	}\
}

#endif


