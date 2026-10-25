#ifndef NctiWindowEvent_H
#define NctiWindowEvent_H
#include "ncti_dcl_window.h"
#include "ncti_base.h"
#include "ncti_event.h"

namespace NCTI
{
    class NctiWindowObject;
    /**
   * @brief the base class of window event
   */
    class DECL_NCTI_WINDOW NctiWindowEvent
    {
    public:

        void SetModifierKeys(ModifierKeys i_modKeys);
        ModifierKeys GetModifierKeys() const;

        /**
       * @brief set position
       * @param[in] i_x
       * @param[in] i_y
       */
        void SetPos(Ncti_Double i_x, Ncti_Double i_y);

        /**
        * @brief get position x
        * @return Ncti_Double
        */
        Ncti_Double PosX();

        /**
       * @brief get position y
       * @return Ncti_Double
       */
        Ncti_Double PosY();

    private:
        ModifierKeys m_modKeys;
        Ncti_Double m_x{ 0 };
        Ncti_Double m_y{ 0 };
    };
}
#endif
