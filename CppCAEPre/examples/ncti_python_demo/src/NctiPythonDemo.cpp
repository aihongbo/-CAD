#include "NctiPythonDemo.h"
#include "NctiPythonInterfaceDemo.h"

using namespace NCTI;

/**
* @brief Python示例函数
* @param self Python模块对象指针
* @param args 函数参数，包含一个字符串参数
* @return None
* @details 此函数接收一个字符串参数name，并打印"Hello, %s!"的问候信息
*/
static PyObject* example_hello(PyObject* self, PyObject* args)
{
    const char* name;
    if (!PyArg_ParseTuple(args, "s", &name)) { return nullptr; }
    
    char ch[256];
    sprintf(ch, "print('Hello, %s!')", name);
    PyRun_SimpleString(ch);

    Py_RETURN_NONE;
}

/**
* @brief Python Method 定义
*/
static PyMethodDef example_methods[] = {
    // The first property is the name exposed to Python, hello
    // The second is the C++ function with the implementation
    {"hello", example_hello, METH_VARARGS, "Say hello."},

    // Terminate the array with an object containing nulls
    {nullptr, nullptr, 0, nullptr}};

/**
* @brief Python Module 定义
* @details 通过 PyModuleDef 结构体定义 Python 模块的结构和行为，
* 提供模块的元数据和模块级别的定义，如模块名、模块文档字符串、模块保持状态、以及模块中包含的函数和初始化函数等。
*/
static struct PyModuleDef Demo_Module = {
    PyModuleDef_HEAD_INIT,
    "DEMO",        // Module name to use with Python import statements
    "DEMO module", // Module description
    -1,
    example_methods // Structure that defines the methods of the module
};

#ifdef _MSC_VER
PyMODINIT_FUNC PyInit_ncti_python_demo(void)
{
    NctiPythonInterfaceDemo* pNctiPythonInterfaceDemo = NctiPythonInterfaceDemo::instance();

    // PyModule_Create 用于根据 PyModuleDef 结构创建一个新的 Python 模块对象。
    PyObject* pSys = PyModule_Create(&Demo_Module);
    pNctiPythonInterfaceDemo->SetSysPyObject(pSys);
    pNctiPythonInterfaceDemo->InitPyObject();
    return pSys;
}
#else
PyMODINIT_FUNC PyInit_libncti_python(void)
{
    NctiPythonInterfaceDemo* pNctiPythonInterfaceDemo = NctiPythonInterfaceDemo::instance();
    PyObject* pSys                                    = PyModule_Create(&Demo_Module);
    pNctiPythonInterfaceDemo->SetSysPyObject(pSys);
    pNctiPythonInterfaceDemo->InitPyObject();
    return pSys;
}
#endif
