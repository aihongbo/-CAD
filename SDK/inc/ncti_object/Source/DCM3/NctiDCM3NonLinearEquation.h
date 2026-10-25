#ifndef NctiDCM3NonLinearEquation_H
#define NctiDCM3NonLinearEquation_H
#include "dcl_ncti_object.h"
#include "NctiDisplayGModelObject.h"
#include "NctiDCM3Equation.h"
#include "NctiDCM3Variable.h"
#include "NctiDCM3Def.h"
namespace NCTI
{
	class DECL_NCTI_OBJECT NctiDCM3NonLinearEquation : public NctiDCM3Equation
	{
		NCTI_DISPLAYOBJECT_FUNCTIONS(NctiDCM3NonLinearEquation)
	public:
		virtual ~NctiDCM3NonLinearEquation();
	public:
		virtual void Init();
		virtual EnumNctiResult UpdateDisplay();
	private:
		NCTI_READ_AND_WRITE_VERSION_FUN(1)
		ncti_DCM3_equation_status (*m_fresidual) (NctiDCM3NonLinearEquation*, double*);
		ncti_DCM3_equation_status (*m_fderivative) (NctiDCM3NonLinearEquation*, double*,  NctiDCM3Variable*);
		bool(*m_check_fresidual) (NctiDCM3NonLinearEquation*, double tol);
		Ncti_Address m_residFuncPtr;
		Ncti_Address m_derivFuncPtr;
		std::string m_expression;
	public:
		virtual ncti_DCM3_e_type identify() override { return NCTI_DCM3_NON_LINEAR_EQUATION; }
		virtual std::string describe() const override;
		virtual bool check(double i_tol) override;
		virtual std::string expression() const override { return m_expression; }
	public:
		/**
		* @brief set residual callback function and derivative callback function
		* @param[in] residual, residual callback function 
		* @param[in] derivative, derivative callback function 
		*/
		void set_evaluators(ncti_DCM3_equation_status(*residual)(NctiDCM3NonLinearEquation*, double*),
			ncti_DCM3_equation_status(*derivative)(NctiDCM3NonLinearEquation*, double*, NctiDCM3Variable* v) = NULL)
		{
			m_fresidual = residual; m_fderivative = derivative;
		}

		/**
		* @brief set callback function to check the non linear equation solution result is correct or not
		* @param[in] funcPtr, check callback function
		*/
		void setCheckFresidualFunc(bool(*funcPtr) (NctiDCM3NonLinearEquation*, double i_tol)) { m_check_fresidual = funcPtr; }
		/**
		* @brief get callback function which checks the non linear equation solution result is correct or not
		* @return Ncti_Address, callback function pointer
		*/
		Ncti_Address getCheckFresidualFunc() const { return (void*)m_check_fresidual; }

		void setResidualFunc(Ncti_Address i_funcPtr) { m_residFuncPtr = i_funcPtr; }
		Ncti_Address getResidualFunc() const { return m_residFuncPtr; }

		void setDerivativeFunc(Ncti_Address i_funcPtr) { m_derivFuncPtr = i_funcPtr; }
		Ncti_Address getDerivativeFunc() const { return m_derivFuncPtr; }

		void setExpression(const char* i_expr) { m_expression = i_expr; }
		const char* getExpression() const { return m_expression.c_str(); }

		ncti_DCM3_equation_status residual(double* i_residual) { return (*m_fresidual)(this, i_residual); }
		int exist_deriv() { return m_fresidual != NULL; }
		ncti_DCM3_equation_status derivative(double* i_deriv, NctiDCM3Variable* i_var) { return (*m_fderivative)(this, i_deriv, i_var); }
	};
}
#endif