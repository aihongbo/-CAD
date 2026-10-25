#ifndef NctiFileVersionDocElement_H
#define NctiFileVersionDocElement_H
#include "NctiDisplayObject.h"
#include <vector>
namespace NCTI
{
	struct NctiFileReadInfoVecTree
	{
		Ncti_Integer m_Type;
		std::vector<Ncti_Integer> m_FIVersionVec;
		std::vector<NctiFileReadInfoVecTree*> m_Childs;
		NctiFileReadInfoVecTree(Ncti_Integer type)
		{
			m_Type = type;
		}
	};
	class DECL_NCTI NctiFileReadInfo
	{
	public:
		NctiFileReadInfo() { m_ObjectType = nullptr; }
		~NctiFileReadInfo() {}
	public:
		char* m_ObjectType;
		std::vector<Ncti_Integer> m_VersionVec;
		std::vector<std::vector<Ncti_Integer>> m_FIVecVec;
		std::vector<NctiFileReadInfoVecTree*> m_FIHelpVec;
	};
	/**
	* @brief internal used
	*/
	class DECL_NCTI NctiFileVersionDocElement : public NctiDisplayObject
	{
		NCTI_DISPLAYOBJECT_FUNCTIONS(NctiFileVersionDocElement)
		NCTI_DOC_FILE_SUPPORT
	public:
		virtual ~NctiFileVersionDocElement();
#pragma region Virtual Inheritance Function
		//************************************
		// Method:    Init
		// FullName:  NCTI::NctiFileVersionDocElement::Init
		// Access:    virtual public 
		// Returns:   void
		// Qualifier: Initialize when create object pointed.
		//************************************
		virtual void Init();
#pragma endregion
	public:
		//no history.
		void SetFileNameInfo(const std::vector<char*>& i_FileNameVec, const std::vector<char*>& i_FileMD5NameVec);
		const char* GetFileMD5NameVec(const char* i_cpFileName);
		const char* GetFirstMD5Name();
		const char* GetFilePath();
		void SetFilePathNoHistoty(const char* i_cpFilepath);
		void AddFileModifyRecordVec(const char* i_cpSoftinfo);
		//don't delete the vec.
		void GetFileModifyRecordVec(std::vector<char*>& o_FileModifyRecordVec);
		//don't delete the vec.
		void GetFileNameInfo(std::vector<char*>& o_FileNameVec, std::vector<char*>& o_FileMD5NameVec);
	public:
		Ncti_Boolean IsHasFileReadInfo(const char* i_cpTypeObject);
		void AddFileReadInfo(NctiFileReadInfo* pFileReadInfo);
		void ReadDataByRecordVersion(const char* i_cpObjectType, Ncti_Integer i_version, NctiFileInterface* i_pFileInterface);
		void ReadDataByRecordVersion(NctiFileReadInfoVecTree* i_pFileReadInfoVecTree, NctiFileInterface* i_pFileInterface);
		void WriteSDFileReadInfoVecTree(NctiFileReadInfoVecTree* i_pFileReadInfoVecTree, NctiFileInterface*& i_pFileInterface);
		void ReadSDFileReadInfoVecTree(NctiFileReadInfoVecTree*& o_pFileReadInfoVecTree, NctiFileInterface*& i_pFileInterface);
		void ReleaseDFileReadInfoVecTree(NctiFileReadInfoVecTree* i_pFileReadInfoVecTree);
#pragma region Public Function
		//************************************
		// Method:    GetNewObjectId
		// FullName:  NCTI::NctiFileVersionDocElement::GetNewObjectId
		// Access:    public 
		// Returns:   Ncti_Integer
		// Qualifier: Get a new object id,and MaxID will plus one.
		//************************************
		Ncti_Size GetNewObjectId();
#pragma endregion
#pragma region protected Attribute Save Version 1
	private:
		char* m_psFilePath;
		std::vector<NctiFileReadInfo*> m_ObjectTypeVec;
		std::vector<NctiFileReadInfo*> m_ObjectTypeDLLVec;
		std::vector<char*> m_FileNameVec;
		std::vector<char*> m_FileMD5NameVec;
		static Ncti_Integer m_SoftInfoNum;
		std::vector<char*> m_FileModifyRecordVec;
#pragma endregion
#pragma region protected Attribute Save Version 2
	private:
		Ncti_Size m_MaxId;
#pragma endregion
#pragma region Internal Private Function
	private:
		void ReadOneVersion(NctiFileInterface* i_pFI);
		void WriteOneVersion(NctiFileInterface*& o_pFI);
	private:
		void ReadTwoVersion(NctiFileInterface* i_pFI);
		void WriteTwoVersion(NctiFileInterface*& o_pFI);
#pragma endregion
	
	};
}
#endif // !NctiFileVersionDocElement_H
