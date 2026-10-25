#ifndef NctiRenderImageItem_H
#define NctiRenderImageItem_H
#include "NctiRenderMarkerItem.h"
namespace NCTI
{
    /**
     * @brief Render Item for image
     * @note Not yet implemented
     */
	class DECL_NCTI_RENDER NctiRenderImageItem : public NctiRenderMarkerItem
	{
        NCTI_RENDER_FUNCTIONS(NctiRenderImageItem);
	public:
        NctiRenderImageItem();
	};
}
#endif
