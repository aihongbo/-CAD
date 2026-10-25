#ifndef NctiDisplayGroup_H
#define NctiDisplayGroup_H
#include "NctiDisplayObject.h"
namespace NCTI
{
	class NctiDisplayObjectList;
	/**
	* @brief Group Object class
	* @details use to include object
	* @see NctiDisplayDocElement,NctiDisplayObject
	*/
	class DECL_NCTI NctiDisplayGroup : public NctiDisplayObject
	{
		NCTI_DISPLAYOBJECT_FUNCTIONS(NctiDisplayGroup)
	public:
		virtual ~NctiDisplayGroup();
	public:
		/**
	   * @brief Get all the child member in a Group
	   * @return NctiDisplayObjectList
	   */
		NctiDisplayObjectList* GetMemberDoList();
		/**
	   * @brief internal used
	   * @return Ncti_Boolean
	   */
		virtual NctiDisplayObject* CreateInstance(NctiBaseView* i_pBaseView, NctiDisplayObject* i_pDisplayObject);

		/**
	   * @brief Get all the member in a Group
	   * @return NctiDisplayObjectList
	   */
		void GetAllMembers(NctiDisplayObjectList* o_pDoListAllMembers);
		/**
	   * @brief Get all the child member in a Group
	   * @param[out] o_pDoListAllMembers, a new list
	   */
		void GetCurMembers(NctiDisplayObjectList* o_pDoListAllMembers);
		/**
	   * @brief internal used
	   * @return Ncti_Boolean
	   */
		EnumNctiResult UnhookMember(NctiDisplayObject* i_pDoMember);
		/**
	   * @brief add the child member in a Group
	   * @param[in] i_pDoMember
	   * @return the number of Members
	   */
		Ncti_Integer AddMember(NctiDisplayObject* i_pDoMember);
		virtual Ncti_Boolean MoveActualToWork();
	protected:
		NctiDisplayObjectList* m_pMemberDoList;
	private:
		NCTI_READ_AND_WRITE_VERSION_FUN(1)
	};
}
#endif // !NctiDisplayGroup_H
