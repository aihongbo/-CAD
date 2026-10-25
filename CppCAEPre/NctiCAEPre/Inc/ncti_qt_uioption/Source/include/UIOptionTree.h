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

#include <QTreeView>
#include <QDragMoveEvent>

#include "UIOptionItemModel.h"

namespace NCTI {

// 前向声明
class UIPanel;

/**
 * @brief UI选项树类
 * @details 继承自QTreeView，用于显示和管理UI选项树结构
 */
class NCTI_UIOPTION UIOptionTree : public QTreeView
{
    Q_OBJECT
public:
    /**
     * @brief 构造函数
     */
    explicit UIOptionTree(QWidget* parent = nullptr, bool useDefault = true);
    
    /**
     * @brief 禁止拷贝构造
     */
    UIOptionTree(const UIOptionTree& other)            = delete;
    
    /**
     * @brief 禁止赋值操作
     */
    UIOptionTree& operator=(const UIOptionTree& other) = delete;
    
    /**
     * @brief 析构函数
     */
    ~UIOptionTree();

public:
    /**
     * @brief 菜单动作枚举
     * @details 定义了上下文菜单中的各种操作
     */
    enum MenuAction {
        New = 0,    ///< 创建分类，创建面板
        Rename,     ///< 重命名分类，重命名面板，重命名动作，重命名动作分组
        Edit,       ///< 编辑分类，编辑面板，编辑动作，编辑分组，编辑动作分组
        Delete,     ///< 删除
        ActionCount,///< 动作计数
        ActionBegin = New, ///< 动作开始
        ActionEnd   = ActionCount ///< 动作结束
    };

    /**
     * @brief 加载本地模型
     * @param bReload 是否重新加载
     */
    void loadLocalModel(bool bReload = false);
    
    /**
     * @brief 更新本地模型
     * @param iconPath 图标路径
     * @param appTitle 应用标题
     * @return true表示成功，false表示失败
     */
    bool updateLocalModel(const QString& iconPath, const QString& appTitle);
    
    /**
     * @brief 获取模型
     * @return UIOptionItemModel指针
     */
    UIOptionItemModel* getModel() const { return mModel; };

protected:
    /**
     * @brief 拖拽对象
     * @return QMimeData指针
     */
    QMimeData* dragObject();
    
    /**
     * @brief 拖拽进入事件
     * @param event 拖拽进入事件指针
     */
    void dragEnterEvent(QDragEnterEvent* event) override;
    
    /**
     * @brief 拖拽移动事件
     * @param event 拖拽移动事件指针
     */
    void dragMoveEvent(QDragMoveEvent* event) override;
    
    /**
     * @brief 拖拽释放事件
     * @param event 拖拽释放事件指针
     */
    void dropEvent(QDropEvent* event) override;
    
    /**
     * @brief 拖拽离开事件
     * @param event 拖拽离开事件指针
     */
    void dragLeaveEvent(QDragLeaveEvent* event) override;
    
    /**
     * @brief 开始拖拽
     * @param supportedActions 支持的拖拽操作
     */
    void startDrag(Qt::DropActions supportedActions) override;

private:
    /**
     * @brief 初始化树
     */
    void initTree();
    
    /**
     * @brief 初始化上下文菜单
     */
    void initContextMenu();
    
    /**
     * @brief 初始化连接
     */
    void initConnections();
    
    /**
     * @brief 自定义上下文菜单请求处理
     * @param pos 位置点
     */
    void onCustomContextMenuRequested(const QPoint& pos);
    
    /**
     * @brief 显示编辑对话框
     * @param index 模型索引
     */
    void showEditDlg(const QModelIndex& index);
    
    /**
     * @brief 显示创建面板项对话框
     * @param index 模型索引
     */
    void showCreatePanelItemDlg(const QModelIndex& index);
    
    /**
     * @brief 删除项
     */
    void deleteItems();
    
    /**
     * @brief 检查动作是否启用
     * @param index 模型索引
     * @param type 菜单动作类型
     * @return true表示启用，false表示禁用
     */
    bool enableAction(QModelIndex const& index, MenuAction const type) const;
    
    /**
     * @brief 获取面板数据
     * @param panelIndex 面板索引
     * @return UIPanel对象
     */
    UIPanel getPanelData(const QModelIndex& panelIndex);

private:
    QAction* mActions[ActionCount];             ///< 动作数组

    QMenu* mContextMenu{nullptr};               ///< 上下文菜单

    QModelIndex mPreviousEventItem;             ///< 上一个事件项
    QPoint mDragMovePosition;                   ///< 拖拽移动位置
    QPoint mDragStartPosition;                  ///< 拖拽起始位置
    QPersistentModelIndex mExtraItem;           ///< 额外项

    UIOptionItemModel* mModel{nullptr};         ///< 模型指针
    bool mUseDefault{true};                     ///< 是否使用默认配置
};
} // namespace NCTI