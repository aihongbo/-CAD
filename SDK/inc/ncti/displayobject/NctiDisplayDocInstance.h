#ifndef NctiDisplayDocInstance_H
#define NctiDisplayDocInstance_H
#include "NctiDisplayDocElement.h"
namespace NCTI
{
	class NctiBaseView;
	class NctiStringArray;
    class NctiRenderGeometryItem;
	/**
	* @brief Doc Instance class
	* @detael Doc Instance of NctiDisplayDocElement
	* @see NctiDisplayDocElement,NctiDisplayObject
	*/
	class DECL_NCTI NctiDisplayDocInstance : public NctiDisplayDocElement
	{
		NCTI_DISPLAYOBJECT_FUNCTIONS(NctiDisplayDocInstance)
			NCTI_DISPLAYOBJECT_INSTANCE
	public:
		virtual ~NctiDisplayDocInstance();
		/**
	   * @brief Initialization during obj class creation
	   */
		virtual void Init(NctiBaseView* i_pBaseView, NctiDisplayDocElement* i_pDisplayDocElement, NctiDisplayObject* i_pDisplayObject);
		virtual void Init(NctiBaseView* i_pBaseView, NctiDisplayDocElement* i_pDisplayDocElement);
		virtual EnumNctiDoCallbackStatus Callback(NctiBaseView* i_pBaseView, EnumNctiDoCallbackType i_eType, NctiDisplayObject* i_pDoCaller);
		void GetTreeTextDispObj(Ncti_Integer i_iIndent, NctiStringArray* i_pStrArray, NctiDisplayObjectList* i_pDoList);
	protected:
		Ncti_Boolean determine_browse_prop_do(NctiDisplayDocElement* i_pDocTarget);
		NctiBaseView* m_pOwnerBaseView;
		Ncti_Boolean m_bBrowseDescendant;
	};
}
#endif
