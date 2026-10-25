#ifndef NctiRenderMarkerItem_H
#define NctiRenderMarkerItem_H
#include "NctiRenderGeometryItem.h"

namespace NCTI
{
    class NctiViewerRenderer;
    /**
     * @brief Point Geometry Render Object
     */
	class DECL_NCTI_RENDER NctiRenderMarkerItem : public NctiRenderGeometryItem
	{
        NCTI_RENDER_FUNCTIONS(NctiRenderMarkerItem);
	public:
        /**
       * @brief construct
       */
        NctiRenderMarkerItem();

        /**
         * @brief get marker position
         */
		NctiPosition GetPosition(int)const override;

        /**
         * @brief GetPositions
         */
        const VertexDataType& GetPositions()const override;

        /**
         * @brief set marker position
         */
        void SetVertexBuffer(const NctiPosition& i_pt);

        /**
         * @brief completion virtual function
         * @return 1. means 1 point
         */
        Ncti_Size GetVertexCount()const override;

        /**
         * @brief Get bounding box.completion virtual function
         */
		bool GetBox(NctiViewerRenderer* i_pViewerRenderer, NctiPosition& o_Max, NctiPosition& o_Min)override;

        /**
         * @brief clone self.completion virtual function
         */
		NctiRenderGeometryItem* clone()const override;

        /**
         * @brief SetPosition
         */
        void SetPosition(const NctiPosition& i_pt);
	};
}
#endif // !NctiRenderMarkerItem_H
