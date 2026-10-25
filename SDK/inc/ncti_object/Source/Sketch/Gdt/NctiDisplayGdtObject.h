#ifndef NctiDisplayGdtObject_H
#define NctiDisplayGdtObject_H
#include "dcl_ncti_object.h"
#include "NctiDisplayObject.h"
namespace NCTI
{
	class DECL_NCTI_OBJECT NctiDisplayGdtObject : public NctiDisplayObject
	{
		NCTI_DISPLAYOBJECT_FUNCTIONS(NctiDisplayGdtObject)
	public:
		virtual ~NctiDisplayGdtObject() {};
		void Init();
	public:
		void SetSegOwner(NctiDisplayObject* i_DisplayObj);
		NctiDisplayObject* GetSegOwner() { return m_SegOwner; }
	private:
		NctiDisplayObject* m_SegOwner;
		Ncti_Long m_SegOwnerIndex;
	private:
		NCTI_READ_AND_WRITE_VERSION_FUN(1)

	};
}
#endif
