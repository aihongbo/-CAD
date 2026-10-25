#ifndef NctiRenderTouchEvent_H
#define NctiRenderTouchEvent_H
#include "NctiRenderInputEvent.h"
#include "NctiPosition.h"
#include <vector>
namespace NCTI
{
	struct NctiTouchPoint
	{
		NctiPosition m_StartPos;
		NctiPosition m_EndPos;
		NctiPosition m_Pos;
		NctiTouchPoint()
		{
			m_StartPos = NctiPosition(0, 0, 0);
			m_EndPos = NctiPosition(0, 0, 0);
			m_Pos = NctiPosition(0, 0, 0);
		}
	};
	/**
	* @brief touch screen event
	*/
	class DECL_NCTI NctiRenderTouchEvent : public NctiRenderInputEvent
	{
	public:
		NctiRenderTouchEvent();
		~NctiRenderTouchEvent();
		enum class Action
		{
			TouchBegin,
			TouchUpdate,
			TouchEnd
		};
	public:
		NctiRenderTouchEvent::Action CurrentAction;
		std::vector<NctiTouchPoint> touchPoints;
	};
}
#endif
