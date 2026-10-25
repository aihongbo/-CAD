#ifndef NctiWindowWheelEvent_H
#define NctiWindowWheelEvent_H
#include "NctiWindowEvent.h"
namespace NCTI
{
	/**
   * @brief window wheel event
   * @see NctiWindowEvent
   */
	class DECL_NCTI_WINDOW NctiWindowWheelEvent : public NctiWindowEvent
	{
	public:
		/**
	   * @brief set position offset
	   * @param[in] i_x
	   * @param[in] i_y
	   */
		void SetPosOffset(Ncti_Double i_x, Ncti_Double i_y);

		/**
	   * @brief get position offset x
	   * @return Ncti_Double
	   */
		Ncti_Double PosXOffset() { return m_xoffset; }
		/**
	   * @brief get position offset y
	   * @return Ncti_Double
	   */
		Ncti_Double PosYOffset() { return m_yoffset; }
	private:
        Ncti_Double m_xoffset{0};
        Ncti_Double m_yoffset{0};
	};
}
#endif
