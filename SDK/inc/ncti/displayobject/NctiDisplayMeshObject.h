#ifndef NctiDisplayMeshObject_H
#define NctiDisplayMeshObject_H
#include "NctiDisplayGModelObject.h"
#include "ncti_include.h"
namespace NCTI
{
	/**
	* @brief mesh object class
	* @details Base class of mesh object
	* @see NctiDisplayGModelObject
	*/
	class DECL_NCTI NctiDisplayMeshObject : public NctiDisplayGModelObject
	{
		NCTI_DISPLAYOBJECT_FUNCTIONS(NctiDisplayMeshObject)

	public:
		virtual ~NctiDisplayMeshObject();

    private:
        NCTI_READ_AND_WRITE_VERSION_FUN(1)
	};
}

#endif


