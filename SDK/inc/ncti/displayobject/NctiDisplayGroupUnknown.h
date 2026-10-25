#ifndef NctiDisplayGroupUnknown_H
#define NctiDisplayGroupUnknown_H
#include "NctiDisplayGroup.h"
namespace NCTI
{
	/**
	* @brief Doc Unknown Group class
	* @details if the class object is missing , use this
	* @see NctiDisplayGroup
	*/
	class DECL_NCTI NctiDisplayGroupUnknown : public NctiDisplayGroup
	{
		NCTI_DISPLAYOBJECT_FUNCTIONS(NctiDisplayGroupUnknown)
	public:
		virtual ~NctiDisplayGroupUnknown();
	};
}
#endif // !NctiDisplayGroupUnknown_H
