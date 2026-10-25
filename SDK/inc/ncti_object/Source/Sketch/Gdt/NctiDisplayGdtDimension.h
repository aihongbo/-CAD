#ifndef NctiDisplayGdtDimension_H
#define NctiDisplayGdtDimension_H
#include "NctiSketchComDefine.h"
#include "dcl_ncti_object.h"
#include "NctiPositionArray.h"
#include "NctiDisplayGdtObject.h"
namespace NCTI
{
	class NctiPositionArray;
	class NctiRenderSegmentItem;
	class NctiRenderGeometryItem;
	enum EnumNctiDimElemType
	{
		NCTI_DIM_LINE = 1,
		NCTI_DIM_TEXT,
		NCTI_DIM_FAILED
	};

	class DECL_NCTI_OBJECT NctiDisplayGdtDimension : public NctiDisplayGdtObject
	{
		NCTI_DISPLAYOBJECT_FUNCTIONS(NctiDisplayGdtDimension)
	public:
		virtual ~NctiDisplayGdtDimension();
		virtual EnumNctiDoCallbackStatus Callback(NctiBaseView* i_pBaseView, EnumNctiDoCallbackType i_eType, NctiDisplayObject* i_pDoCaller);

		char* GetDimText() { return m_pszDimText; };
		double  GetDimDouble();
		void SetDimText(const char* i_pszNewDimText);
		void UpdateShape(NctiRenderSegmentItem* pSegment); // This is not virtual function.
		virtual EnumNctiDimElemType GetDimElemType(NctiRenderGeometryItem* i_segkey);
		virtual void SetPositionData(NctiPositionArray& i_cPosArray);
		void SetTextColor(EnumNctiColor i_eTextColor) { back_up(); m_eTextColor = i_eTextColor; };
	protected:
		virtual bool insert_do(NctiRenderSegmentItem* pSegment);
		virtual void update_segment(NctiRenderGeometryItem** plKey);
	protected:
		double	m_dMaxDispSize;
		char* m_pszDimText;
		EnumNctiColor m_eTextColor;
		bool m_bFixFrontDirection;
	private:
		NCTI_READ_AND_WRITE_VERSION_FUN(1)
	};
}
#endif