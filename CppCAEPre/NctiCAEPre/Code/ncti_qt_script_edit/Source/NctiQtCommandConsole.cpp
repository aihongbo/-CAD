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

#include "NctiQtCommandConsole.h"
#include "NctiQtScriptExecutor.h"

#include <QTextCursor>
#include <QTextBlock>
#include <QTextDocument>
#include <QDebug>
#include <QInputMethodEvent>
#include "CodeCompleter.h"
#include "ConsoleHistory.h"
#include <QApplication>
#include <QMenu>

#include "NctiPosition.h"
#include "NctiVector.h"

using namespace NCTI;

NctiQtCommandConsole::NctiQtCommandConsole(QWidget* parent)
	: QTextEdit(parent)
	, m_HistoryPos(-1)
	, m_executor(nullptr)
	, m_errorMessageForeground(QColor(180, 63, 63))
	, m_completer(new CodeCompleter(":/code_completer.json", this))
	, m_skipCodeMesssage(false)
	, m_history(new ConsoleHistory(this))
{
	m_Commands.push_back("HELP");
	m_Commands.push_back("HISTORY");
	m_Commands.push_back("CLEAR");
	m_Commands.push_back("CLASSIFY");

	m_defaultCharFormat = currentCharFormat();
	setExecutor(new NctiQtScriptExecutor(this));
	//installEventFilter(this);

	//setCursorWidth(0);
	connect(this, &NctiQtCommandConsole::cursorPositionChanged, this, &NctiQtCommandConsole::onCursorPositionChanged);
}

NctiQtCommandConsole::~NctiQtCommandConsole()
{
	//退出程序会报错
	//setScript(nullptr);
}

void NctiQtCommandConsole::setExecutor(NctiQtScriptExecutor* executor)
{
	if (m_executor)
	{
		disconnect(m_executor);
		m_executor = nullptr;
	}
	m_executor = executor;
	if (m_executor)
	{
		connect(m_executor, &NctiQtScriptExecutor::signalMessage, this, [this](QString message, int type)
			{
				if (type == NctiQtScriptExecutor::MessageTypeError)
					appendMessageError(message);
				else if (type == NctiQtScriptExecutor::MessageTypeCode)
					appendMessageCode(message);
				else if (type == NctiQtScriptExecutor::MessageTypeNewLine)
					newPrefixLine();
				else
					appendMessageLog(message);
			});
		connect(m_executor, &NctiQtScriptExecutor::signalClear, this, [this]
			{
				clear();
			});
		connect(m_executor, &NctiQtScriptExecutor::sigStateChanged, this, [this](int state)
			{
				//if (state == NctiQtScriptExecutor::ExecuteState::ExecuteStateStopped)
				//{
				//	newPrefixLine();
				//}
			});
	}
}

NctiQtScriptExecutor* NctiQtCommandConsole::getExecutor()
{
	return m_executor;
}


void NctiQtCommandConsole::setCodePrefix(const QString& prefix, const QColor& color)
{ 
	m_codePrefix = prefix; 
	m_codePrefixColor = color; 
	newPrefixLine();
}

void NctiQtCommandConsole::setErrorMessageForeground(const QColor& color)
{
	m_errorMessageForeground = color;
}

void NctiQtCommandConsole::appendMessageLog(const QString& message, int* first, bool prefix, bool autorf)
{
	// 移动到当前最后位置并记录position
	auto textCursor = this->textCursor();
	if (textCursor.position() != QTextCursor::End)
		textCursor.movePosition(QTextCursor::End, QTextCursor::MoveAnchor);

	int lastIndex = textCursor.position();	

	// 追加文本
	textCursor.setCharFormat(m_defaultCharFormat);
	setTextCursor(textCursor);

	if (prefix)
	{
		auto block = this->document()->lastBlock();
		if (blockOnlyPrefix(block) && autorf) {
			textCursor.insertText(message);
		}
		else 
		{
			append(m_codePrefix + message);
			if (block.blockNumber() != 0){
				lastIndex += 1;
			}
			changeBlockForeground(this, lastIndex, lastIndex + m_codePrefix.length(), m_codePrefixColor);
			lastIndex += m_codePrefix.length();
		}
	}
	else
	{
		lastIndex += 1;
		append(message);
	}

	if (first != nullptr) {
		*first = lastIndex;
	}
}

void NctiQtCommandConsole::appendMessageError(const QString& message)
{
	// 
	int first = -1;
	appendMessageLog(message, &first);

	//
	changeBlockForeground(this, first, this->textCursor().position(), m_errorMessageForeground);
}

void NctiQtCommandConsole::appendMessageCode(const QString& message)
{
	if (m_skipCodeMesssage) {
		return;
	}
	appendMessageLog(message, nullptr, true);
}

void NctiQtCommandConsole::newPrefixLine()
{
	appendMessageLog("",nullptr,true,false);
	restoreDefaultCharFormat();
	document()->clearUndoRedoStacks();
}

void NctiQtCommandConsole::clear()
{
	QTextEdit::clear();
	newPrefixLine();
}

void NctiQtCommandConsole::GetPositionFunc(const NctiPosition& pt)
{
    double x = pt.x();
    double y = pt.y();
    double z = pt.z();
	QString qsx = QString::number(x, 'g', 16);
	QString qsy = QString::number(y, 'g', 16);
	QString qsz = QString::number(z, 'g', 16);
    appendMessageLog(QString("Position: (%1, %2, %3)").arg(qsx).arg(qsy).arg(qsz));
}

void NctiQtCommandConsole::GetLengthFunc(Ncti_Double height)
{
	QString qsh = QString::number(height, 'g', 16);
    appendMessageLog(QString("Length: (%1)").arg(qsh));
}

void NCTI::NctiQtCommandConsole::GetRadiusFunc(Ncti_Double radius)
{
    QString qsh = QString::number(radius, 'g', 16);
    appendMessageLog(QString("Radius: (%1)").arg(qsh));
}

void NCTI::NctiQtCommandConsole::GetAngleFunc(Ncti_Double angle)
{
    QString qsh = QString::number(angle, 'g', 16);
    appendMessageLog(QString("Angle: (%1)").arg(qsh));
}

void NCTI::NctiQtCommandConsole::GetVectorFunc(const NctiVector& vec)
{
    double x = vec.x();
    double y = vec.y();
    double z = vec.z();
    QString qsx = QString::number(x, 'g', 16);
    QString qsy = QString::number(y, 'g', 16);
    QString qsz = QString::number(z, 'g', 16);
    appendMessageLog(QString("Vector: (%1, %2, %3)").arg(qsx).arg(qsy).arg(qsz));
}

void NctiQtCommandConsole::GetMidPositionFunc(const NctiPosition& pt)
{
    double x = pt.x();
    double y = pt.y();
    double z = pt.z();
	QString qsx = QString::number(x, 'g', 16);
	QString qsy = QString::number(y, 'g', 16);
	QString qsz = QString::number(z, 'g', 16);
	appendMessageLog(QString("Mid Position: (%1, %2, %3)").arg(qsx).arg(qsy).arg(qsz));
}

void NCTI::NctiQtCommandConsole::GetCenterFunc(const NctiPosition& pt)
{
    double x = pt.x();
    double y = pt.y();
    double z = pt.z();
	QString qsx = QString::number(x, 'g', 16);
	QString qsy = QString::number(y, 'g', 16);
	QString qsz = QString::number(z, 'g', 16);
	appendMessageLog(QString("Center Position: (%1, %2, %3)").arg(qsx).arg(qsy).arg(qsz));
}

bool NctiQtCommandConsole::eventFilter(QObject* w, QEvent* e)
{
	if (w == this) 
	{
		auto type = e->type();
		if (type == QEvent::InputMethodQuery)
		{
			restoreDefaultCharFormat();
		}
	}
	return QTextEdit::eventFilter(w, e);
}

void NctiQtCommandConsole::keyPressEvent(QKeyEvent* event)
{
	QList<int> skip = { Qt::Key_Enter, Qt::Key_Left, Qt::Key_Right };
	if ((Qt::NoModifier == event->modifiers() || Qt::KeypadModifier == event->modifiers()) && !skip.contains(event->key()))
	{
		fixTextCursor();
	}

	// 如果按下回车键
	if (event->key() == Qt::Key_Return) 
	{
		// TODO: 提前取出最后一行输入的内容
		QString content = getLastBlockContent();
		m_history->append(content);
		if (!content.isEmpty()) {
			m_skipCodeMesssage = true;
			getExecutor()->excuteCommand(content);
			m_skipCodeMesssage = false;

			if (getExecutor()->getStderrtMessage().isEmpty() && getExecutor()->getStdoutMessage().isEmpty()) {
				newPrefixLine();
			}
		}
		else {
			newPrefixLine();
		}	

		event->accept();
		return;
	}
	else if (event->key() == Qt::Key_Backspace) {
		if (blockOnlyPrefix(document()->lastBlock())) {
			event->accept();
			return;
		}
	}
	else if (event->key() == Qt::Key_Up) {
		auto content = m_history->previous();
		if (!content.isNull()) {
			setLastBlockContent(content);
		}
		event->accept();
		return;
	}
	else if (event->key() == Qt::Key_Down) {
		auto content = m_history->next();
		if (!content.isNull()) {
			setLastBlockContent(content);
		}
		event->accept();
		return;
	}
	
	if (blockOnlyPrefix(document()->lastBlock())) {
		restoreDefaultCharFormat();
	}
	QTextEdit::keyPressEvent(event);
}

void NctiQtCommandConsole::inputMethodEvent(QInputMethodEvent* event)
{
	//// 获取预编辑文本
	//QString preeditText = event->preeditString();
	//qDebug() << "Preedit text:" << preeditText;

	//// 创建 QTextCharFormat 对象，设置文本格式
	//QTextCharFormat format;
	//format.setForeground(Qt::blue);   // 设置文本颜色为蓝色
	//format.setFontPointSize(12);      // 设置文本字体大小为 12

	//// 为每个字符设置 TextFormat 属性
	//QList<QInputMethodEvent::Attribute> attributes;

	//// 遍历预编辑文本的每个字符，设置格式
	//for (int i = 0; i < preeditText.length(); ++i) {
	//	QInputMethodEvent::Attribute attr(QInputMethodEvent::TextFormat, i, 1, format);
	//	attributes.append(attr);
	//}

	//// 将创建的属性添加到事件中
	//event->setAttributes(attributes);

	// 调用父类的实现继续处理事件
	fixTextCursor();
	QTextEdit::inputMethodEvent(event);
}

void NctiQtCommandConsole::wheelEvent(QWheelEvent* e)
{
	if (QApplication::keyboardModifiers() == Qt::ControlModifier)
	{
        int delta = e->angleDelta().y();
		if (delta > 0) {
			zoomIn();
		}
		else {
			zoomOut();
		}
		e->accept();
	}
	else {
		QTextEdit::wheelEvent(e);
	}
}

void NctiQtCommandConsole::contextMenuEvent(QContextMenuEvent* event)
{
	QMenu menu(this);
	QAction* action1 = menu.addAction(QStringLiteral("清空"));
	connect(action1, &QAction::triggered, this, &NctiQtCommandConsole::clear);
	menu.exec(event->globalPos());
}

void NctiQtCommandConsole::onCursorPositionChanged()
{
	// 如果是在最后一行且只有prefix时调整charformat
	auto tc = textCursor();
	if (tc.position() == document()->lastBlock().position() + m_codePrefix.length()) {
		tc.setCharFormat(m_defaultCharFormat);
	}
}

void NctiQtCommandConsole::fixTextCursor()
{
	QTextCursor cursor = textCursor();
	if (cursor.hasSelection())
	{
		int start = cursor.selectionStart();
		int end = cursor.selectionEnd();
		if (start > end) {
			qSwap(start, end);
		}

		int avaStart = document()->lastBlock().position() + m_codePrefix.length();
		int avaEnd = document()->lastBlock().position() + document()->lastBlock().length();

		if (end > avaStart) {
			if (start < avaStart) {
				start = avaStart;
			}
			cursor.setPosition(start);
			cursor.movePosition(QTextCursor::Right, QTextCursor::KeepAnchor, end - start);
		}
		else {
			cursor.movePosition(QTextCursor::MoveOperation::End);
		}

		cursor.setCharFormat(m_defaultCharFormat);
		setTextCursor(cursor);
	}
	else if (cursor.block() != document()->lastBlock() || 
		(cursor.position() < document()->lastBlock().position() + m_codePrefix.length()))
	{
		cursor.movePosition(QTextCursor::End, QTextCursor::MoveAnchor);
		cursor.setCharFormat(m_defaultCharFormat);
		setTextCursor(cursor);
	}
	else {
		cursor.setCharFormat(m_defaultCharFormat);
		setTextCursor(cursor);
	}
}

bool NctiQtCommandConsole::blockOnlyPrefix(const QTextBlock& block) const
{
	return block.text() == m_codePrefix;
}

QString NctiQtCommandConsole::getLastBlockContent() const
{
	QString content;

	auto block = document()->lastBlock();
	while (block.isValid()) {
		auto con = block.text();
		if(content.isEmpty()){
			content.prepend(con);
		}
		else {
			content.prepend(con + "\n");
		}
		if (con.startsWith(m_codePrefix)) {
			break;
		}
		block = block.previous();
	}
	
	return content.mid(m_codePrefix.length());
}

void NctiQtCommandConsole::setLastBlockContent(const QString& content)
{
	auto tc = textCursor();
	auto beginPosition = document()->lastBlock().position() + m_codePrefix.length();
	auto endPosition = beginPosition + document()->lastBlock().length()- m_codePrefix.length()-1;
	tc.setPosition(beginPosition);

	if (endPosition>beginPosition) {
		tc.setPosition(endPosition, QTextCursor::KeepAnchor);
		tc.removeSelectedText();
		setTextCursor(tc);

		tc = textCursor();
	}
	tc.setCharFormat(m_defaultCharFormat);
	tc.insertText(content);
}

void NctiQtCommandConsole::restoreDefaultCharFormat()
{
	auto tc = textCursor();
	tc.setCharFormat(m_defaultCharFormat);
	//setTextCursor(tc);
}

void NctiQtCommandConsole::excuteCommand(const QString& content)
{
	m_HistoryPos = -1;
	for (auto i = m_History.size() - 1; i >= 0; i--) {
		if (m_History[i] == content) {
			m_History.erase(m_History.begin() + i);
			break;
		}
	}
	m_History.push_back(content);

	if (content.compare("HELP", Qt::CaseInsensitive) == 0) {
		appendMessageCode(QString("%1").arg(content));
		appendMessageLog("Commands:");
		for (int i = 0; i < m_Commands.size(); i++)
			appendMessageLog(QString("- %1").arg(m_Commands[i]));
	}
	else if (content.compare("HISTORY", Qt::CaseInsensitive) == 0)
	{
		appendMessageCode(QString("%1").arg(content));
		auto first = m_History.size() - 10;
		for (auto i = first > 0 ? first : 0; i < m_History.size(); i++)
			appendMessageLog(QString("%1: %2").arg(i).arg(m_History[i]));
	}
	else
	{
		if(m_executor)
			m_executor->excuteCommand(content);
	}
}

void NctiQtCommandConsole::changeBlockForeground(QTextEdit* textEdit, int first, int last, const QColor& color)
{
	// 选择内容
	auto textCursor = textEdit->textCursor();
	textCursor.setPosition(first);
	textCursor.movePosition(QTextCursor::Right, QTextCursor::KeepAnchor, last - first);

	// 设置字体颜色
	auto lastCharFormat = textCursor.charFormat();
	auto charFormat = textCursor.charFormat();
	charFormat.setForeground(color);
	textCursor.setCharFormat(charFormat);
	textEdit->setTextCursor(textCursor);

	// 还原光标
	textCursor = textEdit->textCursor();
	textCursor.movePosition(QTextCursor::End, QTextCursor::MoveAnchor);
	textCursor.setCharFormat(m_defaultCharFormat);
	textEdit->setTextCursor(textCursor);
}
