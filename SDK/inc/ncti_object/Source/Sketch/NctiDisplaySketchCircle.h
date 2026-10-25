#ifndef NctiDisplaySketchCircle_H
#define NctiDisplaySketchCircle_H
#include "ncti.h"
#include "dcl_ncti_object.h"
#include "NctiDisplaySketchSurface.h"
namespace NCTI
{
	class NctiDisplayGdtDimRadius;
	class NctiRenderPolylineItem;
	class DECL_NCTI_OBJECT NctiDisplaySketchCircle : public NctiDisplaySketchSurface
	{
		NCTI_DISPLAYOBJECT_FUNCTIONS(NctiDisplaySketchCircle)
	public:
		virtual ~NctiDisplaySketchCircle();
		void Init(NctiPosition& i_posCenter, NctiPosition& i_posOnCircle, bool i_bDiaMode);
		virtual EnumNctiDoCallbackStatus Callback(NctiBaseView* i_pBaseView, EnumNctiDoCallbackType i_eType, NctiDisplayObject* i_pDoVariable);
		virtual EnumNctiResult ActivateData(NctiDisplayDocCustomContainer* i_pDocCustomContainer, const std::vector<NCTI_MODEL_TAG>& i_ModelBodyVec);
		virtual EnumNctiResult CreateModelBody(NctiDisplayDocCustomContainer* i_pDoContainer, NCTI_MODEL_TAG& o_pDoBody, NctiDisplayDocCustomContainer* i_pDocCustomContaine) override;

		virtual EnumNctiResult	CreateSketch();
		virtual EnumNctiResult	ProcessActivateSketch();
		virtual void GetPosition(NctiPositionArray& o_posArray);
		EnumNctiResult SetPosition(NctiPositionArray* i_pPosArray);
		virtual EnumNctiResult NotifyDimensionChanged();
		bool IsDiaMode() { return m_bDiaMode; };
		void init_using(NctiDisplayObject* i_pDoCopyFrom);
	private:
		NctiPosition m_aPosition[2];
		NctiRenderPolylineItem* m_keyCircle;
		bool m_bDiaMode;
		NctiDisplayGdtDimRadius* m_pGdtDimension;
	private:
		EnumNctiResult CreateCircle();
	private:
		NCTI_READ_AND_WRITE_VERSION_FUN(1)
	};
}


#endif
