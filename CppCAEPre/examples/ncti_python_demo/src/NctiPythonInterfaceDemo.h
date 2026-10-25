#ifndef NCTI_PYTHON_INTERFACE_DEMO_H
#define NCTI_PYTHON_INTERFACE_DEMO_H

#include "NctiPythonFunctionInterface.h"
#include <Python.h>
#include <map>

namespace NCTI {
class NctiPyPrintDemo;
class NctiPyAddDemo;

/**
 * @brief Python接口演示类
 * @details 该类继承自[NctiPythonFunctionInterface]，用于管理Python扩展对象
 * 提供了Python对象的初始化和管理功能
 * 
 * @ingroup PythonDemo
 */

/**
 * @brief Python接口管理类
 * @details 负责管理所有Python扩展对象的创建、初始化和注册
 */
class NctiPythonInterfaceDemo : public NctiPythonFunctionInterface
{
    NCTI_PLUGIN_FUNCTIONS(NctiPythonInterfaceDemo)
public:
    /**
     * @brief 构造函数
     */
    NctiPythonInterfaceDemo();

    /**
     * @brief 析构函数
     */
    virtual ~NctiPythonInterfaceDemo();

    /**
     * @brief 获取单例实例
     * @return 返回NctiPythonInterfaceDemo的单例指针
     */
    static NctiPythonInterfaceDemo* instance();

    /**
     * @brief 初始化Python对象
     * @return 成功返回true，失败返回false
     */
    Ncti_Boolean InitPyObject();

    /**
     * @brief 设置系统Python对象
     * @param i_SysPyObject Python系统对象指针
     */
    void SetSysPyObject(PyObject* i_SysPyObject);

private:
    PyObject* m_SysPyObject{nullptr};        ///< 系统Python对象指针
    NctiPyPrintDemo* m_pyPrintDemo{nullptr}; ///< Python打印演示对象指针
    NctiPyAddDemo* m_pyAddDemo{nullptr};     ///< Python加法演示对象指针
};
} // namespace NCTI

#endif //!NCTI_PYTHON_INTERFACE_DEMO_H