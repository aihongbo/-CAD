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

#include "UserInteractionManager.h"
#include "NctiQTPubFun.h"
#include "NctiQtCommandConsole.h"
#include "NctiMeasuringTool.h"

#include "DockTitleBar.h"
#include "NctiQtRightSideView.h"
#include "NctiQtPythonScriptEdit.h"
#include "UIOptionManager.h"

#include <QCoreApplication>
#include <QDockWidget>
#include <QHBoxLayout>
#include <QDir>
#include <QTimer>
#include <QStandardPaths>

namespace NCTI {

UserInteractionManager::UserInteractionManager(MainWindow* mainWindow)
    : MainWindowModule(mainWindow)
{
}

void UserInteractionManager::initialize()
{
    addCommandConsole();

    connect(m_mainWindow->Signals(), &MainWindowSignals::console, this, &UserInteractionManager::onCommandConsole);
    connect(m_mainWindow->Signals(), &MainWindowSignals::scriptEdit, this, &UserInteractionManager::onScriptEdit);
    
}

void UserInteractionManager::initCommandConsole()
{
    if (m_commandConsole) {
        return;
    }

    m_commandConsole = new NctiQtCommandConsole(m_mainWindow);
    m_commandConsole->document()->setDocumentMargin(10);

    if (getScriptExecutor()) {
        m_commandConsole->setExecutor(getScriptExecutor());
    }

    m_commandConsole->setCodePrefix(">> ", QColor(180, 180, 180));

    m_commandConsoleDockWidget = new QDockWidget(QStringLiteral("控制台"), m_mainWindow);

    QFrame* frame = new QFrame(m_commandConsoleDockWidget);
    {
        QHBoxLayout* layout = new QHBoxLayout(frame);
        layout->setContentsMargins(0, 0, 0, 0);
        frame->setObjectName("frame_commandConsole");
        frame->setLayout(layout);
        layout->addWidget(m_commandConsole);
    }
    m_commandConsoleDockWidget->setWidget(frame);
    m_commandConsoleDockWidget->setAllowedAreas(Qt::BottomDockWidgetArea);
    m_commandConsoleDockWidget->setFeatures(QDockWidget::NoDockWidgetFeatures);

    DockTitleBar* titleBar = new DockTitleBar(m_commandConsoleDockWidget);
    titleBar->setTitle(QStringLiteral("控制台"));
    titleBar->setObjectName("dockTitleBar_commandConsole");
    connect(titleBar, &DockTitleBar::signalClose, m_commandConsoleDockWidget, &QDockWidget::close);
    connect(titleBar, &DockTitleBar::signalClose, this, [this] { m_consoleState = false; });

    m_commandConsoleDockWidget->setTitleBarWidget(titleBar);
    m_commandConsoleDockWidget->hide();

    auto cbPosition = [this](const NctiPosition& pt) { m_commandConsole->GetPositionFunc(pt); };
    auto cbLength   = [this](const Ncti_Double& dbl) { m_commandConsole->GetLengthFunc(dbl); };
    auto cbMidPos   = [this](const NctiPosition& pt) { m_commandConsole->GetMidPositionFunc(pt); };
    auto cbCenter   = [this](const NctiPosition& pt) { m_commandConsole->GetCenterFunc(pt); };
    auto cbRadius   = [this](const Ncti_Double& dbl) { m_commandConsole->GetRadiusFunc(dbl); };
    auto cbVector   = [this](const NctiVector& vec) { m_commandConsole->GetVectorFunc(vec); };
    auto cbAngle    = [this](const Ncti_Double& dbl) { m_commandConsole->GetAngleFunc(dbl); };
    NctiMeasuringTool::instance()->Init(cbPosition, cbLength, cbMidPos, cbCenter, cbRadius, cbVector, cbAngle);
}

void UserInteractionManager::onCommandConsole()
{
    showCommandConsole(!m_consoleState);
}

void UserInteractionManager::showCommandConsole(bool show)
{
    if (!m_commandConsoleDockWidget) {
        return;
    }

    if (show) {
        m_commandConsoleDockWidget->show();
        m_consoleState = true;
    }
    else {
        m_commandConsoleDockWidget->hide();
        m_consoleState = false;
    }
}

void UserInteractionManager::addCommandConsole()
{
    initCommandConsole();
    m_mainWindow->addDockWidget(Qt::BottomDockWidgetArea, m_commandConsoleDockWidget);

    static bool inited = false;
    if (!inited) {
        inited = true;
        m_mainWindow->resizeDocks({m_commandConsoleDockWidget}, {200}, Qt::Vertical);
    }
    
    if (m_consoleState) {
        m_commandConsoleDockWidget->show();
    }
}

void UserInteractionManager::removeCommandConsole()
{
    initCommandConsole();
    m_mainWindow->removeDockWidget(m_commandConsoleDockWidget);
    m_commandConsoleDockWidget->hide();
    m_consoleState = false;
}

bool UserInteractionManager::getConsoleState() const
{
    return m_consoleState;
}

void UserInteractionManager::onScriptEdit()
{
    showRightSide();

    if (m_rightSideView->currentView() != NctiQtRightSideView::ViewEditor) {
        m_rightSideView->changeCurrentView(NctiQtRightSideView::ViewEditor);
    }
    else {
        if (m_scriptEditorShowState) {
            m_rightSideView->hideScriptEditor();
        }
        else {
            m_rightSideView->changeCurrentView(NctiQtRightSideView::ViewEditor);
        }
    }
}

void UserInteractionManager::initRightSide()
{
    if (m_rightSideView) {
        return;
    }

    const std::map<NctiQtPythonScriptEdit::Button, QString> buttonIconMap = {
    {NctiQtPythonScriptEdit::ButtonBreakpoint_Clear, ":/ScriptEditor/breakpoint_remove.svg"},
    {NctiQtPythonScriptEdit::ButtonBreakpoint_Disable, ":/ScriptEditor/breakpoint_disable.svg"},
    {NctiQtPythonScriptEdit::ButtonBreakpoint_Enable, ":/ScriptEditor/breakpoint_enable.svg"},
    {NctiQtPythonScriptEdit::ButtonBreakpoint_Next, ":/ScriptEditor/breakpoint_next.svg"},
    {NctiQtPythonScriptEdit::ButtonBreakpoint_Single, ":/ScriptEditor/breakpoint_single.svg"}
    };

    m_rightSideView = new NctiQtRightSideView(m_mainWindow);
    
    // 设置Editor
    auto scriptEdit = m_rightSideView->editorView();
    for (const auto& [buttonType, iconPath] : buttonIconMap) {
        scriptEdit->configButtonIcon(buttonType, QIcon(iconPath));
    }
    scriptEdit->configScene(false);
    scriptEdit->setup();
    scriptEdit->setHistoryFilePath(getScriptDataPath());

    m_rightSideView->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);

#ifdef NCTI_ENABLE_AIQA_SERVICE
    m_rightSideView->setUrl(QUrl("http://172.16.37.104:17792/AiAssistant"),
        QUrl("http://172.16.37.104:17792/AiCodeStore"));

    QString dirPath = QDir(QCoreApplication::applicationDirPath()).filePath("webdata");
    if (!QFileInfo(dirPath).exists()) {
        QDir().mkpath(dirPath);
    }
    m_rightSideView->setDbPath(QDir(dirPath).filePath("chat.db"));
#endif
    m_rightSideDockWidget = new QDockWidget("", m_mainWindow);
    m_rightSideDockWidget->setWidget(m_rightSideView);
    m_rightSideDockWidget->setAllowedAreas(Qt::RightDockWidgetArea);
    m_rightSideDockWidget->setFeatures(QDockWidget::NoDockWidgetFeatures); // 禁用所有特性

    connect(m_rightSideView->editorView(), &QWidget::windowTitleChanged, this, [this] {
        if (m_rightSideView->currentView() != NctiQtRightSideView::ViewEditor || !m_rightSidePanelVisible) {
            return;
        }
        m_rightSideDockWidget->setWindowTitle(m_rightSideView->editorView()->windowTitle());
        auto bar = qobject_cast<DockTitleBar*>(m_rightSideDockWidget->titleBarWidget());
        bar->setTitle(m_rightSideView->editorView()->windowTitle());
    });

    connect(m_rightSideView, &NctiQtRightSideView::sigSidePanelVisible, this, [this](int id, bool visible) {
        if (visible) {
            if (m_rightSidePanelVisible && m_rightSideDockWidth != m_rightSideDockWidget->width()) {
                m_rightSideDockWidth = m_rightSideDockWidget->width();
            }
            m_rightSidePanelVisible = true;

            QString title;
            if (id == NctiQtRightSideView::ViewEditor) {
                title = m_rightSideView->editorView()->windowTitle();
            }
            else if (id == NctiQtRightSideView::ViewProperty) {
                title = QStringLiteral("属性");
            }
#ifdef NCTI_ENABLE_AIQA_SERVICE
            else if (id == NctiQtRightSideView::ViewChat) {
                title = QStringLiteral("问答");
            }
            else if (id == NctiQtRightSideView::ViewFav) {
                title = QStringLiteral("命令收藏");
                m_rightSideView->updateFavView();
            }
#endif
            m_scriptEditorShowState = (id == NctiQtRightSideView::ViewEditor);
            m_rightSideTitleBar->setTitle(title);
            m_mainWindow->resizeDocks({m_rightSideDockWidget}, {m_rightSideDockWidth}, Qt::Horizontal);
            m_rightSideDockWidget->setMaximumWidth(QWIDGETSIZE_MAX);
        }
        else {
            if (id == NctiQtRightSideView::ViewEditor) {
                m_scriptEditorShowState = false;
            }
            m_rightSidePanelVisible = false;
            m_rightSideDockWidth    = m_rightSideDockWidget->width();
            m_rightSideTitleBar->setTitle(QStringLiteral(""));
            m_mainWindow->resizeDocks({m_rightSideDockWidget}, {40}, Qt::Horizontal);
            QTimer::singleShot(0, this, [this]() { m_rightSideDockWidget->setMaximumWidth(40); });
        }
    });

    m_rightSideView->editorView()->getButton(NctiQtPythonScriptEdit::Button::ButtonCustom)->setVisible(true);
    connect(m_rightSideView->editorView()
        , &NctiQtPythonScriptEdit::addCustomAction
        , m_mainWindow->getUIOptionMgr()
        , &UIOptionManager::onAddCustomAction);

    m_rightSideTitleBar = new DockTitleBar(m_rightSideDockWidget, false, true);
    m_rightSideTitleBar->setTitle(m_rightSideView->editorView()->windowTitle());
    m_rightSideTitleBar->skipEliedTitle("脚本编辑 - ");

    m_rightSideDockWidget->setTitleBarWidget(m_rightSideTitleBar);
    m_rightSideDockWidget->setMinimumWidth(0);
    m_rightSideDockWidget->hide();

    if (m_commandConsole && m_commandConsole->getExecutor() != m_rightSideView->editorView()->getExecutor()) {
        m_commandConsole->setExecutor(m_rightSideView->editorView()->getExecutor());
    }
}

void UserInteractionManager::showRightSide()
{
    initRightSide();

    if (m_rightSideDockWidget) {
        m_mainWindow->addDockWidget(Qt::RightDockWidgetArea, m_rightSideDockWidget);
        m_rightSideDockWidget->show();
        m_mainWindow->resizeDocks({m_rightSideDockWidget}, {300}, Qt::Horizontal);
        m_rightSideDockWidth = m_rightSideDockWidget->width();
    }
}

NctiQtRightSideView* UserInteractionManager::getRightSideView()
{
    return m_rightSideView;
}

NctiObjectProperty* UserInteractionManager::getPropertyView()
{
    return m_rightSideView->propertyView();
}

NctiQtPythonScriptEdit* UserInteractionManager::getEditorView()
{
    if (!m_rightSideView)
        return nullptr;
    return m_rightSideView->editorView();
}

NctiQtScriptExecutor* UserInteractionManager::getScriptExecutor()
{
    if (m_rightSideView) {
        return m_rightSideView->editorView()->getExecutor();
    }
    return nullptr;
}

void UserInteractionManager::SetFocus()
{
    if (m_rightSideView) {
        auto editor = m_rightSideView->editorView()->getEditor();
        if (editor) {
            editor->setFocus();
        }
    }
}

bool UserInteractionManager::getScriptEditorState() const
{
    return m_scriptEditorShowState;
}

QString UserInteractionManager::getScriptDataPath() const
{
    // 获取%APPDATA%对应的目录（Roaming目录）
    QString appDataPath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QString dataDir = QDir(appDataPath).filePath("scriptdata");
    if (!QDir().mkpath(dataDir)) {
        qWarning() << "Cannot create data directory:" << dataDir;
        return QString{};
    }
    return QDir(dataDir).filePath("exechistory.json");
}

} // namespace NCTI