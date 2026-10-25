#ifndef NNctiBltBrdDisplayEraseStatus_H
#define NNctiBltBrdDisplayEraseStatus_H
#include "NctiDisplayObject.h"
#include "NctiBulletinBoard.h"
namespace NCTI
{
	class NctiDocViewManager;
	class NctiDisplayDocElement;
	/**
	* @brief internal used
	*/
	class NctiBltBrdDisplayEraseStatus : public NctiBulletinBoard
	{
		NCTI_BULLETINBOARD_FUNCTIONS(NctiBltBrdDisplayEraseStatus)
	public:
		NctiBltBrdDisplayEraseStatus(NctiDocViewManager* i_pDocViewMan, NctiDisplayObject* i_pDo);
		virtual ~NctiBltBrdDisplayEraseStatus();
		virtual Ncti_Boolean CallbackAfterRoll(Ncti_Boolean i_bRollback);
	protected:
		NctiDocViewManager* m_pDocViewMan;
		NctiDisplayObject* m_pTargetDo;
	};
}
#endif
