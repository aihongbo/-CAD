#ifndef NctiCommandStateFactory_H
#define NctiCommandStateFactory_H
#include "ncti.h"

namespace NCTI
{
	class NctiDisplayObject;
	class NctiCommandState;
	class NctiHistoryManager;
	/**
	* @brief internal used
	*/
	class DECL_NCTI NctiCommandStateFactory : public NCTI_BASE_CLASS
	{
	public:
		NctiCommandStateFactory();
		virtual ~NctiCommandStateFactory();
	public:
		EnumNctiResult StartState(NctiDisplayObject* i_pDoCallback, EnumNctiDoCallbackType i_eDoCallbackType);
		NctiCommandState* NoteState(NctiHistoryManager* i_pHisMan);
		NctiCommandState* GetCurrentState() { return m_pCurrentState; };
		Ncti_Integer	GetDepthLevel() { return m_iDepthLevel; };
		void SetCancel(Ncti_Boolean i_bCancel) { m_bCancel = i_bCancel; };
		void MergeStates(NctiCommandState* i_pComStatSource);
		void RollBack();
		void RollForward();
		NctiCommandState* GetRecentOpenState();
		NctiCommandState* GetFirstState() { return m_aOpenState[0]; };
	private:
		NctiCommandState* m_pCurrentState;
		Ncti_Integer m_iDepthLevel;
		NctiCommandState* m_aOpenState[NCTI_LOCAL_NUM_MAX_INTERRUPT];
		Ncti_Boolean m_bCancel;
	};
}
#endif
