#ifndef NctiTopoEdge_H
#define NctiTopoEdge_H
#include "NctiTopoCell.h"
namespace NCTI
{
	class NctiTopoFace;
	class NctiGeomCurve;
	class NctiTopoEdgeCurve;
	class DECL_NCTI_GEOM_ENGINE NctiTopoEdge : public NctiTopoCell
	{
		NCTI_GEOM_FUNCTIONS(NctiTopoEdge)
	public:
		NctiTopoEdge();
		virtual ~NctiTopoEdge();
	protected:
		virtual void OnAddShape(NctiTopoShape* i_pShape);
	public:
		void SetRange(Ncti_Double i_first, Ncti_Double i_last);
		void AddTopoEdgeCurve(NctiTopoEdgeCurve* i_pEdgeCurve);
	public:
		void GetRange(Ncti_Double& o_first, Ncti_Double& o_last) { o_first = m_First; o_last = m_Last; }
		std::vector<NctiTopoFace*> GetTopoFace();
	public:
		void FirstPt(NctiPosition& o_pt);
		void LastPt(NctiPosition& o_pt);
	public:
		NCTI_GE_ATT_DEF(NctiGeomCurve*, m_GeomCurve)
		NCTI_GE_ATT_DEF(std::vector<NctiTopoEdgeCurve*>, m_EdgeCurveVec)
	private:
		Ncti_Double m_First;
		Ncti_Double m_Last;
	};
}
#endif
