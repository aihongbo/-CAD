#ifndef NctiPyVector_H
#define NctiPyVector_H
#include "NctiPyObject.h"
namespace NCTI
{
	typedef struct {
		PyObject_HEAD
		Ncti_Double x;
		Ncti_Double y;
		Ncti_Double z;
	} NctiPyVectorStr;
	class NctiPyVector : public NctiPyObject
	{
	public:
		virtual void Init();
	public:
		static PyObject* NctiPyVector_new(PyTypeObject* i_type, PyObject* i_args, PyObject* i_kwds);
		static PyObject* print(NctiPyVectorStr* i_self);
		static PyObject* GetX(NctiPyVectorStr* i_self, void* i_closure);
		static Ncti_Integer SetX(NctiPyVectorStr* i_self, PyObject* i_value, void* i_closure);
		static PyObject* GetY(NctiPyVectorStr* i_self, void* i_closure);
		static Ncti_Integer SetY(NctiPyVectorStr* i_self, PyObject* i_value, void* i_closure);
		static PyObject* GetZ(NctiPyVectorStr* i_self, void* i_closure);
		static Ncti_Integer SetZ(NctiPyVectorStr* i_self, PyObject* i_value, void* i_closure);
	};
}
#endif
