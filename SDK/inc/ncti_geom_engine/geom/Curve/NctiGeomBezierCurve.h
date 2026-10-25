#ifndef NctiGeomBezierCurve_H
#define NctiGeomBezierCurve_H
#include "NctiGeomBoundedCurve.h"
namespace NCTI
{
	class DECL_NCTI_GEOM_ENGINE NctiGeomBezierCurve : public NctiGeomBoundedCurve
	{
		NCTI_GEOM_FUNCTIONS(NctiGeomBezierCurve)
	public:
		NctiGeomBezierCurve();
		NctiGeomBezierCurve(
			Ncti_Boolean i_rational,
			Ncti_Boolean i_closed,
			const std::vector<NctiPosition>& i_PoleVec,
			const std::vector<Ncti_Double>& i_WeightVec,
			Ncti_Double i_maxderivinv,
			Ncti_Boolean i_maxderivinvok);
		virtual ~NctiGeomBezierCurve();
	public:
		Ncti_Boolean GetRational() { return m_rational; }
		Ncti_Boolean GetClosed() { return m_closed; }
		const std::vector<NctiPosition>& GetPoles() { return m_PoleVec; }
		const std::vector<Ncti_Double>& GetWeights() { return m_WeightVec; }
		Ncti_Double GetMaxderivinv() { return m_maxderivinv; }
		Ncti_Boolean GetMaxderivinvok() { return m_maxderivinvok; }
	private:
		Ncti_Boolean m_rational;
		Ncti_Boolean m_closed;
		std::vector<NctiPosition> m_PoleVec;
		std::vector<Ncti_Double> m_WeightVec;
		Ncti_Double m_maxderivinv;
		Ncti_Boolean m_maxderivinvok;
	};
}
#endif
