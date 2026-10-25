#ifndef NctiDisplayDCM3Circle_H
#define NctiDisplayDCM3Circle_H
#include "dcl_ncti_object.h"
#include "NctiDisplayDCM3Geometry.h"
#include "NctiDCM3Def.h"
namespace NCTI
{
	class NctiDCM3Variable;
	class NctiDCMEXVec3d;
	class DECL_NCTI_OBJECT NctiDisplayDCM3Circle : public NctiDisplayDCM3Geometry
	{
		friend class NctiDCM3Variable;
		NCTI_DISPLAYOBJECT_FUNCTIONS(NctiDisplayDCM3Circle)
	public:
		virtual ~NctiDisplayDCM3Circle();
	public:
		virtual void Init();
		virtual EnumNctiResult UpdateDisplay();
	private:
		NCTI_READ_AND_WRITE_VERSION_FUN(1)
		NctiDCMEXVec3d	m_fcentre;
		NctiDCMEXVec3d	m_faxis;
		double	m_fradius;
		double m_radius_offset;
	public:
		void InitCentre(const NctiDCMEXVec3d& i_pos);
		void InitAxis(const NctiDCMEXVec3d& i_axis);
		void InitRadius(Ncti_Double i_radius);
	public:
		virtual void transform(double i_mat[4][4]) override;
		virtual std::string describe() const override;
		virtual ncti_DCM3_g_type identify()	const override { return NCTI_DCM3_CIRCLE; }
		virtual double radius()	const  override { return m_fradius; }
		virtual void set_radius(double i_val) override;
		virtual void ResetLastTransform() override;
	public:
		const NctiDCMEXVec3d& centre()	const { return m_fcentre; }
		const NctiDCMEXVec3d& axis()	const { return m_faxis; }
		double radius_offset() const { return m_radius_offset; }
	};
}
#endif