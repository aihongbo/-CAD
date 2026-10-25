#ifndef NctiRenderMouseState_H
#define NctiRenderMouseState_H
#include "ncti_dcl.h"

namespace NCTI
{
	class NctiRenderMouseEvent;
	/**
	* @brief mouse state
	* @see NctiRenderOperator
	*/
	class DECL_NCTI NctiRenderMouseState
	{
	public:
		NctiRenderMouseState();
		virtual ~NctiRenderMouseState();
	public:
		/**
	   * @brief get active event
	   * @return NctiRenderMouseEvent
	   */
		NctiRenderMouseEvent* GetActiveEvent() { return m_MouseEvent; }
		/**
	   * @brief set active event
	   */
		void SetMouseEvent(NctiRenderMouseEvent* i_pRenderMouseEvent) { m_MouseEvent = i_pRenderMouseEvent; }
	private:
		NctiRenderMouseEvent* m_MouseEvent;
	};
}
#endif
