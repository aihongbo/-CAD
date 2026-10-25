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

#include <array>

#include "NctiBaseDialog.h"

class QListView;
class QComboBox;
class QRadioButton;
class QCheckBox;
class QTreeWidget;
class QTreeWidgetItem;
class QListWidget;
class QLineEdit;
class QStackedWidget;
class SelectColorWidget;
class ModelColorPreviewWidget;

enum class ColorWidgetType {
    General,    
    Model,      
    Sketch,     
    Render      
};

namespace NCTI {
/**
 * @brief 选项卡对话框类
 * @details 用于设置和配置各种选项的对话框，包括主题颜色、多语言、环境设置等
 */
class OptionsDlg : public NctiBaseDialog
{
    Q_OBJECT

public:
    explicit OptionsDlg(QWidget* parent = nullptr);

    ~OptionsDlg();

    /**
     * @brief 设置显示模式
     * @param face 面显示状态
     * @param edge 边显示状态
     * @param vertex 顶点显示状态
     */
    void setObjectDisplayMode(bool face, bool edge, bool vertex);

    /**
     * @brief 显示或隐藏控制台
     * @param consoleState 控制台显示状态
     */
    void setConsoleVisible(bool consoleState);

    /**
     * @brief 显示或隐藏脚本编辑器
     * @param scriptEditorState 脚本编辑器显示状态
     */
    void setScriptEditorVisible(bool scriptEditorState);

    /**
     * @brief 更新显示模式图标
     * @details 根据当前的显示模式（面、边、顶点）更新UI中的显示图标
     */
    void updateDisplayModeIcon();

    /**
     * @brief 递归删除树控件项
     * @param item 要删除的树项
     */
    void deleteItemRecursive(QTreeWidgetItem* item);

    /**
     * @brief 显示浮动标签
     * @details 在操作后显示临时提示信息
     */
    void showFloatingLabel(const QString& text);

    /**
     * @brief 显示颜色选择控件
     * @param color 初始颜色
     * @param pos 显示位置
     */
    void showSelectColorWidget(const QColor& color, const QPoint& pos);

    /**
     * @brief 添加应用程序目录中的插件
     * @param appDir 应用程序目录
     * @param pluginName 插件名称
     * @return 添加的树控件项指针
     */
    QTreeWidgetItem* addPluginInApplicationDir(const QString& appDir, const QString& pluginName);

    /**
     * @brief 添加外部目录中的插件
     * @param pluginName 插件名称
     * @return 添加的树控件项指针
     */
    QTreeWidgetItem* addPluginInOutsideDir(const QString& pluginName);

    /**
     * @brief 添加插件
     * @param pluginPath 插件路径
     * @param plugin 插件名称
     */
    void onAddPlugin(const QString pluginPath, const QString plugin);

    /**
     * @brief 面按钮状态改变处理
     * @details 当面按钮选中状态改变时调用
     */
    void onFaceButtonToggled();

    /**
     * @brief 边按钮状态改变处理
     * @details 当边按钮选中状态改变时调用
     */
    void onEdgeButtonToggled();

    /**
     * @brief 顶点按钮状态改变处理
     * @details 当顶点按钮选中状态改变时调用
     */
    void onVertexButtonToggled();

    /**
     * @brief 设置按钮颜色
     * @param color 要设置的颜色
     */
    void setButtonColor(const QColor& color);

    /**
     * @brief 添加测试用例路径
     * @details 打开文件对话框让用户选择测试用例路径并添加
     */
    void onAddTestCasePathClicked();

    /**
     * @brief 删除测试用例路径
     * @details 删除当前选中的测试用例路径
     */
    void onDeleteTestCasePathClicked();

    /**
     * @brief 删除加载的插件
     * @details 删除当前选中的插件项
     */
    void onDeleteLoadingPluginsClicked();

    /**
     * @brief 是否开启备份功能
     */
    void onEnableBackup(bool enable);

    /**
     * @brief 选择目录
     * @details 打开目录选择对话框并设置到指定的行编辑框
     * @param lineEdit 目标行编辑框
     */
    void selectDir(QLineEdit* lineEdit);

    /**
     * @brief 更新颜色
     * @details 根据用户选择更新颜色设置
     * @param color 新的颜色值
     */
    void onUpdateColor(const QColor& color);

    /**
     * @brief 在按钮下方显示颜色选择控件
     * @param button 目标按钮
     * @param type 颜色控件类型
     */
    void onShowColorWidgetBelowButton(QPushButton* button, ColorWidgetType type);

private:
    /**
     * @brief 初始化界面
     * @details 创建并设置UI布局和控件
     */
    void setupUI();

    QListView* CreateItemListView(QStackedWidget* );
    QPushButton* CreateDefaultBtn();
    QPushButton* CreateSaveBtn();
    QLabel* CreateFloatingLabel();
    QPushButton* CreateColorBtn(const QString& objName);

    std::pair<QRadioButton*, QRadioButton*> createRadioButtonPair(QWidget* parent, const QString& showText, const QString& hideText, int width = 60);

    /**
     * @brief 初始化控件
     * @details 创建并配置UI控件
     */
    void initWidgets();

    /**
     * @brief 初始化信号连接
     * @details 设置控件之间的信号和槽连接
     */
    void initConnects();
    void initColorConnections();
    void initPathConnections();
    void initPluginConnections();
    void initBackupConnections();

    /**
     * @brief 初始化应用配置
     */
    void loadAppConfig();

    /**
     * @brief 初始化插件列表
     * @param config 应用配置对象
     */
    void initPlugins();

    /**
     * @brief 获取插件数据
     * @param config 应用配置对象引用，用于存储插件数据
     */
    void getPluginsData();

    /**
     * @brief 设置颜色按钮样式表
     * @param button 目标按钮
     * @param color 要设置的颜色
     */
    void setColorButtonStyleSheet(QPushButton* button, const QColor& color);

    /**
     * @brief 更新背景颜色
     * @details 根据当前设置更新背景渐变颜色
     */
    void updateBackgroundColor();

    /**
     * @brief 设置预览模型控件颜色
     * @param button 目标按钮
     * @param color 要设置的颜色
     */
    void setPreviewModelWidgetColor(QPushButton* button, const QColor& color);

    /**
     * @brief 批量设置颜色按钮
     * @param buttons 按钮指针数组
     * @param colors 颜色值数组
     */
    void setColorButtons(const std::array<QPushButton*, 8>& buttons, const std::array<int, 8>& colors);

    /**
     * @brief 设置单选按钮对
     * @param showBtn 显示按钮
     * @param hideBtn 隐藏按钮
     * @param show 是否显示
     */
    void setRadioButtonPair(QRadioButton* showBtn, QRadioButton* hideBtn, bool show);

    /**
     * @brief 批量保存颜色配置
     * @param buttons 按钮指针数组
     * @param configColors 配置颜色颜色数组
     */
    void saveColorConfigs(const std::array<QPushButton*, 8>& buttons, std::array<int, 8>& configColors);

    /**
     * @brief 更新应用配置JSON
     * @details 将当前UI设置保存到配置JSON文件
     */
    bool updateAppConfig();

    /**
     * @brief 添加加载插件点击处理
     * @details 处理添加插件按钮点击事件，打开添加插件对话框
     */
    void onAddLoadingPluginsClicked();

    /**
    * @brief 创建基本设置控件
    */
    QWidget* CreateSettingWidget();

    /**
     * @brief 创建CAD环境设置控件
     */
    QWidget* CreateCADEnvironmentSettingsWidget();

    /**
     * @brief 创建颜色设置控件
     */
    QWidget* CreateColorSettingWidget();

    /**
     * @brief 创建模式和光照设置控件
     */
    QWidget* CreateModeAndLightingSettingWidget();

    /**
     * @brief 创建草图绘制和操作轴设置控件
     */
    QWidget* SketchDrawingAndModeAxiseSettingWidget();

    /**
     * @brief 创建路径设置控件
     */
    QWidget* CreatePathSettingsWidget();

    /**
     * @brief 创建加载插件控件
     */
    QWidget* CreateLoadingPluginsWidget();

    /**
     * @brief 创建窗口控件
     */
    QWidget* CreateWindowWidget();

    /**
     * @brief 创建备份控件
     */
    QWidget* CreateBackupsWidget();

protected:
    /**
     * @brief 事件过滤器
     * @param obj 对象指针
     * @param event 事件指针
     * @return 是否处理事件
     */
    bool eventFilter(QObject* obj, QEvent* event) override;

Q_SIGNALS:
    /**
     * @brief 保存按钮点击信号
     */
    void savePushButtonClicked();

private:
    class OptionsDlgPrivate;
    OptionsDlgPrivate* d_ptr;
};

} // namespace NCTI