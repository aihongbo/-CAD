#ifndef NctiDisplayWorldPlane_H
#define NctiDisplayWorldPlane_H
#include "NctiDisplayPlane.h"
#include "ncti.h"
#include "dcl_ncti_object.h"
namespace NCTI
{
	class NctiPosition;
	class NctiUnitVector;

	class DECL_NCTI_OBJECT NctiDisplayWorldPlane : public NctiDisplayPlane
	{
		NCTI_DISPLAYOBJECT_FUNCTIONS(NctiDisplayWorldPlane)
			NCTI_DISPLAYOBJECT_REQUIRE_VIEW_UNIT_LENGTH
			NCTI_DISPLAYOBJECT_REQUIRE_INSTANCE_REDRAW

	public:
		enum EnumNctiLocalWorldPlaneType
		{
			XY,
			YZ,
			XZ
		};
		void Init(EnumNctiLocalWorldPlaneType wpt);
		virtual ~NctiDisplayWorldPlane();
		virtual EnumNctiDoCallbackStatus Callback(NctiBaseView* i_pBaseView, EnumNctiDoCallbackType i_eType, NctiDisplayObject* i_pDoCaller);

		EnumNctiLocalWorldPlaneType GetPlaneType() { return m_wpt; };
		virtual NctiTransf	GetTransform();
		void GetCoordinate(NctiPosition& o_cOrigin, NctiUnitVector& o_cXAxis, NctiUnitVector& o_cYAxis);

	private:
		bool insert_do();

	private:
		EnumNctiLocalWorldPlaneType	m_wpt;
	};

}

#endif