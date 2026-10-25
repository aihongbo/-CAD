#ifndef NctiDisplayDCM3Plane_H
#define NctiDisplayDCM3Plane_H
#include "dcl_ncti_object.h"
#include "NctiDisplayDCM3Geometry.h"
#include "NctiDCM3Def.h"
namespace NCTI
{
	class NctiDCMEXVec3d;
	class DECL_NCTI_OBJECT NctiDisplayDCM3Plane : public NctiDisplayDCM3Geometry
	{
		NCTI_DISPLAYOBJECT_FUNCTIONS(NctiDisplayDCM3Plane)
	public:
		virtual ~NctiDisplayDCM3Plane();
	public:
		virtual void Init();
		virtual EnumNctiResult UpdateDisplay();
	private:
		NCTI_READ_AND_WRITE_VERSION_FUN(1)
		NctiDCMEXVec3d m_fbase_point;
		NctiDCMEXVec3d m_fnormal;
	public:
		void InitBasePoint(NctiDCMEXVec3d& b);
		void InitNormal(NctiDCMEXVec3d& n);
	public:
		virtual ncti_DCM3_g_type identify() const override { return NCTI_DCM3_PLANE; }
		virtual void transform(double i_mat[4][4]) override;
		virtual std::string describe() const override;
	public:
		NctiDCMEXVec3d base_point() const { return m_fbase_point; }
		NctiDCMEXVec3d normal()	const { return m_fnormal; }
		void copy(NctiDisplayDCM3Plane& i_plane) { m_fbase_point = i_plane.base_point(); m_fnormal = i_plane.normal(); }
	};
}
#endif