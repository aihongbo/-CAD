#ifndef NctiBooleanArray_H
#define NctiBooleanArray_H
#include "ncti.h"
namespace NCTI
{
	/**
	* @brief internal used
	*/
	class NctiBooleanArray : public NCTI_BASE_CLASS
	{
	public:
		NctiBooleanArray(Ncti_Integer i_iNumBoolean);
		virtual ~NctiBooleanArray();
		Ncti_Integer GetSize();
		void Initialize();
		void SetData(Ncti_Integer i_iIndex, Ncti_Boolean i_bOnOff);
		Ncti_Boolean GetData(Ncti_Integer i_iIndex);
		Ncti_Integer CountTrue();
		void Init();
		Ncti_Integer Next();
		void MakeCopy(NctiBooleanArray*& i_pBoolArray);
	private:
		Ncti_Integer m_iLen;
		Ncti_Integer m_iNumBoolean;
		Ncti_Integer m_iSize;
		Ncti_UInteger* m_aBoolean;
		Ncti_Integer m_iIndex;
	};
}
#endif
