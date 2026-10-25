#ifndef NctiBltBrdCallback_H
#define NctiBltBrdCallback_H
#include "NctiBulletinBoard.h"
namespace NCTI
{
	class NctiDisplayObject;
	class NctiDisplayObjectList;
	/**
	* @brief internal used
	*/
	class NctiBltBrdCallback : public NctiBulletinBoard
	{
		NCTI_BULLETINBOARD_FUNCTIONS(NctiBltBrdCallback)
	public:
		NctiBltBrdCallback(NctiDisplayObject* i_pDoTarget, EnumNctiDoCallbackType i_eDoCallbackType, EnumNctiBeginEnd i_eBeginEnd);
		NctiBltBrdCallback(NctiDisplayObjectList* i_pcDoList, EnumNctiDoCallbackType i_eDoCallbackType, EnumNctiBeginEnd i_eBeginEnd);
		virtual ~NctiBltBrdCallback();
		virtual Ncti_Boolean CallbackAfterRoll(Ncti_Boolean i_bRollback);
	protected:
		EnumNctiBeginEnd m_eBeginEnd;
		NctiDisplayObject**	m_pDoTargets;
		Ncti_Integer m_iNumDo;
		EnumNctiDoCallbackType m_eDoCallbackType;
	};
}
#endif
