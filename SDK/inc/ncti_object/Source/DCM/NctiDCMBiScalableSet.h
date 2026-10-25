#ifndef NctiDCMBiScalableSet_H
#define NctiDCMBiScalableSet_H
#include "dcl_ncti_object.h"
#include "NctiDCMUniScalableSet.h"
#include "NctiDCMDef.h"
namespace NCTI
{
	class DECL_NCTI_OBJECT NctiDCMBiScalableSet : public NctiDCMUniScalableSet
	{
		NCTI_DISPLAYOBJECT_FUNCTIONS(NctiDCMBiScalableSet)
	public:
		virtual ~NctiDCMBiScalableSet();
	public:
		virtual void Init();
		virtual EnumNctiResult UpdateDisplay();
	private:
		NCTI_READ_AND_WRITE_VERSION_FUN(1)
		Ncti_Double	m_fscaling_transform1;
		Ncti_Double	m_fscaling_transform2;
	public:
		virtual std::string describe() const override;
		virtual ncti_DCM_g_type identify()	const override { return NCTI_DCM_BI_SCALABLE_SET; }
		virtual NctiDCMEXGType type() const override { return EX_BI_SCALABLE_SET; }
	public:
		double scaling_transform1() const { return m_fscaling_transform1; }
		double scaling_transform2() const { return m_fscaling_transform2; }
		void set_scaling_transform1(double i_scaleFactor) { m_fscaling_transform1 = i_scaleFactor; }
		void set_scaling_transform2(double i_scaleFactor) { m_fscaling_transform2 = i_scaleFactor; }
	};
}
#endif