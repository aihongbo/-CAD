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

#include "CodeCompleter.h"
#include <QStringListModel>
#include <QTextEdit>
#include <QListView>
#include <QTextCursor>
#include <QAbstractTextDocumentLayout>
#include <QScrollBar>
#include <QTextBlock>
#include <QTextLayout> 
#include <QEvent>
#include <QDebug>
#include <QKeyEvent>
#include <QScreen>
#include <QJsonDocument>
#include <QJsonArray>
#include <QApplication>
#include <QFile>

#if QT_VERSION_MAJOR >= 6
#include <QRegularExpression>
#else
#include <QRegExp>
#endif

#include "CodeEditor.h"

static constexpr QMargins ITEM_MARGIN{ 1,1,1,1 };

using namespace NCTI;

QSize CodeCompleterItemDelegate::sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const
{
	QString text = index.data(Qt::DisplayRole).toString();
	QFontMetrics fm(option.font);
	int width = fm.horizontalAdvance(text);
	int height = fm.height();
	return QSize(width+ITEM_MARGIN.left()+ITEM_MARGIN.right(), height+ ITEM_MARGIN.top() + ITEM_MARGIN.bottom());
}

CodeCompleterItemDelegate::CodeCompleterItemDelegate(QObject* parent)
	: QStyledItemDelegate(parent)
{}

Qt::ItemFlags CodeCompleterModel::flags(const QModelIndex& index) const
{
	return Qt::ItemFlag::ItemIsEnabled | Qt::ItemFlag::ItemIsSelectable;
}

CodeCompleterModel::CodeCompleterModel(QObject* parent)
	: QStringListModel(parent)
{}

CodeCompleter::CodeCompleter(const QString& config, QTextEdit* parent)
	: QObject(parent)
	, m_codeEdit(parent)
	, m_window(nullptr)
	, m_listView(new QListView(parent))
	, m_delegate(new CodeCompleterItemDelegate(this))
	, m_model(new CodeCompleterModel(this))
	, m_mousePressed(false)
	, m_autoInsertCompletion(true)
{
	setupConfig(config);
	setupCompleterView();

	m_codeEdit->installEventFilter(this);
	m_codeEdit->viewport()->installEventFilter(this);
	m_listView->installEventFilter(this);
	connect(m_codeEdit, &QTextEdit::cursorPositionChanged, this, &CodeCompleter::onCursorPositionChanged);
}

CodeCompleter::~CodeCompleter()
{}

void CodeCompleter::setupConfig(const QString& path)
{
	QFile file(path);
	if (!file.exists() || !file.open(QIODevice::ReadOnly)) {
		qWarning() << "could not open file." << path;
		return;
	}
	QJsonParseError error;
	auto jsonDocument = QJsonDocument::fromJson(file.readAll(), &error);
	file.close();

	if (error.error != QJsonParseError::NoError) {
		qWarning() << "could not parse json." << path;
		return;
	}

	auto varMap = jsonDocument.toVariant().toMap();
	for (auto iter = varMap.cbegin(); iter != varMap.cend(); iter++)
	{
		m_name2contentList.insert(iter.key(), iter.value().toStringList());
	}
}

void CodeCompleter::setupCompleterView()
{
	m_listView->setWindowFlags(Qt::FramelessWindowHint | Qt::ToolTip);
	m_listView->setModel(m_model);
	m_listView->setItemDelegate(m_delegate);
	m_listView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	m_listView->setAlternatingRowColors(true);
	m_listView->setContentsMargins(0, 0, 0, 0);
	m_listView->viewport()->setContentsMargins(0, 0, 0, 0);
	m_listView->hide();
	connect(m_listView, &QListView::clicked, this, &CodeCompleter::onCompleteItemClicked);
}

QString CodeCompleter::getCompleterPrefix(int* from, int* len)
{
#if QT_VERSION_MAJOR >= 6
    QRegularExpression regExp("[\\r\\n\\t\\s,\\(\\)\\[\\]]");
#else
    QRegExp regExp("[\\r\\n\\t\\s,\\(\\)\\[\\]]");
#endif

	QTextEdit* textEdit = qobject_cast<QTextEdit*>(parent());

	auto originalTextCursor = textEdit->textCursor();	
	auto originalBlock = originalTextCursor.block();
	auto textCursor = textEdit->document()->find(regExp, originalTextCursor.position(), QTextDocument::FindBackward);
	QString prefix;

	if (textCursor.isNull() || textCursor.blockNumber()!= originalBlock.blockNumber())
	{
		prefix = textEdit->toPlainText().mid(originalBlock.position(), originalTextCursor.position()- originalBlock.position());
		if (from && len) {
			*from = originalBlock.position();
			*len = originalTextCursor.position() - originalBlock.position();
		}
	}
	else{
		prefix = textEdit->toPlainText().mid(textCursor.position(), originalTextCursor.position() - textCursor.position());
		if (from && len) {
			*from = textCursor.position();
			*len = originalTextCursor.position() - textCursor.position();
		}
	}

	return prefix;
}

QPoint CodeCompleter::getCompleterPos(const QSize& size)
{
	m_codeEdit->textCursor();
	auto cursor = m_codeEdit->textCursor();
	auto cursorRect = m_codeEdit->cursorRect(cursor);
	auto point = m_codeEdit->viewport()->mapToGlobal(cursorRect.bottomLeft());

	QRect rect(point, size);
	QRect screenRect = m_codeEdit->screen()->geometry();
	int dx = rect.right() + 10 - screenRect.right();
	if (dx > 0) {
		point.rx() -= dx;
	}

	int dy = rect.bottom() + 10 - screenRect.bottom();
	if (dy > 0) {
		point.ry() -= rect.height() + cursorRect.height();
	}

	return point;
}

QSize CodeCompleter::getCompleterSize(const QStringList& content)
{
	auto fm = m_listView->fontMetrics();

	int height = (fm.height() + 2) * content.count();
	height += m_listView->viewport()->contentsMargins().top() + m_listView->viewport()->contentsMargins().bottom();
	height += m_listView->contentsMargins().top() + m_listView->contentsMargins().bottom();
	height += ITEM_MARGIN.top() + ITEM_MARGIN.bottom();

	int width = 0;
	for (auto iter = content.cbegin(); iter != content.cend(); iter++) {
		width = qMax(width, fm.horizontalAdvance(*iter));
	}

	width += m_listView->viewport()->contentsMargins().left() + m_listView->viewport()->contentsMargins().right();
	width += m_listView->contentsMargins().left() + m_listView->contentsMargins().right();
	width += m_listView->verticalScrollBar()->width();
	width += ITEM_MARGIN.left() + ITEM_MARGIN.right();

	return QSize(width, qMin(height, 500));
}

QStringList CodeCompleter::getCompleterContent(const QString& prefix)
{
	QStringList content;
	auto&& nodes = prefix.split('.', Qt::KeepEmptyParts);
	if (nodes.count()>=2)
	{		
		auto objIndex = nodes.count() - 2;
		auto funcIndex = nodes.count() - 1;
		auto iter = m_name2contentList.find(nodes[objIndex] + '.');
		if (iter!= m_name2contentList.end())
		{
			if (nodes[funcIndex].isEmpty())
			{
				content.append(iter.value());
			}
			else
			{
				for (auto viter = iter.value().cbegin(); viter != iter.value().cend(); ++viter)
				{
					if (viter->startsWith(nodes[funcIndex], Qt::CaseInsensitive)) {
						content.append(*viter);
					}
				}
			}
		}
	}
	/*else if (QString("cmd_ncti_").startsWith(prefix))
	{
		for (auto iter = m_name2contentList.cbegin(); iter != m_name2contentList.cend(); ++iter)
		{
			if (iter.key().startsWith("cmd_ncti_")) {
				content.append(iter.value());
			}
		}
	}
	else if (prefix.startsWith("cmd_ncti_")) 
	{
		for (auto iter = m_name2contentList.cbegin(); iter != m_name2contentList.cend(); ++iter)
		{
			if (iter.key().startsWith(prefix)) {
				content.append(iter.value());
			}
		}
	}*/
	else
	{
		for (auto iter = m_name2contentList.cbegin(); iter != m_name2contentList.cend(); ++iter)
		{
			if (iter.key().contains(".")) {
				continue;
			}

			// 对cmd_ncti_的模糊匹配，由于命令暂时以"cmd_ncti_create_box", "box", Point, X, Y, Z形式，取出命令名称进行匹配，无须以起始匹配（避免过多匹配，需要prefix长度为2以上才进行匹配）
			// 对于模糊匹配的cmd，自动加上doc.RunCommand
			if (iter.key().startsWith("cmd_ncti_", Qt::CaseInsensitive))
			{
				if (prefix.length() >= 2 && iter.key().contains(prefix))
				{
					for (auto viter = iter.value().cbegin(); viter != iter.value().cend(); ++viter)
					{
						content.append(QString("doc.RunCommand(%1)").arg(*viter));
					}
				}
			}
			else 
			{
				for (auto viter = iter.value().cbegin(); viter != iter.value().cend(); ++viter)
				{
					if (viter->startsWith(prefix, Qt::CaseInsensitive)) {
						content.append(*viter);
					}
				}
			}
			
		}
	}
	return content;
}

void CodeCompleter::updateCompleterPosition()
{
	m_listView->move(getCompleterPos(m_listView->size()));
}

void CodeCompleter::updateCompleter(const QPoint& pos, const QSize &size, const QStringList& content)
{
	m_model->setStringList(content);
	if (content.isEmpty()) {
		m_listView->hide();
	}
	else {
		m_listView->setFixedSize(size);
		m_listView->move(pos);
		m_listView->raise();
		m_listView->show();
		m_listView->setCurrentIndex(m_model->index(0));
	}
}

void CodeCompleter::hideCompleter()
{
	if (m_listView->isHidden()) {
		return;
	}
	m_listView->hide();
	//m_model->setStringList({});
}

bool CodeCompleter::isCompleterVisible()
{
	return m_listView->isVisible();
}

void CodeCompleter::selectFirstCompleteItem()
{
	if (m_model->rowCount()==0) {
		return;
	}
	m_listView->setCurrentIndex(m_model->index(0));
}

void CodeCompleter::selectNextCompleteItem()
{
	auto modelIndex = m_listView->currentIndex();
	if (!modelIndex.isValid()) {
		selectFirstCompleteItem();
		return;
	}
	if (modelIndex.row()+1>= m_model->rowCount()) {
		return;
	}
	m_listView->setCurrentIndex(m_model->index(modelIndex.row()+1));
}

void CodeCompleter::selectPreviousCompleteItem()
{
	auto modelIndex = m_listView->currentIndex();
	if (!modelIndex.isValid()) {
		selectFirstCompleteItem();
		return;
	}
	if (modelIndex.row() - 1 < 0) {
		return;
	}
	m_listView->setCurrentIndex(m_model->index(modelIndex.row() - 1));
}

QString CodeCompleter::getCompleteItemContent(const QModelIndex& modelIndex) const
{
	return m_model->data(modelIndex).toString();
}

void CodeCompleter::updateFont()
{
	m_listView->setFont(m_codeEdit->font());
}

void CodeCompleter::updateActiveWindow(QWidget* widget)
{
	if (widget == m_window) {
		return;
	}

	if (m_window != nullptr) {
		m_window->removeEventFilter(this);
	}
	m_window = widget;
	if (m_window != nullptr) {
		m_window->installEventFilter(this);
	}
}

void CodeCompleter::insertCompletion(QString s, int from, int len)
{
	auto tc = m_codeEdit->textCursor();
	tc.setPosition(from);
	tc.movePosition(QTextCursor::Right, QTextCursor::KeepAnchor, len);
	tc.insertText(s);
	m_codeEdit->setTextCursor(tc);
}

bool CodeCompleter::eventFilter(QObject* w, QEvent* e)
{
	int type = e->type();
	if (w == m_codeEdit)
	{
		/*if (type == QEvent::CursorChange)
		{
			hideCompleter();
		}*/
		/*else if (type == QEvent::InputMethodQuery) 
		{
			QMetaObject::invokeMethod(this, "onTextChanged", Qt::QueuedConnection);
		}*/
		//qDebug() << __FUNCTION__ << e->type();
		if (type == QEvent::KeyPress)
		{
			QKeyEvent* keyEvent = reinterpret_cast<QKeyEvent*>(e);
			if (isCompleterVisible())
			{
				if (keyEvent->key() == Qt::Key_Up) {
					selectPreviousCompleteItem();
					return true;
				}
				else if (keyEvent->key() == Qt::Key_Down) {
					selectNextCompleteItem();
					return true;
				}
				else if (keyEvent->key() == Qt::Key_Return) {
					auto modelIndex = m_listView->currentIndex();
					if (modelIndex.isValid()) {
						onCompleteItemClicked(modelIndex);
					}
					else {
						hideCompleter();
					}
					return true;
				}
				else if (keyEvent->key() == Qt::Key_Escape) {
					hideCompleter();
					return true;
				}
				else if (keyEvent->key() == Qt::Key_Tab) {
					auto modelIndex = m_listView->currentIndex();
					if (modelIndex.isValid()) {
						onCompleteItemClicked(modelIndex);
					}
					else {
						hideCompleter();
					}
					return true;
				}
				else {
					QMetaObject::invokeMethod(this, "onTextChanged", Qt::QueuedConnection);
				}
			}
			else if (keyEvent->modifiers() == Qt::NoModifier) {
				QMetaObject::invokeMethod(this, "onTextChanged", Qt::QueuedConnection);
			}
			else {
			}
		}
		else if (type == QEvent::FocusOut) {
			if (!m_listView->window()->isActiveWindow()) {
				hideCompleter();
			}
		}
		else if (type == QEvent::Move || type == QEvent::Resize || type == QEvent::Wheel) {
			hideCompleter();
		}
		else if (type == QEvent::FontChange) {
			hideCompleter();
			updateFont();
		}
	}
	else if (w == m_codeEdit->viewport()) 
	{
		if (type == QEvent::MouseButtonPress) {
			m_mousePressed = true;
		}
		else if (type == QEvent::MouseButtonRelease) {
			m_mousePressed = false;
		}
	}
	else if (w == m_window)
	{
		if (type == QEvent::Move || type == QEvent::Resize) {
			hideCompleter();
		}
	}
	else if (w == m_listView) 
	{
		if (type == QEvent::Show) {
			updateActiveWindow(m_codeEdit->window());
		}
	}
	return QObject::eventFilter(w, e);
}

void CodeCompleter::onTextChanged()
{
	auto&& prefix = getCompleterPrefix();
	if (prefix.isEmpty()) {
		hideCompleter();
		return;
	}

	auto&& content = getCompleterContent(prefix);
	auto&& size = getCompleterSize(content);
	auto&& point = getCompleterPos(size);

	QRect rect(point, size);
	QRect screenRect = m_codeEdit->screen()->geometry();
	int dx = rect.right() + 10 - screenRect.right();
	if (dx > 0){
		point.rx() -= dx;
	}

	int dy = rect.bottom() + 10 - screenRect.bottom();
	if (dy > 0){
		point.ry() -= dy;
	}

	updateCompleter(point, size, content);
}

void CodeCompleter::onCursorPositionChanged()
{
	if (m_mousePressed) {
		hideCompleter();
	}
}

void CodeCompleter::onCompleteItemClicked(const QModelIndex& index)
{
	int from = -1;
	int len = 0;
	QString prefix = getCompleterPrefix(&from, &len);
	if (prefix.contains('.')) {
		auto fixed = prefix.section('.', -1, -1);
		from = from + len - fixed.length();
		len = fixed.length();
	}
	if (m_autoInsertCompletion){
		insertCompletion(getCompleteItemContent(index), from, len);
	}
	else {
        Q_EMIT sigActivated(getCompleteItemContent(index), from, len);
	}
	hideCompleter();
}
