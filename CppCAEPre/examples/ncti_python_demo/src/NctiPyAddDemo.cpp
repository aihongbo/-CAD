#include "NctiPyAddDemo.h"
#include "floatobject.h"
#include <string>

using namespace NCTI;

NCTI::NctiPyAddDemo::NctiPyAddDemo(NctiPythonInterfaceDemo* i_pPythonInterface)
{
    m_PythonInterface = i_pPythonInterface;
}

NCTI::NctiPyAddDemo::~NctiPyAddDemo()
{
}

PyObject* NctiPyAddDemo::print(NctiPyAddDemoStr* i_self)
{
    std::string ret;
    ret += std::to_string(i_self->a);
    ret += ",";
    ret += std::to_string(i_self->b);
    return PyUnicode_FromString(ret.c_str());
}

Ncti_Integer NctiPyAddDemo::SetA(NctiPyAddDemoStr* i_self, PyObject* i_value, void* i_closure)
{
    i_self->a = PyFloat_AsDouble(i_value);
    return 0;
}

PyObject* NctiPyAddDemo::GetA(NctiPyAddDemoStr* i_self, void* i_closure)
{
    return PyFloat_FromDouble(i_self->a);
}

Ncti_Integer NctiPyAddDemo::SetB(NctiPyAddDemoStr* i_self, PyObject* i_value, void* i_closure)
{
    i_self->b = PyFloat_AsDouble(i_value);
    return 0;
}

PyObject* NctiPyAddDemo::GetB(NctiPyAddDemoStr* i_self, void* i_closure)
{
    return PyFloat_FromDouble(i_self->b);
}

PyObject* NctiPyAddDemo::NctiPyAddDemo_new(PyTypeObject* i_type, PyObject* i_args, PyObject* i_kwds)
{
    NctiPyAddDemoStr* self = (NctiPyAddDemoStr*)i_type->tp_alloc(i_type, 0);
    Py_ssize_t num_argsss  = PyTuple_Size(i_args);
    if (num_argsss == 2) {
        PyObject* argData0 = PyTuple_GetItem(i_args, 0);
        PyObject* argData1 = PyTuple_GetItem(i_args, 1);

        if ((PyFloat_Check(argData0) || PyLong_Check(argData0))
            && (PyFloat_Check(argData1) || PyLong_Check(argData1))) {
            self->a = PyFloat_AsDouble(argData0);
            self->b = PyFloat_AsDouble(argData1);
        }
    }
    else {
        if (self != NULL) {
            self->a = 0.0f;
            self->b = 0.0f;
        }
    }

    return (PyObject*)self;
}

void NctiPyAddDemo::Init()
{
    //att
    {
        PyGetSetDef GetSetDef{};
        GetSetDef.name    = "A";
        GetSetDef.get     = (getter)NctiPyAddDemo::GetA;
        GetSetDef.set     = (setter)NctiPyAddDemo::SetA;
        GetSetDef.doc     = "A ATT";
        GetSetDef.closure = nullptr;
        m_AttVec.push_back(GetSetDef);

        GetSetDef.name    = "B";
        GetSetDef.get     = (getter)NctiPyAddDemo::GetB;
        GetSetDef.set     = (setter)NctiPyAddDemo::SetB;
        GetSetDef.doc     = "B ATT";
        GetSetDef.closure = nullptr;
        m_AttVec.push_back(GetSetDef);

        GetSetDef = PyGetSetDef{nullptr};
        m_AttVec.push_back(GetSetDef);
    }

    //注册新的Python函数
    //method
    {
        PyMethodDef MethodDef{};
        MethodDef.ml_name  = "Add";
        MethodDef.ml_meth  = NctiPyAddDemo::Add;
        MethodDef.ml_flags = METH_VARARGS;
        MethodDef.ml_doc   = "Add Function";
        m_MethodVec.push_back(MethodDef);

        MethodDef.ml_name  = nullptr;
        MethodDef.ml_meth  = nullptr;
        MethodDef.ml_flags = 0;
        MethodDef.ml_doc   = nullptr;
        m_MethodVec.push_back(MethodDef);
    }

    m_TypeObject.ob_base      = PyVarObject_HEAD_INIT(NULL, 0)
    m_TypeObject.tp_name      = "Demo";
    m_TypeObject.tp_basicsize = sizeof(NctiPyAddDemoStr);
    m_TypeObject.tp_getset    = m_AttVec.data();
    m_TypeObject.tp_methods   = m_MethodVec.data();
    m_TypeObject.tp_new       = (newfunc)NctiPyAddDemo::NctiPyAddDemo_new;
    m_TypeObject.tp_str       = (reprfunc)NctiPyAddDemo::print;
}

PyObject* NctiPyAddDemo::Add(PyObject* i_self, PyObject* i_args)
{
    NctiPyAddDemoStr* self = (NctiPyAddDemoStr*)i_self;
    double dResult         = 0;
    if (!self) {
        PyErr_SetString(PyExc_RuntimeError, "Invalid object reference");
        return nullptr;
    }

    if (!i_args || PyTuple_Size(i_args) == 0) {
        // i_args为空或没有参数时，使用内置属性
        dResult = self->a + self->b;
    }
    else {
        int a, b;
        if (!PyArg_ParseTuple(i_args, "ii", &a, &b)) { 
            return nullptr; 
        }
        dResult = a + b;
    }
    return PyFloat_FromDouble(dResult);
}
