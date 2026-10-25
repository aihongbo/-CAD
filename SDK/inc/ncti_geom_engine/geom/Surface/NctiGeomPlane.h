#ifndef NctiGeomPlane_H
#define NctiGeomPlane_H
#include "NctiGeomElementarySurface.h"
namespace NCTI
{
	class DECL_NCTI_GEOM_ENGINE NctiGeomPlane : public NctiGeomElementarySurface
	{
		NCTI_GEOM_FUNCTIONS(NctiGeomPlane)
	public:
		NctiGeomPlane();
		virtual ~NctiGeomPlane();
	public:
		void D0(Ncti_Double i_U, Ncti_Double i_V, NctiPosition& o_P) override;
	};
}
#endif
