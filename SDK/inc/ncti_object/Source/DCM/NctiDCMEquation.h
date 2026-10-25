#ifndef NctiDCMEquation_H
#define NctiDCMEquation_H
#include "dcl_ncti_object.h"
#include "NctiDisplayGModelObject.h"
#include "NctiDCMDef.h"
#include <iostream>
namespace NCTI
{
	class NctiDisplayDCMDimSys;
	class NctiDCMVariable;
	class NctiDCMLinearEquation;
	class NctiDCMNonLinearEquation;
	class DECL_NCTI_OBJECT NctiDCMEquation : public NctiDisplayGModelObject
	{
		NCTI_DISPLAYOBJECT_FUNCTIONS(NctiDCMEquation)
	public:
		virtual ~NctiDCMEquation();
	public:
		virtual void Init();
		virtual EnumNctiResult UpdateDisplay();

	private:
		NCTI_READ_AND_WRITE_VERSION_FUN(1)
		std::vector<NctiDCMVariable*> m_fvar_array;
		NctiDisplayDCMDimSys* m_fdcm;
		NCTI_E_NODE m_fe_node;
	public:
		virtual ncti_DCM_e_type identify() const { return NCTI_DCM_UNKNOWN_EQUATION; }
		virtual std::string describe() const;
		virtual bool check(double i_tol);
	public:
		int n_vars() const { return m_fvar_array.size(); }
		void set_var(int i, NctiDCMVariable* var);
		NctiDisplayDCMDimSys* get_dcm() const { return m_fdcm; }
		void set_dcm(NctiDisplayDCMDimSys* dsp); 
		NctiDCMVariable* var(int i_index)	const { return m_fvar_array.size() > i_index ? m_fvar_array[i_index] : nullptr; }
		int var_index(const NctiDCMVariable* i_var);
		void set_e_node(NCTI_E_NODE i_en);
		NCTI_E_NODE enode()	const { return m_fe_node; }
	};
}
#endif
