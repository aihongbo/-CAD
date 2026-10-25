#ifndef NctiDisplayDocApplication_H
#define NctiDisplayDocApplication_H
#include "NctiDisplayDocElement.h"
namespace NCTI
{
	class NctiDisplayDocInstance;
	/**
	* @brief Doc Application class
	* @details only one doc app in a Document
	* @see NctiDisplayDocElement,NctiDisplayObject
	*/
	class DECL_NCTI NctiDisplayDocApplication : public NctiDisplayDocElement
	{
		NCTI_DISPLAYOBJECT_FUNCTIONS(NctiDisplayDocApplication)
	public:
		virtual ~NctiDisplayDocApplication();
        virtual void Init(NCTI::NctiRenderSegmentItem* i_segkey);
	};
}
#endif
