#ifndef NctiSelectionDataHash_H
#define NctiSelectionDataHash_H
#include "ncti.h"
namespace NCTI
{
	class NctiSelHashNode;
	class NctiSelectionDataList;
	class NctiSelectionData;
	class NctiSelectionDataHash : public NCTI_BASE_CLASS
	{
	public:
		NctiSelectionDataHash();
		virtual ~NctiSelectionDataHash();
	public:
		NctiSelectionData* AddData(NctiSelectionData* i_pSelData);
		Ncti_Boolean ReleaseData(NctiSelectionData* i_pSelData, Ncti_Integer& o_iRefCount);
		Ncti_Integer GetSelectionData(NctiSelectionDataList& o_cSelectionDataList);
		Ncti_Boolean FindData(NctiSelectionData* i_pSelData, NctiSelectionData*& i_pSelDataFound);
		void Clear();
		Ncti_Integer GetSelectionDataForUpdating(Ncti_Integer i_iIndex, NctiSelectionDataList& o_cSelectionDataList);
		Ncti_Integer GetReferenceCounter(NctiSelectionData* i_pSelData);
		void GetSelectionDataByType(NctiSelectionDataList& o_cSelDataList,const char* o_pszDataType);
	protected:
		Ncti_Integer	m_iRefCounter;
		NctiSelHashNode** m_apSelHashNode;
	protected:
		Ncti_Integer increase_ref_counter() { return ++m_iRefCounter; };
		Ncti_Integer decrease_ref_counter() { return --m_iRefCounter; }; 
		Ncti_Integer get_ref_counter() { return m_iRefCounter; };
	};
}
#endif // !NctiSelectionDataHash_H

