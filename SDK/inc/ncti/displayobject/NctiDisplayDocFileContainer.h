#ifndef NctiDisplayDocFileContainer_H
#define NctiDisplayDocFileContainer_H
#include "NctiDisplayDocElement.h"
namespace NCTI
{
	/**
	* @brief Doc File Container class
	* @details Base Class of Core or Mesh Container.Such as OCC Container
	* @see NctiDisplayDocElement
	*/
	class DECL_NCTI NctiDisplayDocFileContainer : public NctiDisplayDocElement
	{
		NCTI_DISPLAYOBJECT_FUNCTIONS(NctiDisplayDocFileContainer)
	public:
		~NctiDisplayDocFileContainer();
		virtual void Init();
	public:
		virtual EnumNctiResult ActivateData();
		virtual EnumNctiResult save_temp_file(NctiFileInterface* i_pFI);
		virtual EnumNctiResult restore_temp_file(NctiFileInterface* i_pFI);
	protected:
		char* m_pwsTempFileName;		// No save data, don't need to delete.
		FILE* m_File;
	public:
		void SetFilePoint(FILE* fi);
		void SetFormat(const char* format);
		const char* GetFormat() { return m_Format; }
	public:
		void ReadFileByFileName(const char* chFileName);
		FILE* GetFilePoint() { return m_File; }
		const char* GetTempFile() { return m_pwsTempFileName; }
	protected:
		char* m_Format;
	public:
		void SetDetachModel(const Ncti_Boolean& i_DetachModel);
	private:
		void SetModelPath(const char* i_modelPath);//no backup
	protected:
		char* m_modelFileName;//if m_detachModel is true,m_modelPath will not nullptr;
		Ncti_Boolean m_detachModel;
		
	private:
		NCTI_READ_AND_WRITE_VERSION_FUN(1)
		NCTI_READ_AND_WRITE_VERSION_FUN(2)
	};
}

#endif

