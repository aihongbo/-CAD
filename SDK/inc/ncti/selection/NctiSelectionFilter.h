#ifndef NctiSelectionFilter_H
#define NctiSelectionFilter_H
#include "ncti.h"
namespace NCTI
{
	class NctiSelectionDataList;
	class NctiSelectionDataNewList;
	/**
	* @brief the selection filter
	* @see NctiSelectionData
	*/
	class DECL_NCTI NctiSelectionFilter : public NCTI_BASE_CLASS
	{
	public:
		NctiSelectionFilter();
		virtual ~NctiSelectionFilter();
	public:
		virtual void apply_filter(NctiSelectionDataList& i_cInputSelectDataList,
			EnumNctiSelectionFilterMode	i_eSelectionFilterMode,
			NctiSelectionDataList& o_cOutputSelectDataList,
			NctiSelectionDataNewList& o_cNewSelectDataList) = 0;
	protected:
		EnumNctiSelectionFilterMode m_eSelectionFilterMode;
	};
}
#endif