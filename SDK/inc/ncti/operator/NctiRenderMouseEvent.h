#ifndef NctiRenderMouseEvent_H
#define NctiRenderMouseEvent_H
#include "NctiRenderInputEvent.h"
#include "NctiPosition.h"

namespace NCTI
{
	/**
	* @brief mouse event
	*/
	class DECL_NCTI NctiRenderMouseEvent : public NctiRenderInputEvent
	{
	public:
		NctiRenderMouseEvent();
		~NctiRenderMouseEvent();
		enum class Action
		{
			ButtonUp,
			ButtonDown,	
			Move,	
			Scroll,	
			Enter,	
			Leave
		};
	public:
		NctiRenderMouseEvent::Action CurrentAction;
		NctiPosition Location;		
		MouseButtons CurrentButton;
		Ncti_Double WheelDelta;		
		Ncti_Size ClickCount;
	};
}
#endif // !NctiRenderMouseEvent_H
