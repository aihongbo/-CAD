#pragma once

#include "NctiRenderObject.h"
#include "string"
#include "ncti_include.h"
#include "NctiPosition.h"
#include "NctiGridPickSet.h"


namespace NCTI
{
    class NctiMeshBody;
    class NctiRenderGeometryItem;
    class NctiRenderPolylineItem;
    class NctiRenderTriangleItem;
    class NctiRenderMarkerItem;
    class NctiRenderUnstructureItem;
    class NctiRenderTextItem;
    class NctiRenderImageItem;

    class NctiRenderKit;
    class NctiRenderVisSelKit;
    class NctiRenderMaterialKit;
    class NctiRenderFeatureKit;
    class NctiRenderDrawingKit;

    class NctiViewerRenderer;
    class NctiRenderKit;
    struct NctiRenderSegmentItemPrivateData;

    /**
     * @brief Segment to compose the scene tree or object tree
     */
    class DECL_NCTI_RENDER NctiRenderSegmentItem : public NctiRenderObject
    {
        NCTI_RENDER_FUNCTIONS(NctiRenderSegmentItem);
    public:
        NctiRenderSegmentItem();
        virtual ~NctiRenderSegmentItem();

        /**
         * @brief get name
         */
        const char* Name()const;

        /**
         * @brief set name
         */
        void SetName(const Ncti_Char* i_cpName);

        /**
         * @brief get the bounding box of this item
         * @param[in] i_pViewerRenderer the render to display this item
         * @param[out] i_Max the max position
         * @param[out] i_Min the min position
         */
        Ncti_Boolean GetBox(NctiViewerRenderer* i_pViewerRenderer, NctiPosition& i_Max, NctiPosition& i_Min);

        /**
         * @brief clear the geometry item in this item
         * @param[in] i_type geometry type. nullptr for all types
         */
        void Flush(const char* i_type = nullptr);

        /**
         * @brief unlink the sub segment
         */
        void UnlinkSubsegment();

        /**
         * @brief touch the sub segment
         * @param[in] i_cpName name.nullptr for auto generate
         * @param[in] i_new true for speed up create with no look up duplicated
         * @param[in] i_IsInstanceKey if is instance
         */
        NctiRenderSegmentItem* Subsegment(const Ncti_Char* i_cpName = nullptr, Ncti_Boolean i_new = false, Ncti_Boolean i_IsInstanceKey = false);

        /**
         * @brief get sub segment item
         * @param[out] o_SubSegmentItemVec sub segment items
         * @param[in] i_booSegChild if search child
         * @param[in] i_booSegInc if search inc item
         */
        void GetSubSegmentItemVec(std::vector<NctiRenderSegmentItem*>& o_SubSegmentItemVec, Ncti_Boolean i_booSegChild = false,Ncti_Boolean i_booSegInc = false)const;
        
        /**
         * @brief static the geometry items
         * @return all geometry items count
         */
        Ncti_Integer GetEndSegmentItemCount();

        /**
         * @brief  sub geometry no child and inc
         */
        const std::vector<NctiRenderGeometryItem*>& GetSubGeomtryItemVec()const;

        /**
         * @brief get sub geometry item
         * @param[out] o_SubGeometryItemVec sub items
         * @param[in] i_booSegChild if search child
         * @param[in] i_insCount instance display count each geometry
         * @param count internal used in loop
         */
        void GetSubGeometryItemVec(std::vector<NctiRenderGeometryItem*>& o_SubGeometryItemVec, Ncti_Boolean i_booSegChild = false, std::vector<Ncti_Integer>* i_insCount = nullptr,Ncti_Integer* count = nullptr);

        /**
         * @brief get all sub geometry item visible
         * @details GetSubGeomtryItemVecVis();
         */
        void GetSubGeomtryItemVecVis(std::vector<NctiPickSelectObjectStr>& o_SubGeometryItemVec)const;


        /**
         * @brief Insert Vertex item
         * @param[in] i_pt vertex position
         * @return NctiRenderMarkerItem
         */
        NctiRenderMarkerItem* InsertVertex(const NctiPosition& i_pt);

        /**
         * @brief Insert Grid item
         * @param[in] body mesh body
         * @return NctiRenderUnstructureItem
         */
        NctiRenderUnstructureItem* InsertUnstructureGrid(NctiMeshBody* body);

        /**
         * @brief Insert PolyLine item
         * @param[in] i_PositionVec poly line positions
         * @return NctiRenderPolylineItem
         */
        NctiRenderPolylineItem* InsertLine(const std::vector<Ncti_Float>& i_PositionVec);

        /**
         * @brief Insert PolyLine item
         * @param[in] i_PositionVec poly line positions
         * @return NctiRenderPolylineItem
         */
        NctiRenderPolylineItem* InsertLine(const std::vector<Ncti_Double>& i_PositionVec);

        /**
         * @brief Insert PolyLine item
         * @param[in] i_ptS first position
         * @param[in] i_ptE second position
         * @return NctiRenderPolylineItem
         */
        NctiRenderPolylineItem* InsertLine(const NctiPosition& i_ptS, const NctiPosition& i_ptE);

        /**
         * @brief Insert Triangle item
         * @param[in] i_NctiMeshData face data
         * @return NctiRenderTriangleItem
         */
        NctiRenderTriangleItem* InsertTriangle(const NctiMeshData& i_NctiMeshData);

        /**
         * @brief Insert Triangle item
         * @param[in] i_positions vertex positions
         * @param[in] i_triangles triangle indexes
         * @param[in] i_normals vertex normals.empty for auto calculate
         * @return NctiRenderTriangleItem
         */
        NctiRenderTriangleItem* InsertTriangle(const std::vector<Ncti_Float>& i_positions, const std::vector<Ncti_UInteger>& i_triangles, const std::vector<Ncti_Float>& i_normals);
       
         /**
         * @brief Insert Triangle item
         * @param[in] i_ptVec vertex positions
         * @param[in] i_triangles triangle indexes
         * @return NctiRenderTriangleItem
         */
        NctiRenderTriangleItem* InsertShell(const std::vector<NctiPosition>& i_ptVec, const std::vector<Ncti_UInteger>& i_triangles);

        /**
        * @brief Insert Triangle item
        * @param[in] i_positions vertex positions
        * @param[in] i_triangles triangle indexes
        * @return NctiRenderTriangleItem
        */
        NctiRenderTriangleItem* InsertShell(const std::vector<Ncti_Float>& i_positions, const std::vector<Ncti_UInteger>& i_triangles);

        /**
        * @brief Insert Text item
        * @param[in] text text to display
        * @param[in] i_pt text position
        * @param[in] size text size in pixel
        * @param[in] x text x align
        * @param[in] y text y align
        * @return NctiRenderTextItem
        */
        NctiRenderTextItem* InsertText(const char* text, const NctiPosition& i_pt,
            Ncti_Integer size = 16, RenderAlgnX x= e_alx_center, RenderAlgnY y= e_aly_top);

        /**
        * @brief Insert multi line Text item
        * @param[in] text text to display
        * @param[in] i_pt text position
        * @param[in] size text size in pixel
        * @param[in] x text x align
        * @param[in] y text y align
        * @return NctiRenderTextItem
        */
        NctiRenderTextItem* InsertText(const std::vector<std::wstring>& i_name, const NctiPosition& i_pt,
            Ncti_Integer size = 16, RenderAlgnX = e_alx_center, RenderAlgnY = e_aly_top);

        /**
        * @brief Insert image item
        * @param[in] i_pt text position
        * @param[in] i_PixelW image width
        * @param[in] i_PixelH image hight
        * @param[in] i_ImageId image file
        * @return NctiRenderImageItem
        */
        NctiRenderImageItem* InsertImage(const NctiPosition& i_pt, Ncti_UInteger i_PixelW, Ncti_UInteger i_PixelH, const char* i_ImageId);
        
        /**
        * @brief GetVisibilityControl
        * @param[in] i_force force crate
        * @return NctiRenderVisSelKit
        */
        NctiRenderVisSelKit* GetVisibilityControl(Ncti_Boolean i_force = true);

        /**
        * @brief GetVisibilityControl
        * @param[in] i_force force crate
        * @return NctiRenderVisSelKit
        */
        NctiRenderVisSelKit* GetSelectabilityControl(Ncti_Boolean i_force = true);

        /**
        * @brief GetFeatureControl
        * @param[in] i_force force crate
        * @return NctiRenderFeatureKit
        */
        NctiRenderFeatureKit* GetFeatureControl(Ncti_Boolean i_force = true);

        /**
        * @brief GetDrawingAttributeControl
        * @param[in] i_force force crate
        * @return NctiRenderDrawingKit
        */
        NctiRenderDrawingKit* GetDrawingAttributeControl(Ncti_Boolean i_force = true);

        /**
        * @brief GetMaterialMappingControl
        * @param[in] i_force force crate
        * @return NctiRenderMaterialKit
        */
        NctiRenderMaterialKit* GetMaterialMappingControl(Ncti_Boolean i_force = true);

        /**
         * @brief internal usage
         */
        NctiRenderSegmentItem* GetIncludeSegment()const;
        void IncludeSegment(NctiRenderSegmentItem* i_pSegmentItem);
        void RemoveIncludeSegment();
        Ncti_Boolean IsInstanceKey()const;

        /**
         * @brief internal usage
         */
        Ncti_UInteger UpdateRebuild(NctiViewerRenderer* i_pViewerRenderer);
        void GetIncludeOwnerVec(std::vector<NctiRenderSegmentItem*>& o_IncludeOwnerVec)const;
        void RemoveItem(NctiRenderObject* i_pRenderItem);
        void AddItem(NctiRenderObject* i_pRenderItem);
        NctiRenderKit* GetKit(int i)const;

    private:
        void SubGeomtryItemVecVis(std::vector<NctiPickSelectObjectStr>& o_SubGeometryItemVec, NctiRenderSegmentItem* ins = nullptr, Ncti_Integer fmod = -1, Ncti_Integer lmod = -1, Ncti_Integer vmod = -1)const;
        NctiRenderSegmentItemPrivateData* _d;
    };
}

