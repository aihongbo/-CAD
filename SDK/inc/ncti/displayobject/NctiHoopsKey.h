#ifndef NctiHoopsKey_H
#define NctiHoopsKey_H
#include "ncti.h"
#include "NctiData.h"
#include "NctiRenderMemoryPool.h"

namespace NCTI
{
	class NctiRenderSegmentItem;
	/**
	* @brief internal used
	*/
	class DECL_NCTI NctiHoopsKey : public NctiMemoryBase
	{
	public:
		NctiHoopsKey();
        NctiHoopsKey(NCTI::NctiRenderSegmentItem* i_keyClient, NctiReferenceCounterManager* i_pRefMan);
		virtual ~NctiHoopsKey();
        NCTI::NctiRenderSegmentItem* GetHoopsKey();
	protected:
        NCTI::NctiRenderSegmentItem* m_keyClient;
		NctiReferenceCounterManager* m_pRefMan;
	};

	class NctiData_NctiHoopsKey : public NctiData
	{
	public:
		NctiData_NctiHoopsKey(NctiHoopsKey* pClientObject, NctiReferenceCounterManager* i_pRefMan);
		virtual ~NctiData_NctiHoopsKey();
		NctiHoopsKey* GetData();
		virtual void release_data();
	};
}
#endif // !NctiHoopsKey_H
