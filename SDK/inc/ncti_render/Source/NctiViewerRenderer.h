#ifndef NctiViewerRenderer_H
#define NctiViewerRenderer_H

#include "NctiRGBAColor.h"
#include "vector"
#include "NctiGridPickSet.h"

namespace NCTI
{
    struct NctiViewerRendererPrivateData;
    class NctiRenderSceneItem;
    class NctiRenderSegmentItem;

    class NctiRenderKit;
    class NctiRenderDrawingKit;
    class NctiRenderFeatureKit;
    class NctiRenderMaterialKit;
    class NctiRenderVisSelKit;
    class NctiRenderCamaraKit;

    class NctiRenderImageItem;
    class NctiRenderTriangleItem;
    class NctiRenderPolylineItem;
    class NctiRenderMarkerItem;
    class NctiRenderTextItem;
    class NctiRenderUnstructureItem;

    /**
     * @brief Render base class
     */
    class DECL_NCTI_RENDER NctiViewerRenderer
    {
    public:
        NctiViewerRenderer();
        virtual ~NctiViewerRenderer();

        /**
         * @brief GetRenderInfo
         */
        virtual std::string GetRenderInfo()const;

        /**
         * @brief RenderName
         */
        void SetRenderName(const std::string&);
        const std::string& RenderName()const;
        /**
         * @brief DestryoyMode for speed up Destroy
         */
        void SetDestryoyMode();

        /**
         * @brief is in DestryoyMode
         */
        bool IsDestroyMode()const;

        /**
         * @brief EngenType
         */
        void SetEngenType(EnumRenderType);

        /**
         * @brief GetEngenType
         */
        EnumRenderType GetEngenType()const;

        /**
         * @brief scene tree is modify
         */
        Ncti_Boolean GetsTreeModify();

        /**
         * @brief set scene tree modify
         * @details when modify ,the scene will rebuild on display
         */
        void SetsTreeModify();  

        /**
         * @brief get the select type
         */
        NctiSelectType GetSelectElementType()const;

        /**
         * @brief set the select type
         */
        void SetSelectElementType(NctiSelectType i_SelectElementType);

        /**
         * @brief OnWindowInit
         * @details render should init the window from the handle
         */
        virtual void OnWindowInit(Ncti_LongLong i_window_handle) = 0;

        /**
         * @brief modify the window size
         * @details window resize event
         * @see NctiRenderSceneItem::GetWindowSize
         */
        virtual void OnWindowChange(const std::vector<NCTI::NctiRenderCamaraKit*>&) = 0;

        /**
         * @brief OnRender
         * @details render event
         * @return true for do render
         */
        virtual bool OnRender() = 0;

        /**
         * @brief OnCameraChange
         * @details camera change event
         * @param[in] camaras
         * @see NctiRenderSceneItem::GetCameraInfo
         */
        virtual void OnCameraChange(const std::vector<NCTI::NctiRenderCamaraKit*>& camaras) = 0;

        /**
         * @brief OnLightChange
         * @details light change event
         * @param[in] light point light
         * @param[in] index light index
         * @see NctiRenderSceneItem::ShowPointLightAtt
         */
        virtual void OnLightChange(const NCTI::PointLightAtt& light, Ncti_Integer index) {};

        /**
         * @brief OnBackGroundChange
         * @param[in] c1 top color
         * @param[in] c2 bottom color
         */
        virtual void OnBackGroundChange(const RGBAColor& c1, const RGBAColor& c2) = 0;

        /**
         * @brief OnSceneRebuld
         * @details SceneRebuld event
         * @param[in] onlyPreview only rebuild the preview
         * @return success
         */
        virtual bool OnSceneRebuld(bool onlyPreview) = 0;

        /**
         * @brief the item no exist any more,render should destroy the resource with it
         * @param[item] NctiRenderSegmentItem to be delete
         */
        virtual void DeleteSegementItem(NctiRenderSegmentItem* item) {}

        /**
         * @brief DrawTriangleItem
         */
        virtual void DrawTriangleItem(const std::vector<NctiRenderTriangleItem*>&) {}

        /**
         * @brief DrawPoliLineItem
         */
        virtual void DrawPoliLineItem(const std::vector<NctiRenderPolylineItem*>&) {}

        /**
         * @brief DrawMarkerItem
         */
        virtual void DrawMarkerItem(const std::vector<NctiRenderMarkerItem*>&) {}

        /**
         * @brief DrawTextItem
         */
        virtual void DrawTextItem(const std::vector<NctiRenderTextItem*>&) {}

        /**
         * @brief DrawGridItem
         */
        virtual void DrawGridItem(const std::vector<NctiRenderUnstructureItem*>&) {}

        /**
         * @brief DrawGridItem
         */
        virtual void DrawImageItem(const std::vector<NctiRenderImageItem*>&) {};

        /**
         * @brief Point Select
         * @param[in] posx window pos x ,-1~1
         * @param[in] posy window pos y,-1~1
         * @param[out] o_sel pick result
         * @see NctiPickSelectObjectStr
         */
        virtual bool GetPointSelectData(Ncti_Double posx, Ncti_Double posy, std::vector<NctiPickSelectObjectStr>& o_sel);

        /**
         * @brief Box Select
         * @param[in] i_st start window pos -1~1
         * @param[in] i_ed end window pos -1~1
         * @param[out] o_sel pick result
         * @see NctiPickSelectObjectStr
         */
        virtual bool GetBoxSelectData(const NctiPosition&i_st, const NctiPosition&i_ed, std::vector<NctiPickSelectObjectStr>&);

        /**
         * @brief get the current scene display image
         * @param[out] o_Buffer image data
         * @param[out] o_w image width
         * @param[out] o_h image hight
         * @param[out] o_rowPitch image row pitch
         */
        virtual void GetImageData(std::vector<unsigned char>& o_Buffer, Ncti_Integer& o_w, Ncti_Integer& o_h, Ncti_Integer& o_rowPitch);

        /**
         * @brief highlight the geometry item
         * @param[in] i_pGeometryItem item to be operate
         * @param[in] high highlight or dis highlight
         * @param[in] ins instance flag for multi render
         */
        virtual void Highlight(NctiRenderGeometryItem* i_pGeometryItem, bool high, NctiRenderSegmentItem* ins = nullptr) {};

        /**
         * @brief highlight the segment item
         * @param[in] i_pSegmentItem item to be operate
         * @param[in] high highlight or dis highlight
         * @param[in] ins instance flag for multi render
         */
        virtual void Highlight(NctiRenderSegmentItem* i_pSegmentItem, bool high, NctiRenderSegmentItem*ins = nullptr) {};

        /**
         * @brief prev highlight the geometry item
         * @param[in] i_pSegmentItem item to be operate
         * @param[in] high highlight or dis highlight
         * @param[in] ins instance flag for multi render
         */
        virtual void PreHighlight(NctiRenderGeometryItem* i_pSegmentItem, bool high, NctiRenderSegmentItem* ins = nullptr) {};

        /**
         * @brief visible the geometry item
         * @param[in] i_pRenderGeometryItem item to be operate
         * @param[in] i_visible vis or hide
         * @param[in] ins instance flag for multi render
         */
        virtual void SetVisible(NctiRenderGeometryItem* i_pRenderGeometryItem, Ncti_Boolean i_visible, NctiRenderSegmentItem* ins = nullptr) {}

        /**
         * @brief visible the geometry item
         * @param[in] i_pSegmentItem item to be operate
         * @param[in] i_visible vis or hide
         * @param[in] ins instance flag for multi render
         */
        virtual void SetVisible(NctiRenderSegmentItem* i_pSegmentItem, Ncti_Boolean i_visible, NctiRenderSegmentItem* ins = nullptr) {}

        /**
         * @brief get visible of the geometry item
         * @param[in] i_pRenderGeometryItem item to be operate
         * @param[in] ins instance flag for multi render
         * @return vis
         */
        virtual Ncti_Boolean GetVisible(NctiRenderGeometryItem* i_pRenderGeometryItem, NctiRenderSegmentItem* ins = nullptr) { return true; }

        /**
         * @brief re transform data from CPU to GPU
         * @param[in] i_pRenderGeometryItem item to be operate
         */
        virtual void UpdateVertexBuffer(NctiRenderGeometryItem* i_pRenderGeometryItem,NctiRenderSegmentItem* ins = nullptr) {}

        /**
         * @brief rebind the render command
         * @param[in] i_pRenderGeometryItem item to be operate
         */
        virtual void RebindVertexBuffer(NctiRenderGeometryItem* i_pRenderGeometryItem, NctiRenderSegmentItem* ins = nullptr) {}

        /**
         * @brief internal usage
         */
        void BackUpKit();
        /**
         * @brief internal usage
         */
        void RevertKit();
        /**
         * @brief internal usage
         */
        NctiRenderKit* GetKit(int i)const;
        /**
         * @brief internal usage
         */
        NctiRenderDrawingKit* GetDrawingAttributeKit();
        /**
         * @brief internal usage
         */
        NctiRenderFeatureKit* GetFeatureAttributeKit();
        /**
         * @brief internal usage
         */
        NctiRenderMaterialKit* GetMaterialMappingKit();
        /**
         * @brief internal usage
         */
        NctiRenderVisSelKit* GetSelectabilityKit();
        /**
         * @brief internal usage
         */
        NctiRenderVisSelKit* GetVisibilityKit();
        /**
         * @brief internal usage
         */
        void initRenderParam(bool start);
        void getCalcuBox(NctiPosition& min, NctiPosition& max)const;
        bool DrawSegment(NctiRenderSegmentItem*);
        void SetCurrentInstance(NctiRenderSegmentItem*);
        NctiRenderSegmentItem* GetCurrentInstance();

    private:
        NctiViewerRendererPrivateData* _d;
    };
}
#endif // !NctiViewerRenderer_H
