#ifndef NctiDisplayDCM3Ellipse_H
#define NctiDisplayDCM3Ellipse_H
#include "dcl_ncti_object.h"
#include "NctiDisplayDCM3Geometry.h"
#include "NctiDCM3Def.h"
namespace NCTI
{
	class NctiDCM3Variable;
	class NctiDCMEXVec3d;
	class DECL_NCTI_OBJECT NctiDisplayDCM3Ellipse : public NctiDisplayDCM3Geometry
	{
		friend class NctiDCM3Variable;
		NCTI_DISPLAYOBJECT_FUNCTIONS(NctiDisplayDCM3Ellipse)
	public:
		virtual ~NctiDisplayDCM3Ellipse();
	public:
		virtual void Init();
		virtual EnumNctiResult UpdateDisplay();
	private:
		NCTI_READ_AND_WRITE_VERSION_FUN(1)
		NctiDCMEXVec3d m_fcentre;
		NctiDCMEXVec3d m_fnormal;		//direction of plane normal
		NctiDCMEXVec3d m_fmajor_axis;	//direction of major axis
		double m_fmaj_radius;
		double m_fmin_radius;
		double m_maj_radius_offset;
		double m_min_radius_offset;
		Ncti_Double m_rigid;
	public:
		void InitCentre(const NctiDCMEXVec3d& i_pos);
		void InitNoraml(const NctiDCMEXVec3d& i_normal);
		void InitMajorAxis(const NctiDCMEXVec3d& i_axis);
		void InitMajRadius(Ncti_Double i_radius);
		void InitMinRadius(Ncti_Double i_radius);
		void InitRigid(Ncti_Boolean i_rigid);
	public:
		virtual ncti_DCM3_g_type identify()	const override { return NCTI_DCM3_ELLIPSE; }
		virtual void transform(double i_mat[4][4]) override;
		virtual std::string describe() const override;
		virtual void set_radius(double i_radius) override;
		virtual double radius() const override { return m_fmaj_radius; }
		virtual double radius_offset() const override { return m_maj_radius_offset; }
		virtual void set_minor_radius(double i_radius) override;
		virtual double minor_radius() const override { return m_fmin_radius; }
		virtual double minor_radius_offset() const override { return m_min_radius_offset; }
		virtual void ResetLastTransform() override;
	public:
		NctiDCMEXVec3d centre() const { return m_fcentre; }
		NctiDCMEXVec3d normal() const { return m_fnormal; }
		NctiDCMEXVec3d major_axis() const { return m_fmajor_axis; }
		NctiDCMEXVec3d minor_axis() const { return m_fnormal * m_fmajor_axis; }
		double major_radius() const { return m_fmaj_radius; }
		Ncti_Double rigid() const { return m_rigid; }
		void evaluator(double o_pt[3], double o_firstDer[3], double o_secondDer[3], double i_t) const;
	};
}
#endif