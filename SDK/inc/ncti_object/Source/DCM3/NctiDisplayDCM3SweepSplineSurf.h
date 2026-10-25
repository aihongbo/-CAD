#ifndef NctiDisplayDCM3SweepSplineSurf_H
#define NctiDisplayDCM3SweepSplineSurf_H
#include "dcl_ncti_object.h"
#include "NctiDisplayDCM3Geometry.h"
#include "NctiDCM3Def.h"
namespace NCTI
{
	class NctiDCMEXVec3d;
	class DECL_NCTI_OBJECT NctiDisplayDCM3SweepSplineSurf : public NctiDisplayDCM3Geometry
	{
		NCTI_DISPLAYOBJECT_FUNCTIONS(NctiDisplayDCM3SweepSplineSurf)
	public:
		virtual ~NctiDisplayDCM3SweepSplineSurf();
	public:
		virtual void Init();
		virtual EnumNctiResult UpdateDisplay();
	private:
		NCTI_READ_AND_WRITE_VERSION_FUN(1)
		ncti_DCM3_bs_data m_bs_data;
		NctiDCMEXVec3d m_direction;
	public:
		void InitSweepSplineSurf(const ncti_DCM3_bs_data& i_bs_data, const NctiDCMEXVec3d& i_dir);
	public:
		virtual ncti_DCM3_g_type identify()	const override { return NCTI_DCM3_SWEEP_SPLINE_SURFACE; }
		virtual void transform(double i_mat[4][4]) override;
		virtual std::string describe() const override;

	public: 
		ncti_DCM3_bs_periodicity periodicity() const { return m_bs_data.periodicity; };
		const NctiDCMEXVec3d& direction() const { return m_direction; };
		const ncti_DCM3_bs_data& data() { return m_bs_data; }
		void update_data(const ncti_DCM3_bs_data& i_data);
	};
}
#endif