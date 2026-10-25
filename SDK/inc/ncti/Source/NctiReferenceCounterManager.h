#ifndef NctiReferenceCounterManager_H
#define NctiReferenceCounterManager_H
#include "NctiManager.h"
#include "NctiMutex.h"
namespace NCTI
{
	struct NctiLocalObjRefCount
	{
		void* pObject;
		Ncti_Integer iRefCount;
	};
	/**
	* @brief internal used
	*/
	class NctiObjectCountTable : public NCTI_BASE_CLASS
	{
	public:
		NctiObjectCountTable();
		virtual ~NctiObjectCountTable();
		Ncti_Boolean Init(Ncti_Integer i_iSize);
		Ncti_Integer AddData(void* i_pObject, Ncti_Integer i_iRefCount = 0);
		void IncreaseReferenceCounter(void* i_pObject);
		void* DecreaseReferenceCounter(void* i_pObject);
		Ncti_Integer FindObject(void* i_pObject);
		Ncti_Integer GetNumIndex() { return m_iIndex; };
	protected:
		Ncti_Integer expand();
		Ncti_Boolean remove_data(Ncti_Integer  i_iIndex);
	private:
		Ncti_Integer m_iSize;				// Size of m_sArray
		Ncti_Integer	m_iIndex;				// Index for m_sArray
		NctiLocalObjRefCount* m_sArray;	
        NctiMutex m_mutex;
	};
	class NctiBaseView;
	class NctiBaseModel;
	/**
	* @brief internal used
	*/
	class DECL_NCTI NctiReferenceCounterManager : public NctiManager
	{
		NCTI_MANAGER_FUNCTIONS(NctiReferenceCounterManager)
	public:
		virtual ~NctiReferenceCounterManager();
		void AddRef(void*  i_pObject);
		void* Release(void*  i_pObject);
	private:
		NctiObjectCountTable* m_pRefCntTbl;
	public:
		static NctiReferenceCounterManager* GetReferenceCounterManager(NctiBaseView* i_pBaseView);
		static NctiReferenceCounterManager* GetReferenceCounterManager(NctiBaseModel* i_pBaseModel);
		static NctiReferenceCounterManager* GetReferenceCounterManager(NctiManager* i_pManager);
	};
}
DECL_NCTI NCTI_MANAGER_TYPEDEF(NctiReferenceCounterManager)
#endif 
