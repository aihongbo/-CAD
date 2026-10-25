#ifndef NctiCommand_H
#define NctiCommand_H
#include "ncti.h"

#define NCTI_COMMAND_FUNCTIONS( COMMAND_NAME )	\
	friend class NctiCommandManager;\
public:\
	static const char* ID;\
	COMMAND_NAME( );\
	virtual const char* TypeName(){ return COMMAND_NAME::ID; };\
	virtual Ncti_Boolean		IsTypeName( const char *sTypeName );\
	virtual Ncti_UInteger GetDerrivationLevel();\
	virtual NctiCommand* Instantiate();

#define NCTI_COMMAND_DEF( COMMAND_NAME, COMMAND_NAME_DERIVED_FROM, IDENTITY_STRING ) \
	const char* COMMAND_NAME::ID = IDENTITY_STRING;\
	Ncti_Boolean COMMAND_NAME::IsTypeName( const char *sTypeName )\
	{\
		if ( strcmp( COMMAND_NAME::ID, sTypeName ) == 0 )\
		{\
			return true;\
		}\
		return COMMAND_NAME_DERIVED_FROM::IsTypeName( sTypeName );\
	}\
	Ncti_UInteger COMMAND_NAME::GetDerrivationLevel()\
	{\
		Ncti_UInteger retval = COMMAND_NAME_DERIVED_FROM::GetDerrivationLevel() + 1;\
		return retval;\
	}\
	NctiCommand* COMMAND_NAME::Instantiate()\
	{\
		NctiCommand* pCopyCommand = NCTI_NEW COMMAND_NAME();\
		return pCopyCommand;\
	}
#define NCTI_COMMAND_REGISTRATION( COMMAND_NAME ) \
	NctiCommand* Generate_##COMMAND_NAME()\
	{\
		NctiCommand* pCommand = NCTI_NEW COMMAND_NAME( );\
		return pCommand;\
	}\
	static NctiCommandGenerator Register_##COMMAND_NAME(\
								(NctiCommand* (*)(...))Generate_##COMMAND_NAME );

#define NCTI_COMMAND_ADD_DO( COMMAND_NAME, DISPLAYOBJECT ) \
	static NctiCommandDoMapper CommandDoMap_##DISPLAYOBJECT( COMMAND_NAME::ID, DISPLAYOBJECT::ID );

#define NCTI_COMMAND_TITLE( COMMAND_TITLE )\
	if ( m_cpCommandTitle != nullptr )\
	{\
		NCTI_DELETE [] m_cpCommandTitle;\
		m_cpCommandTitle = nullptr;\
	}\
	size_t iSize = strlen( COMMAND_TITLE );\
	m_cpCommandTitle = NCTI_NEW char[iSize + 1];\
	strcpy( m_cpCommandTitle, COMMAND_TITLE );

#define NCTI_COMMAND_ACTIVATE_COMMON \
	if ( m_bTerminationRequested == true )\
	{\
		m_pCommandManager->RequestTermination( this );\
	}\
	if ( m_bActivated == true  )\
	{\
		return NCTI_FAILED;\
	}\
	NctiSelectionManager* pSelMan = NULL; \
	NctiDocViewManager* pDocViewMan = NULL; \
	NctiHistoryManager* pHisMan = NULL; \
	pSelMan = NctiSelectionManager::GetSelectionManager(m_pCommandManager); \
	pDocViewMan = NctiDocViewManager::GetDocViewManager(m_pCommandManager); \
	pHisMan = NctiHistoryManager::GetHistoryManager(m_pCommandManager); \
	if (pSelMan == NULL || pDocViewMan == NULL || pHisMan == NULL)\
	{\
	return NCTI_FAILED; \
	}\
	{\
	NctiSelectionDataNewList cSelectDataList; \
	NctiSelectionDataList cTempSelDataList; \
	pSelMan->GetSelected(cTempSelDataList); \
	cTempSelDataList.Init(); \
	NctiSelectionData* pSelData = NULL; \
	while ((pSelData = cTempSelDataList.Next()) != NULL)\
	{\
	NctiSelectionData* pCopy = pSelData->MakeCopy(); \
	pCopy->SetFilterFlag(pSelData->GetFilterFlag()); \
	cSelectDataList.AddData(pCopy); \
	}\
	pSelMan->ResetSelection(); \
	if (cSelectDataList.GetIterationCount() > 0)\
	{\
	pSelMan->SetSelected(cSelectDataList); \
	}\
	}
#define NCTI_COMMAND_DEACTIVATE \
	/*m_bActivated = false;*/ /* Reset flag in order to allow new call */ \
	NctiLocalDeactivateWhenExit _deactivate(this);\
	m_bTerminationRequested = false;/* Reset flag */ \
	initialize_status();\

namespace NCTI
{
	class NctiDisplayObject;
	class NctiTool;
	class NctiSelectionFilter;
    class NctiCommandManager;
	/**
	* @brief The Base class of Register Command
	* @details all command come from this
	* @see NctiCommandManager
	*/
	class DECL_NCTI NctiCommand : public NCTI_BASE_CLASS
	{
		friend class NctiCommandManager;
		friend class NctiLocalDeactivateWhenExit;
	public:
		NctiCommand();
		virtual ~NctiCommand();
		/**
	   * @brief get the type name
	   * @details need to implement, override
	   * @return const char*
	   */
		virtual const char* TypeName() = 0;
		/**
	   * @brief check if the command type is correct
	   * @param[in] i_psName, the type of command object
	   * @return Ncti_Boolean
	   */
		virtual Ncti_Boolean IsTypeName(const char* i_psName) = 0;
		/**
	   * @brief start the command
	   * @param[in] i_pDoInstance, support all display object type,you can deal it by yourself
	   * @return EnumNctiResult
	   */
		virtual EnumNctiResult Activate(NctiDisplayObject* i_pDoInstance) = 0;
		/**
	   * @brief end the command
	   * @return EnumNctiResult
	   */
		virtual EnumNctiResult DeActivate();
		/**
	   * @brief end the command
	   * @return EnumNctiResult
	   */
		Ncti_Boolean IsActivated();
		/**
	   * @brief get the command title name
	   * @return const char*
	   */
		const char* GetCommandTitle() { return m_cpCommandTitle; };
		/**
	   * @brief get the tool of command
	   * @return NctiTool
	   */
		NctiTool* GetTool() { return m_pTool; };
		/**
	   * @brief command event
	   * @details need to implement, override
	   * @return NctiTool
	   */
		virtual void ProcessUpdate();
		/**
	   * @brief internal used
	   */
		virtual Ncti_UInteger GetDerrivationLevel();
		/**
	   * @brief to over the command
	   * @details next, it will run DeActivate() function
	   * @return NctiTool
	   */
		void RequestTermination();
		/**
	   * @brief internal used
	   */
		void set_command_manager(NctiCommandManager* i_pCommandManager);
		/**
	   * @brief get the default tool of command
	   * @return NctiTool
	   */
		NctiTool* GetDefaultTool() { return m_pTool; };
		/**
	   * @brief command event
	   * @details need to implement, override
	   * @return NctiTool
	   */
		virtual NctiCommand* Instantiate() = 0;
		/**
	   * @brief internal used
	   */
		Ncti_Boolean IsCancelProcessed() { return m_bCancelProcessed; };
		/**
	   * @brief command event
	   * @details need to implement, override
	   * @return NctiTool
	   */
		virtual void NotifyJobStatusChanged();
		/**
	   * @brief command event
	   * @details need to implement, override
	   * @return NctiTool
	   */
		virtual void NotifyJobFinished();
		/**
	   * @brief command event
	   * @details need to implement, override
	   * @return NctiTool
	   */
		virtual void NotifyDragModeChanged();
		/**
	   * @brief command event
	   * @details need to implement, override
	   * @return NctiTool
	   */
		virtual void ProcessCancelButton();
		/**
	   * @brief command event
	   * @details need to implement, override
	   * @return NctiTool
	   */
		virtual void ProcessOkButton();
		/**
	   * @brief command event
	   * @details need to implement, override
	   * @return NctiTool
	   */
		virtual void ProcessCancel();
		/**
	   * @brief command event
	   * @details need to implement, override
	   * @return NctiTool
	   */
		virtual void ProcessUndo();
		/**
	   * @brief command event
	   * @details need to implement, override
	   * @return NctiTool
	   */
		virtual void ProcessRedo();
		/**
	   * @brief command event
	   * @details need to implement, override
	   * @return NctiTool
	   */
		virtual void ProcessPreUndo();
		/**
	   * @brief command event
	   * @details need to implement, override
	   * @return NctiTool
	   */
		virtual void ProcessPreRedo();
		/**
	   * @brief command event
	   * @details need to implement, override
	   * @return NctiTool
	   */
		virtual void ProcessOk();
		/**
	   * @brief internal used
	   */
		void SetInterruptCommand(NctiCommand* i_InterruptCommand);
		/**
	   * @brief internal used
	   */
		NctiCommand* GetInterruptCommand() { return m_pInterruptCommand; }
		/**
	   * @brief internal used
	   */
		virtual Ncti_Boolean IsUseTimerEvent() { return false; };
		/**
	   * @brief check command status
	   * @return NctiTypeCommandStatus
	   */
		NctiTypeCommandStatus CheckStatus(const NctiTypeCommandStatus  i_TypeToCheck, NctiDisplayObject* i_pDoOptional = nullptr);
		/**
	   * @brief internal used
	   */
		NctiDisplayObject* GetTriggerDoInstance() { return m_pTriggerDoInstance; }
		/**
	   * @brief internal used
	   */
		NctiDisplayObject* GetTriggerDoOriginal() { return m_pTriggerDoOriginal; }
	protected:
		/**
	   * @brief internal used
	   */
		virtual void start_default_tool();
		/**
	   * @brief internal used
	   */
		virtual void end_default_tool();
		/**
	   * @brief internal used
	   */
		void initialize_status();
		/**
	   * @brief internal used
	   */
		void SetDefaultSelectionFilter();
		/**
	   * @brief internal used
	   */
		virtual Ncti_Boolean check_status_executable(){ return false; }
		/**
	   * @brief internal used
	   */
		virtual Ncti_Boolean check_status_on(){ return false; }
		/**
	   * @brief internal used
	   */
		void set_trigger_do(NctiDisplayObject* i_pDo);
	protected:
		char* m_cpCommandTitle;
		Ncti_Boolean m_bActivated;
		Ncti_Boolean m_bViewActive;
		NctiTool* m_pTool;
		NctiCommand* m_pInterruptCommand;
		Ncti_Boolean m_bUpdated;
		Ncti_Boolean m_bTerminationRequested;
		NctiCommandManager* m_pCommandManager;
		NctiSelectionFilter* m_pSelectionFilter;
		NctiPickType m_iPickType;

		Ncti_Boolean	m_bOkButtonPushed;
		Ncti_Boolean	m_bCancelButtonPushed;
		Ncti_Boolean	m_bOkProcessed;
		Ncti_Boolean	m_bCancelProcessed;
		Ncti_Boolean	m_bPickPositionProcessed;

		NctiDisplayObject* m_pOptionalDoToCheckExecutable;

		NctiDisplayObject* m_pTriggerDoInstance;
		NctiDisplayObject* m_pTriggerDoOriginal;
	};
	/**
	* @brief internal used
	*/
	class DECL_NCTI NctiLocalDeactivateWhenExit
	{
		NctiLocalDeactivateWhenExit() {};
	public:
		NctiLocalDeactivateWhenExit(NctiCommand* pOwner) { m_pOwner = pOwner; };
		virtual ~NctiLocalDeactivateWhenExit()
		{
			if (m_pOwner != nullptr)
			{
				m_pOwner->m_bActivated = false;
			}
		}
	protected:
		NctiCommand* m_pOwner;
	};
	/**
	* @brief internal used
	*/
	class DECL_NCTI NctiSetValueWhenExit
	{
		NctiSetValueWhenExit() {};
	public:
		NctiSetValueWhenExit(Ncti_Boolean& bVariableToSet, const Ncti_Boolean bValue)
		{
			m_bVariableToSet = &bVariableToSet;
			m_bValue = bValue;
		}

		~NctiSetValueWhenExit()
		{
			*m_bVariableToSet = m_bValue;
		}
	protected:
		Ncti_Boolean *m_bVariableToSet;
		Ncti_Boolean m_bValue;
	};
}
#endif // !NctiCommand_H
