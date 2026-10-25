#ifndef NctiDisplayGdtDimRadius_H
#define NctiDisplayGdtDimRadius_H
#include "NctiDisplayGdtDimension.h"
#include "dcl_ncti_object.h"
namespace NCTI
{
	class NctiRenderTextItem;
	class NctiRenderPolylineItem;
	class DECL_NCTI_OBJECT NctiDisplayGdtDimRadius : public NctiDisplayGdtDimension
	{
		NCTI_DISPLAYOBJECT_FUNCTIONS(NctiDisplayGdtDimRadius)
	public:
		virtual ~NctiDisplayGdtDimRadius();
		void Init(NctiPosition i_posCenter,
			NctiPosition i_posOnLine,
			NctiPosition* i_pPosText = NULL
		);
		virtual EnumNctiResult ActivateData(NctiDisplayDocCustomContainer* i_pDocCustomContainer, const std::vector<NCTI_MODEL_TAG>& i_ModelBodyVec);
		void SetPositionData(NctiPositionArray& i_cPosArray);
		virtual EnumNctiDimElemType GetDimElemType(NctiRenderGeometryItem* i_segkey);
	protected:
		virtual bool insert_do(NctiRenderSegmentItem* i_pSegment);
	private:
		NctiPosition m_posCenter;
		NctiPosition m_posOnLine;
		NctiPosition* m_pPosText;
		NctiRenderPolylineItem* m_lkeyArrowRadius;
		NctiRenderTextItem* m_lKeyText;
	private:
		NCTI_READ_AND_WRITE_VERSION_FUN(1)

	};
}
#endif