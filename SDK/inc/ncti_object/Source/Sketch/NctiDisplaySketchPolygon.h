#ifndef NctiDisplaySketchPolygon_H
#define NctiDisplaySketchPolygon_H
#include "NctiDisplaySketchSurface.h"
#include "ncti.h"
#include "dcl_ncti_object.h"
namespace NCTI
{
	class NctiRenderPolylineItem;
	class DECL_NCTI_OBJECT NctiDisplaySketchPolygon : public NctiDisplaySketchSurface
	{
		NCTI_DISPLAYOBJECT_FUNCTIONS(NctiDisplaySketchPolygon)
	public:
		virtual ~NctiDisplaySketchPolygon();
		void Init(NctiPositionArray* i_pPosArray);
		virtual EnumNctiDoCallbackStatus Callback(NctiBaseView* i_pBaseView, EnumNctiDoCallbackType i_eType, NctiDisplayObject* i_pDoVariable);
		virtual EnumNctiResult ActivateData(NctiDisplayDocCustomContainer* i_pDocCustomContainer, const std::vector<NCTI_MODEL_TAG>& i_ModelBodyVec);
		virtual EnumNctiResult CreateModelBody(NctiDisplayDocCustomContainer* i_pDoContainer, NCTI_MODEL_TAG& o_pDoBody, NctiDisplayDocCustomContainer* i_pDocCustomContaine) override;

		virtual EnumNctiResult CreateSketch();
		virtual EnumNctiResult EndEditing();
		EnumNctiResult SetPosition(NctiPositionArray* i_pPosArray);
		virtual void GetPosition(NctiPositionArray& o_posArray);
	protected:
		void init_using(NctiDisplayObject* i_pDoCopyFrom);
	private:
		int	m_iNumPoints;
		NctiPositionArray* m_paPositions;
		NctiRenderPolylineItem* m_keyPolygon;
		NCTI_READ_AND_WRITE_VERSION_FUN(1)
	};
}
#endif