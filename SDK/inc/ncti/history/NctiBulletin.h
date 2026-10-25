#ifndef NctiBulletin_H
#define NctiBulletin_H
#include "ncti.h"
#include "NctiMutex.h"
namespace NCTI
{
	class NctiDisplayObject;
	class NctiHistoryManager;
	/**
	* @brief internal used
	*/
	class DECL_NCTI NctiBulletin : public NCTI_BASE_CLASS
	{
	public:
		NctiBulletin(NctiDisplayObject* i_pOldDo, NctiDisplayObject* i_pNewDo, NctiHistoryManager* i_pHistoryManager);
		virtual ~NctiBulletin();
		NctiDisplayObject* GetNewDo() { return m_pNewDo; };
		NctiDisplayObject* GetOldDo() { return m_pOldDo; };
		void SetNext(NctiBulletin* i_pNext);
		NctiBulletin* GetNext() { return m_pNext; };
		void SetOldDo(NctiDisplayObject* i_pDoOld) { m_pOldDo = i_pDoOld; };
		void SetNewDo(NctiDisplayObject* i_pDoNew) { m_pNewDo = i_pDoNew; };
		void Roll();
	protected:
		NctiDisplayObject* m_pNewDo;
		NctiDisplayObject* m_pOldDo;
		NctiBulletin* m_pNext;
		NctiMutex m_mutex;
	};
}
#endif
