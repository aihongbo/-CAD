#ifndef NctiDisplayDCMCircle_H
#define NctiDisplayDCMCircle_H
#include "dcl_ncti_object.h"
#include "NctiDisplayDCMGeometry.h"
#include "NctiDCMDef.h"
namespace NCTI
{
	class NctiDCMEXVec2d;
	class DECL_NCTI_OBJECT NctiDisplayDCMCircle : public NctiDisplayDCMGeometry
	{
		NCTI_DISPLAYOBJECT_FUNCTIONS(NctiDisplayDCMCircle)
	public:
		virtual ~NctiDisplayDCMCircle();
	public:
		virtual void Init();
		virtual EnumNctiResult UpdateDisplay();
	private:
		NCTI_READ_AND_WRITE_VERSION_FUN(1)
		NctiDCMEXVec2d	m_fcentre;
		double	m_fradius;
		double m_radius_offset;
	public:
		void InitCenter(const NctiDCMEXVec2d& i_pos);
		void InitRadius(Ncti_Double i_radius);
	public:
		virtual std::string describe() const override;
		virtual ncti_DCM_g_type identify()	const override { return NCTI_DCM_CIRCLE; }
		virtual NctiDCMEXGType type() const override { return EX_CIRCLE; }
		virtual void transform(double i_mat[3][3]) override;
		virtual void ResetLastTransform() override;
	public:
		void set_radius(double i_radius) ;
		double radius() const { return m_fradius; }
		double radius_offset() const;
		const NctiDCMEXVec2d& centre()	const { return m_fcentre; }
	};
}
#endif