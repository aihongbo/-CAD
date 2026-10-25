#ifndef NctiGeomCircle_H
#define NctiGeomCircle_H
#include "NctiGeomConic.h"
namespace NCTI
{
	class DECL_NCTI_GEOM_ENGINE NctiGeomCircle : public NctiGeomConic
	{
		NCTI_GEOM_FUNCTIONS(NctiGeomCircle)
	public:
		NctiGeomCircle() {};
		NctiGeomCircle(const NctiPosition& i_pt, 
			const NctiUnitVector& i_xdir,
			const NctiUnitVector& i_ydir,
			Ncti_Double i_radius);
		virtual ~NctiGeomCircle();
	public:
		virtual void D0(Ncti_Double i_U, NctiPosition& o_pt) const;
	public:
		Ncti_Double GetRadius() { return m_radius; }
		NCTI_GE_ATT_DEF(Ncti_Double, m_radius)
	};
}
#endif
