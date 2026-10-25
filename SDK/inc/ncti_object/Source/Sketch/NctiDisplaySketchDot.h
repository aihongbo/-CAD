#ifndef NctiDisplaySketchDot_H
#define NctiDisplaySketchDot_H
#include "ncti.h"
#include "dcl_ncti_object.h"
#include "NctiDisplaySketchObject.h"
#include "NctiPosition.h"

namespace NCTI
{
	class NctiRenderGeometryItem;
	class NctiRenderMarkerItem;
	class DECL_NCTI_OBJECT NctiDisplaySketchDot : public NctiDisplaySketchObject
	{
		NCTI_DISPLAYOBJECT_FUNCTIONS(NctiDisplaySketchDot)
	public:
		void Init(NctiPosition cPos);
		virtual ~NctiDisplaySketchDot();
		virtual EnumNctiDoCallbackStatus Callback(NctiBaseView* pBaseView, EnumNctiDoCallbackType eType, NctiDisplayObject* pDoVariable);
		virtual EnumNctiResult ActivateData(NctiDisplayDocCustomContainer* i_pDocCustomContainer, const std::vector<NCTI_MODEL_TAG>& i_ModelBodyVec);

		virtual NctiRenderGeometryItem* GetSketchDotKey();
		virtual EnumNctiResult	CreateSketch();
		virtual void GetPosition(NctiPositionArray& o_posArray);
		virtual	EnumNctiResult SetPosition(NctiPositionArray* i_pPosArray);
	protected:
		virtual void set_attribute(bool i_bActive);
		void init_using(NctiDisplayObject* i_pDoCopyFrom);
	private:
		EnumNctiResult CreateDot();
	private:
		NctiPosition		m_aPosition;
		NctiRenderMarkerItem* m_keyDot;
		NCTI_READ_AND_WRITE_VERSION_FUN(1)
	};
}


#endif
