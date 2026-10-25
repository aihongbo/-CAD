#ifndef NctiDCMVariable_H
#define NctiDCMVariable_H
#include "dcl_ncti_object.h"
#include "NctiDisplayGModelObject.h"
#include "NctiDCMDef.h"
namespace NCTI
{
	class NctiDisplayDCMDimension;
	class DECL_NCTI_OBJECT NctiDCMVariable : public NctiDisplayGModelObject
	{
		NCTI_DISPLAYOBJECT_FUNCTIONS(NctiDCMVariable)
	public:
		virtual ~NctiDCMVariable();
		virtual void Init();
		virtual EnumNctiResult UpdateDisplay();

	private:
		NCTI_READ_AND_WRITE_VERSION_FUN(1)
		Ncti_Double m_fvalue;
		NCTI_V_NODE m_fv_node;
		NCTI_DR_NODE m_fdr_node;
		NctiDisplayDCMDimension* m_pDimension;
	public:
		void InitVariable(double i_value = 0.0);
		void InitVariable(NCTI_DR_NODE node, NctiDisplayDCMDimension* i_pDim);
	public:
		virtual std::string describe() const;
	public:
		Ncti_Double value() const  { return m_fvalue; }
		void set_value(Ncti_Double i_val); 
		void set_v_node(NCTI_V_NODE i_v);
		NCTI_V_NODE vnode()	const { return m_fv_node; }
	};
}
#endif
