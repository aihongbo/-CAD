#ifndef NCTI_PYTHON_DEMO_H
#define NCTI_PYTHON_DEMO_H

#include <Python.h>

/**
 * @brief Python模块初始化示例
 * @details 以下是Python扩展模块的示例实现，包含一个hello函数。
 * 
 * @code{.py}
 * import ncti_python_demo
 * ncti_python_demo.hello("World")
 * @endcode
 * 
 * @ingroup PythonDemo
 */



#ifdef _MSC_VER
/**
 * @brief Python模块初始化函数(Windows版本)
 * @details 作为模块的入口点，用于定义ncti_python_demo模块的初始化函数。
 * @return Python模块对象
 */
PyMODINIT_FUNC PyInit_ncti_python_demo(void);
#else
/**
 * @brief Python模块初始化函数(非Windows版本)
 * @return Python模块对象
 */
PyMODINIT_FUNC PyInit_libncti_python(void);
#endif

#endif //!NCTI_PYTHON_DEMO_H