#ifndef NctiDebug_H
#define NctiDebug_H
#include "ncti_base.h"

#if defined(_MSC_VER) || defined(__MINGW32__)
// Windows (MSVC, MinGW)
struct _iobuf;
typedef struct _iobuf FILE;

#elif defined(__ANDROID__)
// Android NDK - 直接使用系统头文件
#include <stdio.h>
#elif defined(__GNUC__) || defined(__clang__)
// GCC, Clang (Linux, macOS, ����Unix-like)
struct _IO_FILE;
typedef struct _IO_FILE FILE;
#else
#include <stdio.h>
#endif
namespace NCTI
{
	/**
	* @brief use to debug some problems,it can output the console
	*/
	class DECL_NCTI_BASE NctiDebug
	{
	public:

		enum EnumNctiFileOpenMode
		{
			NCTI_FILE_MODE_READ
			, NCTI_FILE_MODE_WRITE
			, NCTI_FILE_MODE_APPEND
			, NCTI_FILE_MODE_APPEND_PLUS
			, NCTI_FILE_MODE_DO_NOT_OPEN
		};
		// Log Level
		enum LogLevel {
			LOG_INFO = 0,
			LOG_WARN,
			LOG_ERROR,
			LOG_FATAL
		};

        NctiDebug(const char* i_cpFullFileName, EnumNctiFileOpenMode i_eMode);
		~NctiDebug();

		/**
	   * @brief get the log file point 
	   * @return FILE*
	   */
		FILE* GetFile();
		/**
	   * @brief get the log file path
	   * @return const char*
	   */
		const char* GetFilePath();
		/**
	   * @brief write the log 
	   */
		void write(const char* i_chValue, NctiDebug::LogLevel =NctiDebug::LogLevel::LOG_INFO);

	public:
		/**
	   * @brief debug some information to console directly
	   * @param[in] i_ouputInfor
       * @param[in] i_level LogLevel
	   */
		static void debug(const char* i_ouputInfor, LogLevel i_level = LOG_INFO);
		/**
	   * @brief debug some information to console by format
	   * @param[in] _DstBuf
	   * @param[in] _Format
	   */
		static void debug(char* _DstBuf, const char* _Format, ...);

		/**
	   * @brief debug some information to console by format
	   * @param[in] _Format
	   */
		static void debugf(const char* _Format, ...);

        /**
       * @brief debug some information to console by format in level
       * @param[in] _Format
       * @param[in] i_level LogLevel
       */
        static void debuglf(LogLevel i_level,const char* _Format, ...);

	protected:
		FILE* m_fp;
		char* m_cpzFilePath;
		EnumNctiFileOpenMode m_Model;

	};
}
#define NctiPrintf(format, ...) NCTI::NctiDebug::debugf(format, ##__VA_ARGS__)
#endif
