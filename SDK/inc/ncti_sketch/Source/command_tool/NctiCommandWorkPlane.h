#ifndef NctiCommandWorkPlane_H
#define NctiCommandWorkPlane_H
#include "NctiRegComBase.h"

#include "dcl_ncti_sketch.h"
namespace NCTI
{
	class NctiDisplayGrid;
	class NctiDisplayWorkPlane;
	class DECL_NCTI_SKETCH NctiCommandWorkPlane : public NctiRegComBase
	{
		NCTI_COMMAND_FUNCTIONS(NctiCommandWorkPlane)
	public:
		virtual ~NctiCommandWorkPlane();
		EnumNctiResult Activate(NctiDisplayObject* i_pDoTarget);
		EnumNctiResult DeActivate();
		virtual void ProcessPickPosition(NctiPosition& i_cPickPos);
	protected:
		bool check_value(NctiPosition& i_cOrig, NctiPosition& i_cXPos, NctiPosition& i_cYPos);
		bool compute_axis(NctiPosition& i_cOrig, NctiPosition& i_cXPos, NctiPosition& i_cYPos, NctiUnitVector& o_cUDir, NctiUnitVector& o_cVDir);
		void update_sketch();
		virtual void start_default_tool();
		virtual bool check_status_executable();
	protected:
		NctiDisplayWorkPlane* m_pDoWorkPlane;
		NctiDisplayGrid* m_pDisplayGrid;
		NctiPosition		m_cOld_Origin;
		NctiUnitVector	m_cOld_U_Axis;
		NctiUnitVector	m_cOld_V_Axis;
	};
}
#endif
