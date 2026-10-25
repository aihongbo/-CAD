#ifndef NctiToolCreateWorkPlane_H
#define NctiToolCreateWorkPlane_H
#include "NctiWinToolSelectDo.h"
#include "dcl_ncti_sketch.h"
#include "NctiUnitVector.h"
namespace NCTI
{
	class NctiDisplayWorkPlane;
	class DECL_NCTI_SKETCH NctiToolCreateWorkPlane : public NctiWinToolSelectDo
	{
	public:
		NctiToolCreateWorkPlane();
		virtual ~NctiToolCreateWorkPlane();
		void SetWorkPlaneInstance(NctiDisplayObject* i_pDoWorkPlane);
		NctiDisplayWorkPlane* GetDisplayWorkPlane();
		NctiDisplayObject* GetWorkPlaneInstance();
		bool GetWorkPlaneByFace(NctiPosition& o_posOrigin, NctiUnitVector& o_uvecAxisU, NctiUnitVector& o_uvecAxisV);
		void ResetWorkPlaneByFace() { m_bWorkPlaneByFace = false; };

	protected:
		EnumNctiResult process_marker(NctiRenderGeometryItem* i_key);
		EnumNctiResult process_shell(NctiRenderGeometryItem* i_key);
		EnumNctiResult process_polyline(NctiRenderGeometryItem* i_key);
		EnumNctiResult process_work_plane(NctiDisplayObject* i_pSelectedWorkPlaneIns);

		virtual void on_l_button_up();
		virtual bool process_left_click_selection();
	private:
		EnumNctiResult create_work_plane(NctiPosition i_cOrigin, NctiUnitVector i_cUAxis, NctiUnitVector i_cVAxis);
	private:
		bool m_bWorkPlaneByFace;
		NctiPosition m_posOrigin;
		NctiUnitVector m_uvecAxisU;
		NctiUnitVector m_uvecAxisV;
		bool m_bDragging;
		NctiDisplayObject* m_pDisplayInsWorkPlane;
	};
}
#endif
