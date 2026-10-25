#ifndef NctiTopoEdgeCurve_H
#define NctiTopoEdgeCurve_H
#include "NctiTopoCell.h"
namespace NCTI
{
	class NctiTopoFace;
	class NctiGeomCurve;
	class NctiTopoEdge;
	class DECL_NCTI_GEOM_ENGINE NctiTopoEdgeCurve : public NctiGEObject
	{
		NCTI_GEOM_FUNCTIONS(NctiTopoEdgeCurve)
	public:
		NctiTopoEdgeCurve();
		virtual ~NctiTopoEdgeCurve();
	public:
		NCTI_GE_ATT_DEF(NctiTopoFace*, m_TopoFace)
		NCTI_GE_ATT_DEF(Ncti_Orientation, m_Orientation)
		NCTI_GE_ATT_DEF(NctiTopoEdge*, m_TopoEdge)
	};
}
#endif
