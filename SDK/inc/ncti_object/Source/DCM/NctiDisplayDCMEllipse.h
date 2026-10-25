#ifndef NctiDisplayDCMEllipse_H
#define NctiDisplayDCMEllipse_H
#include "dcl_ncti_object.h"
#include "NctiDisplayDCMGeometry.h"
#include "NctiDCMDef.h"
namespace NCTI
{
	class NctiDCMEXVec2d;
	class DECL_NCTI_OBJECT NctiDisplayDCMEllipse : public NctiDisplayDCMGeometry
	{
		NCTI_DISPLAYOBJECT_FUNCTIONS(NctiDisplayDCMEllipse)
	public:
		virtual ~NctiDisplayDCMEllipse();
	public:
		virtual void Init();
		virtual EnumNctiResult UpdateDisplay(); 
	private:
		NCTI_READ_AND_WRITE_VERSION_FUN(1)
		NctiDCMEXVec2d	m_fcentre;
		NctiDCMEXVec2d	m_fdirection;
		double	m_fmaj_radius;
		double	m_fmin_radius;
		double  m_fmaj_radius_offset;
		double  m_fmin_radius_offset;
	public:
		void InitCenter(const NctiDCMEXVec2d& i_pos);
		void InitDirection(const NctiDCMEXVec2d& i_dir);
		void InitMajRadius(Ncti_Double i_radius);
		void InitMinRadius(Ncti_Double i_radius);
	public:
		virtual std::string describe() const override;
		virtual ncti_DCM_g_type identify()	const override { return NCTI_DCM_ELLIPSE; }
		virtual NctiDCMEXGType type() const override { return EX_ELLIPSE; }
		virtual void transform(Ncti_Double i_mat[3][3]) override;
	public:
		const NctiDCMEXVec2d& centre()	const { return m_fcentre; }
		const NctiDCMEXVec2d& direction()	const { return m_fdirection; }
		double maj_radius()	const { return m_fmaj_radius; }
		double min_radius()	const { return m_fmin_radius; }
		double maj_radius_offset()	const { return m_fmaj_radius_offset; }
		double min_radius_offset()	const { return m_fmin_radius_offset; }
		void set_maj_radius(double i_val); 
		void set_min_radius(double i_val);
	};
}
#endif