#ifndef NctiGeomTrimmedCurve_H
#define NctiGeomTrimmedCurve_H
#include "NctiGeomBoundedCurve.h"
namespace NCTI
{
	class DECL_NCTI_GEOM_ENGINE NctiGeomTrimmedCurve : public NctiGeomBoundedCurve
	{
		NCTI_GEOM_FUNCTIONS(NctiGeomTrimmedCurve)
	public:
		NctiGeomTrimmedCurve();
		virtual ~NctiGeomTrimmedCurve();
	public:
		virtual void D0(Ncti_Double i_U, NctiPosition& o_P) const;
	public:
		NCTI_GE_ATT_DEF(NctiGeomCurve*, m_basisCurve)
		NCTI_GE_ATT_DEF(Ncti_Double, m_uTrim1)
		NCTI_GE_ATT_DEF(Ncti_Double, m_uTrim2)
	};
}
#endif
