#ifndef NCTI_PY_PRINT_DEMO_H
#define NCTI_PY_PRINT_DEMO_H

#include "NctiPyObjectDemo.h"

namespace NCTI {
class NctiPythonInterfaceDemo;

/**
 * @brief Python脚本测试 - 拓展新的Python类型(NctiPyPrintDemo)
 * @details 该类演示了如何扩展新的Python类型，提供基本的打印功能
 * 
 * @code{.py}
 * DEMO = importlib.import_module("ncti_python_demo")
 * demo = DEMO.DemoPrint(1,2)
 * demo.A = 3
 * xx = demo.A
 * print(xx)
 * print(demo)
 * @endcode
 * 
 * @ingroup PythonDemo
 */

/**
 * @brief Python打印演示结构体
 * @details 继承自PyObject_HEAD，包含两个浮点数成员变量用于演示
 */
typedef struct
{
    PyObject_HEAD 
    Ncti_Double a; ///< 浮点数A
    Ncti_Double b; ///< 浮点数B
} NctiPyPrintDemoStr;

/**
 * @brief Python打印演示类
 * @details 继承自[NctiPyObjectDemo]，用于演示Python扩展类型的实现
 */
class NctiPyPrintDemo : public NctiPyObjectDemo
{
public:
    /**
     * @brief 构造函数
     * @param i_pPythonInterface Python接口指针
     */
    NctiPyPrintDemo(NctiPythonInterfaceDemo* i_pPythonInterface);

    /**
     * @brief 析构函数
     */
    virtual ~NctiPyPrintDemo();

public:
    /**
     * @brief 初始化函数
     * @details 初始化Python类型对象及相关属性和方法
     */
    virtual void Init();

public:
    /**
     * @brief Python对象创建函数
     * @param i_type Python类型对象
     * @param i_args 参数元组
     * @param i_kwds 关键字参数字典
     * @return 新创建的Python对象
     */
    static PyObject* NctiPyPrintDemo_new(PyTypeObject* i_type, PyObject* i_args, PyObject* i_kwds);

    /**
     * @brief 获取属性A的值
     * @param i_self 对象实例指针
     * @param i_closure 闭包参数
     * @return 属性A的值
     */
    static PyObject* GetA(NctiPyPrintDemoStr* i_self, void* i_closure);

    /**
     * @brief 设置属性A的值
     * @param i_self 对象实例指针
     * @param i_value 要设置的值
     * @param i_closure 闭包参数
     * @return 设置结果
     */
    static Ncti_Integer SetA(NctiPyPrintDemoStr* i_self, PyObject* i_value, void* i_closure);

    /**
     * @brief 获取属性B的值
     * @param i_self 对象实例指针
     * @param i_closure 闭包参数
     * @return 属性B的值
     */
    static PyObject* GetB(NctiPyPrintDemoStr* i_self, void* i_closure);

    /**
     * @brief 设置属性B的值
     * @param i_self 对象实例指针
     * @param i_value 要设置的值
     * @param i_closure 闭包参数
     * @return 设置结果
     */
    static Ncti_Integer SetB(NctiPyPrintDemoStr* i_self, PyObject* i_value, void* i_closure);

    /**
     * @brief 打印对象内容
     * @param i_self 对象实例指针
     * @return 表示对象内容的Python字符串
     */
    static PyObject* print(NctiPyPrintDemoStr* i_self);
};
} // namespace NCTI

#endif //!NCTI_PY_PRINT_DEMO_H