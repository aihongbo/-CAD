#ifndef NctiTrace_H
#define NctiTrace_H
#include "ncti.h"
#include <vector>
namespace NCTI
{
	class NctiUserInterfaceManager;
	class NctiBaseView;
	class NctiDisplayObject;
	class NctiRenderGeometryItem;
	class NctiDocViewManager;
	/**
	* @brief custome user interface
	* @details help use to create Popup menu
	* @see NctiMenuInfo
	*/
	class DECL_NCTI NctiTrace : public NCTI_BASE_CLASS
	{
	public:
		NctiTrace();
		virtual~NctiTrace();
	public:
		/**
	   * @brief print message
	   * @details need to implement, override
	   */
		virtual Ncti_Integer Trace(const char* i_cpMessage);
	public:
		/**
	   * @brief HistoryIsStart
	   * @details need to implement, override
	   */
		virtual void HistoryIsStart();
		/**
	   * @brief HistoryIsEndBySucceeded
	   * @details need to implement, override
	   */
		virtual void HistoryIsEndBySucceeded();
		/**
	   * @brief HistoryIsEndByFailed
	   * @details need to implement, override
	   */
		virtual void HistoryIsEndByFailed();
	public:
		/**
	   * @brief UndoAndRedoStart
	   * @details need to implement, override
	   */
		virtual void UndoAndRedoStart();
		/**
	   * @brief UndoAndRedoEnd
	   * @details need to implement, override
	   */
		virtual void UndoAndRedoEnd();
	public:
		/**
	   * @brief NotifyDataChanged
	   * @details need to implement, override
	   */
		virtual void NotifyDataChanged(NctiDisplayObject* i_pDisplayObject, Ncti_Integer i_type, const char* i_id);
		/**
	   * @brief NotifySelectionDataChanged
	   * @details need to implement, override
	   */
		virtual void NotifySelectionDataChanged();
		/**
	   * @brief ExecuteCameraCallback
	   * @details need to implement, override
	   */
		virtual void ExecuteCameraCallback(NctiBaseView* i_pBaseView);
		/**
	   * @brief NotifyRenderItemSelectionDataChanged
	   * @details need to implement, override
	   */
		virtual void NotifyRenderItemSelectionDataChanged(NctiBaseView* i_pBaseView);
		/**
	   * @brief ElementTreeIsChanged
	   * @details need to implement, override
	   */
		virtual void ElementTreeIsChanged(NctiDocViewManager* pDocView){}

	public:
		/**
	   * @brief set user interface manager
	   */
		void SetUserInterfaceManager(NctiUserInterfaceManager* i_pUserInterfaceManager) { m_UserInterfaceManager = i_pUserInterfaceManager; }
		/**
	   * @brief get user interface manager
	   */
		NctiUserInterfaceManager* GetUserInterfaceManager() { return m_UserInterfaceManager; }
	protected:
		NctiUserInterfaceManager* m_UserInterfaceManager;
		std::vector<NctiDisplayObject*> m_DisplayObjectCallBackVec;
	};
}
#endif // !NctiTrace_H
