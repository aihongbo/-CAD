#ifndef NCTI_REG_COM_DEMO_PAN_H
#define NCTI_REG_COM_DEMO_PAN_H

#include "ncti_base.h"
#include "NctiRegComBase.h"
#include "NctiComInc.h"
namespace NCTI {
class NctiArgumentObject;

/**
 * @brief Python脚本测试 - 命令中修改对象(平移对象)
 * @details 该命令用于演示如何在命令中修改现有对象，例如平移几何对象
 * 
 * @code{.py}
 * doc.RunCommand("cmd_ncti_create_box", "box", NCTI.Point(0, 0, 0), 10, 20, 30)
 * doc.RunCommand("cmd_ncti_demo_pan")
 * @endcode
 * 
 * @ingroup DemoCommands
 */

/**
 * @brief 平移对象的命令类
 * @details 继承自[NctiRegComBase]的基础命令类，用于演示如何平移现有几何对象
 */
class NctiRegComDemoPan : public NctiRegComBase
{
    NCTI_COMMAND_FUNCTIONS(NctiRegComDemoPan)
public:
    /**
     * @brief 析构函数
     */
    ~NctiRegComDemoPan();

    /**
     * @brief 激活命令
     * @param i_pDoTarget 目标显示对象
     * @return 执行结果
     */
    EnumNctiResult Activate(NctiDisplayObject* i_pDoTarget) override;

    /**
     * @brief 取消激活命令
     * @return 执行结果
     */
    EnumNctiResult DeActivate() override;

protected:
    /**
     * @brief 检查命令是否可执行
     * @return true表示可执行，false表示不可执行
     */
    Ncti_Boolean check_status_executable() override;

public:
    /**
     * @brief 解析Python参数
     * @param i_PyArgsss Python参数对象
     * @return true表示解析成功
     */
    Ncti_Boolean AnalizePyArgsss(PyObject* i_PyArgsss);

    /**
     * @brief 解析UI参数
     * @param i_Argsss UI参数对象
     * @return true表示解析成功
     */
    Ncti_Boolean AnalizeUIArgsss(NctiArgumentObject* i_Argsss);

    /**
     * @brief 解析Python和UI参数
     * @param i_PyArgsss Python参数对象
     * @return true表示解析成功
     */
    Ncti_Boolean AnalizePyAndUI(PyObject* i_PyArgsss);

private:
    NctiDisplayObject* m_object{nullptr}; ///< 目标对象
};
} // namespace NCTI

#endif // !NCTI_REG_COM_DEMO_PAN_H