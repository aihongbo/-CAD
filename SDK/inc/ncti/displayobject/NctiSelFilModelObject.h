#ifndef NctiSelFilModelObject_H
#define NctiSelFilModelObject_H
#include "NctiSelectionFilter.h"
namespace NCTI
{
	class NctiSelectionDataList;
	/**
	* @brief internal used
	*/
	class DECL_NCTI NctiSelFilModelObject : public NctiSelectionFilter
	{
	public:
		NctiSelFilModelObject(Ncti_Integer i_iFilterType);
		virtual ~NctiSelFilModelObject();
	public:
		virtual void apply_filter(NctiSelectionDataList& i_cInputSelectDataList,
			EnumNctiSelectionFilterMode	i_eSelectionFilterMode,
			NctiSelectionDataList&		o_cOutputSelectDataList,
			NctiSelectionDataNewList&	o_cNewSelectDataList);

	private:
		Ncti_Integer m_iFilterType;

	};
}
#endif