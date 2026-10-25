#ifndef NctiDCMUniScalableSet_H
#define NctiDCMUniScalableSet_H
#include "dcl_ncti_object.h"
#include "NctiDCMScalableSet.h"
#include "NctiDCMDef.h"
namespace NCTI
{
	class DECL_NCTI_OBJECT NctiDCMUniScalableSet : public NctiDCMScalableSet
	{
		NCTI_DISPLAYOBJECT_FUNCTIONS(NctiDCMUniScalableSet)
	public:
		virtual ~NctiDCMUniScalableSet();
	public:
		virtual void Init();
		virtual EnumNctiResult UpdateDisplay();
	private:
		NCTI_READ_AND_WRITE_VERSION_FUN(1)
		NctiDCMEXVec2d m_fscaling_direction;
	public:
		virtual std::string describe() const override;
		virtual ncti_DCM_g_type identify()	const override { return NCTI_DCM_UNI_SCALABLE_SET; }
		virtual NctiDCMEXGType type() const override { return EX_UNI_SCALABLE_SET; }
		virtual void transform(double i_mat[3][3]) override;

	public:
		NctiDCMEXVec2d scaling_direction() const { return m_fscaling_direction; }
		void set_scaling_direction(const NctiDCMEXVec2d& i_dir); 
	};
}
#endif