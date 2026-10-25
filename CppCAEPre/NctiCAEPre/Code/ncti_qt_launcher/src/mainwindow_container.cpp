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

#include "mainwindow_container.h"
#include "SARibbonBar.h"
#include "SARibbonTitleTabBar.h"
#include "SARibbonSystemButtonBar.h"
#include "SARibbonButtonGroupWidget.h"

#include "WindowMask.h"
#include "IPCData.h"

#ifdef Q_OS_WIN
#include <windows.h>
#endif

#include <QWindow>
#include <QProcess>
#include <QDateTime>
#include <QMessageBox>
#include <QFileDialog>
#include <QSettings>
#include <QStandardPaths>
#include <QCloseEvent>
#include <QApplication>

#if QT_VERSION_MAJOR >= 6 && QT_VERSION_MINOR >= 5
#include <QOverload>
#endif

#include "NewDocDialog.h"
#include "SaveDocDialog.h"
#include "FileFilterTreeDelegate.h"

#include "NctiDocument.h"

#include <unordered_set>

namespace NCTI {
    static std::string toString(const QString& qstr) {
        QByteArray ba = qstr.toUtf8();
        return ba.toStdString();
    }

    static QString readStyleSheet(const QString& filePath) {
        QFile file(filePath);
        if (!file.exists()) {
            qWarning() << "QSS file does not exist:" << filePath;
            return QString();
        }

        if (file.open(QFile::ReadOnly | QFile::Text)) {
            QString styleSheet = QString::fromUtf8(file.readAll());
            file.close();
            return styleSheet;
        }
        else {
            qWarning() << "Failed to open QSS file:" << filePath;
            return QString();
        }
    }

    static void applyStyleSheets()
    {
        qApp->setStyleSheet(readStyleSheet(QStringLiteral(":/style/launcher.qss")));
    }

    static void initFileDB()
    {
        // 获取%APPDATA%对应的目录（Roaming目录）
        QString appDataPath = QStandardPaths::writableLocation(
            QStandardPaths::AppDataLocation
        );

        QString dataDir = QDir(appDataPath).filePath("data");
        if (!QDir().mkpath(dataDir)) {
            qWarning() << "Cannot create data directory:" << dataDir;
            return;
        }

        QString dbPath = dataDir + "/recentFiles.db";
        if (!FileDatabase::getInst()->initDB(toString(dbPath).c_str())) {
            qWarning() << "init sqlite failed";
        }
    }  

    static int64_t getUpdatedTime()
    {
        QDateTime currentDateTime = QDateTime::currentDateTimeUtc();
        int64_t secsSinceEpoch = currentDateTime.toSecsSinceEpoch();
        return secsSinceEpoch;
    }

    // 获取路径
    static QString getLastDir(const QString& key, QStandardPaths::StandardLocation loc = QStandardPaths::DocumentsLocation)
    {
        QSettings settings;
        QString dir = settings.value(key).toString();
        if (dir.isEmpty() || !QDir(dir).exists()) {
            dir = QStandardPaths::writableLocation(loc);
        }
        return dir;
    }

    // 保存路径
    static void setLastDir(const QString& key, const QString& path)
    {
        QSettings settings;
        settings.setValue(key, path);
    }

    MainwindowContainer::MainwindowContainer(QWidget* parent)
        : SARibbonMainWindow(parent)
    {
        initFileDB();

        setupUi();
        
        connectSignals();

        // 初始化IPC管理器
        mIpcManager = std::make_unique<IPCServerManager>(this);

        // 连接IPC信号槽
        connect(mIpcManager.get(), &IPCServerManager::sigSocketDisconnected, this, &MainwindowContainer::onSocketDisconnected);
        connect(mIpcManager.get(), &IPCServerManager::sigWindowIdMessage, this, &MainwindowContainer::onMsgTypeWindowId);
        connect(mIpcManager.get(), &IPCServerManager::sigTaskDetailMessage, this, &MainwindowContainer::onMsgTaskDetail);
        connect(mIpcManager.get(), &IPCServerManager::sigExitSaveMessage, this, &MainwindowContainer::onMsgTypeExitSave);
        connect(mIpcManager.get(), &IPCServerManager::sigDocDirtyMessage, this, &MainwindowContainer::onMsgTypeDocDirty);
        connect(mIpcManager.get(), &IPCServerManager::sigDataUpdateMessage, this, &MainwindowContainer::onMsgTypeDataUpdate);
    }

    MainwindowContainer::~MainwindowContainer()
    {
        mTaskDetail.reset();
        mWinMask.reset();

        if (mIpcManager) {
            mIpcManager.reset();
        }
    }

    void MainwindowContainer::onSearchRecentFiles()
    {
        QString text = mSearchLineEdit->text().trimmed();
        if (text == mSearchText) {
            return;
        }
        mSearchText = text;
        std::vector<FileDetail> fileList;
        if (mSearchText.isEmpty()) {
            auto fileList = FileDetailGallery::getFileList(mRecentFileType);
        }
        else {
            auto allFileList = FileDetailGallery::getFileList(mRecentFileType);
            auto filteredFileList = FileDetailGallery::getFileList(text);

            std::unordered_set<int> idSet;
            for (const auto& file : filteredFileList) {
                idSet.insert(file.id);
            }
            for (const auto& file : allFileList) {
                if (idSet.find(file.id) != idSet.end()) {
                    fileList.push_back(file);
                }
            }
        }
        mFileDetailGallery->loadData(fileList);
        mFileDetailGallery->update();
    }
    
    void MainwindowContainer::onUpdateRecentFiles()
    {
        //QElapsedTimer cost;
        //cost.start();
        auto fileList = FileDetailGallery::getFileList(mRecentFileType);
        mFileDetailGallery->loadData(fileList);
        mFileDetailGallery->update();
        //qDebug() << "UpdateRecentFiles cost:" << cost.elapsed() << " ms";
    }


    void MainwindowContainer::closeEvent(QCloseEvent* event)
    {
        if (mIpcManager->getEmbeddedWindowCount() > 0) {
            QString text = QStringLiteral("是否关闭所有打开的文档？");
            auto dlg = std::make_unique<SaveDocDialog>(this, text, ShowType::NoDoc);
            dlg->setFixedSize(342, 212);
            dlg->exec();
            auto saveStatus = dlg->GetSaveStatus();
            if (saveStatus == SaveStatus::Cancel) {
                event->ignore();
                return;
            }

            mIpcManager->sendExitMessageToAllClient();
            
            // 等待所有套接字断开连接
            QCoreApplication::processEvents(QEventLoop::AllEvents, 1000);
        }

        QMainWindow::closeEvent(event);
    }

    void MainwindowContainer::resizeEvent(QResizeEvent* event)
    {
        auto titleTabBar = ribbonBar()->titleTabBar();
        if (titleTabBar) {
            titleTabBar->triggerResizeEvent();
        }

        QMainWindow::resizeEvent(event); 
    }

    void MainwindowContainer::showEvent(QShowEvent* event)
    {
        QMainWindow::showEvent(event);

        if (mStackedWidget) {
            mIpcManager->refreshDocView(mStackedWidget->currentWidget());
        }
    }

    void MainwindowContainer::setupUi()
    {
        mWinMask = std::make_unique<WindowMask>(this);

        setupRibbonUi();

        setMinimumSize(QSize(1460, 800));
    }

    void MainwindowContainer::setupRibbonUi()
    {
        SARibbonBar* ribbonbar = ribbonBar();
        if (!ribbonbar) {
            qDebug() << "ribbonbar is null";
            return;
        }

        // 使用多文档样式
        ribbonbar->setMultiDocumentStyle(true);
        ribbonbar->setApplicationButton(nullptr);
        ribbonbar->setQuickAccessBarVisible(false);
        ribbonbar->setTabBarVisible(false);
        ribbonbar->setTabBarHeight(0);
        ribbonbar->setRibbonPageHeight(0);

        // 设置窗口图标和标题
        setupIniIconTitle();

        // 设置主题
        QTimer::singleShot(0, this, [this]() { this->setRibbonTheme(SARibbonTheme::RibbonThemeLight); });

        // 标题栏Tab
        connect(ribbonbar->titleTabBar(), &SARibbonTitleTabBar::tabCloseRequested, this, &MainwindowContainer::onTitleTabClose);

        //增加标签按钮
        initTitleTabAddWidget();

        // 创建中央容器
        mStackedWidget = new QStackedWidget(this);
        mStackedWidget->setObjectName("stackedWidget");
        QPalette palette = mStackedWidget->palette();
        palette.setColor(QPalette::Window, Qt::darkGray);
        mStackedWidget->setPalette(palette);
        mStackedWidget->setAutoFillBackground(true);
        setCentralWidget(mStackedWidget);

        createBlankPage();
        createRecentFilePage();
        mStackedWidget->setCurrentWidget(FileDetailGallery::getFileList(RecentFileType::ALL_FILE).empty() 
            ? mBlankPage
            : mRecentFilePage);
        addMainPageTab();

        // 加载样式表
        applyStyleSheets();
    }

    void MainwindowContainer::setupIniIconTitle()
    {
        QString iniPath = QDir(QCoreApplication::applicationDirPath()).filePath("display.ini");
        if (!QFileInfo::exists(iniPath)) {
            setWindowIcon(QIcon(":/app/app.png"));
            setWindowTitle(QStringLiteral("GMDE"));
            return;
        }

        QSettings settings(iniPath, QSettings::IniFormat);
#if QT_VERSION_MAJOR < 6
        settings.setIniCodec("UTF-8");
#endif
        settings.beginGroup("App");
        QString iconPath = settings.value("icon", ":/app/app.png").toString();
        QString title = settings.value("title", "GMDE").toString();
        settings.endGroup();

        QFileInfo fileInfo(iconPath);
        if (!fileInfo.isAbsolute()) {
            QString fullPath = QDir(QCoreApplication::applicationDirPath()).filePath(iconPath);
            iconPath = QDir::cleanPath(fullPath);
        }

        if (QFile::exists(iconPath)) {
            setWindowIcon(QIcon(iconPath));
        }
        else {
            setWindowIcon(QIcon(":/app/app.png"));
        }

        setWindowTitle(title);
    }

    void MainwindowContainer::retranslateRibbonUi()
    {
    }

    void MainwindowContainer::connectSignals()
    {
        SARibbonBar* ribbon = ribbonBar();
        connect(ribbon, &SARibbonBar::currentTitleTabChanged, this, &MainwindowContainer::onTitleTabChanged);
        connect(ribbon, &SARibbonBar::actionTriggered, this, &MainwindowContainer::onActionTriggered);
    }

    void MainwindowContainer::initTitleTabAddWidget()
    {
        SARibbonBar* ribbonbar = ribbonBar();
        if (!ribbonbar) {
            return;
        }
        auto addWidget = ribbonbar->titleAddWidget();
        addWidget->setFixedWidth(42);
        addWidget->setFixedHeight(26);
        addWidget->setContentsMargins(1, 1, 1, 1);
        addWidget->setIconSize(QSize(16, 16));

        QAction* addBtn = new QAction(QIcon(":/titlebar/add.svg"), QStringLiteral("新建"), this);
        addWidget->addAction(addBtn);
        addWidget->addSeparator();

        QAction* newAssembly = new QAction(QIcon(":/file/new_assembly.svg"), QStringLiteral("新建装配"), this);
        connect(newAssembly, &QAction::triggered, this, &MainwindowContainer::onNewAssembly);
        QAction* newPart = new QAction(QIcon(":/file/new_part.svg"), QStringLiteral("新建部件"), this);
        connect(newPart, &QAction::triggered, this, &MainwindowContainer::onNewPart);

        SARibbonMenu* menu = new SARibbonMenu(this);
        menu->addAction(newAssembly);
        menu->addAction(newPart);
        menu->menuAction()->setIcon(QIcon(":/titlebar/down_arrow.svg"));
        addWidget->addMenu(menu);
    }

    void MainwindowContainer::onTitleTabChanged(int index)
    {
        int64_t windowId = getTabWindowId(index);
        //qDebug() << "tab changed to window: " << windowId;
        if (windowId == MAIN_PAGE_ID) {
            bool isEmpty = FileDetailGallery::getFileList(RecentFileType::ALL_FILE).empty();
            mStackedWidget->setCurrentWidget(isEmpty ? mBlankPage : mRecentFilePage);
            if (!isEmpty) {
                onUpdateRecentFiles();
            }
            return;
        }

        auto embedded = mIpcManager->getEmbeddedWindow(windowId);
        if (embedded.widget) {
            mStackedWidget->setCurrentWidget(embedded.widget);
            embedded.widget->adjustSize();
            mIpcManager->sendDocRefreshMessage(windowId);
        }
    }
    
    void MainwindowContainer::onActionTriggered(QAction* action)
    {
        qDebug() << "action triggered" << action->text();
    }

    void MainwindowContainer::createBlankPage()
    {
        mBlankPage = new QWidget(mStackedWidget);
        mBlankPage->setObjectName("blankPage");
        
        QVBoxLayout* pageLayout = new QVBoxLayout(mBlankPage);
        pageLayout->setContentsMargins(0, 0, 0, 0);
        pageLayout->setAlignment(Qt::AlignCenter);

        QWidget* topSpacer = new QWidget(mBlankPage);
        topSpacer->setFixedHeight(190);
        pageLayout->addWidget(topSpacer);

        auto newPartBtn = new QPushButton(mBlankPage);
        newPartBtn->setObjectName("newPartBtn");
        newPartBtn->setFixedSize(374, 257);
        pageLayout->addWidget(newPartBtn, 0, Qt::AlignCenter);

        QWidget* middleSpacer = new QWidget(mBlankPage);
        middleSpacer->setFixedHeight(60);
        pageLayout->addWidget(middleSpacer);

        auto newAssemblyBtn = new QPushButton(mBlankPage);
        newAssemblyBtn->setObjectName("newAssemblyBtn");
        newAssemblyBtn->setFixedSize(104, 36);
        pageLayout->addWidget(newAssemblyBtn, 0, Qt::AlignHCenter);

        QWidget* bottomSpacer = new QWidget(mBlankPage);
        bottomSpacer->setFixedHeight(32);
        pageLayout->addWidget(bottomSpacer);

        auto openFileBtn = new QPushButton(mBlankPage);
        openFileBtn->setObjectName("openFileBtn");
        openFileBtn->setFixedSize(104, 36);
        pageLayout->addWidget(openFileBtn, 0, Qt::AlignHCenter);
        pageLayout->addStretch();

        connect(newPartBtn, &QAbstractButton::clicked, this, &MainwindowContainer::onNewPart);
        connect(newAssemblyBtn, &QAbstractButton::clicked, this, &MainwindowContainer::onNewAssembly);
        connect(openFileBtn, &QAbstractButton::clicked, this, &MainwindowContainer::onOpenFile);

        mStackedWidget->addWidget(mBlankPage);
    }

    void MainwindowContainer::onNewPart()
    {
        createSubProcess("new_part");
    }

    void MainwindowContainer::onNewAssembly()
    {
        createSubProcess("new_assembly");
    }

    void MainwindowContainer::onOpenFile()
    {
        const QString LAST_DIRECTORY_KEY = "MainwindowContainer/Open/LastDirectory";
        QString openNctiDir = getLastDir(LAST_DIRECTORY_KEY);

        QString filePath = QFileDialog::getOpenFileName(this
            , tr("Open File")
            , openNctiDir
            , tr("NCTI File (*.ncti)"));

        if (filePath.isEmpty()) { return; }

        QString currentDir = QFileInfo(filePath).absoluteDir().path();
        if (currentDir != openNctiDir) {
            setLastDir(LAST_DIRECTORY_KEY, currentDir);
        }
        onOpenNctiFile(filePath);
    }

    void MainwindowContainer::onOpenNctiFile(const QString& filePath)
    {
        if (!checkFileExist(filePath)) {
            return;
        }

        TaskDetail detail;
        detail.type = "open_file";
        detail.file_path = toString(filePath);
        createSubProcess(detail);
    }

    bool MainwindowContainer::checkFileExist(const QString& filePath)
    {
        QFileInfo fileInfo(filePath);
        if (fileInfo.exists()) {
            return true;
        }
        QString tips = QStringLiteral("此文件在本地未找到，是否删除该记录？");
        removeRecord(filePath, tips);

        return false;
    }

    void MainwindowContainer::onRemoveRecord(const QString& filePath)
    {
        QString tips = QStringLiteral("您是否确认要删除这条记录？");
        removeRecord(filePath, tips);
    }

    void MainwindowContainer::removeRecord(const QString& targetPath, const QString& tips)
    {
        auto dlg = std::make_unique<SaveDocDialog>(this, tips, ShowType::NoDoc);
        dlg->setFixedSize(342, 212);
        dlg->exec();
        auto saveStatus = dlg->GetSaveStatus();
        if (saveStatus == SaveStatus::Cancel) {
            return;
        }

        FileDetailGallery::removeFile(targetPath);
        auto fileList = FileDetailGallery::getFileList(mRecentFileType);
        mFileDetailGallery->loadData(fileList);
        mFileDetailGallery->update();
    }

    void MainwindowContainer::createRecentFilePage()
    {
        mRecentFilePage = new QWidget(mStackedWidget);
        mRecentFilePage->setObjectName("recentFilePage");
        QHBoxLayout* pageLayout = new QHBoxLayout(mRecentFilePage);
        pageLayout->setContentsMargins(0, 0, 0, 0);
        pageLayout->setSpacing(0);
        pageLayout->addWidget(createLeftSideWidget());
        pageLayout->addWidget(createRightSideWidget());
        mStackedWidget->addWidget(mRecentFilePage);
    }

    QWidget* MainwindowContainer::createLeftSideWidget()
    {
        //左侧的导航栏
        QWidget* leftSideWidget = new QWidget(mRecentFilePage);
        leftSideWidget->setFixedWidth(300);
        QVBoxLayout* leftSideLayout = new QVBoxLayout(leftSideWidget);
        leftSideLayout->setContentsMargins(0, 0, 0, 0);
        
        QTreeWidget* treeWidget = new QTreeWidget(leftSideWidget);
        treeWidget->setObjectName("recentFileTreeWidget");
        treeWidget->setItemDelegate(new FileFilterTreeDelegate(treeWidget));
        
        initTreeWidget(treeWidget);
        
        connect(treeWidget, &QTreeWidget::currentItemChanged, this, &MainwindowContainer::onItemChanged);
        
        addTreeWidgetData(treeWidget);
        
        leftSideLayout->addWidget(treeWidget);
        return leftSideWidget;
    }

    QWidget* MainwindowContainer::createRightSideWidget()
    {
        //右侧搜索栏
        QWidget* rightSideWidget = new QWidget(mRecentFilePage);
        rightSideWidget->setObjectName("rightSideWidget");
        QVBoxLayout* rightSideLayout = new QVBoxLayout(rightSideWidget);
        rightSideLayout->setContentsMargins(0, 0, 0, 0);
        rightSideLayout->setSpacing(0);

        QWidget* searchWidget = new QWidget(rightSideWidget);
        searchWidget->setObjectName("searchWidget");
        searchWidget->setFixedHeight(68);
        QHBoxLayout* searchLayout = new QHBoxLayout(searchWidget);

        mSearchLineEdit = new QLineEdit(searchWidget);
        mSearchLineEdit->setObjectName("searchLineEdit");
        mSearchLineEdit->setPlaceholderText("请输入项目名称");
        QAction* action = new QAction(mSearchLineEdit);
        action->setIcon(QIcon(":recentpage/search.svg"));
        mSearchLineEdit->addAction(action, QLineEdit::LeadingPosition);
        connect(mSearchLineEdit, &QLineEdit::returnPressed, this, &MainwindowContainer::onSearchRecentFiles);

        QPushButton* openFileBtn = new QPushButton(searchWidget);
        openFileBtn->setObjectName("recentPageOpenFileBtn");
        openFileBtn->setFixedSize(108, 36);
        openFileBtn->setText("+ 打开文件");
        connect(openFileBtn, &QPushButton::clicked, this, &MainwindowContainer::onOpenFile);

        searchLayout->addWidget(mSearchLineEdit);
        searchLayout->addStretch();
        searchLayout->addWidget(openFileBtn);
        rightSideLayout->addWidget(searchWidget);

        //右侧文件列表        
        mFileDetailGallery = new FileDetailGallery(rightSideWidget);
        mFileDetailGallery->setObjectName("fileDetailGallery");
        mFileDetailGallery->loadData(FileDetailGallery::getFileList(mRecentFileType));

        connect(mFileDetailGallery, &FileDetailGallery::sigDetailWidgetClicked, this, &MainwindowContainer::onNewPart);
        connect(mFileDetailGallery, &FileDetailGallery::sigNewAssembly, this, &MainwindowContainer::onNewAssembly);
        connect(mFileDetailGallery, &FileDetailGallery::sigNewPart, this, &MainwindowContainer::onNewPart);
        connect(mFileDetailGallery, &FileDetailGallery::sigOpenFile, this, &MainwindowContainer::onOpenNctiFile);
        connect(mFileDetailGallery, &FileDetailGallery::sigDeleteRecord, this, &MainwindowContainer::onRemoveRecord);
        rightSideLayout->addWidget(mFileDetailGallery);
        return rightSideWidget;
    }

    void MainwindowContainer::initTreeWidget(QTreeWidget* treeWidget)
    {
        treeWidget->setHeaderHidden(true);
        treeWidget->setFrameShape(QFrame::NoFrame);
        treeWidget->setRootIsDecorated(false);
        treeWidget->setIndentation(0);
        treeWidget->setUniformRowHeights(true);
        treeWidget->setExpandsOnDoubleClick(false);
        treeWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
        treeWidget->setSelectionMode(QAbstractItemView::SingleSelection);
        treeWidget->setColumnCount(1);
    }

    void MainwindowContainer::addTreeWidgetData(QTreeWidget* treeWidget)
    {
        QTreeWidgetItem* recentFileItem = new QTreeWidgetItem(treeWidget);
        recentFileItem->setText(0, QStringLiteral("最近打开"));
        recentFileItem->setIcon(0, QIcon(":/recentpage/tree_recent_file.svg"));
        recentFileItem->setData(0, Qt::UserRole, static_cast<int>(RecentFileType::RECENT_FILE));

        auto allFileItem = new QTreeWidgetItem(treeWidget);
        allFileItem->setText(0, QStringLiteral("全部文件"));
        allFileItem->setIcon(0, QIcon(":/recentpage/tree_all_file.svg"));
        allFileItem->setData(0, Qt::UserRole, static_cast<int>(RecentFileType::ALL_FILE));

        auto assemblyItem = new QTreeWidgetItem(allFileItem);
        assemblyItem->setText(0, "装配文件");
        assemblyItem->setData(0, Qt::UserRole, static_cast<int>(RecentFileType::ASSEMBLY_FILE));

        auto partsItem = new QTreeWidgetItem(allFileItem);
        partsItem->setText(0, "部件文件");
        partsItem->setData(0, Qt::UserRole, static_cast<int>(RecentFileType::PARTS_FILE));

        auto favoriteItem = new QTreeWidgetItem(treeWidget);
        favoriteItem->setText(0, QStringLiteral("收藏文件"));
        favoriteItem->setIcon(0, QIcon(":/recentpage/tree_favorite_file.svg"));
        favoriteItem->setData(0, Qt::UserRole, static_cast<int>(RecentFileType::FAVORITE_FILE));

        treeWidget->expandAll();
        treeWidget->setCurrentItem(allFileItem);
    }

    // 设置标签数据
    void MainwindowContainer::setTitleTabData(QTabBar* tabbar, int index, bool isLoading, int64_t windowId)
    {
        QMap<QString, QVariant> dataMap;
        dataMap["isLoading"] = isLoading;
        dataMap["windowId"] = static_cast<long long>(windowId);
        tabbar->setTabData(index, QVariant::fromValue(dataMap));
    }

    void MainwindowContainer::addMainPageTab()
    {
        auto titleTabBar = ribbonBar()->titleTabBar();
        if (!titleTabBar) { return; }
        titleTabBar->setVisible(true);

        int index = titleTabBar->addTab(QStringLiteral("主页"));
        titleTabBar->setTabButton(index, QTabBar::RightSide, nullptr);
        titleTabBar->setCurrentIndex(index);
        setTitleTabData(titleTabBar, index, true, MAIN_PAGE_ID);
        this->adjustSize();
    }

    void MainwindowContainer::addTitleTab(const QString& nctiFilePath)
    {
        auto titleTabBar = ribbonBar()->titleTabBar();
        if (!titleTabBar) { return; }

        int availableWidth = titleTabBar->maximumWidth();
        int tabCount = titleTabBar->count();
        int minWidth = 40;
        if (availableWidth < minWidth * (tabCount + 1)) {
            QMessageBox::warning(this, "警告", "没有足够的空间添加新的标签页。");
            return;
        }

        QString text("未命名");
        if (!nctiFilePath.isEmpty()) {
            QFileInfo fileInfo(nctiFilePath);
            text = fileInfo.completeBaseName();
        }
    
        int index = titleTabBar->addTab(text);
        setTitleTabData(titleTabBar, index, false, NEW_PAGE_ID);
        titleTabBar->triggerResizeEvent();
    }

    void MainwindowContainer::updateTitleTabData(const MessageData& fromData)
    {
        auto titleTabBar = ribbonBar()->titleTabBar();
        if (!titleTabBar) { return; }

        QString fileName = QString::fromUtf8(fromData.file_name.c_str());
        if(fromData.window_id != MAIN_PAGE_ID && fromData.window_id != NEW_PAGE_ID) {
            for (int index = 0; index < titleTabBar->count(); ++index) {
                if (getTabWindowId(index) == fromData.window_id) {
                    titleTabBar->setTabText(index, fileName);
                    return;
                }
            }
        }

        QString text = fileName.isEmpty() ? getNewTabText() : fileName;
        
        for (int index = 0; index < titleTabBar->count(); ++index) {
            if (getTabWindowId(index) == NEW_PAGE_ID) {
                setTitleTabData(titleTabBar, index, true, fromData.window_id);
                titleTabBar->setTabText(index, text);
                titleTabBar->setCurrentIndex(index);
                return;
            }
        }
    }

    QString MainwindowContainer::getNewTabText()
    {
        auto titleTabBar = ribbonBar()->titleTabBar();
        if (!titleTabBar) { return "未命名-1"; }

        int maxNum = 0;
        QRegularExpression regex("^未命名-(\\d+)$");
        
        for (int index = 0; index < titleTabBar->count(); ++index) {
            QString text = titleTabBar->tabText(index);
            QRegularExpressionMatch match = regex.match(text);
            if (match.hasMatch()) {
                int num = match.captured(1).toInt();
                if (num > maxNum) {
                    maxNum = num;
                }
            }
        }
        
        int newNum = maxNum + 1;
        return QString("未命名-%1").arg(newNum);
    }

    int64_t MainwindowContainer::getTabWindowId(int index)
    {
        auto titleTabBar = ribbonBar()->titleTabBar();
        if (!titleTabBar || titleTabBar->count() <= 0) { return 0; }

        auto dataMap = titleTabBar->getTabData(index);
        if (!dataMap.isEmpty()) {
            return dataMap["windowId"].toLongLong();
        }
        if (index != 1) {
            qWarning() << "Failed to retrieve windowId of Index " << index;
        }
        return 0;
    }

    void MainwindowContainer::setTabText(const QString& text)
    {
        auto titleTabBar = ribbonBar()->titleTabBar();
        if (!titleTabBar) { return; }
        titleTabBar->setCurrentTabText(text);
    }

    QString MainwindowContainer::getTabText(int index) const
    {
        auto titleTabBar = ribbonBar()->titleTabBar();
        if (!titleTabBar) { return ""; }
        return titleTabBar->tabText(index);
    }

    void MainwindowContainer::removeTitleTab(int64_t window_id)
    {
        auto titleTabBar = ribbonBar()->titleTabBar();
        if (!titleTabBar) {
            return;
        }

        for (int index = 0; index < titleTabBar->count(); ++index) {
            if (getTabWindowId(index) == window_id) {
                titleTabBar->removeTab(index);
                break;
            }
        }
    }

    bool MainwindowContainer::isTabSelected(int index)
    {
        auto titleTabBar = ribbonBar()->titleTabBar();
        if (titleTabBar) {
            return (titleTabBar->currentIndex() == index);
        }
        return false;
    }

    void MainwindowContainer::createSubProcess(const QString& actionType)
    {
        NewDocDialog dlg(this);
        mWinMask->addWidget(&dlg);
        auto ret = dlg.exec();
        if (ret != QDialog::Accepted) {
            return;
        }
        auto&& [geo, cons, mesh] = dlg.GetInfo();
        TaskDetail detail;
        detail.type = toString(actionType);
        detail.geometry = toString(geo);
        detail.constraint = toString(cons);
        detail.mesh = toString(mesh);

        createSubProcess(detail);
    }

    void MainwindowContainer::createSubProcess(const TaskDetail& detail)
    {
        if (mTaskDetail) {
            qWarning() << "TaskDetail already exists";
            mTaskDetail.reset();
        }

        mTaskDetail = std::make_unique<TaskDetail>(detail);

        QStringList arguments{
            "sub_proc",
            "-s", mIpcManager->getFullServerName(),
            "-f", QString::fromUtf8(detail.file_path.c_str())
        };

        if (mCachedExePath.isEmpty()) {
            QString basePath = QCoreApplication::applicationDirPath();
            QStringList fileNames = { "ncti_qt_cae_pre.exe"};
            auto checkFileExists = [&basePath](const QString& fileName) {
                QString filePath = basePath + QDir::separator() + fileName;
                QFileInfo fileInfo(filePath);
                return fileInfo.exists();
                };

            QString exePath;
            for (const auto& fileName : fileNames) {
                if (checkFileExists(fileName)) {
                    exePath = basePath + QDir::separator() + fileName;
                    break;
                }
            }
            mCachedExePath = exePath;
        }
       
        if (!mCachedExePath.isEmpty()) {
            bool success = QProcess::startDetached(mCachedExePath, arguments);
            if (success) {
                addTitleTab(QString::fromUtf8(detail.file_path.c_str()));
            }
            else {
                qWarning() << "Failed to start subprocess: " << mCachedExePath;
            }
        }
    }

    void MainwindowContainer::onTitleTabClose(int tabIndex)
    {
        if (!isTabSelected(tabIndex)) {
            return;
        }
        auto winId = getTabWindowId(tabIndex);
        if (winId == MAIN_PAGE_ID) {
            return;
        }

        // 发送是否保存的消息
        if (!mIpcManager->sendDocDirtyMessage(winId, getTabText(tabIndex))) {
            // 发送消息失败
            removeTitleTab(winId);

            EmbeddedWndData data = mIpcManager->removeEmbeddedWindow(winId);
            removeStackedWidget(data.widget);
        }
    }

    void MainwindowContainer::onItemChanged(QTreeWidgetItem* currentItem, QTreeWidgetItem* previousItem) 
    {
        if (!mFileDetailGallery || !currentItem) { return; }
        
        mRecentFileType = static_cast<RecentFileType>(currentItem->data(0, Qt::UserRole).toInt());
        mSearchText = "";
        auto fileList = FileDetailGallery::getFileList(mRecentFileType);
        mFileDetailGallery->loadData(fileList);
        mFileDetailGallery->update();
    }

    void MainwindowContainer::removeStackedWidget(QWidget* widget)
    {
        if (!widget) {
            return;
        }
        int currentIndex = mStackedWidget->currentIndex();
        int indexToRemove = mStackedWidget->indexOf(widget);

        if (indexToRemove == -1) return;

        if (mStackedWidget->count() > 2) {
            if (indexToRemove == currentIndex) {
                // If removing the current widget, switch to the next or previous widget
                if (indexToRemove + 1 < mStackedWidget->count() + 2) {
                    // There is a next widget, set it as current
                    mStackedWidget->setCurrentIndex(indexToRemove + 1);
                }
                else {
                    // There is no next widget, set the previous one as current
                    mStackedWidget->setCurrentIndex(indexToRemove - 1);
                }
            }
        }
        else {
            mStackedWidget->setCurrentWidget(FileDetailGallery::getFileList(RecentFileType::ALL_FILE).empty()
                ? mBlankPage
                : mRecentFilePage);
        }

        mStackedWidget->removeWidget(widget);
        widget->deleteLater();
    }

    void MainwindowContainer::onSocketDisconnected(QLocalSocket* socket)
    {
        if (!socket) { return; }

        if (mIpcManager) {
            auto embedded = mIpcManager->removeEmbeddedWindow(socket);
            if (embedded.windowId > 0) {
                removeTitleTab(embedded.windowId);
                removeStackedWidget(embedded.widget);
            }
        }
        onUpdateRecentFiles();
    }

    void MainwindowContainer::onMsgTypeWindowId(QLocalSocket* socket, const MessageData& fromData)
    {
        //收到客户端窗口ID的消息
        QWindow* childWindow = QWindow::fromWinId(static_cast<quintptr>(fromData.window_id));
        if (!childWindow) {
            qWarning() << "Failed to create QWindow from ID:" << fromData.window_id;
            return;
        }

        QWidget* widget = QWidget::createWindowContainer(childWindow, mStackedWidget);
        if (!widget) {
            qWarning() << "Failed to create widget container for window ID:" << fromData.window_id;
            return;
        }
        widget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        int newIndex = mStackedWidget->addWidget(widget);
        mStackedWidget->setCurrentIndex(newIndex);

        //保存嵌入的窗口和对应的socket到IPC管理器
        mIpcManager->addEmbeddedWindow(fromData.window_id, widget, socket);

        updateTitleTabData(fromData);

        //保存文件详情到数据库
        saveFileDetailToDB(fromData);
    }

    void MainwindowContainer::onMsgTaskDetail(const MessageData& msgData)
    {
        //发送任务消息
        if (mTaskDetail) {
            mIpcManager->sendRunTaskMessage(msgData.window_id, *mTaskDetail);
            mTaskDetail.reset();
        }
    }

    void MainwindowContainer::onMsgTypeExitSave(const MessageData& fromData)
    {
        //收到客户端保存退出的消息回复
        saveFileDetailToDB(fromData);
    }

    void MainwindowContainer::onMsgTypeDocDirty(const MessageData& fromData)
    {
        if (fromData.traversed) {
            //为ture时，直接通知子进程退出程序
            mIpcManager->sendExitMessage(fromData.window_id);
            return;
        }

        if (!fromData.file_path.empty()) {
            if(fromData.dirty) {
                QString title = QStringLiteral("文档有修改，是否保存到 %1？")
                    .arg(QString::fromUtf8(fromData.file_path.c_str()));
                auto saveDlg = std::make_unique<SaveDocDialog>(this, title);
                saveDlg->setFixedSize(388, 212);
                saveDlg->SetSavePath(QString::fromUtf8(fromData.file_path.c_str()));
                saveDlg->exec();
                auto saveStatus = saveDlg->GetSaveStatus();
                if (saveStatus == SaveStatus::Save) {
                    //保存并退出
                    mIpcManager->sendExitSaveMessage(fromData.window_id, saveDlg->GetSavePath());
                    return;
                }
                else if (saveStatus == SaveStatus::Cancel) {
                    //取消操作
                    return;
                }
            }
            
            // 不保存退出
            mIpcManager->sendExitMessage(fromData.window_id);
            saveFileDetailToDB(fromData);
            return;
        }

        //文档未保存
        QString title = QStringLiteral("是否保存文档到%1").arg(QString::fromUtf8(fromData.file_name.c_str()));
        auto saveDlg = std::make_unique<SaveDocDialog>(this, title);
        saveDlg->setFixedSize(388, 212);
        saveDlg->exec();
        auto saveStatus = saveDlg->GetSaveStatus();
        if (saveStatus == SaveStatus::Cancel) {
            return;
        }
        else if (saveStatus == SaveStatus::NoSave) {
            mIpcManager->sendExitMessage(fromData.window_id);
        }
        else if (saveStatus == SaveStatus::Save) {
            mIpcManager->sendExitSaveMessage(fromData.window_id, saveDlg->GetSavePath());
        }
    }

    void MainwindowContainer::onMsgTypeDataUpdate(const MessageData& fromData)
    {
        updateTitleTabData(fromData);
        saveFileDetailToDB(fromData);
    }

    void MainwindowContainer::saveFileDetailToDB(const MessageData& msgData)
    {
        if (msgData.file_path.empty()) { return; }

        QString filePath = QString::fromUtf8(msgData.file_path.c_str());
        QFile file(filePath);
        if (!file.exists()) { return; }

        FileDetail detail;
        detail.file_name = msgData.file_name;
        detail.file_path = msgData.file_path;
        detail.ncti_type = msgData.project_type;
        detail.update_time = static_cast<std::uint64_t>(getUpdatedTime());
        detail.thumbnail = FileDetailGallery::getNctiThumbnailBlob(QString(msgData.file_path.c_str()));
        FileDetailGallery::setFileList(detail);
    }

    bool MainwindowContainer::readNctiFileImage(const QString& nctiFilePath, const QString& thumbnailPath)
    {
        QByteArray dst = thumbnailPath.toUtf8();
        QByteArray nctiFile = nctiFilePath.toUtf8();

        NctiDocument* pDocument = NctiDocumentManager::instance()->CreateDocument();
        if (pDocument->ReadFileImage(nctiFile.data(), dst.data()) == NCTI_SUCCEEDED) {
            NctiDocumentManager::instance()->RemoveDocument(pDocument->GetID());
            return true;
        }
        return false;
    }
}

