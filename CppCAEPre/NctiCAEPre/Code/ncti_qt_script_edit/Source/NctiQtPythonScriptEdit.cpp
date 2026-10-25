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

#include "NctiQtPythonScriptEdit.h"

#include <QMenu>
#include <QPushButton>
#include <QToolButton>
#include <QMessageBox>
#include <QHBoxLayout>
#include <QFileDialog>
#include <QScrollBar>
#include <QWidgetAction>
#include <QTextEdit>
#include <QTextDocumentFragment>
#include <QDebug>

#include "BreakpointArea.h"
#include "CodeEditor.h"
#include "ExecuteHistory.h"

#include "NctiQtScriptExecutor.h"
#include "NctiQtScriptDebugger.h"
#include "NctiQtScriptScene.h"

using namespace NCTI;

NctiQtPythonScriptEdit::NctiQtPythonScriptEdit(QWidget* parent)
    : QFrame(parent)
{}

NctiQtPythonScriptEdit::~NctiQtPythonScriptEdit()
{}

void NctiQtPythonScriptEdit::setup()
{
	m_executor = new NctiQtScriptExecutor(this);
	setWindowTitle(QStringLiteral("脚本编辑"));

	setupButton();
	setupButtonBar();
	setupUntitledScript();
	setupDebugger();
	setupScroll();
}

void NctiQtPythonScriptEdit::setExecutor(NctiQtScriptExecutor* script)
{
	m_executor = script;
}

NctiQtScriptExecutor* NctiQtPythonScriptEdit::getExecutor()
{
	return m_executor;
}

const QList<NctiQtScriptScene*>& NctiQtPythonScriptEdit::getSceneList() const
{
	return m_sceneList;
}

NctiQtScriptScene* NctiQtPythonScriptEdit::getScene() const
{
	return m_sceneList.first();
}

NctiQtScriptDebugger* NctiQtPythonScriptEdit::getDebugger()
{
	return getScene()->getDebugger();
}

QTextEdit* NctiQtPythonScriptEdit::getEditor()
{
	return getScene()->getEditor();
}

void NctiQtPythonScriptEdit::excute()
{
	save();

	auto content = getEditor()->textCursor().selectedText();
	QTextDocumentFragment fragment = QTextDocumentFragment::fromPlainText(content);
	content = fragment.toPlainText();
	if (content.isEmpty())
	{
		content = getEditor()->toPlainText();
	}

	getExecutor()->excuteCommand(content, true);
}

void NctiQtPythonScriptEdit::clearObject()
{
	getExecutor()->excuteCommand("doc.Clear()\nview.ClearScene()\ndoc.ResetCaseResult()\ndoc.ClearPyVariables()");
}

void NctiQtPythonScriptEdit::clearContent() const
{
	getScene()->clear();
}

void NctiQtPythonScriptEdit::load(int index) const
{
	getScene()->readFromExecuteHistory(index);
}

void NctiQtPythonScriptEdit::save() const
{
	getScene()->writeToExecuteHistory();
}

void NctiQtPythonScriptEdit::open(const QString& path)
{
    auto scene = getScene();
    saveSceneContentToFileOrNot(scene);
    scene->close();
    m_closeButton->setEnabled(false);

    if (path.isEmpty()) {
        return;
    }
    getScene()->open(path);
    m_closeButton->setEnabled(true);
}

void NctiQtPythonScriptEdit::save(const QString& path) const
{
    getScene()->save(path);
}

void NctiQtPythonScriptEdit::startDebug()
{
	save();
	getDebugger()->setContent(getEditor()->toPlainText());
	getDebugger()->runNextBreakpoint();
}

void NctiQtPythonScriptEdit::stopDebug()
{
	getDebugger()->stop();
}

void NctiQtPythonScriptEdit::debugNextBreakpoint()
{
	getDebugger()->runNextBreakpoint();
}

void NctiQtPythonScriptEdit::debugNextLine()
{
	getDebugger()->runNextStep();
}

void NctiQtPythonScriptEdit::removeAllBreakpoint()
{
	getDebugger()->removeAllBreakpoint();
	qobject_cast<CodeEditor*>(getEditor())->getBreakpointArea()->clearBreakpoint();
}

void NctiQtPythonScriptEdit::enableBreakpoint()
{
	getDebugger()->enableAllBreakpoint(true);
	qobject_cast<CodeEditor*>(getEditor())->getBreakpointArea()->enableAllBreakpoint(true);
}

void NctiQtPythonScriptEdit::disableBreakpoint()
{
	getDebugger()->enableAllBreakpoint(false);
	qobject_cast<CodeEditor*>(getEditor())->getBreakpointArea()->enableAllBreakpoint(false);
}

void NctiQtPythonScriptEdit::configButtonIcon(Button button, const QIcon& icon)
{
	m_button2Icon.insert(button, icon);
}

void NctiQtPythonScriptEdit::configScene(bool isDark)
{
	m_sceneConfig.isDark = isDark;
}

void NctiQtPythonScriptEdit::setHistoryFilePath(const QString& filePath)
{
    ExecuteHistory::instance()->config(filePath);
}

void NctiQtPythonScriptEdit::newScene()
{
	appendScene(new NctiQtScriptScene(m_sceneConfig.isDark, getExecutor(), this));
}

void NctiQtPythonScriptEdit::resizeEvent(QResizeEvent* event)
{
	QFrame::resizeEvent(event);
	updateScrollToPosition();
}

void NctiQtPythonScriptEdit::showEvent(QShowEvent* event)
{
	QFrame::showEvent(event);
	updateScrollToPosition();
}

bool NctiQtPythonScriptEdit::saveSceneContentToFileOrNot(NctiQtScriptScene* scene)
{
	if (scene->isContentChanged())
	{
        const auto& filePath = scene->getPath();
        const auto& message = filePath.isEmpty() 
            ? QStringLiteral("是否保存当前内容到指定文件？") 
            : QStringLiteral("是否保存当前内容到\n%1").arg(filePath);
        
        if (popupQuestion(message)) {
            saveSceneContentToFile(scene);
            return true;
        }
	}
    return false;
}

void NctiQtPythonScriptEdit::saveSceneContentToFile(NctiQtScriptScene* scene)
{
	if (scene->getPath().isEmpty())
	{
		QString path = QFileDialog::getSaveFileName(nullptr, QStringLiteral("保存脚本"), "", QStringLiteral("Python文件 (*.py);;所有文件 (*)"));
		if (!path.isEmpty())
		{
			scene->setPath(path);
			scene->save();
		}
	}
	else
	{
		scene->save();
	}
}

bool NctiQtPythonScriptEdit::popupQuestion(const QString& message)
{
    QMessageBox msgBox(QMessageBox::Question, "", message, QMessageBox::Yes | QMessageBox::No, this);
    msgBox.setWindowFlags(msgBox.windowFlags() | Qt::WindowStaysOnTopHint);

    QRect rect = this->geometry();
    QSize sz = msgBox.sizeHint();

    int localX = rect.left() + (rect.width() - sz.width()) / 2;
    int localY = rect.top() + (rect.height() - sz.height()) / 2;
    QPoint globalPos = this->mapToGlobal(QPoint(localX, localY - 50));
    msgBox.move(globalPos);

    int flag = msgBox.exec();
    return (QMessageBox::Yes == flag);
}

void NctiQtPythonScriptEdit::installTooltip(QObject* object, const QString& tip)
{
	
}

void NctiQtPythonScriptEdit::setupButton()
{
	auto newButton = [this](const QString& name, const QString& tip, QWidget* parent)
		{
			QPushButton* button = new QPushButton(QStringLiteral(""), parent);
			button->setObjectName(name);
			button->setToolTip(tip);
			button->setFocusPolicy(Qt::NoFocus);
			installTooltip(button, tip);
			return button;
		};
	auto newToolButton = [this](const QString& name, const QString& tip, QWidget* parent)
		{
			QToolButton* button = new QToolButton(parent);
			button->setText("");
			button->setObjectName(name);
			button->setPopupMode(QToolButton::InstantPopup);
			button->setToolTip(tip);
			installTooltip(button, tip);
			return button;
		};

	m_runButton = newButton("pushButton_runScript", QStringLiteral("执行脚本"), this);
	m_cleanButton = newButton("pushButton_cleanScript", QStringLiteral("清空脚本"), this);
	m_loadToolButton = newToolButton("pushButton_loadLast", QStringLiteral("加载上次执行脚本"), this);
	m_loadToolMenu = new QMenu(m_loadToolButton);
	m_loadToolButton->setMenu(m_loadToolMenu);

	connect(m_runButton, &QPushButton::clicked, this, &NctiQtPythonScriptEdit::excute);
	connect(m_cleanButton, &QPushButton::clicked, this, &NctiQtPythonScriptEdit::clearObject);
	connect(m_loadToolButton, &QToolButton::clicked, this, [this]
		{
			load();
		});
	connect(m_loadToolMenu, &QMenu::aboutToShow, this, [this]
		{
			m_loadToolMenu->clear();
			auto items = ExecuteHistory::instance()->names();
			int index = 0;
			for (auto &&item : items)
			{
				m_loadToolMenu->addAction(item)->setData(index);
				index++;
			}
		});
	connect(m_loadToolMenu, &QMenu::triggered, this, [this](QAction *action)
		{
			load(action->data().toInt());
		});

	m_openButton = newButton("pushButton_open", QStringLiteral("打开脚本"), this);
	m_saveButton = newButton("pushButton_save", QStringLiteral("保存脚本"), this);
	m_closeButton = newButton("pushButton_close", QStringLiteral("关闭脚本"), this);
	setButtonEnable(ButtonClose, false);
	connect(m_openButton, &QPushButton::clicked, this, [this]
		{
			auto scene = getScene();
			saveSceneContentToFileOrNot(scene);

			QString path = QFileDialog::getOpenFileName(nullptr, QStringLiteral("打开脚本"), "", QStringLiteral("Python文件 (*.py);;所有文件 (*)"));
			if (path.isEmpty()) {
				return;
			}

			getScene()->open(path);
			m_closeButton->setEnabled(true);
		});
	connect(m_saveButton, &QPushButton::clicked, this, [this]
		{
			auto scene = getScene();
			saveSceneContentToFile(scene);
			m_closeButton->setEnabled(scene->getPath()!="");
		});
	connect(m_closeButton, &QPushButton::clicked, this, [this]
		{
			auto scene = getScene();
			saveSceneContentToFileOrNot(scene);
			scene->close();
			m_closeButton->setEnabled(false);
		});

	m_debugStartButton = newButton("pushButton_debugStart", QStringLiteral("开始调试"), this);
	m_debugStopButton = newButton("pushButton_debugStop", QStringLiteral("结束调试"), this);
	setButtonEnable(ButtonStopDebug, false);

	m_breakpointButton = newToolButton("pushButton_breakpoint", QStringLiteral("断点"), this);
	m_breakpointToolMenu = new QMenu(m_breakpointButton);
	m_breakpointButton->setMenu(m_breakpointToolMenu);

	m_breakpointRemoveAction = m_breakpointToolMenu->addAction(getButtonIcon(ButtonBreakpoint_Clear), QStringLiteral("移除所有断点"), this, &NctiQtPythonScriptEdit::removeAllBreakpoint);
	m_breakpointNextAction = m_breakpointToolMenu->addAction(getButtonIcon(ButtonBreakpoint_Next), QStringLiteral("下一个断点"), this, &NctiQtPythonScriptEdit::debugNextBreakpoint);
	m_breakpointSingleAction = m_breakpointToolMenu->addAction(getButtonIcon(ButtonBreakpoint_Single), QStringLiteral("下一行断点"), this, &NctiQtPythonScriptEdit::debugNextLine);
	m_breakpointDisableAction = m_breakpointToolMenu->addAction(getButtonIcon(ButtonBreakpoint_Disable), QStringLiteral("禁用断点"), this, &NctiQtPythonScriptEdit::disableBreakpoint);
	m_breakpointEnableAction = m_breakpointToolMenu->addAction(getButtonIcon(ButtonBreakpoint_Enable), QStringLiteral("启用断点"), this, &NctiQtPythonScriptEdit::enableBreakpoint);
	setButtonEnable(ButtonBreakpoint_Next, false);
	setButtonEnable(ButtonBreakpoint_Single, false);

	connect(m_debugStartButton, &QPushButton::clicked, this, &NctiQtPythonScriptEdit::startDebug);
	connect(m_debugStopButton, &QPushButton::clicked, this, &NctiQtPythonScriptEdit::stopDebug);
	
    // 自定义按钮
    m_customToolButton = newToolButton("pushButton_custom", QStringLiteral("自定义"), this);
    m_customToolButton->setVisible(false);
    connect(m_customToolButton, &QToolButton::clicked, this, [this] {
            Q_EMIT addCustomAction();
        }
    );

	setupButtonText();
}

void NctiQtPythonScriptEdit::setupButtonBar()
{
	auto newIndicator = [](QWidget* parent)
		{
			QWidget* indicator = new QWidget(parent);
			indicator->setObjectName("widget_indicator");
			return indicator;
		};

	QFrame* buttonFrame = new QFrame(this);
	buttonFrame->setObjectName("frame_buttonBackground");
	QHBoxLayout* buttonLayout = new QHBoxLayout(buttonFrame);
	buttonLayout->setContentsMargins(0, 0, 0, 0);
	buttonLayout->setSpacing(4);
	buttonLayout->addWidget(m_runButton);
	buttonLayout->addWidget(m_loadToolButton);
	buttonLayout->addWidget(m_cleanButton);
	buttonLayout->addWidget(newIndicator(this));
	buttonLayout->addWidget(m_openButton);
	buttonLayout->addWidget(m_saveButton);
	buttonLayout->addWidget(m_closeButton);
	buttonLayout->addWidget(newIndicator(this));
	buttonLayout->addWidget(m_debugStartButton);
	buttonLayout->addWidget(m_debugStopButton);
	buttonLayout->addWidget(m_breakpointButton);
    buttonLayout->addWidget(m_customToolButton);
	buttonLayout->addStretch(1);

	QVBoxLayout* layout = new QVBoxLayout(this);
	layout->setContentsMargins(0, 0, 0, 0);
	layout->setSpacing(0);
	layout->addWidget(buttonFrame);

	setLayout(layout);
}

void NctiQtPythonScriptEdit::setupButtonText()
{
	m_runButton->setText("运行");
	m_cleanButton->setText("清除");
	m_loadToolButton->setText("恢复");
	m_loadToolButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
	m_openButton->setText("打开");
	m_saveButton->setText("保存");
	m_closeButton->setText("关闭");
	m_debugStartButton->setText("调试");
	m_debugStopButton->setText("停止");
	m_breakpointButton->setText("断点");
	m_breakpointButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    m_customToolButton->setText("自定义");
    m_customToolButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
}

void NctiQtPythonScriptEdit::setupUntitledScript()
{
	newScene();
}

void NctiQtPythonScriptEdit::setupDebugger()
{
	connect(getDebugger(), &NctiQtScriptDebugger::sigCurrentBreakpointChanged, this, [this](int previous, int current)
		{
			if (current >= 0) {
				setButtonEnable(ButtonBreakpoint_Next, true);
				setButtonEnable(ButtonBreakpoint_Single, true);
			}
		});
	connect(getDebugger(), &NctiQtScriptDebugger::sigExecuteStateChanged, this, [this](int state)
		{
			if (state == NctiQtScriptDebugger::ExecuteStateRunning) {
				m_runButton->setChecked(false);
				m_cleanButton->setEnabled(false);
				m_loadToolButton->setEnabled(false);
				m_debugStartButton->setEnabled(false);
				m_debugStopButton->setEnabled(true);
				setButtonEnable(ButtonBreakpoint_Next, true);
				setButtonEnable(ButtonBreakpoint_Single, true);
				m_openButton->setEnabled(false);
				m_saveButton->setEnabled(false);
				m_closeButton->setEnabled(false);
                m_customToolButton->setEnabled(false);
			}
			else if (state == NctiQtScriptDebugger::ExecuteStateStopped) {
				m_runButton->setChecked(true);
				m_cleanButton->setEnabled(true);
				m_loadToolButton->setEnabled(true);
				m_debugStartButton->setEnabled(true);
				m_debugStopButton->setEnabled(false);
				setButtonEnable(ButtonBreakpoint_Next, false);
				setButtonEnable(ButtonBreakpoint_Single, false);
				m_openButton->setEnabled(true);
				m_saveButton->setEnabled(true);
				m_closeButton->setEnabled(getScene()->getPath() != "");
                m_customToolButton->setEnabled(true);
			}
			else {

			}
		});
}

void NctiQtPythonScriptEdit::setupScroll()
{
	m_scrollToTopButton = new QPushButton(this);
	m_scrollToTopButton->setObjectName("pushButton_scrollToTop");
	connect(m_scrollToTopButton, &QPushButton::clicked, this,
		[this]
		{
			auto bar = getEditor()->verticalScrollBar();
			bar->setValue(bar->minimum());
		});
	m_scrollToTopButton->setEnabled(false);

	m_scrollToBottomButton = new QPushButton(this);
	m_scrollToBottomButton->setObjectName("pushButton_scrollToBottom");
	connect(m_scrollToBottomButton, &QPushButton::clicked, this,
		[this]
		{
			auto bar = getEditor()->verticalScrollBar();
			bar->setValue(bar->maximum());
		});
	m_scrollToBottomButton->setEnabled(false);

	auto bar = getEditor()->verticalScrollBar();

	connect(bar, &QScrollBar::rangeChanged, this,
		[this](int min, int max)
		{
			auto value = getEditor()->verticalScrollBar()->value();
			m_scrollToTopButton->setEnabled(value != min);
			m_scrollToBottomButton->setEnabled(value != max);
		});
	connect(bar, &QScrollBar::valueChanged, this,
		[this](int value)
		{
			auto min = getEditor()->verticalScrollBar()->minimum();
			auto max = getEditor()->verticalScrollBar()->maximum();
			m_scrollToTopButton->setEnabled(value != min);
			m_scrollToBottomButton->setEnabled(value != max);
		});
}

void NctiQtPythonScriptEdit::updateScrollToPosition()
{
	auto bottomRight = getEditor()->geometry().bottomRight();

	// 在右下角的基础上，减去按键高宽和内边距，可得按键左上角点
	auto scrollToBottomButtonPoint = bottomRight - QPoint(m_scrollToBottomButton->width(), m_scrollToBottomButton->height()) - QPoint(7, 12);
	m_scrollToBottomButton->move(scrollToBottomButtonPoint);

	// 在上一个按键左上角的基础上，减去下一个按键的高度和间距，可得下一个按键左上角点
	auto scrollToTopButtonPoint = scrollToBottomButtonPoint - QPoint(0, m_scrollToTopButton->height()) - QPoint(0, 2);
	m_scrollToTopButton->move(scrollToTopButtonPoint);
}

void NctiQtPythonScriptEdit::updateSceneTitle(NctiQtScriptScene* scene)
{
	QString path = scene->getPath();
	bool isChanged = scene->isContentChanged();
	if (path.isEmpty()) {
		setWindowTitle(QStringLiteral("脚本编辑 - %1%2").arg(QStringLiteral("Untitled")).arg(isChanged ? "*" : ""));
	}
	else {
		setWindowTitle(QStringLiteral("脚本编辑 - %1%2").arg(path).arg(isChanged ? "*" : ""));
	}
}

void NctiQtPythonScriptEdit::appendScene(NctiQtScriptScene* scene)
{
	m_sceneList.append(scene);
    Q_EMIT sigSceneAppend(scene);

	this->layout()->addWidget(scene->getEditor());
	updateSceneTitle(scene);

	connect(scene, &NctiQtScriptScene::sigPathChanged, [this,scene]
		{
			updateSceneTitle(scene);
		});
	connect(scene, &NctiQtScriptScene::sigContentChanged, [this, scene]
		{
			updateSceneTitle(scene);
		});
}

QIcon NctiQtPythonScriptEdit::getButtonIcon(Button button) const
{
	return m_button2Icon.value(button);
}

QAbstractButton* NctiQtPythonScriptEdit::getButton(Button button) const
{
	switch (button)
	{
	case NCTI::NctiQtPythonScriptEdit::ButtonRun:
		return m_runButton;
	case NCTI::NctiQtPythonScriptEdit::ButtonRestore:
		return m_loadToolButton;
	case NCTI::NctiQtPythonScriptEdit::ButtonClear:
		return m_cleanButton;
	case NCTI::NctiQtPythonScriptEdit::ButtonOpen:
		return m_openButton;
	case NCTI::NctiQtPythonScriptEdit::ButtonSave:
		return m_saveButton;
	case NCTI::NctiQtPythonScriptEdit::ButtonClose:
		return m_closeButton;
	case NCTI::NctiQtPythonScriptEdit::ButtonStartDebug:
		return m_debugStartButton;
	case NCTI::NctiQtPythonScriptEdit::ButtonStopDebug:
		return m_debugStopButton;
	case NCTI::NctiQtPythonScriptEdit::ButtonBreakpoint:
		return m_breakpointButton;
    case NCTI::NctiQtPythonScriptEdit::ButtonCustom:
        return m_customToolButton;
	default:
		return nullptr;
	}
}

QAction* NctiQtPythonScriptEdit::getAction(Button button) const
{
	switch (button)
	{
	case NCTI::NctiQtPythonScriptEdit::ButtonBreakpoint_Clear:
		return m_breakpointRemoveAction;
	case NCTI::NctiQtPythonScriptEdit::ButtonBreakpoint_Next:
		return m_breakpointNextAction;
	case NCTI::NctiQtPythonScriptEdit::ButtonBreakpoint_Single:
		return m_breakpointSingleAction;
	case NCTI::NctiQtPythonScriptEdit::ButtonBreakpoint_Disable:
		return m_breakpointDisableAction;
	case NCTI::NctiQtPythonScriptEdit::ButtonBreakpoint_Enable:
		return m_breakpointEnableAction;
	default:
		return nullptr;
	}
}

void NctiQtPythonScriptEdit::setButtonEnable(Button button, bool enable)
{
	switch (button)
	{
	case NCTI::NctiQtPythonScriptEdit::ButtonRun:
	case NCTI::NctiQtPythonScriptEdit::ButtonRestore:
	case NCTI::NctiQtPythonScriptEdit::ButtonClear:
	case NCTI::NctiQtPythonScriptEdit::ButtonOpen:
	case NCTI::NctiQtPythonScriptEdit::ButtonSave:
	case NCTI::NctiQtPythonScriptEdit::ButtonClose:
	case NCTI::NctiQtPythonScriptEdit::ButtonStartDebug:
	case NCTI::NctiQtPythonScriptEdit::ButtonStopDebug:
	case NCTI::NctiQtPythonScriptEdit::ButtonBreakpoint:
		getButton(button)->setEnabled(enable);
		break;
	case NCTI::NctiQtPythonScriptEdit::ButtonBreakpoint_Clear:
	case NCTI::NctiQtPythonScriptEdit::ButtonBreakpoint_Next:
	case NCTI::NctiQtPythonScriptEdit::ButtonBreakpoint_Single:
	case NCTI::NctiQtPythonScriptEdit::ButtonBreakpoint_Disable:
	case NCTI::NctiQtPythonScriptEdit::ButtonBreakpoint_Enable:
		getAction(button)->setEnabled(enable);
		break;
	default:
		break;
	}
}