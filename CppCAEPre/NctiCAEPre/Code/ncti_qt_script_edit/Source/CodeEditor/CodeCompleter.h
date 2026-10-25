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

#include <QObject>
#include <QMap>
#include <QStringList>
#include <QStringListModel>
#include <QStyledItemDelegate>
#include <QTextEdit>

class QListView;
namespace NCTI
{
	class CodeEditor;
	class CodeCompleterItemDelegate;
	class CodeCompleterModel;
	class CodeCompleter : public QObject
	{
		Q_OBJECT 
	public:
		explicit CodeCompleter(const QString &config, QTextEdit* parent);
		~CodeCompleter();

		Q_SIGNAL void sigActivated(QString content, int from, int len);

	private:
		void setupConfig(const QString &path);
		void setupCompleterView();

		QString getCompleterPrefix(int *from = nullptr, int *len = nullptr);
		QPoint getCompleterPos(const QSize &size);
		QSize getCompleterSize(const QStringList &content);
		QStringList getCompleterContent(const QString &prefix);

		Q_SLOT void updateCompleterPosition();
		void updateCompleter(const QPoint& pos, const QSize& size, const QStringList& content);
		void hideCompleter();
		bool isCompleterVisible();

		void selectFirstCompleteItem();
		void selectNextCompleteItem();
		void selectPreviousCompleteItem();
		QString getCompleteItemContent(const QModelIndex &modelIndex) const;

		void updateFont();
		void updateActiveWindow(QWidget *widget);
		void insertCompletion(QString s, int from, int len);

		bool eventFilter(QObject* w, QEvent* e) override;
		Q_SLOT void onTextChanged();
		Q_SLOT void onCursorPositionChanged();
		Q_SLOT void onCompleteItemClicked(const QModelIndex& index);

	private:
		QTextEdit* m_codeEdit;
		QWidget* m_window;
		QMap<QString, QStringList> m_name2contentList;
		QListView* m_listView;
		CodeCompleterItemDelegate* m_delegate;
		CodeCompleterModel* m_model;
		bool m_mousePressed;
		bool m_autoInsertCompletion;
	};	

	class CodeCompleterItemDelegate : public QStyledItemDelegate 
	{
		friend class CodeCompleter;
		Q_OBJECT
	public:
		QSize sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const override;
	private:
		explicit CodeCompleterItemDelegate(QObject* parent = nullptr);
	};

	class CodeCompleterModel : public QStringListModel
	{
		friend class CodeCompleter;
		Q_OBJECT
	public:
		Qt::ItemFlags flags(const QModelIndex& index) const override;
	private:
		explicit CodeCompleterModel(QObject* parent = nullptr);
	};
};