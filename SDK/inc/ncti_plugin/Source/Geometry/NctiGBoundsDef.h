#ifndef NctiGBoundsDef_H
#define NctiGBoundsDef_H
#include "dcl_ncti_plugin.h"
#include "ncti_base.h"

namespace NCTI
{
	class DECL_NCTI_PLUGIN NctiGeomBounds : public NCTI_BASE_CLASS
	{
	public:
		NctiGeomBounds();

		void SetBoundsU(Ncti_Double boundsu1, Ncti_Double boundsu2);
		void SetBoundsV(Ncti_Double boundsv1, Ncti_Double boundsv2);
		void GetBoundsU(Ncti_Double& boundsu1, Ncti_Double& boundsu2) const;
		void GetBoundsV(Ncti_Double& boundsv1, Ncti_Double& boundsv2) const;
	private:
		//UV边界
		Ncti_Double m_BoundsU1;
		Ncti_Double m_BoundsU2;
		Ncti_Double m_BoundsV1;
		Ncti_Double m_BoundsV2;
	};

    enum NctiParamEnd
    {
        NCTI_PARAM_END_PERIODIC = 0,
        NCTI_PARAM_END_NATURAL = 1,
        NCTI_PARAM_END_CLAMPED_VEC = 2,
        NCTI_PARAM_END_CLAMPED_BCURVE = 3,
    };
}
#endif // !NctiGBoundsDef_H
