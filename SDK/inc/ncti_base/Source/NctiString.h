#ifndef NctiString_H
#define NctiString_H
#include "ncti_dcl_base.h"
#include "ncti_base.h"
#include <vector>
#include <string>
namespace NCTI
{
	/**
	* @brief deal some string problems
	*/
	class DECL_NCTI_BASE NctiString
	{
	public:
		NctiString();
		~NctiString();
	public:
		/**
	   * @brief split the string by char
	   * @param[in] i_str,
	   * @param[in] i_delim, a char
	   * @return std::vector<std::string>
	   */
		static std::vector<std::string> stringSplit(const std::string& i_str, char i_delim);
		/**
	   * @brief convert int to string
	   * @param[in] i_num,
	   * @return std::string
	   */
		static std::string int_to_string(Ncti_Integer i_num);
		/**
	   * @brief convert float to string
	   * @param[in] i_f,
	   * @param[in] i_num, decimal place
	   * @return std::string
	   */
		static std::string float_to_string(Ncti_Float i_f, Ncti_Integer i_num = -1);
		/**
	   * @brief convert doubl to string
	   * @param[in] i_f,
	   * @param[in] i_num, decimal place
	   * @return std::string
	   */
		static std::string double_to_string(Ncti_Double i_d, Ncti_Integer i_num = -1);
		/**
	   * @brief convert bool to string
	   * @param[in] i_boo,
	   * @return std::string
	   */
		static std::string bool_to_string(Ncti_Boolean i_boo);
		/**
	   * @brief convert string to bool
	   * @param[in] i_str_boo,
	   * @return Ncti_Boolean
	   */
		static Ncti_Boolean string_to_bool(std::string i_str_boo);
		/**
	   * @brief search string by right
	   * @param[in] i_str,
	   * @param[in] i_num,
	   * @return std::string
	   */
		static std::string right(const std::string& i_str, Ncti_UInteger i_num);
		/**
	   * @brief search string by mid
	   * @param[in] i_str,
	   * @param[in] i_s,
	   * param[in] i_len,
	   * @return std::string
	   */
		static std::string mid(const std::string& i_str, Ncti_Integer i_s, Ncti_Integer i_len);
		/**
	   * @brief convert string to wstring
	   * @param[in] i_str,
	   * @return std::wstring
	   */
		static std::wstring str_to_wstr(const std::string& i_str);
		/**
	   * @brief convert wstring to string
	   * @param[in] i_str,
	   * @return std::string
	   */
		static std::string wstr_to_str(const std::wstring& i_str);
		/**
	   * @brief convert wstring to upper
	   * @param[in] i_str,
	   * @return std::string
	   */
		static std::string str_to_upper(const std::string& i_str);
		/**
	   * @brief convert wstring to lower
	   * @param[in] i_str,
	   * @return std::string
	   */
		static std::string str_to_lower(const std::string& i_str);
		/**
	   * @brief determine whether two strings are the same
	   * @param[in] i_str1,
	   * @param[in] i_str2,
	   * @param[in] i_CaseInsensitive, ignore case if it is true
	   * @return Ncti_Boolean
	   */
		static Ncti_Boolean same(const std::string& i_str1, const std::string& i_str2, Ncti_Boolean i_CaseInsensitive = true);
		/**
	   * @brief determine whether two chars are the same
	   * @param[in] i_cstr1,
	   * @param[in] i_cstr2,
	   * @param[in] i_CaseInsensitive, ignore case if it is true
	   * @return Ncti_Boolean
	   */
		static Ncti_Boolean same(const char* i_cstr1, const char* i_cstr2, Ncti_Boolean i_CaseInsensitive = true);
		/**
	   * @brief format the string 
	   * @param[in] _DstBuf,
	   * @param[in] _Format,
	   * @return Ncti_Integer
	   */
		static Ncti_Integer LocaleSprintf(char* _DstBuf, const char* _Format, ...);
		/**
	   * @brief determine whether the i_str2 is in the i_str1
	   * @param[in] i_str1,
	   * @param[in] i_str2,
	   * @param[in] i_CaseInsensitive, ignore case if it is true
	   * @return Ncti_Boolean
	   */
		static Ncti_Boolean find(const std::string& i_str1, const std::string& i_str2, Ncti_Boolean i_CaseInsensitive = true);
		/**
	   * @brief convert uft8 to wstring
	   * @param[in] i_UTF8,
	   * @return std::wstring
	   */
		static std::wstring utf8_to_wstr(const char* i_UTF8);
		/**
	   * @brief convert wstring to utf8
	   * @param[in] i_wStr,
	   * @return std::string
	   */
		static std::string wstr_to_utf8(const std::wstring& i_wStr);
		/**
	   * @brief determine whether the i_str is end with i_end
	   * @param[in] i_str,
	   * @param[in] i_end,
	   * @return Ncti_Boolean
	   */
		static Ncti_Boolean ends_with(const std::string& i_str, const std::string& i_end);
		/**
	   * @brief determine whether the i_str is start with i_start
	   * @param[in] i_str,
	   * @param[in] i_start,
	   * @return Ncti_Boolean
	   */
		static Ncti_Boolean starts_with(const std::string& i_str, const std::string& i_start);
		/**
	   * @brief internal use
	   */
		static std::string join(const std::string& i_str, const std::vector<std::string>& i_StrVec);
		/**
	   * @brief internal use
	   */
		static std::string strip(const std::string& i_str);
		/**
	   * @brief internal use
	   */
		static std::string splitByFirst(const std::string& i_split, const std::string& i_InputStr);
		/**
	   * @brief internal use
	   */
		static std::string rstrip(const std::string& i_str);
		/**
	   * @brief internal use
	   */
		static Ncti_Boolean is_digit(const std::string& i_str);
		/**
	   * @brief internal use
	   */
		static std::string expandTabs(const std::string& str, Ncti_Size tabSize = 8);
		/**
	   * @brief internal use
	   */
		static std::string replaceDoubleBackslashWithSlash(const std::string& i_input);
		/**
	   * @brief internal use
	   */
		static bool get_char_by_name_id(Ncti_Char* i_result, const Ncti_Char* i_name, const Ncti_Char* i_mid, Ncti_Integer i_id, const Ncti_Char* i_include, Ncti_Integer len);
	};
}
#endif
