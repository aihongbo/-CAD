#pragma once

#include "NctiRenderObject.h"
#include "NctiTransf.h"

namespace NCTI
{
    class NctiViewerRenderer;
    /**
     * @brief base class for geometry display
     * @details the truly object contains the display data
     * the renders will generate display resource from it
     */
    class DECL_NCTI_RENDER NctiRenderGeometryItem : public NctiRenderObject
    {
        NCTI_RENDER_FUNCTIONS(NctiRenderGeometryItem);
    public:
        NctiRenderGeometryItem();
        virtual ~NctiRenderGeometryItem();

        using VertexDataType = std::vector<Ncti_Float>;
        using ElemDataType = std::vector<Ncti_UInteger>;

        enum GeomAttrType
        {
            e_vertex_pos = 0,
            e_elem_index,
            e_vertex_norm,
            e_cell_color,
            e_cell_vis,
            e_custom_type
        };

        /**
         * @brief get the minmax apply trans for this geometry
         * @param[in] i_trans transform
         * @param[out] o_min min position
         * @param[out] o_max max position
         */
        void GetMinMax(NctiPosition& o_max, NctiPosition& o_min,const NctiTransf&i_trans);

        /**
         * @brief get the right top position for this geometry
         * @param[out] o_max max position
         */
        void GetMax(NctiPosition& o_max);

        /**
         * @brief get the left bot position for this geometry
         * @param[out] o_min min position
         */
        void GetMin(NctiPosition& o_min);

        /**
         * @brief get the bounding box fro this geometry
         * @details if this geometry is not display,will get nothing
         * @param[in] i_pViewerRenderer the render contains visible info
         * @param[out] o_Max max position
         * @param[out] o_Min min position
         */
        virtual bool GetBox(NctiViewerRenderer* i_pViewerRenderer, NctiPosition& o_Max, NctiPosition& o_Min);

        /**
         * @brief clone self
         * @return the clone object
         */
        virtual NctiRenderGeometryItem* clone()const;

        /**
         * @brief the geometry element count
         * @return the count
         */
        virtual Ncti_Size GetVertexCount()const;

        /**
         * @brief the geometry element position
         * @param[in] index
         * @return the position
         */
        virtual NctiPosition GetPosition(int index)const;

        /**
         * @brief the geometry element position buffer
         * @param[out] o_buffer
         */
        virtual const VertexDataType& GetPositions()const = 0;

        /**
         * @brief box ray hit to this geometry
         * @param[in] m_ptLT box left top
         * @param[in] m_ptLB box left bottom
         * @param[in] m_ptRT box right top
         * @param[in] m_ptRB box right bottom
         * @param[in] m_Orig the ray origin
         * @param[in] trans,if exist ,means multiple this geometry
         * @return true for intersect with this geometry
         */
        virtual bool BoxRayHit(const NctiPosition& m_ptLT, const NctiPosition& m_ptLB, const NctiPosition& m_ptRT, const NctiPosition& m_ptRB, const NctiVector& m_Orig, NctiTransf* trans) const;

        /**
         * @brief Point ray hit to this geometry
         * @param[in] i_pt position
         * @param[in] i_area area
         * @param[out] o_pos interest position
         * @param[out] o_t
         * @param[in] trans,if exist ,means multiple this geometry
         * @return true for intersect with this geometry
         */
        virtual bool PointRayHit(const NctiPosition& i_pt, Ncti_Double i_area, const NctiVector& i_vec, NctiPosition& o_pos, Ncti_Double& o_t, NctiTransf* trans) const;

    protected:
        NctiPosition m_Max;
        NctiPosition m_Min;
    };
}

