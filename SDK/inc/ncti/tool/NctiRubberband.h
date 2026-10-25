#ifndef NctiRubberband_H
#define NctiRubberband_H
#include "ncti_dcl.h"
#include "ncti_base.h"
namespace NCTI
{
	class NctiBaseView;
	class NctiRenderSegmentItem;
	/**
	* @brief internal used
	*/
	class DECL_NCTI NctiRubberband : public NCTI_BASE_CLASS
	{
	public:
		NctiRubberband();
		virtual ~NctiRubberband();
	public:
		virtual void Hide(NctiBaseView* i_pBaseView);
	protected:
		NctiRenderSegmentItem* m_keyRubberband;
	};
}
#endif
