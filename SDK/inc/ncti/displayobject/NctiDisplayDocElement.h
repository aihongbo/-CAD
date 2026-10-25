#ifndef NctiDisplayDocElement_H
#define NctiDisplayDocElement_H
#include "NctiDisplayObject.h"
#define NCTI_DOC_MULTI_INSTANCING_CAPABLE \
public:\
	virtual Ncti_Boolean IsMultiInstancingCapable(){ return true; };
namespace NCTI
{
	class NctiDisplayObjectList;
	class NctiDisplayDocInstance;
	/**
	* @brief Doc Element class
	* @details Base Class of Element.Such as Container, assembly, part
	* @see NctiDisplayObject
	*/
	class DECL_NCTI NctiDisplayDocElement : public NctiDisplayObject
	{
		NCTI_DISPLAYOBJECT_FUNCTIONS(NctiDisplayDocElement)
	public:
		/**
	   * @brief Initialization during obj class creation
	   */
		virtual void Init();
		virtual ~NctiDisplayDocElement();
	protected:
		/**
	   * @brief Initialization when saving the document obj class
	   * @details Define Core or Mesh Container, need to implement, override
	   * @return EnumNctiResult
	   */
		virtual EnumNctiResult restore_temp_file(NctiFileInterface* i_pFI);
	protected:
		NCTI_VERSION(1, NctiDisplayDocElement*, m_pNext, sd_read_long);
		NCTI_VERSION(1, NctiDisplayDocElement*, m_pFirstDescendant, sd_read_long);
	private:
		NCTI_READ_AND_WRITE_VERSION_FUN(1)
		NCTI_READ_AND_WRITE_VERSION_FUN(2)
	protected:
		NCTI_VERSION(1, NctiDisplayObjectList*, m_pPropDoList, sd_read_long);
		NCTI_VERSION(1, Ncti_Char*, m_cpInstanceName, sd_read_string);
		NCTI_VERSION(1, Ncti_Char*, m_cpFilePath, sd_read_string);
		NCTI_VERSION(2, Ncti_Size, m_MaxId, sd_read_size);
	private:
		//no save.
		Ncti_Boolean m_IsMissingSomeObject;
		Ncti_Integer m_ProXYRef;
	public:
		/**
	   * @brief set the save file name
	   * @details if element is assembly or part, it is the file name
	   * if element is proxy, assembly can find child element by proxy
	   * @param[in] i_cpFilePath the file name
	   * @return Ncti_Boolean
	   */
		void SetFilePath(const char* i_cpFilePath);
		/**
	   * @brief get the save file name
	   * @details if element is assembly or part, it is the file name
	   * if element is proxy, assembly can find child element by proxy
	   * @return const char*
	   */
		const char*	GetFilePath();
		/**
	   * @brief add the child for this element
	   * @details one element has many child element
	   * @param[in] i_pDocElement the child element
	   * @return EnumNctiResult
	   */
		EnumNctiResult AddDescendant(NctiDisplayDocElement* i_pDocElement);
		/**
	   * @brief get the last child in this element
	   * @details one element has many child element
	   * @return NctiDisplayDocElement
	   */
		NctiDisplayDocElement* GetLastElement();
		/**
	   * @brief get the same level element by next
	   * @return NctiDisplayDocElement
	   */
		NctiDisplayDocElement* GetNext();
		/**
	   * @brief set the next same level element
	   * @param[in] i_pNewNext the next element
	   */
		void SetNext(NctiDisplayDocElement* i_pNewNext);
		/**
	   * @brief get the child NctiDisplayObject by NctiDisplayObject Type
	   * @param[out] o_pDoList NctiDisplayObjectList
	   * @param[in] i_cpTypeId NctiDisplayObject Type, if i_cpTypeId is nullptr, get all child NctiDisplayObject
	   * @return the number of NctiDisplayObjectList
	   */
		Ncti_Integer GetAllDisplayObjectsByType(NctiDisplayObjectList* o_pDoList, const char* i_cpTypeId = nullptr);
		/**
	   * @brief get the all child NctiDisplayObject by NctiDisplayObject Type
	   * @param[out] o_pDoList NctiDisplayObjectList
	   * @param[in] i_iDepthLevel, if i_iDepthLevel is 0, add original DocElement as the first call
	   * @return the number of NctiDisplayObjectList
	   */
		Ncti_Integer	GetAllDisplayObjects(NctiDisplayObjectList* o_pDoList, Ncti_Integer i_iDepthLevel);
		/**
	   * @brief get the first child in this element
	   * @details one element has many child element
	   * @return NctiDisplayDocElement
	   */
		NctiDisplayDocElement*	GetFirstDescendant() { return m_pFirstDescendant; }
		/**
	   * @brief set the first child element in this element
	   * @details one element has many child element
	   * @param[in] i_pNewDescendant
	   */
		void SetDescendant(NctiDisplayDocElement* i_pNewDescendant);
		/**
	   * @brief internal used
	   * @return Ncti_Boolean
	   */
		void ActivateDocument(NctiFileInterface* i_pFI);
		/**
	   * @brief get the next level child element in this element
	   * @return NctiDisplayObjectList
	   */
		NctiDisplayObjectList* GetPropDoList();
		/**
	   * @brief add the next level child element in this element
	   * @return EnumNctiResult
	   */
		EnumNctiResult AddPropDo(NctiDisplayObject* i_pNewDisplayObject);
		/**
	   * @brief get the all child NctiDisplayDocElement 
	   * @param[out] o_pDoList NctiDisplayObjectList
	   * @return the number of NctiDisplayObjectList
	   */
		Ncti_Integer GetAllDescendants(NctiDisplayObjectList* o_pDoList);
	public:
		/**
	   * @brief internal used
	   * @return Ncti_Boolean
	   */
		virtual EnumNctiResult Instantiate(NctiBaseView* i_pBaseView, 
			NctiDisplayObjectList* i_pDoListOriginal, 
			NctiDisplayObjectList* o_pDoListInstance,
			NctiDisplayDocInstance* i_pDisplayDocInstance);

		/**
	   * @brief internal used
	   */
		virtual void GetTreeText(char* i_psIndent, char* o_psText);
		/**
	   * @brief remove the next level child element in this element
	   * @return EnumNctiResult
	   */
		EnumNctiResult RemovePropDo(NctiDisplayObject* i_pTargetDisplayObject);
		/**
	   * @brief internal used
	   * @return EnumNctiResult
	   */
		EnumNctiResult UnhookDescendant(NctiDisplayDocElement* i_pDocElement);
		/**
	   * @brief internal used
	   * @return EnumNctiResult
	   */
		EnumNctiResult RemoveDescendant(NctiDisplayDocElement* i_pDocElement);
		/**
	   * @brief internal used
	   * @return EnumNctiResult
	   */
		EnumNctiResult UnhookPropDo(NctiDisplayObject* i_pTargetDisplayObject);
		/**
	   * @brief internal used
	   * @return Ncti_Size
	   */
		Ncti_Size GetNewObjectId();
		/**
	   * @brief internal used
	   * @return Ncti_Boolean
	   */
		virtual Ncti_Boolean GetFileExtension(const char*& i_cpFileExtension) { return false; };
		/**
	   * @brief internal used
	   * @return Ncti_Boolean
	   */
		virtual Ncti_Boolean IsMultiInstancingCapable() { return false; };
		
		/**
	   * @brief internal used
	   * @return Ncti_Boolean
	   */
		void SetMissingSomeObject(Ncti_Boolean i_bboo) { m_IsMissingSomeObject = i_bboo; }
		/**
	   * @brief internal used
	   * @return Ncti_Boolean
	   */
		Ncti_Boolean IsMissingSomeObject() { return m_IsMissingSomeObject; }
		/**
	   * @brief internal used
	   * @return const char*
	   */
		const char* GetInstanceName() { return m_cpInstanceName; };
		/**
	   * @brief internal used
	   */
		void SetInstanceName(const char* i_cpInstanceName);

		/**
	   * @brief internal used
	   */
		Ncti_Integer GetProXYRef();
	protected:
		/**
	   * @brief internal used
	   * @return Ncti_Boolean
	   */
		void DeletePropDoList();
		/**
	   * @brief internal used
	   * @return Ncti_Boolean
	   */
		EnumNctiResult save_descendant(NctiFileInterface* i_pFI);
		/**
	   * @brief internal used
	   * @return Ncti_Boolean
	   */
		EnumNctiResult restore_descendant(NctiFileInterface* i_pFI);
		/**
	   * @brief internal used
	   * @return Ncti_Boolean
	   */
		EnumNctiResult save_next_document(NctiFileInterface* i_pFI);
		/**
	   * @brief internal used
	   * @return Ncti_Boolean
	   */
		EnumNctiResult restore_next_document(NctiFileInterface* i_pFI);
	};
}
#endif // !NctiDisplayDocElement_H
