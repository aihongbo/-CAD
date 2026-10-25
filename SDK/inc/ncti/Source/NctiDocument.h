#ifndef NctiDocument_H
#define NctiDocument_H
#include "ncti.h"
#include "NctiMutex.h"
#include <map>
#include <vector>
namespace NCTI
{
	class NctiBaseModel;
	class NctiBaseView;
	class NctiDisplayDocPart;
	class NctiDisplayDocElement;
	class NctiDocumentManager;
	class DECL_NCTI NctiDocumentObject
	{
	public:
		NctiDocumentObject(){}
		virtual ~NctiDocumentObject(){}
	};
	/**
	* @brief only one document
	* @details one document has one base model, it can help you to get all the object or data
	* @see NctiBaseModel,NctiBaseView,NctiDocumentManager
	*/
	class DECL_NCTI NctiDocument
	{
	public:
        ~NctiDocument();
		/**
	   * @brief create a root assembly for document
	   * @details you need to run NewAssembleDocument first,then you can create child assembly or part,container
	   */
		void NewAssembleDocument();
		/**
	   * @brief create a root part for document
	   * @details you need to run NewPartDocument first,then you can create container, such as occ container
	   */
		void NewPartDocument();
		/**
	   * @brief read data by file path
	   * @details it will init all data,it don't include view
	   * @param[in] i_cpFileFullPath, if it is assembly, it's a root file path
	   * @return EnumNctiResult
	   */
		EnumNctiResult ReadFile(const char* i_cpFileFullPath);
		/**
	   * @brief save data by file path
	   * @details it will init all data
	   * @param[in] i_cpFileFullPath, if it is assembly, it's a root file path
	   * @param[in] SaveAs, if it is true ,it will SaveAs
	   * @param[in] bmanual_save, it will record save status
	   * @return EnumNctiResult
	   */
		EnumNctiResult SaveFile(const char* i_cpFileFullPath, Ncti_Boolean SaveAs = false, Ncti_Boolean bmanual_save =true);
		/**
	   * @brief get the base model
	   * @return EnumNctiResult
	   */
		NctiBaseModel* GetBaseModel() { return m_BaseModel; }
		/**
	   * @brief read the file image in a system object quickly 
	   * @param[in] i_cpFileFullPath, the file path
	   * @param[in] i_imagePathPng, the save image path
	   * @return EnumNctiResult
	   */
		EnumNctiResult ReadFileImage(const char* i_cpFileFullPath, const Ncti_Char* i_imagePathPng);
		/**
	   * @brief undo in a document
	   */
		void Undo();
		/**
	   * @brief redo in a document
	   */
		void Redo();
		/**
	   * @brief check if undo is valid in a document
	   */
		Ncti_Boolean IsUndoValid();
		/**
	   * @brief check if redo is valid in a document
	   */
		Ncti_Boolean IsRedoValid();
		/**
	   * @brief get document id
	   */
		Ncti_UInteger GetID() { return m_ID; }
	public:
		/**
	   * @brief internal used
	   */
		void AddDocumentObject(NctiDocumentObject* i_pDocumentObject);
		/**
	   * @brief internal used
	   */
		NctiDocumentObject* GetDocumentObject(Ncti_Integer i_num);
		/**
	   * @brief internal used
	   */
		NctiDisplayDocElement* ImportFile(const char* i_cpFileFullPath);
	public:
		/**
	   * @brief set Manual Modified
	   */
		void SetManualModified(Ncti_Boolean i_Modified);
		/**
	   * @brief get Manual Modified
	   * @return Ncti_Boolean
	   */
		Ncti_Boolean GetManualModified();
		/**
	   * @brief set Auto Modified
	   */
		void SetAutoModified(Ncti_Boolean i_Modified);
		/**
	   * @brief get Auto Modified
	   * @return Ncti_Boolean
	   */
		Ncti_Boolean GetAutoModified();
		/**
	   * @brief get doc mutex
	   * @return NctiMutex
	   */
		NctiMutex* GetDocMutex();

	private:
		friend class NctiDocumentManager;
		NctiDocument();

		NctiBaseModel* m_BaseModel;
		std::vector<NctiDocumentObject*> m_DocumentObjectVec;
		Ncti_UInteger m_ID;

		//auto save
		Ncti_Boolean m_manual_modified;
		Ncti_Boolean m_auto_modified;
		NctiMutex m_mutex;
	};
	/**
	* @brief manager the document
	* @details one document has one base model, it can help you to get all the object or data
	* @see NctiDocument
	*/
	class DECL_NCTI NctiDocumentManager
	{
	public:
		/**
	   * @brief get the document manager instance
	   * @return NctiDocumentManager
	   */
		static NctiDocumentManager* instance();
		/**
	   * @brief creat a new document
	   * @return NctiDocument
	   */
		NctiDocument* CreateDocument();
		/**
	   * @brief remove a document by id
	   * @return Ncti_Boolean
	   */
        Ncti_Boolean RemoveDocument(Ncti_UInteger i_id);
		/**
	   * @brief get a document by id
	   * @return NctiDocument
	   */
        NctiDocument* GetDocument(Ncti_UInteger i_id);
		/**
	   * @brief get all the document
	   * @return std::vector<NctiDocument*>
	   */
        std::vector<NctiDocument*> AllDocument();
		/**
	   * @brief get the ids of all the document
	   * @return std::vector<Ncti_UInteger>
	   */
        std::vector<Ncti_UInteger> AllID();

	private:
		std::map<Ncti_UInteger, NctiDocument*> m_DocumentMap;
		NctiMutex m_mutex;
	};
}
#endif
