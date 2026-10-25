#ifndef NctiGeomEllipse_H
#define NctiGeomEllipse_H
#include "NctiGeomConic.h"
namespace NCTI
{
	class DECL_NCTI_GEOM_ENGINE NctiGeomEllipse : public NctiGeomConic
	{
		NCTI_GEOM_FUNCTIONS(NctiGeomEllipse)
	public:
		NctiGeomEllipse() {};
		NctiGeomEllipse(const NctiPosition& i_pt,
			const NctiUnitVector& i_dir, 
			const NctiUnitVector& i_nor,
			Ncti_Double i_majorRadius,
			Ncti_Double i_minorRadius);
		virtual ~NctiGeomEllipse();
	public:
		virtual void D0(Ncti_Double i_U, NctiPosition& o_pt) const;
		Ncti_Double GetMajorRadius() { return m_majorRadius; }
		Ncti_Double GetMinorRadius() { return m_minorRadius; }

		NCTI_GE_ATT_DEF(Ncti_Double, m_majorRadius)
		NCTI_GE_ATT_DEF(Ncti_Double, m_minorRadius)
	};
}
#endif
