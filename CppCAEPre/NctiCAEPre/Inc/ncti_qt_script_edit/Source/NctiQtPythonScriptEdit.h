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

#include "dcl_ncti_qt_script_edit.h"


#include <QFrame>
#include <QMap>

class QAbstractButton;
class QMenu;
class QPushButton;
class QTextEdit;
class QToolButton;

namespace NCTI
{
	class NctiQtScriptScene;
	class NctiQtScriptExecutor;
	class NctiQtScriptDebugger;
	
	/**
	 * @brief Qt Python脚本编辑器类
	 * @details 提供Python脚本编辑、执行和调试功能的完整界面
	 */
	class NCTI_QT_SCRIPT_EDIT NctiQtPythonScriptEdit : public QFrame
	{
		Q_OBJECT
	public:
		/**
		 * @brief 构造函数
		 * @param parent 父对象
		 */
		explicit NctiQtPythonScriptEdit(QWidget* parent = nullptr);
		
		/**
		 * @brief 析构函数
		 */
		virtual ~NctiQtPythonScriptEdit();

		/**
		 * @brief 按钮枚举
		 */
		enum Button
		{
			ButtonRun,                ///< 运行按钮
			ButtonRestore,            ///< 恢复按钮
			ButtonClear,              ///< 清除按钮
			ButtonOpen,               ///< 打开按钮
			ButtonSave,               ///< 保存按钮
			ButtonClose,              ///< 关闭按钮
			ButtonStartDebug,         ///< 开始调试按钮
			ButtonStopDebug,          ///< 停止调试按钮
			ButtonBreakpoint,         ///< 断点按钮
			ButtonBreakpoint_Clear,   ///< 清除断点按钮
			ButtonBreakpoint_Next,    ///< 下一个断点按钮
			ButtonBreakpoint_Single,  ///< 单步执行按钮
			ButtonBreakpoint_Disable, ///< 禁用断点按钮
			ButtonBreakpoint_Enable,  ///< 启用断点按钮
            ButtonCustom,             ///< 自定义按钮
		};

		/**
		 * @brief 设置界面
		 */
		void setup();

		/**
		 * @brief 设置脚本执行器
		 * @param script 脚本执行器指针
		 */
		void setExecutor(NctiQtScriptExecutor *script);
		
		/**
		 * @brief 获取脚本执行器
		 * @return 脚本执行器指针
		 */
		NctiQtScriptExecutor* getExecutor();		

		/**
		 * @brief 获取场景列表
		 * @return 场景列表
		 */
		const QList<NctiQtScriptScene*>& getSceneList() const;
		
		/**
		 * @brief 获取当前场景
		 * @return 当前场景指针
		 */
		NctiQtScriptScene* getScene() const;

		/**
		 * @brief 获取调试器
		 * @return 调试器指针
		 */
		NctiQtScriptDebugger* getDebugger();
		
		/**
		 * @brief 获取编辑器
		 * @return 编辑器指针
		 */
		QTextEdit* getEditor();

		/**
		 * @brief 执行脚本
		 */
		Q_SLOT void excute();
		
		/**
		 * @brief 清除对象
		 */
		Q_SLOT void clearObject();
		
		/**
		 * @brief 清除内容
		 */
		Q_SLOT void clearContent() const;
		
		/**
		 * @brief 加载脚本
		 * @param index 索引
		 */
		Q_SLOT void load(int index = 0) const;
		
		/**
		 * @brief 保存脚本
		 */
		Q_SLOT void save() const;
        
        /**
         * @brief 打开指定路径的脚本
         * @param path 脚本路径
         */
        void open(const QString& path);
        
        /**
         * @brief 保存脚本到指定路径
         * @param path 脚本路径
         */
        void save(const QString& path) const;

		/**
		 * @brief 开始调试
		 */
		Q_SLOT void startDebug();
		
		/**
		 * @brief 停止调试
		 */
		Q_SLOT void stopDebug();
		
		/**
		 * @brief 调试到下一个断点
		 */
		Q_SLOT void debugNextBreakpoint();
		
		/**
		 * @brief 调试下一行
		 */
		Q_SLOT void debugNextLine();

		/**
		 * @brief 移除所有断点
		 */
		Q_SLOT void removeAllBreakpoint();
		
		/**
		 * @brief 启用断点
		 */
		Q_SLOT void enableBreakpoint();
		
		/**
		 * @brief 禁用断点
		 */
		Q_SLOT void disableBreakpoint();

		/**
		 * @brief 配置按钮图标
		 * @param button 按钮类型
		 * @param icon 图标
		 */
		void configButtonIcon(Button button, const QIcon &icon);
		
		/**
		 * @brief 配置场景
		 * @param isDark 是否使用暗色主题
		 */
		void configScene(bool isDark);

        /**
         * @brief 设置历史文件路径
         */
        void setHistoryFilePath(const QString& filePath);
		
		/**
		 * @brief 创建新场景
		 */
		void newScene();

        /**
         * @brief 场景添加信号
         * @param scene 场景对象
         */
        Q_SIGNAL void sigSceneAppend(QObject* scene);
        
        /**
         * @brief 添加自定义动作信号
         */
        Q_SIGNAL void addCustomAction();

	protected:
		/**
		 * @brief 调整大小事件
		 * @param event 事件指针
		 */
		void resizeEvent(QResizeEvent* event) override;
		
		/**
		 * @brief 显示事件
		 * @param event 事件指针
		 */
		void showEvent(QShowEvent* event) override;
		
		/**
		 * @brief 保存场景内容到文件（可选）
		 * @param scene 场景指针
		 */
		virtual bool saveSceneContentToFileOrNot(NctiQtScriptScene* scene);
		
		/**
		 * @brief 保存场景内容到文件
		 * @param scene 场景指针
		 */
		virtual void saveSceneContentToFile(NctiQtScriptScene* scene);
		
		/**
		 * @brief 弹出询问对话框
		 * @param message 消息内容
		 * @return true表示确认，false表示取消
		 */
		virtual bool popupQuestion(const QString& message);
		
		/**
		 * @brief 安装提示信息
		 * @param object 对象指针
		 * @param tip 提示信息
		 */
		virtual void installTooltip(QObject *object, const QString &tip);

	private:
		/**
		 * @brief 设置按钮
		 */
		void setupButton();
		
		/**
		 * @brief 设置按钮栏
		 */
		void setupButtonBar();
		
		/**
		 * @brief 设置按钮文本
		 */
		void setupButtonText();
		
		/**
		 * @brief 设置未命名脚本
		 */
		void setupUntitledScript();
		
		/**
		 * @brief 设置滚动条
		 */
		void setupScroll();
		
		/**
		 * @brief 设置调试器
		 */
		void setupDebugger();
		
		/**
		 * @brief 更新滚动位置
		 */
		void updateScrollToPosition();
		
		/**
		 * @brief 更新场景标题
		 * @param scene 场景指针
		 */
		void updateSceneTitle(NctiQtScriptScene *scene);
		
		/**
		 * @brief 添加场景
		 * @param scene 场景指针
		 */
		void appendScene(NctiQtScriptScene *scene);
		
		/**
		 * @brief 获取按钮图标
		 * @param button 按钮类型
		 * @return 图标
		 */
		QIcon getButtonIcon(Button button) const;
		
		/**
		 * @brief 获取动作
		 * @param button 按钮类型
		 * @return 动作指针
		 */
		QAction* getAction(Button button) const;
		
		/**
		 * @brief 设置按钮启用状态
		 * @param button 按钮类型
		 * @param enable 是否启用
		 */
		void setButtonEnable(Button button, bool enable);
    
    public:
        /**
         * @brief 获取按钮
         * @param button 按钮类型
         * @return 按钮指针
         */
        QAbstractButton* getButton(Button button) const;

	private:
        NctiQtScriptExecutor* m_executor{ nullptr };  ///< 脚本执行器
		QList<NctiQtScriptScene*> m_sceneList;        ///< 场景列表
		struct SceneConfig
		{
			bool isDark = false;  ///< 是否使用暗色主题
		}m_sceneConfig;

		QPushButton* m_runButton{ nullptr };              ///< 运行按钮
		QPushButton* m_cleanButton{ nullptr };            ///< 清除按钮
		QToolButton* m_loadToolButton{ nullptr };         ///< 加载工具按钮
		QMenu* m_loadToolMenu{ nullptr };                 ///< 加载工具菜单

		QPushButton* m_openButton{ nullptr };             ///< 打开按钮
		QPushButton* m_saveButton{ nullptr };             ///< 保存按钮
		QPushButton* m_closeButton{ nullptr };            ///< 关闭按钮

		QPushButton* m_debugStartButton{ nullptr };       ///< 调试开始按钮
		QPushButton* m_debugStopButton{ nullptr };        ///< 调试停止按钮
		QToolButton* m_breakpointButton{ nullptr };       ///< 断点按钮
		QMenu* m_breakpointToolMenu{ nullptr };           ///< 断点工具菜单
		QAction* m_breakpointRemoveAction{ nullptr };     ///< 移除断点动作
		QAction* m_breakpointNextAction{ nullptr };       ///< 下一个断点动作
		QAction* m_breakpointSingleAction{ nullptr };     ///< 单步执行动作
		QAction* m_breakpointDisableAction{ nullptr };    ///< 禁用断点动作
		QAction* m_breakpointEnableAction{ nullptr };     ///< 启用断点动作
		
        QToolButton* m_customToolButton{ nullptr };       ///< 自定义工具按钮
            
		QPushButton* m_scrollToTopButton{ nullptr };      ///< 滚动到顶部按钮
		QPushButton* m_scrollToBottomButton{ nullptr };   ///< 滚动到底部按钮

		QMap<Button, QIcon> m_button2Icon;                ///< 按钮图标映射
	};
};