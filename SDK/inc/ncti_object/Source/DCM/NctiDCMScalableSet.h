#ifndef NctiDCMScalableSet_H
#define NctiDCMScalableSet_H
#include "dcl_ncti_object.h"
#include "NctiDCMSet.h"
#include "NctiDCMDef.h"
namespace NCTI
{
	class DECL_NCTI_OBJECT NctiDCMScalableSet : public NctiDCMSet
	{
		NCTI_DISPLAYOBJECT_FUNCTIONS(NctiDCMScalableSet)
	public:
		virtual ~NctiDCMScalableSet();
	public:
		virtual void Init();
		virtual EnumNctiResult UpdateDisplay();
	private:
		NCTI_READ_AND_WRITE_VERSION_FUN(1)
		Ncti_Double	m_fscaling_transform;
		NCTI_G_NODE m_fscaling_centre;
	public:
		virtual std::string describe() const override;
		virtual ncti_DCM_g_type identify()	const override { return NCTI_DCM_SCALABLE_SET; }
		virtual NctiDCMEXGType type() const override { return EX_SCALABLE_SET; }
		virtual void transform(double i_mat[3][3]) override;
	public:
		double scaling_transform() const { return m_fscaling_transform; }
		void set_scaling_transform(double i_scaleFactor) { m_fscaling_transform = i_scaleFactor; };
		NCTI_G_NODE scaling_centre() const { return m_fscaling_centre; }
		void set_scaling_centre(NCTI_G_NODE i_gn) { m_fscaling_centre = i_gn; };
	};
}
#endif