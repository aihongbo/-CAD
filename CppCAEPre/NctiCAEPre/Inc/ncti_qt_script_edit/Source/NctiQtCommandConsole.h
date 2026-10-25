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
#include <QLineEdit>
#include <QTextEdit>
#include <QTextCursor>
#include <QTextCharFormat>

#include "ncti_base.h"

namespace NCTI
{
	class NctiQtScriptExecutor;
	class CodeCompleter;
    class NctiPosition;
	class ConsoleHistory;
    class NctiVector;
	
	/**
	 * @brief Qt命令控制台类
	 * @details 提供命令行交互界面，支持代码补全、历史记录等功能
	 */
	class NCTI_QT_SCRIPT_EDIT NctiQtCommandConsole : public QTextEdit
	{
		Q_OBJECT
	public:
		/**
		 * @brief 构造函数
		 * @param parent 父对象
		 */
		explicit NctiQtCommandConsole(QWidget *parent = nullptr);
		
		/**
		 * @brief 析构函数
		 */
		virtual ~NctiQtCommandConsole();

		/**
		 * @brief 设置脚本执行器
		 * @param script 脚本执行器指针
		 */
		void setExecutor(NctiQtScriptExecutor* script);
		
		/**
		 * @brief 获取脚本执行器
		 * @return 脚本执行器指针
		 */
		NctiQtScriptExecutor* getExecutor();

		/**
		 * @brief 设置代码前缀
		 * @param prefix 前缀字符串
		 * @param color 颜色
		 */
		void setCodePrefix(const QString& prefix, const QColor& color = QColor());
		
		/**
		 * @brief 设置错误消息前景色
		 * @param color 颜色
		 */
		void setErrorMessageForeground(const QColor& color);

		/**
		 * @brief 添加日志消息
		 * @param message 消息内容
		 * @param first 首行位置
		 * @param prefix 是否添加前缀
		 * @param autorf 是否自动刷新
		 */
		void appendMessageLog(const QString& message, int* first = nullptr, bool prefix = false, bool autorf = true);
		
		/**
		 * @brief 添加错误消息
		 * @param message 消息内容
		 */
		void appendMessageError(const QString& message);
		
		/**
		 * @brief 添加代码消息
		 * @param message 消息内容
		 */
		void appendMessageCode(const QString& message);
		
		/**
		 * @brief 添加新前缀行
		 */
		void newPrefixLine();
		
		/**
		 * @brief 清空控制台
		 */
		void clear();

        /**
         * @brief 获取位置回调函数（NctiMeasuringTool使用）
         * @param pos 位置信息
         */
        void GetPositionFunc(const NctiPosition&);
        
        /**
         * @brief 获取长度回调函数
         * @param length 长度值
         */
        void GetLengthFunc(Ncti_Double length);

        /**
         * @brief 获取半径回调函数
         * @param radius 半径值
         */
        void GetRadiusFunc(Ncti_Double radius);

        /**
         * @brief 获取角度回调函数
         * @param angle 角度值
         */
        void GetAngleFunc(Ncti_Double angle);

        /**
         * @brief 获取向量回调函数
         * @param vec 向量值
         */
        void GetVectorFunc(const NctiVector& vec);
        
        /**
         * @brief 获取中点位置回调函数
         * @param pos 位置信息
         */
        void GetMidPositionFunc(const NctiPosition&);
        
        /**
         * @brief 获取中心点回调函数
         * @param pos 位置信息
         */
        void GetCenterFunc(const NctiPosition&);

	protected:
		/**
		 * @brief 事件过滤器
		 * @param w 对象指针
		 * @param e 事件指针
		 * @return true表示已处理，false表示未处理
		 */
		bool eventFilter(QObject *w, QEvent *e) override;
		
		/**
		 * @brief 按键按下事件
		 * @param event 事件指针
		 */
		void keyPressEvent(QKeyEvent* event) override;
		
		/**
		 * @brief 输入法事件
		 * @param event 事件指针
		 */
		void inputMethodEvent(QInputMethodEvent* event) override;
		
		/**
		 * @brief 鼠标滚轮事件
		 * @param e 事件指针
		 */
		void wheelEvent(QWheelEvent* e) override;
		
		/**
		 * @brief 上下文菜单事件
		 * @param event 事件指针
		 */
		void contextMenuEvent(QContextMenuEvent* event) override;
		
		/**
		 * @brief 光标位置改变槽函数
		 */
		Q_SLOT void onCursorPositionChanged();

	private:
		/**
		 * @brief 编辑前对光标进行修正
		 * @details 
		 * 1. 光标不在最后一行，设置为最后字符
		 * 2. 选中时，修正为只选中最后一行输入内容
		 */
		void fixTextCursor();
		
		/**
		 * @brief 检查块是否只有前缀
		 * @param block 文本块
		 * @return true表示只有前缀，false表示有其他内容
		 */
		bool blockOnlyPrefix(const QTextBlock &block) const;
		
		/**
		 * @brief 获取最后一块内容
		 * @return 内容字符串
		 */
		QString getLastBlockContent() const;
		
		/**
		 * @brief 设置最后一块内容
		 * @param content 内容字符串
		 */
		void setLastBlockContent(const QString &content);
		
		/**
		 * @brief 恢复默认字符格式
		 */
		void restoreDefaultCharFormat();
		
		/**
		 * @brief 执行命令
		 * @param content 命令内容
		 */
		void excuteCommand(const QString& content);

		/**
		 * @brief 改变块前景色
		 * @param textEdit 文本编辑器
		 * @param first 起始位置
		 * @param last 结束位置
		 * @param color 颜色
		 */
		void changeBlockForeground(QTextEdit* textEdit, int first, int last, const QColor& color);

	private:
		std::vector<QString> m_Commands;          ///< 命令列表
		std::vector<QString> m_History;           ///< 历史记录
		std::vector<QString> m_Items;             ///< 项目列表
		int m_HistoryPos = -1;                    ///< 历史记录位置
		QString m_codePrefix;                     ///< 代码前缀
		QColor m_codePrefixColor;                 ///< 代码前缀颜色

		QTextCharFormat m_defaultCharFormat;      ///< 默认字符格式
		QColor m_errorMessageForeground;          ///< 错误消息前景色
		NctiQtScriptExecutor* m_executor;         ///< 脚本执行器
		CodeCompleter* m_completer;               ///< 代码补全器
		ConsoleHistory* m_history;                ///< 控制台历史记录

		bool m_skipCodeMesssage;                  ///< 是否跳过代码消息
		int m_inputPosition;                      ///< 输入位置
		int m_selectPosition;                     ///< 选择位置
		int m_selectLength;                       ///< 选择长度
	};
};