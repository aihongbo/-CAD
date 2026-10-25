#ifndef NctiPythonTool_H
#define NctiPythonTool_H
#include "dcl_ncti_pubfun.h"
#include "ncti_base.h"
#include <functional>
#include <vector>
#include <map>
#include "NCTIVariant.h"
#include "CallbackInterfaces.h"
namespace NCTI
{
	enum CUSTOMDLGID
	{
		DLGID_MESH_QUALITY = 10001,
		DLGID_FEATURE_TREE= 10002,
		DLGID_COMMON_EDGE = 10003,
		DLGID_ABNORMAL_OBJECT = 10004,
		DLGID_DCM3_ASSEMBLY = 10005
	};

	struct DocImage;
	using DialogCallback = std::function<bool(void* i_args, void* o_args, bool bReturn, void* mianWindow)>;
	using CustomDialogCallback = std::function<bool(void* i_args, void* o_args, bool bReturn,void* mianWindow)>;
	using ProgressCallback = std::function<void(int progress)>;
	using PyObjectToVariantCallback = std::function<std::vector<Ncti_VariantValue>(void* i_args)>;
	using InputStingCallback = std::function<void(const char*)>;
	using ReturnBoolInputStingCallback = std::function<bool(const char*)>;
	using InputStingCallback2 = std::function<void(const char*, std::string&, std::string&)>;
	class DECL_NCTI_PUBFUN NctiPythonTool
	{
	public:
		static void SetDialogCallbackFun(DialogCallback fun, void* mainWindow = nullptr);
		static bool RunGetDialogCallbackFun(void* i_args, void* o_args, bool bReturn);
		static bool CheckDialogCallbackFun();
		static void SetDialogIDs(std::vector<Ncti_Long> dialogIDVec);
		static const std::vector<Ncti_Long>& GetDialogIDs() { return m_DialogIDVec; }
		static bool CheckShowDialog(Ncti_Long id);

		static void SetCustomDialogCallbackFun(CustomDialogCallback fun, void* mainWindow);
		static bool RunGetCustomDialogCallbackFun(void* i_args, void* o_args, bool bReturn);
		static bool CheckCustomDialogCallbackFun();

		static void SetProgressCallbackFun(ProgressCallback fun);
        static void RunProgressCallbackFun(Ncti_Integer progress);
        static bool CheckProgressCallbackFun();

		static void SetPyObjectToVariantCallbackFun(PyObjectToVariantCallback fun);
        static std::vector<Ncti_VariantValue> PyObjectToVariants(void* i_args);

		static void SetRunPythonStringCallbackFun(InputStingCallback fun);
        static void RunPythonString(const char*);

		static void SetInitPyInterpreterCallbackFun(ReturnBoolInputStingCallback fun);
		static bool InitPyInterpreter(const char*);

		static void SetExcuteScriptCallbackFun(InputStingCallback2 fun);
		static void ExcuteScript(const char*, std::string&, std::string&);

		static void InitPyDocument(Ncti_UInteger i_docId);
	public:
		static bool RunAssemblyConsDialog(Ncti_Integer i_docID, Ncti_Integer i_dimType, Ncti_UInteger m_editMode = 0, const char* i_dimObjName = nullptr);

	private:
		static void* m_pMainWindow;
		static DialogCallback m_DialogCallback;
		static std::vector<Ncti_Long> m_DialogIDVec;

		static void* m_mainWindow;
		static CustomDialogCallback m_customDialogCallback;

        static ProgressCallback m_ProgressCallback;
        static PyObjectToVariantCallback m_PyObjectToVariantCallback;
        static InputStingCallback m_RunPythonStringCallback;
        static ReturnBoolInputStingCallback m_RunInitPyInterpreterCallback;
        static InputStingCallback2 m_ExcuteScriptCallback;
	};
}
#endif
