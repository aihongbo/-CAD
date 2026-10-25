#ifndef NctiDisplayBodyGroup_H
#define NctiDisplayBodyGroup_H
#include "NctiDisplayGroup.h"
#include "dcl_ncti_object.h"
namespace NCTI
{
	
	/**
	* @brief Grouping object
	*/
	class DECL_NCTI_OBJECT NctiDisplayBodyGroup : public NctiDisplayGroup
	{
		NCTI_DISPLAYOBJECT_FUNCTIONS(NctiDisplayBodyGroup)
	public:
		virtual void Init();
		virtual ~NctiDisplayBodyGroup();
	private:
		NCTI_READ_AND_WRITE_VERSION_FUN(1)
	};
}
#endif
