#ifndef NctiDisplayViewObject_H
#define NctiDisplayViewObject_H
#include "NctiDisplayObject.h"
namespace NCTI
{
	class NctiBaseView;
	/**
	* @brief internal used
	*/
	class DECL_NCTI NctiDisplayViewObject : public NctiDisplayObject
	{
		NCTI_DISPLAYOBJECT_FUNCTIONS(NctiDisplayViewObject)
	public:
		virtual ~NctiDisplayViewObject();
		void Init(NctiBaseView* i_pBaseView);
	protected:
		NctiBaseView* m_pOwnerBaseView;
	};
}
#endif
