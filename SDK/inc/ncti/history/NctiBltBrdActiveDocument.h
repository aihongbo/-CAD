#ifndef NctiBltBrdActiveDocument_H
#define NctiBltBrdActiveDocument_H
#include "NctiDisplayObject.h"
#include "NctiBulletinBoard.h"
namespace NCTI
{
	class NctiDocViewManager;
	class NctiDisplayDocElement;
	/**
	* @brief internal used
	*/
	class NctiBltBrdActiveDocument : public NctiBulletinBoard
	{
		NCTI_BULLETINBOARD_FUNCTIONS(NctiBltBrdActiveDocument)
	public:
		NctiBltBrdActiveDocument(NctiDocViewManager* i_pDocViewMan, NctiDisplayDocElement* i_pDocPrevActive, NctiDisplayDocElement* i_pDocCurrentActive, NctiDisplayDocElement* i_pDocNextActive);
		virtual ~NctiBltBrdActiveDocument();
		NctiDisplayDocElement* GetDocPrevActive() { return m_pDocPrevActive; };
		NctiDisplayDocElement* GetDocCurrentActive() { return m_pDocCurrentActive; };
		NctiDisplayDocElement* GetDocNextActive() { return m_pDocNextActive; };
		virtual Ncti_Boolean CallbackAfterRoll(Ncti_Boolean i_bRollback);
	protected:
		NctiDocViewManager* m_pDocViewMan;
		NctiDisplayDocElement* m_pDocPrevActive;
		NctiDisplayDocElement* m_pDocCurrentActive;
		NctiDisplayDocElement* m_pDocNextActive;
	};
}
#endif
