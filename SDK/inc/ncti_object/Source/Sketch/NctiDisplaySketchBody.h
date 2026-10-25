#ifndef NctiDisplaySketchBody_H
#define NctiDisplaySketchBody_H
#include "NctiDisplayModelBody.h"
#include "dcl_ncti_object.h"
namespace NCTI
{
	class DECL_NCTI_OBJECT NctiDisplaySketchBody : public NctiDisplayModelBody
	{
		NCTI_DISPLAYOBJECT_FUNCTIONS(NctiDisplaySketchBody)
	public:
		virtual ~NctiDisplaySketchBody();
		virtual void Init();
	};
}
#endif
