#ifndef NctiRenderKeyboardEvent_H
#define NctiRenderKeyboardEvent_H
#include "NctiRenderInputEvent.h"
#include "ncti_event.h"
#include <vector>
namespace NCTI
{
	/**
	* @brief Keyboard Event
	*/
	class DECL_NCTI NctiRenderKeyboardEvent : public NctiRenderInputEvent
	{
	public:
		NctiRenderKeyboardEvent();
		~NctiRenderKeyboardEvent();
		enum class Action
		{
			None,		
			KeyDown,	
			KeyUp		
		};
	public:
		NctiRenderKeyboardEvent::Action CurrentAction;
		std::vector<KeyboardCode> KeyboardCodes;
	};
}
#endif // !NctiRenderKeyboardEvent_H
