#ifndef NctiGeomBoundedSurface_H
#define NctiGeomBoundedSurface_H
#include "NctiGeomSurface.h"
namespace NCTI
{
	class DECL_NCTI_GEOM_ENGINE NctiGeomBoundedSurface : public NctiGeomSurface
	{
		NCTI_GEOM_FUNCTIONS(NctiGeomBoundedSurface)
	public:
		NctiGeomBoundedSurface();
		virtual ~NctiGeomBoundedSurface();
		//
		NCTI_GE_ATT_DEF(Ncti_Integer, m_UDegree)
		NCTI_GE_ATT_DEF(Ncti_Integer, m_VDegree)
		NCTI_GE_ATT_DEF(std::vector<std::vector<NctiPosition>>, m_Poles)
		NCTI_GE_ATT_DEF(std::vector<std::vector<Ncti_Double>>, m_Weights)
	};
}
#endif
