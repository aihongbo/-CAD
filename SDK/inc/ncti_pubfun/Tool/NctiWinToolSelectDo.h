#ifndef NctiWinToolSelectDo_H
#define NctiWinToolSelectDo_H
#include "NctiToolSelectDo.h"
#include "dcl_ncti_pubfun.h"
namespace NCTI
{
	class NctiOpSelectDo;
	class NctiDisplayObject;
	class NctiRubberbandScreenRect;
	class NctiDisplayObjectList;
	class DECL_NCTI_PUBFUN NctiWinToolSelectDo : public NctiToolSelectDo
	{
		NCTI_TOOL_FUNCTIONS(NctiWinToolSelectDo)
	public:
		NctiWinToolSelectDo();
		virtual ~NctiWinToolSelectDo();

		EnumNctiResult ProcessContextMenu(EnumNctiMenuProcMode i_eProcMode) override;

	protected:
		//void Inactivate()override;
	};
}
#endif // !NctiToolSelectDo_H
