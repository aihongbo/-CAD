#ifndef NctiDisplaySketchSpline_H
#define NctiDisplaySketchSpline_H
#include "NctiDisplaySketchCurve.h"
#include "ncti.h"
#include "dcl_ncti_object.h"
#include "NctiRenderPolylineItem.h"

namespace NCTI
{
	class DECL_NCTI_OBJECT NctiDisplaySketchSpline : public NctiDisplaySketchCurve
	{
		NCTI_DISPLAYOBJECT_FUNCTIONS(NctiDisplaySketchSpline)
	public:
		void Init(NctiPositionArray* pPosArray);
		virtual ~NctiDisplaySketchSpline();
		virtual EnumNctiDoCallbackStatus Callback(NctiBaseView* i_pBaseView, EnumNctiDoCallbackType i_eType, NctiDisplayObject* i_pDoVariable);
		virtual EnumNctiResult ActivateData(NctiDisplayDocCustomContainer* i_pDocCustomContainer, const std::vector<NCTI_MODEL_TAG>& i_ModelBodyVec);
		virtual NctiRenderGeometryItem* GetSketchCurveKey() { return m_keySpline; };
		virtual EnumNctiResult	CreateModelBody(NctiDisplayDocCustomContainer* i_pDoContainer, NCTI_MODEL_TAG& o_pBodyCreated, NctiDisplayDocCustomContainer* i_pDocCustomContaine) override;

		virtual EnumNctiResult	CreateSketch();
		virtual EnumNctiResult SetPosition(NctiPositionArray* i_pPosArray);
		virtual void GetPosition(NctiPositionArray& o_posArray);

	protected:
		void init_using(NctiDisplayObject* i_pDoCopyFrom);

	private:
		int				m_iNumPoints;
		NctiPositionArray* m_paPositions;
		NctiRenderPolylineItem* m_keySpline;
		NCTI_READ_AND_WRITE_VERSION_FUN(1)
	};
}


#endif
