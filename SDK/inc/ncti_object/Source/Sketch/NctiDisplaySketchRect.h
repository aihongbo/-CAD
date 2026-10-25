#ifndef NctiDisplaySketchRect_H
#define NctiDisplaySketchRect_H
#include "NctiDisplaySketchSurface.h"
#include "ncti.h"
#include "dcl_ncti_object.h"
namespace NCTI
{
	class NctiDisplayGdtDim2Point;
	class NctiDisplayGModelObject;
	class DECL_NCTI_OBJECT NctiDisplaySketchRect : public NctiDisplaySketchSurface
	{
		NCTI_DISPLAYOBJECT_FUNCTIONS(NctiDisplaySketchRect)
	public:
		virtual ~NctiDisplaySketchRect();
		void Init(NctiPosition& pos1, NctiPosition& pos2);
		virtual EnumNctiDoCallbackStatus Callback(NctiBaseView* i_pBaseView, EnumNctiDoCallbackType i_eType, NctiDisplayObject* i_pDoVariable);
		virtual EnumNctiResult ActivateData(NctiDisplayDocCustomContainer* i_pDocCustomContainer, const std::vector<NCTI_MODEL_TAG>& i_ModelBodyVec);
		virtual EnumNctiResult CreateModelBody(NctiDisplayDocCustomContainer* i_pDoContainer, NCTI_MODEL_TAG& o_pDoBody, NctiDisplayDocCustomContainer* i_pDocCustomContaine) override;

		virtual EnumNctiResult	CreateSketch();
		virtual void GetPosition(NctiPositionArray& o_posArray);
		EnumNctiResult SetPosition(NctiPositionArray* i_pPosArray);
		virtual EnumNctiResult ProcessActivateSketch();
		virtual EnumNctiResult NotifyDimensionChanged();
	protected:
		void init_using(NctiDisplayObject* i_pDoCopyFrom);
	private:
		NctiPosition m_aPosition[2];
		NctiDisplayGdtDim2Point* m_pGdtDimHeight;
		NctiDisplayGdtDim2Point* m_pGdtDimWidth;
	private:
		EnumNctiResult CreateRect();
	private:
		NCTI_READ_AND_WRITE_VERSION_FUN(1)
	};
}
#endif
