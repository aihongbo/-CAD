#ifndef NctiDisplayDocSketch_H
#define NctiDisplayDocSketch_H
#include <string.h>
#include "NctiDisplayDocElement.h"
#include "NctiDisplayWorkPlane.h"
#include "ncti.h"
#include "dcl_ncti_object.h"
#include "NctiSketchComDefine.h"
namespace NCTI
{
	class NctiDisplayGSketch;
	class NctiDisplayGFeature;
	class NctiDisplayGrid;
	class NctiDisplaySketchRect;
	class NctiDisplaySketchDot;
	class NctiDisplaySketchCenterLine;
	class NctiDisplaySketchCircle;
	class NctiDisplaySketchPolygon;
	class NctiDisplaySketchPolyline;
	class NctiDisplaySketchLine;
	class NctiDisplaySketchArc;
	class NctiDisplaySketchTan2Circles;
	class NctiDisplaySketchEllipse;
	class NctiDisplaySketchSpline;
	class NctiPositionArray;
	class NctiDisplayGFeature;
	class NctiDisplayGModelObject;
	class NctiDisplaySketchObject;
	class NctiDisplaySketchBody;
	class NctiSketchConstrManager;
	class DECL_NCTI_OBJECT NctiDisplayDocSketch : public NctiDisplayDocElement
	{
		NCTI_DISPLAYOBJECT_FUNCTIONS(NctiDisplayDocSketch)
	public:
		virtual ~NctiDisplayDocSketch();
		void Init();
		virtual void GetTreeText(char* i_psIndent, char* o_psText);
		virtual int GetAllDisplayGroup(NctiDisplayObjectList* o_pDoGroupList);
		virtual EnumNctiResult ActivateData(NctiDisplayDocCustomContainer* i_pDocCustomContainer, const std::vector<NCTI_MODEL_TAG>& i_ModelBodyVec);
		virtual EnumNctiDoCallbackStatus Callback(NctiBaseView* i_pBaseView, EnumNctiDoCallbackType i_eType, NctiDisplayObject* i_pDoCaller);
		EnumNctiResult AddNewSketch(NctiDisplayWorkPlane* i_pDoWorkPlane);
		EnumNctiResult OpenSketch(NctiDisplayGSketch* i_pNewActiveSketch);
		EnumNctiResult CloseSketch();
		NctiDisplayGSketch* GetActiveSketch();
		EnumNctiResult UpdateShape();
		EnumNctiResult AddSolidFeature(NctiDisplayGFeature* i_pDoFeature, NctiDisplayGSketch* i_pDoGSketch);
		EnumNctiResult CreateModelBody(NCTI_MODEL_TAG& i_pDoBodyCreated, NctiDisplayDocCustomContainer* i_pDocCusContainer);
		void EnableUpdateShape();
		void DisableUpdateShape();
		bool GetUpdateShape();
		int	GetWorkPlanes(NctiDisplayObjectList* o_pDoWorkPlanes);
		NctiDisplayGrid* GetDisplayInputGrid();
		EnumNctiResult CreateSketchRect(NctiPosition& i_pos1, NctiPosition& i_pos2, NctiDisplaySketchRect*& o_pDoSketchRect);
		EnumNctiResult CreateSketchCenterLine(NctiPosition& i_pos1, NctiPosition& i_pos2, NctiDisplaySketchCenterLine*& o_pDoSketchCenterLine);
		EnumNctiResult CreateSketchCircle(NctiPosition& i_pos1, NctiPosition& i_pos2, bool bDiaMode, NctiDisplaySketchCircle*& o_pDoSketchCircle);
		EnumNctiResult CreateSketchLine(NctiPosition& i_pos1, NctiPosition& i_pos2, NctiDisplaySketchLine*& o_pDoSketchLine);
		EnumNctiResult CreateSketchPolyline(NctiPositionArray* i_aPosArray, NctiDisplaySketchPolyline*& o_pDoSketchPolyline);
		EnumNctiResult CreateSketchDot(NctiPosition& i_pos, NctiDisplaySketchDot*& o_pDoSketchDot);
		EnumNctiResult CreateSketchPolygon(NctiPositionArray* i_pPosArray, NctiDisplaySketchPolygon*& o_pDoSketchPolyon);
		EnumNctiResult CreateSketchEllipse(NctiPositionArray* i_aPosArray, NctiDisplaySketchEllipse*& o_pDoSketchEllipse);
		EnumNctiResult CreateSketchTan2Circles(NctiPosition& i_posCenter1, NctiPosition& i_posOnCircle1, NctiPosition& i_posCenter2, NctiPosition& i_posOnCircle2, NctiDisplaySketchTan2Circles*& o_pDoSketchTan2Circles);
		EnumNctiResult CreateSketchArc(NctiPosition& i_posOnArc1, NctiPosition& i_posOnArc2, NctiPosition& i_posOnArc3, NctiDisplaySketchArc*& o_pDoSketchArc, bool i_bAngleMode);
		EnumNctiResult CreateSketchSpline(NctiPositionArray* i_pPosArray, NctiDisplaySketchSpline*& o_pDoSketchSpline);
		EnumNctiResult ProcessSketchGroup(NctiDisplayObject* i_pDoSketchObjOrGroup);
		NctiDisplayDocCustomContainer* GetDocModelContainer();
		NctiSketchConstrManager* GetSketchConstrMananger();
		virtual void UpdateSketch(NctiDisplayDocCustomContainer* i_pDocCustomContainer);
	protected:
		EnumNctiResult find_chain_sketch_curves(NctiDisplaySketchObject* i_pDo, NctiDisplayObjectList* o_pDoList);
		EnumNctiResult get_sketch_curve_end_positions(NctiDisplaySketchObject* o_pDo, NctiPosition& o_start_pos, NctiPosition& o_end_pos);
		EnumNctiResult find_intersection_sketch_curves(NctiDisplayObjectList* o_pChainOfSketchCurveList);
	private:
		NctiDisplayGSketch* m_pActiveSketch;
		Ncti_Long m_pActiveSketchIndex;
		bool	m_bUpdateShape;
		bool m_bUseSketchContainer;
		bool m_bHlrStatus;
		Ncti_Boolean m_bActive;
		NctiDisplaySketchBody* m_SketchResult;
		Ncti_Long m_SketchResultIndex;
	public:
		NctiDisplaySketchBody* GetSketchResult() { return m_SketchResult; }
	private:
		NCTI_READ_AND_WRITE_VERSION_FUN(1)
	};

}

#endif