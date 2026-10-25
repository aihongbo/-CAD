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

#pragma once

#include <QLineEdit>
#include <QKeyEvent>

/**
 * @brief 颜色输入行编辑控件类
 * @details 扩展QLineEdit控件，添加颜色更新功能
 */
class ColorLineEdit : public QLineEdit
{
    Q_OBJECT

public:
    /**
     * @brief 构造函数
     * @param parent 父控件指针
     */
    explicit ColorLineEdit(QWidget* parent = nullptr);

Q_SIGNALS:
    /**
     * @brief 更新颜色信号
     */
    void updateColor();

private:
    /**
     * @brief 键盘按下事件处理
     * @param event 键盘事件指针
     */
    void keyPressEvent(QKeyEvent* event) override;

};