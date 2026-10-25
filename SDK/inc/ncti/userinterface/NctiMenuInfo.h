#ifndef NctiMenuInfo_H
#define NctiMenuInfo_H
#include "ncti.h"
namespace NCTI
{
	/**
	* @brief menu item value
	* @see NctiUserPopupMenu
	*/
	class DECL_NCTI NctiMenuInfo : public NCTI_BASE_CLASS
	{
	public:
		enum MenuItemState
		{
			MIS_NoneFlag = 0,
			MIS_Disable = 0x1,
			MIS_Invisible = 0x2,
			MIS_DisableAndInvisible = MIS_Disable | MIS_Invisible,
		};
		//static const Ncti_Integer virtualRoot = -1;
	public:
		NctiMenuInfo(EnumNctiMenuType i_eType,
			const char* i_cpString,
			Ncti_Integer i_iValue,
			const char* i_cpImage = nullptr,
			MenuItemState menuState = MIS_NoneFlag,
			Ncti_Integer parentValue = -1);
		virtual ~NctiMenuInfo();
		/**
	   * @brief menu type
	   * @return EnumNctiMenuType
	   */
		EnumNctiMenuType GetMenuType();
		/**
	   * @brief menu name
	   * @return const char*
	   */
		const char* GetMenuText();
		/**
	   * @brief menu value
	   * @return Ncti_Integer
	   */
		Ncti_Integer GetMenuValue();
		/**
	   * @brief menu image
	   * @return const char*
	   */
		const char* GetMenuImage();
		/**
	   * @brief parent value
	   * @return Ncti_Integer
	   */
		Ncti_Integer GetParentValue();
		/**
	   * @brief is visible
	   * @return Ncti_Boolean
	   */
		Ncti_Boolean IsVisible();
		/**
	   * @brief is enable
	   * @return Ncti_Boolean
	   */
		Ncti_Boolean IsEnable();
	private:
		EnumNctiMenuType	m_eMenuType;
		char*				m_cpMenuString;
		Ncti_Integer		m_iMenuValue;
		char*				m_cpMenuImage;
		Ncti_Integer		m_parentValue;
		MenuItemState		m_menuState;
	};
}
#endif // !NctiMenuInfo_H
