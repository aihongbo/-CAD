#ifndef NctiPositionArray_H
#define NctiPositionArray_H
#include "dcl_ncti_object.h"
#include "NctiData.h"
namespace NCTI
{
	class NctiPosition;

	class DECL_NCTI_OBJECT NctiPositionArray : public NCTI_BASE_CLASS
	{
	public:
		NctiPositionArray(int  i_iSize = 10);
		NctiPositionArray(NctiPositionArray& cCopyFrom);
		NctiPositionArray(NctiPositionArray* const  i_pCopyFrom);
		virtual ~NctiPositionArray();
		int Add(const NctiPosition& i_pos);
		int	GetCount();
		NctiPosition& operator[](int  i_iIndex) const;
	protected:
		int expand();

	private:
		int m_iSize;
		int	m_iCount;
		NctiPosition* m_pArray;
	public:
		void reverse();
	};
}
NCTI_DATA_DEF(NctiPositionArray)

#endif