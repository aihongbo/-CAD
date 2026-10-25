#ifndef NctiToolCreateRevolve_H
#define NctiToolCreateRevolve_H
#include "NctiToolSelectDo.h"
#include "dcl_ncti_sketch.h"
namespace NCTI
{
	class NctiDisplayGSketch;
	class NctiDisplayGRevolve;
	class NctiRubberbandRevolve;
	class DECL_NCTI_SKETCH NctiToolCreateRevolve : public NctiToolSelectDo
	{
	public:
		NctiToolCreateRevolve(NctiDisplayGRevolve* i_pDoRevolve);
		virtual ~NctiToolCreateRevolve();
		void RedrawRubberband(bool i_bUseAngle,
			double i_dStartAngle,
			double i_dEndAngle,
			bool i_bReverse);
	private:
		NctiRubberbandRevolve* m_pRubberbandRevolve;
		NctiDisplayGSketch* m_pTargetSketch;
	};
}
#endif
