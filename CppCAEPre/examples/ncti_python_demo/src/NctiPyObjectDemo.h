#ifndef NCTI_PY_OBJECT_DEMO_H
#define NCTI_PY_OBJECT_DEMO_H

#include "ncti_base.h"
#include <Python.h>
#include <vector>

namespace NCTI {
class NctiPythonInterfaceDemo;

/**
 * @brief Python对象基类
 * @details 该类是所有Python扩展对象的基类，提供了Python类型对象的基本管理功能
 */
class NctiPyObjectDemo : public NCTI_BASE_CLASS
{
public:
    /**
     * @brief 构造函数
     */
    NctiPyObjectDemo();

    /**
     * @brief 析构函数
     */
    virtual ~NctiPyObjectDemo();

public:
    /**
     * @brief 初始化函数
     * @details 初始化Python类型对象及相关属性
     */
    virtual void Init();

public:
    /**
     * @brief 获取类型对象指针
     * @return Python类型对象指针
     */
    PyTypeObject* GetTypeObject();

protected:
    std::vector<PyMethodDef> m_MethodVec;                ///< Python方法数组
    PyTypeObject m_TypeObject;                           ///< Python类型对象
    std::vector<PyGetSetDef> m_AttVec;                   ///< Python属性数组
    NctiPythonInterfaceDemo* m_PythonInterface{nullptr}; ///< Python接口指针
};
} // namespace NCTI

#endif //!NCTI_PY_OBJECT_DEMO_H