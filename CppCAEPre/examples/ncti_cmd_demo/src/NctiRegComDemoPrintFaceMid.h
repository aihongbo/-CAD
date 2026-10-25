#ifndef NCTI_REG_COM_DEMO_PRINT_FACE_MID_H
#define NCTI_REG_COM_DEMO_PRINT_FACE_MID_H

#include "ncti_base.h"
#include "NctiRegComBase.h"
#include "NctiComInc.h"

namespace NCTI {
class NctiArgumentObject;

/**
 * @brief Python脚本测试 - 命令中操作实体子元素(打印面的中点)
 * @details 该命令用于演示如何在命令中操作实体的子元素，例如获取面的中点坐标
 * 
 * @code{.py}
 * doc.RunCommand("cmd_ncti_create_box", "box", NCTI.Point(0, 0, 0), 10, 20, 30)
 * doc.RunCommand("cmd_ncti_demo_print_face_mid")
 * @endcode
 * 
 * @ingroup DemoCommands
 */

/**
 * @brief 打印面中点坐标的命令类
 * @details 继承自[NctiRegComBase]的基础命令类，用于计算并打印几何面的中点坐标
 */
class NctiRegComDemoPrintFaceMid : public NctiRegComBase
{
    NCTI_COMMAND_FUNCTIONS(NctiRegComDemoPrintFaceMid)
public:
    /**
     * @brief 析构函数
     */
    ~NctiRegComDemoPrintFaceMid();

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

#endif // !NCTI_REG_COM_DEMO_PRINT_FACE_MID_H