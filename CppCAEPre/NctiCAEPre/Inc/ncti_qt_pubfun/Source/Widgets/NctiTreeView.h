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

#include "dcl_ncti_qt_pubfun.h"
#include <QTreeView>
#include <QTimer>
#include <QFocusEvent>
#include <vector>
#include <qpainterpath.h>

namespace NCTI {
    /**
     * @brief 树视图类型枚举
     */
    enum class NctiTreeViewType { 
        Normal,     ///< 普通类型
        Assemble,   ///< 装配类型
        Object,     ///< 对象类型
        Scene       ///< 场景类型
    };

    /**
     * @brief 树模型数据结构体前置声明
     */
    struct NctiTreeModelData;
    
    /**
     * @brief 树项类前置声明
     */
    class NctiTreeItem;
    
    /**
     * @brief 树视图类
     * @details 用于显示树形结构数据的视图控件，继承自QTreeView，支持多种交互操作
     */
    class DECL_NCTI_QT_PUBFUN NctiTreeView : public QTreeView
    {
        Q_OBJECT
    public:
        /**
         * @brief 构造函数
         * @param parent 父窗口指针
         * @param type 树视图类型
         */
        explicit NctiTreeView(QWidget* parent = 0, NctiTreeViewType type = NctiTreeViewType::Normal);
        
        /**
         * @brief 更新视图
         * @param vModelData 模型数据列表
         */
        void update(const std::vector<NctiTreeModelData>& vModelData);
        
        /**
         * @brief 鼠标按下事件处理
         * @param event 鼠标事件指针
         */
        void mousePressEvent(QMouseEvent* event) override;
        
        /**
         * @brief 鼠标移动事件处理
         * @param event 鼠标事件指针
         */
        void mouseMoveEvent(QMouseEvent* event) override;
        
        /**
         * @brief 鼠标释放事件处理
         * @param event 鼠标事件指针
         */
        void mouseReleaseEvent(QMouseEvent* event) override;
        
        /**
         * @brief 事件过滤器
         * @param obj 对象指针
         * @param event 事件指针
         * @return 过滤结果
         */
        bool eventFilter(QObject* obj, QEvent* event) override;
        
        /**
         * @brief 焦点离开事件处理
         * @param event 焦点事件指针
         */
        void focusOutEvent(QFocusEvent* event) override;
        
        /**
         * @brief 获取选中项
         */
        void getSelectedItems();
        
    Q_SIGNALS:
        /**
         * @brief 项点击信号
         * @param ojbName 对象名称
         * @param pObj 对象指针
         */
        void sigItemClicked(const QString& ojbName, void* pObj);
        
        /**
         * @brief 上下文菜单请求信号
         * @param ojbName 对象名称
         * @param pObj 对象指针
         */
        void sigContextMenuRequested(const QString& ojbName, void* pObj);
        
        /**
         * @brief 项双击信号
         * @param typeName 类型名称
         * @param pObj 对象指针
         */
        void sigItemDoubleClicked(const QString& typeName, void* pObj);
        
        /**
         * @brief 树项选择信号
         * @param objPointers 对象指针列表
         * @param selectedIndexes 选中索引列表
         */
        void sigTreeItemSelected(const std::vector<void*> objPointers, const QModelIndexList& selectedIndexes = QModelIndexList());
        
        /**
         * @brief 树模型数据改变信号
         * @param type 树视图类型
         * @param vModelData 模型数据列表
         */
        void sigTreeModelDataChanged(NctiTreeViewType type, const std::vector<NctiTreeModelData>& vModelData);

    private Q_SLOTS:
        /**
         * @brief 项点击槽函数
         * @param index 索引
         */
        void onItemClicked(const QModelIndex& index);
        
        /**
         * @brief 双击槽函数
         * @param index 索引
         */
        void onDoubleClicked(const QModelIndex& index);
        
        /**
         * @brief 树视图菜单请求槽函数
         * @param pos 位置点
         */
        void onTreeViewMenuRequested(const QPoint& pos);
        
        /**
         * @brief 选择改变槽函数
         * @param selected 选中项
         * @param deselected 取消选中项
         */
        void onSelectionChanged(const QItemSelection& selected, const QItemSelection& deselected);
        
        /**
         * @brief 检查并触发选择改变槽函数
         */
        void checkAndTriggerSelectionChange();

    private:
        /**
         * @brief 设置连接
         */
        void setupConnections();
        
        /**
         * @brief 获取树项
         * @param index 索引
         * @return 树项指针
         */
        NctiTreeItem* getTreeItem(const QModelIndex& index);
        
        /**
         * @brief 设置树视图属性
         */
        void setTreeViewProperty();
        
    private:
        QRect m_rect;                                    ///< 矩形区域
        QPainterPath m_path;                             ///< 绘制路径
        QPoint m_selectionStartPos;                      ///< 选择起始位置
        QTimer m_selectionTimer;                         ///< 选择定时器
        NctiTreeViewType m_type{ NctiTreeViewType::Normal };  ///< 树视图类型
        bool m_isRubberBandSelecting{ false };           ///< 框选状态
        bool m_isCtrlPressed{ false };                   ///< Ctrl键按下状态
        bool m_isShiftPressed{ false };                  ///< Shift键按下状态
    };

}