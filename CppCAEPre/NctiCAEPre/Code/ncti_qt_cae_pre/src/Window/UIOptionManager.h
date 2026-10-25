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

#ifndef UI_OPTION_MANAGER_H
#define UI_OPTION_MANAGER_H

#include "MainWindowModules.h"

#include "UIOption.h"
#include "CustomActionManager.h"

#include <QFileSystemWatcher>
#include <QHash>
#include <QString>
#include <QTimer>
#include <QVariant>

#include <QAction>
#include <QCheckBox>
#include <QToolButton>
#include <QList>
#include <QRadioButton>

class SARibbonBar;
class SARibbonMenu;
class SARibbonPage;
class SARibbonPanel;

namespace NCTI {

/**
* @brief UI配置模块类
* @details 对功能区的界面进行配置
* - json配置文件的生成
* - json配置文件的加载
* - 功能区界面组件的生成
*/
struct ActionInfo
{
    QString pageName;                              ///< 所在页的名称
    QString text;                                  ///< 命令名称
    QString iconName;                              ///< 命令图标
    const char* slot             = nullptr;        ///< 槽函数名称
    const QKeySequence& shortCut = QKeySequence(); ///< 快捷键
};

class ConfigCustomActionDialog;

/**
* @brief UI选项管理器类
* @details 管理UI选项配置，包括功能区、自定义命令等
*/
class UIOptionManager : public MainWindowModule
{
    Q_OBJECT

public:
    /**
	* @brief 构造函数
	* @param mainWindow 主窗口指针
	*/
    explicit UIOptionManager(MainWindow* mainWindow);

    /**
	* @brief 模块初始化，在这里处理主窗口的信号
	*/
    void initialize() override;

    /**
	* @brief 加载配置文件，并创建组件
	*/
    void CreateRibbonPanels();

    /**
	* @brief 获取网格单选按钮
	* @return 网格单选按钮哈希表
	*/
    QHash<QString, QRadioButton*> getGridRadioButtons();

    /**
	* @brief 获取选择模式复选框
	* @return 选择模式复选框哈希表
	*/
    QHash<QString, QCheckBox*> getSelCheckBoxs();

    /**
	* @brief 获取显示模式复选框
	* @return 显示模式复选框哈希表
	*/
    QHash<QString, QCheckBox*> getVisualCheckBoxs();

    /**
	* @brief 获取窗口标题
	* @return 窗口标题
	*/
    QString getWindowTitle();

    /**
	* @brief 获取窗口图标
	* @return 窗口图标
	*/
    QString getWindowIcon();

public Q_SLOTS:
    /**
	* @brief UI选项槽函数
	*/
    void onUIOption();

    /**
	* @brief 自定义设置槽函数
	*/
    void onCustomSetting();

    /**
	* @brief 运行自定义脚本槽函数
	*/
    void onRunCustomScript();

    /**
	* @brief 编辑自定义脚本槽函数
	*/
    void onEditCustomScript();

    /**
	* @brief 删除自定义脚本槽函数
	*/
    void onDeleteCustomScript();

    /**
	* @brief 添加自定义命令槽函数
	*/
    void onAddCustomAction();

    /**
	* @brief UI文件改变槽函数
	* @param filePath 文件路径
	*/
    void onUIFileChanged(const QString& filePath);

    /**
	* @brief 编辑自定义命令槽函数
	* @param name 命令名称
	* @param iconUrl 图标URL
	*/
    void onEditCustomAction(const QString& name, const QString& iconUrl);

private:
    /**
	* @brief 创建新面板
	* @param page 页面指针
	* @param text 面板文本
	* @return 面板指针
	*/
    SARibbonPanel* CreateNewPanel(SARibbonPage* page, const QString& text);

    /**
	* @brief 从UI选项创建面板
	* @return 创建成功返回true，否则返回false
	*/
    bool CreatePanelsFromUIOption();

    /**
	* @brief 创建UI页面
	* @param tabDetail 标签页详情
	*/
    void CreateUIPage(const UITabDetail& tabDetail);

    /**
	* @brief 创建UI面板
	* @param page 页面指针
	* @param uiPanel UI面板
	*/
    void CreateUIPanel(SARibbonPage* page, const UIPanel& uiPanel);

    /**
	* @brief 重新加载UI选项
	*/
    void reloadUIOption();

    /**
	* @brief 设置动作对象名称
	* @param action 动作指针
	* @param obj_name 对象名称
	*/
    void SetActionObjName(QAction* action, const std::string& obj_name);

    /**
	* @brief 设置动作快捷键
	* @param action 动作指针
	* @param short_cut 快捷键
	*/
    void SetActionShortCut(QAction* action, const std::string& short_cut);

    /**
	* @brief 创建UI动作
	* @param action UI动作
	* @return 动作指针
	*/
    QAction* CreateUIAction(const UIAction& action);

    /**
	* @brief 创建UI菜单动作
	* @param action UI动作
	* @return 动作指针
	*/
    QAction* CreateUIMenuAction(const UIAction& action);

    /**
	* @brief 创建UI组
	* @param panel 面板指针
	* @param group UI组
	*/
    void CreateUIGroup(SARibbonPanel* panel, const UIGroup& group);

    /**
	* @brief 创建UI动作组
	* @param panel 面板指针
	* @param actionGroup UI动作组
	*/
    void CreateUIActionGroup(SARibbonPanel* panel, const UIActionGroup& actionGroup);

    /**
	* @brief 创建UI面板动作
	* @param p 面板指针
	* @param index 索引
	* @param vUIAction UI动作列表
	* @return 创建成功返回true，否则返回false
	*/
    bool CreateUIPanelAction(SARibbonPanel* p, int index, const std::vector<UIAction>& vUIAction);

    /**
	* @brief 创建UI面板组
	* @param p 面板指针
	* @param index 索引
	* @param vUIGroup UI组列表
	* @return 创建成功返回true，否则返回false
	*/
    bool CreateUIPanelGroup(SARibbonPanel* p, int index, const std::vector<UIGroup>& vUIGroup);

    /**
	* @brief 创建UI面板动作组
	* @param p 面板指针
	* @param index 索引
	* @param vUIActionGroup UI动作组列表
	* @return 创建成功返回true，否则返回false
	*/
    bool CreateUIPanelActionGroup(SARibbonPanel* p, int index, const std::vector<UIActionGroup>& vUIActionGroup);

    /**
	* @brief 创建组标题控件
	* @param parent 父控件指针
	* @param uiActionGroup UI动作组
	* @return 工具按钮指针
	*/
    QToolButton* createGroupTitleWidget(QWidget* parent, const UIActionGroup& uiActionGroup);

private:
    /**
	* @brief 加载自定义命令
	*/
    void loadCustomActions();

    /**
	* @brief 添加命令到自定义面板
	* @param customPanel 自定义面板指针
	* @param customAction 自定义命令
	*/
    void addActionToCustomPanel(SARibbonPanel* customPanel, const CustomAction& customAction);

    /**
	* @brief 获取自定义命令名称
	* @param menuAction 菜单动作指针
	* @return 命令名称
	*/
    QString getCustomActionName(QAction* menuAction);

    /**
	* @brief 获取自定义命令按钮
	* @param actionName 命令名称
	* @return 动作指针
	*/
    QAction* getCustomActionButton(const QString& actionName);

    /**
	* @brief 移除自定义命令按钮
	* @param actionName 命令名称
	*/
    void removeCustomActionButton(const QString& actionName);

    /**
	* @brief 删除自定义脚本
	* @param actionName 命令名称
	*/
    void deleteCustomScript(const QString& actionName);

private:
    /**
	* @brief 添加视图动作到面板
	* @param panel 面板指针
	*/
    void AddViewActionsToPanel(SARibbonPanel* panel);

    /**
	* @brief 创建视图动作
	* @param text 文本
	* @param iconName 图标名称
	* @param slot 槽函数
	* @return 动作指针
	*/
    QAction* CreateViewAction(const QString& text, const QString& iconName, const char* slot = nullptr);

    /**
	* @brief 创建菜单动作
	* @param info 动作信息
	* @param items 子项列表
	* @return 动作指针
	*/
    QAction* CreateMenuAction(const ActionInfo& info, const QList<ActionInfo>& items);

    /**
	* @brief 创建菜单
	* @param items 子项列表
	* @param var 变量
	* @return 菜单指针
	*/
    SARibbonMenu* CreateMenu(const QList<ActionInfo>& items, const QVariant& var = QVariant());

    /**
	* @brief 获取图标信息
	* @param pageName 页面名称
	* @param iconName 图标名称
	* @return 图标信息对
	*/
    std::pair<QString, QString> getIconInfo(const QString& pageName, const QString& iconName);

    /**
	* @brief 获取文件哈希值
	* @param filePath 文件路径
	* @return 文件哈希值
	*/
    QString getFileHash(const QString& filePath);

    /**
	* @brief 添加动作到面板
	* @param panel 面板指针
	* @param action 动作指针
	* @param minWidth 最小宽度
	*/
    void addActionToPanel(SARibbonPanel* panel, QAction* action, int minWidth);

    /**
	* @brief 添加动作到面板
	* @param panel 面板指针
	* @param item 动作信息
	* @return 动作指针
	*/
    QAction* addActionToPanel(SARibbonPanel* panel, const ActionInfo& item);

    /**
	* @brief 添加动作到面板
	* @param panel 面板指针
	* @param pageName 页面名称
	* @param text 文本
	* @param iconName 图标名称
	* @param slotName 槽函数名称
	* @param shortCut 快捷键
	* @return 动作指针
	*/
    QAction* addActionToPanel(SARibbonPanel* panel,
                              const QString& pageName,
                              const QString& text,
                              const QString& iconName,
                              const char* slotName         = nullptr,
                              const QKeySequence& shortCut = QKeySequence());

    /**
	* @brief 添加动作到面板
	* @param panel 面板指针
	* @param item 动作信息列表
	* @return 动作指针列表
	*/
    QList<QAction*> addActionToPanel(SARibbonPanel* panel, const QList<ActionInfo>& item);

    /**
	* @brief 创建动作组项
	* @tparam T 控件类型
	* @param parent 父控件指针
	* @param item 动作组项
	* @return 控件指针
	*/
    template <typename T>
    inline T* createActionGroupItem(QWidget* parent, const UIActionGroupItem& item)
    {
        T* widget = new T(QString::fromUtf8(item.name.c_str()), parent);
        widget->setObjectName(QString::fromStdString(item.object_name));
        widget->setProperty("select_mode_checkbox", true);
        return widget;
    }

    /**
	* @brief 创建单选按钮动作组项（重载版本）
	* @param parent 父控件指针
	* @param item 动作组项
	* @return 单选按钮指针
	*/
    inline QRadioButton* createActionGroupItem(QWidget* parent, const UIActionGroupItem& item)
    {
        QRadioButton* btn = new QRadioButton(QString::fromUtf8(item.name.c_str()), parent);
        btn->setAutoExclusive(true);
        btn->setObjectName(QString::fromStdString(item.object_name));
        return btn;
    }

    /**
	* @brief 连接控件到槽函数
	* @tparam WidgetType 控件类型
	* @tparam SignalFunc 信号函数类型
	* @param widget 控件指针
	* @param signal 信号
	* @param slot_name 槽函数名称
	* @param obj_name 对象名称
	*/
    template <typename WidgetType, typename SignalFunc>
    inline bool ConnectWidgetToSlot(WidgetType* widget,
                                    SignalFunc signal,
                                    const std::string& slot_name,
                                    const std::string& obj_name = "")
    {
		if (slot_name.empty() || !widget) {
			return false;
		}

        QString slotName = QString::fromStdString(slot_name);
        QString objName  = QString::fromStdString(obj_name);

        QString signature;
        if (!objName.isEmpty()) {
            // 查找带QString参数的函数签名
            signature = slotName + "(QString)";
        }
        else {
            signature = slotName + "()";
        }
        int slotIndex = m_mainWindow->Signals()->metaObject()->indexOfSlot(qUtf8Printable(signature));
        if (slotIndex != -1) {
            if (!objName.isEmpty()) {
                connect(widget, signal, this, [this, slotName, objName]() mutable {
                    QMetaObject::invokeMethod(m_mainWindow->Signals(),
                        qUtf8Printable(slotName), Qt::DirectConnection, Q_ARG(QString, objName));
                    });
            }
            else {
                connect(widget, signal, [this, slotName]() {
                    QMetaObject::invokeMethod(m_mainWindow->Signals(), qUtf8Printable(slotName), Qt::DirectConnection);
                    });
            }
            return true;
        }
        else {
            int signalIndex = m_mainWindow->Signals()->metaObject()->indexOfSignal(qUtf8Printable(signature));
            if (signalIndex != -1) {
                if (!objName.isEmpty()) {
                    connect(widget, signal, this, [this, slotName, objName]() mutable {
                        QMetaObject::invokeMethod(m_mainWindow->Signals(),
                            qUtf8Printable(slotName), Qt::DirectConnection, Q_ARG(QString, objName));
                        });
                }
                else {
                    connect(widget, signal, [this, slotName]() {
                        QMetaObject::invokeMethod(m_mainWindow->Signals(), qUtf8Printable(slotName), Qt::DirectConnection);
                        });
                }
                return true;
            }
        }
        
        qDebug() << "Failed to find slot or signal for " << slotName;
        return false;
    }

    /**
	* @brief 保存Python脚本到本地
	* @param filePath 文件路径
	* @return 保存成功返回true，否则返回false
	*/
    bool savePyScriptToLocal(const QString& filePath);

    /**
	* @brief 获取自定义面板
	* @return 自定义面板指针
	*/
    SARibbonPanel* getCustomPanel();

    /**
	* @brief 获取页面
	* @param objectName 对象名称
	* @return 页面指针
	*/
    SARibbonPage* getPage(const std::string& objectName);

private:
    ConfigCustomActionDialog* mCustomActionCfgDlg{nullptr}; ///< 自定义命令配置对话框
    SARibbonBar* mRibbonbar;                                ///< 功能区栏
    std::unordered_map<std::string, SARibbonPage*> mPageMap; ///< 页面映射
    SARibbonPanel* mCustomPanel{nullptr};                   ///< 自定义命令面板

    QHash<QString, QCheckBox*> mVisualModeCheckBoxs;       ///< 显示模式复选框
    QHash<QString, QCheckBox*> mSelectModeCheckBoxs;       ///< 选择模式复选框
    QHash<QString, QRadioButton*> mGridSelectRadioButtons; ///< 网格拾取单选按钮

    QFileSystemWatcher mUIWatcher;          ///< UI监视器
    QTimer* mUIReloadTimer{nullptr};        ///< UI重载定时器
    QHash<QString, QString> mFileHashCache; ///< 文件哈希缓存
};

} // namespace NCTI

#endif // UI_OPTION_MANAGER_H