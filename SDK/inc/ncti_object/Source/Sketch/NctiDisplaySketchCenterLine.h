#ifndef NctiDisplaySketchCenterLine_H
#define NctiDisplaySketchCenterLine_H
#include "ncti.h"
#include "dcl_ncti_object.h"
#include "NctiDisplaySketchCurve.h"
#include "NctiRenderPolylineItem.h"
namespace NCTI
{
	class DECL_NCTI_OBJECT NctiDisplaySketchCenterLine : public NctiDisplaySketchCurve
	{
		NCTI_DISPLAYOBJECT_FUNCTIONS(NctiDisplaySketchCenterLine)
	public:
		void Init(NctiPosition& i_pos1, NctiPosition& i_pos2);
		virtual ~NctiDisplaySketchCenterLine();
		virtual EnumNctiDoCallbackStatus Callback(NctiBaseView* i_pBaseView, EnumNctiDoCallbackType i_eType, NctiDisplayObject* i_pDoVariable);
		virtual EnumNctiResult ActivateData(NctiDisplayDocCustomContainer* i_pDocCustomContainer, const std::vector<NCTI_MODEL_TAG>& i_ModelBodyVec);
		virtual NctiRenderGeometryItem* GetSketchCurveKey() { return m_keyCenterLine; };
		virtual EnumNctiResult	CreateModelBody(NctiDisplayDocCustomContainer* i_pDoContainer, NCTI_MODEL_TAG& o_pBodyCreated, NctiDisplayDocCustomContainer* i_pDocCustomContaine) override;

		virtual EnumNctiResult	CreateSketch();
		virtual EnumNctiResult	ProcessActivateSketch();
		virtual EnumNctiResult	ProcessInactivateSketch();
		virtual void		TransformPosition(const NctiTransf& i_cTrans);
		EnumNctiResult GetAxis(NctiPosition& o_cOrigin, NctiUnitVector& o_cAxis);
		EnumNctiResult SetPosition(NctiPositionArray* i_pPosArray);
		virtual void GetPosition(NctiPositionArray& o_posArray);

	protected:
		virtual void set_attribute(bool i_bActive);
		void init_using(NctiDisplayObject* i_pDoCopyFrom);

	private:
		NctiPosition		m_aPosition[2];
		NctiRenderPolylineItem* m_keyCenterLine;
		NCTI_READ_AND_WRITE_VERSION_FUN(1)
	};
}


#endif
