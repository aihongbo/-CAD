/*
 * Copyright (c) 2025 粤港澳大湾区（广东）国创中心
 *
 * This file is a part of NctiCAEPre.
 *
 * NctiCAEPre is licensed under Mulan PSL v2.
 * You can use this software according to the terms and conditions of the Mulan PSL v2.
 * You may obtain a copy of Mulan PSL v2 at:
 *          http://license.coscl.org.cn/MulanPSL2
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
 * EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
 * MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
 * See the Mulan PSL v2 for more details.
 *
 */

#ifndef NctiCallbackCommandCreateDocSketch_H
#define NctiCallbackCommandCreateDocSketch_H
#include "NctiCommandCreateDocSketch.h"
#include "NctiSketchComDefine.h"

namespace NCTI {
/**
* @brief 创建文档草图回调命令类
* @details 继承自NctiCommandCreateDocSketch，用于处理创建文档草图命令的回调实现
*/
class NctiCallbackCommandCreateDocSketch : public NctiCommandCreateDocSketch
{
public:
    /**
	* @brief 命令函数宏定义
	*/
    NCTI_COMMAND_FUNCTIONS(NctiCallbackCommandCreateDocSketch)

    /**
	* @brief 析构函数
	*/
    virtual ~NctiCallbackCommandCreateDocSketch();

    /**
	* @brief 激活命令
	* @param pDoInstance 显示对象实例指针
	* @return 操作结果枚举值
	*/
    EnumNctiResult Activate(NctiDisplayObject* pDoInstance) override;

    /**
	* @brief 取消激活命令
	* @return 操作结果枚举值
	*/
    EnumNctiResult DeActivate() override;

    /**
	* @brief 处理确定按钮事件
	*/
    virtual void ProcessOkButton() override;

    /**
	* @brief 处理更新事件
	*/
    virtual void ProcessUpdate() override;

    /**
	* @brief 处理点选位置事件
	* @param cPickPos 选择的位置
	*/
    virtual void ProcessPickPosition(NctiPosition& cPickPos) override;

    /**
	* @brief 处理取消事件
	*/
    virtual void ProcessCancel() override;

    /**
	* @brief 处理撤销事件
	*/
    void ProcessUndo() override;

    /**
	* @brief 处理重做事件
	*/
    void ProcessRedo() override;

protected:
    /**
	* @brief 检查对话框值的有效性
	* @return true表示有效，false表示无效
	*/
    bool check_dlg_value();

    /**
	* @brief 更新对话框
	*/
    virtual void update_dialog();

    /**
	* @brief 修改工作平面
	*/
    void modify_workplane();

private:
    EnumNctiEuler m_eEulerAxis;  ///< 当前欧拉轴
    bool m_bHistoryActiveBackup; ///< 历史状态备份
};
} // namespace NCTI

#endif