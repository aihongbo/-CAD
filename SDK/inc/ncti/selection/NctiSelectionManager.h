#ifndef NctiSelectionManager_H
#define NctiSelectionManager_H
#include "NctiManager.h"
#include "ncti_event.h"

namespace NCTI
{
	class NctiSelectionData;
	class NctiSelectionDataList;
	class NctiDisplayObjectList;
	class NctiSelectionDataNewList;
	class NctiSelectionFilter;
	class NctiSelectionDataHash;
	class NctiBooleanArray;
	class NctiDisplayViewObject;
	class NctiBaseView;
	class NctiSelectionDataHolder;
	class NctiDisplayObject;
	class NctiPosition;
	class NctiUnitVector;
	/**
	* @brief select manager
	* @details manager selection data
	* @see NctiManager
	*/
	class DECL_NCTI NctiSelectionManager : public NctiManager
	{
		NCTI_MANAGER_FUNCTIONS(NctiSelectionManager)
	public:
		virtual ~NctiSelectionManager();
		/**
	   * @brief set selection data to selection manager
	   * @param[in] i_pSelData, selection data 
	   * @param[in] i_eMouseEvent, the selection type
	   * @param[in] i_bNotifySelectionDataChanged, data selection changed
	   * @return Ncti_Boolean
	   */
		Ncti_Boolean SetSelected(NctiSelectionData* i_pSelData,
			EnumNctiMouseEventForSelection i_eMouseEvent = NCTI_SELECT_NO_MOUSE, 
			Ncti_Boolean i_bNotifySelectionDataChanged = true);
		/**
	   * @brief set selection data list to selection manager
	   * @param[in] i_cSelectDataList, selection data list
	   * @param[in] i_eMouseEvent, the selection type
	   * @param[in] i_bNotifySelectionDataChanged, data selection changed
	   * @return Ncti_Boolean
	   */
		Ncti_Boolean SetSelected(NctiSelectionDataList& i_cSelectDataList,
			EnumNctiMouseEventForSelection i_eMouseEvent = NCTI_SELECT_NO_MOUSE, 
			Ncti_Boolean i_bNotifySelectionDataChanged = true);
		/**
	   * @brief internal used
	   */
        Ncti_Boolean AssignSelected(NctiSelectionDataList& i_cSelectDataList,
            Ncti_Boolean i_bNotifySelectionDataChanged = true);
		/**
	   * @brief reset selection manager
	   *  @param[in] i_bNotifySelectionDataChanged, data selection changed
	   */
        void ResetSelection(Ncti_Boolean i_bNotifySelectionDataChanged = true);
		/**
	   * @brief add selection data to selection manager
	   * @param[in] i_pDoSelected, original or instance
	   * @return Ncti_Boolean
	   */
        Ncti_Boolean AddSelected(NctiDisplayObject* i_pDoSelected);
		/**
	   * @brief set key status of selection manager
	   * @param[in] i_iKeyStatus, iKeyStatus |= NCTI_KEY_SHIFT,NCTI_KEY_ALT,NCTI_KEY_CTRL
	   */
		void SetKeyStatus(const ModifierKeys& i_iKeyStatus);
		/**
	   * @brief set selection filter of selection manager
	   * @param[in] i_pSelectionFilter
	   * @param[in] i_iPickType,  NCTI_PICK_FACE | NCTI_PICK_EDGE | NCTI_PICK_VERTEX
	   */
        void SetSelectionFilter(NctiSelectionFilter* i_pSelectionFilter, NctiPickType i_iPickType);
		/**
	   * @brief get selection data list of selection manager
	   * @param[out] o_cSelDataList
	   * @param[in] i_cpDataType, IsTypeName
	   */
		void GetSelected(NctiSelectionDataList& o_cSelDataList, const char* i_cpDataType = nullptr);
		/**
	   * @brief get select manager by NctiBaseView
	   * @param[in] i_pBaseView, the render view
	   * @return NctiSelectionManager
	   */
		static NctiSelectionManager* GetSelectionManager(NctiBaseView* i_pBaseView);
		/**
	   * @brief get select manager by NctiBaseModel
	   * @param[in] i_pBaseModel, the document base model, only one in a document
	   * @return NctiSelectionManager
	   */
		static NctiSelectionManager* GetSelectionManager(NctiBaseModel* i_pBaseModel);
		/**
	   * @brief get select manager by NctiManager
	   * @param[in] i_pManager, other manager
	   * @return NctiSelectionManager
	   */
		static NctiSelectionManager* GetSelectionManager(NctiManager* i_pManager);
		/**
	   * @brief internal used
	   */
		Ncti_Integer GetNewSelectID();
		/**
	   * @brief internal used
	   */
        Ncti_Boolean add_selected(NctiSelectionData* i_pSelectionData);
		/**
	   * @brief internal used
	   */
		void ProcessSelectNone();
		/**
	   * @brief internal used
	   */
		void NotifyTermination() override;
	protected:
		/**
	   * @brief internal used
	   */
        Ncti_Boolean FindSelectedData(NctiSelectionData* i_pSelData, NctiSelectionData*& o_pSelDataFound);
		/**
	   * @brief internal used
	   */
		Ncti_Boolean apply_selection_filter(NctiSelectionDataList& i_cSelectionDataList, 
			EnumNctiSelectionFilterMode i_eFilterMode, 
			NctiSelectionDataList& o_cFilteredSelectionDataList, 
			NctiSelectionDataNewList& o_cNewSelectionDataList);
		/**
	   * @brief internal used
	   */
		void reset_selection_data();
		/**
	   * @brief internal used
	   */
		Ncti_Boolean remove_or_add_select_data(NctiSelectionData* i_pSelData);
		/**
	   * @brief internal used
	   */
		Ncti_Boolean remove_selected_data(NctiSelectionData* i_pSelData);
		/**
	   * @brief internal used
	   */
		void remove_or_add_select_data_list(NctiSelectionDataList& i_cSelectionDataList);
	private:
		NctiSelectionFilter* m_pSelectionFilter;
		NctiSelectionFilter* m_pDefaultSelectionFilter;
		NctiSelectionDataHash* m_pSelectionDataHash;

        ModifierKeys	m_iKeyStatus;
		NctiPickType m_iPickType;
		Ncti_Integer m_iImanagerSelectID;
	};
}
DECL_NCTI NCTI_MANAGER_TYPEDEF(NctiSelectionManager)
#endif
