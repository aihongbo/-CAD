#ifndef NctiParametricModelTool_H
#define NctiParametricModelTool_H
#include "dcl_ncti_pubfun.h"
#include "ncti_base.h"
#include "NctiVector.h"
#include <vector>
#include <cstdio>
namespace NCTI
{
	class NctiParamOperator;
	class NctiBaseModel;
	class NctiDisplayModelBody;
	class NctiParametricObject;
	class NctiParametricManagerObject;
	class NctiDisplayGSketch;
	class NctiDisplayObject;
	class NctiParamVariable;
	class DECL_NCTI_PUBFUN NctiParametricModelTool
	{
	public:
		static void CreateParamManagerObject(NctiBaseModel* i_pBaseModel);
		static NctiParametricManagerObject* GetParamManagerObject(NctiBaseModel* i_pBaseModel);
		static NctiParametricObject* GetParamObjFromInputObj(NctiBaseModel* i_pBaseModel, NctiDisplayObject* i_pDisplayModelBody);
		static  Ncti_Boolean ExportScripts(NctiBaseModel* i_pBaseModel, std::vector<std::string>& o_scripts);
		static Ncti_Boolean RebuildAll(NctiBaseModel* i_pBaseModel);
	public:
		//参数关系
		static void SetDataToManager(NctiBaseModel* i_pBaseModel, const std::vector<NctiParamVariable>& i_variable, const std::vector<std::string>& i_expr);
		static std::vector<NctiParamVariable> GetVariableFromManager(NctiBaseModel* i_pBaseModel);
		static std::vector<std::string> GetExprFromManager(NctiBaseModel* i_pBaseModel);
	public:
		//草图
		static Ncti_Boolean ExecuteSketchOperator(NctiBaseModel* i_pBaseModel, NctiDisplayObject* i_pDisplayModelBody);
		static Ncti_Boolean HasSketch(NctiBaseModel* i_pBaseModel, NctiDisplayObject* i_pDisplayModelBody);
		static Ncti_Boolean UpdateSketchOperator(NctiBaseModel* i_pBaseModel, NctiParametricObject* i_pParametricObject);
		static Ncti_Boolean UpdateSketchOperator(NctiBaseModel* i_pBaseModel, NctiDisplayObject* i_pDisplayModelBody);

		//拉伸
		static Ncti_Boolean ExecuteStretchOperator(NctiBaseModel* i_pBaseModel, NctiDisplayGSketch* i_pDisplayModelBody, Ncti_Double i_distance, Ncti_Boolean i_both, Ncti_Boolean i_reversed/*, NctiDisplayModelBody*& i_pRes*/);
		static Ncti_Boolean UpdateStretchOperator(NctiBaseModel* i_pBaseModel, NctiParametricObject* i_pParametricObject, Ncti_Double i_distance, const Ncti_Char* i_DistanceName, Ncti_Boolean i_both, Ncti_Boolean i_reversed);
		//圆角
		static Ncti_Boolean ExecuteRoundOperator(NctiBaseModel* i_pBaseModel, NctiDisplayModelBody* i_pDisplayModelBody, Ncti_Double i_distance, const std::vector<Ncti_Long>& i_cells);
		static Ncti_Boolean UpdateRoundOperator(NctiBaseModel* i_pBaseModel, NctiParametricObject* i_pParametricObject, Ncti_Double i_distance, const Ncti_Char* i_DistanceName, const std::vector<Ncti_Long>& i_cells);

		static Ncti_Boolean ExecuteRevolveOperator(NctiBaseModel* i_pBaseModel, NctiDisplayGSketch* i_pDisplayModelBody, Ncti_Boolean i_useAngle, Ncti_Double i_startAngle, Ncti_Double i_endAngle, Ncti_Boolean i_bReversed);
		static Ncti_Boolean UpdateRevolveOperator(NctiBaseModel* i_pBaseModel, NctiParametricObject* i_pParametricObject, Ncti_Boolean i_useAngle, Ncti_Double i_startAngle, const Ncti_Char* i_startAngleName, Ncti_Double i_endAngle, const Ncti_Char* i_endAngleName, Ncti_Boolean i_bReversed);
	//public:
	//	static 
	};

}
#endif
