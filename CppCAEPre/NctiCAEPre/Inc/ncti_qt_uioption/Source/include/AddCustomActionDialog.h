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
#include "dcl_ncti_uioption.h"

#include "NctiBaseDialog.h"
#include "CustomActionManager.h"

namespace Ui {
class AddCustomActionDialog;
}

#include <QListView>
#include <QAbstractListModel>
#include <QStyledItemDelegate>

class QSvgWidget;
class QSvgRenderer;

namespace NCTI {
    
/**
 * @brief 自定义图标模型类
 * @details 继承自QAbstractListModel，用于管理自定义图标的列表显示
 */
class CustomIconModel : public QAbstractListModel
{
    Q_OBJECT
public:
    /**
     * @brief 构造函数
     * @param parent 父对象指针
     */
    CustomIconModel(QObject* parent = nullptr);
    
    /**
     * @brief 添加SVG图标
     * @param path SVG文件路径
     */
    void addSvg(const QString& path);
    
    /**
     * @brief 获取行数
     * @param parent 父索引
     * @return 行数
     */
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    
    /**
     * @brief 获取数据
     * @param index 索引
     * @param role 角色
     * @return 数据变量
     */
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

private:
    QStringList m_svgList; ///< SVG文件路径列表
};

/**
 * @brief 自定义图标委托类
 * @details 继承自QStyledItemDelegate，用于自定义图标项的绘制和事件处理
 */
class CustomIconDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    /**
     * @brief 构造函数
     * @param parent 父对象指针
     */
    CustomIconDelegate(QObject* parent = nullptr);
    
    /**
     * @brief 绘制项
     * @param painter 绘图器
     * @param option 选项
     * @param index 索引
     */
    void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const override;
    
    /**
     * @brief 编辑器事件处理
     * @param event 事件
     * @param model 模型
     * @param option 选项
     * @param index 索引
     * @return true表示处理成功，false表示处理失败
     */
    bool editorEvent(QEvent* event,
                     QAbstractItemModel* model,
                     const QStyleOptionViewItem& option,
                     const QModelIndex& index) override;
                     
    /**
     * @brief 获取项大小
     * @param option 选项
     * @param index 索引
     * @return 项大小
     */
    QSize sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const override;
    
    /**
     * @brief 设置默认选中索引
     * @param index 索引
     */
    void setDefaultSelectedIndex(const QModelIndex& index);
    
    /**
     * @brief 清除选中索引
     */
    void clearSelectedIndex();

private:
    mutable QModelIndex m_selectedIndex; ///< 选中索引
};

/**
 * @brief 添加自定义动作对话框类
 */
class NCTI_UIOPTION AddCustomActionDialog : public NctiBaseDialog
{
    Q_OBJECT
public:
    /**
     * @brief 构造函数
     * @param parent 父对象指针
     * @param title 标题
     * @param actionName 动作名称
     */
    explicit AddCustomActionDialog(QWidget* parent, const QString& title, const QString& actionName = "");
    
    /**
     * @brief 析构函数
     */
    ~AddCustomActionDialog();
    
    /**
     * @brief 设置UI界面
     */
    void setupUi();
    
    /**
     * @brief 获取状态
     * @return 状态值
     */
    int GetStatus() const;
    
    /**
     * @brief 获取动作名称
     * @return 动作名称
     */
    QString actionName();
    
    /**
     * @brief 获取图标路径
     * @return 图标路径
     */
    QString iconPath();
    
    /**
     * @brief 更新图标
     * @param actionName 动作名称
     * @param iconPath 图标路径
     */
    void UpdateIcon(const QString& actionName, const QString& iconPath);
    
    /**
     * @brief 设置图标
     * @param icon QIcon对象
     * @param useDefaultIcon 是否使用默认图标
     */
    void SetIcon(const QIcon& icon, bool useDefaultIcon);

protected:
    /**
     * @brief 取消保存处理
     */
    void onNoSave();
    
    /**
     * @brief 保存处理
     */
    void onSave();
    
    /**
     * @brief 初始化列表视图
     */
    void initListView();
    
    /**
     * @brief 添加默认Logo
     */
    void addDefaultLogo();
    
    /**
     * @brief 设置默认图标
     */
    void setDefaultIcon();
    
    /**
     * @brief 从本地选择Logo
     */
    void onSelectLogoFromLocal();
    
    /**
     * @brief 选择本地Logo
     * @param selected 是否选中
     */
    void onSelectLocalLogo(bool selected);
    
    /**
     * @brief 设置图标
     * @param iconPath 图标路径
     * @param useDefaultIcon 是否使用默认图标
     */
    void SetIcon(const QString& iconPath, bool useDefaultIcon);

private:
    /**
     * @brief 保存状态枚举
     */
    enum SaveStatus { 
        Cancel, ///< 取消
        Save    ///< 保存
    };
    
    Ui::AddCustomActionDialog* ui;          ///< UI界面指针
    SaveStatus m_saveStatus{SaveStatus::Cancel}; ///< 保存状态
    CustomIconModel m_model;                ///< 自定义图标模型
    CustomIconDelegate* m_delegate{nullptr};///< 自定义图标委托
    QString m_originActionName;             ///< 原始动作名称
    QString m_actionName;                   ///< 动作名称
    QString m_iconPath;                     ///< 图标路径
    bool m_isAddMode{true};                 ///< 是否为添加模式
};
} // namespace NCTI