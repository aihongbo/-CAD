#ifndef NctiRenderPubFun_H
#define NctiRenderPubFun_H
#include "ncti_render.h"
namespace NCTI
{
	class NctiRenderVisSelKit;
	class NctiRenderGeometryItem;
	class NctiRenderDrawingKit;

	class DECL_NCTI_RENDER NctiRenderPubFun
	{
	public:
		NctiRenderPubFun();
		virtual ~NctiRenderPubFun();

        /**
         * @brief get the near VisibilityKit
         * @param[in] i_pGeometryItem
         * @param[in] i_type the art to be get
         */
		static NctiRenderVisSelKit* GetNearVisibilityKit(NctiRenderGeometryItem* i_pGeometryItem, int i_type);
		
        /**
         * @brief get the near DrawingAttributeKit(
         * @param[in] i_pGeometryItem
         * @param[in] i_type the art to be get
         */
        static NctiRenderDrawingKit* GetNearDrawingAttributeKit(NctiRenderGeometryItem* i_pGeometryItem, int i_type);

	};
}
#endif // !NctiRenderPubFun_H
