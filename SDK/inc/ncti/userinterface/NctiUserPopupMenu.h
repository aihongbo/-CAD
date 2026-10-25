#ifndef NctiUserPopupMenu_H
#define NctiUserPopupMenu_H
#include "ncti.h"
#include "NctiMenuInfo.h"

namespace NCTI
{
	class NctiUserInterfaceManager;
	class NctiMenuInfo;
	/**
	* @brief user Popup menu
	* @details help use to create Popup menu
	* @see NctiMenuInfo
	*/
	class DECL_NCTI NctiUserPopupMenu : public NCTI_BASE_CLASS
	{
	public:
		NctiUserPopupMenu();
		virtual ~NctiUserPopupMenu();
	public:
		/**
	   * @brief init the menu item num
	   */
		void Init(Ncti_Integer i_iNumItem);
		/**
	   * @brief init the menu item
	   */
		void Init();
		/**
	   * @brief create menu item
	   * @param[in] i_eType, EnumNctiMenuType
	   * @param[in] i_cpMenuString, menu name
	   * @param[in] i_cpImage, icon
	   * @param[in] menuState, MenuItemState
	   * @param[in] parentValue, menu father
	   * @return EnumNctiResult
	   */
		EnumNctiResult AddMenuItem(EnumNctiMenuType i_eType,
			const char* i_cpMenuString,
			Ncti_Integer i_iValue,
			const char* i_cpImage = nullptr,
			NctiMenuInfo::MenuItemState menuState = NctiMenuInfo::MIS_NoneFlag,
			Ncti_Integer parentValue = -1);
		/**
	   * @brief set the menu item value
	   */
		void SetValue(Ncti_Integer i_iValue);
		/**
	   * @brief get the menu item value
	   */
		Ncti_Integer GetValue();
		/**
	   * @brief check if the menu is valid
	   * @param[in] i_cpMenuString, menu name
	   * @return Ncti_Boolean
	   */
		virtual Ncti_Boolean IsMenuValid(const char* i_psMenuName); 
		/**
	   * @brief Execute menu
	   * @details need to implement, override
	   */
		virtual void Execute();
		/**
	   * @brief Run menu
	   * @details need to implement, override
	   */
		virtual void RunMenu(const char* i_psMenuName);
		/**
	   * @brief get the menu item size
	   * @return Ncti_Integer
	   */
		Ncti_Integer GetNumItem() { return m_iNumItem; };
	protected:
		/**
	   * @brief internal used
	   */
		void delete_data();
		/**
	   * @brief internal used
	   */
		void expand(Ncti_Integer i_iNewSize);
	protected:
		Ncti_Integer		m_iSize;
		Ncti_Integer		m_iNumItem;
		NctiMenuInfo** m_paMenuInfo;
	private:
		Ncti_Integer		m_iValue;	// MenuID currently clicked
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
	};
}
#endif // !NctiUserPopupMenu_H
