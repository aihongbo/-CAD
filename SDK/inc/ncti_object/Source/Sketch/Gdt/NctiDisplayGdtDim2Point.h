#ifndef NctiDisplayGdtDim2Point_H
#define NctiDisplayGdtDim2Point_H
#include "NctiSketchComDefine.h"
#include "dcl_ncti_object.h"
#include "NctiPositionArray.h"
#include "NctiDisplayGdtDimension.h"
namespace NCTI
{
    class NctiRenderTextItem;
    class NctiRenderPolylineItem;
	class DECL_NCTI_OBJECT NctiDisplayGdtDim2Point : public NctiDisplayGdtDimension
	{
		NCTI_DISPLAYOBJECT_FUNCTIONS(NctiDisplayGdtDim2Point)
	public:
		virtual ~NctiDisplayGdtDim2Point();
		void Init(const NctiPosition& i_posStart/*dim line start*/,
			const NctiPosition& i_posEnd/*dim line end*/,
			NctiPosition* i_pPosDimLine = NULL,
			bool i_bFrontDirection = false,
			NctiUnitVector* i_pUVecExtLineDir = NULL/*extension line direction*/,
			const char* i_pszText = NULL);
		virtual EnumNctiResult ActivateData(NctiDisplayDocCustomContainer* i_pDocCustomContainer, const std::vector<NCTI_MODEL_TAG>& i_ModelBodyVec);
		virtual EnumNctiDoCallbackStatus Callback(NctiBaseView* i_pBaseView, EnumNctiDoCallbackType i_eType, NctiDisplayObject* i_pDoCaller);
		virtual EnumNctiDimElemType GetDimElemType(NctiRenderGeometryItem* i_segkey);
		void GetValueForCreateMeasurLine(NctiPosition i_posBase,
			NctiPosition& o_posDimStart,
			NctiPosition& o_posDimEnd,
			NctiPosition& o_posSubStart,
			NctiPosition& o_posSubEnd);
		void SetPositionData(NctiPositionArray& i_cPosArray);
		bool IsModifiedMeasureLine() { return m_bModifiedMeasureLine; };
		NctiPosition GetDimLinePosition() { return m_posDimLine; };
		void SetDimLinePosition(NctiPosition& i_posDimLine) { m_posDimLine = i_posDimLine; };
	protected:
		virtual bool insert_do(NctiRenderSegmentItem* pSegment);
	private:
		NctiPosition m_posStart;
		NctiPosition m_posEnd;
		NctiUnitVector m_uvecMeasurDir;
		NctiPosition m_posDimLine;

		NctiUnitVector* m_pUVecExtLineDir;
        NctiRenderTextItem* m_lKeyText;
		NctiRenderPolylineItem* m_lKeyArrowLine;
		EnumNctiDimArrowDirection m_eArrowDirection;
		EnumNctiDimTextPosition m_eTextPosition;

		bool m_bModifiedMeasureLine;
	private:
		NCTI_READ_AND_WRITE_VERSION_FUN(1)
	};
}
#endif