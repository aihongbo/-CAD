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

#include "NctiQtCaePreApi.h"
#include "mainwindow.h"

#include <QWidget>
#include <QString>
#include <QFileInfo>
namespace NCTI
{
	QWidget* NctiQtCaePre::CreateMainWindow(QWidget* i_Parent)
	{
		MainWindow* w = new MainWindow(i_Parent, SARibbonMainWindowStyleFlag::UseNativeFrame, false);
		return qobject_cast<QWidget*>(w);
	}

	void NctiQtCaePre::CloseMainWindow(QWidget* i_MainWindow)
	{
		MainWindow* w = qobject_cast<MainWindow*>(i_MainWindow);
		if (w) {
			w->close();
		}
	}

	bool NctiQtCaePre::RunPyScript(QWidget* i_MainWindow, const RunArguments& i_Arg)
	{
		MainWindow* w = qobject_cast<MainWindow*>(i_MainWindow);
		if (w == nullptr) {
			return false;
		}

		QFileInfo fileInfo(i_Arg.pyPath);
		if (!fileInfo.exists()) {
			return false;
		}

		QString fileSuffix = fileInfo.suffix().toLower();
		if (fileSuffix != "py") {
			return false;
		}

		return w->runPyScript(i_Arg);
	}

}