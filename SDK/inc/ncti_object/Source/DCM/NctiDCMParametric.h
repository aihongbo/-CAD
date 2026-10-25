#ifndef NctiDCMParametric_H
#define NctiDCMParametric_H
#include "dcl_ncti_object.h"
#include "NctiDisplayDCMGeometry.h"
#include "NctiDisplayDCMDimSys.h"
#include "NctiDCMExExtensionData.h"
#include "NctiDCMDef.h"
namespace NCTI
{
	class NctiDCMEXVec2d;
	class DECL_NCTI_OBJECT NctiDCMParametric : public NctiDisplayDCMGeometry
	{
		NCTI_DISPLAYOBJECT_FUNCTIONS(NctiDCMParametric)
	public:
		virtual ~NctiDCMParametric();
	public:
		virtual void Init();
		virtual EnumNctiResult UpdateDisplay();
	private:
		NCTI_READ_AND_WRITE_VERSION_FUN(1)
		double m_flimit_low;
		double m_flimit_up;
	public:
		virtual std::string describe() const;
		virtual NctiDCMEXVec2d direction() const { return NctiDCMEXVec2d(); }
		virtual NctiDCMEXVec2d position(double i_param) { return NctiDCMEXVec2d(); }
		virtual NctiDCMEXVec2d first_der(double i_param) { return NctiDCMEXVec2d(); }
		virtual NctiDCMEXVec2d second_der(double i_param) { return NctiDCMEXVec2d(); }

		virtual ncti_DCM_g_type identify()	const override { return NCTI_DCM_PARAMETRIC; }
		virtual NctiDCMEXGType type() const override { return EX_PARAMETRIC; }
	public:
		void Set_lower_lim(const double i_lower_lim);
		void Set_upper_lim(const double i_upper_lim);
		double lower_lim()		const { return m_flimit_low; }
		double upper_lim()		const { return m_flimit_up; }
	};
}
#endif