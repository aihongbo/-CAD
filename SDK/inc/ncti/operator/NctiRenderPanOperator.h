#ifndef NctiRenderPanOperator_H
#define NctiRenderPanOperator_H
#include "ncti_dcl.h"
#include "NctiRenderOperator.h"

namespace NCTI
{
	/**
	* @brief mouse pan operator
	* @details Hold down the middle button of the mouse to pan
	* @see NctiRenderOperator
	*/
	class DECL_NCTI NctiRenderPanOperator : public NctiRenderOperator
	{
	public:
		NctiRenderPanOperator(NctiBaseView*,MouseButtons in_mouse_trigger = MouseButtons::ButtonLeft(), ModifierKeys in_modifier_trigger = ModifierKeys());
		virtual ~NctiRenderPanOperator();

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
		virtual Ncti_Boolean OnMouseDown(NctiRenderMouseState* in_state) override;
		/**
	   * @brief OnMouseUp, override
	   * @param[in] in_state, mouse state
	   * @return Ncti_Boolean
	   */
		virtual Ncti_Boolean OnMouseUp(NctiRenderMouseState* in_state) override;
		/**
	   * @brief OnMouseMove, override
	   * @param[in] in_state, mouse state
	   * @return Ncti_Boolean
	   */
		virtual Ncti_Boolean OnMouseMove(NctiRenderMouseState* in_state) override;
		/**
	   * @brief OnTouchUpdate, override
	   * @param[in] in_state, mouse state
	   * @return Ncti_Boolean
	   */
		virtual Ncti_Boolean OnTouchUpdate(NctiRenderTouchState* in_state) override;
		/**
	   * @brief OnTouchEnd, override
	   * @param[in] in_state, mouse state
	   * @return Ncti_Boolean
	   */
		virtual Ncti_Boolean OnTouchEnd(NctiRenderTouchState* in_state) override;
	private:
		Ncti_Boolean m_MiddleDown;
		Ncti_Double m_windowX;
		Ncti_Double m_windowY;
        Ncti_Boolean m_ctl{ false };
	};
}
#endif // !NctiRenderPanOperator_H
