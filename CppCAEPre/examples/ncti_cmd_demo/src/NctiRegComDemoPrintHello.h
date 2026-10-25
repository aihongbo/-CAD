#ifndef NCTI_REG_COM_DEMO_PRINT_HELLO_H
#define NCTI_REG_COM_DEMO_PRINT_HELLO_H

#include "ncti_base.h"
#include "NctiRegComBase.h"
#include "NctiComInc.h"
namespace NCTI {
class NctiArgumentObject;

/**
 * @brief Python脚本测试 - 打印"hello"消息
 * @details 该命令用于演示如何在Python脚本中执行简单的命令并打印"hello"消息
 * 
 * @code{.py}
 * doc.RunCommand("cmd_ncti_demo_print_hello")
 * @endcode
 * 
 * @ingroup DemoCommands
 */

/**
 * @brief 打印"hello"消息的命令类
 * @details 继承自[NctiRegComBase]的基础命令类，用于演示简单的命令执行
 */
class NctiRegComDemoPrintHello : public NctiRegComBase
{
    NCTI_COMMAND_FUNCTIONS(NctiRegComDemoPrintHello)
public:
    /**
     * @brief 析构函数
     */
    ~NctiRegComDemoPrintHello();

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

private:
    /**
     * @brief 记录命令信息
     * @return true表示记录成功
     */
    Ncti_Boolean on_command_record_infor() override;

public:
    /**
     * @brief 解析Python参数
     * @param i_PyArgsss Python参数对象
     * @return true表示解析成功
     */
    Ncti_Boolean AnalizePyArgsss(PyObject* i_PyArgsss);

    /**
     * @brief 解析UI参数
     * @param pArgument UI参数对象
     * @return true表示解析成功
     */
    Ncti_Boolean AnalizeUIArgsss(NctiArgumentObject* pArgument);

    /**
     * @brief 解析Python和UI参数
     * @param i_PyArgsss Python参数对象
     * @return true表示解析成功
     */
    Ncti_Boolean AnalizePyAndUI(PyObject* i_PyArgsss);
};
} // namespace NCTI

#endif // !NCTI_REG_COM_DEMO_PRINT_HELLO_H