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
#include <QObject>
#include <QTextEdit>

namespace NCTI
{
	class NctiQtScriptExecutor;
	class NctiQtScriptDebugger;
	class NctiQtScriptEditDelegate;
	
	/**
	 * @brief Qt脚本场景类
	 * @details 管理脚本编辑器中的单个脚本文件，包括文件操作、内容管理等
	 */
	class NCTI_QT_SCRIPT_EDIT NctiQtScriptScene : public QObject
	{
		Q_OBJECT
	public:
		/**
		 * @brief 构造函数
		 * @param isDark 是否使用暗色主题
		 * @param executor 脚本执行器
		 * @param parent 父对象
		 */
		explicit NctiQtScriptScene(bool isDark, NctiQtScriptExecutor *executor, QObject* parent = nullptr);
		
		/**
		 * @brief 析构函数
		 */
		virtual ~NctiQtScriptScene();

		/**
		 * @brief 设置委托
		 * @param delegate 委托对象指针
		 */
		void setDelegate(NctiQtScriptEditDelegate *delegate);

		/**
		 * @brief 打开文件
		 * @param path 文件路径
		 */
		void open(const QString &path);
		
		/**
		 * @brief 保存文件
		 */
		void save();
		
		/**
		 * @brief 保存文件到指定路径
		 * @param path 文件路径
		 */
        void save(const QString& path);
		
		/**
		 * @brief 清空内容
		 */
		void clear();
		
		/**
		 * @brief 关闭文件
		 */
		void close();

		/**
		 * @brief 写入执行历史
		 */
		void writeToExecuteHistory();
		
		/**
		 * @brief 从执行历史读取
		 * @param index 历史记录索引
		 */
		void readFromExecuteHistory(int index);

		/**
		 * @brief 路径改变信号
		 */
		Q_SIGNAL void sigPathChanged();
		
		/**
		 * @brief 获取文件路径
		 * @return 文件路径
		 */
		const QString& getPath() const;
		
		/**
		 * @brief 设置文件路径
		 * @param path 文件路径
		 */
		void setPath(const QString &path);		

		/**
		 * @brief 内容改变信号
		 */
		Q_SIGNAL void sigContentChanged();
		
		/**
		 * @brief 检查内容是否改变
		 * @return true表示内容已改变，false表示未改变
		 */
		bool isContentChanged() const;
		
		/**
		 * @brief 设置内容改变状态
		 * @param changed 是否改变
		 */
		void setContentChanged(bool changed);

		/**
		 * @brief 获取脚本执行器
		 * @return 脚本执行器指针
		 */
		NctiQtScriptExecutor* getExecutor() const;
		
		/**
		 * @brief 获取脚本调试器
		 * @return 脚本调试器指针
		 */
		NctiQtScriptDebugger* getDebugger() const;
		
		/**
		 * @brief 获取编辑器
		 * @return 编辑器指针
		 */
		QTextEdit* getEditor() const;

	private:
		/**
		 * @brief 获取内容
		 * @param excludePrefix 是否排除前缀
		 * @return 内容字符串
		 */
		QString getContent(bool excludePrefix = true);
		
		/**
		 * @brief 设置内容
		 * @param content 内容字符串
		 */
		void setContent(const QString & content);
		
		/**
		 * @brief 清空内容
		 */
		void clearContent();
		
		/**
		 * @brief 检查是否包含前缀
		 * @param content 内容字符串
		 * @return true表示包含前缀，false表示不包含
		 */
		bool hasPrefix(const QString &content) const;
		
		/**
		 * @brief 移除前缀
		 * @param content 内容字符串
		 */
		void removePrefix(QString &content);
		
		/**
		 * @brief 添加前缀
		 * @param content 内容字符串
		 */
		void addPrefix(QString &content);

	private:
		QString m_path;                         ///< 文件路径
		bool m_isContentChanged;                ///< 内容是否改变
		NctiQtScriptExecutor* m_executor;       ///< 脚本执行器
		NctiQtScriptDebugger* m_debugger;       ///< 脚本调试器
		QTextEdit* m_editor;                    ///< 编辑器
		NctiQtScriptEditDelegate* m_delegate;   ///< 委托对象
	};
};