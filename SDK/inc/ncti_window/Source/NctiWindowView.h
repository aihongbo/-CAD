#ifndef NctiWindowView_H
#define NctiWindowView_H
#include "NctiWindowObject.h"
#include "NctiRenderKeyboardEvent.h"
#include "NctiRenderMouseEvent.h"
namespace NCTI
{
	class NctiBaseView;
	class NctiWindowViewManager;
	class NctiViewerRenderer;
	/**
	* @brief the window view, display render data
	* @see NctiWindowObject
	*/
	class DECL_NCTI_WINDOW NctiWindowView : public NctiWindowObject
	{
	public:
		NctiWindowView(const std::string& name, int w,int h);
		virtual ~NctiWindowView();

		/**
	   * @brief Initialization during obj class creation by NctiBaseView
	   * @param[in] i_pBaseView, the base view 
       * @param[in] i_mgr
       * @param[in] i_Type render type
	   */
        NctiViewerRenderer* InitRender(NctiWindowViewManager*i_mgr, NctiBaseView* i_pBaseView, EnumRenderType i_Type);

        /**
       * @brief ReInit
       */
        void ReInit();

		/**
	   * @brief get base view
	   * @return NctiBaseView*
	   */
		NctiBaseView* GetBaseView();

        /**
       * @brief window pos change
       */
        void posEvent(NctiWindowEvent*)override;

		/**
	   * @brief implement the resize function event
	   * @param[in] i_event, NctiWindowResizeEvent
	   */
        void resizeEvent(NctiWindowResizeEvent* i_event) override;
		/**
	   * @brief implement key press function event
	   * @param[in] i_event, NctiWindowKeyEvent
	   */
        void keyPressEvent(const NctiWindowKeyEvent* i_event) override;
		/**
	   * @brief implement key release function event
	   * @param[in] i_event, NctiWindowKeyEvent
	   */
        void keyReleaseEvent(const NctiWindowKeyEvent* i_event) override;
		/**
	   * @brief implement mouse press function event
	   * @param[in] i_event, NctiWindowMouseEvent
	   */
        void mousePressEvent(NctiWindowMouseEvent* i_event) override;
		/**
	   * @brief implement mouse release function event
	   * @param[in] i_event, NctiWindowMouseEvent
	   */
        void mouseReleaseEvent(NctiWindowMouseEvent* i_event) override;
		/**
	   * @brief implement mouse move function event
	   * @param[in] i_event, NctiWindowMouseEvent
	   */
        void mouseMoveEvent(NctiWindowMouseEvent* i_event) override;
		/**
	   * @brief implement mouse double click function event
	   * @param[in] i_enter, NctiWindowMouseEvent
	   */
        void mouseDoubleClickEvent(NctiWindowMouseEvent* i_event) override;
		/**
	   * @brief implement wheel function event
	   * @param[in] i_enter, NctiWindowWheelEvent
	   */
        void wheelEvent(NctiWindowWheelEvent* i_event) override;
		/**
	   * @brief implement enter leave function event
	   * @param[in] i_enter
	   */
        void enterLeaveEvent(bool enter)override;

        /**
       * @brief render update
       */
        void OnUpdate()override;

	private:
		/**
		* @brief internal used
		*/
		void buildMouseEvent(
			NctiWindowMouseEvent* i_event,
			NctiRenderMouseEvent::Action i_action,
			Ncti_UInteger i_click_count);
		/**
		* @brief internal used
		*/
		void buildKeyboardEvent(
            const NctiWindowKeyEvent* i_event,
			NctiRenderKeyboardEvent::Action i_action);

    private:
        Ncti_Boolean m_RightMove{false};
        Ncti_Boolean m_Right{ false };
        NctiBaseView* m_BaseView{nullptr};
        NctiWindowViewManager* m_mgr{nullptr};
        NctiViewerRenderer* m_RenderCanvas{ nullptr };
	};
}
#endif
