#ifndef NctiDisplayPositionArray_H
#define NctiDisplayPositionArray_H
#include "dcl_ncti_object.h"
#include "NctiDisplayObject.h"
#include "NctiPositionArray.h"

namespace NCTI
{
	class NctiPositionArray;
	class NctiHistoryManager;
	class NctiBaseModel;
	class DECL_NCTI_OBJECT NctiDisplayPositionArray : public NctiDisplayObject
	{
		NCTI_DISPLAYOBJECT_FUNCTIONS(NctiDisplayPositionArray);

	public:
		NctiDisplayPositionArray(int i_iDummy);
		void Init();
		virtual ~NctiDisplayPositionArray();
		void AddPosition(const NctiPosition& i_pos);
		void SetPosition(int i_iIndex, const NctiPosition& i_pos);
		NctiPosition& operator[](int i_nIndex);
		int GetNumPosition();

	private:
		NctiData_NctiPositionArray* m_pDataPositionArray;
		int	m_iNum;
	};
}
#endif