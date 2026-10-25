#ifndef NctiDisplayObjectLifeCycleManager_H
#define NctiDisplayObjectLifeCycleManager_H
#include "NctiManager.h"
#include "NctiMutex.h" 

#define LCM_GenerateDisplayObject(type_string, obj) NctiDisplayObjectLifeCycleManager::GetDisplayObjectLifeCycleManager(obj)->GenerateDisplayObject(type_string);
#define LCM_Release(do_pointer) do_pointer->GetLCM()->Release(do_pointer);
#define LCM_AddRef(do_pointer, obj) \
	if ( do_pointer->GetLCM() ) \
	   do_pointer->GetLCM()->AddRef(do_pointer); \
	else \
		NctiDisplayObjectLifeCycleManager::GetDisplayObjectLifeCycleManager(obj)->AddRef(do_pointer);
namespace NCTI
{
	class NctiDisplayObject;
	class NctiBaseView;
	class NctiDisplayObjectLifeCycleManager;
	/**
	* @brief internal used
	*/
	class DECL_NCTI NctiObjectGenerator : public NCTI_BASE_CLASS
	{
	public:
		NctiObjectGenerator(const char* i_cpTypeName, NctiDisplayObject*(*)(NctiDisplayObjectLifeCycleManager* i_pLCM));
		//NctiObjectGenerator(const char* i_cpTypeName, NctiDisplayObject* (*)(...));
		void SetNext(NctiObjectGenerator* i_pNext);;
		NctiObjectGenerator* GetNext();;
		NctiDisplayObject* GenerateDisplayObject(NctiDisplayObjectLifeCycleManager* i_pLCM);
		const char* GetTypeName();;
	private:
		const char* m_cpDoTypeName;
		NctiDisplayObject* (*m_pProcPointer)(NctiDisplayObjectLifeCycleManager*);
		NctiObjectGenerator* m_pNextGenerator;
	};
	struct ah_DoRefCount
	{
		NctiDisplayObject* pDo;
		Ncti_Integer iRefCount;
	};
	/**
	* @brief internal used
	*/
	class DECL_NCTI NctiRefCountTable : public NCTI_BASE_CLASS
	{
	public:
		NctiRefCountTable();
		virtual ~NctiRefCountTable();
		Ncti_Boolean Init(Ncti_Integer i_iSize);
		Ncti_Integer AddData(NctiDisplayObject* i_pDoTarget, Ncti_Integer i_iRefCount = 0);
		NctiDisplayObject* DecreaseReferenceCounter(NctiDisplayObject* i_pDoTarget);
		void IncreaseReferenceCounter(NctiDisplayObject* i_pDoTarget);
		Ncti_Integer FindDo(NctiDisplayObject* i_pDoTarget) const;
		Ncti_Boolean remove_data(Ncti_Integer i_iIndex);
		Ncti_Integer GetDoRefCount(NctiDisplayObject* i_pDoTarget) const;
		void SetLCM(NctiDisplayObjectLifeCycleManager* i_pLCM) { m_pLCM = i_pLCM; }
	protected:
		Ncti_Integer expand();
	private:
		Ncti_Integer m_iSize;				// Size of m_sArray
		Ncti_Integer	m_iIndex;				// Index for m_sArray
		ah_DoRefCount* m_sArray;	// Array of record for NctiDisplayObject and Reference Count
        NctiMutex m_mutex;
		NctiDisplayObjectLifeCycleManager* m_pLCM;
	};
	/**
	* @brief internal used
	*/
	class DECL_NCTI NctiDoIter : public NCTI_BASE_CLASS
	{
	public:
		NctiDoIter();
		Ncti_Boolean Next();
		Ncti_Boolean IsName(const char* i_cpTypeName);
		const char* GetName();
	private:
		NctiObjectGenerator* m_pCurrent;
	};
	/**
	* @brief manage all display object
	* @see NctiManager
	*/
	class DECL_NCTI NctiDisplayObjectLifeCycleManager : public NctiManager 
	{
		NCTI_MANAGER_FUNCTIONS(NctiDisplayObjectLifeCycleManager)
	public:
		virtual ~NctiDisplayObjectLifeCycleManager();
		/**
	   * @brief internal used
	   */
		NctiDisplayObject* GenerateDisplayObject(const char* i_cpTypeName, Ncti_Boolean i_bIsHasUnknown = false, Ncti_Boolean i_MutilThread = false);
		/**
	   * @brief internal used
	   */
		NctiDisplayObject* Release(NctiDisplayObject* i_pDoTarget);
		/**
	   * @brief internal used
	   */
		void AddRef(NctiDisplayObject* i_pDoTarget);
		/**
	   * @brief internal used
	   */
		Ncti_Integer GetDoRefCount(NctiDisplayObject* i_pDoTarget) const;
		/**
	   * @brief internal used
	   */
		void AddData(NctiDisplayObject* i_pDoTarget);
	private:
		NctiRefCountTable* m_pRefCntTbl;
	public:
		/**
	   * @brief get lifecycle manager by NctiBaseView
	   * @param[in] i_pBaseView, the render view
	   * @return NctiDisplayObjectLifeCycleManager
	   */
		static NctiDisplayObjectLifeCycleManager* GetDisplayObjectLifeCycleManager(NctiBaseView* i_pBaseView);
		/**
	   * @brief get lifecycle manager by NctiBaseModel
	   * @param[in] i_pBaseModel, the document base model, only one in a document
	   * @return NctiDisplayObjectLifeCycleManager
	   */
		static NctiDisplayObjectLifeCycleManager* GetDisplayObjectLifeCycleManager(NctiBaseModel* i_pBaseModel);
		/**
	   * @brief get lifecycle manager by NctiManager
	   * @param[in] i_pManager, other manager
	   * @return NctiDisplayObjectLifeCycleManager
	   */
		static NctiDisplayObjectLifeCycleManager* GetDisplayObjectLifeCycleManager(NctiManager* i_pManager);
	};
}
DECL_NCTI NCTI_MANAGER_TYPEDEF(NctiDisplayObjectLifeCycleManager)
#endif
