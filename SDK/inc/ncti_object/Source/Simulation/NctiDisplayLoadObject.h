#ifndef NctiDisplayLoadObject_H
#define NctiDisplayLoadObject_H
#include "ncti_base.h"
#include "dcl_ncti_object.h"
#include "NctiDisplayBasePhysicalObj.h"
namespace NCTI
{
	class NctiDisplayGridMesh;
	
	/**
	* @brief The load object
	*/
	class DECL_NCTI_OBJECT NctiDisplayLoadObject : public NctiDisplayBasePhysicalObj
	{
		NCTI_DISPLAYOBJECT_FUNCTIONS(NctiDisplayLoadObject)
	public:
		virtual ~NctiDisplayLoadObject();
	public:
		virtual void Init();

	private:
		NCTI_READ_AND_WRITE_VERSION_FUN(1)
	};
}
#endif
