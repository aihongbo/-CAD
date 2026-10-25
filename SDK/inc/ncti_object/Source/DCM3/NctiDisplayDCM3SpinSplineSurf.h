#ifndef NctiDisplayDCM3SpinSplineSurf_H
#define NctiDisplayDCM3SpinSplineSurf_H
#include "dcl_ncti_object.h"
#include "NctiDisplayDCM3Geometry.h"
#include "NctiDCM3Def.h"
namespace NCTI
{
	class NctiDCMEXVec3d;
	class DECL_NCTI_OBJECT NctiDisplayDCM3SpinSplineSurf : public NctiDisplayDCM3Geometry
	{
		NCTI_DISPLAYOBJECT_FUNCTIONS(NctiDisplayDCM3SpinSplineSurf)
	public:
		virtual ~NctiDisplayDCM3SpinSplineSurf();
	public:
		virtual void Init();
		virtual EnumNctiResult UpdateDisplay();
	private:
		NCTI_READ_AND_WRITE_VERSION_FUN(1)
		ncti_DCM3_bs_data m_bs_data;
		NctiDCMEXVec3d m_basePoint;
		NctiDCMEXVec3d m_direction;
	public:
		void InitSpinSplineSurf(const ncti_DCM3_bs_data& i_bs_data, const NctiDCMEXVec3d& i_pos, const NctiDCMEXVec3d& i_dir);
	public:
		virtual ncti_DCM3_g_type identify()	const override { return NCTI_DCM3_SPIN_SPLINE_SURFACE; }
		virtual void transform(double i_mat[4][4]) override;
		virtual std::string describe() const override;

	public: 
		ncti_DCM3_bs_periodicity periodicity() const { return m_bs_data.periodicity; };
		const NctiDCMEXVec3d& base_point() const { return m_basePoint; };
		const NctiDCMEXVec3d& direction() const { return m_direction; };
		const ncti_DCM3_bs_data& data() { return m_bs_data; }
		void update_data(const ncti_DCM3_bs_data& i_data);
	};
}
#endif