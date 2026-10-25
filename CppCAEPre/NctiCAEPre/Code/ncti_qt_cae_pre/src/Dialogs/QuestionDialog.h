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

#include "Dialog.h"

namespace NCTI {
/**
 * @brief 问题对话框类
 * @details 用于显示问题提示并获取用户选择的对话框，继承自Dialog类
 */
class QuestionDialog : public Dialog
{
    Q_OBJECT
public:
    /**
	 * @brief 构造函数
	 * @param parent 父窗口指针
	 */
    explicit QuestionDialog(QWidget* parent = nullptr);

    /**
	 * @brief 执行对话框
	 * @param title 对话框标题
	 * @param message 对话框消息
	 * @return 用户选择结果
	 */
    int exec(const QString& title = QString(), const QString& message = QString());
};
}; // namespace NCTI