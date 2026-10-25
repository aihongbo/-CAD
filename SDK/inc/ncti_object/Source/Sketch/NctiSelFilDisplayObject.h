#ifndef NctiSelFilDisplayObject_H
#define NctiSelFilDisplayObject_H
#include "ncti.h"
#include "dcl_ncti_object.h"
#include "NctiSelectionFilter.h"
#include "NctiSelectionManager.h"
namespace NCTI
{
	class NctiSelectionDataList;
	class NctiSelectionDataNewList;
	class NctiStringArray;
	class DECL_NCTI_OBJECT NctiSelFilDisplayObject : public NctiSelectionFilter
	{
	public:
		NctiSelFilDisplayObject();
		virtual ~NctiSelFilDisplayObject();
		void AddDoType(const char* i_pszDoType);

	protected:
		virtual void apply_filter(NctiSelectionDataList& i_cInputSelectDataList,
			EnumNctiSelectionFilterMode	i_eSelectionFilterMode,
			NctiSelectionDataList& i_cOutputSelectDataList,
			NctiSelectionDataNewList& i_cNewSelectDataList);
		bool get_target_do(const char* i_pszTypeName, NctiDisplayObject* const i_pDoInstance, NctiDisplayObject*& o_pDoOriginalFound, NctiDisplayObject*& o_pDoInstanceFound);

	private:
		NctiStringArray* m_pDoTypeList;

	};
}


#endif