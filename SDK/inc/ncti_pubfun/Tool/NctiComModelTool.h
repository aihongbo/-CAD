#ifndef NctiComModelTool_H
#define NctiComModelTool_H
#include "dcl_ncti_pubfun.h"
#include "ncti_base.h"
#include <functional>
#include <vector>
#include <map>
#include <string>

#define Create_Model_Key_Name "NCTIModelData"
namespace NCTI
{
	class NctiDocument;
	class NctiArgumentObject;
	using BoolCallback = std::function<bool(NctiDocument*, const std::string)>;
	using myBoolCallBack = std::function<bool(NctiDocument*, NctiArgumentObject*)>;
	class DECL_NCTI_PUBFUN NctiComModelTool
	{
	public:
		static void SetUpdateModelViewFun(BoolCallback fun) { m_UpdateModelView = fun; }
		static bool RunUpdateModelViewFun(NctiDocument* pDoc, const std::string json);

		static void SetUpdateScriptModelViewFun(myBoolCallBack fun) { m_UpdateScriptModelView = fun; }
		static bool RunUpdateScriptModelViewFun(NctiDocument* pDoc, NctiArgumentObject* argumentObject);
	private:
		static BoolCallback m_UpdateModelView;

		static myBoolCallBack m_UpdateScriptModelView;
	};
}
#endif
