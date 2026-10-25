#ifndef NctiPyPoint_H
#define NctiPyPoint_H
#include "NctiPyObject.h"
namespace NCTI
{
	typedef struct {
		PyObject_HEAD
		Ncti_Double x;
		Ncti_Double y;
		Ncti_Double z;
	} NctiPyPointStr;
	class NctiPyPoint : public NctiPyObject
	{
	public:
		virtual void Init();
	public:
		static PyObject* NctiPyPoint_new(PyTypeObject* i_type, PyObject* i_args, PyObject* i_kwds);
		static PyObject* GetX(NctiPyPointStr* i_self, void* i_closure);
		static Ncti_Integer SetX(NctiPyPointStr* i_self, PyObject* i_value, void* i_closure);
		static PyObject* GetY(NctiPyPointStr* i_self, void* i_closure);
		static Ncti_Integer SetY(NctiPyPointStr* i_self, PyObject* i_value, void* i_closure);
		static PyObject* GetZ(NctiPyPointStr* i_self, void* i_closure);
		static Ncti_Integer SetZ(NctiPyPointStr* i_self, PyObject* i_value, void* i_closure);
		static PyObject* print(NctiPyPointStr* i_self);
	};
}
#endif
