#ifndef NctiSelectionDataNewList_H
#define NctiSelectionDataNewList_H
#include "NctiSelectionDataList.h"
namespace NCTI
{
	/**
	* @brief create the clone selection data of list
	* @details manager selection data
	* @see NctiSelectionDataList
	*/
	class DECL_NCTI NctiSelectionDataNewList : public NctiSelectionDataList
	{
		NctiSelectionDataNewList(const NctiSelectionDataNewList&) {};
	public:
		NctiSelectionDataNewList(Ncti_Integer  i_iInitSize = 0) : NctiSelectionDataList(i_iInitSize) {};
		NctiSelectionDataNewList(NctiSelectionDataList* const  i_pSelDataList);
		virtual ~NctiSelectionDataNewList();
		/**
	   * @brief clone the selection data list
	   * @param[in] i_pSelDataList, the selection data list
	   * @return Ncti_Boolean
	   */
		Ncti_Boolean Duplicate(NctiSelectionDataList* const  i_pSelDataList);
	};
}
#endif
