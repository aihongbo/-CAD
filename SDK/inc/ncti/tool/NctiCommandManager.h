#ifndef NctiCommandManager_H
#define NctiCommandManager_H
#include "NctiManager.h"
#include <vector>
namespace NCTI
{
	class NctiCommand;
	class NctiTool;
	class NctiCommandCharList;
	/**
	* @brief internal used
	*/
	class DECL_NCTI NctiJobBase : public NCTI_BASE_CLASS
	{
	public:
		NctiJobBase();
		virtual ~NctiJobBase();
		virtual EnumNctiResult Execute();
		NctiJobBase* GetNext();
		void SetNext(NctiJobBase* i_pNext);
		virtual void CheckProcessStatus();
		EnumNctiJobStatus GetState();
		virtual void ProcessCancel();
	protected:

		EnumNctiJobStatus m_eState;
		NctiJobBase* m_pNext;
	};
	/**
	* @brief internal used
	*/
	class DECL_NCTI NctiCommandDoMapper : public NCTI_BASE_CLASS
	{
	public:
		NctiCommandDoMapper(const char* i_pszCommandName, const char* i_pszDoName);
		virtual ~NctiCommandDoMapper();
		NctiCommandDoMapper* GetNext() { return m_pNextDoMapper; };
		char* GetDoName() { return m_pszDoName; }
		char* GetCommandName() { return m_pszCommandName; }
	protected:
		char* m_pszCommandName;
		char* m_pszDoName;
		NctiCommandDoMapper* m_pNextDoMapper;
	};
	/**
	* @brief internal used
	*/
	class DECL_NCTI NctiCommandGenerator : public NCTI_BASE_CLASS
	{
	public:
		NctiCommandGenerator(NctiCommand*(*)(...));
		void SetNext(NctiCommandGenerator* i_pNext) { m_pNextGenerator = i_pNext; };
		NctiCommandGenerator* GetNext() { return m_pNextGenerator; };
		NctiCommand* GenerateCommand();
		const char* GetTargetName() { return m_pTargetName; };
	private:
		const char* m_pTargetName;
		NctiCommand* (*m_pProcPointer)(...);
		NctiCommandGenerator* m_pNextGenerator;
	};
	/**
	* @brief internal used
	*/
	class DECL_NCTI NctiJobControler : public NCTI_BASE_CLASS
	{
	public:
		NctiJobControler();
		virtual ~NctiJobControler();
		void InitJob();
		void AddJob(NctiJobBase* i_pJob);
		void ClearJob();
		void UpdateJob(Ncti_Boolean& i_bChanged);
		void GetJobProgress(Ncti_Integer& i_iFinished, Ncti_Integer& i_iTotal);
		void ProcessCancel();
	private:

		NctiJobBase** m_apJobSlot;
		NctiJobBase* m_pFirst;
		Ncti_Integer m_iTotal;
		Ncti_Integer m_iIndex;
		Ncti_Integer m_iNumJobSlot;
		Ncti_Integer m_iFinished;
		NctiJobBase* m_pCurrent;
		NctiJobBase* m_pLast;
		Ncti_Boolean m_bCancel;
	};
	class NctiBaseView;
	/**
	* @brief manager all command
	* @see NctiCommand
	*/
	class DECL_NCTI NctiCommandManager : public NctiManager
	{
		NCTI_MANAGER_FUNCTIONS(NctiCommandManager)
	public:
		virtual ~NctiCommandManager();
	public:
		/**
	   * @brief Initialization during obj class creation
	   */
		void Init();
		/**
	   * @brief set default tool
	   * @param[in] i_pDefaultTool, the system tool or default tool
	   */
		void SetDefaultTool(NctiTool* i_pDefaultTool);
		/**
	   * @brief get default tool
	   * @return NctiTool
	   */
		NctiTool* GetDefaultTool() { return m_pDefaultTool; }
		/**
	   * @brief get active tool
	   * @return NctiTool
	   */
		NctiTool* GetActiveTool();
		/**
	   * @brief get active command
	   * @return NctiCommand
	   */
		NctiCommand* GetActiveCommand();
		/**
	   * @brief request termination the command
	   * @param[in] i_pTargetCommand
	   * @return NctiCommand
	   */
		void RequestTermination(NctiCommand* i_pTargetCommand);
		
		/**
		* @brief get all commnad names
		* @return all command names
		*/
		std::vector<std::string> GetCommandCharList();
	private:
		NctiTool* m_pDefaultTool;
		NctiCommand* m_pActiveCommand;
		Ncti_Boolean m_bTerminationRequested;
		NctiCommand* m_pCommandTerminated;
		NctiCommandCharList* m_pCommandCharList;
		Ncti_Integer m_iNum;
		Ncti_Integer m_iSize;
		NctiCommand** m_paCommand;
		NctiJobControler* m_pJobControler;
		Ncti_Boolean m_bRequestNextCommand;
		NctiDisplayObject* m_pNextDoTarget;
		NctiCommand* m_pNextCommand;
		Ncti_Boolean m_bNotifyDragModeChanged;
	public:
		/**
	   * @brief Queue Command by command name
	   * @details next to Run(), it will active Queue Command
	   * @param[in] i_pTargetCommand
	   * @return EnumNctiResult
	   */
		EnumNctiResult QueueCommand(const char* i_psDoName, NctiDisplayObject* i_pDoActivated = nullptr);
		/**
	   * @brief Queue Command by i_pDoInstance
	   * @details next to Run(), it will active Queue Command
	   * @param[in] i_pTargetCommand
	   * @return EnumNctiResult
	   */
		EnumNctiResult QueueCommand(NctiDisplayObject* i_pDoInstance);
		/**
	   * @brief add the new command to manager
	   * @param[in] i_pNewCommand
	   * @return EnumNctiResult
	   */
		EnumNctiResult AddCommand(NctiCommand* i_pNewCommand);
		/**
	   * @brief to run the current command
	   * @return EnumNctiResult
	   */
		EnumNctiResult Run();
		/**
	   * @brief get Queue Command status
	   * @param[in] i_pszCommandID
	   * @return NctiTypeCommandStatus
	   */
		NctiTypeCommandStatus QuerryCommandStatus(const char* i_pszCommandID, NctiDisplayObject* i_pOptionalDoToCheck = NULL);
		/**
	   * @brief exit the command
	   * @details the command is running,it don't end
	   */
		void ExitCommand();
	protected:
		/**
	   * @brief internal used
	   */
		Ncti_Integer lookup_command(NctiCommand* i_pCommand);
		/**
	   * @brief internal used
	   */
		EnumNctiResult set_next_command(NctiDisplayObject* i_pDoNextTarget, NctiCommand* i_pNextCommand);
		/**
	   * @brief internal used
	   */
		void expand(Ncti_Integer i_iNewSize);
		/**
	   * @brief internal used
	   */
		void remove(Ncti_Integer i_iIndex);
		/**
	   * @brief internal used
	   */
		void de_activate_current_command();
		/**
	   * @brief internal used
	   */
		void redraw_command_button();
		/**
	   * @brief internal used
	   */
		void interrupt(NctiCommand* i_pCommand);
	public:
		/**
	   * @brief internal used
	   */
		virtual void NotifyTermination();
		/**
	   * @brief internal used
	   */
		void NotifyViewDeletion(NctiBaseView* i_pBaseView);
		/**
	   * @brief internal used
	   */
		void NotifyTimerEvent();
		/**
	   * @brief internal used
	   */
		void CheckTermination();
	public:
		/**
	   * @brief run active command ProcessUpdate
	   */
		void ProcessUpdate();
		/**
	   * @brief run active command ProcessESC
	   */
		void ProcessESC();
		/**
	   * @brief run active command ProcessOkButton
	   */
		void ProcessOkButton();
		/**
	   * @brief run active command ProcessCancelButton
	   */
		void ProcessCancelButton();
		/**
	   * @brief run active command ProcessUndo
	   */
		void ProcessUndo();
		/**
	   * @brief run active command ProcessRedo
	   */
		void ProcessRedo();
		/**
	   * @brief run active command ProcessPreUndo
	   */
		void ProcessPreUndo();
		/**
	   * @brief run active command ProcessPreRedo
	   */
		void ProcessPreRedo();
	public:
		/**
	   * @brief run the command by command register name
	   * @param[in] i_cpCommand, the command register name
	   * @param[in] i_pDoActivated, the display object
	   * @return EnumNctiResult
	   */
		EnumNctiResult RunCommand(const char* i_cpCommand, NctiDisplayObject* i_pDoActivated = nullptr);
	public:
		/**
	   * @brief get command manager by NctiBaseView
	   * @param[in] i_pBaseView, the render view
	   * @return NctiCommandManager
	   */
		static NctiCommandManager* GetCommandManager(NctiBaseView* i_pBaseView);
		/**
	   * @brief get command manager by NctiBaseView
	   * @param[in] i_pBaseView, the render view
	   * @return NctiCommandManager
	   */
		static NctiCommandManager* GetCommandManager(NctiBaseModel* i_pBaseModel);
		/**
	   * @brief get command manager by NctiBaseView
	   * @param[in] i_pBaseView, the render view
	   * @return NctiCommandManager
	   */
		static NctiCommandManager* GetCommandManager(NctiManager* i_pManager);
	};
}
DECL_NCTI NCTI_MANAGER_TYPEDEF(NctiCommandManager)
#endif
