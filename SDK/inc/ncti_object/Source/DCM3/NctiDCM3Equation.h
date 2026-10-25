#ifndef NctiDCM3Equation_H
#define NctiDCM3Equation_H
#include "dcl_ncti_object.h"
#include "NctiDisplayDCM3Object.h"
#include "NctiDCM3Def.h"
#include "NctiDCM3Variable.h"
namespace NCTI
{
	class NctiDisplayDCM3DimSys;
	/**
	* @brief the base class of equations 
	* @details create an equation
	* @see NctiDisplayDCM3Object
	*/
	class DECL_NCTI_OBJECT NctiDCM3Equation : public NctiDisplayDCM3Object
	{
		NCTI_DISPLAYOBJECT_FUNCTIONS(NctiDCM3Equation)
	public:
		virtual ~NctiDCM3Equation();
	public:
		virtual void Init();
		virtual EnumNctiResult UpdateDisplay();
	private:
		NCTI_READ_AND_WRITE_VERSION_FUN(1)
		std::vector<NctiDCM3Variable*> m_fvar_array;
		NctiDisplayDCM3DimSys* m_dimsys;
		NCTI_E_NODE m_fe_node;
		ncti_DCM3_d_node_status m_status;
	public:
		/**
		* @brief initialize variable count of equation
		* @param[in] i_num, the number of variables 
		*/
		virtual void init_equation(int i_num) { m_fvar_array.assign(i_num, nullptr); }
		/**
		* @brief get equation type
		* @return ncti_DCM3_e_type
		*/
		virtual ncti_DCM3_e_type identify() { return NCTI_DCM3_UNKNOWN_EQUATION; }
		/**
		* @brief get the json describe string of the current equation
		* @return std::string
		*/
		virtual std::string describe() const;
		/**
		* @brief check the equation solution result is correct or not
		* @param[in] i_tol, solution tolerance
		* @return bool
		*/
		virtual bool check(double i_tol);
		/**
		* @brief get euqation expression
		* @return string
		*/
		virtual std::string expression() const;
	public:
		/**
		* @brief get node pointer of equation
		* @return NCTI_E_NODE
		*/
		NCTI_E_NODE get_enode() { return m_fe_node; }
		/**
		* @brief set node pointer of equation
		* @param[in] i_en, equation node pointer
		*/
		void set_enode(NCTI_E_NODE i_en);
		/**
		* @brief get dimention system object
		* @return NctiDisplayDCM3DimSys object pointer
		*/
		NctiDisplayDCM3DimSys* get_dcm() const { return m_dimsys; }
		/**
		* @brief set dimention system object to equation
		* @param[in] i_pDimSys, dimention system object pointer
		*/
		void set_dcm(NctiDisplayDCM3DimSys* i_pDimSys);
		/**
		* @brief get variables count of equation 
		* @return int
		*/
		int n_vars() const { return m_fvar_array.size(); }
		/**
		* @brief set variable by index
		* @param[in] i_index, index of variables in the equation
		* @param[in] i_var, variable object pointer
		*/
		void set_var(int i_index, NctiDCM3Variable* i_var) { m_fvar_array[i_index] = i_var; i_var->AddOwner(this); }
		/**
		* @brief get variable by index
		* @param[in] i_index, index of variables in the equation
		* @return NctiDCM3Variable object pointer
		*/
		NctiDCM3Variable* var(int i_index) const { return m_fvar_array[i_index]; }
		/**
		* @brief get variable index in the equation by variable object pointer
		* @param[in] i_var, variable object pointer
		* @return int
		*/
		int var_index(NctiDCM3Variable* i_var);
		/**
		* @brief remove variable from equation by index
		* @param[in] i_index, index of variables in the equation
		*/
		void remove_var(int i_index) { m_fvar_array.erase(m_fvar_array.begin() + i_index); }
		/**
		* @brief set equation node status
		* @param[in] i_status, equation node status
		*/
		void set_status(ncti_DCM3_d_node_status i_status) { m_status=i_status; }
		/**
		* @brief get equation node status
		* @return ncti_DCM3_d_node_status
		*/
		ncti_DCM3_d_node_status status() const { return m_status; }
	};
}
#endif