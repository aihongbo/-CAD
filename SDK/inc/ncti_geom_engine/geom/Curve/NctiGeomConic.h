#ifndef NctiGeomConic_H
#define NctiGeomConic_H
#include "NctiGeomCurve.h"
namespace NCTI
{
	class DECL_NCTI_GEOM_ENGINE NctiGeomConic : public NctiGeomCurve
	{
		NCTI_GEOM_FUNCTIONS(NctiGeomConic)
	public:
		NctiGeomConic() {};
		NctiGeomConic(const NctiPosition& i_pt, const NctiUnitVector& i_xdir, const NctiUnitVector& i_ydir);
		virtual ~NctiGeomConic();
	public:
		virtual void D0(Ncti_Double i_U, NctiPosition& o_pt) const;
	public:
		const NctiPosition& GetPt() { return m_pt; }
		const NctiUnitVector& GetXDir() { return m_XDir; }
		const NctiUnitVector& GetYDir() { return m_YDir; }
	public:
		NCTI_GE_ATT_DEF(NctiPosition, m_pt)
		NCTI_GE_ATT_DEF(NctiUnitVector, m_XDir)
		NCTI_GE_ATT_DEF(NctiUnitVector, m_YDir)
	};
}
#endif
