#ifndef NctiGeomSurface_H
#define NctiGeomSurface_H
#include "NctiGeomGeometry.h"
namespace NCTI
{
	class DECL_NCTI_GEOM_ENGINE NctiGeomSurface : public NctiGeomGeometry
	{
		NCTI_GEOM_FUNCTIONS(NctiGeomSurface)
	public:
		NctiGeomSurface();
		virtual ~NctiGeomSurface();
	public:
		void Value(Ncti_Double i_U, Ncti_Double i_V, NctiPosition& o_P);
	public:
		virtual void D0(Ncti_Double i_U, Ncti_Double i_V, NctiPosition& o_P) {}

		//
		NCTI_GE_ATT_DEF(Ncti_Double, m_UMin)
		NCTI_GE_ATT_DEF(Ncti_Double, m_UMax)
		NCTI_GE_ATT_DEF(Ncti_Double, m_VMin)
		NCTI_GE_ATT_DEF(Ncti_Double, m_VMax)
	};
}
#endif
