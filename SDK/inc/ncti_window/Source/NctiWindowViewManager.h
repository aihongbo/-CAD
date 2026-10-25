#ifndef NctiWindowViewManager_H
#define NctiWindowViewManager_H

#include "ncti_dcl_window.h"
#include "NctiWindowObject.h"
#include "map"

namespace NCTI
{
	class NctiBaseView;
	class NctiWindowView;
	class NctiDocument;
	class NctiWindowObject;
	/**
	* @brief manager oneself window view
	* @see NctiUserInterfaceManager
	*/
	class DECL_NCTI_WINDOW NctiWindowViewManager : public NctiWindowObject
	{
	public:
		virtual ~NctiWindowViewManager();
		/**
	   * @brief create a view manager
	   * @param[in] i_docid, the Document ID
       * @param[in] w width
       * @param[in] h height
	   * @return NctiWindowViewManager
	   */
        static NctiWindowViewManager* CreateViewMgr(Ncti_UInteger i_docId,int w,int h);
		/**
	   * @brief get a view manager by Document ID
	   * @param[in] i_docid, the Document ID
	   * @return NctiWindowViewManager
	   */
        static NctiWindowViewManager* GetViewMgr(Ncti_UInteger i_docId);
		/**
	   * @brief remove a view manager
	   * @param[in] i_doc
	   */
        static Ncti_Boolean RemoveViewMgr(Ncti_UInteger i_doc);
		/**
	   * @brief refresh the window
	   */
        void OnUpdate()override;

		/**
	   * @brief implement the resize function event
	   * @param[in] i_event, NctiWindowResizeEvent
	   */
        void resizeEvent(NctiWindowResizeEvent* i_event)override;

        /**
        * @brief Delete window
        * @param[in] i_baseViewId
        */
        Ncti_Boolean DeleteWindowView(NctiBaseView* i_baseViewId);

		/**
	   * @brief create window view
	   * @param[in] i_baseView
	   * @param[in] i_RenderModelType
	   */
        NctiWindowView* CreateWindowView(NctiBaseView* i_baseView, EnumRenderType i_RenderModelType);
		/**
	   * @brief activate window by NctiWindowView
	   * @param[in] i_win
	   * @param[in] i_activeBaseview
	   */
		void OnActivateWindow(NctiWindowView* i_win, Ncti_Boolean i_active);

		/**
	   * @brief activate window by NctiWindowView index
	   * @param[in] view
	   * @param[in] i_active
	   */
        void OnActivateView(NctiBaseView* view, Ncti_Boolean i_active);

		/**
	   * @brief SetViewVisible
	   * @param[in] i_view nullptr for current view
	   */
		void SetViewVisible(Ncti_Boolean i_show, NctiBaseView* i_view = nullptr);

		/**
	   * @brief GetWindowView
	   * @return NctiWindowView
	   */
        NctiWindowView* GetWindowView(NctiBaseView*)const;

		/**
	   * @brief get document of this
	   * @return NctiDocument
	   */
		NctiDocument* GetDocument();

	private:
		void InitControlPosition(Ncti_Integer i_w, Ncti_Integer i_h);
        NctiWindowViewManager(Ncti_Integer id,int w,int h);
        std::vector<std::pair<NctiBaseView*,NctiWindowView*>> m_ViewVec;
		Ncti_Integer m_docId{-1};
	};
}
#endif
