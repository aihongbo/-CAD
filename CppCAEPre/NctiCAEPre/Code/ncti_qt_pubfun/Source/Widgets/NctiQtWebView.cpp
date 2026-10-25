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

#ifdef NCTI_ENABLE_AIQA_SERVICE

#include "NctiQtWebView.h"
#include <QDebug>

namespace NCTI
{
	NctiQtWebView::NctiQtWebView(QWidget* parent)
		: QWebEngineView(parent)
	{
		installEventFilter(this);
	}
	
    NctiQtWebView::~NctiQtWebView()
	{}

	QWebEngineView* NctiQtWebView::getDevToolsView()
	{
		if (m_DevToolsView == nullptr) {
			m_DevToolsView = new QWebEngineView(this);
			m_DevToolsView->setWindowFlags(Qt::Dialog);
			m_DevToolsView->page()->setInspectedPage(page());
			m_DevToolsView->resize(500, 500);
		}
		return m_DevToolsView;
	}
	
    bool NctiQtWebView::eventFilter(QObject* obj, QEvent* event) 
	{
		if (obj == this && event->type() == QEvent::ShortcutOverride)
		{
			QKeyEvent* e = (QKeyEvent*)(event);
			if (e->modifiers() && Qt::ControlModifier && e->key() == Qt::Key_D)
			{
				getDevToolsView()->show();
			}
		}
		return QWebEngineView::eventFilter(obj, event);
	}
}
#endif