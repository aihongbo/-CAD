#ifndef NctiOperatingKey_H
#define NctiOperatingKey_H
#include "dcl_ncti_pubfun.h"
#include "NctiRenderOperator.h"
#include <functional>
namespace NCTI
{
	class NctiBaseModel;
	class DECL_NCTI_PUBFUN NctiOperatingKey : public NctiRenderOperator
	{
	public:
		NctiOperatingKey(NctiBaseModel* pBaseModel,NctiBaseView*view);
		virtual ~NctiOperatingKey();
	public:
		Ncti_Boolean OnKeyDown(NctiRenderKeyboardState* in_state)override;
		Ncti_Boolean OnKeyUp(NctiRenderKeyboardState* in_state)override;
	private:
		NctiBaseModel* m_pBaseModel;
		Ncti_Boolean m_KeyRun;
	};
}
#endif
