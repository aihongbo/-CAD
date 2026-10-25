#ifndef NctiGeomCylindricalSurface_H
#define NctiGeomCylindricalSurface_H
#include "NctiGeomElementarySurface.h"
namespace NCTI
{
	class DECL_NCTI_GEOM_ENGINE NctiGeomCylindricalSurface : public NctiGeomElementarySurface
	{
		NCTI_GEOM_FUNCTIONS(NctiGeomCylindricalSurface)
	public:
		NctiGeomCylindricalSurface();
		virtual ~NctiGeomCylindricalSurface();
	public:
		NCTI_GE_ATT_DEF(Ncti_Double, m_radius)
	};
}
#endif
