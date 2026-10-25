#ifndef NctiRenderInputEvent_H
#define NctiRenderInputEvent_H
#include "ncti_dcl.h"

#include "ncti_event.h"

namespace NCTI
{
	/**
	* @brief The Base Event Class
	*/
	class DECL_NCTI NctiRenderInputEvent
	{
	public:
		NctiRenderInputEvent();
		virtual ~NctiRenderInputEvent();
	public:
		ModifierKeys GetModifierKeys() const
		{
			return ModifierKeyState;
		}
		ModifierKeys ModifierKeyState;
	};
}
#endif // !NctiRenderInputEvent_H
