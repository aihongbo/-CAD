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

#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include "SARibbonMainWindow.h"
#include <QAbstractNativeEventFilter>
#include "mainwindowsignals.h"

#ifdef NCTI_ENABLE_GRPC_SERVICE
#include "CAEPreServiceServer.h"
#include "CAEPreServiceClient.h"
#endif

class QCloseEvent;
class QDragEnterEvent;
class QDragMoveEvent;
class QDropEvent;
namespace NCTI {

struct RunArguments;
struct MainWindowPrivate;

class NctiCallbackPopupMenu;
class NctiBaseModel;
class NctiDocument;
class NctiDisplayObject;
class NctiDisplayDocElement;
class NctiWindowPlatform;
class NctiWindowPlatformContainer;
class NctiOperatingKey;

class UIOptionManager;
class SimulationController;
class FileOperations;
class IPCManager;
class PreferenceSettings;
class UserInteractionManager;
class ObjectTreeManager;
class NctiDisplayObjectList;

struct AppArguments
{
    QString file;           // 文件路径
    QString pyFile;         // Python脚本路径
    QString server;         // 服务器名称（用于IPC）
    QString type;           // 任务类型（用于IPC）
    int geometry = 0;       // 几何类型
    int constraint = 0;     // 约束类型
    int mesh = 0;           // 网格类型
    bool titlebarVisible = true; // 标题栏是否可见
    int port = 0;           // gRPC服务端口号
};

struct ErrorInfo
{
    int code;            // 错误码
    std::string message; // 错误描述
    std::string detail;  // 详细错误信息
};

/**
 * @brief 主窗口类
 * @details 实现了应用程序的主窗口，包括功能区界面、菜单、工具栏等
 */
class MainWindow : public SARibbonMainWindow, public QAbstractNativeEventFilter
{
    Q_OBJECT

public:
    /**
     * @brief 构造函数
     * @param parent 父窗口指针
     * @param flag 窗口样式
     * @param titlebarVisible 标题栏是否可见
     */
    MainWindow(QWidget* parent
        , SARibbonMainWindowStyleFlag flag = SARibbonMainWindowStyleFlag::UseRibbonFrame
        , bool titlebarVisible = true);

    /**
     * @brief 构造函数
     * @param args 结构体参数
     * @param parent 父窗口指针
     */
    MainWindow(SARibbonMainWindowStyleFlag flag, const AppArguments& args);

    /**
     * @brief 析构函数
     */
    ~MainWindow();

private:
    MainWindowPrivate* d_ptr;
    friend struct MainWindowPrivate;

protected:
    /**
     * @brief 窗口显示事件处理
     */
    void showEvent(QShowEvent* event) override;

    /**
     * @brief 窗口关闭事件处理
     */
    void closeEvent(QCloseEvent* event) override;

    /**
     * @brief 窗口移动事件处理
     */
    void moveEvent(QMoveEvent* event) override;

    /**
     * @brief 消息过滤
     */
#if QT_VERSION_MAJOR >= 6
    bool nativeEventFilter(const QByteArray& _EventType, void* _Message, qintptr* _Result) override;
#else
    bool nativeEventFilter(const QByteArray& _EventType, void* _Message, long* _Result) override;
#endif

    /**
     * @brief 拖入
     */
    void dragEnterEvent(QDragEnterEvent* _Event) override;

    /**
     * @brief 移动
     */
    void dragMoveEvent(QDragMoveEvent* _Event) override;

    /**
     * @brief 放下
     */
    void dropEvent(QDropEvent* _Event) override;

Q_SIGNALS:
    /**
     * @brief 拖放事件
     */
    void signalAdminDrop(WId _Hwnd, const QPoint& _Point, const QList<QUrl>& _Urls);

private Q_SLOTS:
    /**
     * @brief 动作触发处理
     */
    void onActionTriggered(QAction* action);

    /**
     * @brief 拖放事件
     */
    virtual void receiveAdminDrop(WId _Hwnd, const QPoint& _Point, const QList<QUrl>& _Urls) noexcept final;
public:
    /**
     * @brief 获取信号对象（用于连接信号）
     */
    MainWindowSignals* Signals() const;

    /**
     * @brief 获取窗口平台对象
     */
    NctiWindowPlatform* getWindowPlatform();

    /**
     * @brief 获取UI选项管理器对象
     */
    UIOptionManager* getUIOptionMgr();

    /**
     * @brief 获取文件操作对象
     */
    FileOperations* getFileOperations();

    /**
     * @brief 获取IPC管理器对象
     */
    IPCManager* getIPCMgr();

    /**
     * @brief 获取用户交互管理器对象
     */
    UserInteractionManager* getUserInteractionMgr();

    /**
     * @brief 获取偏好设置对象
     */
    PreferenceSettings* getPreferenceSettings();

    /**
     * @brief 获取对象树管理器对象
     */
    ObjectTreeManager* getObjectTreeMgr();

    /**
     * @brief 运行Python脚本
     * @param pyPath Python脚本路径
     */
    bool runPyScript(const QString& pyPath, int64_t task_id = 0);

    /**
     * @brief 运行Python脚本
     * @param arg 运行参数
     */
    bool runPyScript(const RunArguments& arg, int64_t task_id = 0);

    /**
     * @brief 获取当前视图文档对象
     */
    NctiDocument* getCurrentViewDocment();

    /**
     * @brief 激活文档
     * @param i_pBaseModel 基础模型指针
     */
    NctiDisplayDocElement* activeDoc(NctiBaseModel* i_pBaseModel);

    /**
     * @brief 初始化平台窗口
     */
    bool initWindowPlatform();

    /**
     * @brief 关闭平台窗口
     */
    void closeWindowPlatform();

    /**
     * @brief 初始化文档数据
     */
    void initDocData(NctiDocument* pDocument);

    /**
     * @brief 获取弹出菜单回调
     */
    NctiCallbackPopupMenu* getPopupMenuCallback();

    /**
     * @brief 设置状态栏提示
     */
    void setStatusText();

    /**
     * @brief 设置状态栏提示
     */
    void setStatusText(const QString& str);

    /**
     * @brief 获取状态栏提示
     */
    QString getStatusText();

    /**
     * @brief 删除操作键
     */
    void deleteOperatingKey();

    /**
     * @brief py脚本执行进度
     */
    void setProgress(int value, int64_t task_id);
    int getProgress(int64_t task_id) const;

    /**
    * @brief py脚本执行错误消息
    */
    std::string getErrMsg(int64_t task_id) const;

	int64_t& GetTaskID() { return mCurrentTaskId; }
private:
    /**
     * @brief 设置UI界面
     */
    void setupUi();

    /**
     * @brief 设置状态栏
     */
    void setupStatusBar();

    /**
     * @brief 设置Ribbon UI界面
     */
    void setupRibbonUi();

    /**
     * @brief 设置图标和标题
     */
    void setupIconAndTitle();

    /**
     * @brief 隐藏标题栏
     */
    void setTitleBarHidden();

    /**
     * @brief 初始化窗口平台容器
     */
    void initWindowPlatformContainer();

    /**
    * @brief 更新平台
    */
    void onUpdatePlatform();

    /**
     * @brief CAD热键新建文档回调
     */
    static void HotKeyNewDoc();

    /**
     * @brief CAD热键打开NCTI文件回调
     */
    static void HotKeyOpenNcti();

    /**
     * @brief CAD热键保存NCTI文件回调
     */
    static void HotKeySaveNcti();

	/**
	 * @brief 删除对象前回调
	 */
	static void StartDelete(NctiBaseModel* ,NctiDisplayObjectList& );

	/**
	 * @brief 删除对象后回调
	 */
	static void EndDelete();

    /**
     * @brief 设置状态栏进度条值
     */
    void setStatusProgress(int value);

    /**
     * @brief 设置状态栏进度条可见性
     */
    void setStatusProgressVisible(bool visible);

private:
    static MainWindow* mInstance;              ///< 主窗口实例
    MainWindowSignals* mSignals{nullptr};      ///< 信号对象成员
    NctiOperatingKey* mOperatingKey{nullptr};  ///< 操作键

    NctiWindowPlatformContainer* mWinPlatformContainer{nullptr}; ///< 窗口平台容器
    NctiCallbackPopupMenu* mCallbackPopupMenu{nullptr};          ///< 回调弹出菜单

    std::unordered_map<int64_t, int> mMapProgress;
    std::unordered_map<int64_t, std::string> mMapErrMsg;
    int64_t mCurrentTaskId{ 0 };
    QTimer* m_timer{nullptr};

#ifdef NCTI_ENABLE_GRPC_SERVICE
    CAEPreServiceServer mAPIServer;
#endif
};

} // namespace NCTI
#endif // MAIN_WINDOW_H