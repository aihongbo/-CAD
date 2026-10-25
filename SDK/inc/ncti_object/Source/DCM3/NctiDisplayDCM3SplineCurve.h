#ifndef NctiDisplayDCM3SplineCurve_H
#define NctiDisplayDCM3SplineCurve_H
#include "dcl_ncti_object.h"
#include "NctiDisplayDCM3Geometry.h"
#include "NctiDisplayDCM3Point.h"
#include "NctiDCM3Def.h"
namespace NCTI
{
	class NctiDCMEXVec3d;
	class DECL_NCTI_OBJECT NctiDisplayDCM3SplineCurve : public NctiDisplayDCM3Geometry
	{
		NCTI_DISPLAYOBJECT_FUNCTIONS(NctiDisplayDCM3SplineCurve)
	public:
		virtual ~NctiDisplayDCM3SplineCurve();
	public:
		virtual void Init();
		virtual EnumNctiResult UpdateDisplay();
	private:
		NCTI_READ_AND_WRITE_VERSION_FUN(1)
		int m_degree;
		std::vector<NctiDisplayDCM3Point*> m_points;
		ncti_DCM3_bs_periodicity m_fperiodicity;
		bool m_frigid;
		bool m_interp;//插值样条
	public:
		void InitSplineCurve(const std::vector<NctiDisplayDCM3Point*>& i_points,
			ncti_DCM3_bs_periodicity i_periodicity = NCTI_DCM3_BS_PERIODICITY_NON_PER,
			Ncti_Integer i_degree = 3, Ncti_Boolean i_rigid = false, Ncti_Boolean i_interp = false);
	public:
		virtual ncti_DCM3_g_type identify()	const override { return NCTI_DCM3_SPLINE_CURVE; }
		virtual void transform(double i_mat[4][4]) override;
		virtual std::string describe() const override;
	public: 
		bool IsInterp() const { return m_interp; }
		ncti_DCM3_bs_periodicity periodicity() const { return m_fperiodicity; }
		void setPeriodicity(ncti_DCM3_bs_periodicity i_per);
		int degree() const { return m_degree; }
		void setDegree(int i_deg);
		std::vector<NctiDisplayDCM3Point*> points() const { return m_points; }
		void setPoints(const std::vector<NctiDisplayDCM3Point*>& i_pPointVec);
		NCTI_G_NODE nth_point(int i_index) const;
		NCTI_G_NODE start_pt() const;
		NCTI_G_NODE end_pt() const;
		
	};
}
#endif