#ifndef NCTI_REG_COM_DEMO_CANCEL_H
#define NCTI_REG_COM_DEMO_CANCEL_H

#include "ncti_base.h"
#include "NctiRegComBase.h"
#include "NctiComInc.h"
/**
 * @brief Python脚本测试 - 命令的取消
 * @details 该命令用于测试Python脚本中命令的取消功能。
 * 
 * @code{.py}
 * doc.RunCommand("cmd_ncti_demo_cancel")
 * @endcode
 * 
 * @ingroup DemoCommands
 */
namespace NCTI {
class NctiArgumentObject;

/**
 * @brief 命令取消演示类
 * @details 继承自[NctiRegComBase]的基础命令类，用于演示如何处理命令的取消操作
 */
class NctiRegDemoComCancel : public NctiRegComBase
{
    NCTI_COMMAND_FUNCTIONS(NctiRegDemoComCancel)
public:
    /**
	 * @brief 析构函数
	 * @details 清理资源并释放由此类实例分配的任何内存
	 */
    ~NctiRegDemoComCancel();

public:
    /**
	 * @brief 激活命令
	 * @details 激活当前命令并准备执行
	 * 
	 * @param i_pDoTarget 目标显示对象，表示命令作用的对象
	 * @return 执行结果，返回EnumNctiResult类型的值表示激活操作的结果
	 */
    EnumNctiResult Activate(NctiDisplayObject* i_pDoTarget) override;

    /**
	 * @brief 取消激活命令
	 * @details 取消已经激活的命令，停止其执行
	 * 
	 * @return 执行结果，返回EnumNctiResult类型的值表示取消操作的结果
	 */
    EnumNctiResult DeActivate() override;

protected:
    /**
	 * @brief 检查命令是否可执行
	 * @details 验证当前状态是否允许命令执行
	 * 
	 * @return Ncti_Boolean true表示命令可以执行，false表示不可执行
	 */
    Ncti_Boolean check_status_executable() override;

private:
    /**
	 * @brief 记录命令信息
	 * @details 将命令的执行信息保存到日志或其它存储中
	 * 
	 * @return Ncti_Boolean true表示记录成功，false表示记录失败
	 */
    Ncti_Boolean on_command_record_infor() override;

public:
    /**
	 * @brief 解析Python参数
	 * @details 从Python对象中提取参数用于命令执行
	 * 
	 * @param i_PyArgsss Python参数对象，包含传递给命令的参数
	 * @return Ncti_Boolean true表示解析成功，false表示解析失败
	 */
    Ncti_Boolean AnalizePyArgsss(PyObject* i_PyArgsss);

    /**
	 * @brief 解析UI参数
	 * @details 从UI界面获取参数用于命令执行
	 * 
	 * @param pArgument UI参数对象，包含从用户界面收集的参数
	 * @return Ncti_Boolean true表示解析成功，false表示解析失败
	 */
    Ncti_Boolean AnalizeUIArgsss(NctiArgumentObject* pArgument);

    /**
	 * @brief 解析Python和UI参数
	 * @details 同时处理从Python脚本和UI界面传来的参数
	 * 
	 * @param i_PyArgsss Python参数对象，包含传递给命令的Python参数
	 * @return Ncti_Boolean true表示解析成功，false表示解析失败
	 */
    Ncti_Boolean AnalizePyAndUI(PyObject* i_PyArgsss);
};
} // namespace NCTI

#endif // !NCTI_REG_COM_DEMO_CANCEL_H