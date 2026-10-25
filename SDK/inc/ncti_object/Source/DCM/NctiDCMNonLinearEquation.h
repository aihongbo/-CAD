#ifndef NctiDCMNonLinearEquation_H
#define NctiDCMNonLinearEquation_H
#include "dcl_ncti_object.h"
#include "NctiDisplayDCMGeometry.h"
#include "NctiDCMDef.h"
#include "NctiDCMEquation.h"
namespace NCTI
{
	class NctiDCMHelpNode
	{
		NCTI_G_NODE m_gn;
		NCTI_D_NODE m_dn;
	public:
		NctiDCMHelpNode(NCTI_G_NODE* gi, NCTI_D_NODE* di) { m_gn = gi, m_dn = di; }
		NCTI_G_NODE geometry() const { return m_gn; }
		NCTI_D_NODE dimension() const { return m_dn; }
	};

	class DECL_NCTI_OBJECT NctiDCMNonLinearEquation : public NctiDCMEquation
	{
		NCTI_DISPLAYOBJECT_FUNCTIONS(NctiDCMNonLinearEquation)
	public:
		virtual ~NctiDCMNonLinearEquation();
	public:
		virtual void Init();
		virtual EnumNctiResult UpdateDisplay();

	private:
		NCTI_READ_AND_WRITE_VERSION_FUN(1)
		double (*m_fresidual) (NctiDCMNonLinearEquation*);
		double (*m_fderivative) (NctiDCMNonLinearEquation*, NctiDCMVariable*);
		bool(*m_check_fresidual) (NctiDCMNonLinearEquation*, double i_tol);

		std::vector<NctiDisplayDCMGeometry*> m_GeomVec;
		std::vector<NctiDCMHelpNode*> m_HelpNodeVec;
		std::string m_expression;
		Ncti_Address m_residFuncPtr;
		Ncti_Address m_derivFuncPtr;
	public:
		void InitNonLinearEquation(double (*residual)(NctiDCMNonLinearEquation*),
			double (*derivative)(NctiDCMNonLinearEquation*, NctiDCMVariable*),
			const std::vector<NctiDisplayDCMGeometry*>& geomVec,
			const std::vector<NctiDCMHelpNode*>& helpNodeVec);
	public:
		virtual std::string describe() const override;
		virtual bool check(double i_tol) override;
		virtual ncti_DCM_e_type identify()	const  override  { return NCTI_DCM_NON_LINEAR_EQUATION; }
	public:
		void setResidualFunc(Ncti_Address i_funcPtr) { m_residFuncPtr = i_funcPtr; }
		Ncti_Address getResidualFunc() const { return m_residFuncPtr; }
		void setDerivativeFunc(Ncti_Address i_funcPtr) { m_derivFuncPtr = i_funcPtr; }
		Ncti_Address getDerivativeFunc() const { return m_derivFuncPtr; }
	
		void setCheckFresidualFunc(bool(*funcPtr) (NctiDCMNonLinearEquation*, double i_tol)) { m_check_fresidual = funcPtr; }
		Ncti_Address getCheckFresidualFunc() const { return (void*)m_check_fresidual; }

		double residual() { return (*m_fresidual)(this); }
		double derivative(NctiDCMVariable* i_var) { return (*m_fderivative)(this, i_var); }
		int exist_deriv()		const { return m_derivFuncPtr != nullptr; }

		void setExpression(const char* i_expr);
		const char* getExpression() const { return m_expression.c_str(); }
	};
}
#endif
