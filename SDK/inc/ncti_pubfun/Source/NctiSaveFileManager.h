#ifndef NctiSaveFileManager_H
#define NctiSaveFileManager_H
#include "dcl_ncti_pubfun.h"
#include "ncti_base.h"
#include <string>
#include <map>
#include <unordered_map>
#include <queue>
#include "NctiMutex.h"
#include <thread>
#include <atomic>
namespace NCTI
{
	struct NCTI_SaveFileData
	{
	public:
		NCTI_SaveFileData() :m_auto_path(""), m_manuanl_path("") {}
		NCTI_SaveFileData(const std::string& i_autoPath, const std::string& i_manualPath):m_auto_path(i_autoPath), m_manuanl_path(i_manualPath) {}

		void SetAutoPath(const std::string& i_Path) { m_auto_path = i_Path; }
		std::string GetAutoPath() { return m_auto_path; }

		void SetManualPath(const std::string& i_Path) { m_manuanl_path = i_Path; }
		std::string GetManualPath() { return m_manuanl_path; }

		Ncti_Boolean IsValid() { 
			if ((!m_auto_path.empty()) && (!m_manuanl_path.empty()))
				return true;
			else
				return false;
		}
	private:
		std::string m_auto_path;
		std::string m_manuanl_path;
	};

	class NctiDocument;
	class DECL_NCTI_PUBFUN NctiSaveFileManager
	{
	public:
		NctiSaveFileManager();
		virtual ~NctiSaveFileManager();
	public:
		static NctiSaveFileManager* instance() { return m_instance; }
		void Init(Ncti_Boolean i_bAutoSave,
			const std::string& i_saveFolder,
			Ncti_Integer i_saveTime);
	public:
		//是否开启自动保存
		void SetAutoSave(Ncti_Boolean i_bSave);
		Ncti_Boolean GetAutoSave();
		//自动保存时间间隔
		void SetAutoSaveTime(Ncti_Integer i_SecondsGap);
		Ncti_Integer GetAutoSaveTime();
		//自动保存文件夹
		void SetAutoSaveFileFolder(const std::string& i_strFolder);
		std::string GetAutoSaveFileFolder();

		//增加文档到保存队列中，返回新加文档的路径数据
		NCTI_SaveFileData  AddDocument(NctiDocument* pDoc, const std::string& strPath);

		//获取文档保存路径
		NCTI_SaveFileData GetDocument(NctiDocument* pDoc);
		//删除文档在自动保存队列中
		Ncti_Boolean DelDocument(NctiDocument* pDoc);

		void StopThread();
		void StartThread();
	private:
		static NctiSaveFileManager* m_instance;

		Ncti_Boolean m_is_auto_save;//是否自动保存
		Ncti_Long m_save_time;//保存时间间隔
		std::string m_auto_folder;//自动保存文件夹
		std::map<NctiDocument*, NCTI_SaveFileData> m_file_pathVec;//各个文档自动保存路径
		std::atomic_bool m_run;//是否正在运行
		void AutoSaveFile();
		std::thread m_thread;//自动保存的线程
        NctiMutex m_mutex;
	};
}
#endif
