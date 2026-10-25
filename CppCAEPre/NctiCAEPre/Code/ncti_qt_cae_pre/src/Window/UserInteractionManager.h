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

#ifndef USER_INTERACTION_MANAGER_H
#define USER_INTERACTION_MANAGER_H

#pragma once

#include "MainWindowModules.h"

namespace NCTI {

   class NctiQtCommandConsole;
   class NctiQtPythonScriptEdit;
   class NctiQtScriptExecutor;
   class NctiObjectProperty;

class NctiQtRightSideView;
   class DockTitleBar;

/**
* @brief 用户交互管理器类
* @details 管理用户交互相关的组件，如控制台、右侧栏等
*/
class UserInteractionManager : public MainWindowModule
{
    Q_OBJECT

public:
    /**
	* @brief 构造函数
	* @param mainWindow 主窗口指针
	*/
    explicit UserInteractionManager(MainWindow* mainWindow);

    /**
	* @brief 模块初始化，在这里处理主窗口的信号
	*/
    void initialize() override;

    /**
	* @brief 初始化命令控制台
	*/
    void initCommandConsole();

    /**
    * @brief 显示或隐藏命令控制台
    */
    void onCommandConsole();

    /**
    * @brief 显示或隐藏命令控制台
    */
    void showCommandConsole(bool show);

    /**
	 * @brief 添加命令控制台
	 */
    void addCommandConsole();

    /**
    * @brief 移除命令控制台
    */
    void removeCommandConsole();
	
	/**
	 * @brief 获取控制台状态
	 * @return 控制台状态
	 */
	bool getConsoleState() const;

    /**
     * @brief 获取脚本编辑器状态
     * @return 脚本编辑器状态
     */
    bool getScriptEditorState() const;

    /**
     * @brief 获取脚本数据路径
     */
    QString getScriptDataPath() const;

	/**
	 * @brief 脚本编辑槽函数
	 */
	void onScriptEdit();

	/**
	 * @brief 初始化右侧栏
	 */
	void initRightSide();
	
	/**
	 * @brief 显示右侧栏
	 */
	void showRightSide();
	
	/**
	 * @brief 获取右侧栏视图
	 * @return 右侧栏视图指针
	 */
	NctiQtRightSideView* getRightSideView();
	
    /**
    * @brief 获取对像属性视图
    */
    NctiObjectProperty* getPropertyView();

    /**
    * @brief 获取脚本编辑器
    */
    NctiQtPythonScriptEdit* getEditorView();

    /**
    * @brief 获取脚本执行器
    */
    NctiQtScriptExecutor* getScriptExecutor();

    /**
    * @brief 获取焦点
    */
    void SetFocus();

private:
	NctiQtCommandConsole* m_commandConsole{nullptr};          ///< 命令控制台
	QDockWidget* m_commandConsoleDockWidget{nullptr};         ///< 控制台窗口
	bool m_consoleState{false};                               ///< 控制台显示状态

	int m_rightSideDockWidth{200};                            ///< 右侧栏宽度
	bool m_rightSidePanelVisible{true};                       ///< 右侧栏显示状态
	QDockWidget* m_rightSideDockWidget{nullptr};              ///< 右侧栏停靠窗口
	NctiQtRightSideView* m_rightSideView{nullptr};            ///< 右侧栏视图
	DockTitleBar* m_rightSideTitleBar{nullptr};               ///< 右侧栏标题栏
	bool m_scriptEditorShowState{false};                      ///< 编辑器显示状态
};

} // namespace NCTI

#endif // USER_INTERACTION_MANAGER_H