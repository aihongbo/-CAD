#ifndef NctiDisplaySketchEllipse_H
#define NctiDisplaySketchEllipse_H
#include "NctiDisplaySketchSurface.h"
#include "ncti.h"
#include "dcl_ncti_object.h"
namespace NCTI
{
	class NctiRenderPolylineItem;
	class DECL_NCTI_OBJECT NctiDisplaySketchEllipse : public NctiDisplaySketchSurface
	{
		NCTI_DISPLAYOBJECT_FUNCTIONS(NctiDisplaySketchEllipse)
	public:
		void Init(NctiPositionArray* i_pPosArray);
		virtual ~NctiDisplaySketchEllipse();
		virtual EnumNctiDoCallbackStatus Callback(NctiBaseView* i_pBaseView, EnumNctiDoCallbackType i_eType, NctiDisplayObject* i_pDoVariable);
		virtual EnumNctiResult ActivateData(NctiDisplayDocCustomContainer* i_pDocCustomContainer, const std::vector<NCTI_MODEL_TAG>& i_ModelBodyVec);
		virtual EnumNctiResult	CreateModelBody(NctiDisplayDocCustomContainer* i_pDoContainer, NCTI_MODEL_TAG& o_pBodyCreated, NctiDisplayDocCustomContainer* i_pDocCustomContaine) override;

		virtual EnumNctiResult	CreateSketch();
		virtual EnumNctiResult	EndEditing();
		EnumNctiResult SetPosition(NctiPositionArray* i_pPosArray);
		virtual EnumNctiResult NotifyDimensionChanged();
		virtual void GetPosition(NctiPositionArray& o_posArray);

	protected:
		void init_using(NctiDisplayObject* i_pDoCopyFrom);
		EnumNctiResult CreateEllipse(NctiDisplayDocCustomContainer* pDocCustomContainer);

	private:
		NctiDisplayGdtDimension* m_pGdtDimensionMajor;
		NctiDisplayGdtDimension* m_pGdtDimensionMinor;
		NctiPosition            m_PositionCenterPoint;
		NctiVector              m_VectorMajorAxis;
		NctiVector              m_VectorMinorAxis;
		NctiRenderPolylineItem* m_keyEllipse;
		NCTI_READ_AND_WRITE_VERSION_FUN(1)
	};
}


#endif