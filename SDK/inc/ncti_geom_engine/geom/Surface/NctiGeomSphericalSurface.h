#ifndef NctiGeomSphericalSurface_H
#define NctiGeomSphericalSurface_H
#include "NctiGeomElementarySurface.h"
namespace NCTI
{
	class DECL_NCTI_GEOM_ENGINE NctiGeomSphericalSurface : public NctiGeomElementarySurface
	{
		NCTI_GEOM_FUNCTIONS(NctiGeomSphericalSurface)
	public:
		NctiGeomSphericalSurface();
		virtual ~NctiGeomSphericalSurface();

		//
		NCTI_GE_ATT_DEF(Ncti_Double, m_Radius)
	};
}
#endif
