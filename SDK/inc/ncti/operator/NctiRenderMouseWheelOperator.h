#ifndef NctiRenderMouseWheelOperator_H
#define NctiRenderMouseWheelOperator_H
#include "NctiRenderOperator.h"
namespace NCTI
{
	/**
	* @brief mouse pan operator
	* @details use the wheel button of the mouse to scale
	* @see NctiRenderOperator
	*/
	class DECL_NCTI NctiRenderMouseWheelOperator : public NctiRenderOperator
	{
	public:
		NctiRenderMouseWheelOperator(NctiBaseView*,MouseButtons in_mouse_trigger = MouseButtons::ButtonMiddle(), ModifierKeys in_modifier_trigger = ModifierKeys());
		virtual ~NctiRenderMouseWheelOperator();
	public:
		/**
	   * @brief OnMouseWheel, override
	   * @param[in] in_state, mouse state
	   * @return Ncti_Boolean
	   */
        Ncti_Boolean OnMouseWheel(NctiRenderMouseState* in_state)override;
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
	private:
		Ncti_Double m_scaleFactor;
        Ncti_Boolean m_ctl{ false };
	};
}
#endif
