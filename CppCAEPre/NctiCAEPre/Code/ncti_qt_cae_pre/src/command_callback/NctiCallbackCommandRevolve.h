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

#ifndef NctiCallbackCommandRevolve_H
#define NctiCallbackCommandRevolve_H
#include "NctiCommandRevolve.h"

namespace NCTI {
class NctiDisplayGRevolve;

/**
* @brief 旋转回调命令类
* @details 继承自NctiCommandRevolve，用于处理旋转命令的回调实现
*/
class NctiCallbackCommandRevolve : public NctiCommandRevolve
{
public:
    /**
	* @brief 命令函数宏定义
	*/
    NCTI_COMMAND_FUNCTIONS(NctiCallbackCommandRevolve)

    /**
	* @brief 析构函数
	*/
    virtual ~NctiCallbackCommandRevolve();

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
	* @brief 更新对话框
	*/
    void UpdateDialog();

private:
    //	NctiCallbackCommandRevolve* m_pDlg;  ///< 对话框指针
};
} // namespace NCTI
#endif