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

#include "mainwindow.h"
#include "SARibbonBar.h"
#include "NctiConfig.h"
#include "NctiQtCaePreApi.h"
#include "IPCManager.h"
#include "NctiWindowEventPubFun.h"
#include "UIOptionManager.h"
#include "SketchEditor.h"
#include "AssemblyOperations.h"
#include "AIFeatureRecognizer.h"
#include "SimulationController.h"
#include "GeometryBuilder.h"
#include "FileOperations.h"
#include "ViewControl.h"
#include "PreferenceSettings.h"
#include "UserInteractionManager.h"
#include "ObjectTreeManager.h"

#include "ncti_base.h"
#include "NctiString.h"

#include "NctiBaseModel.h"
#include "NctiBaseView.h"
#include "NctiDocument.h"
#include "NctiDocViewManager.h"
#include "NctiDisplayDocElement.h"
#include "NctiUserInterfaceManager.h"

#include "NctiDocElementPubFun.h"
#include "NctiOperatingKey.h"
#include "NctiShortcutKeyOperating.h"
#include "NctiPythonTool.h"

#include "NctiWindowPlatform.h"
#include "NctiWindowViewManager.h"

// 回调/接口
#include "NctiCallbackPopupMenu.h"
#include "NctiWinUserTraceInterface.h"

//Widgets
#include "NctiWindowPlatformContainer.h"
#include "NctiDeleteTool.h"
#include "NctiRefreshObject.h"

#ifdef NCTI_QT_CAD_TEST_LOCAL_QSS
#include "QSSLoader.h"
#endif

#ifdef Q_OS_WIN
#include <windows.h>
#include <shellapi.h>
#include <ole2.h>
#endif

// 共用组件
#include "NctiQTPubFun.h"
#include "NctiObjectTree.h"
#include "DockTitleBar.h"

// 编辑器
#include "NctiQtPythonScriptEdit.h"

#include <QDir>
#include <QTimer>
#include <QApplication>
#include <QWindow>
#include <QScreen>
#include <QStatusBar>
#include <QProgressBar>
#include <QCloseEvent>
#include <QHBoxLayout>
#include <QDebug>

// 拖拽事件
#include <QDragEnterEvent>
#include <QDragMoveEvent>
#include <QDragLeaveEvent>
#include <QDropEvent>
#include <QMimeData>

#include <random>

#include "NctiDebug.h"
#include "NctiPluginsManager.h"
#include "NctiInitializeTool.h"
#include "LoadingSpinnerWidget.h"

namespace NCTI {

static void outputErrorAsJson(const ErrorInfo& error)
{
    std::cout << "{"
        << " \"code\": \"" << error.code << "\","
        << " \"message\": \"" << error.message << "\","
        << " \"detail\": \"" << error.detail << "\""
        << "}"
        << std::endl;
}

static int64_t generateRandomTaskId()
{
    static std::mt19937_64 engine(
        std::chrono::system_clock::now().time_since_epoch().count()
    );

    static std::uniform_int_distribution<int64_t> dist(0, std::numeric_limits<int64_t>::max());
    return dist(engine);
}

struct MainWindowPrivate
{
    MainWindow* _this{ nullptr };
    bool mTitlebarVisible{ true };         ///< 标题栏是否可见
    QStatusBar* mStatusBar{ nullptr };     ///< 状态栏
    QLabel* mStatusText{ nullptr };        ///< 选择提示标签
    QProgressBar* mProgressBar{ nullptr }; ///< 进度条
    
    // 功能模块管理器
    UIOptionManager* mUIOptMgr{ nullptr };                  ///< UI选项管理器
    AssemblyOperations* mAssOperations{ nullptr };          ///< 装配操作
    SketchEditor* mSketchEditor{ nullptr };                 ///< 草图编辑器
    AIFeatureRecognizer* mAIFeatureRecognizer{ nullptr };   ///< AI特征识别器
    SimulationController* mSimulationController{ nullptr }; ///< 仿真控制器
    GeometryBuilder* mGeometryBuilder{ nullptr };           ///< 几何构建器
    FileOperations* mFileOperations{ nullptr };             ///< 文件操作
    ViewControl* mViewControl{ nullptr };                   ///< 视图控制
    IPCManager* mIPCManager{ nullptr };                     ///< IPC管理器
    PreferenceSettings* mPreferenceSettings{ nullptr };     ///< 偏好设置
    UserInteractionManager* mUserInteractionMgr{ nullptr }; ///< 用户交互管理器
    ObjectTreeManager* mObjectTreeMgr{ nullptr };           ///< 对象树管理器

    MainWindowPrivate(MainWindow* mainWindow, bool bVisible)
        : _this(mainWindow)
        , mTitlebarVisible(bVisible)
    {
    }

    void OpenNctiFile(const QString& nctiFile)
    {
        if (mFileOperations) {
            mFileOperations->onOpenNcti(nctiFile);
        }
    }
    void OpenPyFile(const QString& pyFile)
    {
        if (mUserInteractionMgr && mUserInteractionMgr->getEditorView()) {
            mUserInteractionMgr->getEditorView()->open(pyFile);
        }
    }
    void OpenModelFiles(const QStringList& modelFiles)
    {
        if (mFileOperations) {
            mFileOperations->importModels(modelFiles);
        }
    }
};

/**
 * @brief 读取样式表文件
 * @param filePath 样式表文件路径
 * @return 样式表内容
 */
static QString readStyleSheet(const QString& filePath)
{
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

/**
 * @brief 应用样式表
 */
static void applyStyleSheets()
{
#ifdef NCTI_QT_CAD_TEST_LOCAL_QSS
    QSSLoader::getInstance()->load(QDir(NCTI_QT_CAD_TEST_LOCAL_QSS),
                                         {"widgets", "script_editor", "option", "sketchDialog"});
#else
    QStringList qssFiles = {QStringLiteral(":/style/widgets.qss"),
                            QStringLiteral(":/style/script_editor.qss"),
                            QStringLiteral(":/style/option.qss"),
                            QStringLiteral(":/style/sketchDialog.qss")};

    QStringList stylesheets;
    for (const auto& path : qssFiles) {
        QString styleSheet = readStyleSheet(path);
        if (!styleSheet.isEmpty()) {
            stylesheets.append(styleSheet.trimmed());
        }
    }

    if (!stylesheets.isEmpty()) {
        QString qss = stylesheets.join("\n");
        qApp->setStyleSheet(qss);
    }
#endif // NCTI_QT_CAD_TEST_LOCAL_QSS
}

MainWindow* MainWindow::mInstance = nullptr;


MainWindow::MainWindow(QWidget* parent, SARibbonMainWindowStyleFlag flag, bool titlebarVisible)
    : SARibbonMainWindow(parent, flag)
    , d_ptr(new MainWindowPrivate(this, titlebarVisible))
{
    mInstance = this;

    mSignals = new MainWindowSignals();

    QCoreApplication::instance()->installNativeEventFilter(this);
    QObject::connect(this, &MainWindow::signalAdminDrop, this, &MainWindow::receiveAdminDrop, Qt::QueuedConnection);

    setAcceptDrops(true);
    
    // 初始化功能模块管理器
    d_ptr->mUIOptMgr             = new UIOptionManager(this);
    d_ptr->mSketchEditor         = new SketchEditor(this);
    d_ptr->mAssOperations         = new AssemblyOperations(this);
    d_ptr->mAIFeatureRecognizer  = new AIFeatureRecognizer(this);
    d_ptr->mSimulationController = new SimulationController(this);
    d_ptr->mGeometryBuilder      = new GeometryBuilder(this);
    d_ptr->mFileOperations       = new FileOperations(this);
    d_ptr->mViewControl          = new ViewControl(this);
    d_ptr->mIPCManager           = new IPCManager(this);
    d_ptr->mPreferenceSettings   = new PreferenceSettings(this);
    d_ptr->mUserInteractionMgr   = new UserInteractionManager(this);
    d_ptr->mObjectTreeMgr        = new ObjectTreeManager(this);
    
    // 初始化各模块
	d_ptr->mUIOptMgr->initialize();
	d_ptr->mAssOperations->initialize();
	d_ptr->mSketchEditor->initialize();
	d_ptr->mAIFeatureRecognizer->initialize();
	d_ptr->mSimulationController->initialize();
	d_ptr->mGeometryBuilder->initialize();
	d_ptr->mFileOperations->initialize();
	d_ptr->mViewControl->initialize();
	d_ptr->mIPCManager->initialize();
	d_ptr->mPreferenceSettings->initialize();
	d_ptr->mUserInteractionMgr->initialize();
	d_ptr->mObjectTreeMgr->initialize();
	d_ptr->mObjectTreeMgr->initialize();

    setupUi();

    // 初始化选择模式和显示模式
    d_ptr->mPreferenceSettings->initSelVisualMode();

    //设置窗口尺寸
	resize(1280, 720);

	// 检查窗口尺寸是否超过屏幕可用区域
	QSize windowSize = frameSize();
	QRect screenGeo = QGuiApplication::primaryScreen()->availableGeometry();
	if (windowSize.width() > screenGeo.width() || windowSize.height() > screenGeo.height()) {
		showMaximized();
	}
	else {
		setGeometry(QStyle::alignedRect(Qt::LeftToRight, Qt::AlignCenter, windowSize, screenGeo));
	}

    NctiShortcutKeyOperating::SetOpenFileFun(HotKeyOpenNcti); ///< 设置打开ncti文件快捷键回调
    NctiShortcutKeyOperating::SetNewFileFun(HotKeyNewDoc);    ///< 设置新建文档快捷键回调
    NctiShortcutKeyOperating::SetSaveFileFun(HotKeySaveNcti); ///< 设置保存ncti文件快捷键回调
    NctiDeleteTool::SetStartDeleteCallback(StartDelete);//对象删除前回调
    NctiDeleteTool::SetEndDeleteCallback(EndDelete);    //对象删除后回调

    //先显示窗体，后台再加载
    LoadingSpinnerWidget::showLoading(this, []() {
            bool ret = NCTI::NctiInitializeTool().LoadPythonModel();
            if (ret == false)
                ret = false;
        }, [this]() {
            // Python初始化要保证在主线程来执行，否则调用会出现问题
            const char* exeDir = NctiPluginsManager::instance()->GetTempFullPath();
            if (!NctiPythonTool::InitPyInterpreter(exeDir)) {
                NctiQTPubFun::showErrorMsgBox(NctiErrorType::PythonError);
                close();
            }

            NCTI::NctiInitializeTool().InitPlugins();

            // 设置Py脚本对话框回调
            NctiPythonTool::SetDialogCallbackFun(NctiQTPubFun::PythonShowDlg, this);

            // 设置自定义Py脚本对话框回调
            NctiPythonTool::SetCustomDialogCallbackFun(NctiQTPubFun::PythonShowCustomDlg, this);

            // 设置Py脚本进度回调
            NctiPythonTool::SetProgressCallbackFun([this](int value) { this->setProgress(value, mCurrentTaskId); });

            // 初始化完成后，向launcher发送任务请求
            if (d_ptr->mIPCManager) {
                d_ptr->mIPCManager->sendTaskRequest();
            }
        });
}

MainWindow::MainWindow( SARibbonMainWindowStyleFlag flag, const AppArguments& args)
    : MainWindow(nullptr, flag, args.titlebarVisible)
{
    if (!args.server.isEmpty()) {
        //连接服务器
        d_ptr->mIPCManager->initTaskInfo(args.type, args.file, args.geometry, args.constraint, args.mesh);
        d_ptr->mIPCManager->createLocalSocket(args.server);
    }
    else {
#ifdef NCTI_ENABLE_GRPC_SERVICE
        if (args.port > 0) {
            mAPIServer.setMainWindow(this);
            std::string address = "localhost:{";
            address += std::to_string(args.port);
            address += "}";
            try {
                // 启动gRPC服务
                mAPIServer.Start(address);
            }
            catch (const std::exception& e) {
                ErrorInfo error;
                error.code = 2;
                error.message = "ServiceStartFailed,port "+std::to_string(args.port);
                error.detail = e.what();
                outputErrorAsJson(error);
            
                auto cleanupAndExit = [error, this]() {
                    qApp->exit(error.code);
                    };
                
                // 服务启动失败后退出程序
                QMetaObject::invokeMethod(qApp, cleanupAndExit, Qt::QueuedConnection);
                return;
            }
        }
#endif
        if (!args.file.isEmpty() || !args.pyFile.isEmpty()) {
            // 执行Python脚本
            RunArguments pyArg;
            pyArg.file = args.file;
            pyArg.pyPath = args.pyFile;
            pyArg.doc = (EnumModelDoc)args.geometry;
            pyArg.dcmDoc = (EnumGCSDoc)args.constraint;
            pyArg.meshDoc = (EnumMeshDoc)args.mesh;
            runPyScript(pyArg);
        }
    }
}

MainWindow::~MainWindow()
{
    mInstance = nullptr;
}

void MainWindow::showEvent(QShowEvent* event)
{
    QMainWindow::showEvent(event);
    
#ifdef Q_OS_WIN
    static bool dropSetupDone = false;
    if (!dropSetupDone) {
        auto vHwnd = (HWND)winId();
        if (vHwnd) {
            DragAcceptFiles(vHwnd, true);
            RevokeDragDrop(vHwnd);
        }
        dropSetupDone = true;
    }
#endif

    if (mWinPlatformContainer) {
        NctiQTPubFun::RefreshViews(mWinPlatformContainer->GetPlatform());
    }
}

void MainWindow::closeEvent(QCloseEvent* event)
{
    QMainWindow::closeEvent(event);
    if (mWinPlatformContainer)
	{
        delete mWinPlatformContainer;
        mWinPlatformContainer = nullptr;
	}
}

void MainWindow::moveEvent(QMoveEvent* event)
{
    QMainWindow::moveEvent(event);
}

#if QT_VERSION_MAJOR >= 6
bool MainWindow::nativeEventFilter(const QByteArray& _EventType, void* _Message, qintptr* _Result)
#else
bool MainWindow::nativeEventFilter(const QByteArray& _EventType, void* _Message, long* _Result)
#endif
{
#ifdef Q_OS_WIN
    auto vMsg = (MSG*)_Message;
    if (vMsg && vMsg->message == WM_DROPFILES)
    {
        auto vFileArray = QList<QUrl>();
        wchar_t vFilePath[1024] = { 0 };
        auto vCount = DragQueryFileW((HDROP)vMsg->wParam, 0xFFFFFFFF, nullptr, 0);
        for (auto vIndex = 0u; vIndex < vCount; ++vIndex)
        {
            auto vPathSize = DragQueryFileW((HDROP)vMsg->wParam, vIndex, vFilePath, 1024 - 1);
            vFilePath[vPathSize] = { 0 };
            vFileArray.push_back(QUrl::fromLocalFile(QString::fromStdWString(vFilePath)));
        }
        POINT vPoint;
        DragQueryPoint((HDROP)vMsg->wParam, &vPoint);
        DragFinish((HDROP)vMsg->wParam);

        Q_EMIT signalAdminDrop((WId)vMsg->hwnd, QPoint((int)vPoint.x, (int)vMsg->pt.y), vFileArray);
        return true;
    }
#endif
    return false;
}

void MainWindow::dragEnterEvent(QDragEnterEvent* _Event)
{
    auto vMimeData = _Event->mimeData();
    if (vMimeData) {
        auto vUrls = vMimeData->urls();
        for (const auto& vIterator : vUrls) {
            if (vIterator.isLocalFile()) {
                _Event->accept();
            }
        }
    }
    QWidget::dragEnterEvent(_Event);
}

void MainWindow::dragMoveEvent(QDragMoveEvent* _Event)
{
    QWidget::dragMoveEvent(_Event);
}

void MainWindow::dropEvent(QDropEvent* _Event)
{
    if (auto* vMimeData = _Event->mimeData(); vMimeData) {
        std::optional<QString> nctiFile;
        std::optional<QString> pyFile;
        QStringList modelFiles;

        // 支持的模型文件类型
        static const auto modelExtensions = std::set<QString>{ "igs", "stp", "step", "fbx", "prt" };

        for (const auto& url : vMimeData->urls()) {
            if (url.isLocalFile()) {
                const auto filePath = url.toLocalFile();
                QFileInfo fileInfo(filePath);
                const auto extension = fileInfo.suffix().toLower();
                if (extension == "ncti") {
                    nctiFile = filePath;
                }
                else if (extension == "py") {
                    pyFile = filePath;
                }
                else// if (modelExtensions.contains(extension)) 
                {
                    modelFiles.append(filePath);
                }
            }
        }
        
        bool validFile = true;
        if (nctiFile.has_value())       { d_ptr->OpenNctiFile(*nctiFile);    }
        else if (pyFile.has_value())    { d_ptr->OpenPyFile(*pyFile);        }
        else if (!modelFiles.isEmpty()) { d_ptr->OpenModelFiles(modelFiles); }
        else { validFile = false; }
        validFile ? _Event->accept() : _Event->ignore();
    }
    QWidget::dropEvent(_Event);
}

void MainWindow::receiveAdminDrop(WId _Hwnd, const QPoint& _Point, const QList<QUrl>& _Urls) noexcept
{
    // 查找指定窗口
    auto vWidget = QWidget::find(_Hwnd);
    if (nullptr == vWidget || !vWidget->acceptDrops()) {
        return;
    }

    // 发送事件
    QMimeData vMimeData;
    vMimeData.setUrls(_Urls);
    QDragEnterEvent vDragEnterEvent(_Point, Qt::CopyAction, &vMimeData, Qt::LeftButton, Qt::NoModifier);
    QCoreApplication::sendEvent(vWidget, &vDragEnterEvent);

    QDragMoveEvent vDragMoveEvent(_Point, Qt::CopyAction, &vMimeData, Qt::LeftButton, Qt::NoModifier);
    QCoreApplication::sendEvent(vWidget, &vDragMoveEvent);

    QDropEvent vDropEvent(_Point, Qt::CopyAction, &vMimeData, Qt::LeftButton, Qt::NoModifier, QEvent::Drop);
    QCoreApplication::sendEvent(vWidget, &vDropEvent);
}

MainWindowSignals* MainWindow::Signals() const
{
    return mSignals;
}

void MainWindow::setupUi()
{
    setupStatusBar();

    setupRibbonUi();

    initWindowPlatformContainer();

    if (d_ptr->mUserInteractionMgr) { 
        d_ptr->mUserInteractionMgr->initCommandConsole();
    }

    setMinimumSize(QSize(1280, 720));

    #if defined(__GNUC__) || defined(__clang__)
    m_timer = new QTimer(this);
    connect(m_timer,&QTimer::timeout,[](){
         NctiWindowEventPubFun().handPoolEvent();
    });
    m_timer->start(10);
    #endif
}

void MainWindow::setupStatusBar()
{
    d_ptr->mStatusBar = new QStatusBar(this);
    d_ptr->mStatusBar->setObjectName("statusbar");
    setStatusBar(d_ptr->mStatusBar);

    QWidget* statusContainer = new QWidget(this);
    QHBoxLayout* statusLayout = new QHBoxLayout(statusContainer);
    statusLayout->setContentsMargins(5, 0, 5, 0);
    statusLayout->setSpacing(10);

    d_ptr->mStatusText = new QLabel("", this);
    statusLayout->addWidget(d_ptr->mStatusText, 0);
    statusLayout->addStretch(1);

    // 创建进度条
    d_ptr->mProgressBar = new QProgressBar(this);
    d_ptr->mProgressBar->setObjectName("progressBar");
    d_ptr->mProgressBar->setFixedWidth(150);
    d_ptr->mProgressBar->setRange(0, 100);
    d_ptr->mProgressBar->setValue(0);
    d_ptr->mProgressBar->setTextVisible(false);

    d_ptr->mProgressBar->setStyleSheet(
        "QProgressBar { border: none; background-color: #F0F0F0; }"
        "QProgressBar::chunk { background-color: #0078D7; border-radius: 2px; }"
    );
    // 添加进度条到状态栏右侧
    statusLayout->addWidget(d_ptr->mProgressBar);

    d_ptr->mStatusBar->addWidget(statusContainer, 1);
}

void MainWindow::setupRibbonUi()
{
    SARibbonBar* ribbonbar = ribbonBar();
    if (!ribbonbar) {
        return;
    }

    ribbonbar->setRibbonStyle(SARibbonBar::RibbonStyleLooseTwoRow);
    ribbonbar->setApplicationButton(nullptr);   // 不显示应用程序按钮
    ribbonbar->setQuickAccessBarVisible(false); // 不显示快速应用栏
    ribbonbar->setRibbonPageHeight(72);         // 设置功能页高度

    // 设置主题
    QTimer::singleShot(0, this, [this]() { this->setRibbonTheme(SARibbonTheme::RibbonThemeLight); });

    // 信号处理
    connect(ribbonbar, &SARibbonBar::actionTriggered, this, &MainWindow::onActionTriggered);

    if (!d_ptr->mTitlebarVisible) {
        setTitleBarHidden();
    }
    else {
        setupIconAndTitle();
    }

    // 创建功能面板
    if (d_ptr->mUIOptMgr) {
        d_ptr->mUIOptMgr->CreateRibbonPanels();
    }

    // 加载样式表
    applyStyleSheets();

    //自动切换网格tool
    //connect(ribbonbar, &SARibbonBar::currentRibbonTabChanged, this, &MainWindow::onUpdSelectTool);
}

void MainWindow::setupIconAndTitle()
{
    QString title;
    QString iconPath;

    if (d_ptr->mUIOptMgr) {
        title    = d_ptr->mUIOptMgr->getWindowTitle();
        iconPath = d_ptr->mUIOptMgr->getWindowIcon();
    }

    if (title.isEmpty() || iconPath.isEmpty()) {
        setWindowIcon(QIcon(":/App/app.png"));
        setWindowTitle(QStringLiteral("CAE前处理通用架构集成平台"));
        return;
    }

    QIcon icon(iconPath);
    if (!icon.isNull()) {
        setWindowIcon(icon);
    }
    else {
        setWindowIcon(QIcon(":/App/app.png"));
    }

    setWindowTitle(title);
}

void MainWindow::setTitleBarHidden()
{
    // DLL模式和多进程模式下，不显示标题栏
    setWindowFlags(windowFlags() | Qt::FramelessWindowHint); // 去除边框

    ribbonBar()->setTitleBarVisible(false);
    ribbonBar()->setTitleVisible(false);
    ribbonBar()->setTitleBarHeight(0);
    d_ptr->mStatusBar->setSizeGripEnabled(false);
}

bool MainWindow::runPyScript(const RunArguments& arg, int64_t task_id)
{
    if (!initWindowPlatform()) {
        return false;
    }

    NctiDocument* pDocument = mWinPlatformContainer->GetCurrentViewDocument();
    if (!pDocument || arg.isCreateNewDoc) {
        if (!arg.file.isEmpty()) {
            pDocument = NctiQTPubFun::LoadNctiFile(mWinPlatformContainer->GetPlatform(), arg.file);
        }
        else {
            if (arg.isCreateAssembly) {
                pDocument = NctiQTPubFun::CreateAssemblyDocument(mWinPlatformContainer->GetPlatform(),
                    arg.doc, arg.dcmDoc, arg.meshDoc);
            }
            else {
                pDocument = NctiQTPubFun::CreateModelDocument(mWinPlatformContainer->GetPlatform(),
                    arg.doc, arg.dcmDoc, arg.meshDoc);
            }
        }
        initDocData(pDocument);
        PreferenceSettings::LoadingUIBasedOnJson(this);
    }

    if (!arg.pyPath.isEmpty()) {
        return runPyScript(arg.pyPath, task_id);
    }

    return pDocument == nullptr ? false : true;
}

bool MainWindow::runPyScript(const QString& pyPath, int64_t task_id)
{
    auto doc = mWinPlatformContainer->GetCurrentViewDocument();
    if (!doc)
        return false;

    if (NctiQTPubFun::RunPyScript(mWinPlatformContainer->GetPlatform(), pyPath)) {
        auto view = doc->GetBaseModel()->GetActiveBaseView();
        if (view) {
            view->Zoom();
            view->Update();
        }
        return true;
    }
    return false;
}

void MainWindow::onActionTriggered(QAction* action)
{
	/*QString objName = action->objectName();
	QString strAction = QString("action object name=%1 triggered").arg(objName);
	NctiDebug::debug(strAction.toStdString().c_str());*/
}

NctiDisplayDocElement* MainWindow::activeDoc(NctiBaseModel* i_pBaseModel)
{
    NctiDocViewManager* pDocView      = NctiDocViewManager::GetDocViewManager(i_pBaseModel);
    NctiDisplayDocElement* pActiveDoc = pDocView->GetActiveDocElement()->GetFirstDescendant();
    return pActiveDoc;
}

void MainWindow::HotKeyNewDoc()
{
    if (mInstance) {
        mInstance->getFileOperations()->onNewPart();
    }
}
void MainWindow::HotKeyOpenNcti()
{
    if (mInstance) {
        mInstance->getFileOperations()->onOpenNcti();
    }
}
void MainWindow::HotKeySaveNcti()
{
    if (mInstance) {
        mInstance->getFileOperations()->onSaveNcti();
    }
}

void MainWindow::StartDelete(NctiBaseModel* i_pBaseModel, NctiDisplayObjectList& objVec)
{
	NctiRefreshObject::Instance().Start(i_pBaseModel, objVec);
}

void MainWindow::EndDelete()
{
	NctiRefreshObject::Instance().Finsh();
}

NctiCallbackPopupMenu* MainWindow::getPopupMenuCallback()
{
    return mCallbackPopupMenu;
}

void MainWindow::initDocData(NctiDocument* pDocument)
{
    if (pDocument == nullptr) {
        return;
    }

    auto pUserInterfaceManager = NctiUserInterfaceManager::GetUserInterfaceManager(pDocument->GetBaseModel());
    if (pUserInterfaceManager) {
        mCallbackPopupMenu = NCTI_NEW NctiCallbackPopupMenu(this, pDocument);
        pUserInterfaceManager->SetUserPopupMenu(mCallbackPopupMenu);
        NctiWinUserTraceInterface* pTrace = NCTI_NEW NctiWinUserTraceInterface(this);
        if (pTrace) {
            pUserInterfaceManager->SetTrace(pTrace);
        }
    }

    d_ptr->mObjectTreeMgr->SetTreeModified();
    
    // 对象显示模式同步
    auto cfg = AppConfig::GetConfig();
    //面、边、顶点
    bool face   = cfg->Renderer.ObjectDisplayMode[0];
    bool edge   = cfg->Renderer.ObjectDisplayMode[1];
    bool vertex = cfg->Renderer.ObjectDisplayMode[2];
    if (d_ptr->mViewControl) {
        d_ptr->mViewControl->updateDisplayMode(face, edge, vertex);
    }

    //恢复选择模式
    auto selCheckBoxs  = d_ptr->mUIOptMgr->getSelCheckBoxs();
    auto gridRadioBtns = d_ptr->mUIOptMgr->getGridRadioButtons();

    NctiWindowPlatform* platform = mWinPlatformContainer->GetPlatform();
    if (platform) {
        NctiQTPubFun::SelBody(platform, selCheckBoxs["select_body"]->isChecked());
    }

    for (auto it = gridRadioBtns.begin(); it != gridRadioBtns.end(); ++it) {
        if (it.value()->isChecked()) {
            Q_EMIT mSignals->meshGridSelect(it.key());
            break;
        }
    }

    auto baseModel  = pDocument->GetBaseModel();
    auto baseView   = baseModel->GetFirstBaseView();
    mOperatingKey = NCTI_NEW NctiOperatingKey(baseModel, baseView);
    if (baseView) {
        baseView->AddOperator("NctiOperatingKey", mOperatingKey);
    }
}

void MainWindow::setStatusText()
{
    if (d_ptr->mStatusText == nullptr)
        return;

    NctiDocument* pDocument = mWinPlatformContainer->GetCurrentViewDocument();
    if (!pDocument) {
        d_ptr->mStatusText->setText("");
        return;
    }

    std::string str = NctiDocElementPubFun::GetCurContainerMessage(pDocument);
    std::vector<std::string> arr = NctiString::stringSplit(str, ' ');
    if (arr.size() > 2) {
        str = " " + arr[0] + " " + arr[2];
    }
    d_ptr->mStatusText->setText(str.c_str());
}

void MainWindow::setStatusText(const QString& str)
{
    if (d_ptr->mStatusText == nullptr) {
        return;
    }
    d_ptr->mStatusText->setText(str);
}

QString MainWindow::getStatusText()
{
    if (d_ptr->mStatusText == nullptr) {
        return QString();
    }
    return d_ptr->mStatusText->text();
}

void MainWindow::initWindowPlatformContainer()
{
    mWinPlatformContainer = new NctiWindowPlatformContainer(this);
    mWinPlatformContainer->setContentsMargins(0, 0, 0, 0);

    QPalette palette = mWinPlatformContainer->palette();
    palette.setColor(QPalette::Window, Qt::darkGray);

    mWinPlatformContainer->setPalette(palette);
    mWinPlatformContainer->setAutoFillBackground(true); // 确保背景自动填充

    mWinPlatformContainer->setMinimumWidth(300);
    setCentralWidget(mWinPlatformContainer);

    connect(mWinPlatformContainer, &NctiWindowPlatformContainer::updatePlatform, this, &MainWindow::onUpdatePlatform);
}

void MainWindow::onUpdatePlatform()
{
    if (!mWinPlatformContainer || !mWinPlatformContainer->GetPlatform()) {
        return;
    }

    QScreen* currentScreen = this->screen();
    if (!currentScreen) {
        qWarning() << "updatePlatform: No screen available";
        return;
    }

    const qreal ratio = currentScreen->devicePixelRatio();
    auto&& geo        = mWinPlatformContainer->geometry();
    int width         = static_cast<int>(geo.width() * ratio);
    int height        = static_cast<int>(geo.height() * ratio);

    //qDebug() << "devicePixelRatio: " << ratio << ", updatePlatform: " << width << ", " << height;
    mWinPlatformContainer->GetPlatform()->setSize(width, height);
}

bool MainWindow::initWindowPlatform()
{
    if (!mWinPlatformContainer) {
        qWarning() << "Window platform container not initialized";
        return false;
    }

    mWinPlatformContainer->CreatePlatform();

    if (d_ptr->mObjectTreeMgr) {
        d_ptr->mObjectTreeMgr->onObjectTree();
    }

    if (d_ptr->mUserInteractionMgr) {
        d_ptr->mUserInteractionMgr->showRightSide();
    }

    return true;
}

void MainWindow::closeWindowPlatform()
{
    if (mWinPlatformContainer) {
        mWinPlatformContainer->ClosePlatform();
    }
}

NctiWindowPlatform* MainWindow::getWindowPlatform()
{
    if (mWinPlatformContainer) {
        return mWinPlatformContainer->GetPlatform();
    }
    return nullptr;
}

NctiDocument* MainWindow::getCurrentViewDocment()
{
    if (mWinPlatformContainer) {
        return mWinPlatformContainer->GetCurrentViewDocument();
    }
    return nullptr;
}

UIOptionManager* MainWindow::getUIOptionMgr()
{
    return d_ptr->mUIOptMgr;
}

FileOperations* MainWindow::getFileOperations()
{
    return d_ptr->mFileOperations;
}

IPCManager* MainWindow::getIPCMgr()
{
    return d_ptr->mIPCManager;
}

UserInteractionManager* MainWindow::getUserInteractionMgr()
{
    return d_ptr->mUserInteractionMgr;
}

PreferenceSettings* MainWindow::getPreferenceSettings()
{
    return d_ptr->mPreferenceSettings;
}

ObjectTreeManager* MainWindow::getObjectTreeMgr()
{
    return d_ptr->mObjectTreeMgr;
}

void MainWindow::deleteOperatingKey()
{
    delete mOperatingKey;
    mOperatingKey = nullptr;
}

void MainWindow::setProgress(int value, int64_t task_id)
{
    if (value < 0 || value > 100) {
        return;
    }

    if (task_id <= 0) {
        task_id = generateRandomTaskId();
    }
    mCurrentTaskId = task_id;
    mMapProgress[mCurrentTaskId] = value;

    setStatusProgress(value);
}

int MainWindow::getProgress(int64_t task_id) const
{
    auto it = mMapProgress.find(task_id);
    if (it != mMapProgress.end()) {
        return it->second;
    }
    return 0;
}

std::string MainWindow::getErrMsg(int64_t task_id) const
{
    auto it = mMapErrMsg.find(task_id);
    if (it != mMapErrMsg.end()) {
        return it->second;
    }
    return std::string();
}

void MainWindow::setStatusProgress(int value)
{
    if (d_ptr && d_ptr->mProgressBar) {
        value = qBound(0, value, 100); // 确保值在有效范围内
        d_ptr->mProgressBar->setValue(value);
    }
   
    setStatusProgressVisible(value < 100);
}

void MainWindow::setStatusProgressVisible(bool visible)
{
    if (d_ptr && d_ptr->mProgressBar) {
        d_ptr->mProgressBar->setVisible(visible);
    }
}


} // namespace NCTI

