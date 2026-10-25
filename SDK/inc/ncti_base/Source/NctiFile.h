#ifndef NctiFile_H
#define NctiFile_H
#include "ncti_dcl_base.h"
#include "ncti_base.h"
#include <string>
#include <vector>
namespace NCTI
{
	/**
	* @brief offer some function to do some file problems, support windows and linux, need utf8 string
	*/
	class DECL_NCTI_BASE NctiFile
	{
	public:
		/**
	   * @brief get the file point of file name
	   * @param[in] i_UTF8Filename, need utf8 string
	   * @param[in] i_mode, open mode,such as "rb", "wb"
	   * @return FILE*
	   */
		static FILE* get_file_point(const char* i_UTF8Filename, const char* i_mode);
		/**
	   * @brief copy a new file from old 
	   * @param[in] i_filename, old file path
	   * @param[in] i_newfilename,new file path
	   * @param[in] i_newfilename, whether it is need to remove the old file
	   * @return Ncti_Boolean
	   */
		static Ncti_Boolean copy(const char* i_filename, const char* i_newfilename, Ncti_Boolean i_remove_old_file = true);
		/**
	   * @brief get the file path of file name, see NctiBaseUtility::FindFileNameAndDirectory
	   * @param[in] i_filename, file name
	   * @return std::string
	   */
		static std::string get_file_path(const char* i_filename);
		/**
	   * @brief determine whether the file is exists
	   * @param[in] i_filename, file name
	   * @return Ncti_Boolean
	   */
		static Ncti_Boolean exists(const char* i_filename);
		/**
	   * @brief get the file name with suffix of file name, see NctiBaseUtility::FindFileNameAndDirectory
	   * @param[in] i_filename, file name
	   * @return std::string
	   */
		static std::string get_file_name(const char* i_filename);
		/**
	   * @brief get the file suffix of file name, see NctiBaseUtility::FindFileNameAndDirectory
	   * @param[in] i_filename, file name
	   * @return std::string
	   */
		static std::string get_file_suffix(const char* i_filename);
		/**
	   * @brief get the file size of file name
	   * @param[in] i_filename, file name
	   * @return Ncti_UInteger
	   */
		static Ncti_UInteger get_file_size(const char* i_filename);
		/**
	   * @brief get the file size of file name by file point
	   * @param[in] i_filename, file name
	   * @return Ncti_UInteger
	   */
		static Ncti_UInteger get_file_size(FILE* i_file);
		/**
	   * @brief search all the file names by path
	   * @param[in] i_path, a path
	   * @param[in] o_files, return the file path list
	   * @return Ncti_Boolean
	   */
		static Ncti_Boolean get_Path_Files(const std::string& i_path, std::vector<std::string>& o_files);
		/**
	   * @brief rename the file
	   * @param[in] i_UTF8OldFilename, old
	   * @param[in] i_UTF8NewFilename, new
	   * @return Ncti_Boolean
	   */
		static Ncti_Boolean rename(const char* i_UTF8OldFilename, const char* i_UTF8NewFilename);
		/**
	   * @brief delete the file from system
	   * @param[in] i_UTF8Filename
	   * @return Ncti_Boolean
	   */
		static Ncti_Boolean remove(const char* i_UTF8Filename);
		/**
	   * @brief get the file point by reading again
	   * @param[in] i_UTF8Filename
	   * @param[in] i_mode
	   * @param[in] i_OldFile
	   * @return FILE*
	   */
		static FILE* re_get_file_point(const char* i_UTF8Filename, const char* i_mode, FILE* i_OldFile);

		/**
	   * @brief get the file size
	   * @param[in] fp
	   * @param[out] size
	   * @return Ncti_Boolean
	   */
		static Ncti_Boolean get_file_size(FILE* fp, Ncti_Size& size);
	};
}
#endif
