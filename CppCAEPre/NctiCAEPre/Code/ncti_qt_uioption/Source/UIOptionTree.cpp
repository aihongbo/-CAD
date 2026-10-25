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

#include <QtGlobal>

#if (QT_VERSION >= QT_VERSION_CHECK(6, 0, 0))
#define DROPEVENT_POS_POINT(DropEventPtr) DropEventPtr->position().toPoint()
#else
#define DROPEVENT_POS_POINT(DropEventPtr) DropEventPtr->pos()
#endif

#include "UIOptionTree.h"
#include "UIOptionItemModel.h"
#include "UIOptionMimeData.h"
#include "UIOption.h"

#include "AddUIActionDialog.h"

#include <QDebug>
#include <QMenu>
#include <QMimeData>
#include <QDragEnterEvent>
#include <QDrag>
#include <QModelIndex>
#include <QInputDialog>
#include <QScopeGuard>

namespace {
bool validateNodeName(const QString& name)
{
    return !name.isEmpty() && !name.contains(QRegularExpression("[\\/\\\\:*?\"<>|]"));
}
} // namespace

namespace NCTI {

// 层级规则映射表
static QHash<UINodeType, QVector<UINodeType>> AllowedChildTypes
    = {{NTRoot, {NTPage}},
       {NTPage, {NTPage, NTPanel}},
       {NTPanel, {NTPanel, NTAction, NTGroup, NTActionGroup}},
       {NTAction, {NTAction, NTGroup, NTActionGroup}},
       {NTGroup, {NTGroup, NTAction, NTActionGroup}},
       {NTActionGroup, {NTActionGroup, NTAction, NTGroup}}};

UIOptionTree::UIOptionTree(QWidget* parent, bool useDefault)
    : QTreeView(parent)
    , mUseDefault(useDefault)
{
    initTree();

    if (!mUseDefault) { initContextMenu(); }

    mModel = new UIOptionItemModel(this);
    setModel(mModel);

    // add the invisible extra item at the end
    if (mModel->insertRows(mModel->rowCount(), 1)) { mExtraItem = mModel->index(mModel->rowCount() - 1, 0); }

    initConnections();
}

UIOptionTree::~UIOptionTree()
{
}

void UIOptionTree::loadLocalModel(bool bReload)
{
    if (bReload) { mModel->clearModel(); }

    UIOptionType type = mUseDefault ? UIOptionType::Default : UIOptionType::User;
    for (auto& detail : UIOption::GetInst().GetTabs(type)) {
        QModelIndex pageIndex = mModel->addUIPage(detail.index, detail.name, detail.object_name);
        mModel->addUIPanels(pageIndex, detail.object_name, mUseDefault);
    }
    mModel->sort(QModelIndex());
}

bool UIOptionTree::updateLocalModel(const QString& iconPath, const QString& appTitle)
{
    UIRibbon uiRibbon;
    uiRibbon.logo    = std::string(iconPath.toUtf8());
    uiRibbon.title   = std::string(appTitle.toUtf8());
    uiRibbon.version = std::string(UIOption::GetInst().GetVersion().toUtf8());
    std::unordered_map<std::string, UIPage> uiPages;
    for (int i = 0; i < mModel->rowCount(); ++i) {
        QModelIndex pageIndex = mModel->index(i, 0);
        if (!mModel->sameNodeType(pageIndex, NTPage)) { continue; }

        // 获取Page节点数据
        UITabDetail tabDetail;
        tabDetail.index       = mModel->data(pageIndex, UINodeIndexRole).toInt();
        tabDetail.name        = std::string(mModel->data(pageIndex, Qt::DisplayRole).toString().toUtf8());
        tabDetail.object_name = std::string(mModel->data(pageIndex, UINodeObjNameRole).toString().toUtf8());
        uiRibbon.tabs.push_back(tabDetail);

        UIPage uiPage;
        uiPage.object_name = tabDetail.object_name;
        for (int j = 0; j < mModel->rowCount(pageIndex); ++j) {
            QModelIndex panelIndex = mModel->index(j, 0, pageIndex);
            // 获取Panel节点数据
            if (mModel->sameNodeType(panelIndex, NTPanel)) { uiPage.panels.push_back(getPanelData(panelIndex)); }
        }
        uiPages.emplace(uiPage.object_name, uiPage);
    }

    UIOption::GetInst().SaveUIOption(uiRibbon);
    UIOption::GetInst().SaveUIPages(uiPages);
    return true;
}

QMimeData* UIOptionTree::dragObject()
{
    UIOptionMimeData::ItemList itemList;
    for (auto const& index : selectedIndexes()) {
        if (!index.isValid()) { break; }
        UIOptionItem* item = static_cast<UIOptionItem*>(index.internalPointer());
        if (item) { itemList.append(item); }
    }
    return new UIOptionMimeData(std::move(itemList));
}

void UIOptionTree::dragEnterEvent(QDragEnterEvent* event)
{
    if (event->mimeData()->hasFormat(UIOptionMimeData::mimeType())) {
        event->acceptProposedAction();
        setState(DraggingState);
    }
    else {
        QAbstractItemView::dragEnterEvent(event);
    }
}

void UIOptionTree::dragMoveEvent(QDragMoveEvent* event)
{
    // Do this first, otherwise the event may be ignored:
    QTreeView::dragMoveEvent(event);

    event->acceptProposedAction();
    event->accept();

    viewport()->update();
}

void UIOptionTree::dropEvent(QDropEvent* event)
{
    auto const connection
        = connect(this, &UIOptionTree::collapsed, [this](QModelIndex const& index) { expand(index); });
    auto cleanup = qScopeGuard([&connection]() noexcept {
        disconnect(connection); // 作用域结束时断开连接
    });

    auto const pos           = DROPEVENT_POS_POINT(event);
    auto const dstIndex      = indexAt(pos);
    const UINodeType dstType = mModel->getNodeType(dstIndex);
    if (event->source() != this) {
        // 拖放源不是当前视图（例如从其他组件拖入的数据）
        UIOptionMimeData const* const mdata = dynamic_cast<UIOptionMimeData const*>(event->mimeData());
        if (!mdata || mdata->itemList().isEmpty()) {
            event->ignore();
            return;
        }

        QModelIndex parentIndex;
        int rowUnderParent   = -1;
        int indexUnderParent = -1;

        UIOptionItem* item = mdata->itemList().first();
        if (!item) {
            event->ignore();
            return;
        }

        const UINodeType srcType = item->type();
        if (!AllowedChildTypes[dstType].contains(srcType)) {
            qWarning() << "Not allowed type (" << srcType << ") to (" << dstType << ")";
            event->ignore();
            return;
        }

        if (!dstIndex.isValid()) {
            //  Drop on root
            parentIndex      = dstIndex;
            rowUnderParent   = mModel->rowCount();
            indexUnderParent = mModel->getMaxIndex(QModelIndex()) + 1;
        }
        else {
            auto dstParentNodeType = static_cast<UINodeType>(dstIndex.parent().data(UINodeTypeRole).toInt());
            if (item->parent()->type() == dstParentNodeType) {
                // 父节点类型相同
                parentIndex      = dstIndex.parent();
                rowUnderParent   = dstIndex.row();
                indexUnderParent = dstIndex.data(UINodeIndexRole).toInt();
                QRect const rect = visualRect(dstIndex);
                if (pos.y() > rect.bottom() - rect.height() / 2) {
                    rowUnderParent++;
                    indexUnderParent++;
                }
                mModel->updateItemIndex(parentIndex, indexUnderParent);
            }
            else {
                parentIndex      = dstIndex;
                rowUnderParent   = mModel->rowCount();
                indexUnderParent = mModel->getMaxIndex(dstIndex) + 1;
            }
        }
        qDebug() << "Dropping item at row: " << rowUnderParent << ",index: " << indexUnderParent;

        if (rowUnderParent < 0 || indexUnderParent < 0) {
            event->ignore();
            return;
        }
        mModel->insertItem(parentIndex, rowUnderParent, item, indexUnderParent);
    }
    else {
        // 拖放源是当前视图（内部拖放）
        event->accept();

        const QModelIndexList selected = selectedIndexes();
        if (selected.isEmpty()) {
            event->ignore();
            return;
        }

        QModelIndex parentIndex;
        int rowUnderParent   = 0;
        int indexUnderParent = 0;

        // 规则1. 不能拖放到自己
        // 规则2. 不能拖放到自己的子节点
        // 规则3. 父节点相同的同级节点进行排序操作
        // 规则4. 父节点不同的同级节点进行复制再排序操作
        if (!dstIndex.isValid()) {
            qWarning() << "dstIndex is invalid";
            event->ignore();
            return;
        }

        const UINodeType dstType = mModel->getNodeType(dstIndex);
        for (auto const& srcIndex : selected) {
            const UINodeType srcType = static_cast<UINodeType>(srcIndex.data(UINodeTypeRole).toInt());
            if (!AllowedChildTypes[dstType].contains(srcType) || srcIndex.parent() == dstIndex) {
                // 不允许的类型，跳过
                qWarning() << "Not allowed type (" << srcType << ") to (" << dstType << ")";
                event->ignore();
                return;
            }

            if (srcIndex.parent() == dstIndex.parent()) {
                // 父节点相同，排序
                parentIndex      = dstIndex.parent();
                indexUnderParent = dstIndex.data(UINodeIndexRole).toInt(); // before the current item

                qDebug() << "Same Parent, "
                         << "Target objName : " << dstIndex.data(UINodeObjNameRole).toString()
                         << "item index: " << indexUnderParent;

                QRect const rect = visualRect(dstIndex);
                if (pos.y() > rect.bottom() - rect.height() / 2) {
                    indexUnderParent++; // after the current item
                }

                mModel->updateItemIndex(parentIndex, indexUnderParent);

                UIOptionItem* srcItem = mModel->getItem(srcIndex);
                srcItem->setIndex(indexUnderParent);
                mModel->sort(parentIndex);
            }
            else {
                // 父节点不相同，排序
                if (srcType != dstType) {
                    parentIndex      = dstIndex; // Panel节点作为父节点
                    indexUnderParent = mModel->getMaxIndex(dstIndex) + 1;
                    rowUnderParent   = mModel->rowCount(dstIndex); // 默认插入到Panel末尾
                }
                else {
                    parentIndex      = dstIndex.parent();
                    rowUnderParent   = dstIndex.row();
                    indexUnderParent = dstIndex.data(UINodeIndexRole).toInt();
                    QRect const rect = visualRect(dstIndex);
                    if (pos.y() > rect.bottom() - rect.height() / 2) {
                        rowUnderParent++;
                        indexUnderParent++;
                    }
                }
                qDebug() << "Different Parent, "
                         << "Target objName : " << dstIndex.data(UINodeObjNameRole).toString()
                         << "item row: " << rowUnderParent << "item index: " << indexUnderParent;
                mModel->updateItemIndex(parentIndex, indexUnderParent);
                mModel->insertItem(parentIndex, rowUnderParent, srcIndex, indexUnderParent);
            }
        }
        scrollTo(parentIndex); // 滚动到目标位置
        expand(parentIndex);   // 展开父节点显示新内容
    }

    // 最终状态：拖放结束，重置视图状态
    setState(QAbstractItemView::NoState);
}

void UIOptionTree::dragLeaveEvent(QDragLeaveEvent* event)
{
    setState(QAbstractItemView::NoState); // Not dragging anymore
    viewport()->update();                 // Clear the arrow
}

void UIOptionTree::startDrag(Qt::DropActions supportedActions)
{
    Q_UNUSED(supportedActions);
    QMimeData* const mimeData = dragObject();
    QDrag* const drag         = new QDrag{this};
    drag->setMimeData(mimeData);
    drag->exec();
}

UIPanel UIOptionTree::getPanelData(const QModelIndex& panelIndex)
{
    int itemIndex = mModel->data(panelIndex, UINodeIndexRole).toInt();

    QVariant dataVar = mModel->data(panelIndex, UINodeDataRole);
    if (!dataVar.canConvert<UINodeData>()) {
        qWarning() << "get UINodeData of Panel Failed.";
        return UIPanel();
    }

    UINodeData nodeData = dataVar.value<UINodeData>();
    UIPanel panel{itemIndex, nodeData.name, nodeData.object_name};

    for (int k = 0; k < mModel->rowCount(panelIndex); ++k) {
        QModelIndex childIndex = mModel->index(k, 0, panelIndex);
        if (!childIndex.isValid()) { continue; }

        int itemIndex    = mModel->data(childIndex, UINodeIndexRole).toInt();
        QVariant dataVar = mModel->data(childIndex, UINodeDataRole);
        if (!dataVar.canConvert<UINodeData>()) { qWarning() << "get UINodeData Failed."; }

        UINodeData data = dataVar.value<UINodeData>();
        if (mModel->sameNodeType(childIndex, NTAction)) {
            UIAction action{itemIndex,
                            data.name,
                            data.object_name,
                            data.icon_path,
                            data.slot_name,
                            data.short_cut,
                            data.width,
                            data.pyscript};

            for (int ix = 0; ix < mModel->rowCount(childIndex); ++ix) {
                QModelIndex childItemIndex = mModel->index(ix, 0, childIndex);
                if (childItemIndex.isValid()) {
                    int itemIndex     = mModel->data(childItemIndex, UINodeIndexRole).toInt();
                    QVariant itemData = mModel->data(childItemIndex, UINodeDataRole);
                    if (itemData.canConvert<UINodeData>()) {
                        UINodeData data = itemData.value<UINodeData>();
                        UIAction childItem{itemIndex,
                                           data.name,
                                           data.object_name,
                                           data.icon_path,
                                           data.slot_name,
                                           data.short_cut,
                                           data.width,
                                           data.pyscript};
                        action.vChild.push_back(childItem);
                    }
                }
            }
            panel.actions.push_back(action);
        }
        else if (mModel->sameNodeType(childIndex, NTGroup)) {
            UIGroup group{itemIndex, data.name, data.object_name};

            for (int ix = 0; ix < mModel->rowCount(childIndex); ++ix) {
                QModelIndex childItemIndex = mModel->index(ix, 0, childIndex);
                if (childItemIndex.isValid()) {
                    QVariant itemData = mModel->data(childItemIndex, UINodeDataRole);
                    if (itemData.canConvert<UINodeData>()) {
                        UINodeData data = itemData.value<UINodeData>();
                        UIGroupItem childItem{data.name, data.object_name, data.icon_path, data.slot_name};
                        group.vChild.push_back(childItem);
                    }
                }
            }

            panel.groups.push_back(group);
        }
        else if (mModel->sameNodeType(childIndex, NTActionGroup)) {
            UIActionGroup actionGroup{itemIndex,
                                      data.row,
                                      data.column,
                                      data.frame_object_name,
                                      data.name,
                                      data.object_name,
                                      data.icon_path,
                                      data.group_type};

            for (int ix = 0; ix < mModel->rowCount(childIndex); ++ix) {
                QModelIndex childItemIndex = mModel->index(ix, 0, childIndex);
                if (childItemIndex.isValid()) {
                    QVariant itemData = mModel->data(childItemIndex, UINodeDataRole);
                    if (itemData.canConvert<UINodeData>()) {
                        UINodeData data = itemData.value<UINodeData>();
                        UIActionGroupItem childItem{data.row, data.column, data.name, data.object_name, data.slot_name};
                        actionGroup.vChild.push_back(childItem);
                    }
                }
            }

            panel.action_groups.push_back(actionGroup);
        }
    }
    return panel;
}

void UIOptionTree::initTree()
{
    // TreeView属性设置
    setHeaderHidden(true);

    // 拖拽属性设置
    setDragEnabled(true);
    setAcceptDrops(true);
    setDragDropMode(QAbstractItemView::DragDrop);
    viewport()->setAcceptDrops(true);
    setSelectionMode(QAbstractItemView::SingleSelection);

    // 禁用双击编辑
    setEditTriggers(editTriggers() ^ QAbstractItemView::DoubleClicked);

    if (!mUseDefault) { setContextMenuPolicy(Qt::CustomContextMenu); }

    // 设置委托
    //setItemDelegate(new UIOptionItemDelegate(this));
}

void UIOptionTree::initContextMenu()
{
    mContextMenu = new QMenu(viewport());

    auto const addMenuAction
        = [this](MenuAction const menuAction, QString const& text, QIcon const& icon, auto&& slot) {
              auto* const action = new QAction(icon, text, this);
              connect(action, &QAction::triggered, std::forward<decltype(slot)>(slot));
              mActions[menuAction] = action;
              mContextMenu->addAction(action);
          };

    addMenuAction(MenuAction::New, "创建", QIcon(":/uioption/menu/add.svg"), [this] {
        if (!selectedIndexes().empty()) {
            if (mModel->sameNodeType(currentIndex(), NTPage)) {
                // 创建Panel节点
                setCurrentIndex(mModel->newUIPanel(mModel->rowCount(currentIndex()), currentIndex()));
            }
            else if (mModel->sameNodeType(currentIndex(), NTPanel)) {
                // 创建Panel子节点
                showCreatePanelItemDlg(currentIndex());
            }
        }
        else {
            // 创建分类节点
            setCurrentIndex(mModel->newUIPage());
        }
    });

    addMenuAction(MenuAction::Rename, "重命名", QIcon(":/uioption/menu/rename.svg"), [this] { edit(currentIndex()); });

    addMenuAction(MenuAction::Edit, "编辑", QIcon(":/uioption/menu/edit.svg"), [this] { showEditDlg(currentIndex()); });

    addMenuAction(MenuAction::Delete, "删除", QIcon(":/uioption/menu/delete.svg"), [this] { deleteItems(); });
}

void UIOptionTree::initConnections()
{
    connect(this, &QTreeView::customContextMenuRequested, this, &UIOptionTree::onCustomContextMenuRequested);
}

void UIOptionTree::onCustomContextMenuRequested(const QPoint& pos)
{
    // 获取当前索引
    QModelIndex index = indexAt(pos);
    QModelIndexList const items(selectedIndexes());
    if (items.isEmpty()) {
        // handling for no selection:
        for (int i = ActionBegin; i < ActionEnd; ++i) {
            mActions[i]->setEnabled(i == New);
        }
    }
    else if (items.size() == 1) {
        // handling for one selected item :
        for (int i = ActionBegin; i < ActionEnd; ++i) {
            mActions[i]->setEnabled(enableAction(items.at(0), static_cast<MenuAction>(i)));
        }
    }
    else if (!index.isValid()) {
        // Disable all actions for invalid index:
        for (int index = ActionBegin; index < ActionEnd; ++index) {
            mActions[index]->setEnabled(false);
        }
    }
    else {
        // 暂不处理多选的情况
    }

    mContextMenu->exec(viewport()->mapToGlobal(pos));
}

void UIOptionTree::showEditDlg(const QModelIndex& index)
{
    if (!index.isValid()) { return; }

    if (!mModel->sameNodeType(currentIndex(), NTAction)) { return; }

    UIOptionItem* item = static_cast<UIOptionItem*>(index.internalPointer());
    if (!item) { return; }

    // TODO, 编辑节点
    UINodeData nodeData    = item->nodeData();
    AddUIActionDialog* dlg = new AddUIActionDialog(this, QStringLiteral("添加动作"));
    dlg->setData(UIActionData{
        QString::fromUtf8(nodeData.icon_path.c_str()),
        QString::fromUtf8(nodeData.name.c_str()),
        QString::fromUtf8(nodeData.slot_name.c_str()),
        QString::fromUtf8(nodeData.pyscript.c_str()),
    });
    dlg->setFixedSize(500, 420);
    dlg->exec();
    if (0 == dlg->GetStatus()) { return; }

    UIActionData data = dlg->getData();
    item->setIconPath(data.iconPath);
    item->setText(data.actionName);

    nodeData.name        = std::string(data.actionName.toUtf8());
    nodeData.icon_path   = std::string(data.iconPath.toUtf8());
    nodeData.slot_name   = std::string(data.slotName.toUtf8());
    nodeData.object_name = std::string(mModel->getObjectName(NTAction).toUtf8());
    nodeData.pyscript    = std::string(data.pyScript.toUtf8());

    model()->setData(index, QVariant::fromValue(nodeData), UINodeDataRole);
}

void UIOptionTree::showCreatePanelItemDlg(const QModelIndex& index)
{
    if (!index.isValid()) { return; }

    UIOptionItem* parentItem = static_cast<UIOptionItem*>(index.internalPointer());
    if (!parentItem) { return; }

    // TODO, 创建Panel子节点
    AddUIActionDialog* dlg = new AddUIActionDialog(this, QStringLiteral("添加动作"));
    dlg->setFixedSize(500, 420);
    dlg->exec();
    if (0 == dlg->GetStatus()) { return; }
    UIActionData data = dlg->getData();

    int row       = mModel->rowCount(index);
    int itemIndex = mModel->getMaxIndex(index) + 1;

    UIOptionItem* newItem = new UIOptionItem();
    newItem->setType(NTAction);
    newItem->setIconPath(data.iconPath);
    newItem->setText(data.actionName);
    newItem->setIndex(itemIndex);

    UINodeData nodeData;
    nodeData.index       = itemIndex;
    nodeData.name        = std::string(data.actionName.toUtf8());
    nodeData.icon_path   = std::string(data.iconPath.toUtf8());
    nodeData.slot_name   = std::string(data.slotName.toUtf8());
    nodeData.object_name = std::string(mModel->getObjectName(NTAction).toUtf8());
    nodeData.pyscript    = std::string(data.pyScript.toUtf8());
    newItem->setNodeData(nodeData);

    mModel->insertChildItem(index, row, newItem, itemIndex);
}

void UIOptionTree::deleteItems()
{
    QList<QPersistentModelIndex> list;
    for (auto const& i : selectedIndexes()) {
        list.append(i);
    }

    for (auto const& i : list) {
        mModel->removeRows(i.row(), 1, i.parent());
    }
}

bool UIOptionTree::enableAction(QModelIndex const& index, MenuAction const type) const
{
    switch (type) {
        case New: return mModel->isContainerNode(index);
        case Rename: return mModel->isRenameable(index);
        case Edit: return mModel->isEditable(index);
        case Delete: return true;
        default: break;
    }
    return false;
}

} // namespace NCTI
