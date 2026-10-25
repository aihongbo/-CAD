#ifndef NctiDisplayDocProxy_H
#define NctiDisplayDocProxy_H
#include "NctiDisplayDocElement.h"
namespace NCTI
{
	/**
	* @brief Doc Proxy class
	* @details use to record element for assembly element
	* @see NctiDisplayDocElement,NctiDisplayObject
	*/
	class DECL_NCTI NctiDisplayDocProxy : public NctiDisplayDocElement
	{
		NCTI_DISPLAYOBJECT_FUNCTIONS(NctiDisplayDocProxy)
	public:
		virtual ~NctiDisplayDocProxy();
		/**
	   * @brief Initialization during obj class creation
	   */
		virtual void Init();
	public:
		virtual void GetTreeText(char* i_psIndent, char* o_psText);
		virtual EnumNctiDoCallbackStatus Callback(NctiBaseView* i_pBaseView, EnumNctiDoCallbackType i_eType, NctiDisplayObject* i_pDoCaller);
	private:
		NCTI_READ_AND_WRITE_VERSION_FUN(1)
	protected:
		NCTI_VERSION(1, Ncti_Integer, m_ModelType, sd_read_long)
	public:
		void SetModelType(Ncti_Integer nType);
		Ncti_Integer GetModelType() { return m_ModelType; }
	};
}
#endif
