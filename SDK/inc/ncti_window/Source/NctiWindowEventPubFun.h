#ifndef NctiWindowEventPubFun_H
#define NctiWindowEventPubFun_H
#include "ncti_base.h"
#include "ncti_event.h"
#include "ncti_dcl_window.h"

namespace NCTI
{
    class NctiWindowObject;
    class DECL_NCTI_WINDOW NctiWindowEventPubFun
	{
	public:

        void handPoolEvent();

        void handButtonEvent(NctiWindowObject* i_window, MouseButtons i_button, ModifierKeys i_mods, ActionMode i_action);

        void handKeyEvent(NctiWindowObject* i_window, KeyboardCode i_key, ModifierKeys i_mods, ActionMode i_action);

        void handMoveEvent(NctiWindowObject* i_window, Ncti_Double i_x, Ncti_Double i_y);

        void handPosEvent(NctiWindowObject* i_window,Ncti_Integer i_x, Ncti_Integer i_y);

        void handSizeEvent(NctiWindowObject* i_window, Ncti_Integer i_x, Ncti_Integer i_y);

        void handScrollEvent(NctiWindowObject* i_window, Ncti_Double i_x, Ncti_Double i_y);

        void handEnterLeaveEvent(NctiWindowObject* i_window, Ncti_Boolean i_enter);

        void handUpdateEvent(NctiWindowObject* i_window);

        void handCloseEvent(NctiWindowObject* i_window);
	};
}

#endif
