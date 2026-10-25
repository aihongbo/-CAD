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
#ifndef ADDLOADINGDLLWIDGET
#define ADDLOADINGDLLWIDGET

#include "NctiBaseDialog.h"

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

namespace NCTI
{
	/**
	 * @brief 添加加载DLL插件窗口类
	 * @details 用于添加和配置需要加载的DLL插件的对话框窗口
	 */
class AddLoadingDLLWidget : public NctiBaseDialog
	{
		Q_OBJECT

	public:
		/**
		 * @brief 构造函数
		 * @param parent 父窗口指针
		 */
		explicit AddLoadingDLLWidget(QWidget* parent = nullptr);
		
		/**
		 * @brief 初始化UI界面
		 */
		void initUI();
		
		/**
		 * @brief 连接信号与槽
		 */
		void connectSignals();

	Q_SIGNALS:
		/**
		 * @brief 插件确认信号
		 * @param pluginPath 插件路径
		 * @param plugin 插件名称
		 */
		void selectPluginConfirmed(const QString pluginPath, const QString plugin);

	private Q_SLOTS:
		/**
		 * @brief 选择插件槽函数
		 */
		void onSelectPlugin();
		
		/**
		 * @brief 确认按钮槽函数
		 */
		void onConfirm();
		
		/**
		 * @brief 取消按钮槽函数
		 */
		void onCancel();

	protected:
		QLabel* selectPluginPathLab;      ///< 选择插件路径标签
		QLabel* selectPluginLab;          ///< 选择插件标签
		QLineEdit* selectPluginPathEdit;  ///< 插件路径输入框
		QLineEdit* selectPluginEdit;      ///< 插件名称输入框
		QPushButton* selectPluginBtn;     ///< 选择插件按钮
		QPushButton* confirmBtn;          ///< 确认按钮
		QPushButton* cancelBtn;           ///< 取消按钮
	};
}
#endif // !ADDLOADINGDLLWIDGET