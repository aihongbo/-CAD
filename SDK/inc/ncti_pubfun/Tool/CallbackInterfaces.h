#ifndef CallbackInterfaces_H
#define CallbackInterfaces_H

#include "dcl_ncti_pubfun.h"

#include <vector>
#include <string>
#include <map>
#include "ncti_base.h"
#include "NctiMutex.h"

typedef struct _object PyObject;
struct NCTIExtrudeBoundParam;
struct NCTIPyBodyLoftParam;
namespace NCTI
{
	class NctiTransf;
	class NctiVector;
	class NctiPosition;
	class RGBAColor;
	class NctiDisplayObject;
	struct NctiPyErrorInfo;
	struct PyArgCallbacks {
		//
		Ncti_Integer(*Size)(PyObject* obj);
		Ncti_Boolean(*IsNull)(PyObject* obj);
		Ncti_Boolean(*IsBool)(PyObject* obj);
		Ncti_Boolean(*IsNone)(PyObject* obj, Ncti_Integer index);
		Ncti_Boolean(*IsList)(PyObject* obj);
		Ncti_Boolean(*IsDict)(PyObject* obj);
		Ncti_Boolean(*isDictContains)(PyObject* obj, const char* key);
		Ncti_Boolean(*IsUnicode)(PyObject* obj);
		Ncti_Boolean(*IsNumber)(PyObject* obj);
		Ncti_Boolean(*IsInt)(PyObject* obj);
		Ncti_Boolean(*IsLong)(PyObject* obj);
		Ncti_Boolean(*IsFloat)(PyObject* obj);
		Ncti_Boolean(*IsDouble)(PyObject* obj);
		Ncti_Boolean(*IsCapsule)(PyObject* obj, const char* capsuleName);
		Ncti_Boolean(*CheckType)(PyObject* obj, const char* typeName);
		//
		PyObject* (*GetSysObject)(const char* name);
		PyObject* (*GetImportModule)(const char* name);
		PyObject* (*GetCallObject)(PyObject* callable, PyObject* args);
		//
		PyObject* (*GetTupleItem)(PyObject* obj, Ncti_Integer index);
		PyObject* (*GetListItem)(PyObject* list, Ncti_Integer index);
		PyObject* (*GetDictItem)(PyObject* dict, const char* key);
		PyObject* (*GetDictItemFromPtr)(PyObject* dict, PyObject* pyKey);
		// 遍历字典，pos为遍历游标(初始传0)，返回0表示遍历完成，1表示成功获取key/value；key/value为借用引用，需手动IncRef
		Ncti_Integer(*GetDictNext)(PyObject* dict, Ncti_Pysize& pos, PyObject*& key, PyObject*& value);
		PyObject* (*GetAttr)(PyObject* obj, const char* attrName);//The new object must be released (Py_DECREF)
		Ncti_Integer(*GetListSize)(PyObject* list);
		Ncti_Integer(*GetDictSize)(PyObject* dict);
		PyObject* (*GetDictKeys)(PyObject* dict);
		//
		PyObject* (*NewLongPyObject)(long val);//The new object, manual IncRef is required. 
		PyObject* (*NewDoublePyObject)(double val);//The new object, manual IncRef is required.
		PyObject* (*NewUnicodePyObject)(const char* str);//The new object, manual IncRef is required.
		PyObject* (*NewBuildPyObject)(const char* format, ...);//The new object, manual IncRef is required.
		PyObject* (*NewTuple)(Ncti_Pysize n);//The new object, manual IncRef is required.
		PyObject* (*NewTupleFromList)(PyObject* list);//The new object, manual IncRef is required.
		PyObject* (*NewTupleFromPack)(Ncti_Pysize, ...);//The new object, manual IncRef is required.
		//
		Ncti_Boolean(*GetBool)(PyObject* obj);
		//int8_t(*GetInt8)(PyObject* obj);
		//uint8_t(*GetUInt8)(PyObject* obj);
		//int16_t(*GetInt16)(PyObject* obj);
		//uint16_t(*GetUInt16)(PyObject* obj);
		//int32_t(*GetInt32)(PyObject* obj);
		//uint32_t(*GetUInt32)(PyObject* obj);
		Ncti_LongLong(*GetLongLong)(PyObject* obj);
		Ncti_Size(*GetULongLong)(PyObject* obj);
		Ncti_Integer(*GetInt)(PyObject* obj);
		Ncti_Long(*GetLong)(PyObject* obj);
		//Ncti_Float(*GetFloat)(PyObject* obj);
		Ncti_Double(*GetDouble)(PyObject* obj);
		Ncti_Boolean(*GetDoubleList)(PyObject* obj, std::vector<Ncti_Double>& values);
		// 返回的字符串为Python内部缓冲区的只读指针，生命周期与obj一致，obj存活则有效，不可手动free
		const Ncti_Char* (*GetUnicodeStr)(PyObject* obj);
		//
		Ncti_Boolean(*GetColor)(PyObject* obj, RGBAColor& color);
		Ncti_Boolean(*GetPosition)(PyObject* obj, NctiPosition& pos);
		Ncti_Boolean(*GetVector)(PyObject* obj, NctiVector& vec);
		Ncti_Boolean(*GetTransform)(PyObject* obj, NctiTransf& transf);
		//Ncti_Boolean(*GetExtrudeParam)(PyObject* obj, NCTIExtrudeBoundParam& param);
		//Ncti_Boolean(*GetLoftParam)(PyObject* obj, NCTIPyBodyLoftParam& param);//未实现
		NctiDisplayObject* (*GetDisplayObjectFromCapsule)(PyObject* obj, const char* capsuleName);
		void* (*GetCapsulePointer)(PyObject* obj, const char* capsuleName);
		//
		Ncti_Boolean(*GetDisplayObjectName)(NctiDisplayObject* obj, std::string& name);
		Ncti_Boolean(*GetDisplayObjectNameCStr)(NctiDisplayObject* obj, const char*& name);//name指向的C字符串生命周期与obj一致，obj不销毁则有效
		//
		Ncti_Integer(*TupleSetItem)(PyObject*, Ncti_Pysize, PyObject*);
		//
		void (*IncRef)(PyObject* obj);
		void (*DecRef)(PyObject* obj);
		//
		int (*PyGILState)();
		void (*PyGILPyGILStateReleaseState)(int);
		void* (*PySaveThread)();
		void (*PyRestoreThread)(void*);
		//
		Ncti_Integer(*RunSimpleString)(const char* s);
		Ncti_Integer(*RunSimpleFile)(const char* filename);
		void (*RaiseAndPrintPyError)(const char* s);
		//
		void (*SetError)(NctiPyErrorInfo* err, Ncti_Integer code, Ncti_Integer index, const std::vector<Ncti_Integer>& types);
	};

	class DECL_NCTI_PUBFUN PyObjRef {
	public:
		PyObjRef() : obj_(nullptr) {}
		~PyObjRef();

		// 从新引用构造（不增加引用计数）
		static PyObjRef newRef(PyObject* new_ref);

		// 从借用引用构造（增加引用计数）
		static PyObjRef borrowedRef(PyObject* borrowed);

		static PyObjRef GetAttrFrom(PyObject* obj, const char* name);
		static PyObjRef GetAttrFrom(const PyObjRef& objRef, const char* name);

		PyObjRef(const PyObjRef&) = delete;
		PyObjRef& operator=(const PyObjRef&) = delete;

		// 允许移动
		PyObjRef(PyObjRef&& other) noexcept;
		PyObjRef& operator=(PyObjRef&& other) noexcept;

		PyObject* get() const;
		PyObject* release();

		operator bool() const {
			return obj_ != nullptr;
		}
		operator PyObject* () const {
			return obj_;
		}
		PyObject* operator->() const {
			return obj_;
		}

		PyObjRef GetAttr(const char* name) const;

	private:
		explicit PyObjRef(PyObject* obj, bool incref);
		//explicit PyObjRef(PyObject* obj, const char* name);
		PyObject* obj_;
	};
	class DECL_NCTI_PUBFUN PyArgCallbackManager {
	private:
		static PyArgCallbackManager* instance;
		static NctiMutex cb_mtx;
		PyArgCallbacks callbacks;
		PyArgCallbackManager() = default;
		bool hasCallbacks = false;

	public:
		static PyArgCallbackManager* GetInstance();

		static void Release();

		void RegisterCallbacks(const PyArgCallbacks& cb);

		const PyArgCallbacks& GetCallbacks() const;

		bool HasCallbacks() const { return hasCallbacks; }
	};

#define NctiPyInstance NCTI::PyArgCallbackManager::GetInstance()
#define NctiPyCB NctiPyInstance->GetCallbacks()
#define NctiPyRunSimpleString(s) (NctiPyCB.RunSimpleString((s)))
#define NctiPyRunSimpleFile(filename) (NctiPyCB.RunSimpleFile((filename)))

}

#endif // CallbackInterfaces_H