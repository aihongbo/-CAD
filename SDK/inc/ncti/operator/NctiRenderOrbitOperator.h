#ifndef NctiRenderOrbitOperator_H
#define NctiRenderOrbitOperator_H
#include "ncti_dcl.h"
#include "NctiRenderOperator.h"
#include "NctiPosition.h"

namespace NCTI
{
	/**
	* @brief mouse pan operator
	* @details Hold down the right button of the mouse to orbit
	* @see NctiRenderOperator
	*/
	class DECL_NCTI NctiRenderOrbitOperator : public NctiRenderOperator
	{
	public:
		NctiRenderOrbitOperator(NctiBaseView*,MouseButtons in_mouse_trigger = MouseButtons::ButtonLeft(), ModifierKeys in_modifier_trigger = ModifierKeys());
		virtual ~NctiRenderOrbitOperator();
		/**
	   * @brief OnKeyDown, override
	   * @param[in] in_state, mouse state
	   * @return Ncti_Boolean
	   */
		Ncti_Boolean OnKeyDown(NctiRenderKeyboardState* in_state)override;
		/**
	   * @brief OnKeyUp, override
	   * @param[in] in_state, mouse state
	   * @return Ncti_Boolean
	   */
		Ncti_Boolean OnKeyUp(NctiRenderKeyboardState* in_state)override;
		/**
	   * @brief OnMouseDown, override
	   * @param[in] in_state, mouse state
	   * @return Ncti_Boolean
	   */
        Ncti_Boolean OnMouseDown(NctiRenderMouseState* in_state)override;
		/**
	   * @brief OnMouseUp, override
	   * @param[in] in_state, mouse state
	   * @return Ncti_Boolean
	   */
        Ncti_Boolean OnMouseUp(NctiRenderMouseState* in_state)override;
		/**
	   * @brief OnMouseMove, override
	   * @param[in] in_state, mouse state
	   * @return Ncti_Boolean
	   */
        Ncti_Boolean OnMouseMove(NctiRenderMouseState* in_state)override;
		/**
	   * @brief OnTouchUpdate, override
	   * @param[in] in_state, mouse state
	   * @return Ncti_Boolean
	   */
        Ncti_Boolean OnTouchUpdate(NctiRenderTouchState* in_state)override;
		/**
	   * @brief OnTouchEnd, override
	   * @param[in] in_state, mouse state
	   * @return Ncti_Boolean
	   */
        Ncti_Boolean OnTouchEnd(NctiRenderTouchState* in_state)override;
	protected:
        Ncti_Boolean m_ctl{ false };
		Ncti_Boolean m_alt{false};
		Ncti_Boolean m_Down{false};
        Ncti_Boolean m_bDrag{false};
        NctiPosition m_lastPos;
	};
}
#endif // !NctiRenderOrbitOperator_H
