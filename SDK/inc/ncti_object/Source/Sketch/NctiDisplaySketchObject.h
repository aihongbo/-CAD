#ifndef NctiDisplaySketchObject_H
#define NctiDisplaySketchObject_H
#include "NctiDisplayObject.h"
#include "NctiDisplayPositionArray.h"
#include "NctiDisplayGSketch.h"
#include "ncti.h"
#include "dcl_ncti_object.h"
namespace NCTI
{
	class NctiDisplayGdtDimension;
	class DECL_NCTI_OBJECT NctiDisplaySketchObject : public NctiDisplayObject
	{
		NCTI_DISPLAYOBJECT_FUNCTIONS(NctiDisplaySketchObject)
	public:
		virtual ~NctiDisplaySketchObject();
		void Init();

		virtual EnumNctiResult ActivateData(NctiDisplayDocCustomContainer* i_pDocCustomContainer, const std::vector<NCTI_MODEL_TAG>& i_ModelBodyVec);
		virtual EnumNctiResult	ProcessActivateSketch();
		virtual EnumNctiResult	ProcessInactivateSketch();
		void GetBooleanMode(EnumNctiSketchBooleanMode& i_eBoolMode);
		void SetBooleanMode(const EnumNctiSketchBooleanMode& i_eBoolMode);
		virtual EnumNctiResult	CreateModelBody(NctiDisplayDocCustomContainer* i_pDoContainer, NCTI_MODEL_TAG& o_pBodyCreated, NctiDisplayDocCustomContainer* i_pDocCustomContaine);
		virtual EnumNctiResult	CreateSketch();
		NctiDisplayGSketch* GetDisplayGSketch();
		virtual EnumNctiResult SetPosition(NctiPositionArray* i_pPosArray);
		virtual void GetPosition(NctiPositionArray& o_posArray);
	protected:
		virtual void set_attribute(bool i_bActive) {};
		void update_display_by_active_state();
	public:
		virtual void init_using(NctiDisplayObject* i_pDoCopyFrom);
	protected:
		EnumNctiSketchBooleanMode m_eBooleanMode;
		bool m_bEditing;
	private:
		NCTI_READ_AND_WRITE_VERSION_FUN(1)
	};

}
#endif

