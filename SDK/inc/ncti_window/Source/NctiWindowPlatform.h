#ifndef NctiWindowPlatform_H
#define NctiWindowPlatform_H
#include "NctiWindowObject.h"
namespace NCTI
{
    class NctiDocument;
	class NctiWindowViewManager;
	/**
	* @brief manager all the NctiWindowViewManager
	* @see NctiWindowObject
	*/
	class DECL_NCTI_WINDOW NctiWindowPlatform : public NctiWindowObject
	{
	public:
		NctiWindowPlatform(int w,int h);
		virtual ~NctiWindowPlatform();
		/**
	   * @brief get the current view manager
	   * @return NctiWindowViewManager*
	   */
		NctiWindowViewManager* GetCurrentViewManager();
		/**
	   * @brief create view manager
	   * @param[in] i_docid, the Document ID
       * @return manager
	   */
        NctiWindowViewManager* CreateViewManager(NctiDocument* i_doc);
		/**
	   * @brief set current mgr
	   * @param[in] i_mgr
	   */
		void setCurrentView(NctiWindowViewManager* i_mgr);
		/**
	   * @brief implement the resize function event
	   * @param[in] i_event, NctiWindowResizeEvent
	   */
		void resizeEvent(NctiWindowResizeEvent* i_event) override;
		/**
	   * @brief close the current view
	   */
		void CloseCurrentView();

    private:
        NctiWindowViewManager* m_curWin=nullptr;
	};
}
#endif
