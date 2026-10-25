#ifndef NctiShortcutKeyOperating_H
#define NctiShortcutKeyOperating_H
#include "dcl_ncti_pubfun.h"
#include <functional>
namespace NCTI
{
	using NormalCallback = std::function<void()>;
	class DECL_NCTI_PUBFUN NctiShortcutKeyOperating
	{
	public:
		NctiShortcutKeyOperating();
		virtual ~NctiShortcutKeyOperating();
	public:
		static void SetNewFileFun(NormalCallback fun) { m_NewFileCallback = fun; }
		static void RunNewFileFun();
		static void SetOpenFileFun(NormalCallback fun) { m_OpenFileCallback = fun; }
		static void RunOpenFileFun();
		static void SetSaveFileFun(NormalCallback fun) { m_SaveFileCallback = fun; }
		static void RunSaveFileFun();
	private:
		static NormalCallback m_NewFileCallback;
		static NormalCallback m_OpenFileCallback;
		static NormalCallback m_SaveFileCallback;
	};
}
#endif
