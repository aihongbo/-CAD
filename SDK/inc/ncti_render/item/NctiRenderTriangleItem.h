#ifndef NctiRenderTriangleItem_H
#define NctiRenderTriangleItem_H
#include "NctiRenderGeometryItem.h"
#include "ncti_include.h"

namespace NCTI
{
    /**
     * @brief Face Geometry Render Object
     */
	class DECL_NCTI_RENDER NctiRenderTriangleItem : public NctiRenderGeometryItem
	{
        NCTI_RENDER_FUNCTIONS(NctiRenderTriangleItem);
	public:
		NctiRenderTriangleItem();

        /**
         * @brief reset the position
         */
        void SetMeshData(const NctiMeshData& i_positions);

        /**
         * @brief completion virtual function
         * @return point count
         */
        Ncti_Size GetVertexCount()const override;

        /**
         * @brief get point position
         */
        NctiPosition GetPosition(int)const override;

        /**
         * @brief GetPositions
         */
        const VertexDataType& GetPositions()const override;

        /**
         * @brief Get bounding box.completion virtual function
         */
        bool GetBox(NctiViewerRenderer* i_pViewerRenderer, NctiPosition& o_Max, NctiPosition& o_Min)override;

        /**
         * @brief clone self.completion virtual function
         */
        NctiRenderGeometryItem* clone()const override;

        /**
         * @brief reset the position
         */
		void SetPositions(const VertexDataType& i_positions);

        /**
         * @brief reset the normal
         */
		void SetNormals(const VertexDataType& i_normals);

        /**
         * @brief reset the triangle
         */
        void SetTriangles(const ElemDataType& i_triangles);

        /**
         * @brief reset the uvs
         */
		void SetUvs(const std::vector<Ncti_Float>& i_uvs);

        /**
         * @brief direct update the render vertex data without rebuild the scene
         * @param[in] FloatVec vertex data
         */
		void SetVertexBuffer(const VertexDataType FloatVec);

        /**
         * @brief GetTriangleCount
         */
		Ncti_UInteger GetTriangleCount()const;

        /**
         * @brief get triangle data
         * @param[out] o_triangle
         * @param[in] i_vertBias
         */
        void GetTriangleData(std::vector<Ncti_UInteger>&o_triangle, Ncti_UInteger i_vertBias = 0)const;

        /**
         * @brief CalculateArea
         */
        Ncti_Float CalculateArea()const;

        /**
         * @brief get normal data
         */
        const std::vector<Ncti_Float>& GetNormals()const;

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
#endif
