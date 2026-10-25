#ifndef NctiInputFileName_H
#define NctiInputFileName_H
#include "ncti.h"
#include "NctiMutex.h" 
#include <vector>
namespace NCTI
{
	class NctiUserInterfaceManager;
	/**
	* @brief input file user interface
	* @see NctiUserInterfaceManager
	*/
	class DECL_NCTI NctiInputFileName : public NCTI_BASE_CLASS
	{
	public:
		NctiInputFileName();
		virtual~NctiInputFileName();
	public:
		/**
	   * @brief get temp file path in a system
	   * @param[out] o_cpTempFileName
	   * @return EnumNctiResult
	   */
		virtual EnumNctiResult GetTempFile(char*& o_cpTempFileName);
		/**
	   * @brief get file size
	   * @param[in] o_cpFileFullPath
	   * @return the file size
	   */
		virtual Ncti_UInteger GetFileSize(char*& o_cpFileFullPath);
	public:
		/**
	   * @brief internal used
	   */
		void SetUserInterfaceManager(NctiUserInterfaceManager* i_pUserInterfaceManager) { m_UserInterfaceManager = i_pUserInterfaceManager; }
		/**
	   * @brief internal used
	   * @return NctiUserInterfaceManager
	   */
		NctiUserInterfaceManager* GetUserInterfaceManager() { return m_UserInterfaceManager; }
	private:
		/**
	   * @brief internal used
	   */
		void AddPointVec(char* i_temp);
	protected:
		NctiUserInterfaceManager* m_UserInterfaceManager;
	private:
		std::vector<char*> m_PointVec;
        NctiMutex m_mutex;
	};
}
#endif // !NctiInputFileName_H
