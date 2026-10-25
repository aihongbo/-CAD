#ifndef NctiGeomUnKnownCurve_H
#define NctiGeomUnKnownCurve_H
#include "NctiGeomCurve.h"

namespace NCTI
{
	class DECL_NCTI_GEOM_ENGINE NctiGeomUnKnownCurve : public NctiGeomCurve
	{
		NCTI_GEOM_FUNCTIONS(NctiGeomUnKnownCurve)
	public:
		NctiGeomUnKnownCurve();
		virtual ~NctiGeomUnKnownCurve();
	public:
		virtual void D0(Ncti_Double i_U, NctiPosition& o_pt) const {}
	public:
		void Value(Ncti_Double i_U, NctiPosition& o_pt) const;
	};
}
#endif
