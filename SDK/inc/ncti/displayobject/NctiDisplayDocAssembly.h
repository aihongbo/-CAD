#ifndef NctiDisplayDocAssembly_H
#define NctiDisplayDocAssembly_H
#include "NctiDisplayDocElement.h"
#include <vector>
namespace NCTI
{   
	/**
	* @brief Doc Assembly class
	* @details Doc Assembly of NctiDisplayDocElement
	* @see NctiDisplayDocElement,NctiDisplayObject
	*/
	class DECL_NCTI NctiDisplayDocAssembly : public NctiDisplayDocElement
	{
		NCTI_DISPLAYOBJECT_FUNCTIONS(NctiDisplayDocAssembly)
			NCTI_DOC_FILE_SUPPORT
			NCTI_DOC_MULTI_INSTANCING_CAPABLE
	public:
		virtual ~NctiDisplayDocAssembly();
		/**
	   * @brief Initialization during obj class creation
	   */
		virtual void Init();
		virtual void GetTreeText(char* i_psIndent, char* i_psText);
		virtual EnumNctiDoCallbackStatus Callback(
			NctiBaseView* i_pBaseView,
			EnumNctiDoCallbackType i_eType, 
			NctiDisplayObject* i_pDoCaller);
	public:
		/**
	   * @brief set all the file list, excluding oneself, internal use
	   * @param[in] i_FileList, it come from NctiDocViewManager's get_all_file
	   */
		void SetFileList(const std::vector<std::string>& i_FileList);
		/**
	   * @brief get all the file list, excluding oneself
	   * @return const std::vector<std::string>& 
	   */
		const std::vector<std::string>& GetFileList() { return m_FileList; }
	private:
		NCTI_READ_AND_WRITE_VERSION_FUN(1)
		NCTI_READ_AND_WRITE_VERSION_FUN(2)
	private:
		std::vector<std::string> m_FileList;
	};
}
#endif
