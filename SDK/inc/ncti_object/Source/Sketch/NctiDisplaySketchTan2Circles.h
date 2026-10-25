#ifndef NctiDisplaySketchTan2Circles_H
#define NctiDisplaySketchTan2Circles_H
#include "NctiDisplaySketchSurface.h"

#include "ncti.h"
#include "dcl_ncti_object.h"
namespace NCTI
{
	class NctiDisplayGdtDimRadius;
	class NctiRenderPolylineItem;
	enum EnumNctiSketchTan2CirclesMode
	{
		NCTI_SKETCH_TAN2CIRCLES_ARC,//Default circle
		NCTI_SKETCH_TAN2CIRCLES_LINE,
		NCTI_SKETCH_TAN2CIRCLES_LINE2CENTER,
//		NCTI_SKETCH_TAN2CIRCLES_POINT
	};
	class DECL_NCTI_OBJECT NctiDisplaySketchTan2Circles : public NctiDisplaySketchSurface
	{
		NCTI_DISPLAYOBJECT_FUNCTIONS(NctiDisplaySketchTan2Circles)
	public:
		void Init(NctiPosition i_posCenter1, NctiPosition i_posOnCircle1, NctiPosition i_posCenter2, NctiPosition i_posOnCircle2);
		virtual ~NctiDisplaySketchTan2Circles();
		virtual EnumNctiDoCallbackStatus Callback(NctiBaseView* i_pBaseView, EnumNctiDoCallbackType i_eType, NctiDisplayObject* i_pDoVariable);
		virtual EnumNctiResult ActivateData(NctiDisplayDocCustomContainer* i_pDocCustomContainer, const std::vector<NCTI_MODEL_TAG>& i_ModelBodyVec);
		virtual EnumNctiResult	CreateModelBody(NctiDisplayDocCustomContainer* i_pDoContainer, NCTI_MODEL_TAG& o_pBodyCreated, NctiDisplayDocCustomContainer* i_pDocCustomContaine) override;

		virtual EnumNctiResult	CreateSketch();
		virtual EnumNctiResult	ProcessActivateSketch();
		EnumNctiSketchTan2CirclesMode GetCircle1ShapeMode() { return m_eShapeMode1; };
		void SetCircle1ShapeMode(const EnumNctiSketchTan2CirclesMode& i_eShapeMode) { m_eShapeMode1 = i_eShapeMode; };
		EnumNctiSketchTan2CirclesMode GetCircle2ShapeMode() { return m_eShapeMode2; };
		void SetCircle2ShapeMode(const EnumNctiSketchTan2CirclesMode& i_eShapeMode) { m_eShapeMode2 = i_eShapeMode; };
		virtual EnumNctiResult SetPosition(NctiPositionArray* i_pPosArray);
		virtual void GetPosition(NctiPositionArray& i_posArray);
		virtual EnumNctiResult NotifyDimensionChanged();
		bool GetTanPosCalculated() {return m_bTanPosCalculated;}
	protected:
		void init_using(NctiDisplayObject* i_pDoCopyFrom);
		EnumNctiResult CreateTan2Circles();
	private:
		NctiPosition		m_aPosition[4]; // cen1,pos1,cen2,pos2
		NctiRenderPolylineItem* m_aCircleKey[2];
		NctiRenderPolylineItem* m_keyTan2Circles;

		NctiDisplayGdtDimRadius* m_pGdtDimRadiusForCircle1;
		NctiDisplayGdtDimRadius* m_pGdtDimRadiusForCircle2;

		EnumNctiSketchTan2CirclesMode m_eShapeMode1;// circle1
		EnumNctiSketchTan2CirclesMode m_eShapeMode2; // circle2

		NctiPosition     m_aTanPos[4];// internal use, tangent points, 1/2---3/4

		bool m_bTanPosCalculated;
		NCTI_READ_AND_WRITE_VERSION_FUN(1)
	};

}

#endif
