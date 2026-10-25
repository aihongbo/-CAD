#ifndef NctiDisplayDCM3Cone_H
#define NctiDisplayDCM3Cone_H
#include "dcl_ncti_object.h"
#include "NctiDisplayDCM3Geometry.h"
#include "NctiAxis.h"
#include "NctiDCM3Def.h"
namespace NCTI
{
	class NctiDCMEXVec3d;
	class NctiDCM3Variable;
	class DECL_NCTI_OBJECT NctiDisplayDCM3Cone : public NctiDisplayDCM3Geometry
	{
		friend class NctiDCM3Variable;
		NCTI_DISPLAYOBJECT_FUNCTIONS(NctiDisplayDCM3Cone)
	public:
		virtual ~NctiDisplayDCM3Cone();
	public:
		virtual void Init();
		virtual EnumNctiResult UpdateDisplay();
	private:
		NCTI_READ_AND_WRITE_VERSION_FUN(1)
		NctiDCMEXVec3d m_center;//圆锥底部圆心
		NctiDCMEXVec3d m_normal;//圆锥顶点向底部圆心的方向
		double m_radius;
		double m_fhalf_angle;//弧度
		double m_hafl_angle_offset;
	public:
		void InitPoint(const NctiDCMEXVec3d& i_center);
		void InitNormal(const NctiDCMEXVec3d& i_normal);
		void InitRadius(const double i_radius);
		void InitHalfAngle(const double i_angle);
	public:
		virtual ncti_DCM3_g_type identify() const override { return NCTI_DCM3_CONE; }
		virtual std::string describe() const override;
		virtual void transform(double i_mat[4][4]) override;
		virtual void ResetLastTransform() override;
	public:
		NctiDCMEXVec3d point() const { return m_center; }
		NctiDCMEXVec3d top() const;
		NctiDCMEXVec3d normal() const { return m_normal; }
		double radius() const { return m_radius; }
		double half_angle() const { return m_fhalf_angle; }
		void set_half_angle(double i_ang);
		double half_angle_offset() const { return m_hafl_angle_offset; }
	};
}
#endif