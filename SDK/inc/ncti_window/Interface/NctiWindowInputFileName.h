#ifndef NctiWindowInputFileName_H
#define NctiWindowInputFileName_H
#include "NctiInputFileName.h"
#include "ncti_dcl_window.h"
namespace NCTI
{
	/**
   * @brief Implement the function of input file name interface function
   * @see NctiInputFileName
   */
	class DECL_NCTI_WINDOW NctiWindowInputFileName : public NctiInputFileName
	{
	public:
		NctiWindowInputFileName();
		virtual~NctiWindowInputFileName();
	public:
		/**
	   * @brief get temp file path in a system
	   * @param[out] o_cpTempFileName
	   * @return EnumNctiResult
	   */
		virtual EnumNctiResult GetTempFile(char*& o_cpTempFileName);
		/**
	   * @brief get file size, same to NctiFile::get_file_size
	   * @param[in] o_cpFileFullPath
	   * @return the file size
	   */
		virtual Ncti_UInteger GetFileSize(char*& o_cpFileFullPath);
	private:
		std::vector<char*> m_TempPointVec;
	};
}
#endif
