#ifndef NctiExprFunctionInterface_H
#define NctiExprFunctionInterface_H
#include "dcl_ncti_plugin.h"
#include "NctiFunctionInterface.h"
#include <string>
#include <map>
namespace NCTI
{
	/**
	* @brief define Expr function interface
	*/
	class DECL_NCTI_PLUGIN NctiExprFunctionInterface : public NctiFunctionInterface
	{
		NCTI_PLUGIN_FUNCTIONS(NctiExprFunctionInterface)
	public:
		NctiExprFunctionInterface();
		virtual ~NctiExprFunctionInterface();
		virtual Ncti_Boolean Clear();
		virtual Ncti_Boolean SetVariable(const std::string& i_variableName, Ncti_Double i_value);
		virtual Ncti_Boolean SetExpr(const std::vector<std::string>& i_exprs);
		virtual Ncti_Boolean GetVariables(std::map<std::string , Ncti_Double>& o_mapNameValue);
	protected:
		virtual void* InitExprObject();
		virtual void ReleaseExprObject(void*);
		void* m_slv;

	};
}
#endif
