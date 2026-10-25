#ifndef NctiHighlightManager_H
#define NctiHighlightManager_H
#include "NctiManager.h"
namespace NCTI
{
	class NctiSelectionData;
	class NctiSelectionDataHash;
	class NctiBooleanArray;
	class NctiBaseView;
	/**
	* @brief Highlight manager
	* @details manager selection data highlight
	* @see NctiManager
	*/
	class DECL_NCTI NctiHighlightManager : public NctiManager
	{
		NCTI_MANAGER_FUNCTIONS(NctiHighlightManager)
	public:
		virtual ~NctiHighlightManager();
		/**
	   * @brief highlight the selection data
	   * @param[in] i_pBaseSelData, the base selection class
	   * @return Ncti_Boolean
	   */
		Ncti_Boolean Highlight(NctiSelectionData* i_pBaseSelData);
		/**
	   * @brief unhighlight the selection data
	   * @param[in] i_pBaseSelData, the base selection class
	   * @return Ncti_Boolean
	   */
		Ncti_Boolean UnHighlight(NctiSelectionData* i_pBaseSelData);
		/**
	   * @brief internal used
	   */
		void NotifyTermination()override;
		/**
	   * @brief set to select body state
	   * @param[in] i_boo
	   */
		void SetIsSelectBody(Ncti_Boolean i_boo);
		/**
	   * @brief get to select body state
	   * @return Ncti_Boolean
	   */
		Ncti_Boolean GetIsSelectBody();
	private:
		NctiSelectionDataHash* m_pHighlightSelDataHash;
		NctiBooleanArray* m_pBoolNeedUpdate;
		Ncti_Boolean m_IsSelectBody;
	public:
		/**
	   * @brief get highlight manager by NctiBaseView
	   * @param[in] i_pBaseView, the render view
	   * @return NctiHighlightManager
	   */
		static NctiHighlightManager* GetHighlightManager(NctiBaseView* i_pBaseView);
		/**
	   * @brief get highlight manager by NctiBaseModel
	   * @param[in] i_pBaseModel, the document base model, only one in a document
	   * @return NctiHighlightManager
	   */
		static NctiHighlightManager* GetHighlightManager(NctiBaseModel* i_pBaseModel);
		/**
	   * @brief get highlight manager by NctiManager
	   * @param[in] i_pManager, other manager
	   * @return NctiHighlightManager
	   */
		static NctiHighlightManager* GetHighlightManager(NctiManager* i_pManager);
	};
}
DECL_NCTI NCTI_MANAGER_TYPEDEF(NctiHighlightManager)
#endif
