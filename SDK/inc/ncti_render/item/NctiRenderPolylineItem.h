#ifndef NctiRenderPolylineItem_H
#define NctiRenderPolylineItem_H
#include "NctiRenderGeometryItem.h"
namespace NCTI
{
    /**
     * @brief PolyLine Geometry Render Object
     */
	class DECL_NCTI_RENDER NctiRenderPolylineItem : public NctiRenderGeometryItem
	{
        NCTI_RENDER_FUNCTIONS(NctiRenderPolylineItem);
	public:
        /**
         * @brief construct
         */
        NctiRenderPolylineItem();

        /**
         * @brief reset the poly data
         * @param[in] i_PositionVec poly line point
         */
        void SetPositionVec(const std::vector<Ncti_Double>& i_PositionVec);

        /**
         * @brief reset the poly data
         * @param[in] i_PositionVec poly line point
         */
        void SetPositionVec(const VertexDataType& i_PositionVec);

        /**
         * @brief completion virtual function
         * @return poly line point count
         */
        Ncti_Size GetVertexCount()const override;
        /**
         * @brief completion virtual function
         * @param[in] index the point index in poly line
         * @return poly line point position
         */
        NctiPosition GetPosition(int index)const override;

        /**
         * @brief GetPositions
         */
        const VertexDataType& GetPositions()const override;
        
        /**
         * @brief CalculateLength
         */
        Ncti_Float CalculateLength()const;

        /**
         * @brief Get bounding box.completion virtual function
         * @details when line is inviable get nothing
         */
        bool GetBox(NctiViewerRenderer* i_pViewerRenderer, NctiPosition& o_Max, NctiPosition& o_Min)override;
		
        /**
         * @brief clone self.completion virtual function
         */
        NctiRenderGeometryItem* clone()const override;

        /**
         * @brief direct set the render vertex buffer without rebuild
         * @param[in] i_FloatVec buffer data
         */
		void SetVertexBuffer(const VertexDataType&);

        /**
         * @brief Point ray hit to this geometry
         * @param[in] i_pt position
         * @param[in] i_area area
         * @param[out] o_pos interest position
         * @param[out] o_t
         * @param[in] trans,if exist ,means multiple this geometry
         * @return true for intersect with this geometry
         */
        bool PointRayHit(const NctiPosition& i_pt, Ncti_Double i_area, const NctiVector& i_vec, NctiPosition& o_pos, Ncti_Double& o_t, NctiTransf* trans) const override;
	};
}
#endif // !NctiRenderPolylineItem_H
