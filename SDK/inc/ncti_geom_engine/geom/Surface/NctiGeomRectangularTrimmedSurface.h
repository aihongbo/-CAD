#ifndef NctiGeomRectangularTrimmedSurface_H
#define NctiGeomRectangularTrimmedSurface_H
#include "NctiGeomBoundedSurface.h"
namespace NCTI
{
	class DECL_NCTI_GEOM_ENGINE NctiGeomRectangularTrimmedSurface : public NctiGeomBoundedSurface
	{
		NCTI_GEOM_FUNCTIONS(NctiGeomRectangularTrimmedSurface)
	public:
		NctiGeomRectangularTrimmedSurface();
		virtual ~NctiGeomRectangularTrimmedSurface(); 
	public:
		NCTI_GE_ATT_DEF(NctiGeomSurface*, m_basisSurf)
		NCTI_GE_ATT_DEF(Ncti_Double, m_utrim1)
		NCTI_GE_ATT_DEF(Ncti_Double, m_vtrim1)
		NCTI_GE_ATT_DEF(Ncti_Double, m_utrim2)
		NCTI_GE_ATT_DEF(Ncti_Double, m_vtrim2)
		NCTI_GE_ATT_DEF(Ncti_Boolean, m_isutrimmed)
		NCTI_GE_ATT_DEF(Ncti_Boolean, m_isvtrimmed)

	};
}
#endif
