#ifndef NctiDisplayGSketchGroup_H
#define NctiDisplayGSketchGroup_H
#include "NctiDisplayGroup.h"
#include "dcl_ncti_object.h"
#include "NctiDisplayGSketch.h"
#include "NctiSketchComDefine.h"
namespace NCTI
{
	class DECL_NCTI_OBJECT NctiDisplayGSketchGroup : public NctiDisplayGroup
	{
		NCTI_DISPLAYOBJECT_FUNCTIONS(NctiDisplayGSketchGroup)
	public:
		void Init();
		virtual ~NctiDisplayGSketchGroup();

		virtual EnumNctiDoCallbackStatus Callback(NctiBaseView* i_pBaseView, EnumNctiDoCallbackType i_eType, NctiDisplayObject* i_pDoVariable);
		bool IsValid();
		NctiDisplayGSketch* GetDisplayGSketch();
		virtual EnumNctiResult	CreateModelBody(NctiDisplayDocCustomContainer* i_pDoContainer, NCTI_MODEL_TAG& i_pBodyCreated, NctiDisplayDocCustomContainer* i_pDocCustomContaine);
		void GetBooleanMode(EnumNctiSketchBooleanMode& i_eBoolMode);
		void SetBooleanMode(const EnumNctiSketchBooleanMode& i_eBoolMode);
		virtual void		TransformPosition(const NctiTransf& i_cTrans);
	protected:
		EnumNctiSketchBooleanMode m_eBooleanMode;
	};
}
#endif