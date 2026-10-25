#ifndef NctiDisplayGExtrude_H
#define NctiDisplayGExtrude_H
#include "NctiDisplayGFeature.h"
#include "dcl_ncti_object.h"
#include "NctiSketchComDefine.h"
namespace NCTI
{
	class NctiDisplayGdtDim2Point;
	class NctiDisplayDocCustomContainer;
	class NctiRenderSegmentItem;
	class NctiRenderGeometryItem;
	class DECL_NCTI_OBJECT NctiDisplayGExtrude : public NctiDisplayGFeature
	{
		NCTI_DISPLAYOBJECT_FUNCTIONS(NctiDisplayGExtrude)
			NCTI_DISPLAYOBJECT_REQUIRE_VIEW_UNIT_LENGTH
	public:
		virtual ~NctiDisplayGExtrude();
		void Init();
		virtual Ncti_Boolean MoveActualToWork();

		virtual EnumNctiResult ActivateData(NctiDisplayDocCustomContainer* i_pDocCustomContainer, const std::vector<NCTI_MODEL_TAG>& i_ModelBodyVec);
		virtual EnumNctiDoCallbackStatus Callback(NctiBaseView* i_pBaseView, EnumNctiDoCallbackType i_eType, NctiDisplayObject* i_pDoVariable);
		virtual EnumNctiResult CreateModelBody(NCTI_MODEL_TAG& i_pDoBodyCreated, NctiDisplayDocCustomContainer* i_pDocCusContainer) override;
		double GetHeight();
		Ncti_Boolean GetReverse();
		Ncti_Boolean GetBothSide();
		Ncti_Boolean GetUseAngle();
		double GetAngle();
		void SetHeight(double i_dHeight);
		void SetReverse(Ncti_Boolean i_bReverse);
		void SetBothSide(Ncti_Boolean i_bBothSide);
		void SetUseAngle(Ncti_Boolean i_bUseAngle);
		void SetAngle(double i_dAngle);
		void SetEditMode(Ncti_Boolean i_bEdit) { m_bEdit = i_bEdit; };
		Ncti_Boolean IsEditMode() { return m_bEdit; };
		Ncti_Boolean IsMoveHandle() { return m_bMoveHandle; };

	protected:
		void move_handle(NctiBaseView* i_pBaseView);
		void create_handle(NctiBaseView* i_pBaseView, double i_dHeight);
	private:
		Ncti_Boolean	m_bReverse;
		double	m_dHeight;
		Ncti_Boolean	m_bBothSide;
		Ncti_Boolean	m_bUseAngle;
		double  m_dAngle;

		NctiPosition	m_posLocalMiddle;
		Ncti_Boolean			m_bFirstCreate;
		Ncti_Boolean			m_bEdit;
		Ncti_Boolean			m_bMoveHandle;
		NctiRenderSegmentItem* m_lHandleSegKey;
		NctiRenderSegmentItem* m_lDimensionKey;
		NctiRenderGeometryItem* m_lMarkerKey;
		NctiRenderGeometryItem* m_lOppositeMarkerKey;
		double			m_dTempHeight;
		double			m_dDimExtendLength;
		NctiDisplayGdtDim2Point* m_pDim2Point;
	private:
		NCTI_READ_AND_WRITE_VERSION_FUN(1)

	};
}
#endif