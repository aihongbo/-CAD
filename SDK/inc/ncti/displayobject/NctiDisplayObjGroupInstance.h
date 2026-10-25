#ifndef NctiDisplayObjGroupInstance_H
#define NctiDisplayObjGroupInstance_H
#include "NctiDisplayObjInstance.h"
namespace NCTI
{
	class NctiDisplayGroup;
	class NctiDisplayObjectList;
	/**
	* @brief Group Instance class
	* @detael Group Instance of NctiDisplayGroup
	* @see NctiDisplayObjInstance,NctiDisplayGroup
	*/
	class DECL_NCTI NctiDisplayObjGroupInstance : public NctiDisplayObjInstance
	{
		NCTI_DISPLAYOBJECT_FUNCTIONS(NctiDisplayObjGroupInstance)
	public:
		virtual ~NctiDisplayObjGroupInstance();
		void Init(NctiBaseView* i_pBaseView, NctiDisplayGroup* i_pDoOriginal, NctiDisplayObject* i_pDisplayObject);
		virtual EnumNctiDoCallbackStatus Callback(NctiBaseView* i_pBaseView, EnumNctiDoCallbackType i_eType, NctiDisplayObject* i_pDoCaller);
	public:
		Ncti_Integer	AddMember(NctiDisplayObject* i_pDoMember);
		void GetTreeTextDispObj(Ncti_Integer i_iIndent, NctiStringArray* o_pStrArray, NctiDisplayObjectList* o_pDoList);
		EnumNctiResult UnhookMember(NctiDisplayObject* i_pDoMember);
		EnumNctiResult RemoveMember(NctiDisplayObject* i_pDoMember);
		NctiDisplayObjectList* GetDoObjInstanceList();
	protected:
		NctiDisplayObjectList* m_pDoObjInstanceList;
		Ncti_Boolean m_bBrowseDescendant;
	};
}
#endif

