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

#ifndef MAIN_WINDOW_MODULES_H
#define MAIN_WINDOW_MODULES_H

#include <QObject>

#include "mainwindow.h"

namespace NCTI {

/**
 * @brief MainWindow模块基类
 * 所有功能模块管理器都应继承此类
 */
class MainWindowModule : public QObject
{
    Q_OBJECT

public:
    /**
     * @brief 构造函数
     * @param mainWindow 主窗口指针
     */
    explicit MainWindowModule(MainWindow* mainWindow) : m_mainWindow(mainWindow) {}

    /**
     * @brief 初始化模块
     * 在此函数中进行模块的初始化操作，如连接信号等
     */
    virtual void initialize() = 0;

protected:
    MainWindow* m_mainWindow; ///< 主窗口指针
};

} // namespace NCTI

#endif // MAIN_WINDOW_MODULES_H