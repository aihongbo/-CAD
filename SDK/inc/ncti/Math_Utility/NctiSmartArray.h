#ifndef NctiSmartArray_H
#define NctiSmartArray_H
#include "ncti.h"
#include "NctiPosition.h"
#include "NctiVector.h"
namespace NCTI
{
	class NctiFileInterface;
	class NctiStreamFileContext;
	class NctiSmartArrayLifeCycleManager;
	/**
    * @brief internal used
	*/
	class DECL_NCTI NctiSmartArray : NCTI_BASE_CLASS
	{
		friend class NctiSmartArrayLifeCycleManager;
		enum EnumNctiLocalType
		{
			SM_INT, 
			SM_DOUBLE, 
			SM_POSITION, 
			SM_VECTOR, 
			SM_FLOAT
		};
	public:
		NctiSmartArray(const char*  i_pszTypeName, Ncti_Integer  i_iNumData, const char*  i_pszNameId = NULL);
		virtual ~NctiSmartArray();
		Ncti_Boolean  IsDataType(char*  i_pszTypeName); // "NctiVector", "Ncti_Integer",
		Ncti_Boolean SetData(Ncti_Integer  i_iIndex, Ncti_Integer  i_iValue);
		Ncti_Boolean GetData(Ncti_Integer  i_iIndex, Ncti_Integer& o_iValue);
		Ncti_Boolean AddData(Ncti_Integer  i_iValue); 
		Ncti_Boolean SetData(Ncti_Integer  i_iIndex, Ncti_Double o_dValue);
		Ncti_Boolean GetData(Ncti_Integer  i_iIndex, Ncti_Double& o_dValue);
		Ncti_Boolean AddData(Ncti_Double  i_dValue);
		Ncti_Boolean SetData(Ncti_Integer  i_iIndex, const NctiPosition& o_pos);
		Ncti_Boolean GetData(Ncti_Integer  i_iIndex, NctiPosition& o_pos);
		Ncti_Boolean AddData(NctiPosition&  i_pos);
		Ncti_Boolean SetData(Ncti_Integer  i_iIndex, const NctiVector& o_vec);
		Ncti_Boolean GetData(Ncti_Integer  i_iIndex, NctiVector& o_vec);
		Ncti_Boolean AddData(NctiVector&  i_vec);
		Ncti_Boolean SetData(Ncti_Integer  i_iIndex, Ncti_Float  i_fValue);
		Ncti_Boolean GetData(Ncti_Integer  i_iIndex, Ncti_Float& o_fValue);
		Ncti_Boolean AddData(Ncti_Float  i_fValue);
		Ncti_Double GetCompValue(Ncti_Integer  i_iIndex, Ncti_Integer o_xyz);
		void SetCompValue(Ncti_Integer  i_iIndex, Ncti_Integer  i_xyz, Ncti_Double  i_dValue);
		Ncti_Integer   GetNumData();
		const char* GetNameId(); 
		void SetNameId(const char*  i_name); 
		const char* GetTypeName();
		void SetInitSize(Ncti_Integer  i_iInitSizeOfMemory);
		Ncti_Integer GetInitSize() { return m_iInitSizeOfMemory; };
		EnumNctiResult    SaveData(NctiFileInterface*  i_pFI);
		EnumNctiResult    RestoreData(NctiFileInterface*  i_pFI);
		//EnumNctiResult	WriteStreamFile(NctiStreamFileContext*  i_pSFC);
		//EnumNctiResult	ReadStreamFile(NctiStreamFileContext*  i_pSFC);
		Ncti_Boolean MemCopy(void*  i_pCopyBuffer);
		NctiSmartArrayLifeCycleManager* GetSmartArrayLifeCycleManager() { return m_pSALCM; };
	protected:
		Ncti_Integer	get_size_of();
		void expand();
	private:
		char* m_pszTypeName;
		EnumNctiLocalType m_eTypeId;
		char* m_pszNameId; 
		Ncti_Integer   m_iNumData;
		Ncti_Integer   m_iNumArray; 
		Ncti_Integer   m_iSize; 
		Ncti_Integer	  m_iCapacity; 
		void** m_ppArray;
		Ncti_Integer m_iInitSizeOfMemory;
		NctiSmartArrayLifeCycleManager* m_pSALCM; 
	};
}
#endif // !NctiSmartArray_H
