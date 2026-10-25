#ifndef NctiCommandExtrude_H
#define NctiCommandExtrude_H
#include "dcl_ncti_sketch.h"
#include "NctiRegComBase.h"


namespace NCTI
{
	class NctiDisplayGExtrude;
	class NctiArgumentObject;
	class NctiDisplayGSketch;
	class DECL_NCTI_SKETCH NctiCommandExtrude : public NctiRegComBase
	{
		NCTI_COMMAND_FUNCTIONS(NctiCommandExtrude)
	public:
		virtual ~NctiCommandExtrude();
		EnumNctiResult Activate(NctiDisplayObject* i_pDoTarget) override; 
		EnumNctiResult DeActivate() override;
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
		NctiDisplayGExtrude* m_pDoGExtrude;
		NctiDisplayGSketch* m_pDoGSketch;
		double	m_dOldHeight;
		bool	m_bOldReverse;
		bool	m_bOldRemove;
		bool	m_bOldBothSide;
		bool	m_bOldUseAngle;
		double	m_dOldAngle;
	};

}

#endif