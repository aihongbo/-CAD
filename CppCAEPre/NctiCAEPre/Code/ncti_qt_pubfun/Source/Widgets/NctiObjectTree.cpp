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

#include "NctiObjectTree.h"

#include <QVBoxLayout>
#include <QPushButton>

#include "NctiTreeSideBar.h"
#include "NctiTreeSidePannel.h"
#include "NctiTreeViewDelegate.h"
#include "NctiDisplayObject.h"

#include <QDebug>
#include <QToolButton>
#include <iostream>

namespace NCTI
{
    enum View {
        ViewAssembleTree = 0,
        ViewObjTree,
        ViewSceneTree,
    };
    NctiObjectTree::NctiObjectTree(QWidget* p_parent)
        : QFrame(p_parent)
    {
        setupUI();
    }

    void NctiObjectTree::SetModelData(const std::vector<NctiTreeModelData>& vData, NctiTreeViewType type)
    {
        if (type == NctiTreeViewType::Assemble && mAssembleTreeView) {
            return mAssembleTreeView->update(vData);
        }
        if (type == NctiTreeViewType::Object && mObjTreeView) {
            return mObjTreeView->update(vData);
        }
#ifdef NCTI_SHOW_SCENE_VIEW
        if (type == NctiTreeViewType::Scene && mSceneTreeView) {
            return mSceneTreeView->update(vData);
        }
#endif // NCTI_SHOW_SCENE_VIEW
    }

    void NctiObjectTree::SelectItems(int index, const QStringList& objNames, bool bNotify)
    {
        NctiTreeModel* model = getTreeModel(index);
        if (!model) { return; }

        NctiTreeView* treeView = static_cast<NctiTreeView*>(mTreeSideBar->getWidget(index));
        QItemSelection selection;
        for (const auto& objName : objNames) {
            QModelIndex index = findModelIndexByName(model, objName);
            if (index.isValid()) {
                selection.select(index, index);
            }
        }

        treeView->selectionModel()->clear();

        if (selection.isEmpty() && bNotify) {
            treeView->getSelectedItems();
            return;
        }

        treeView->selectionModel()->select(selection, QItemSelectionModel::Select | QItemSelectionModel::Rows);
        if (!objNames.isEmpty()) {
            QModelIndex firstIndex = findModelIndexByName(model, objNames.first());
            if (firstIndex.isValid()) {
                treeView->scrollTo(firstIndex);
            }
		}
        if (bNotify) {
            treeView->getSelectedItems();
        }
    }

    void NctiObjectTree::showCurrentObjectTreeView()
    {
        if (mTreeSideBar) {
            int index = mTreeSideBar->getCurrentIndex();
            mTreeSideBar->setCurrentIndex(index);
            mTreeSidePanel->show();
            mTreeSidePanel->setCurrentIndex(index);
            Q_EMIT sigSidePanelVisible(index, true);
        }
    }

    NctiTreeViewType NctiObjectTree::currentTreeViewType() const
    {
        if (mTreeSideBar) {
            int index = mTreeSideBar->getCurrentIndex();
            if (index == 0) { return NctiTreeViewType::Assemble; }
            if (index == 1) { return NctiTreeViewType::Object; }
            if (index == 2) { return NctiTreeViewType::Scene; }
        }
        return NctiTreeViewType::Assemble;
    }

	void NctiObjectTree::ShowOrHideTreeSideBar(bool bShow)
	{
        if (mTreeSideBar) {
            if (bShow) {
                mTreeSideBar->show();
            } 
            else {
                mTreeSideBar->hide();
            }
        }
	}

	void NctiObjectTree::SetSideCurrentIndex(int index)
	{
        if (mTreeSideBar)
            mTreeSideBar->setCurrentIndex(index);
	}

    void NctiObjectTree::TraverseSetItemShowStyle(NctiTreeItem* item, const int style)
    {
        if (item == nullptr) {
            return;
        }
            
        auto& color = m_colors[style];
        if (color.isValid()) {
            item->setItemTextColor(color);
        }

        QList<NctiTreeItem*>& itemList = item->getChildList();
        for (auto it = itemList.begin(); it != itemList.end(); ++it) {
            if (*it) {
                TraverseSetItemShowStyle(*it, style);
            }
        }
    }
    
    bool NctiObjectTree::TraverseGetObjectItems(std::set<NctiTreeItem*>& outputItems, NctiTreeItem* item, std::set<NctiDisplayObject*>& objects)
    {
        if (item == nullptr) {
            return false;
        }

        QList<NctiTreeItem*>& itemList = item->getChildList();
        for (auto it = itemList.begin(); it != itemList.end(); ++it) {
            if (*it) {
                NctiDisplayObject* pObj = static_cast<NctiDisplayObject*>((*it)->getObject());
                if (objects.find(pObj) != objects.end()) {
                    outputItems.insert(*it);
                }
                TraverseGetObjectItems(outputItems , *it, objects);
            }
        }
        return true;
    }

    NctiTreeModel* NctiObjectTree::getTreeModel(int index)
    {
        if (mTreeSideBar) {
            NctiTreeView* treeView = static_cast<NctiTreeView*>(mTreeSideBar->getWidget(index));
            if (treeView && treeView->model()) {
                NctiTreeModel* model = qobject_cast<NctiTreeModel*>(treeView->model());
                return model;
            }
        }
        return nullptr;
    }

    NctiTreeItem* NctiObjectTree::GetItemByIndex(const int index, const QModelIndex& modelIndex)
    {
        NctiTreeModel* model = getTreeModel(index);
        if (model && modelIndex.isValid()) {
            return model->itemFromIndex(modelIndex);
        }
        return nullptr;
    }

    NctiTreeItem* NctiObjectTree::GetRootItem(const int index)
    {
        NctiTreeModel* model = getTreeModel(index);
        if (model) {
            return model->itemFromIndex(QModelIndex());
        }
        return nullptr;
    }

    QModelIndexList NctiObjectTree::GetIndexListByNames(const int index, const QStringList& objNames)
    {
        QModelIndexList indexList = QModelIndexList();
        NctiTreeModel* model = getTreeModel(index);
        if (model) {
            for (const auto& name : objNames) {
                QModelIndex itemIndex = findModelIndexByName(model, name);
                if (itemIndex.isValid()) {
                    indexList.append(itemIndex);
                }
            }
        }
        return indexList;
    }
    
	void NctiObjectTree::setupUI()
    {
        // 1. 创建水平布局
        auto hBoxLayout = new QHBoxLayout(this);
        hBoxLayout->setContentsMargins(0, 0, 0, 0);
        hBoxLayout->setSpacing(0);

        // 2. 创建侧边栏、分割线和侧边面板
        mTreeSideBar = new NctiTreeSideBar(this);
        mTreeSideBar->setObjectName("objTreeSidebar");
        mTreeSideBar->setContentsMargins(0, 0, 0, 0);
        mTreeSideBar->setFixedWidth(40);
        mTreeSideBar->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);

        QFrame* vSeparator = new QFrame(this);
        vSeparator->setFrameShape(QFrame::VLine);
        vSeparator->setFixedWidth(1);
        vSeparator->setObjectName(QStringLiteral("objTree_separator"));
        vSeparator->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);

        mTreeSidePanel = new NctiTreeSidePanel(this);
        mTreeSidePanel->setContentsMargins(0, 0, 0, 0);
        mTreeSidePanel->setObjectName("objTreeSidePanel");

        hBoxLayout->addWidget(mTreeSideBar);
        hBoxLayout->addWidget(vSeparator);
        hBoxLayout->addWidget(mTreeSidePanel);

        setLayout(hBoxLayout);
        mTreeSideBar->setSidePanel(mTreeSidePanel);

        // 3. 创建三种树视图
        mAssembleTreeView = createNctiTreeView(NctiTreeViewType::Assemble);
        mObjTreeView = createNctiTreeView(NctiTreeViewType::Object);
#ifdef NCTI_SHOW_SCENE_VIEW
		mSceneTreeView = createNctiTreeView(NctiTreeViewType::Scene);
#endif // NCTI_SHOW_SCENE_VIEW

        // 4. 添加侧边栏按钮并连接信号
        mTreeSideBar->addSideButton(QIcon(":/Tree/assemble.svg"), "sidebar_assemble", mAssembleTreeView, static_cast<int>(ViewAssembleTree));
        mTreeSideBar->addSideButton(QIcon(":/Tree/object.svg"), "sidebar_object", mObjTreeView, static_cast<int>(ViewObjTree));
#ifdef NCTI_SHOW_SCENE_VIEW
        mTreeSideBar->addSideButton(QIcon(":/Tree/scene.svg"), "sidebar_scene", mSceneTreeView, static_cast<int>(ViewSceneTree));
#endif // NCTI_SHOW_SCENE_VIEW
        
        connect(mTreeSideBar, &NctiTreeSideBar::sigButtonClicked, this, &NctiObjectTree::onSideButtonClicked);
        connect(mTreeSideBar, &NctiTreeSideBar::updateTreeModel, this, &NctiObjectTree::updateTreeModel);
        mTreeSideBar->setCurrentIndex(0);

        // 5. 初始化颜色映射
        InsertColorMap(0, 82, 85, 90);
        InsertColorMap(1, 162, 162, 162);
    }

    NctiTreeView* NctiObjectTree::createNctiTreeView(NctiTreeViewType type)
    {
        NctiTreeView* treeView = new NctiTreeView(this, type);
        treeView->setItemDelegate(new NctiTreeViewDelegate(treeView));
        
        if (type == NctiTreeViewType::Assemble) {
			connect(treeView, &NctiTreeView::sigItemClicked, this, &NctiObjectTree::sigTreeItemClicked);
			connect(treeView, &NctiTreeView::sigTreeItemSelected, this, &NctiObjectTree::sigTreeItemSelected);
            connect(treeView, &NctiTreeView::sigItemDoubleClicked, this, &NctiObjectTree::onItemDoubleClicked);
			connect(treeView, &NctiTreeView::sigTreeModelDataChanged, this, &NctiObjectTree::sigTreeModelDataChanged);
			connect(treeView, &NctiTreeView::sigContextMenuRequested, this, &NctiObjectTree::sigContextMenuRequested);
        }
        else if (type == NctiTreeViewType::Object) {
            connect(treeView, &NctiTreeView::sigItemClicked, this, &NctiObjectTree::sigTreeItemClicked);
            connect(treeView, &NctiTreeView::sigTreeItemSelected, this, &NctiObjectTree::sigTreeItemSelected);
            connect(treeView, &NctiTreeView::sigContextMenuRequested, this, &NctiObjectTree::sigContextMenuRequested);
            connect(treeView, &NctiTreeView::sigTreeModelDataChanged, this, &NctiObjectTree::sigTreeModelDataChanged);
		}
        else if (type == NctiTreeViewType::Scene) {
#ifdef NCTI_SHOW_SCENE_VIEW
            connect(treeView, &NctiTreeView::sigItemClicked, this, &NctiObjectTree::sigTreeItemClicked);
#endif // NCTI_SHOW_SCENE_VIEW
		}

        return treeView;
    }

    QModelIndex NctiObjectTree::findModelIndexByName(NctiTreeModel* model, 
        const QString& objName, const QModelIndex& parent)
    {
        for (int i = 0; i < model->rowCount(parent); ++i) {
            QModelIndex index = model->index(i, 0, parent);
            if (model->data(index, Qt::UserRole).toString() == objName) {
                return index;
            }
            QModelIndex childIndex = findModelIndexByName(model, objName, index);
            if (childIndex.isValid()) {
                return childIndex;
            }
        }
        return QModelIndex();
    }

    void NctiObjectTree::changeShowWidget(int index)
    {
        if (mTreeSidePanel && mTreeSidePanel->isVisible()) {
            if (index != mTreeSidePanel->currentIndex()) {
                mTreeSidePanel->setCurrentIndex(index);
            }
        }
    }

    void NctiObjectTree::onSideButtonClicked(QToolButton* clickedButton)
    {
        if (!clickedButton) { return; }
        bool checked = clickedButton->isChecked();
        int id = clickedButton->property("sidePanelId").toInt();
        int index = clickedButton->property("sidePanelIndex").toInt();
        bool otherBtnChecked = mTreeSideBar->uncheckOtherButtons(clickedButton);
        if (checked) {
            if (mTreeSidePanel) {
                mTreeSidePanel->setVisible(true);
                Q_EMIT sigSidePanelVisible(id, true);
            }
            changeShowWidget(index);
        }
        else {
            if (!otherBtnChecked && mTreeSidePanel) {
                mTreeSidePanel->setVisible(false);
                Q_EMIT sigSidePanelVisible(id, false);
            }
        }
    }
           
    void NctiObjectTree::onItemDoubleClicked(const QString& typeName, void* pObj)
    {
        int index = mTreeSideBar->getCurrentIndex();
        if (index != 0 || typeName != "doc_part") {
            //只处理装配树的零件对象的双击事件
            return;
        }
        mTreeSideBar->setCurrentIndex(1);
    }
    
    void NctiObjectTree::InsertColorMap(const int index, const int r, const int g, const int b)
    {
        QColor color(r,g,b);
        std::pair<int, QColor> pairColor(index, color);
        m_colors.insert(pairColor);
    }

    void NctiObjectTree::onResetTargetObjectTreeItem(const QString& objName)
    {
        QStringList nameList = QStringList();
        nameList.append(objName);
        QModelIndexList modelIndexList = GetIndexListByNames(1, nameList);
        for (const QModelIndex& modelIndex : modelIndexList) {
            NctiTreeItem* item = GetItemByIndex(1, modelIndex);
            if (item) {
                TraverseSetItemShowStyle(item, 0);
            }
        }
    }
}

