#ifndef NctiDisplayGSketch_H
#define NctiDisplayGSketch_H
#include "NctiDisplayGroup.h"
#include "ncti.h"
#include "dcl_ncti_object.h"
#include "NctiSketchComDefine.h"
#include "ncti_include.h"
namespace NCTI
{
	class NctiDisplayDocSketch;
	class NctiDisplaySketchObject;
	class NctiDisplayWorkPlane;
	class NctiDisplayGModelObject;
	class NctiDisplayDocCustomContainer;
	class NctiRenderGeometryItem;
	class DECL_NCTI_OBJECT NctiDisplayGSketch : public NctiDisplayGroup
	{
		NCTI_DISPLAYOBJECT_FUNCTIONS(NctiDisplayGSketch)
	public:
		void Init(NctiDisplayDocSketch* i_pDocSketch);
		virtual ~NctiDisplayGSketch();
		virtual bool PreSelectHighlight(NctiRenderGeometryItem* i_lKey, bool i_bHighlight);
		virtual EnumNctiDoCallbackStatus Callback(NctiBaseView* i_pBaseView, EnumNctiDoCallbackType i_eType, NctiDisplayObject* i_pDoVariable);
		void Compress(int)override;
		void UnCompress(int)override;
		virtual EnumNctiResult ActivateData(NctiDisplayDocCustomContainer* i_pSDDisplayDocCustomContainer, const std::vector<NCTI_MODEL_TAG>& i_ModelBodyVec);
		NctiDisplayDocSketch* GetDocSketch();
		EnumNctiResult GetWorkPlane(NctiDisplayWorkPlane*& o_pDoWorkPlane);
		EnumNctiResult Activate();
		EnumNctiResult Inactivate();
		void UpdateProfile();
		EnumNctiResult CreateModelBody(NCTI_MODEL_TAG& i_pBody, NctiDisplayDocCustomContainer* i_pDocCustomContaine, bool i_bUniteOnly = false);
		void UpdateCoordinate();
		bool IsEnclosed(NctiDisplayObject* i_pNewDo);
		NctiTransf GetSketchTransf();
		virtual void TransformPosition(const NctiTransf& i_cTrans);
		NctiRenderSegmentItem* GetkeyProfile() { return m_keyProfile; }
	private:
		NctiDisplayDocSketch* m_pOwnerDoc;
		NctiDisplaySketchObject* m_pActiveSketchObject;
		Ncti_Long m_pActiveSketchObjectIndex;
		NctiRenderSegmentItem* m_keyProfile;
		Ncti_Boolean m_bActive;
	private:
		std::vector<NctiMeshPacked> m_MeshPackedEdgeVec;
		std::vector<std::vector<Ncti_Float>> m_FloatVecVec;
		Ncti_Boolean m_PackedIsSameEdge;
	private:
		NCTI_READ_AND_WRITE_VERSION_FUN(1)
	public:
		void CompressEdge();
		void UnCompressEdge();
	};
}
#endif