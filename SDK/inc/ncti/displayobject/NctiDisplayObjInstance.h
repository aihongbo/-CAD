#ifndef NctiDisplayObjInstance_H
#define NctiDisplayObjInstance_H
#include "NctiDisplayObject.h"
namespace NCTI
{
	class NctiBaseView;
	class NctiDisplayDocInstance;
	class NctiStringArray;
	class NctiDisplayObjectList;
	/**
	* @brief Object Instance class
	* @details Object Instance of NctiDisplayObject
	* @see NctiDisplayObject
	*/
	class DECL_NCTI NctiDisplayObjInstance : public NctiDisplayObject
	{
		NCTI_DISPLAYOBJECT_FUNCTIONS(NctiDisplayObjInstance)
			NCTI_DISPLAYOBJECT_INSTANCE
	public:
		void Init(NctiBaseView* i_pBaseView, NctiDisplayObject* i_pDoOriginal, NctiDisplayObject* i_pDisplayObject);
		virtual ~NctiDisplayObjInstance();
		virtual EnumNctiDoCallbackStatus Callback(NctiBaseView* i_pBaseView, EnumNctiDoCallbackType i_eType, NctiDisplayObject* i_pDoCaller);

		void GetTreeTextDispObj(Ncti_Integer i_iIndent, NctiStringArray* o_pStrArray, NctiDisplayObjectList* o_pDoList);
	protected:
		NctiBaseView* m_pOwnerBaseView;
	};
}
#endif
