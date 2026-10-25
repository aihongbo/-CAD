#ifndef NctiDisplaySketchSurface_H
#define NctiDisplaySketchSurface_H
#include "NctiDisplaySketchObject.h"
#include "NctiDisplayGSketch.h"
#include "ncti.h"
#include "dcl_ncti_object.h"

namespace NCTI
{
	class DECL_NCTI_OBJECT NctiDisplaySketchSurface : public NctiDisplaySketchObject
	{
		NCTI_DISPLAYOBJECT_FUNCTIONS(NctiDisplaySketchSurface)
	public:
		virtual ~NctiDisplaySketchSurface();
		void Init();
		virtual EnumNctiDoCallbackStatus Callback(NctiBaseView* i_pBaseView, EnumNctiDoCallbackType i_eType, NctiDisplayObject* i_pDoVariable);

		virtual EnumNctiResult	StartEditing();
		virtual EnumNctiResult	EndEditing();
		virtual EnumNctiResult CreateModelBody(NctiDisplayDocCustomContainer* i_pDoContainer, NCTI_MODEL_TAG& o_pDoBody);
		virtual EnumNctiResult CreateModelBody(NctiDisplayDocCustomContainer* i_pDoContainer, NCTI_MODEL_TAG& o_pBodyCreated, NctiDisplayDocCustomContainer* i_pDocCustomContaine) override;
	protected:
		virtual void set_attribute(bool bActive);
	private:
		NCTI_READ_AND_WRITE_VERSION_FUN(1)
	};
}

#endif
