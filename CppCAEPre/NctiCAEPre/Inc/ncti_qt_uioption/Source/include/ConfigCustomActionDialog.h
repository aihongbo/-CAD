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

namespace Ui {
class ConfigCustomActionDialog;
}

#include <QListView>
#include <QAbstractListModel>
#include <QStyledItemDelegate>
#include <QStandardItemModel>

class QSvgWidget;
class QSvgRenderer;

namespace NCTI {
    
/**
 * @brief 配置自定义委托类
 * @details 继承自QStyledItemDelegate，用于自定义配置项的绘制和事件处理
 */
class ConfigCustomDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    /**
     * @brief 构造函数
     * @param parent 父对象指针
     */
    ConfigCustomDelegate(QObject* parent = nullptr);
    
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

private:
    /**
     * @brief 绘制按钮
     * @param painter 绘图器
     * @param rect 矩形区域
     * @param text 文本
     */
    void drawButton(QPainter* painter, const QRect& rect, const QString& text) const;
    
    /**
     * @brief 绘制图标按钮
     * @param painter 绘图器
     * @param rect 矩形区域
     * @param iconPath 图标路径
     */
    void drawIconButton(QPainter* painter, const QRect& rect, const QString& iconPath) const;
    
    /**
     * @brief 计算图标矩形区域
     * @param option 选项
     * @return 图标矩形区域
     */
    QRect calculateIconRect(const QStyleOptionViewItem& option) const;
    
    /**
     * @brief 计算文本矩形区域
     * @param option 选项
     * @return 文本矩形区域
     */
    QRect calculateTextRect(const QStyleOptionViewItem& option) const;
    
    /**
     * @brief 计算编辑按钮矩形区域
     * @param option 选项
     * @return 编辑按钮矩形区域
     */
    QRect calculateEditButtonRect(const QStyleOptionViewItem& option) const;
    
    /**
     * @brief 计算删除按钮矩形区域
     * @param option 选项
     * @return 删除按钮矩形区域
     */
    QRect calculateDeleteButtonRect(const QStyleOptionViewItem& option) const;
    
Q_SIGNALS:
    /**
     * @brief 标题双击信号
     * @param index 索引
     */
    void titleDoubleClicked(const QModelIndex& index);
    
    /**
     * @brief 编辑点击信号
     * @param index 索引
     */
    void editClicked(const QModelIndex& index);
    
    /**
     * @brief 删除点击信号
     * @param index 索引
     */
    void deleteClicked(const QModelIndex& index);

private:
    mutable QModelIndex m_selectedIndex; ///< 选中索引
};

/**
 * @brief 配置自定义动作对话框类
 */
class NCTI_UIOPTION ConfigCustomActionDialog : public NctiBaseDialog
{
    Q_OBJECT
public:
    /**
     * @brief 构造函数
     * @param parent 父对象指针
     * @param title 标题
     */
    explicit ConfigCustomActionDialog(QWidget* parent, const QString& title);
    
    /**
     * @brief 析构函数
     */
    ~ConfigCustomActionDialog();
    
    /**
     * @brief 设置UI界面
     */
    void setupUi();
    
    /**
     * @brief 更新动作名称和图标
     * @param actionName 动作名称
     * @param newActionName 新动作名称
     * @param newIconPath 新图标路径
     * @param newIcon 新图标
     */
    void updateActionNameAndIcon(const QString& actionName,
                                 const QString& newActionName,
                                 const QString& newIconPath,
                                 QIcon newIcon);
    
    /**
     * @brief 编辑自定义动作信号
     * @param name 名称
     * @param iconPath 图标路径
     */
    Q_SIGNAL void sigEditCustomAction(const QString& name, const QString& iconPath);
    
    /**
     * @brief 编辑Python脚本信号
     * @param pyPath Python脚本路径
     */
    Q_SIGNAL void sigEditPyScript(const QString& pyPath);
    
    /**
     * @brief 移除Python脚本信号
     * @param name 名称
     */
    Q_SIGNAL void sigRemovePyScript(const QString& name);

protected:
    /**
     * @brief 初始化列表视图
     */
    void initListView();
    
    /**
     * @brief 初始化模型数据
     * @return 数据数量
     */
    int initModelData();
    
    /**
     * @brief 编辑自定义动作
     * @param index 索引
     */
    void onEditCustomAction(const QModelIndex& index);
    
    /**
     * @brief 编辑Python脚本
     * @param index 索引
     */
    void onEditPyScript(const QModelIndex& index);
    
    /**
     * @brief 移除Python脚本
     * @param index 索引
     */
    void onRemovePyScript(const QModelIndex& index);
    
    /**
     * @brief 确认移除
     * @param itemName 项名称
     * @return true表示确认，false表示取消
     */
    bool IsConfirmRemove(const QString& itemName);

private:
    Ui::ConfigCustomActionDialog* ui;       ///< UI界面指针
    QStandardItemModel m_model;             ///< 标准项模型
    ConfigCustomDelegate* m_delegate{nullptr}; ///< 配置自定义委托
};
} // namespace NCTI