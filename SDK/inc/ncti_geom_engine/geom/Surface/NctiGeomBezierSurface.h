#ifndef NctiGeomBezierSurface_H
#define NctiGeomBezierSurface_H
#include "NctiGeomBoundedSurface.h"
namespace NCTI
{
	class DECL_NCTI_GEOM_ENGINE NctiGeomBezierSurface : public NctiGeomBoundedSurface
	{
		NCTI_GEOM_FUNCTIONS(NctiGeomBezierSurface)
	public:
		NctiGeomBezierSurface();
		virtual ~NctiGeomBezierSurface();
	public:
		NCTI_GE_ATT_DEF(Ncti_Boolean, m_urational)
		NCTI_GE_ATT_DEF(Ncti_Boolean, m_vrational)

	};
}
#endif
