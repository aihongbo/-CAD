#ifndef NctiWindowMouseEvent_H
#define NctiWindowMouseEvent_H
#include "NctiWindowEvent.h"
#include "ncti_event.h"
namespace NCTI
{
	/**
   * @brief window mouse event
   * @see NctiWindowEvent
   */
	class DECL_NCTI_WINDOW NctiWindowMouseEvent : public NctiWindowEvent
	{
	public:
		/**
	   * @brief set mouse buttons
	   */
		void SetMouseButtons(MouseButtons i_buttons);

		/**
	   * @brief  mouse buttons
	   * @return const MouseButtons&
	   */
		const MouseButtons& button()const;

	private:
		MouseButtons m_CurrentButton;
	};
}
#endif
