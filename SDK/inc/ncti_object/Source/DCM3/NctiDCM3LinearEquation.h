#ifndef NctiDCM3LinearEquation_H
#define NctiDCM3LinearEquation_H
#include "dcl_ncti_object.h"
#include "NctiDisplayGModelObject.h"
#include "NctiDCM3Equation.h"
#include "NctiDCM3Variable.h"
#include "NctiDCM3Def.h"
namespace NCTI
{
	/**
	* @brief linear equation
	* @details create a linear equation
	* @see NctiDCM3Equation
	*/
	class DECL_NCTI_OBJECT NctiDCM3LinearEquation : public NctiDCM3Equation
	{
		NCTI_DISPLAYOBJECT_FUNCTIONS(NctiDCM3LinearEquation)
	public:
		virtual ~NctiDCM3LinearEquation();
	public:
		virtual void Init();
		virtual EnumNctiResult UpdateDisplay();
	private:
		NCTI_READ_AND_WRITE_VERSION_FUN(1)
		double m_fconstant;
		std::vector<double> m_fcoeff_array;
	public:
		virtual void init_equation(int i_num) override; 
		virtual ncti_DCM3_e_type identify() override { return NCTI_DCM3_LINEAR_EQUATION; }
		virtual std::string describe() const override;
		virtual bool check(double i_tol) override;
		virtual std::string expression() const override;
	public:
		/**
		* @brief set constant of the linear equation
		* @param[in] i_constant, the constant of linear equation
		*/
		void set_constant(double i_constant);
		/**
		* @brief get constant of the linear equation
		* @return double
		*/
		double constant() const { return m_fconstant; }
		/**
		* @brief get coeff of variable by index
		* @param[in] i_index, variable index in the linear equation
		* @return double
		*/
		double coeff(int i_index)	const { return m_fcoeff_array[i_index]; }
		/**
		* @brief set variable and coeff to the linear equation by index
		* @param[in] i_index, variable index in the linear equation
		* @param[in] i_var, variable object pointer
		* @param[in] i_coeff, coeff of variable
		*/
		void set_var_and_coeff(int i_index, NctiDCM3Variable* i_var, double i_coeff);
		/**
		* @brief remove coeff from the linear equation by index
		* @param[in] i_index, coeff index in the linear equation
		*/
		void remove_coeff(int i_index);
	};
}
#endif