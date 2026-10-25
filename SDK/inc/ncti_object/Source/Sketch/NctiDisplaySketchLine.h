#ifndef NctiDisplaySketchLine_H
#define NctiDisplaySketchLine_H
#include "NctiDisplaySketchCurve.h"
#include "ncti.h"
#include "dcl_ncti_object.h"
#include "NctiRenderPolylineItem.h"
namespace NCTI
{
	class DECL_NCTI_OBJECT NctiDisplaySketchLine : public NctiDisplaySketchCurve
	{
		NCTI_DISPLAYOBJECT_FUNCTIONS(NctiDisplaySketchLine)
	public:
		void Init(NctiPosition& i_pos1, NctiPosition& i_pos2);
		virtual ~NctiDisplaySketchLine();
		virtual EnumNctiDoCallbackStatus Callback(NctiBaseView* i_pBaseView, EnumNctiDoCallbackType i_eType, NctiDisplayObject* i_pDoVariable);
		virtual EnumNctiResult ActivateData(NctiDisplayDocCustomContainer* i_pDocCustomContainer, const std::vector<NCTI_MODEL_TAG>& i_ModelBodyVec);
		virtual NctiRenderGeometryItem* GetSketchCurveKey() { return m_keyLine; };
		virtual EnumNctiResult	CreateModelBody(NctiDisplayDocCustomContainer* i_pDoContainer, NCTI_MODEL_TAG& o_pBodyCreated, NctiDisplayDocCustomContainer* i_pDocCustomContaine) override;

		virtual EnumNctiResult	CreateSketch();
		virtual EnumNctiResult SetPosition(NctiPositionArray* i_pPosArray);
		virtual void GetPosition(NctiPositionArray& i_posArray);

	protected:
		void init_using(NctiDisplayObject* i_pDoCopyFrom);

	private:
		NctiPosition		m_aPosition[2];
		NctiRenderPolylineItem* m_keyLine;
		NCTI_READ_AND_WRITE_VERSION_FUN(1)
	};
}
#endif
