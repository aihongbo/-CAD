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

#include "NctiQtScriptScene.h"

#include <QAbstractTextDocumentLayout>
#include <QTextBlock>
#include <QScrollBar>
#include <QFileInfo>
#include <QDebug>

#include "CodeEditor.h"
#include "BreakpointArea.h"
#include "ExecuteHistory.h"
#include "NctiQtScriptExecutor.h"
#include "NctiQtScriptDebugger.h"
#include "NctiQtPythonScriptEdit.h"

using namespace NCTI;

constexpr const char* SCRIPT_CLEAR_PREFIX = "doc.Clear()\ndoc.ResetCaseResult()\n";

NctiQtScriptScene::NctiQtScriptScene(bool isDark, NctiQtScriptExecutor* executor, QObject* parent)
	: QObject(parent)
	, m_executor(executor)
	, m_debugger(new NctiQtScriptDebugger(this))
	, m_editor(new CodeEditor)
	, m_isContentChanged(false)
{
	m_debugger->setExecutor(m_executor);
	qobject_cast<CodeEditor*>(m_editor)->setDefaultSyntaxStyle(isDark ? CodeEditor::Dark : CodeEditor::Light);
	m_editor->document()->setDocumentMargin(10);
	m_editor->setTabStopDistance(40);
	// 请谨慎删除下面的setPlainText
	// 1 创建后添加默认的clear命令
	// 2 经测试发现CodeEditor创建后isundoavailable==true（可能是因为上面设置了margin和distance），直接撤销后会导致crash，
	//	 使用setPlainText之后，undo/redo的stack记录重置，避免crash
	m_editor->setPlainText(SCRIPT_CLEAR_PREFIX);
	connect(m_editor, &QTextEdit::textChanged, this,
		[this]
		{
			setContentChanged(true);
		});
	connect(qobject_cast<CodeEditor*>(getEditor())->getBreakpointArea(), &BreakpointArea::sigClicked, this,
		[this](int blockNumber, int button)
		{
			if (getDebugger()->containsBreakpoint(blockNumber))
			{
				if (button == Qt::MouseButton::LeftButton) {
					getDebugger()->removeBreakpoint(blockNumber);
					qobject_cast<CodeEditor*>(getEditor())->getBreakpointArea()->removeBreakpoint(blockNumber);
				}
				else if (button == Qt::MouseButton::RightButton) {
					bool isEnable = getDebugger()->isEnableBreakpoint(blockNumber);
					getDebugger()->enableBreakpoint(blockNumber, !isEnable);
					qobject_cast<CodeEditor*>(getEditor())->getBreakpointArea()->enableBreakpoint(blockNumber, !isEnable);
				}
				else {

				}
			}
			else
			{
				if (button == Qt::MouseButton::LeftButton) {
					getDebugger()->addBreakpoint(blockNumber, true);
					qobject_cast<CodeEditor*>(getEditor())->getBreakpointArea()->addBreakpoint(blockNumber, true);
				}
				else if (button == Qt::MouseButton::RightButton) {
					getDebugger()->addBreakpoint(blockNumber, false);
					qobject_cast<CodeEditor*>(getEditor())->getBreakpointArea()->addBreakpoint(blockNumber, false);
				}
				else {

				}
			}
		});
	connect(getDebugger(), &NctiQtScriptDebugger::sigCurrentBreakpointChanged, this,
		[this](int previous, int current)
		{
			do {
				auto textEdit = qobject_cast<CodeEditor*>(getEditor());
				if (current < 0 || current >= textEdit->document()->blockCount()) {
					break;
				}

				auto block = textEdit->document()->findBlockByNumber(current);
				auto top = textEdit->document()->documentLayout()->blockBoundingRect(block).top();
				auto bottom = top + (int)textEdit->document()->documentLayout()->blockBoundingRect(block).height();

				int value = bottom - textEdit->viewport()->height() * 0.5;
				int min = textEdit->verticalScrollBar()->minimum();
				int max = textEdit->verticalScrollBar()->maximum();
				if (value <= min) {
					textEdit->verticalScrollBar()->setValue(min);
				}
				else if (value >= max) {
					textEdit->verticalScrollBar()->setValue(max);
				}
				else {
					textEdit->verticalScrollBar()->setValue(value);
				}
			} while (0);

			qobject_cast<CodeEditor*>(getEditor())->getBreakpointArea()->setCurrentBlockNumber(current);
		});
}

NctiQtScriptScene::~NctiQtScriptScene()
{
	if (m_editor->parentWidget() == nullptr) {
		m_editor->deleteLater();
	}
}

void NctiQtScriptScene::setDelegate(NctiQtScriptEditDelegate* delegate)
{
	m_delegate = delegate;
}

void NctiQtScriptScene::open(const QString& path)
{
	setPath("");
	clear();

	QFile file(path);
	if (file.exists() && file.open(QIODevice::ReadOnly))
	{
		getEditor()->append(QString::fromUtf8(file.readAll()));
		setPath(path);
		file.close();
	}
	
	setContentChanged(false);
}

void NctiQtScriptScene::save()
{
	if (getPath().isEmpty()) {
		return;
	}	
    save(m_path);
	setContentChanged(false);
}

void NCTI::NctiQtScriptScene::save(const QString& path)
{
    QString content = getContent();
    QFile file(path);
    if (!file.open(QIODevice::ReadWrite | QIODevice::Truncate)) {
        return;
    }
    file.write(content.toUtf8());
    file.close();
}

void NctiQtScriptScene::clear()
{
	clearContent();
}

void NctiQtScriptScene::close()
{
	setPath("");
	clear();
	setContentChanged(false);
}

void NctiQtScriptScene::writeToExecuteHistory()
{
	auto&& content = getContent();
	auto&& lines = content.split('\n', Qt::SkipEmptyParts);
	if (lines.isEmpty()) {
		return;
	}

	QString name = "Untitled";
	if (!m_path.isEmpty()) {
		name = QFileInfo(m_path).fileName();
	}

	ExecuteHistory::instance()->add(content, name);
}

void NctiQtScriptScene::readFromExecuteHistory(int index)
{
	auto&& content = ExecuteHistory::instance()->get(index);
	setContent(content);
}

const QString& NctiQtScriptScene::getPath() const
{
	return m_path;
}

void NctiQtScriptScene::setPath(const QString& path)
{
	if (m_path == path) {
		return;
	}
	m_path = path;
	Q_EMIT sigPathChanged();
}

bool NctiQtScriptScene::isContentChanged() const
{
	return m_isContentChanged;
}

void NctiQtScriptScene::setContentChanged(bool changed)
{
	if (m_isContentChanged == changed) {
		return;
	}
	m_isContentChanged = changed;
	Q_EMIT sigContentChanged();
}

NctiQtScriptExecutor* NctiQtScriptScene::getExecutor() const
{
	return m_executor;
}

NctiQtScriptDebugger* NctiQtScriptScene::getDebugger() const
{
	return m_debugger;
}

QTextEdit* NctiQtScriptScene::getEditor() const
{
	return m_editor;
}

QString NctiQtScriptScene::getContent(bool excludePrefix)
{
	QString content = getEditor()->toPlainText();
	//if (excludePrefix) {
	//	removePrefix(content);
	//}
	return content;
}

void NctiQtScriptScene::setContent(const QString& content)
{
	QString t(content);
	//addPrefix(t);

	// 不直接使用setPlainText，避免redo/undo的记录被重置
	QTextCursor cursor = getEditor()->textCursor();
	cursor.select(QTextCursor::Document);
	cursor.insertText(t);
	cursor.movePosition(QTextCursor::End);
	//getEditor()->setFocus();
}

void NctiQtScriptScene::clearContent()
{
	setContent("");
}

bool NctiQtScriptScene::hasPrefix(const QString& content) const
{
	return content.startsWith(SCRIPT_CLEAR_PREFIX);
}

void NctiQtScriptScene::removePrefix(QString& content)
{
	if (!hasPrefix(content)) {
		return;
	}

	content = content.mid(static_cast<int>(strlen(SCRIPT_CLEAR_PREFIX)));
}

void NctiQtScriptScene::addPrefix(QString& content)
{
	if (hasPrefix(content)) {
		return;
	}

	content.prepend(SCRIPT_CLEAR_PREFIX);
}