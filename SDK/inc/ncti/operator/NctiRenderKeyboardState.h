#ifndef NctiRenderKeyboardState_H
#define NctiRenderKeyboardState_H
#include "ncti_dcl.h"
namespace NCTI
{
	class NctiRenderKeyboardEvent;
	/**
	* @brief Keyboard State
	*/
	class DECL_NCTI NctiRenderKeyboardState
	{
	public:
		NctiRenderKeyboardState();
		virtual ~NctiRenderKeyboardState();
	public:
		/**
	   * @brief get active event
	   * @return NctiRenderKeyboardEvent
	   */
		NctiRenderKeyboardEvent* GetActiveEvent() { return m_KeyboardEvent; }
		/**
	   * @brief set active event
	   */
		void SetMouseEvent(NctiRenderKeyboardEvent* i_pRenderKeyboardEvent) { m_KeyboardEvent = i_pRenderKeyboardEvent; }
	private:
		NctiRenderKeyboardEvent* m_KeyboardEvent;
	};
}
#endif // !NctiRenderKeyboardState_H
