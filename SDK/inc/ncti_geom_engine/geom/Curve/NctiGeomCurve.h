#ifndef NctiGeomCurve_H
#define NctiGeomCurve_H
#include "NctiGeomGeometry.h"

namespace NCTI
{
	class DECL_NCTI_GEOM_ENGINE NctiGeomCurve : public NctiGeomGeometry
	{
		NCTI_GEOM_FUNCTIONS(NctiGeomCurve)
	public:
		NctiGeomCurve();
		virtual ~NctiGeomCurve();
	public:
		virtual void D0(Ncti_Double i_U, NctiPosition& o_pt) const = 0;
	public:
		void Value(Ncti_Double i_U, NctiPosition& o_pt) const;
	public:
		NCTI_GE_ATT_DEF(Ncti_Double, m_UMin)
		NCTI_GE_ATT_DEF(Ncti_Double, m_UMax)
	};
}
#endif
