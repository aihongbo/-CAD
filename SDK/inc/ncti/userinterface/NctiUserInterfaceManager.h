#ifndef NctiUserInterfaceManager_H
#define NctiUserInterfaceManager_H
#include "NctiManager.h"
namespace NCTI
{
	class NctiInputFileName;
	//class NctiModelInterface;
	class NctiTrace;
	class NctiBaseView;
	class NctiUserLockerInterface;
	class NctiUserPopupMenu;
	class NctiUserProgressBar;
	/**
	* @brief user interface manager
	* @details define some user interface
	* @see NctiManager
	*/
	class DECL_NCTI NctiUserInterfaceManager : public NctiManager 
	{
		NCTI_MANAGER_FUNCTIONS(NctiUserInterfaceManager)
	public:
		virtual~NctiUserInterfaceManager();
		EnumNctiResult SetInputFileName(NctiInputFileName* i_pInputFileName);
		NctiInputFileName* GetInputFileName() { return m_pInputFileName; }
		EnumNctiResult SetTrace(NctiTrace* i_pTrace);
		NctiTrace* GetTrace() { return m_pTrace; }
		EnumNctiResult SetUserLockerInterface(NctiUserLockerInterface* i_pUserLockerInterface);
		NctiUserLockerInterface* GetUserLockerInterface() { return m_pUserLockerInterface; }
		NctiUserPopupMenu* GetUserPopupMenu() { return m_UserPopupMenu; }
		EnumNctiResult SetUserPopupMenu(NctiUserPopupMenu* i_pUserPopupMenu);
		NctiUserProgressBar* GetUserProgressBar() { return m_UserProgressBar; }
		EnumNctiResult SetUserProgressBar(NctiUserProgressBar* i_pUserProgressBar);
	protected:
		NctiInputFileName*	m_pInputFileName;
		NctiTrace* m_pTrace;
		NctiUserLockerInterface* m_pUserLockerInterface;
		NctiUserPopupMenu* m_UserPopupMenu;
		NctiUserProgressBar* m_UserProgressBar;
	public:
		/**
	   * @brief get user interface manager by NctiBaseView
	   * @param[in] i_pBaseView, the render view
	   * @return NctiUserInterfaceManager
	   */
		static NctiUserInterfaceManager* GetUserInterfaceManager(NctiBaseView* i_pBaseView);
		/**
	   * @brief get user interface manager by NctiBaseModel
	   * @param[in] i_pBaseModel, the document base model, only one in a document
	   * @return NctiUserInterfaceManager
	   */
		static NctiUserInterfaceManager* GetUserInterfaceManager(NctiBaseModel* i_pBaseModel);
		/**
	   * @brief get user interface manager by NctiManager
	   * @param[in] i_pManager, other manager
	   * @return NctiUserInterfaceManager
	   */
		static NctiUserInterfaceManager* GetUserInterfaceManager(NctiManager* i_pManager);
	};
}
DECL_NCTI NCTI_MANAGER_TYPEDEF(NctiUserInterfaceManager)
#endif
