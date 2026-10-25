#ifndef NctiSelectionDataList_H
#define NctiSelectionDataList_H
#include "ncti.h"
#include "NctiPosition.h"
namespace NCTI
{
    class NctiViewerRenderer;
	class NctiSelectionData;
	/**
	* @brief  the selection data of list
	* @details manager selection data
	* @see NctiDummyBaseClass
	*/
	class DECL_NCTI NctiSelectionDataList : public NCTI_BASE_CLASS
	{
		friend class NctiSelectionDataNewList;
		NctiSelectionDataList(const NctiSelectionDataList&) {};
	public:
		NctiSelectionDataList();
		NctiSelectionDataList(Ncti_Integer i_iInitSize);
		NctiSelectionDataList(const NctiSelectionDataList* i_pSelDataList);
		virtual ~NctiSelectionDataList();
		/**
	   * @brief reset the data
	   */
		void Init();
		/**
	   * @brief get box size, geometry box or segment box
	   * @param[out] o_ptMin, position
	   * @param[out] o_ptMax, position
	   */
        void GetBoundingBox(NctiPosition& o_ptMin, NctiPosition& o_ptMax);
		/**
	   * @brief add the new selection data
	   * return the length of list
	   */
		Ncti_Integer AddData(NctiSelectionData*  i_pSelData);
		/**
	   * @brief get the selection data by index
	   * @param[out] o_pBaseSelData, the selection data
	   * @param[in] i_iIndex, the selection data of index
	   * return Ncti_Boolean
	   */
		Ncti_Boolean GetSelDataByIndex(NctiSelectionData*& o_pBaseSelData, Ncti_Integer i_iIndex);
		/**
	   * @brief get the next selection data
	   * return NctiSelectionData
	   */
		NctiSelectionData* Next();
		/**
	   * @brief find the index by the selection data
	   * @param[in] i_pSelData, the selection data
	   * @param[out] o_Index, the selection data of index
	   * return Ncti_Boolean
	   */
		Ncti_Boolean FindSelData(NctiSelectionData* i_pSelData, Ncti_Integer& o_Index) const;
		/**
	   * @brief get the count of list
	   * return Ncti_Integer
	   */
		Ncti_Integer GetCount() { return m_iCount; };
		/**
	   * @brief get the valid count of list
	   * return Ncti_Integer
	   */
		Ncti_Integer GetIterationCount();
		/**
	   * @brief remove the selection data by index in a list
	   * return Ncti_Boolean
	   */
		Ncti_Boolean RemoveSelDataByIndex(Ncti_Integer i_iIndex);
		/**
	   * @brief remove the selection data in a list
	   * return Ncti_Boolean
	   */
		Ncti_Boolean RemoveSelData(NctiSelectionData* i_pBaseSelData);
		/**
	   * @brief clear the list
	   */
		void Clear();
		NctiSelectionData* operator[](Ncti_Integer  i_index) const;
	public:
		/**
	   * @brief internal used
	   */
		void sort();
	protected:
		/**
	   * @brief internal used
	   */
		Ncti_Integer expand();
	protected:
		Ncti_Integer m_iSize;		
		Ncti_Integer	m_iIndex;
		Ncti_Integer m_iCount;
		NctiSelectionData**	m_paSelData;
	};
}
#endif