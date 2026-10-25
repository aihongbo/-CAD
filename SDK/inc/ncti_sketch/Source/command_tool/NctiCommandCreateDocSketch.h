#ifndef NctiCommandCreateDocSketch_H
#define NctiCommandCreateDocSketch_H

#include "NctiCommand.h"
#include "NctiDisplayWorkPlane.h"

#include "dcl_ncti_sketch.h"
#include "NctiCommandWorkPlane.h"

namespace NCTI
{
	class NctiSketchConstrManager;
	class DECL_NCTI_SKETCH NctiCommandCreateDocSketch : public NctiCommandWorkPlane
	{
		NCTI_COMMAND_FUNCTIONS(NctiCommandCreateDocSketch)
	public:
		virtual ~NctiCommandCreateDocSketch();
		EnumNctiResult Activate(NctiDisplayObject* i_pDoTarget) override;
		EnumNctiResult DeActivate() override;
	protected:
		virtual bool check_status_executable() override;
	private:
		NctiSketchConstrManager* m_pConstrMan;
	};
}


#endif
