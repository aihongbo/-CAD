#ifndef NctiOpSelectDo_H
#define NctiOpSelectDo_H
#include "ncti.h"

#include "NctiRenderOperator.h"

namespace NCTI
{
	class NctiRenderMouseState;
	class NctiRenderKeyboardState;
	class NctiToolSelectDo;
	/**
	* @brief the system default operator, internal used
	* @details work together with NctiToolSelectDo
	* @see NctiRenderOperator,NctiToolSelectDo
	*/
	class DECL_NCTI NctiOpSelectDo : public NctiRenderOperator
	{
	public:
		NctiOpSelectDo(NctiToolSelectDo* i_pTool);
		virtual ~NctiOpSelectDo();
        virtual Ncti_Boolean OnMouseDown(NctiRenderMouseState* in_state);
        virtual Ncti_Boolean OnMouseUp(NctiRenderMouseState* in_state);
        virtual Ncti_Boolean OnMouseMove(NctiRenderMouseState* in_state);
		virtual Ncti_Boolean OnKeyDown(NctiRenderKeyboardState* in_state);
		virtual Ncti_Boolean OnKeyUp(NctiRenderKeyboardState* in_state);
		virtual Ncti_Boolean OnMouseWheel(NctiRenderMouseState* in_state);

	private:
		NctiToolSelectDo* m_tool{nullptr};
		Ncti_Boolean m_bStartSelection;
        Ncti_Boolean m_bStartRotate{false};
		Ncti_Double m_windowX;
		Ncti_Double m_windowY;
	};
}
#endif
