#ifndef NctiBltBrdDocViewMan_H
#define NctiBltBrdDocViewMan_H
#include "NctiBulletinBoard.h"
namespace NCTI
{
	enum EnumNctiBltBrdDocViewMan
	{
		NCTI_BB_ADD_DISPLAY_OBJECT,
		NCTI_BB_ADD_DOCUMENT,
		NCTI_BB_ADD_GROUP_MEMBER,
		NCTI_BB_REMOVE_DISPLAY_OBJECT,
		NCTI_BB_REMOVE_DOCUMENT,
		NCTI_BB_REMOVE_GROUP_MEMBER,
		NCTI_BB_MOVE_DISPLAY_OBJECT,
		NCTI_BB_ADD_ATTRIBUTE,
		NCTI_BB_REMOVE_ATTRIBUTE
	};
	class NctiDisplayObject;
	class NctiDisplayObjectList;
	class NctiDocViewManager;
	/**
	* @brief internal used
	*/
	class NctiBltBrdDocViewMan : public NctiBulletinBoard
	{
		NCTI_BULLETINBOARD_FUNCTIONS(NctiBltBrdDocViewMan)
	public:
		NctiBltBrdDocViewMan(EnumNctiBltBrdDocViewMan i_eOperationType, 
			NctiDisplayObject* i_pOwner, 
			Ncti_Integer i_iNumChild, 
			NctiDisplayObject** i_paChild,
			NctiDocViewManager* i_pDocViewManager);
		virtual ~NctiBltBrdDocViewMan();
		void GetChildList(NctiDisplayObjectList &o_AHChildList);
		virtual Ncti_Boolean CallbackBeforeRoll(Ncti_Boolean i_bRollback);
		virtual Ncti_Boolean CallbackAfterRoll(Ncti_Boolean i_bRollback);
	protected:
		EnumNctiBltBrdDocViewMan m_eOperationType;
		NctiDisplayObject* m_pOwner;
		Ncti_Integer	m_iNumChild;
		NctiDisplayObject** m_paChild;
		Ncti_Boolean m_bAdd;
		NctiDocViewManager* m_DocViewManager;
	};
}
#endif
