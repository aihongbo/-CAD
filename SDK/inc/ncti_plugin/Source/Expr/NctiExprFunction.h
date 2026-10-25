#ifndef NctiExprFunction_H
#define NctiExprFunction_H
#include "NctiExprFunctionInterface.h"
#include "dcl_ncti_plugin.h"
namespace NCTI
{

	class DECL_NCTI_PLUGIN NctiExprFunction
	{
	public:
		NctiExprFunction();
		virtual ~NctiExprFunction();
	public:
		static Ncti_Boolean Clear();
		static Ncti_Boolean SetVariable(const std::string& i_variableName, Ncti_Double i_value);
		static Ncti_Boolean SetExpr(const std::vector<std::string>& i_exprs);
		static Ncti_Boolean GetVariables(std::map<std::string, Ncti_Double>& o_mapNameValue);
	};
}
#endif