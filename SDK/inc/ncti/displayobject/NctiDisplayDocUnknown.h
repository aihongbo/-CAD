#ifndef NctiDisplayDocUnknown_H
#define NctiDisplayDocUnknown_H
#include "NctiDisplayDocElement.h"
namespace NCTI
{
	/**
	* @brief Doc Unknown Element class
	* @details if the class object is missing , use this
	* @see NctiDisplayDocElement
	*/
	class DECL_NCTI NctiDisplayDocUnknown : public NctiDisplayDocElement
	{
		NCTI_DISPLAYOBJECT_FUNCTIONS(NctiDisplayDocUnknown)
	public:
		virtual ~NctiDisplayDocUnknown();
	public:
		virtual EnumNctiResult restore_temp_file(NctiFileInterface* i_pFI);
	};
}
#endif
