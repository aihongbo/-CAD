#ifndef NctiDisplayDCMScalableSpline_H
#define NctiDisplayDCMScalableSpline_H
#include "dcl_ncti_object.h"
#include "NctiDCMDef.h"
#include "NctiDisplayDCMSpline.h"

namespace NCTI
{
	class DECL_NCTI_OBJECT NctiDisplayDCMScalableSpline : public NctiDisplayDCMSpline
	{
		NCTI_DISPLAYOBJECT_FUNCTIONS(NctiDisplayDCMScalableSpline)
	public:
		virtual ~NctiDisplayDCMScalableSpline();
	public:
		virtual void Init();
		virtual EnumNctiResult UpdateDisplay();

	private:
		NCTI_READ_AND_WRITE_VERSION_FUN(1)
			NCTI_G_NODE m_fscaling_centre;
	public:
		virtual std::string describe() const override;
		virtual ncti_DCM_g_type identify()	const override { return NCTI_DCM_SPLINE; }
		virtual NctiDCMEXGType type() const override { return EX_SCALABLE_SPLINE; }
	public:
		NCTI_G_NODE scaling_centre() const { return m_fscaling_centre; }
		void set_scaling_centre(NCTI_G_NODE i_g) { m_fscaling_centre = i_g; };
	};
}
#endif
