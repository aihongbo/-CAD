#ifndef NctiDisplayDCM3Sphere_H
#define NctiDisplayDCM3Sphere_H
#include "dcl_ncti_object.h"
#include "NctiDisplayDCM3Geometry.h"
#include "NctiAxis.h"
#include "NctiDCM3Def.h"
namespace NCTI
{
	class NctiDCM3Variable;
	class NctiDCMEXVec3d;
	class DECL_NCTI_OBJECT NctiDisplayDCM3Sphere : public NctiDisplayDCM3Geometry
	{
		friend class NctiDCM3Variable;
		NCTI_DISPLAYOBJECT_FUNCTIONS(NctiDisplayDCM3Sphere)
	public:
		virtual ~NctiDisplayDCM3Sphere();
	public:
		virtual void Init();
		virtual EnumNctiResult UpdateDisplay();
	private:
		NCTI_READ_AND_WRITE_VERSION_FUN(1)
		double m_fradius;
		double m_radius_offset;
		NctiDCMEXVec3d m_centre;
		NctiAxis m_axis;
		double m_angle1;//弧度
		double m_angle2;
		double m_angle3;
	public:
		void InitRadius(double i_radius);
		void InitAxis(const NctiAxis& i_axis);
		void InitAngle(const double i_a1, const double i_a2, const double i_a3);
	public:
		virtual double radius() const override { return m_fradius; }
		virtual void set_radius(double i_radius) override;
		virtual double radius_offset() const override { return m_radius_offset; }
		virtual ncti_DCM3_g_type identify() const override { return NCTI_DCM3_SPHERE; }
		virtual std::string describe() const override;
		virtual void transform(double i_mat[4][4]) override;
		virtual void ResetLastTransform() override;
	public:
		NctiAxis Axis() const { return m_axis; }
		void Angle(double& a1, double& a2, double& a3) const { a1 = m_angle1, a2 = m_angle2, a3 = m_angle3; }
		NctiDCMEXVec3d centre() const { return m_centre; }
	};
}
#endif