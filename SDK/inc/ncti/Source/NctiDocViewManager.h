#ifndef NctiDocViewManager_H
#define NctiDocViewManager_H
#include "NctiManager.h"
#include <map>
#include "NctiTransf.h"
#include <vector>
#define NCTI_DOCUMENT_COUNTER_REGISTRATION( DOCUMENT_NAME) \
	NctiDocumentCounter* Generate_Counter_##DOCUMENT_NAME(NctiBaseModel* i_pBaseModel)\
	{\
	    NctiDocumentCounter* pDocumentCounter = NCTI_NEW NctiDocumentCounter( DOCUMENT_NAME::ID, i_pBaseModel );\
		return pDocumentCounter;\
	}\
	static NctiDocumentCounterGenerator Register_Counter_##DOCUMENT_NAME(\
								(NctiDocumentCounter* (*)(...))Generate_Counter_##DOCUMENT_NAME );
#define NCTI_DOC_FILE_REGISTRATION( DISPLAY_OBJECT_CLASS_NAME, EXTENSION_STRING, EXTENSION_DESCRIPTION )\
	const char* DISPLAY_OBJECT_CLASS_NAME::FILE_EXTENSION = EXTENSION_STRING;\
	const char* DISPLAY_OBJECT_CLASS_NAME::FILE_DESCRIPTION = EXTENSION_DESCRIPTION;\
	Ncti_Boolean DISPLAY_OBJECT_CLASS_NAME::GetFileExtension( const char*& pszExt ){ pszExt = DISPLAY_OBJECT_CLASS_NAME::FILE_EXTENSION; return true; }\
	Ncti_Boolean DISPLAY_OBJECT_CLASS_NAME::GetFileDescription( const char*& pszDesc){ pszDesc = DISPLAY_OBJECT_CLASS_NAME::FILE_DESCRIPTION; return true; }\
	static NctiFileExtension FileExt_##DISPLAY_OBJECT_CLASS_NAME( EXTENSION_STRING, EXTENSION_DESCRIPTION )
namespace NCTI
{
	class NctiDisplayObject;
	class NctiDisplayObjectVariable;
	class NctiFileVersionDocElement;
	class NctiDisplayDocElement;
	class NctiBaseModel;
	class NctiDisplayDocApplication;
	class NctiDisplayObjectList;
	class NctiFileInterface;
	class NctiBaseView;
	class NctiDisplayViewObject;
	class NctiBooleanArray;
	class NctiBltBrdDocViewMan;
	class NctiDisplayGroup;
	class NctiBulletinBoard;
	class NctiThreadPool;
	class NctiDisplayDocInstance;
	class NctiDisplayDocSystemObject;
	/**
	* @brief internal used
	*/
    class DECL_NCTI NctiDocumentCounter : public NCTI_BASE_CLASS
	{
	public:
		NctiDocumentCounter(const char* i_cpDocumentId, NctiBaseModel* i_pBaseModel);
		virtual ~NctiDocumentCounter();
		void SetCounter(Ncti_Integer& i_iValue);
		void GetCounter(Ncti_Integer& o_iValue);
		const char* GetDocumentId();
	private:
		char*	m_cpDocumentId;
		NctiDisplayObjectVariable* m_pDocumentUniqueCounter;
	};
	class DECL_NCTI NctiDocumentCounterGenerator : public NCTI_BASE_CLASS
	{
	public:
		NctiDocumentCounterGenerator(NctiDocumentCounter*(*)(...));
		void SetNext(NctiDocumentCounterGenerator* i_pNext) { m_pNextGenerator = i_pNext; };
		NctiDocumentCounterGenerator* GetNext() { return m_pNextGenerator; };
		NctiDocumentCounter* GenerateDocumentCounter(NctiBaseModel* i_pBaseModel);
		const char* GetTargetName() { return m_cpTargetName; };
	private:
		const char* m_cpTargetName;
		NctiDocumentCounter* (*m_pProcPointer)(...);
		NctiDocumentCounterGenerator* m_pNextGenerator;
	};
	/**
	* @brief internal used
	*/
	class DECL_NCTI NctiFileExtension : public NCTI_BASE_CLASS
	{
	public:
		NctiFileExtension(const char* i_cpFileExtension, const char* i_cpFileDescription);
		const char* GetFileExtension() { return m_cpFileExtension; };
		const char* GetFileDescription() { return m_cpFileDescription; };
		NctiFileExtension* GetNext() { return m_pNextFileExtension; };
	private:
		const char* m_cpFileExtension;
		const char* m_cpFileDescription;
		NctiFileExtension* m_pNextFileExtension;
	};
	/**
	* @brief manager doc data function, data relation
	* @details it can read, save, add object to document......
	* @see NctiManager,NctiDocument
	*/
	class DECL_NCTI NctiDocViewManager : public NctiManager
	{
		friend class NctiLocalUpdateRequester;
		NCTI_MANAGER_FUNCTIONS(NctiDocViewManager)
	public:
		virtual ~NctiDocViewManager();
		/**
	   * @brief Initialization during obj class creation
	   */
		void Init(NctiBaseModel* i_pBaseModel);
	public:
		/**
	   * @brief get doc view manager by NctiBaseView
	   * @param[in] i_pBaseView, the render view
	   * @return NctiDocViewManager
	   */
		static NctiDocViewManager* GetDocViewManager(NctiBaseView* i_pBaseView);
		/**
	   * @brief get  doc view manager by NctiBaseModel
	   * @param[in] i_pBaseModel, the document base model, only one in a document
	   * @return NctiDocViewManager
	   */
		static NctiDocViewManager* GetDocViewManager(NctiBaseModel* i_pBaseModel);
		/**
	   * @brief get  doc view manager by NctiManager
	   * @param[in] i_pManager, other manager
	   * @return NctiDocViewManager
	   */
		static NctiDocViewManager* GetDocViewManager(NctiManager* i_pManager);
		/**
	   * @brief Construct display object in a lifecycle manager
	   * @param[in] i_cpObjName, the display type name
	   * @param[in] i_bIsHasUnknown, the unknown object
	   * @param[in] i_MutilThread, use the multi threading
	   * @return NctiDisplayObject
	   */
		NctiDisplayObject* ConstructDisplayObject(const char* i_cpObjName, Ncti_Boolean i_bIsHasUnknown = false, Ncti_Boolean i_MutilThread = false);
		/**
	   * @brief add a new element to owner element
	   * @param[in] i_pDocOwner, the owner element
	   * @param[in] i_pDocNew, a new element
	   * @return EnumNctiResult
	   */
		EnumNctiResult AddDocument(NctiDisplayDocElement* i_pDocOwner, NctiDisplayDocElement* i_pDocNew);
		/**
	   * @brief remove a element from owner element
	   * @param[in] i_pDocOwner, the owner element
	   * @param[in] i_pDocTarget, the remove element
	   * @return EnumNctiResult
	   */
		EnumNctiResult RemoveDocument(NctiDisplayDocElement* i_pDoOwner, NctiDisplayDocElement* i_pDocTarget);
		/**
	   * @brief unhook a element from owner element, internal use
	   * @param[in] i_pDocOwner, the owner element
	   * @param[in] i_pDocTarget, the unhook element
	   * @return EnumNctiResult
	   */
		EnumNctiResult unhook_document(NctiDisplayDocElement* i_pDocOwner, NctiDisplayDocElement* i_pDocTarget);
		/**
	   * @brief save the file by file path
	   * @param[in] i_cpFileFullPath, the owner element
	   * @param[in] i_SaveAs, if it's true ,it will SaveAs
	   * @return EnumNctiResult
	   */
		EnumNctiResult SaveFile(const char* i_cpFileFullPath, Ncti_Boolean i_SaveAs = false);
		/**
	   * @brief read the file by file path
	   * @return EnumNctiResult
	   */
		EnumNctiResult ReadFile(const char* i_cpFileFullPath);
		/**
	   * @brief read the file image in a system object quickly
	   * @param[in] i_cpFileFullPath, the file path
	   * @param[in] i_imagePathPng, the save image path
	   * @return EnumNctiResult
	   */
		EnumNctiResult ReadFileImage(const char* i_cpFileFullPath, const Ncti_Char* i_imagePathPng);
		/**
	   * @brief internal used
	   */
		NctiDisplayDocElement* ImportFile(const char* i_cpFileFullPath);
		/**
	   * @brief set the root element,it maybe assembly or part
	   * @param[in] i_pDocElement, it maybe assembly or part
	   * @return EnumNctiResult
	   */
		EnumNctiResult SetRootDocElement(NctiDisplayDocElement* i_pDocElement);
		/**
	   * @brief set the active element,it maybe assembly or part
	   * @param[in] i_pDocActive, it maybe assembly or part
	   * @param[in] i_pBaseView, call back the base view data
	   */
		void SetActiveDocElement(NctiDisplayDocElement* i_pDocActive, NctiBaseView* i_pBaseView = nullptr);
		/**
	   * @brief set the active doc sketch element
	   * @param[in] i_pDocSketch, doc sketch element
	   */
		void SetActiveDocSketch(NctiDisplayObject* i_pDocSketch);
		/**
	   * @brief get root doc element, it maybe assembly or part doc element
	   * @return NctiDisplayDocElement
	   */
		NctiDisplayDocElement* GetRootDocElement() { return m_pRootDocElement; }
		/**
	   * @brief get all original count
	   * @return Ncti_Integer
	   */
		Ncti_Integer GetOriginalListCount();
		/**
	   * @brief add a new display object to element
	   * @param[in] i_pDoOwner, it is assembly or part
	   * @param[in] i_pDoChild, a new display object created by lifecycle
	   * @return EnumNctiResult
	   */
		EnumNctiResult AddDisplayObject(NctiDisplayDocElement* i_pDoOwner, NctiDisplayObject* i_pDoChild);
		/**
	   * @brief add a new display object list to element
	   * @param[in] i_pDoOwner, it is assembly or part
	   * @param[in] i_pChildList, a new display object list created by lifecycle
	   * @return EnumNctiResult
	   */
		EnumNctiResult AddDisplayObjects(NctiDisplayDocElement* i_pDoOwner, NctiDisplayObjectList* i_pChildList);
		/**
	   * @brief move a display object list to element
	   * @param[in] i_pDoOwner, it is assembly or part
	   * @param[in] i_pDoToBeMoved, an existing display object 
	   * @return EnumNctiResult
	   */
		EnumNctiResult MoveDisplayObject(NctiDisplayObject* i_pDoNewOwner, NctiDisplayObject* i_pDoToBeMoved);
		/**
	   * @brief update the view when add a new display object to element
	   * @param[in] i_pDoOwner, it is assembly or part
	   * @param[in] i_pChild, a new display object created by lifecycle
	   */
		void UpdateViewForAddDisplayObject(NctiDisplayDocElement* i_pDoOwner, NctiDisplayObject* i_pChild);
		/**
	   * @brief update the view when add a new element to element
	   * @param[in] i_pDoOwner, it is assembly or part
	   * @param[in] i_pDocNew, a new element created by lifecycle
	   */
		void UpdateViewForAddDocument(NctiDisplayDocElement* i_pDocOwner, NctiDisplayDocElement* i_pDocNew);
		/**
	   * @brief update the view when remove a display object from element
	   * @param[in] i_pDoOwner, it is assembly or part
	   * @param[in] i_pChild, an existing display object 
	   */
		void UpdateViewForUnhookDisplayObject(NctiDisplayDocElement* i_pDoOwner, NctiDisplayObject* i_pChild);
		/**
	   * @brief update the view when remove a element from element
	   * @param[in] i_pDoOwner, it is assembly or part
	   * @param[in] i_pDocTarget, an existing element
	   */
		void UpdateViewForUnhookDocument(NctiDisplayDocElement* i_pDocOwner, NctiDisplayDocElement* i_pDocTarget);
		/**
	   * @brief update the view when move a object from element
	   * @param[in] i_pDoNewOwner, it is assembly or part
	   * @param[in] i_pDoToBeMoved, an existing display object 
	   */
		void UpdateViewForMoveDisplayObject(NctiDisplayObject* i_pDoNewOwner, NctiDisplayObject* i_pDoToBeMoved);
		/**
	   * @brief update the view when add a new display object to group
	   * @param[in] i_pDoGroup, it is a group object
	   * @param[in] i_pDoMember, a new display object created by lifecycle
	   */
		void UpdateViewForAddGroupMember(NctiDisplayGroup* i_pDoGroup, NctiDisplayObject* i_pDoMember);
		/**
	   * @brief update the view when remove a display object from group
	   * @param[in] i_pDoGroup, it is a group object
	   * @param[in] i_pDoMember, an existing display object 
	   */
		void UpdateViewForUnhookGroupMember(NctiDisplayGroup* i_pDoGroup, NctiDisplayObject* i_pDoMember);
		/**
	   * @brief get active doc element
	   * @details it maybe assembly or part
	   * @return NctiDisplayDocElement
	   */
		NctiDisplayDocElement* GetActiveDocElement();
		/**
	   * @brief get active doc sketch
	   * @return NctiDisplayObject
	   */
		NctiDisplayObject* GetActiveDocSketch();
		/**
	   * @brief get system object, it is first child of a root element
	   * @return NctiDisplayDocSketch
	   */
		NctiDisplayDocSystemObject* GetDocSystemObject();
		/**
	   * @brief remove a existing display object from element
	   * @param[in] i_pDoOwner, it is assembly or part
	   * @param[in] i_pDoChild, a existing display object 
	   * @return EnumNctiResult
	   */
		EnumNctiResult RemoveDisplayObject(NctiDisplayDocElement* i_pDoOwner, NctiDisplayObject* i_pDoChild);
		/**
	   * @brief remove a existing display object list from element
	   * @param[in] i_pDoOwner, it is assembly or part
	   * @param[in] i_pDoChild, a existing display object list
	   * @return EnumNctiResult
	   */
		EnumNctiResult RemoveDisplayObjects(NctiDisplayDocElement* i_pDoOwner, NctiDisplayObjectList* i_pChildList);
		/**
	   * @brief unhook a existing display object from element, internal use
	   * @param[in] i_pDoOwner, it is assembly or part
	   * @param[in] i_pDoChild, a existing display object
	   * @return EnumNctiResult
	   */
		EnumNctiResult UnhookDisplayObject(NctiDisplayDocElement* i_pDoOwner, NctiDisplayObject* i_pDoChild);
		/**
	   * @brief add a new display object to group
	   * @param[in] i_pDoGroup, it is group object
	   * @param[in] i_pDoMember, a new display object created by lifecycle
	   * @return EnumNctiResult
	   */
		EnumNctiResult AddGroupMember(NctiDisplayGroup* i_pDoGroup, NctiDisplayObject* i_pDoMember);
		/**
	   * @brief remove a existing display object from group
	   * @param[in] i_pDoGroup, it is group object
	   * @param[in] i_pDoMember, a existing display object
	   * @return EnumNctiResult
	   */
		EnumNctiResult RemoveGroupMember(NctiDisplayGroup* i_pDoGroup, NctiDisplayObject* i_pDoMember);
		/**
	   * @brief unhook a existing display object from group, internal use
	   * @param[in] i_pDoGroup, it is group object
	   * @param[in] i_pDoMember, a existing display object
	   * @return EnumNctiResult
	   */
		EnumNctiResult UnhookGroupMember(NctiDisplayGroup* i_pDoGroup, NctiDisplayObject* i_pDoMember);
		/**
	   * @brief get the instance object to call back, NCTI_DO_CALLBACK_UPDATE_INSTANCE
	   * @param[in] i_pDoTarget, it is original object
	   */
		void RequestUpdateInstance(NctiDisplayObject* i_pDoTarget);
		/**
	   * @brief find nearest owner
	   * @param[in] i_pDo, it is original object
	   * @param[out] o_pDocElementFound, nearest owner
	   * @return Ncti_Boolean
	   */
		Ncti_Boolean FindDisplayDocElement(NctiDisplayObject* i_pDo, NctiDisplayDocElement*& o_pDocElementFound);
		/**
	   * @brief move a display object list to group
	   * @param[in] i_pDoGroup, it is group, the old group
	   * @param[in] i_pNextDoMember, it is group, the new group
	   * @param[in] i_pDoMember, an existing display object
	   * @return EnumNctiResult
	   */
		EnumNctiResult MoveGroupMember(NctiDisplayGroup* i_pDoGroup, NctiDisplayObject* i_pNextDoMember, NctiDisplayObject* i_pDoMember);
		/**
	   * @brief unhook a existing element to owner element
	   * @param[in] i_pDocOwner, the owner element
	   * @param[in] i_pDocTarget, a existing element
	   * @return EnumNctiResult
	   */
		EnumNctiResult	UnhookDocument(NctiDisplayDocElement* i_pDocOwner, NctiDisplayDocElement* i_pDocTarget);
		/**
	   * @brief use for python to refresh together
	   */
		void Start_NCTI_LOCAL_UPDATE_REQUESTER();
		/**
	   * @brief use for python to refresh together
	   */
		void End_NCTI_LOCAL_UPDATE_REQUESTER();
		/**
	   * @brief get doc application
	   * @return NctiDisplayDocApplication
	   */
		NctiDisplayDocApplication* GetDocApplication() { return m_pDocApplication; }
		/**
	   * @brief get all display object map,include object and id
	   */
		void GetDataIdAndObjectVec(std::map<Ncti_Size, NctiDisplayObject*>& o_DataIdAndObjectVec) { o_DataIdAndObjectVec = m_DataIdAndObjectVec; }
		/**
	   * @brief get a display object by id
	   */
		NctiDisplayObject* GetObjectFromDataId(Ncti_Size i_id);
	public:
		/**
	   * @brief get file version doc element, internal use
	   * @return NctiFileVersionDocElement
	   */
		NctiFileVersionDocElement* GetFileVersionDocElement() { return m_FileVersionDocElement; }
		/**
	   * @brief set file version doc element, internal use
	   */
		void SetFileVersionDocElement(NctiFileVersionDocElement* i_pFileVersionDocElement) { m_FileVersionDocElement = i_pFileVersionDocElement; }
		/**
	   * @brief internal use
	   */
		void NotifyHistoryEvent(NctiBltBrdDocViewMan* i_pBBDocViewMan);
		/**
	   * @brief internal use
	   */
		void refresh_instance_list();
		/**
	   * @brief internal use
	   */
		void GetOwnerDocElements(NctiDisplayObject* i_pFindDo, NctiDisplayObjectList& o_cOwnerDocList);
		/**
	   * @brief internal use
	   */
		NctiDisplayDocInstance* FindDocInstance(NctiBaseView* i_pBaseView, NctiDisplayDocElement* o_pDocElement);
		/**
	   * @brief internal use
	   */
		void AddDataIdAndObjectVec(Ncti_Size i_id, NctiDisplayObject* i_pObj);
		/**
	   * @brief active document for element, internal use
	   * @return EnumNctiResult
	   */
		EnumNctiResult ActivateDocument(NctiDisplayDocElement* i_pDocElement);
		/**
	   * @brief init view objects, internal use
	   * @return EnumNctiResult
	   */
		EnumNctiResult InitViewObjects();
		/**
	   * @brief add view object for view manager, internal use
	   */
		void AddViewObject(NctiDisplayViewObject* i_pDoViewObj);
		/**
	   * @brief create document name for element, internal use
	   * @return char*
	   */
		char* CreateUniqueDocumentName(NctiDisplayDocElement* i_pDocElement);
		/**
	   * @brief internal used
	   */
		NctiDocumentCounter* get_document_counter(const char* i_pszDocumentId);
		/**
	   * @brief create instance name for element, internal use
	   * @return char*
	   */
		char* CreateInstanceName(NctiDisplayDocElement* i_pDocElement);
		/**
	   * @brief Instantiate document for the base, internal use
	   * @return char*
	   */
		EnumNctiResult InstantiateDocuments(NctiBaseView* i_pBaseView);
		/**
	   * @brief build a tree for the base, internal use
	   * @return char*
	   */
		void BuildTree(NctiBaseView* i_pBaseView);
		/**
	   * @brief internal use
	   */
		NctiTransf GetNetTransform(NctiDisplayObject* i_pDoInstance);
		/**
	   * @brief internal use
	   */
		void NotifyWorkPlaneChanged(NctiDisplayObject* i_pDoWorkPlane);
		/**
	   * @brief internal use
	   */
		EnumNctiResult Erase(NctiDisplayObject* i_pDo);
		/**
	   * @brief internal use
	   */
		EnumNctiResult Display(NctiDisplayObject* i_pDo);
		/**
	   * @brief internal use
	   */
		NctiDisplayDocElement* GetPreviousActiveDocElement();
		/**
	   * @brief internal use
	   */
		virtual Ncti_Boolean BltBrdCallback(NctiBulletinBoard* i_pBltBrd, Ncti_Boolean i_bRollback);
		/**
	   * @brief internal use
	   */
		void NotifyViewDeletion(NctiBaseView* i_pBaseView);
		/**
	   * @brief internal use
	   */
		NctiThreadPool* GetThreadPool() { return m_ThreadPool; }
	private:
		/**
	   * @brief internal use
	   */
		EnumNctiResult open_one_file(const char* i_cpFileName, NCTI::NctiDisplayDocElement*& o_DisplayDocElement);
		/**
	   * @brief internal use
	   */
		EnumNctiResult sd_restore_sub_documents(
			NctiDisplayDocElement* i_pRootDo,
			NctiDisplayObjectList* i_pListDocProxy,
			NctiDisplayObjectList* i_pListDocRestored,
			Ncti_Integer i_iType = 0,
			NctiDisplayObjectList* i_pAllNewElementList = nullptr);
		/**
	   * @brief internal use
	   */
		void move_work_to_actual(NctiFileInterface* i_pFileInterface);
		/**
	   * @brief internal use
	   */
		void save_file_version(const char* i_FileName);
		/**
	   * @brief internal use
	   */
		void save_one_file(NctiDisplayDocElement* i_SaveDocElement, const char* i_FileName = nullptr);
		/**
	   * @brief internal use
	   */
		NctiDisplayDocElement* read_one_file(const char* i_FileName);
		/**
	   * @brief internal use
	   */
		EnumNctiResult restore_sub_documents(
			NctiDisplayDocElement* i_pRootDo,
			NctiDisplayObjectList* i_pListDocProxy,
			NctiDisplayObjectList* i_pListDocRestored,
			NctiDisplayObjectList* i_pAllNewElementList = nullptr);
		/**
	   * @brief internal use
	   */
		void SetOwnerPointers();
		/**
	   * @brief internal use
	   */
		void SetOwnerPointers_Document(NctiDisplayDocElement* i_pDocElement); 
		/**
	   * @brief internal use
	   */
		void SetOwnerPointers_List(NctiDisplayObject* i_pOwner, NctiDisplayObjectList* i_pDoList); 
		/**
	   * @brief internal use
	   */
		Ncti_Boolean set_owner_pointers_attributes(NctiDisplayObject* pDo);
		/**
	   * @brief internal use
	   */
		void add_document_counter(NctiDocumentCounter* i_pDocumentCounter);
		/**
	   * @brief internal use
	   */
		EnumNctiResult InstantiateDocuments();
		/**
	   * @brief internal use
	   */
		void fix_instance_pointer(NctiBaseView* i_pBaseView, NctiDisplayObjectList* i_pDoListOriginal, NctiDisplayObjectList* i_pDoListInstance);
		/**
	   * @brief internal use
	   */
		void refresh_instance_list(NctiBaseView* i_pBaseView);
		/**
	   * @brief internal use
	   */
		void refresh_session_tag(NctiBaseView* i_pViewTarget);
		/**
	   * @brief internal use
	   */
		void reset_session_tag(NctiDisplayObjectList* i_pDoList);
		/**
	   * @brief get the file list, if doc is assembly,  internal use
	   */
		void get_all_file(std::vector<std::string>& o_FileList);
		/**
	   * @brief help function for get_all_file,  internal use
	   */
		void get_all_file_ex(NctiDisplayDocElement* i_pFisrt, NctiDisplayObjectList* i_pListDocRestored);
	private:
		NctiFileVersionDocElement* m_FileVersionDocElement;
		char* m_cpBaseDirectoryPath;
		NctiBaseModel* m_pBaseModel;
		NctiDisplayDocApplication* m_pDocApplication;

		NctiDocumentCounter** m_paDocumentCounter;
		Ncti_Integer	m_iNumDocumentCounter;
		Ncti_Integer	m_iDocumentCounterArraySize;
		char* m_cpNameString;

		Ncti_Boolean m_bUpdateSessionTag;
		Ncti_Boolean m_bOriginalDataModified;
		NctiDisplayObjectList* m_pOriginalList;
		NctiThreadPool* m_ThreadPool;
	protected:
		NctiDisplayDocElement* m_pRootDocElement;
		NctiDisplayDocElement* m_pActiveDocElement;
		NctiDisplayDocElement* m_pPreviousActiveDocElement;
		NctiDisplayObject* m_pDocSketch;
	private:
		std::map<Ncti_Size, NctiDisplayObject*> m_DataIdAndObjectVec;
	};
}
DECL_NCTI NCTI_MANAGER_TYPEDEF(NctiDocViewManager)
#endif
