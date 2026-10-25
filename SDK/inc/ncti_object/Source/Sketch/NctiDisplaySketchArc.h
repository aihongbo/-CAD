#ifndef NctiDisplaySketchArc_H
#define NctiDisplaySketchArc_H
#include "NctiDisplaySketchCurve.h"
#include "NctiRenderPolylineItem.h"
namespace NCTI
{
	class NctiDisplayGdtDimRadius;

	class DECL_NCTI_OBJECT NctiDisplaySketchArc : public NctiDisplaySketchCurve
	{
		NCTI_DISPLAYOBJECT_FUNCTIONS(NctiDisplaySketchArc)
	public:
		void Init(NctiPosition& i_posOnArc1, NctiPosition& i_posOnArc2, NctiPosition& i_posOnArc3, bool i_bAngleMode);
		virtual ~NctiDisplaySketchArc();
		virtual EnumNctiDoCallbackStatus Callback(NctiBaseView* i_pBaseView, EnumNctiDoCallbackType i_eType, NctiDisplayObject* i_pDoVariable);
		virtual EnumNctiResult ActivateData(NctiDisplayDocCustomContainer* i_pDocCustomContainer, const std::vector<NCTI_MODEL_TAG>& i_ModelBodyVec);
		virtual NctiRenderGeometryItem* GetSketchCurveKey() { return m_keyArc; };
		virtual EnumNctiResult	CreateModelBody(NctiDisplayDocCustomContainer* i_pDoContainer, NCTI_MODEL_TAG& o_pBodyCreated, NctiDisplayDocCustomContainer* i_pDocCustomContaine) override;

		virtual EnumNctiResult	CreateSketch();
		virtual EnumNctiResult	ProcessActivateSketch();
		virtual EnumNctiResult SetPosition(NctiPositionArray* i_pPosArray);
		virtual void GetPosition(NctiPositionArray& o_posArray);
		bool IsAngleMode() { return m_bAngleMode; };
		virtual EnumNctiResult NotifyDimensionChanged();

	protected:
		void init_using(NctiDisplayObject* i_pDoCopyFrom);
	private:
		EnumNctiResult CreateArc();
	private:
		NctiPosition m_aPosition[3];
		NctiPosition m_DimPt1;//no save
		NctiPosition m_DimPt2;//no save
		NctiRenderPolylineItem* m_keyArc;
		NctiDisplayGdtDimRadius* m_pDisplayGdtDimRadius;
		bool m_bAngleMode;
		NCTI_READ_AND_WRITE_VERSION_FUN(1)
	};

}

#endif
