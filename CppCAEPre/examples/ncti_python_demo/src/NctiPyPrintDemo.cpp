#include "NctiPyPrintDemo.h"
#include "floatobject.h"
#include <string>

using namespace NCTI;

NCTI::NctiPyPrintDemo::NctiPyPrintDemo(NctiPythonInterfaceDemo* i_pPythonInterface)
{
    m_PythonInterface = i_pPythonInterface;
}

NCTI::NctiPyPrintDemo::~NctiPyPrintDemo()
{
}

PyObject* NctiPyPrintDemo::print(NctiPyPrintDemoStr* i_self)
{
    std::string ret;
    ret += std::to_string(i_self->a);
    ret += ",";
    ret += std::to_string(i_self->b);
    return PyUnicode_FromString(ret.c_str());
}

Ncti_Integer NctiPyPrintDemo::SetA(NctiPyPrintDemoStr* i_self, PyObject* i_value, void* i_closure)
{
    i_self->a = PyFloat_AsDouble(i_value);
    return 0;
}

PyObject* NctiPyPrintDemo::GetA(NctiPyPrintDemoStr* i_self, void* i_closure)
{
    return PyFloat_FromDouble(i_self->a);
}

Ncti_Integer NctiPyPrintDemo::SetB(NctiPyPrintDemoStr* i_self, PyObject* i_value, void* i_closure)
{
    i_self->b = PyFloat_AsDouble(i_value);
    return 0;
}

PyObject* NctiPyPrintDemo::GetB(NctiPyPrintDemoStr* i_self, void* i_closure)
{
    return PyFloat_FromDouble(i_self->b);
}

PyObject* NctiPyPrintDemo::NctiPyPrintDemo_new(PyTypeObject* i_type, PyObject* i_args, PyObject* i_kwds)
{
    NctiPyPrintDemoStr* self = (NctiPyPrintDemoStr*)i_type->tp_alloc(i_type, 0);
    Py_ssize_t num_argsss    = PyTuple_Size(i_args);
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

void NctiPyPrintDemo::Init()
{
    //att
    {
        PyGetSetDef GetSetDef{};
        GetSetDef.name    = "A";
        GetSetDef.get     = (getter)NctiPyPrintDemo::GetA;
        GetSetDef.set     = (setter)NctiPyPrintDemo::SetA;
        GetSetDef.doc     = "A ATT";
        GetSetDef.closure = nullptr;
        m_AttVec.push_back(GetSetDef);

        GetSetDef.name    = "B";
        GetSetDef.get     = (getter)NctiPyPrintDemo::GetB;
        GetSetDef.set     = (setter)NctiPyPrintDemo::SetB;
        GetSetDef.doc     = "B ATT";
        GetSetDef.closure = nullptr;
        m_AttVec.push_back(GetSetDef);

        GetSetDef = PyGetSetDef{nullptr};
        m_AttVec.push_back(GetSetDef);
    }

    m_TypeObject.ob_base      = PyVarObject_HEAD_INIT(NULL, 0)
    m_TypeObject.tp_name      = "Demo";
    m_TypeObject.tp_basicsize = sizeof(NctiPyPrintDemoStr);
    m_TypeObject.tp_getset    = m_AttVec.data();
    m_TypeObject.tp_new       = (newfunc)NctiPyPrintDemo::NctiPyPrintDemo_new;
    m_TypeObject.tp_str       = (reprfunc)NctiPyPrintDemo::print;
}
