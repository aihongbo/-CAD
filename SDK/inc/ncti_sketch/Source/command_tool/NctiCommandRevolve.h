#ifndef NctiCommandRevolve_H
#define NctiCommandRevolve_H
#include "NctiRegComBase.h"
#include "dcl_ncti_sketch.h"

namespace NCTI
{
	class NctiDisplayGRevolve;
	class NctiArgumentObject;
	class NctiDisplayGSketch;
	class DECL_NCTI_SKETCH NctiCommandRevolve : public NctiRegComBase
	{
		NCTI_COMMAND_FUNCTIONS(NctiCommandRevolve)
	public:
		virtual ~NctiCommandRevolve();
		EnumNctiResult Activate(NctiDisplayObject* i_pDoTarget) override;
		EnumNctiResult DeActivate() override;
		bool	IsEditable(NctiDisplayObject* i_pDo);
		void NotifyHistoryEvent();
	protected:
		virtual void start_default_tool() override;
		virtual bool check_status_executable() override;
	public:
		Ncti_Boolean AnalizePyArgsss(void* i_PyArgsss);
		Ncti_Boolean AnalizeUIArgsss(NctiArgumentObject* i_Argsss);
		Ncti_Boolean AnalizePyAndUI(void* i_Argsss);
	protected:
		NctiDisplayObject* m_DisplayObject;
		const Ncti_Char* m_ObjectName;
		NctiDisplayGSketch* m_pDoGSketch;
		NctiDisplayGRevolve* m_pDoGRevolve;
		bool	m_bOldUseAngle;
		double	m_dOldStartAngle;
		double	m_dOldEndAngle;
		bool	m_bOldReverse;
		bool	m_bOldRemove;
	};
}
#endif
