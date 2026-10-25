#ifndef NctiDisplaySketchCurve_H
#define NctiDisplaySketchCurve_H
#include "ncti.h"
#include "dcl_ncti_object.h"
#include "NctiDisplaySketchObject.h"
namespace NCTI
{
	class NctiRenderGeometryItem;
	class DECL_NCTI_OBJECT NctiDisplaySketchCurve : public NctiDisplaySketchObject
	{
		NCTI_DISPLAYOBJECT_FUNCTIONS(NctiDisplaySketchCurve)
	public:
		virtual ~NctiDisplaySketchCurve();
		void Init();

		virtual NctiRenderGeometryItem* GetSketchCurveKey() = 0;
	protected:
		virtual void set_attribute(bool i_bActive);
	private:
		NCTI_READ_AND_WRITE_VERSION_FUN(1)
	};
}
#endif
