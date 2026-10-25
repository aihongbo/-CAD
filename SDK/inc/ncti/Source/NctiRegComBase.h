#ifndef NctiRegComBase_H
#define NctiRegComBase_H
#include "NctiCommand.h"
#include "ncti.h"
#include "NctiSelectionDataList.h"
#include "NctiSelKeyDo.h"
#include "NctiSelectionDataNewList.h"
#include "NctiCommandManager.h"
#include "NctiHistoryManager.h"
#include "NctiDocViewManager.h"
#include "NctiSelectionManager.h"
#include "NctiDocViewManager.h"

namespace NCTI
{
	/**
	* @brief The Base Class of Command
	* @details you can create your owner command by this base class
	* @see NctiCommand
	*/
	class DECL_NCTI NctiRegComBase : public NctiCommand
	{
		NCTI_COMMAND_FUNCTIONS(NctiRegComBase)
	public:
		virtual ~NctiRegComBase();
	public:
		/**
	   * @brief start the command, need to implement, override
	   * @details it help you do something
	   * @param[in] i_pDoInstance, support all display object type,you can deal it by yourself
	   * @return EnumNctiResult
	   */
		virtual EnumNctiResult Activate(NctiDisplayObject* i_pDoTarget);
		/**
	   * @brief end the command, need to implement, override
	   * @details it help you do something
	   * @return EnumNctiResult
	   */
		virtual EnumNctiResult DeActivate();
	protected:
		virtual Ncti_Boolean on_command_record_infor();
	protected:
		void command_record_infor();
	protected:
		Ncti_Boolean m_IsCancel;
	};
}
#endif


