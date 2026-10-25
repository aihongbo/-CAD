#ifndef NctiRenderOperator_H
#define NctiRenderOperator_H
#include "ncti_dcl.h"
#include "ncti_event.h"
#include "NctiRenderMouseState.h"
#include "NctiRenderKeyboardState.h"
#include "NctiRenderTouchState.h"
namespace NCTI
{
	class NctiBaseView;
	/**
	* @brief The Base Operator class 
	* @details all other operator object of base class
	*/
	class DECL_NCTI NctiRenderOperator
	{
	public:
		NctiRenderOperator(NctiBaseView*,MouseButtons in_mouse_trigger = MouseButtons::ButtonLeft(), ModifierKeys in_modifier_trigger = ModifierKeys());
		virtual~NctiRenderOperator();
		/**
	   * @brief OnMouseEnter, override
	   * @param[in] in_state, mouse state
	   * @return Ncti_Boolean
	   */
        virtual Ncti_Boolean OnMouseEnter(NctiRenderMouseState* in_state);
		/**
	   * @brief OnMouseLeave, override
	   * @param[in] in_state, mouse state
	   * @return Ncti_Boolean
	   */
        virtual Ncti_Boolean OnMouseLeave(NctiRenderMouseState* in_state);
		/**
	   * @brief OnMouseDown, override
	   * @param[in] in_state, mouse state
	   * @return Ncti_Boolean
	   */
		virtual Ncti_Boolean OnMouseDown(NctiRenderMouseState* in_state);
		/**
	   * @brief OnMouseUp, override
	   * @param[in] in_state, mouse state
	   * @return Ncti_Boolean
	   */
		virtual Ncti_Boolean OnMouseUp(NctiRenderMouseState* in_state);
		/**
	   * @brief OnMouseMove, override
	   * @param[in] in_state, mouse state
	   * @return Ncti_Boolean
	   */
		virtual Ncti_Boolean OnMouseMove(NctiRenderMouseState* in_state);
		/**
	   * @brief OnMouseWheel, override
	   * @param[in] in_state, mouse state
	   * @return Ncti_Boolean
	   */
		virtual Ncti_Boolean OnMouseWheel(NctiRenderMouseState* in_state);
		/**
	   * @brief OnKeyDown, override
	   * @param[in] in_state, mouse state
	   * @return Ncti_Boolean
	   */
		virtual Ncti_Boolean OnKeyDown(NctiRenderKeyboardState* in_state);
		/**
	   * @brief OnKeyUp, override
	   * @param[in] in_state, mouse state
	   * @return Ncti_Boolean
	   */
		virtual Ncti_Boolean OnKeyUp(NctiRenderKeyboardState* in_state);
		/**
	   * @brief OnTouchBegin, override
	   * @param[in] in_state, mouse state
	   * @return Ncti_Boolean
	   */
		virtual Ncti_Boolean OnTouchBegin(NctiRenderTouchState* in_state);
		/**
	   * @brief OnTouchUpdate, override
	   * @param[in] in_state, mouse state
	   * @return Ncti_Boolean
	   */
		virtual Ncti_Boolean OnTouchUpdate(NctiRenderTouchState* in_state);
		/**
	   * @brief OnTouchEnd, override
	   * @param[in] in_state, mouse state
	   * @return Ncti_Boolean
	   */
		virtual Ncti_Boolean OnTouchEnd(NctiRenderTouchState* in_state);
		/**
	   * @brief check the operator is valid
	   * @return Ncti_Boolean
	   */
		Ncti_Boolean IsValid();
		/**
	   * @brief set the operator valid
	   */
		void SetValid(Ncti_Boolean i_boo);
		/**
	   * @brief set the operator OnMouseDown valid
	   */
		void SetOnMouseDownValid(Ncti_Boolean i_boo);
		/**
	   * @brief set the operator OnMouseUp valid
	   */
		void SetOnMouseUpValid(Ncti_Boolean i_boo);
		/**
	   * @brief set the operator OnMouseMove valid
	   */
		void SetOnMouseMoveValid(Ncti_Boolean i_boo);
		/**
	   * @brief set the operator OnMouseWheel valid
	   */
		void SetOnMouseWheelValid(Ncti_Boolean i_boo);
		/**
	   * @brief check the operator OnMouseDown is valid
	   * @return Ncti_Boolean
	   */
		Ncti_Boolean MouseDownIsValid();
		/**
	   * @brief check the operator OnMouseUp is valid
	   * @return Ncti_Boolean
	   */
		Ncti_Boolean MouseUpIsValid();
		/**
	   * @brief check the operator OnMouseMove is valid
	   * @return Ncti_Boolean
	   */
		Ncti_Boolean MouseMoveIsValid();
		/**
	   * @brief check the operator OnMouseWheel is valid
	   * @return Ncti_Boolean
	   */
		Ncti_Boolean MouseWheelIsValid();

	protected:
		MouseButtons m_mouse_trigger;
		ModifierKeys m_modifier_trigger;

		Ncti_Boolean m_IsValid;
		Ncti_Boolean m_IsFirstTouch;

		Ncti_Boolean m_OnMouseDownIsValid;
		Ncti_Boolean m_OnMouseUpIsValid;
		Ncti_Boolean m_OnMouseMoveIsValid;
		Ncti_Boolean m_OnMouseWheelIsValid;

		NctiBaseView* m_view;
	};
}
#endif // !NctiRenderOperator_H
