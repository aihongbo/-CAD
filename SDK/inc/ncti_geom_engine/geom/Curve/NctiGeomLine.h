#ifndef NctiGeomLine_H
#define NctiGeomLine_H
#include "NctiGeomCurve.h"
namespace NCTI
{
	class DECL_NCTI_GEOM_ENGINE NctiGeomLine : public NctiGeomCurve
	{
		NCTI_GEOM_FUNCTIONS(NctiGeomLine)
	public:
		NctiGeomLine(const NctiPosition& i_pt, const NctiVector& i_dir);
		virtual ~NctiGeomLine();
	public:
		virtual void D0(Ncti_Double i_U, NctiPosition& o_pt) const;
	public:
		const NctiPosition& GetPt() { return m_pt; }
		const NctiVector& GetDir() { return m_dir; }
 	private:
		NctiPosition m_pt;
		NctiVector m_dir;
	};
}
#endif
