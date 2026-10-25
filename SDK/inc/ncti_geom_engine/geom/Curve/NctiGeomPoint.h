#ifndef NctiGeomPoint_H
#define NctiGeomPoint_H
#include "NctiGeomGeometry.h"

namespace NCTI
{
	class DECL_NCTI_GEOM_ENGINE NctiGeomPoint : public NctiGeomGeometry
	{
		NCTI_GEOM_FUNCTIONS(NctiGeomPoint)
	public:
		NctiGeomPoint(const NctiPosition& i_pt);
		virtual ~NctiGeomPoint();
	public:
		const NctiPosition& GetPt() { return m_pt; }
	private:
		NctiPosition m_pt;
	};
}
#endif
