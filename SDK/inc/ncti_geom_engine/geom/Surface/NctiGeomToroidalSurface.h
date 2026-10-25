#ifndef NctiGeomToroidalSurface_H
#define NctiGeomToroidalSurface_H
#include "NctiGeomElementarySurface.h"
namespace NCTI
{
	class DECL_NCTI_GEOM_ENGINE NctiGeomToroidalSurface : public NctiGeomElementarySurface
	{
		NCTI_GEOM_FUNCTIONS(NctiGeomToroidalSurface)
	public:
		NctiGeomToroidalSurface();
		virtual ~NctiGeomToroidalSurface();

		//
		NCTI_GE_ATT_DEF(Ncti_Double, m_MajorRadius)
		NCTI_GE_ATT_DEF(Ncti_Double, m_MinorRadius)
	};
}
#endif
