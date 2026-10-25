#ifndef NctiDCMCopyCurve_H
#define NctiDCMCopyCurve_H
#include "dcl_ncti_object.h"
#include "NctiDCMParametric.h"
#include "NctiDisplayDCMPoint.h"
#include "NctiDisplayDCMSpline.h"
#include "NctiDisplayDCMConic.h"
#include "NctiDCMDef.h"
#include <ostream>
namespace NCTI
{
	class NctiDCMEXVec2d;
	class DECL_NCTI_OBJECT NctiDCMCopyCurve : public NctiDCMParametric
	{
		NCTI_DISPLAYOBJECT_FUNCTIONS(NctiDCMCopyCurve)
	public:
		virtual ~NctiDCMCopyCurve();
	public:
		virtual void Init();
		virtual EnumNctiResult UpdateDisplay();
	private:
		NCTI_READ_AND_WRITE_VERSION_FUN(1)

		NctiDisplayDCMGeometry* m_foriginalcurve;
		double m_fcopymat[3][3];
	private: 
		void InitCopyCurve(NctiDisplayDCMGeometry* i_parent, double i_copymat[3][3] = NULL, double i_lower = 0., double i_upper = 1.);
	public:
		void InitCopyCurve(NctiDisplayDCMSpline* i_parent, double i_copymat[3][3]= NULL);
		void InitCopyCurve(NctiDisplayDCMConic* i_parent, double i_copymat[3][3]= NULL);
		void InitCopyCurve(NctiDCMParametric* i_parent, double i_copymat[3][3]= NULL);
	public:
		virtual std::string describe() const override;
		virtual ncti_DCM_g_type identify() const override { return NCTI_DCM_PARAMETRIC; }
		virtual NctiDCMEXGType type() const override { return EX_COPYCURVE; }

		virtual NctiDCMEXVec2d position(double i_t) override;
		virtual NctiDCMEXVec2d first_der(double i_der) override;
		virtual NctiDCMEXVec2d second_der(double i_der) override;
	public:
		void copy_transform(double o_mat[3][3]) const;
		void update_copy_transform(const double i_mat[3][3]);
		NctiDisplayDCMGeometry* original_curve() const {return m_foriginalcurve;}
	};
}
#endif