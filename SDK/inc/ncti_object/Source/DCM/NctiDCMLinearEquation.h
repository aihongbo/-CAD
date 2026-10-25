#ifndef NctiDCMLinearEquation_H
#define NctiDCMLinearEquation_H
#include "dcl_ncti_object.h"
#include "NctiDisplayDCMGeometry.h"
#include "NctiDCMDef.h"
#include "NctiDCMEquation.h"

namespace NCTI
{
	class DECL_NCTI_OBJECT NctiDCMLinearEquation : public NctiDCMEquation
	{
		NCTI_DISPLAYOBJECT_FUNCTIONS(NctiDCMLinearEquation)
	public:
		virtual ~NctiDCMLinearEquation();
	public:
		virtual void Init();
		virtual EnumNctiResult UpdateDisplay();

	private:
		NCTI_READ_AND_WRITE_VERSION_FUN(1)
		double m_fconstant;
		std::vector<double> m_coeff_vec;
		ncti_DCM_e_type m_etype;
	public:
		virtual std::string describe() const override;
		virtual ncti_DCM_e_type identify()	const override { return m_etype; }
		virtual bool check(double i_tol) override;
		virtual void set_coeff(int i_index, NctiDCMVariable* i_var, double i_coeff);
	public:
		void set_constant(double i_cons);
		void set_e_type(ncti_DCM_e_type i_type);
		double constant()		const { return m_fconstant; }
		double coeff(int i)	const { return m_coeff_vec[i]; }
	};
}
#endif
