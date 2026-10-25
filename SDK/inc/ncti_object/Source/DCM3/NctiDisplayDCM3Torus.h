#ifndef NctiDisplayDCM3Torus_H
#define NctiDisplayDCM3Torus_H
#include "dcl_ncti_object.h"
#include "NctiDisplayDCM3Geometry.h"
#include "NctiAxis.h"
#include "NctiDCM3Def.h"
namespace NCTI
{
	class NctiDCM3Variable;
	class NctiDCMEXVec3d;
	class DECL_NCTI_OBJECT NctiDisplayDCM3Torus : public NctiDisplayDCM3Geometry
	{
		friend class NctiDCM3Variable;
		NCTI_DISPLAYOBJECT_FUNCTIONS(NctiDisplayDCM3Torus)
	public:
		virtual ~NctiDisplayDCM3Torus();
	public:
		virtual void Init();
		virtual EnumNctiResult UpdateDisplay();
	private:
		NCTI_READ_AND_WRITE_VERSION_FUN(1)
		NctiAxis m_axis;
		NctiDCMEXVec3d m_centre;
		double m_fmaj_radius;
		double m_fmin_radius;
		double m_maj_radius_offset;
		double m_min_radius_offset;
		double m_start_sec_angle;
		double m_end_sec_angle;
		double m_complete_angle;
	public:
		void InitAxis(const NctiAxis& i_axis);
		void InitMajRadius(const double i_major);
		void InitMinRadius(const double i_minor);
		void InitStartSecAngle(const double i_angle);
		void InitEndSecAngle(const double i_angle);
		void InitCompleteAngle(const double i_angle);
	public:
		virtual void set_radius(double i_radius) override;
		virtual double radius() const override { return m_fmaj_radius; }
		virtual double radius_offset() const override { return m_maj_radius_offset; }
		virtual void set_minor_radius(double i_radius) override;
		virtual double minor_radius() const override { return m_fmin_radius; }
		virtual double minor_radius_offset() const override { return m_min_radius_offset; }
		virtual ncti_DCM3_g_type identify() const override { return NCTI_DCM3_TORUS; }
		virtual std::string describe() const override;
		virtual void transform(double i_mat[4][4]) override;
		virtual void ResetLastTransform() override;
	public:
		NctiAxis Axis() const { return m_axis; }
		double StartSecAngle() const { return m_start_sec_angle; }
		double EndSecAngle() const { return m_end_sec_angle; }
		double CompleteAngle() const { return m_complete_angle; }
		NctiDCMEXVec3d centre() const; 
		NctiDCMEXVec3d normal() const; 
		double major_radius() const { return m_fmaj_radius; }
	};
}
#endif