#ifndef NctiParamOperator_H
#define NctiParamOperator_H
#include "dcl_ncti_pubfun.h"
#include "ncti_base.h"
#include "NctiVector.h"
#include <vector>
namespace NCTI
{
	class NctiBaseModel;
	class NctiParametricObject;
	class NctiDisplayObject;
	class NctiDisplayDocCustomContainer;
	class NctiDisplayModelBody;
	class DECL_NCTI_PUBFUN NctiParamArg
	{
	public:
		NctiParamArg() :m_object1(nullptr), m_object2(nullptr), m_dbVal(0.0), m_vecVal(0, 0, 0), m_bVal_1(false),m_bVal_2(false), m_body(nullptr), m_char(nullptr), m_char2(nullptr) {}
		NctiDisplayObject* m_object1;
		NctiDisplayObject* m_object2;

		Ncti_Double m_dbVal;
		Ncti_Double m_dbVal2;
		NctiVector  m_vecVal;
		Ncti_Boolean m_bVal_1;
		Ncti_Boolean m_bVal_2;
		NCTI_MODEL_TAG m_body;
		std::vector<Ncti_Long> m_cells;
		const Ncti_Char* m_char;
		const Ncti_Char* m_char2;
	};
	class DECL_NCTI_PUBFUN NctiParamScriptObj
	{
	public:
		NctiParamScriptObj() {}
		std::pair<NctiDisplayObject*, std::string> m_obj_name;
	};

	class DECL_NCTI_PUBFUN NctiParamOperator//ParamOperatorBase
	{

	public:
		static  Ncti_Boolean ExportScripts(NctiBaseModel* i_pBaseModel, std::vector<std::string>& o_scripts);
		static  Ncti_Boolean ExportParamObjectScript(NctiBaseModel* i_pBaseModel, NctiParametricObject* i_pNctiParametricObject, std::vector<std::string>& o_scrpts, std::vector<NctiParamScriptObj>& o_objName);
		static Ncti_Boolean FindVariable(NctiBaseModel* i_pBaseModel, const std::string& i_name, Ncti_Double& o_value);
		static Ncti_Boolean RebuildAll(NctiBaseModel* i_pBaseModel);
	public:
		NctiParamOperator() :m_pParametricObject(nullptr) {}
		virtual  Ncti_Boolean AddToMnger(NctiBaseModel* i_pBaseModel);
		virtual  Ncti_Boolean UpdateParamObject(NctiBaseModel* i_pBaseModel);

		virtual std::vector<NctiDisplayObject*> GetRes();
		virtual NctiDisplayObject* GetSingleObject(std::vector<NctiDisplayObject*> vec);
		virtual NCTI_MODEL_TAG GetSingleBody(std::vector<NCTI_MODEL_TAG> vec);
		virtual  Ncti_Boolean ToScript(std::vector<std::string>& o_scripts, std::vector<NctiParamScriptObj>& o_objName) = 0;
	protected:
		virtual  Ncti_Boolean FreshParamObject(NctiBaseModel* i_pBaseModel, NctiParametricObject* i_pNctiParametricObject);
		virtual  Ncti_Boolean IsValid() = 0;
		virtual  Ncti_Boolean CreateModelBody(NctiBaseModel* i_pBaseModel, NCTI_MODEL_TAG& o_body, Ncti_Boolean i_new = true)= 0;
		virtual  Ncti_Boolean Rebuild(NctiBaseModel* i_psBaseModel, Ncti_Boolean i_FirstNode) = 0;

		virtual  NctiDisplayObject* GenerateParamObject(NctiBaseModel* i_pNctiBaseModel, Ncti_Boolean& bCreateModelBody) = 0;
		NctiDisplayDocCustomContainer* GetContainer(NctiBaseModel* i_pNctiBaseModel);

		std::string GetNameFromData(NctiDisplayObject* i_pPick, const std::vector<NctiParamScriptObj>& i_objName);
	protected:
		NctiParamArg m_ParamArg;
		NctiParametricObject* m_pParametricObject;
	};
}
#endif
