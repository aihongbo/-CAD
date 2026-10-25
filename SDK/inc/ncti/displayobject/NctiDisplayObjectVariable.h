#ifndef NctiDisplayObjectVariable_H
#define NctiDisplayObjectVariable_H
#include "NctiDisplayObject.h"
#include "NctiPosition.h"
#include "NctiTransf.h"
namespace NCTI
{
	/**
	* @brief internal used
	*/
	class DECL_NCTI NctiDisplayObjectVariable : public NctiDisplayObject
	{
		NCTI_DISPLAYOBJECT_FUNCTIONS(NctiDisplayObjectVariable)
	public:
		NctiDisplayObjectVariable(Ncti_Integer i_iTrueFalse);
		virtual ~NctiDisplayObjectVariable();
		enum NctiLocalVariableType { SM_INT, SM_DOUBLE, SM_POSITION, SM_KEY, SM_DISPLAYOBJECT, SM_TRANSF };
		void Init(Ncti_Integer& i_iInt);
		void Init(Ncti_Double& i_dDouble);
		void Init(NctiPosition& i_Position);
		void Init(NCTI_HC_KEY& i_Key);
		void Init(NctiDisplayObject* i_pDo);
		void Init(NctiTransf& i_cTransf);
		const NctiLocalVariableType GetVariableType() { return m_eType; };
		Ncti_Boolean GetInt(Ncti_Integer& o_retval);
		Ncti_Boolean SetInt(Ncti_Integer& i_iValue);
		Ncti_Boolean GetDouble(Ncti_Double& o_retval);
		Ncti_Boolean GetPosition(NctiPosition& o_retval);
		Ncti_Boolean GetKey(NCTI_HC_KEY& o_retval);
		Ncti_Boolean GetDisplayObject(NctiDisplayObject*& o_retval);
		Ncti_Boolean GetTransf(NctiTransf& o_transf); 
	protected:
		void init(NctiLocalVariableType i_eType);
	private:
		NctiLocalVariableType	m_eType;
		Ncti_Integer				m_iInt;
		Ncti_Double			m_dDouble;
		NctiPosition	m_cPosition;
		NCTI_HC_KEY		m_lKey;
		NctiDisplayObject* m_pDisplayObject;
		NctiTransf		m_cTransf; 
	};
}
#endif 
