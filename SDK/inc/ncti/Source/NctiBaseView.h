#ifndef NctiBaseView_H
#define NctiBaseView_H
#include "ncti.h"
#include "NctiGridPickSet.h"
#include "NctiVector.h"
#include <map>
#include <vector>

namespace NCTI
{
    class NctiBaseModel;
	class NctiDisplayObjectList;
	class NctiDisplayObject;
    class NctiRenderSegmentItem;
    class NctiRenderKeyboardEvent;
    class NctiRenderTouchEvent;
    class NctiRenderOrbitOperator;
    class NctiRenderPanOperator;
    class NctiRenderMouseWheelOperator;
    class NctiRenderOperator;
    class NctiRenderMarkerItem;
    class NctiRenderTextItem;
    class NctiRenderSceneItem;
    class NctiRenderGeometryItem;
    class NctiViewerRenderer;
    class NctiRenderMouseEvent;
	/**
	* @brief the base view
	* @details manager render view
	* @see NctiBaseModel,NctiViewerRenderer
	*/
	class DECL_NCTI NctiBaseView : public NCTI_BASE_CLASS
	{
	public:
		NctiBaseView(const std::string& i_ViewName, NctiBaseModel* i_pBaseModel);
		virtual ~NctiBaseView();
		/**
	   * @brief refresh the render view
	   * @param[in] i_force, force to rebuild the scene
	   */
        void Update(Ncti_Boolean i_force = false);
		/**
	   * @brief get the scene item
	   * @return NctiRenderSceneItem
	   */
        NCTI::NctiRenderSceneItem* GetScene();

        /**
       * @brief NewPreviewKey
       * @param[in] i_name kdy identyfy or randon key
       */
        NCTI::NctiRenderSegmentItem* NewPreviewKey(const char* i_name = nullptr)const;

		/**
	   * @brief get the base view name
	   * @return const char*
	   */
        const char* GetViewName();
		/**
	   * @brief get the next base view
	   * @return NctiBaseView
	   */
		NctiBaseView* GetNextView();
		/**
	   * @brief set the next base view
	   * @param[in] i_pBaseView, the next base view
	   */
		void SetNextView(NctiBaseView* i_pBaseView);
		/**
	   * @brief get the base model
	   * @return NctiBaseModel
	   */
		NctiBaseModel* GetBaseModel();

		/**
	   * @brief save the camera to base view from scene key
	   */
		void SaveCamera();
		/**
	   * @brief set the camera to scene key
	   */
		void RestoreCamera();
		/**
	   * @brief get the camera from scene key of base view
	   * @param[out] o_pos, the eye
	   * @param[out] o_tar, the target
	   * @param[out] o_up, the up vector
	   */
		void GetCameraInfo(NctiPosition& o_pos,NctiPosition& o_tar,NctiVector& o_up);
		/**
	   * @brief set the camera to scene key of base view
	   * @param[in] o_pos, the eye
	   * @param[in] o_tar, the target
	   * @param[in] o_up, the up vector
	   */
		void SetCameraInfo(const NctiPosition& i_pos, const NctiPosition& i_tar, const NctiVector& i_up);
		/**
	   * @brief zoom the render view by geometry
	   * @param[in] i_objs, if i_objs is empty, use all the geometry
	   */
        void Zoom(const std::vector<NctiRenderGeometryItem*>& i_objs = {});
		/**
	   * @brief zoom the render view by ptMin and ptMax
	   * @param[in] i_ptMin
	   * @param[in] i_ptMax
	   */
        void ZoomToBox(const NctiPosition& i_ptMin, const NctiPosition& i_ptMax);
		/**
	   * @brief get PrevHighlight segment and geometry
	   * @param[in] o_ins
	   * @return NctiRenderGeometryItem
	   */
        NctiRenderGeometryItem* GetPrevHighlightItem(NctiRenderSegmentItem** o_ins=nullptr);
		/**
	   * @brief set PrevHighlight segment and geometry
	   * @param[in] i_pGeometryItem
	   * @param[in] i_ins
	   */
        void SetPrevHighlightItem(NctiRenderGeometryItem* i_pGeometryItem, NctiRenderSegmentItem* i_ins=nullptr);

		/**
	   * @brief get PrevPosition
	   * @return NctiPosition
	   */
        NctiPosition GetPrevPosition();
		/**
	   * @brief set PrevPosition
	   * @param[out] o_pt
	   */
        void SetPrevPosition3D(const NctiPosition& i_pt);

		/**
	   * @brief internal used
	   */
        void SetViewMode(EnumNctiViewMode i_eViewMode);
		/**
	   * @brief get render view
	   * @return NctiViewerRenderer
	   */
		NctiViewerRenderer* GetRenderCanvas();
		/**
	   * @brief SetRenderCanvas
	   * @param[in] i_pRendererView
	   */
		void SetRenderCanvas(NctiViewerRenderer* i_pRendererView);
		/**
	   * @brief point select 
	   * @param[in] i_windowX, -1 to 1
	   * @param[in] i_windowY, -1 to 1
	   * @param[out] o_RenderThreadTaskHelpVec
	   * @return Ncti_Boolean
	   */
        Ncti_Boolean PointSelectOnSegment(Ncti_Double i_windowX, Ncti_Double i_windowY,
            std::vector<NctiPickSelectObjectStr>& o_RenderThreadTaskHelpVec);


		/**
	   * @brief box select
	   * @param[in] i_ptMin min window coord,-1~1
	   * @param[in] i_ptMax max window coord,-1~1
	   * @param[out] o_RenderGeometryItemVec
	   * @return Ncti_Boolean
	   */
        Ncti_Boolean BoxSelectOnSegment(NctiPosition i_ptMin, NctiPosition i_ptMax,
            std::vector<NctiPickSelectObjectStr>& o_RenderGeometryItemVec);
		/**
	   * @brief use in a window view,internal used
	   */
        void RunOpeator(NctiRenderMouseEvent* i_pRenderMouseEvent);
		/**
	   * @brief use in a window view,internal used
	   */
        void RunOpeator(NctiRenderKeyboardEvent* i_pRenderKeyboardEvent);
		/**
	   * @brief use in a window view,internal used
	   */
        void RunOpeator(NctiRenderTouchEvent* i_pRenderTouchEvent);
		/**
	   * @brief add the operator to base view by name
	   * @param[in] i_OperatorName, the operator name
	   * @param[in] i_pRenderOperator, create a operator
	   */
        void AddOperator(const std::string &i_OperatorName, NctiRenderOperator* i_pRenderOperator);
		/**
	   * @brief remove the operator to base view by name
	   * @param[in] i_OperatorName, the operator name
	   */
        void RemoveOperator(const std::string &i_OperatorName);
		/**
	   * @brief set the orbit operator status
	   * @param[in] i_OperatorName, the operator name
	   */
        void SetOpenOrbitOperator(Ncti_Boolean i_boo);
		/**
	   * @brief set the pan operator status
	   * @param[in] i_OperatorName, the operator name
	   */
        void SetOpenPanOperator(Ncti_Boolean i_boo);
		/**
	   * @brief set the wheel operator status
	   * @param[in] i_OperatorName, the operator name
	   */
        void SetOpenWheelOperator(Ncti_Boolean i_boo);
	public:
		/**
	   * @brief internal used
	   */
		NctiDisplayObjectList* GetCameraCallbackList();
		/**
	   * @brief internal used
	   */
		NctiDisplayObjectList* GetViewUnitLengthCallbackList();
		/**
	   * @brief internal used
	   */
		NctiDisplayObjectList* GetRedrawDoInstanceList();
		/**
	   * @brief internal used
	   */
		NctiDisplayObjectList* GetInstanceList() { return m_pInstanceList; }
		/**
	   * @brief set doc app instance
	   * @param[in] i_pDocAppIns
	   */
		void SetDocApplicationInstance(NctiDisplayObject* i_pDocAppIns);
		/**
	   * @brief get doc app instance
	   * @param[in] i_pDocAppIns
	   */
		NctiDisplayObject* GetDocApplicationInstance() { return m_pDocApplicationInstance; };
		/**
	   * @brief internal used
	   */
		void SetInstanceList(NctiDisplayObjectList* i_pInstanceList);
		/**
	   * @brief internal used
	   */
		void ExecuteCameraCallback();
		/**
	   * @brief internal used
	   */
		void OnPaint();
		/**
	   * @brief internal used
	   */
		Ncti_Boolean ExecuteViewUnitLengthCallback();
		/**
	   * @brief get the first element of doc app instance
	   * @return NctiDisplayObject
	   */
		NctiDisplayObject* GetRootDocInstance();
		/**
	   * @brief internal used
	   */
		NctiDisplayObject* GetDisplayViewObject(const char* i_pszDoViewID);
		/**
	   * @brief internal used
	   */
		void RedrawDoInstance();
		/**
	   * @brief internal used
	   */
		void NotifySelectionDataChanged();
		/**
	   * @brief internal used
	   */
		Ncti_Double GetViewUnitLength();
	private:
		/**
	   * @brief internal used
	   */
        void clear_display_object_instances();
		/**
	   * @brief internal used
	   */
        void clear_do_callback_lists();
		/**
	   * @brief internal used
	   */
        void set_display_object_instances();
		/**
	   * @brief internal used
	   */
        void reset_view_object_callbacks();
	private:
		NctiBaseModel* m_pBaseModel{nullptr};
		NctiRenderSceneItem* m_SceneKey{ nullptr };

		NctiViewerRenderer* m_RenderCanvas{ nullptr };
        NctiDisplayObjectList* m_pInstanceList{nullptr};
		NctiDisplayObjectList* m_pCameraCallbackList;
		NctiDisplayObjectList* m_pViewUnitLengthCallbackList;
		NctiDisplayObjectList* m_pRedrawCallbackList;

        NctiDisplayObject* m_pDocApplicationInstance{ nullptr };
		Ncti_Boolean m_bOnPaintDone;
		Ncti_Boolean m_bNeedRedraw;
		Ncti_Double m_dViewUnitLength;
		std::string m_ViewName;

        NctiBaseView* m_pNextBaseView{nullptr};
		NctiPosition m_bpos,m_btar;
		NctiVector m_bup;
        NctiRenderSegmentItem* m_prevIns{nullptr};
        NctiRenderGeometryItem* m_prevObj{nullptr};
        NctiPosition m_prevPosition3D;

    private:
		NctiRenderOrbitOperator* m_OrbitOperator{nullptr};
        Ncti_Boolean m_OpenOrbitOperator{ true };
        NctiRenderPanOperator* m_PanOperator{ nullptr };
        Ncti_Boolean m_OpenPanOperator{ true };
        NctiRenderMouseWheelOperator* m_WheelOperator{ nullptr };
        Ncti_Boolean m_OpenWheelOperator{ true };
		std::map<std::string, NctiRenderOperator*> m_RenderOperatorMap;
	};
}
#endif // !NctiBaseView_H
