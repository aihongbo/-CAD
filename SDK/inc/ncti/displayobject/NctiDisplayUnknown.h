#ifndef NctiDisplayUnknown_H
#define NctiDisplayUnknown_H
#include "NctiDisplayObject.h"
namespace NCTI
{
	/**
	* @brief Object Unknown Element class
	* @details if the class object is missing , use this
	* @see NctiDisplayObject
	*/
	class DECL_NCTI NctiDisplayUnknown : public NctiDisplayObject
	{
		NCTI_DISPLAYOBJECT_FUNCTIONS(NctiDisplayUnknown)
	public:
		virtual ~NctiDisplayUnknown();
	};
}
#endif
