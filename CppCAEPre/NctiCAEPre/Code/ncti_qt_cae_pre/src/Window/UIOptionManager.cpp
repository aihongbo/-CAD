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

#include "UIOptionManager.h"

#include "UserInteractionManager.h"
#include "UIOptionDialog.h"
#include "AddCustomActionDialog.h"
#include "ConfigCustomActionDialog.h"

#include "NctiQtRightSideView.h"
#include "NctiQtPythonScriptEdit.h"
#include "NctiQtScriptExecutor.h"

#include "SARibbonBar.h"
#include "SARibbonPage.h"
#include "SARibbonPanel.h"
#include "SARibbonToolButton.h"

#include <QMenu>
#include <QLayout>
#include <QFileInfo>
#include <QCryptographicHash>

#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
#include <QStringConverter>
#endif

namespace NCTI {

struct UIElem 
{
    int index;
    enum { ACTION, GROUP, ACTION_GROUP } type;
    union {
        const UIAction* action;
        const UIGroup* group;
        const UIActionGroup* actionGroup;
    } data;

    UIElem(int idx, const UIAction* act) : index(idx), type(ACTION) {
        data.action = act;
    }

    UIElem(int idx, const UIGroup* grp) : index(idx), type(GROUP) {
        data.group = grp;
    }

    UIElem(int idx, const UIActionGroup* actGrp) : index(idx), type(ACTION_GROUP) {
        data.actionGroup = actGrp;
    }

    bool operator<(const UIElem& other) const {
        return index < other.index;
    }
};

static std::string toString(const QString& qstr)
{
    QByteArray ba = qstr.toUtf8();
    return ba.toStdString();
}

UIOptionManager::UIOptionManager(MainWindow* mainWindow)
    : MainWindowModule(mainWindow)
{
    mRibbonbar = m_mainWindow->ribbonBar();
}

void UIOptionManager::initialize()
{
    connect(m_mainWindow->Signals(), &MainWindowSignals::openCustomSetting, this, &UIOptionManager::onCustomSetting);
    connect(m_mainWindow->Signals(), &MainWindowSignals::openUIOption, this, &UIOptionManager::onUIOption);
}

void UIOptionManager::CreateRibbonPanels()
{
    if (CreatePanelsFromUIOption()) {
        mUIReloadTimer = new QTimer(this);
        mUIReloadTimer->setSingleShot(true);
        connect(mUIReloadTimer, &QTimer::timeout, this, &UIOptionManager::reloadUIOption);

        // 监视UI配置文件的变化
        const QStringList uiFiles = UIOption::GetInst().GetUIOptionFiles();
        for (const QString& file : uiFiles) {
            mFileHashCache[file] = getFileHash(file); // 计算初始哈希
        }
        mUIWatcher.addPaths(uiFiles);
        QObject::connect(&mUIWatcher, &QFileSystemWatcher::fileChanged, this, &UIOptionManager::onUIFileChanged);
    }
}

QHash<QString, QRadioButton*> UIOptionManager::getGridRadioButtons()
{
    return mGridSelectRadioButtons;
}

QHash<QString, QCheckBox*> UIOptionManager::getSelCheckBoxs()
{
    return mSelectModeCheckBoxs;
}

QHash<QString, QCheckBox*> UIOptionManager::getVisualCheckBoxs()
{
    return mVisualModeCheckBoxs;
}

QString UIOptionManager::getWindowTitle()
{
    return UIOption::GetInst().GetTitle();
}

QString UIOptionManager::getWindowIcon()
{
    return UIOption::GetInst().GetLogo();
}

void UIOptionManager::onUIOption()
{
    UIOptionDialog dlg(m_mainWindow);
    dlg.exec();
}

QString UIOptionManager::getFileHash(const QString& filePath)
{
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        return QString();
    }
    return QString(QCryptographicHash::hash(file.readAll(), QCryptographicHash::Md5).toHex());
}

void UIOptionManager::onUIFileChanged(const QString& filePath)
{
    if (!mUIWatcher.files().contains(filePath)) {
        mUIWatcher.addPath(filePath);
    }

    const QString currentHash = getFileHash(filePath);
    if (currentHash == mFileHashCache.value(filePath)) {
        return;
    }
    mFileHashCache[filePath] = currentHash;
    mUIReloadTimer->start(200);
}

SARibbonPanel* UIOptionManager::CreateNewPanel(SARibbonPage* page, const QString& text)
{
    if (!page) {
        return nullptr;
    }

    SARibbonPanel* panel = page->addPanel(text);
    panel->setToolButtonIconSize(QSize(26, 26));
    panel->setExpanding(false);
    panel->layout()->setSpacing(12); //设置panel中按钮间距
    panel->layout()->setContentsMargins(12, 4, 12, 8);
    return panel;
}

bool UIOptionManager::CreatePanelsFromUIOption()
{
    if (!UIOption::GetInst().LoadUIOption()) {
        return false;
    }

    for (const auto& tab : UIOption::GetInst().GetUIRibbon().tabs) {
        CreateUIPage(tab);
    }

    // 加载自定义命令按钮
    loadCustomActions();

    return true;
}

void UIOptionManager::CreateUIPage(const UITabDetail& tabDetail)
{
    if (!mRibbonbar || !tabDetail.show) {
        return;
    }

    QString tabName = QString::fromUtf8(tabDetail.name.c_str());
    mPageMap[tabDetail.object_name] = mRibbonbar->addPage(tabName);

    UIPage uiPage = UIOption::GetInst().LoadUIPage(tabDetail.object_name);
    if (!uiPage.panels.empty()) {
        std::sort(uiPage.panels.begin(), uiPage.panels.end(), [](const UIPanel& a, const UIPanel& b) {
            return a.index < b.index;
        });

        for (const auto& uiPanel : uiPage.panels) {
            CreateUIPanel(getPage(uiPage.object_name), uiPanel);
        }
    }
}

void UIOptionManager::CreateUIPanel(SARibbonPage* page, const UIPanel& uiPanel)
{
    auto panel = CreateNewPanel(page, QString::fromUtf8(uiPanel.object_name.c_str()));
    
    std::vector<UIElem> uiElements;
    for (const auto& action : uiPanel.actions) {
        uiElements.emplace_back(action.index, &action);
    }
    for (const auto& group : uiPanel.groups) {
        uiElements.emplace_back(group.index, &group);
    }
    for (const auto& actionGroup : uiPanel.action_groups) {
        uiElements.emplace_back(actionGroup.index, &actionGroup);
    }

    std::sort(uiElements.begin(), uiElements.end());
    
    // 按照排序后的顺序创建UI元素
    for (const auto& elem : uiElements) {
        switch (elem.type) {
        case UIElem::ACTION:
            CreateUIPanelAction(panel, elem.data.action->index, uiPanel.actions);
            break;
        case UIElem::GROUP:
            CreateUIPanelGroup(panel, elem.data.group->index, uiPanel.groups);
            break;
        case UIElem::ACTION_GROUP:
            CreateUIActionGroup(panel, *elem.data.actionGroup);
            break;
        }
    }
}

void UIOptionManager::reloadUIOption()
{
    if (!mRibbonbar) {
        return;
    }

    for (auto& [key, page] : mPageMap) {
        if (page) {
            mRibbonbar->removePage(page);
            delete page;
            page = nullptr;
        }
    }
    mPageMap.clear();

    CreatePanelsFromUIOption();

    // 监视UI配置文件的变化
    mUIWatcher.addPaths(UIOption::GetInst().GetUIOptionFiles());
}

void UIOptionManager::SetActionObjName(QAction* action, const std::string& obj_name)
{
    if (obj_name.empty()) {
        return;
    }
    action->setObjectName(QString::fromUtf8(obj_name.c_str()));
}

void UIOptionManager::SetActionShortCut(QAction* action, const std::string& short_cut)
{
    if (!short_cut.empty()) {
        return;
    }
    QKeySequence shortCut = QKeySequence::fromString(QString::fromStdString(short_cut));
    action->setShortcut(shortCut);
}

QAction* UIOptionManager::CreateUIAction(const UIAction& uiAction)
{
    auto const connectToSlot = [this](QAction* action, auto&& slot) {
        connect(action, &QAction::triggered, std::forward<decltype(slot)>(slot));
    };

    QIcon icon         = QIcon(QString::fromUtf8(uiAction.icon_path.c_str()));
    QString text       = QString::fromUtf8(uiAction.name.c_str());
    QString objectName = QString::fromUtf8(uiAction.object_name.c_str());
    QAction* action    = new QAction(icon, text, m_mainWindow);
    action->setObjectName(objectName);
    if (!uiAction.slot_name.empty()) {
        ConnectWidgetToSlot(action, &QAction::triggered, uiAction.slot_name);
    }
    else {
        if (!uiAction.pystring.empty()) {
            QString content = QString::fromUtf8(uiAction.pystring.c_str());
            connectToSlot(action, [this, content] { 
                NctiQtScriptExecutor* executor = m_mainWindow->getUserInteractionMgr()->getScriptExecutor();
                if (executor) { executor->excuteCommand(content); }
            });
        }
    }
    SetActionShortCut(action, uiAction.short_cut);
    return action;
}

QAction* UIOptionManager::CreateUIMenuAction(const UIAction& uiAction)
{
    QIcon icon          = QIcon(QString::fromUtf8(uiAction.icon_path.c_str()));
    QString text        = QString::fromUtf8(uiAction.name.c_str());
    QAction* menuAction = new QAction(icon, text, m_mainWindow);
    SetActionObjName(menuAction, uiAction.object_name);

    QAction* action    = nullptr;
    SARibbonMenu* menu = new SARibbonMenu(m_mainWindow);
    for (auto& item : uiAction.vChild) {
        QIcon icon   = QIcon(QString::fromUtf8(item.icon_path.c_str()));
        QString text = QString::fromUtf8(item.name.c_str());
        action = menu->addAction(icon, text);
        SetActionObjName(action, item.object_name);
        SetActionShortCut(action, item.short_cut);
        ConnectWidgetToSlot(action, &QAction::triggered, item.slot_name);
    }
    menuAction->setMenu(menu);
    return menuAction;
}

void UIOptionManager::CreateUIGroup(SARibbonPanel* panel, const UIGroup& group)
{
    for (const auto& item : group.vChild) {
        QIcon icon      = QIcon(QString::fromUtf8(item.icon_path.c_str()));
        QString text    = QString::fromUtf8(item.name.c_str());
        QAction* action = new QAction(icon, text, m_mainWindow);
        SetActionObjName(action, item.object_name);
        ConnectWidgetToSlot(action, &QAction::triggered, item.slot_name, item.object_name);
        panel->addMediumAction(action);
    }
}

QToolButton* UIOptionManager::createGroupTitleWidget(QWidget* parent, const UIActionGroup& uiActionGroup)
{
    QString iconUrl = QString::fromUtf8(uiActionGroup.icon_path.c_str());
    QIcon icon;
    icon.addPixmap(QPixmap(iconUrl), QIcon::Mode::Normal);
    icon.addPixmap(QPixmap(iconUrl), QIcon::Mode::Disabled);

    QToolButton* title = new QToolButton(parent);
    title->setObjectName(QString::fromStdString(uiActionGroup.object_name));
    title->setIcon(icon);
    title->setIconSize(QSize(28, 28));
    title->setText(QString::fromUtf8(uiActionGroup.name.c_str()));
    title->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    title->setEnabled(false);
    return title;
}

void UIOptionManager::CreateUIActionGroup(SARibbonPanel* panel, const UIActionGroup& uiActionGroup)
{
    QFrame* frame = new QFrame(panel);
    frame->setObjectName(QString::fromStdString(uiActionGroup.frame_object_name));

    QHBoxLayout* frameLayout = new QHBoxLayout(frame);
    frameLayout->setContentsMargins(2, 2, 2, 2);
    frameLayout->setSpacing(10);
    QToolButton* title = createGroupTitleWidget(frame, uiActionGroup);
    frameLayout->addWidget(title);

    QGridLayout* gridLayout = new QGridLayout();
    gridLayout->setVerticalSpacing(7);
    gridLayout->setHorizontalSpacing(4);
    gridLayout->setContentsMargins(QMargins{2, 5, 2, 2});
    frameLayout->addLayout(gridLayout);

    mGridSelectRadioButtons.clear();
    for (const auto& item : uiActionGroup.vChild) {
        if (uiActionGroup.group_type == "check_box") {
            QCheckBox* checkBox = createActionGroupItem<QCheckBox>(frame, item);
            QString objName     = QString::fromStdString(item.object_name);
            ConnectWidgetToSlot(checkBox, &QCheckBox::toggled, item.slot_name, item.object_name);
            gridLayout->addWidget(checkBox, item.row, item.column);

            if (uiActionGroup.object_name == "title_selectMode") {
                mSelectModeCheckBoxs.insert(objName, checkBox);
            }
            else if (uiActionGroup.object_name == "title_visualMode") {
                mVisualModeCheckBoxs.insert(objName, checkBox);
            }
        }
        else if (uiActionGroup.group_type == "radio_button") {
            QRadioButton* radioBtn = createActionGroupItem<QRadioButton>(frame, item);
            QString objName        = QString::fromStdString(item.object_name);
            if (objName == "grid_geo")
                radioBtn->setChecked(true);
            ConnectWidgetToSlot(radioBtn, &QRadioButton::toggled, item.slot_name, item.object_name);
            gridLayout->addWidget(radioBtn, item.row, item.column);
            mGridSelectRadioButtons.insert(objName, radioBtn);
        }
    }
    panel->addLargeWidget(frame);
}

bool UIOptionManager::CreateUIPanelAction(SARibbonPanel* p, int index, const std::vector<UIAction>& vUIAction)
{
    if (vUIAction.empty()) {
        return false;
    }

    for (const auto& item : vUIAction) {
        if (item.index == index) {
            if (item.vChild.empty()) {
                addActionToPanel(p, CreateUIAction(item), 0);
            }
            else {
                addActionToPanel(p, CreateUIMenuAction(item), 70);
            }
            return true;
        }
    }
    return false;
}

bool UIOptionManager::CreateUIPanelGroup(SARibbonPanel* p, int index, const std::vector<UIGroup>& vUIGroup)
{
    if (vUIGroup.empty()) {
        return false;
    }

    for (const auto& item : vUIGroup) {
        if (item.index == index) {
            CreateUIGroup(p, item);
            return true;
        }
    }
    return false;
}

bool UIOptionManager::CreateUIPanelActionGroup(SARibbonPanel* p,
                                               int index,
                                               const std::vector<UIActionGroup>& vUIActionGroup)
{
    if (vUIActionGroup.empty()) {
        return false;
    }

    for (const auto& item : vUIActionGroup) {
        if (item.index == index) {
            CreateUIActionGroup(p, item);
            return true;
        }
    }
    return false;
}

QAction* UIOptionManager::getCustomActionButton(const QString& actionName)
{
    SARibbonPanel* customPanel = getCustomPanel();
    if (!customPanel) {
        return nullptr;
    }

    auto btnList = customPanel->ribbonToolButtons();
    if (btnList.isEmpty()) {
        return nullptr;
    }

    for (auto& btn : btnList) {
        QAction* action = btn->defaultAction();
        qDebug() << "actionName: " << action->data().toString();
        if (action && action->data().toString() == actionName) {
            return action;
        }
    }
    return nullptr;
}

void UIOptionManager::removeCustomActionButton(const QString& actionName)
{
    SARibbonPanel* customPanel = getCustomPanel();
    if (!customPanel) {
        return;
    }

    auto btnList = customPanel->ribbonToolButtons();
    if (btnList.isEmpty()) {
        return;
    }

    for (auto& btn : btnList) {
        QAction* action = btn->defaultAction();
        if (action && action->objectName() == actionName) {
            action->deleteLater();
            break;
        }
    }
}

void UIOptionManager::deleteCustomScript(const QString& actionName)
{
    if (actionName.isEmpty()) {
        return;
    }

    if (CustomActionManager::getInst().deleteRecord(toString(actionName))) {
        // 移除自定义的命令按钮
        removeCustomActionButton(actionName);

        auto dataList              = CustomActionManager::getInst().allCustomActions();
        SARibbonPanel* customPanel = getCustomPanel();
        if (customPanel) {
            customPanel->setVisible(!dataList.empty());
        }
    }
}

void UIOptionManager::onAddCustomAction()
{
    auto addCustomDlg = std::make_unique<AddCustomActionDialog>(m_mainWindow, QStringLiteral("添加自定义脚本命令"));
    addCustomDlg->setFixedSize(320, 283);
    addCustomDlg->exec();
    if (0 == addCustomDlg->GetStatus()) {
        return;
    }

    // 保存当前脚本到本地
    QString actionName = addCustomDlg->actionName();
    QString pyFile     = CustomActionManager::getInst().getPyFilePath(actionName);
    if (!savePyScriptToLocal(pyFile)) {
        return;
    }

    int index = CustomActionManager::getInst().getIndexForNewAction();

    // 命令图标
    QString iconPath = addCustomDlg->iconPath();
    std::vector<char> thumbnail;
    if (!CustomActionManager::isCustomIcon(iconPath)) {
        thumbnail = CustomActionManager::getThumbnail(toString(iconPath));
    }

    CustomAction customAction;
    customAction.action_index = index;
    customAction.action_name = toString(actionName);
    customAction.icon_path = toString(iconPath);
    customAction.thumbnail = thumbnail;

    // 保存到数据库
    if (CustomActionManager::getInst().insertRecord(customAction)) {
        // 添加到自定义命令面板
        SARibbonPanel* customPanel = getCustomPanel();
        if (customPanel) {
            addActionToCustomPanel(customPanel, customAction);
            customPanel->setVisible(true);
        }
    }

    if (mRibbonbar) {
        std::string key = UIOption::GetTabName(UI_CUSTOM);
        int index       = mRibbonbar->pageIndex(mPageMap[key]);
        mRibbonbar->setCurrentIndex(index);
    }
}

void UIOptionManager::onEditCustomAction(const QString& originActionName, const QString& originIconPath)
{
    if (mCustomActionCfgDlg) {
        mCustomActionCfgDlg->close();
    }

    auto modifyCustomDlg
        = std::make_unique<AddCustomActionDialog>(m_mainWindow, QStringLiteral("修改自定义脚本命令"), originActionName);
    modifyCustomDlg->setFixedSize(320, 283);
    modifyCustomDlg->UpdateIcon(originActionName, originIconPath);
    modifyCustomDlg->exec();
    if (0 == modifyCustomDlg->GetStatus()) {
        return;
    }

    std::string origin_action_name = toString(originActionName);

    QString actionName      = modifyCustomDlg->actionName();
    std::string action_name = toString(actionName);

    QString iconPath      = modifyCustomDlg->iconPath();
    std::string icon_path = toString(iconPath);

    CustomAction originCAData = CustomActionManager::getInst().findByName(origin_action_name);
    if (originCAData.action_name.empty()) {
        return;
    }

    if (action_name != origin_action_name) {
        // 更新名称
        CustomActionManager::getInst().updatePyScriptPath(origin_action_name, action_name);
        originCAData.action_name = action_name;
    }

    if (!icon_path.empty() && icon_path != originCAData.icon_path) {
        // 更新图标
        if (!CustomActionManager::isCustomIcon(icon_path)) {
            originCAData.thumbnail = CustomActionManager::getThumbnail(icon_path);
        }
        else {
            originCAData.thumbnail.clear();
        }
        originCAData.icon_path = icon_path;
    }

    // 更新数据库
    if (!CustomActionManager::getInst().updateRecord(originCAData)) {
        return;
    }

    QString newActionName = CustomActionManager::toQString(originCAData.action_name);
    QString newIconPath   = CustomActionManager::toQString(originCAData.icon_path);
    QIcon newIcon         = QIcon(CustomActionManager::getThumbnail(originCAData.thumbnail));

    // 更新Panel中的按钮
    QAction* actionButton = getCustomActionButton(actionName);
    if (actionButton) {
        actionButton->setText(newActionName);
        actionButton->setObjectName(newActionName);
        actionButton->setData(QVariant(newActionName));
        if (!originCAData.thumbnail.empty()) {
            actionButton->setIcon(newIcon);
        }
        else {
            actionButton->setIcon(QIcon(newIconPath));
        }
    }

    // 更新配置窗口
    if (mCustomActionCfgDlg) {
        mCustomActionCfgDlg->updateActionNameAndIcon(actionName, newActionName, newIconPath, newIcon);
    }
}

void UIOptionManager::onCustomSetting()
{
    auto configDlg = std::make_unique<ConfigCustomActionDialog>(m_mainWindow, QStringLiteral("编辑自定义脚本命令"));
    mCustomActionCfgDlg = configDlg.get();

    connect(mCustomActionCfgDlg,
            &ConfigCustomActionDialog::sigEditCustomAction,
            this,
            &UIOptionManager::onEditCustomAction);

    connect(mCustomActionCfgDlg, &ConfigCustomActionDialog::sigEditPyScript, this, [this](const QString& pyPath) {
        if (!pyPath.isEmpty() && QFileInfo(pyPath).exists()) {
            NctiQtPythonScriptEdit* editorView = m_mainWindow->getUserInteractionMgr()->getEditorView();
            if (editorView) { editorView->open(pyPath); }
        }
    });

    connect(mCustomActionCfgDlg, &ConfigCustomActionDialog::sigRemovePyScript, this, [this](const QString& name) {
        deleteCustomScript(name);
    });

    mCustomActionCfgDlg->exec();
}

QString UIOptionManager::getCustomActionName(QAction* action)
{
    QString actionName;
    QVariant var = action->data();
    if (var.isValid() && var.type() == QVariant::String) {
        actionName = var.toString();
    }
    return actionName;
}

void UIOptionManager::onRunCustomScript()
{
    QAction* action    = qobject_cast<QAction*>(sender());
    QString actionName = getCustomActionName(action);
    if (actionName.isEmpty()) {
        return;
    }

    QString pyPath = CustomActionManager::getInst().getPyFilePath(actionName);
    if (!QFileInfo(pyPath).exists()) {
        return;
    }

    NctiQtScriptExecutor* executor = m_mainWindow->getUserInteractionMgr()->getScriptExecutor();
    if (!executor) {
        return;
    }
    
    QFile file(pyPath);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
        in.setEncoding(QStringConverter::Utf8);
#else
        in.setCodec("UTF-8");
#endif
        QString content = in.readAll();
        file.close();
        if (!content.isEmpty()) {
            executor->excuteCommand(content, true);
        }
    }
}

void UIOptionManager::onEditCustomScript()
{
    QAction* action    = qobject_cast<QAction*>(sender());
    QString actionName = getCustomActionName(action);
    if (actionName.isEmpty()) {
        return;
    }
    QString pyPath = CustomActionManager::getInst().getPyFilePath(actionName);
    if (QFileInfo(pyPath).exists()) {
        NctiQtPythonScriptEdit* editorView = m_mainWindow->getUserInteractionMgr()->getEditorView();
        if (editorView) { editorView->open(pyPath); }
    }
}

void UIOptionManager::onDeleteCustomScript()
{
    QAction* action = qobject_cast<QAction*>(sender());
    deleteCustomScript(getCustomActionName(action));
}

void UIOptionManager::loadCustomActions()
{
    SARibbonPanel* customPanel = getCustomPanel();
    if (!customPanel) {
        return;
    }

    std::vector<CustomAction> dataList = CustomActionManager::getInst().allCustomActions();
    customPanel->setVisible(!dataList.empty());

    for (auto& data : dataList) {
        addActionToCustomPanel(customPanel, data);
    }
}

QAction* UIOptionManager::CreateMenuAction(const ActionInfo& info, const QList<ActionInfo>& items)
{
    auto iconInfo   = getIconInfo(info.pageName, info.iconName);
    QAction* action = new QAction(QIcon(iconInfo.first), info.text, m_mainWindow);
    action->setMenu(CreateMenu(items));
    return action;
}

SARibbonMenu* UIOptionManager::CreateMenu(const QList<ActionInfo>& items, const QVariant& var)
{
    QAction* act       = nullptr;
    SARibbonMenu* menu = new SARibbonMenu(m_mainWindow);
    for (auto& item : items) {
        auto iconInfo = getIconInfo(item.pageName, item.iconName);
        act           = menu->addAction(QIcon(iconInfo.first), QString(item.text));
        act->setObjectName(iconInfo.second);
        if (var.isValid()) {
            act->setData(var);
        }
        if (item.slot) {
            connect(act, SIGNAL(triggered()), this, item.slot);
        }
        if (!item.shortCut.isEmpty()) {
            act->setShortcut(item.shortCut);
        }
    }
    return menu;
}

QAction* UIOptionManager::CreateViewAction(const QString& text, const QString& iconName, const char* slot)
{
    const QString url = QStringLiteral(":/General/%1.svg").arg(iconName);
    QAction* a        = new QAction(QIcon(url), text, m_mainWindow);
    a->setObjectName(iconName);
    if (slot) {
        connect(a, SIGNAL(triggered()), this, slot);
    }
    return a;
}

void UIOptionManager::AddViewActionsToPanel(SARibbonPanel* panel)
{
    if (!panel) {
        return;
    }

    QList<std::pair<QString, QString>> viewList = {
        {"xplus", QStringLiteral("")},  //X正向
        {"xminus", QStringLiteral("")}, //X负向
        {"yplus", QStringLiteral("")},  //Y正向
        {"yminus", QStringLiteral("")}, //Y负向
        {"zplus", QStringLiteral("")},  //Z正向
        {"zminus", QStringLiteral("")}  //Z负向
    };

    for (const auto& item : viewList) {
        panel->addMediumAction(CreateViewAction(item.second, item.first, nullptr));
    }
}

std::pair<QString, QString> UIOptionManager::getIconInfo(const QString& pageName, const QString& iconName)
{
    QString iconUrl = QStringLiteral(":/%1/%2.svg").arg(pageName).arg(iconName);
    if ("AI" == pageName) {
        iconUrl = QStringLiteral(":/%1/%2.png").arg(pageName).arg(iconName);
    }
    QString objName = QStringLiteral("%1_%2").arg(pageName).arg(iconName);
    return std::pair<QString, QString>(iconUrl, objName);
}

void UIOptionManager::addActionToCustomPanel(SARibbonPanel* customPanel, const CustomAction& customAction)
{
    QIcon actionIcon   = CustomActionManager::getInst().getActionIcon(customAction);
    QString actionName = QString::fromUtf8(customAction.action_name.c_str());

    QAction* action = new QAction(actionIcon, actionName, m_mainWindow);
    action->setObjectName(actionName);
    action->setData(QVariant(actionName));
    connect(action, &QAction::triggered, this, &UIOptionManager::onRunCustomScript);
    customPanel->addLargeAction(action);
}

void UIOptionManager::addActionToPanel(SARibbonPanel* panel, QAction* action, int minWidth)
{
    if (panel) {
        panel->addLargeAction(action);
        if (minWidth > 0) {
            auto button = panel->actionToRibbonToolButton(action);
            button->setMinimumWidth(minWidth);
        }
    }
}

QAction* UIOptionManager::addActionToPanel(SARibbonPanel* panel, const ActionInfo& item)
{
    return addActionToPanel(panel, item.pageName, item.text, item.iconName, item.slot, item.shortCut);
}

QAction* UIOptionManager::addActionToPanel(SARibbonPanel* panel,
                                           const QString& pageName,
                                           const QString& text,
                                           const QString& iconName,
                                           const char* slotName,
                                           const QKeySequence& shortCut)
{
    auto iconInfo = getIconInfo(pageName, iconName);
    QAction* a    = new QAction(QIcon(iconInfo.first), text, m_mainWindow);
    a->setObjectName(iconInfo.second);
    if (panel) {
        panel->addAction(a, Large);
    }
    if (slotName) {
        connect(a, SIGNAL(triggered()), this, slotName);
    }
    if (!shortCut.isEmpty()) {
        a->setShortcut(shortCut);
    }
    return a;
}

QList<QAction*> UIOptionManager::addActionToPanel(SARibbonPanel* panel, const QList<ActionInfo>& item)
{
    QList<QAction*> actions;
    for (auto&& it : item) {
        actions << addActionToPanel(panel, it);
    }
    return actions;
}

bool UIOptionManager::savePyScriptToLocal(const QString& filePath)
{
    NctiQtPythonScriptEdit* editorView = m_mainWindow->getUserInteractionMgr()->getEditorView();
    if (editorView) { editorView->save(filePath); }

    //check the file exists
    if (QFileInfo(filePath).exists()) {
        return true;
    }
    return false;
}

SARibbonPage* UIOptionManager::getPage(const std::string& objectName)
{
    auto it = mPageMap.find(objectName);
    if (it != mPageMap.end()) {
        return it->second;
    }
    return nullptr;
}

SARibbonPanel* UIOptionManager::getCustomPanel()
{
    if (mCustomPanel) {
        return mCustomPanel;
    }
    std::string key    = UIOption::GetTabName(UI_CUSTOM);
    SARibbonPage* page = getPage(key);
    if (page) {
        return page->panelByObjectName("customAddPanel");
    }
    return nullptr;
}
} // namespace NCTI