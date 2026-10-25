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

#ifndef NCTI_OBJECT_TREE_H
#define NCTI_OBJECT_TREE_H

#include "dcl_ncti_qt_pubfun.h"
#include <QFrame>
#include <QToolButton>
#include <QSharedPointer>
#include <QScopedPointer>
#include <set>

class QPushButton;

#include "NctiTreeModel.h"
#include "NctiTreeView.h"

namespace NCTI
{
    class NctiTreeView;
    class NctiTreeSideBar;
    class NctiTreeSidePanel;
    class NctiDisplayObject;
    
    /**
     * @brief 对象树类
     * @details 用于显示对象层次结构的树形控件，支持装配树、对象树和场景树等多种视图
     */
    class DECL_NCTI_QT_PUBFUN NctiObjectTree : public QFrame
    {
        Q_OBJECT
    public:
        /**
         * @brief 构造函数
         * @param p_parent 父窗口指针
         */
        NctiObjectTree(QWidget *p_parent = nullptr);
        
        /**
         * @brief 设置模型数据
         * @param vData 模型数据列表
         * @param type 树视图类型
         */
        void SetModelData(const std::vector<NctiTreeModelData>& vData, NctiTreeViewType type);

        /**
         * @brief 获取树模型
         * @param index 索引
         */
        NctiTreeModel* getTreeModel(int index);
        
        /**
         * @brief 选择项
         * @param index 索引
         * @param objNames 对象名称列表
         * @param bNotify 是否通知
         */
        void SelectItems(int index, const QStringList& objNames, bool bNotify = true);

        /**
         * @brief 显示当前对象树的视图
         */
        void showCurrentObjectTreeView();
        
        /**
         * @brief 获取当前树视图类型
         * @return 当前树视图类型
         */
        NctiTreeViewType currentTreeViewType() const;
        
        /**
         * @brief 显示或隐藏树侧边栏
         * @param bShow 是否显示
         */
        void ShowOrHideTreeSideBar(bool bShow);
        
        /**
         * @brief 设置侧边栏当前索引
         * @param index 索引
         */
        void SetSideCurrentIndex(int index);
        
        /**
         * @brief 遍历设置项显示样式
         * @param item 树项指针
         * @param style 样式
         */
        void TraverseSetItemShowStyle(NctiTreeItem* item, const int style);

        /**
         * @brief 通过遍历找到指定的实体对象对应的树项
         * @param 输出的节点集合
         * @param 树的root指针
         * @param 实体集合
         * @return 是否成功
         */
        bool TraverseGetObjectItems(std::set<NctiTreeItem*>&, NctiTreeItem*, std::set<NctiDisplayObject*>&);
        
        /**
         * @brief 根据索引获取项
         * @param index 树类型，1:object
         * @param modelIndex Qt返回的选中值
         * @return 树项指针
         */
        NctiTreeItem* GetItemByIndex(const int index, const QModelIndex& modelIndex);

        /**
         * @brief 根据索引获取树根节点
         * @param index 树类型，1:object
         * @return 树项指针
         */
        NctiTreeItem* GetRootItem(const int index);

        /**
         * @brief 根据名称获取索引列表
         * @param index 索引
         * @param objNames 对象名称列表
         * @return 索引列表
         */
        QModelIndexList GetIndexListByNames(const int index, const QStringList& objNames);
        
    public Q_SLOTS:
        /**
         * @brief 重置目标对象树项槽函数
         * @param objName 对象名称
         */
        void onResetTargetObjectTreeItem(const QString& objName);
        
    Q_SIGNALS:
        /**
         * @brief 树项点击信号
         * @param ojbName 对象名称
         * @param pObj 对象指针
         */
        void sigTreeItemClicked(const QString& ojbName, void* pObj);
        
        /**
         * @brief 上下文菜单请求信号
         * @param ojbName 对象名称
         * @param pObj 对象指针
         */
        void sigContextMenuRequested(const QString& ojbName, void* pObj);
        
        /**
         * @brief 树项选择信号
         * @param vObj 对象指针列表
         * @param selectedIndexes 选中索引列表
         */
        void sigTreeItemSelected(const std::vector<void*> vObj, const QModelIndexList& selectedIndexes = QModelIndexList());
        
        /**
         * @brief 侧边栏可见性信号
         * @param index 索引
         * @param visible 是否可见
         */
        void sigSidePanelVisible(int index, bool visible);
        
        /**
         * @brief 树模型数据改变信号
         * @param type 树视图类型
         * @param vModelData 模型数据列表
         */
        void sigTreeModelDataChanged(NctiTreeViewType type, const std::vector<NctiTreeModelData>& vModelData);
        
        /**
         * @brief 更新树模型信号
         */
        void updateTreeModel();
        
    private:
        /**
         * @brief 设置界面
         */
        void setupUI();
        
        /**
         * @brief 创建NCTI树视图
         * @param type 树视图类型
         * @return 树视图指针
         */
        NctiTreeView* createNctiTreeView(NctiTreeViewType type);
        
        /**
         * @brief 根据名称查找模型索引
         * @param model 模型指针
         * @param objName 对象名称
         * @param parent 父索引
         * @return 模型索引
         */
        QModelIndex findModelIndexByName(NctiTreeModel* model, const QString& objName, 
            const QModelIndex& parent = QModelIndex());
        
        /**
         * @brief 切换显示控件
         * @param index 索引
         */
        void changeShowWidget(int index);
        
        /**
         * @brief 侧边按钮点击槽函数
         * @param clickedButton 点击的按钮指针
         */
        void onSideButtonClicked(QToolButton* clickedButton);
        
        /**
         * @brief 项双击槽函数
         * @param typeName 类型名称
         * @param pObj 对象指针
         */
        void onItemDoubleClicked(const QString& typeName, void* pObj);
        
        /**
         * @brief 插入颜色映射
         * @param index 索引
         * @param r 红色分量
         * @param g 绿色分量
         * @param b 蓝色分量
         */
        void InsertColorMap(const int index, const int r, const int g, const int b);
        
    private:
        NctiTreeView* mAssembleTreeView{ nullptr };    ///< 装配树视图指针
        NctiTreeView* mObjTreeView{ nullptr };         ///< 对象树视图指针
        NctiTreeView* mSceneTreeView{ nullptr };       ///< 场景树视图指针
        NctiTreeSideBar* mTreeSideBar{ nullptr };      ///< 树侧边栏指针
        NctiTreeSidePanel* mTreeSidePanel{ nullptr };  ///< 树侧边面板指针
        std::map<int, QColor> m_colors;                ///< 颜色映射
    };
}

#endif // NCTI_OBJECT_TREE_H