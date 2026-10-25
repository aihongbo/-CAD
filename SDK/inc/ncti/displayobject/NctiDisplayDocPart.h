#ifndef NctiDisplayDocPart_H
#define NctiDisplayDocPart_H
#include "NctiDisplayDocElement.h"
namespace NCTI
{
	/**
	* @brief Doc Part class
	* @details Doc Part of NctiDisplayDocElement
	* @see NctiDisplayDocElement,NctiDisplayObject
	*/
	class DECL_NCTI NctiDisplayDocPart : public NctiDisplayDocElement
	{
		NCTI_DISPLAYOBJECT_FUNCTIONS(NctiDisplayDocPart)
			NCTI_DOC_FILE_SUPPORT
			NCTI_DOC_MULTI_INSTANCING_CAPABLE
	public:
		virtual ~NctiDisplayDocPart();
	public:
		/**
	   * @brief Initialization during obj class creation
	   */
		virtual void Init();
		virtual void GetTreeText(char* i_psIndent, char* o_psText);
		virtual EnumNctiDoCallbackStatus Callback(
			NctiBaseView* i_pBaseView, 
			EnumNctiDoCallbackType i_eType, 
			NctiDisplayObject* i_pDoCaller);
	private:
		NCTI_READ_AND_WRITE_VERSION_FUN(1)
			NCTI_VERSION(1, Ncti_Integer, m_DocType, sd_read_long);
	};
}
#endif
