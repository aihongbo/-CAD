#ifndef NctiFileTask_H
#define NctiFileTask_H
#include "NctiThreadTask.h"
#include "ncti.h"
#include <string>
namespace NCTI
{
	class NctiDisplayDocElement;
	class NctiBaseView;
	class NctiDisplayObject;
	class NctiDisplayObjectList;
	class NctiFileInterface;
	class NctiDocViewManager;
	/**
	* @brief internal used
	*/
	class NctiFileTask : public NctiThreadTask
	{
	public:
		NctiFileTask();
		virtual ~NctiFileTask();
	public:
		enum TaskType
		{
			Nothing,
			save_file,
			call_back,
			update_view_for_add_display_object,
			rename_segment,
			fix_pointer,
			read_file,
			read_file_sub_documents
		};
	public:
		virtual NctiThreadAny run();
	private:
		TaskType m_Type;
		NctiDisplayDocElement* m_DisplayDocElement;
		Ncti_Char* m_cpBaseDirectoryPath;
		std::vector<NctiDisplayObject*> m_DisplayObjectVec;
		EnumNctiDoCallbackType m_DoCallbackType;
		NctiBaseView* m_BaseView;
		std::vector<NctiDisplayObject*> m_cTargetInsList;
		void* m_window_handle;
		Ncti_Integer m_w;
		Ncti_Integer m_h;
		NctiFileInterface* m_FileInterface;
		Ncti_Char* m_ReadFile;
		NctiDocViewManager* m_pDocView;
		NctiDisplayObjectList* m_pcListDocProxy;
		NctiDisplayObjectList* m_pAllDocElementListHelp;
	public:
		void save_one_file(NctiDisplayDocElement* i_pDisplayDocElement, const char* i_cpBaseDirectoryPath);
		void call_back_file_data(
			const std::vector<NctiDisplayObject*>& i_DisplayObjectVec,
			NctiBaseView* i_pBaseView, 
			EnumNctiDoCallbackType i_CallbackType);
		void supdate_view_for_add_display_object_data(
			const std::vector<NctiDisplayObject*>& i_cTargetInsList,
			NctiDisplayDocElement* i_pDoOwner, 
			const std::vector<NctiDisplayObject*>& i_DisplayObjectVec,
			NctiBaseView* i_pBaseView);
		void rename_segment_data(const std::vector<NctiDisplayObject*>& i_DisplayObjectVec);
		void fix_pointer_data(const std::vector<NctiDisplayObject*>& i_DisplayObjectVec, NctiFileInterface* i_pFileInterface);
		void read_one_file(const std::string& i_file, const char* i_cpBaseDirectoryPath, NctiDocViewManager* i_pDocView);
		NctiDisplayDocElement* GetDisplayDocElement() {
			return m_DisplayDocElement;
		}
		const std::vector<NctiDisplayObject*>& GetDisplayObjectVec() { return m_DisplayObjectVec; }
		const Ncti_Char* GetReadFile() { return m_ReadFile; }

		void restore_sub_documents(NctiDisplayObjectList* i_pcListDocProxy, NctiDisplayObjectList* i_pAllDocElementListHelp, NctiDocViewManager* i_pDocView);
	public:
		static void call_back_file_task(NctiDisplayObjectList* i_pDisplayObjectList,
			NctiBaseView* i_pBaseView,
			EnumNctiDoCallbackType i_CallbackType);
		static void update_view_for_add_display_object_task(
			NctiDisplayDocElement* i_pDoOwner, 
			NctiDisplayObjectList* i_pChildList);
		static void fix_pointer_task(NctiDisplayObjectList* i_pChildList, NctiFileInterface* i_pFileInterface);
		
	};
}
#endif
