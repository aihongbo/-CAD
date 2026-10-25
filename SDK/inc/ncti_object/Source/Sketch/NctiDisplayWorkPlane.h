#ifndef NctiDisplayWorkPlane_H
#define NctiDisplayWorkPlane_H
#include "NctiUnitVector.h"
#include "dcl_ncti_object.h"
#include "NctiDisplayPlane.h"

namespace NCTI
{
    class NctiDisplayObject;

	class DECL_NCTI_OBJECT NctiDisplayWorkPlane : public NctiDisplayPlane
	{
		NCTI_DISPLAYOBJECT_FUNCTIONS(NctiDisplayWorkPlane)
	public:
		void Init(NctiPosition i_cOrigin, NctiVector i_cXAxis, NctiVector i_YAxis);
		virtual ~NctiDisplayWorkPlane();
		virtual EnumNctiResult ActivateData(NctiDisplayDocCustomContainer* i_pDocCustomContainer, const std::vector<NCTI_MODEL_TAG>& i_ModelBodyVec);
		virtual EnumNctiDoCallbackStatus Callback(NctiBaseView* i_pBaseView, EnumNctiDoCallbackType i_eType, NctiDisplayObject* i_pDoCaller);
		virtual EnumNctiResult UpdateDisplay();
		virtual NctiTransf	GetTransform();
		bool IsValid();
		virtual void GetCoordinate(NctiPosition& o_cOrigin, NctiUnitVector& o_cXAxis, NctiUnitVector& o_cYAxis);
		virtual void SetCoordinate(const NctiPosition& i_cOrigin, const NctiUnitVector& i_cXAxis, const NctiUnitVector& i_cYAxis);
		EnumNctiResult	StartEditing();
		EnumNctiResult	EndEditing();
		bool IsDragging() { return m_bDragging; }

        void GetCamera(NctiPosition& pos, NctiPosition& tar, NctiVector& up)const;

	protected:
		NctiPosition m_cOrigin;
		NctiUnitVector m_cXAxis;
		NctiUnitVector m_cYAxis;
		bool m_bEditing;
		NctiPosition* m_pPosFirst;
		NctiPosition m_cPlaneOrigin;
		NctiUnitVector m_cPlaneNormal;
		bool m_bDragging;
		NctiVector m_cOffset;
		NctiVector m_cShapeOffset;
	private:
		void Draw();
		NCTI_READ_AND_WRITE_VERSION_FUN(1)
	};
}
#endif