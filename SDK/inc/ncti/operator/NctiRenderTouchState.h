#ifndef NctiRenderTouchState_H
#define NctiRenderTouchState_H
#include "ncti_dcl.h"
namespace NCTI
{
	class NctiRenderTouchEvent;
	/**
	* @brief touch screen state
	*/
	class DECL_NCTI NctiRenderTouchState
	{
	public:
		NctiRenderTouchState();
		virtual ~NctiRenderTouchState();
	public:
		NctiRenderTouchEvent* GetActiveEvent() { return m_TouchEvent; }
		void SetMouseEvent(NctiRenderTouchEvent* i_pRenderTouchEvent) { m_TouchEvent = i_pRenderTouchEvent; }
	private:
		NctiRenderTouchEvent* m_TouchEvent;
	};
}
#endif
