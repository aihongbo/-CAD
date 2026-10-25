#ifndef NctiDisplaySketchPolyline_H
#define NctiDisplaySketchPolyline_H
#include "NctiDisplaySketchCurve.h"
#include "ncti.h"
#include "dcl_ncti_object.h"
#include "NctiRenderPolylineItem.h"
namespace NCTI
{
	class DECL_NCTI_OBJECT NctiDisplaySketchPolyline : public NctiDisplaySketchCurve
	{
		NCTI_DISPLAYOBJECT_FUNCTIONS(NctiDisplaySketchPolyline)
	public:
		void Init(NctiPositionArray* i_pPosArray);
		virtual ~NctiDisplaySketchPolyline();
		virtual EnumNctiDoCallbackStatus Callback(NctiBaseView* i_pBaseView, EnumNctiDoCallbackType i_eType, NctiDisplayObject* i_pDoVariable);
		virtual EnumNctiResult ActivateData(NctiDisplayDocCustomContainer* i_pDocCustomContainer, const std::vector<NCTI_MODEL_TAG>& i_ModelBodyVec);
		virtual NctiRenderGeometryItem* GetSketchCurveKey() { return m_keyPolyline; };
		virtual EnumNctiResult	CreateModelBody(NctiDisplayDocCustomContainer* i_pDoContainer, NCTI_MODEL_TAG& o_pBodyCreated, NctiDisplayDocCustomContainer* i_pDocCustomContaine) override;

		virtual EnumNctiResult	CreateSketch();
		virtual EnumNctiResult SetPosition(NctiPositionArray* i_pPosArray);
		virtual void GetPosition(NctiPositionArray& o_posArray);

	protected:
		void init_using(NctiDisplayObject* i_pDoCopyFrom);

	private:
		int				m_iNumPoints;
		NctiPositionArray* m_paPositions;
		NctiRenderPolylineItem* m_keyPolyline;
		NCTI_READ_AND_WRITE_VERSION_FUN(1)
	};
}


#endif
