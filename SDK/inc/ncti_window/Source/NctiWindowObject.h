#ifndef NctiWindowObject_H
#define NctiWindowObject_H
#include "ncti_dcl_window.h"
#include "ncti_base.h"
#include <vector>
#include <string>

class NctiWindowProxy;
namespace NCTI
{
    class NctiWindowEvent;
	class NctiWindowResizeEvent;
	class NctiWindowMouseEvent;
	class NctiWindowKeyEvent;
	class NctiWindowPlatform;
	class NctiWindowWheelEvent;
	class NctiWindowInputCharEvent;
	/**
	* @brief the base class of all window object
	* @see NctiUserInterfaceManager
	*/
	class DECL_NCTI_WINDOW NctiWindowObject
	{
	public:
		NctiWindowObject(const std::string&name,int w,int h);
		virtual ~NctiWindowObject();

        /**
        * @brief Close
        */
        void Close();

        /**
        * @brief Close
        */
        static void PoolEvent();

        /**
        * @brief set the parent handle of this
        * @param[in] i_handle, the window handle
        */
        void SetParent(Ncti_LongLong i_handle);

        /**
        * @brief SetFocus
        */
        void SetFocus();

        /**
        * @brief Add Child
        * @param[in] i_child
        */
        void AddChild(NctiWindowObject* i_child);

        /**
        * @brief IsChildren
        */
        Ncti_Boolean IsChild()const;

		/**
	   * @brief remove the child of window object
	   * @param[in] i_childe
	   */
        void RemoveChild(NctiWindowObject* i_childe);

        /**
        * @brief isVisible
        */
        Ncti_Boolean isVisible()const;
        /**
       * @brief setVisible
       */
        void setVisible(Ncti_Boolean);
        /**
        * @brief Update
        */
        void Update();
		/**
	   * @brief set the window object geometry of width and height
	   * @param[in] i_w
	   * @param[in] i_h
	   */
        void setSize(
			Ncti_Integer i_w, 
			Ncti_Integer i_h);
        /**
       * @brief set the window object pos
       * @param[in] i_x
       * @param[in] i_y
       */
        void setPos(
            Ncti_Integer i_x,
            Ncti_Integer i_y);
		/**
	   * @brief get the window object geometry of width and height
	   * @param[out] o_x
	   * @param[out] o_y
	   * @param[out] o_w
	   * @param[out] o_h
	   */
        void getSize(
			Ncti_Integer& o_w,
			Ncti_Integer& o_h);
		/**
	   * @brief hide the window object handle
	   * @return window handle
	   */
        Ncti_LongLong winId();

	public:
		/**
	   * @brief set position function event
	   * @details need to implement, override
	   * @param[in] i_x
	   * @param[in] i_y
	   */
		virtual void posEvent(NctiWindowEvent*){}
		/**
	   * @brief resize function event
	   * @details need to implement, override
	   * @param[in] i_event, NctiWindowResizeEvent
	   */
		virtual void resizeEvent(NctiWindowResizeEvent* i_event){}
		/**
	   * @brief key press function event
	   * @details need to implement, override
	   * @param[in] i_event, NctiWindowKeyEvent
	   */
		virtual void keyPressEvent(const NctiWindowKeyEvent* i_event){}
		/**
	   * @brief key release function event
	   * @details need to implement, override
	   * @param[in] i_event, NctiWindowKeyEvent
	   */
		virtual void keyReleaseEvent(const NctiWindowKeyEvent* i_event){}
		/**
	   * @brief key repeat function event
	   * @details need to implement, override
	   * @param[in] i_event, NctiWindowKeyEvent
	   */
		virtual void keyRepeatEvent(const NctiWindowKeyEvent* i_event){}
		/**
	   * @brief mouse press function event
	   * @details need to implement, override
	   * @param[in] i_event, NctiWindowMouseEvent
	   */
		virtual void mousePressEvent(NctiWindowMouseEvent* i_event){}
		/**
	   * @brief mouse release function event
	   * @details need to implement, override
	   * @param[in] i_event, NctiWindowMouseEvent
	   */
		virtual void mouseReleaseEvent(NctiWindowMouseEvent* i_event){}
		/**
	   * @brief mouse move function event
	   * @details need to implement, override
	   * @param[in] i_event, NctiWindowMouseEvent
	   */
		virtual void mouseMoveEvent(NctiWindowMouseEvent* i_event){}
		/**
	   * @brief enter leave function event
	   * @details need to implement, override
	   * @param[in] i_enter
	   */
        virtual void enterLeaveEvent(Ncti_Boolean i_enter) {};
		/**
	   * @brief mouse double click function event
	   * @details need to implement, override
	   * @param[in] i_enter, NctiWindowMouseEvent
	   */
		virtual void mouseDoubleClickEvent(NctiWindowMouseEvent* i_event){}
		/**
	   * @brief wheel function event
	   * @details need to implement, override
	   * @param[in] i_enter, NctiWindowWheelEvent
	   */
		virtual void wheelEvent(NctiWindowWheelEvent* i_event){}

    public:
        /**
        * @brief internal used
        */
        void set_mouth_pos(Ncti_Double i_x, Ncti_Double i_y);
        /**
       * @brief get mouse position of window object
       * @param[out] o_x
       * @param[out] o_y
       */
        void get_mouth_pos(Ncti_Double& o_x, Ncti_Double& o_y);

	protected:
        /**
        * @brief internal used
        */
        virtual void OnUpdate() {}
        Ncti_Boolean m_visible{false};

    private:
        std::string m_name;
        Ncti_Integer m_MousePosX{0};
        Ncti_Integer m_MousePosY{0};
        Ncti_Boolean m_IsChild{false};
        std::vector<NctiWindowObject*> m_ChildVec;
        NctiWindowProxy* m_proxy{ nullptr };
	};
}
#endif
