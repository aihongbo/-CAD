#ifndef NctiGeomConicalSurface_H
#define NctiGeomConicalSurface_H
#include "NctiGeomElementarySurface.h"
namespace NCTI
{
	class DECL_NCTI_GEOM_ENGINE NctiGeomConicalSurface : public NctiGeomElementarySurface
	{
		NCTI_GEOM_FUNCTIONS(NctiGeomConicalSurface)
	public:
		NctiGeomConicalSurface();
		virtual ~NctiGeomConicalSurface();

		//
		NCTI_GE_ATT_DEF(Ncti_Double, m_Radius)
		NCTI_GE_ATT_DEF(Ncti_Double, m_SemiAngle)
	};
}
#endif
