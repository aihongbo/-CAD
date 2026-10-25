#ifndef NctiWindowResizeEvent_H
#define NctiWindowResizeEvent_H
#include "NctiWindowEvent.h"
namespace NCTI
{
	/**
   * @brief window resize event
   * @see NctiWindowEvent
   */
	class DECL_NCTI_WINDOW NctiWindowResizeEvent : public NctiWindowEvent
	{
	public:
		/**
	   * @brief set window size w h
	   * @param[in] i_w
	   * @param[in] i_h
	   */
		void SetWH(Ncti_Integer i_w, Ncti_Integer i_h);
		/**
	   * @brief get window size w h
	   * @param[out] o_w
	   * @param[out] o_h
	   */
		void GetWH(Ncti_Integer& o_w, Ncti_Integer& o_h);
	private:
        Ncti_Integer m_width{0};
        Ncti_Integer m_height{0};
	};
}
#endif
