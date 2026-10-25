#ifndef NctiGeomGeometry_H
#define NctiGeomGeometry_H
#include "NctiGEObject.h"
namespace NCTI
{
	class DECL_NCTI_GEOM_ENGINE NctiGeomGeometry : public NctiGEObject
	{
		NCTI_GEOM_FUNCTIONS(NctiGeomGeometry)
	public:
		NctiGeomGeometry();
		virtual ~NctiGeomGeometry();
	};
}
#endif
