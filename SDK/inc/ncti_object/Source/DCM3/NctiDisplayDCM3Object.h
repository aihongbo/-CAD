#ifndef NctiDisplayDCM3Object_H
#define NctiDisplayDCM3Object_H
#include "dcl_ncti_object.h"
#include "NctiDisplayGModelObject.h"
namespace NCTI
{
	/**
	* @brief the base class of 3d constraint object
	* @details create a constraint object
	* @see NctiDisplayGModelObject
	*/
	class DECL_NCTI_OBJECT NctiDisplayDCM3Object : public NctiDisplayGModelObject
	{
		NCTI_DISPLAYOBJECT_FUNCTIONS(NctiDisplayDCM3Object)
			//NCTI_DISPLAYOBJECT_REQUIRE_INSTANCE_REDRAW
	public:
		virtual ~NctiDisplayDCM3Object();
	public:
		virtual void Init();
		virtual EnumNctiResult UpdateDisplay();
	private:
		NCTI_READ_AND_WRITE_VERSION_FUN(1)
	};
}
#endif
