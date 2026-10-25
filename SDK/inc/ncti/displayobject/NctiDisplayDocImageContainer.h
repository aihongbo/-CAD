#ifndef NctiDisplayDocImageContainer_H
#define NctiDisplayDocImageContainer_H
#include "NctiDisplayDocElement.h"
namespace NCTI
{
	/**
	* @brief Doc Image Container class
	* @see NctiDisplayDocElement
	*/
	class DECL_NCTI NctiDisplayDocImageContainer : public NctiDisplayDocElement
	{
		NCTI_DISPLAYOBJECT_FUNCTIONS(NctiDisplayDocImageContainer)
	public:
		~NctiDisplayDocImageContainer();
		virtual void Init();
	public:
		virtual EnumNctiResult ActivateData();
	protected:
		virtual EnumNctiResult save_temp_file(NctiFileInterface* i_pFI);
		virtual EnumNctiResult restore_temp_file(NctiFileInterface* i_pFI);
	protected:
		char* m_pwsTempFileName;		// No save data, don't need to delete.
		FILE* m_ImageFile;
	public:
		void SetImageFile(FILE* fi);
		void SetFormat(const char* format);
		const char* GetFormat() { return m_Format; }
		FILE* GetImageFilePoint() { return m_ImageFile; }
		const char* GetTempFile() { return m_pwsTempFileName; }
	private:
		char* m_Format;
		//verson 2
		std::vector<Ncti_Integer> m_DeForX;
		std::vector<Ncti_Integer> m_DeForY;
	public:
		void SetDeForX(const std::vector<Ncti_Integer>& DeforX);
		void SetDeForY(const std::vector<Ncti_Integer>& DeforY);
		void GetDeForX(std::vector<Ncti_Integer>& DeforX) { DeforX = m_DeForX; }
		void GetDeForY(std::vector<Ncti_Integer>& DeforY) { DeforY = m_DeForY; }
	public:
		//version 1
		void ReadOneVersion(NctiFileInterface* pFI);
		void WriteOneVersion(NctiFileInterface*& pFI);
		//version 2
		void ReadTwoVersion(NctiFileInterface* pFI);
		void WriteTwoVersion(NctiFileInterface*& pFI);
	};
}
#endif


