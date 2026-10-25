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

#ifndef NctiCallbackCommandExtrude_H
#define NctiCallbackCommandExtrude_H
#include "NctiCommandExtrude.h"

namespace NCTI {
class NctiDisplayGExtrude;

/**
* @brief 拉伸回调命令类
* @details 继承自NctiCommandExtrude，用于处理拉伸命令的回调实现
*/
class NctiCallbackCommandExtrude : public NctiCommandExtrude
{
    /**
	* @brief 命令函数宏定义
	*/
    NCTI_COMMAND_FUNCTIONS(NctiCallbackCommandExtrude)

public:
    /**
	* @brief 析构函数
	*/
    virtual ~NctiCallbackCommandExtrude();

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
	* @brief 处理撤销事件
	*/
    void ProcessUndo() override;

    /**
	* @brief 处理重做事件
	*/
    void ProcessRedo() override;

    /**
	* @brief 处理点选位置事件
	* @param cPickPos 选择的位置
	*/
    void ProcessPickPosition(NctiPosition& cPickPos);

protected:
    /**
	* @brief 更新对话框
	*/
    void update_dialog();

    /**
	* @brief 修改拉伸参数
	* @return true表示修改成功，false表示修改失败
	*/
    bool modify_extrude();
};
} // namespace NCTI

#endif