#ifndef NctiDisplayObjectList_H
#define NctiDisplayObjectList_H
#include "ncti.h"
namespace NCTI
{
	class NctiDisplayObject;
	/**
	* @brief a display object list
	* @details manager many display object
	* @see NctiDisplayObject
	*/
	class DECL_NCTI NctiDisplayObjectList : public NCTI_BASE_CLASS
	{
	private:
		NctiDisplayObjectList(const NctiDisplayObjectList&);
	public:
		NctiDisplayObjectList(Ncti_Integer i_init_size = 0);
		NctiDisplayObjectList(NctiDisplayObjectList* i_pListToBeCopied);
		virtual ~NctiDisplayObjectList();
		/**
	   * @brief reset the list to 0
	   */
		void Init();
		/**
	   * @brief add display object in a list
	   * @param[in] i_pAHDispObj, display object
	   * @param[in] i_eCheckOption
	   * @return Ncti_Integer, the number of list
	   */
		Ncti_Integer AddData(NctiDisplayObject* i_pAHDispObj, EnumNctiCheckExistence i_eCheckOption = NCTI_NO_EXISTENCE_CHECK);
		/**
	   * @brief remove display object in a list
	   * @param[in] i_pAHDispObj, display object
	   * @return Ncti_Boolean, true if it is successful
	   */
		Ncti_Boolean RemoveData(NctiDisplayObject* i_pAHDispObj); 
		/**
	   * @brief remove display object in a list by index
	   * @param[in] i_iIndex, display object index
	   * @return Ncti_Boolean, true if it is successful
	   */
		Ncti_Boolean RemoveDataByIndex(Ncti_Integer i_iIndex);
		/**
	   * @brief check if display object is in a list 
	   * @param[in] i_iIndex, display object index
	   * @return Ncti_Boolean, true if it is successful
	   */
		Ncti_Boolean FindDisplayObject(NctiDisplayObject*& i_pDO);
		/**
	   * @brief release all display object in a list
	   * @details it will use LCM_Release, delete the object by lifecycle manager
	   */
		void ReleaseAllDisplayObjects();
		/**
	   * @brief clear all display object in a list
	   */
		void ClearList();
		/**
	   * @brief get the count of list
	   * @return Ncti_Integer
	   */
		Ncti_Integer GetCount() { return m_nCount; };
		/**
	   * @brief get the valid count of list
	   * @return Ncti_Integer
	   */
		Ncti_Integer GetIterationCount();
		/**
	   * @brief get the current index in a list
	   * @return Ncti_Integer
	   */
		Ncti_Integer GetIndex() { return m_index; };
		/**
	   * @brief get the index by object
	   * @param[in] i_pDO, NctiDisplayObject
	   * @param[out] o_index, display object index
	   * @return Ncti_Boolean
	   */
		Ncti_Boolean GetDisplayObjectIndex(const NctiDisplayObject* i_pDO, Ncti_Integer& o_index);
		/**
	   * @brief reset the index by object
	   * @param[in] i_pDoToFind, NctiDisplayObject
	   * @return Ncti_Boolean
	   */
		Ncti_Boolean InitIndexByDisplayObject(NctiDisplayObject* i_pDoToFind);
		/**
	   * @brief get the next object
	   * @return NctiDisplayObject
	   */
		NctiDisplayObject* Next();
		/**
	   * @brief internal used
	   */
		NctiDisplayObject* operator[](Ncti_Integer i_index) const;
		/**
	   * @brief internal used
	   */
		NctiDisplayObjectList* MakeCopy(NctiDisplayObjectList* i_pDoListCopyFrom);
		/**
	   * @brief internal used
	   */
		void UniqueData();
		/**
	   * @brief internal used
	   */
		Ncti_Integer InsertData(NctiDisplayObject* i_pDo);
	protected:
		/**
	   * @brief internal used
	   */
		Ncti_Integer expand();
		/**
	   * @brief internal used
	   */
		void sort_data();
	protected:
		NctiDisplayObject** m_paDispObjArray;
		Ncti_Integer m_nCount;
		Ncti_Integer m_size;
		Ncti_Integer m_index;

		Ncti_Boolean m_bOrdered;
	};
}
#endif 
