#ifndef NctiDCMLinearInequality_H
#define NctiDCMLinearInequality_H
#include "dcl_ncti_object.h"
#include "NctiDisplayDCMGeometry.h"
#include "NctiDCMDef.h"
#include "NctiDCMLinearEquation.h"

namespace NCTI
{
	class NctiDCMVariable;
	class DECL_NCTI_OBJECT NctiDCMLinearInequality : public NctiDCMLinearEquation
	{
		NCTI_DISPLAYOBJECT_FUNCTIONS(NctiDCMLinearInequality)
	public:
		virtual ~NctiDCMLinearInequality();
	public:
		virtual void Init();
		virtual EnumNctiResult UpdateDisplay();

	private:
		NCTI_READ_AND_WRITE_VERSION_FUN(1)

			bool m_greater_than;
	public:
		void InitLinearInequality(bool i_greater_than, double i_limit);
	public:
		virtual ncti_DCM_e_type identify()	const  override { return NCTI_DCM_RIGID_LINEAR_INEQUALITY; }
		virtual std::string describe() const override;
		virtual bool check(double i_tol) override;
		virtual void set_coeff(int i_index, NctiDCMVariable* i_var, double i_coeff) override;
	public:
		bool is_greater_than() const { return m_greater_than; }
	};
}
#endif
