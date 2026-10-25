#ifndef NctiPythonFunctionInterface_H
#define NctiPythonFunctionInterface_H
#include "dcl_ncti_plugin.h"
#include "NctiFunctionInterface.h"
namespace NCTI
{
	/**
	* @brief define Python function interface
	*/
	class DECL_NCTI_PLUGIN NctiPythonFunctionInterface : public NctiFunctionInterface
	{
		NCTI_PLUGIN_FUNCTIONS(NctiPythonFunctionInterface)
	public:
		NctiPythonFunctionInterface();
		virtual ~NctiPythonFunctionInterface();
	};
}
#endif
