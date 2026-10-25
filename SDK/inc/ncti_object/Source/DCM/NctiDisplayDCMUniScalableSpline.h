#ifndef NctiDisplayDCMUniScalableSpline_H
#define NctiDisplayDCMUniScalableSpline_H
#include "dcl_ncti_object.h"
#include "NctiDCMDef.h"
#include "NctiDisplayDCMScalableSpline.h"

namespace NCTI
{
	class DECL_NCTI_OBJECT NctiDisplayDCMUniScalableSpline : public NctiDisplayDCMScalableSpline
	{
		NCTI_DISPLAYOBJECT_FUNCTIONS(NctiDisplayDCMUniScalableSpline)
	public:
		virtual ~NctiDisplayDCMUniScalableSpline();
	public:
		virtual void Init();
		virtual EnumNctiResult UpdateDisplay();

	private:
		NCTI_READ_AND_WRITE_VERSION_FUN(1)
			NctiDCMEXVec2d m_fscaling_direction;
	public:
		virtual std::string describe() const override;
		virtual ncti_DCM_g_type identify()	const override  { return NCTI_DCM_SPLINE; }
		virtual NctiDCMEXGType type() const override { return EX_UNI_SCALABLE_SPLINE; }
	public:
		NctiDCMEXVec2d scaling_direction() const { return m_fscaling_direction; }
		void set_scaling_direction(const NctiDCMEXVec2d& i_dir) { m_fscaling_direction = i_dir; };
	};
}
#endif
