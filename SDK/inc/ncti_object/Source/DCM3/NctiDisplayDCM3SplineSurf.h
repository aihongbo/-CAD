#ifndef NctiDisplayDCM3SplineSurf_H
#define NctiDisplayDCM3SplineSurf_H
#include "dcl_ncti_object.h"
#include "NctiDisplayDCM3Geometry.h"
#include "NctiDisplayDCM3Point.h"
#include "NctiDCM3Def.h"
namespace NCTI
{
	class NctiDCMEXVec3d;
	class DECL_NCTI_OBJECT NctiDisplayDCM3SplineSurf : public NctiDisplayDCM3Geometry
	{
		NCTI_DISPLAYOBJECT_FUNCTIONS(NctiDisplayDCM3SplineSurf)
	public:
		virtual ~NctiDisplayDCM3SplineSurf();
	public:
		virtual void Init();
		virtual EnumNctiResult UpdateDisplay();
	private:
		NCTI_READ_AND_WRITE_VERSION_FUN(1)
			ncti_DCM3_bs_surface_data m_bs_surf_data;

	public:
		void InitSplineSurf(const ncti_DCM3_bs_surface_data& i_bs_surf_data);
	public:
		virtual ncti_DCM3_g_type identify()	const override { return NCTI_DCM3_SPLINE_SURFACE; }
		virtual void transform(double i_mat[4][4]) override;
		virtual std::string describe() const override;

	public: 
		ncti_DCM3_bs_periodicity u_periodicity() const { return m_bs_surf_data.u_periodicity; }
		ncti_DCM3_bs_periodicity v_periodicity() const { return m_bs_surf_data.v_periodicity; }
		int u_cp_n() const { return m_bs_surf_data.u_cp_n; }
		int v_cp_n() const { return m_bs_surf_data.v_cp_n; }
		int u_degree() const { return m_bs_surf_data.u_degree; }
		int v_degree() const { return m_bs_surf_data.v_degree; }
		const std::vector<double>& weights() const { return m_bs_surf_data.cp_weights; }
		std::vector<NctiDCMEXVec3d> cp_points() const;
		const ncti_DCM3_bs_surface_data& data() { return m_bs_surf_data; }
		void update_data(const ncti_DCM3_bs_surface_data& i_data);
	};
}
#endif