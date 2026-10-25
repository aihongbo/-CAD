#ifndef NctiGeomElementarySurface_H
#define NctiGeomElementarySurface_H
#include "NctiGeomSurface.h"
namespace NCTI
{
	class DECL_NCTI_GEOM_ENGINE NctiGeomElementarySurface : public NctiGeomSurface
	{
		NCTI_GEOM_FUNCTIONS(NctiGeomElementarySurface)
	public:
		NctiGeomElementarySurface();
		virtual ~NctiGeomElementarySurface();
	public:
		NCTI_GE_ATT_DEF(NctiPosition, m_pt)
		NCTI_GE_ATT_DEF(NctiUnitVector, m_XDir)
		NCTI_GE_ATT_DEF(NctiUnitVector, m_YDir)
	
	};
}
#endif
