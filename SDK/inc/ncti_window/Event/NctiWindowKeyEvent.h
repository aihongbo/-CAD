#ifndef NctiWindowKeyEvent_H
#define NctiWindowKeyEvent_H
#include "NctiWindowEvent.h"
#include "ncti_event.h"
#include <vector>
namespace NCTI
{
	/**
   * @brief window key event
   * @see NctiWindowEvent
   */
	class DECL_NCTI_WINDOW NctiWindowKeyEvent : public NctiWindowEvent
	{
	public:
		/**
	   * @brief add keyboard code
	   * @param[in] i_KeyboardCode
	   */
		void AddKeyboardCode(KeyboardCode i_KeyboardCode);
		/**
	   * @brief remove keyboard code
	   * @param[in] i_KeyboardCode
	   */
		void RemoveKeyboardCode(KeyboardCode i_KeyboardCode);
		/**
	   * @brief get all  keyboard code
	   * @param[out] o_KeyboardCodeVec
	   */
		void GetKeyboardCodeVec(std::vector<KeyboardCode>& o_KeyboardCodeVec)const;
		/**
	   * @brief get first keyboard code
	   * @return KeyboardCode
	   */
		KeyboardCode GetFirstKeyboardCode()const;
		/**
	   * @brief determine whether it is character
	   * @return Ncti_Boolean
	   */
		Ncti_Boolean IsCharacter();

	private:
		std::vector<KeyboardCode> m_KeyboardCodeVec;
	};
}
#endif
