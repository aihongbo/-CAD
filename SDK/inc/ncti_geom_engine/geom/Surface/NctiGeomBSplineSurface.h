#ifndef NctiGeomBSplineSurface_H
#define NctiGeomBSplineSurface_H
#include "NctiGeomBoundedSurface.h"
namespace NCTI
{
	class DECL_NCTI_GEOM_ENGINE NctiGeomBSplineSurface : public NctiGeomBoundedSurface
	{
		NCTI_GEOM_FUNCTIONS(NctiGeomBSplineSurface)
	public:
		NctiGeomBSplineSurface();
		virtual ~NctiGeomBSplineSurface();
	public:
		NCTI_GE_ATT_DEF(Ncti_Boolean, m_urational)
		NCTI_GE_ATT_DEF(Ncti_Boolean, m_vrational)

		//
		NCTI_GE_ATT_DEF(std::vector<Ncti_Double>, m_UKnots)
		NCTI_GE_ATT_DEF(std::vector<Ncti_Double>, m_VKnots)
		NCTI_GE_ATT_DEF(std::vector<Ncti_Integer>, m_UMultiplicity)
		NCTI_GE_ATT_DEF(std::vector<Ncti_Integer>, m_VMultiplicity)
	};
}
#endif
