#ifndef NctiHistoryManager_H
#define NctiHistoryManager_H
#include "NctiManager.h"
#include "NctiBulletinBoard.h"
#include <map>
namespace NCTI
{
	class NctiDisplayObject;
	class NctiCommandStateFactory;
	class NctiCommandState;
	class NctiBulletinBoard;
	class NctiBulletin;
	class NctiDisplayObjectList;
	class NctiDisplayDocElement;
	class NctiBaseView;
	/**
	* @brief history manager
	* @details undo and redo, history can include other history
	* @see NctiManager
	*/
	class DECL_NCTI NctiHistoryManager : public NctiManager
	{
		NCTI_MANAGER_FUNCTIONS(NctiHistoryManager)
	public:
		virtual ~NctiHistoryManager();
	public:
		/**
	   * @brief start a history by history manager
	   * @param[in] i_cpCommandPrompt, the history name
	   * @param[out] o_iDepth, get the history depth, if o_iDepth is 0, the history is only one
	   * @return EnumNctiResult
	   */
		EnumNctiResult StartState(const char* i_cpCommandPrompt, 
			Ncti_Integer& o_iDepth, 
			NctiDisplayObject* i_pDoCallback = nullptr, 
			EnumNctiDoCallbackType i_eDoCallbackType = NCTI_DO_CALLBACK_UPDATE_SHAPE);
		/**
	   * @brief end a history by history manager
	   * @param[in] i_eStatus, NCTI_FAILED,NCTI_SUCCEEDED
	   * @param[out] o_iDepth, get the history depth, if o_iDepth is 0, the history is only one
	   * @return EnumNctiResult
	   */
		EnumNctiResult NoteState(EnumNctiResult i_eStatus, Ncti_Integer& o_iDepth);
		/**
	   * @brief check if the history is active
	   * @return Ncti_Boolean
	   */
		Ncti_Boolean GetActive() { return m_bActive; };
		/**
	   * @brief set the history state
	   * @param[in] i_bActive, true or false
	   * @return Ncti_Boolean
	   */
		void SetActive(Ncti_Boolean i_bActive) { m_bActive = i_bActive; };
		/**
	   * @brief all the history will cancel
	   * @param[in] i_bCancel, true or false
	   */
		void SetCancel(Ncti_Boolean i_bCancel);
		/**
	   * @brief check if the history can undo
	   * @return Ncti_Boolean
	   */
		Ncti_Boolean CanRollBack();
		/**
	   * @brief check if the history can redo
	   * @return Ncti_Boolean
	   */
		Ncti_Boolean CanRollForward();
		/**
	   * @brief fix  the history's state
	   * @return Ncti_Boolean
	   */
		Ncti_Boolean FixCommandState();
		/**
	   * @brief commit the data for new object
	   * @param[in] i_pDisplayDocElement, the owner of new object
	   * @param[in] i_pDisplayObject,  the object to be created, create by lifecycle manager
	   */
		void NewDoList(NctiDisplayDocElement* i_pDisplayDocElement, NctiDisplayObject* i_pDisplayObject);
		/**
	   * @brief commit the modified data for new object
	   * @param[in] i_pDisplayObject, the object to be modified
	   */
		void ModifiedDoList(NctiDisplayObject* i_pDisplayObject);
		/**
	   * @brief commit the removed data for new object
	   * @param[in] i_pDisplayObject, the object to be removed
	   */
		void RemoveDoList(NctiDisplayObject* i_pDisplayObject);
		/**
	   * @brief internal used
	   * @return Ncti_Boolean
	   */
		Ncti_Boolean delete_rollforward_command_states();
		/**
	   * @brief internal used
	   * @return Ncti_Boolean
	   */
		NctiBulletinBoard* GetCurrentBulletinBoard();
		/**
	   * @brief internal used
	   * @return Ncti_Boolean
	   */
		NctiCommandState* GetCurrentCommandState();
		/**
	   * @brief internal used
	   * @return Ncti_Boolean
	   */
		NctiCommandStateFactory* GetCommandStateFactory();
		/**
	   * @brief internal used
	   * @return Ncti_Boolean
	   */
		NctiBulletin* CreateBulletin(NctiDisplayObject* i_pOldDo, NctiDisplayObject* i_pNewDo);
		/**
	   * @brief internal used
	   * @return Ncti_Boolean
	   */
		NctiBulletinBoard* CreateBulletinBoard(NCTI::NctiBulletinBoard::EnumNctiBulletinBoardType i_eBulletinBoardType);
		/**
	   * @brief internal used
	   * @return Ncti_Boolean
	   */
		Ncti_Integer RollNStates(Ncti_Integer i_iNumStates);
		/**
	   * @brief internal used
	   * @return Ncti_Boolean
	   */
		Ncti_Boolean check_command_exit(Ncti_Integer iNumStates);
		/**
	   * @brief internal used
	   * @return Ncti_Boolean
	   */
		Ncti_Boolean AddBulletinBoard(NctiBulletinBoard* i_pNewBulletinBoard);
		/**
	   * @brief internal used
	   * @return Ncti_Boolean
	   */
		virtual void NotifyTermination();
	protected:
		/**
	   * @brief internal used
	   * @return Ncti_Boolean
	   */
		Ncti_Boolean roll_back();
		/**
	   * @brief internal used
	   * @return Ncti_Boolean
	   */
		Ncti_Boolean roll_forward();
	protected:
		Ncti_Boolean m_bActive;
		NctiCommandStateFactory* m_pCommandStateFactory;
		NctiCommandState* m_pFirstCommandState; 
		NctiCommandState* m_pActiveCommandState;
		Ncti_Boolean m_bModellingOperationDetected;
	private:
		std::map<NctiDisplayDocElement*, NctiDisplayObjectList> m_cAddNewList;
		NctiDisplayObjectList* m_cModifiedDoList;
		std::map<NctiDisplayObject*, NctiDisplayObjectList> m_cDeleteList;
	private:
		/**
	   * @brief internal used
	   * @return Ncti_Boolean
	   */
		Ncti_Boolean MakeCallbackBulletinBoardBeginEnd(NctiDisplayObjectList* i_pcDoList, EnumNctiDoCallbackType i_eDoCallbackType);
	public:
		/**
	   * @brief internal used
	   * @return Ncti_Boolean
	   */
		Ncti_Boolean MakeCallbackBulletinBoardBeginEnd(EnumNctiDoCallbackType i_eDoCallbackType);
		/**
	   * @brief internal used
	   * @return Ncti_Boolean
	   */
		Ncti_Boolean MakeCallbackBulletinBoard(NctiDisplayObject* i_pDoTarget, EnumNctiDoCallbackType i_eDoCallbackType, EnumNctiBeginEnd i_eBeginEnd);
	public:
		/**
	   * @brief get history manager by NctiBaseView
	   * @param[in] i_pBaseView, the render view
	   * @return NctiHistoryManager
	   */
		static NctiHistoryManager* GetHistoryManager(NctiBaseView* i_pBaseView);
		/**
	   * @brief get history manager by NctiBaseModel
	   * @param[in] i_pBaseModel, the document base model, only one in a document
	   * @return NctiHistoryManager
	   */
		static NctiHistoryManager* GetHistoryManager(NctiBaseModel* i_pBaseModel);
		/**
	   * @brief get history manager by NctiManager
	   * @param[in] i_pManager, other manager
	   * @return NctiHistoryManager
	   */
		static NctiHistoryManager* GetHistoryManager(NctiManager* i_pManager);
	};
}
DECL_NCTI NCTI_MANAGER_TYPEDEF(NctiHistoryManager)
#endif
