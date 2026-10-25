#ifndef NctiGeomBoundedCurve_H
#define NctiGeomBoundedCurve_H
#include "NctiGeomCurve.h"
namespace NCTI
{
	class DECL_NCTI_GEOM_ENGINE NctiGeomBoundedCurve : public NctiGeomCurve
	{
		NCTI_GEOM_FUNCTIONS(NctiGeomBoundedCurve)
	public:
		NctiGeomBoundedCurve();
		virtual ~NctiGeomBoundedCurve();
	public:
		virtual void D0(Ncti_Double i_U, NctiPosition& o_P) const;
	private:
		
	};
}
#endif
