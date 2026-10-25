#include "NctiPythonInterfaceDemo.h"

#ifdef _MSC_VER
#include <Windows.h>
#endif

#include "NctiPyPrintDemo.h"
#include "NctiPyAddDemo.h"
using namespace NCTI;

#define NCTI_OBJ_NAME "NctiPythonInterfaceDemo"
NCTI_PLUGIN_DEF(NctiPythonInterfaceDemo, NctiPythonFunctionInterface, "ncti_plugin_python_demo", NCTI_OBJ_NAME)

NctiPythonInterfaceDemo* g_PythonInterfaceDemo = NCTI_NEW NctiPythonInterfaceDemo();

NCTI::NctiPythonInterfaceDemo::NctiPythonInterfaceDemo()
{
    m_pyPrintDemo = NCTI_NEW NctiPyPrintDemo(this);
    m_pyAddDemo   = NCTI_NEW NctiPyAddDemo(this);
}

NCTI::NctiPythonInterfaceDemo::~NctiPythonInterfaceDemo()
{
    NCTI_DELETE_OBJECT(m_pyPrintDemo)
    NCTI_DELETE_OBJECT(m_pyAddDemo)
}

NCTI::NctiPythonInterfaceDemo* NctiPythonInterfaceDemo::instance()
{
    return g_PythonInterfaceDemo;
}

Ncti_Boolean NctiPythonInterfaceDemo::InitPyObject()
{
    m_pyPrintDemo->Init();
    if (PyType_Ready(m_pyPrintDemo->GetTypeObject()) != 0) {
        return false;
    }
    Py_INCREF(m_pyPrintDemo->GetTypeObject());
    PyModule_AddObject(m_SysPyObject, "DemoPrint", (PyObject*)m_pyPrintDemo->GetTypeObject());

    m_pyAddDemo->Init();
    if (PyType_Ready(m_pyAddDemo->GetTypeObject()) != 0) {
        return false;
    }
    Py_INCREF(m_pyAddDemo->GetTypeObject());
    PyModule_AddObject(m_SysPyObject, "DemoAdd", (PyObject*)m_pyAddDemo->GetTypeObject());
    return true;
}

void NctiPythonInterfaceDemo::SetSysPyObject(PyObject* i_SysPyObject)
{
    m_SysPyObject = i_SysPyObject;
}