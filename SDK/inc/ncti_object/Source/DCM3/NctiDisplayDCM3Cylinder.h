#ifndef NctiDisplayDCM3Cylinder_H
#define NctiDisplayDCM3Cylinder_H
#include "dcl_ncti_object.h"
#include "NctiDisplayDCM3Geometry.h"
#include "NctiDCM3Def.h"
#include "NctiAxis.h"
namespace NCTI
{
	class NctiDCMEXVec3d;
	class NctiDCM3Variable;
	class DECL_NCTI_OBJECT NctiDisplayDCM3Cylinder : public NctiDisplayDCM3Geometry
	{
		friend class NctiDCM3Variable;
		NCTI_DISPLAYOBJECT_FUNCTIONS(NctiDisplayDCM3Cylinder)
	public:
		virtual ~NctiDisplayDCM3Cylinder();
	public:
		virtual void Init();
		virtual EnumNctiResult UpdateDisplay();
	private:
		NCTI_READ_AND_WRITE_VERSION_FUN(1)
		NctiAxis m_axis;
		double m_fradius;
		double m_radius_offset;
		double m_height;
		double m_complete_angle;//弧度
	public:
		void InitAxis(NctiAxis i_axis);
		void InitRadius(double i_raidus);
		void InitHeight(double i_height);
		void InitCompleteAngle(double i_angle);
	public:
		virtual void transform(double i_mat[4][4]) override;
		virtual ncti_DCM3_g_type identify() const override { return NCTI_DCM3_CYLINDER; }
		virtual std::string describe() const override;
		virtual double radius() const override { return m_fradius; }
		virtual void set_radius(double i_val) override;
		virtual double radius_offset() const override { return m_radius_offset; }
		virtual void ResetLastTransform() override;
	public:
		NctiDCMEXVec3d base_point() const { NctiPosition pos = m_axis.GetPosition();  return NctiDCMEXVec3d(pos.x(), pos.y(), pos.z()); }
		NctiDCMEXVec3d normal() const { NctiVector normal = m_axis.GetNormal();  return NctiDCMEXVec3d(normal.x(), normal.y(), normal.z()); }
		NctiAxis axis() const { return m_axis; }
		double height() const { return m_height; }
		double complete_angle() const { return m_complete_angle; }
	};
}
#endif