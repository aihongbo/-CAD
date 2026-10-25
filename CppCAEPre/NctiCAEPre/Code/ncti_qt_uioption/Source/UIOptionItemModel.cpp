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

#include "UIOptionItemModel.h"

#include "UIOption.h"
#include <QRandomGenerator>
#include <QVariant>

namespace NCTI {
UIOptionItem::UIOptionItem(UIOptionItem* parent)
    : mParentItem(parent)
{
}

UIOptionItem::UIOptionItem(const UIOptionItem& other)
    : mParentItem(other.mParentItem)
    , mText(other.mText)
    , mType(other.mType)
    , mIconPath(other.mIconPath)
    , mObjName(other.mObjName)
    , mNodeData(other.mNodeData)
{
}

UIOptionItem::UIOptionItem(UINodeType type, const int row, const UINodeData& data)
    : mType(type)
    , mIndex(row)
{
    mText           = QString::fromUtf8(data.name.c_str());
    mObjName        = QString::fromUtf8(data.object_name.c_str());
    mIconPath       = QString::fromUtf8(data.icon_path.c_str());
    mNodeData       = data;
    mNodeData.index = row;
}

UIOptionItemModel::UIOptionItemModel(QObject* parent)
    : QAbstractItemModel(parent)
    , mRootItem(new UIOptionItem())
{
    mRootItem->setType(UINodeType::NTRoot);
}

UIOptionItemModel::~UIOptionItemModel()
{
    delete mRootItem;
}

QModelIndex UIOptionItemModel::addUIPage(int index, const std::string& name, const std::string& object_name)
{
    UIOptionItem* item = new UIOptionItem(mRootItem);
    item->setType(UINodeType::NTPage);
    item->setIndex(index);
    item->setText(QString::fromUtf8(name.c_str()));
    item->setObjectName(QString::fromUtf8(object_name.c_str()));

    int row = mRootItem->childCount();
    beginInsertRows(QModelIndex(), row, row);
    mRootItem->appendChild(item);
    endInsertRows();
    return createIndex(row, 0, item);
}

void UIOptionItemModel::addUIPanels(QModelIndex pageIndex, const std::string& object_name, bool bDefault)
{
    UIPage uiPage = UIOption::GetInst().LoadUIPage(object_name, bDefault);

    for (const auto& panel : uiPage.panels) {
        // 添加panel节点
        QModelIndex panelIndex = addUINode(pageIndex, UINodeType::NTPanel, panel.index, panel.name, panel.object_name);

        // 添加action节点
        for (const auto& action : panel.actions) {
            addUINode(panelIndex, action);
        }

        // 添加group节点
        for (const auto& group : panel.groups) {
            addUINode(panelIndex, group);
        }

        // 添加actionGroup节点
        for (const auto& actionGroup : panel.action_groups) {
            addUINode(panelIndex, actionGroup);
        }
    }
}

void UIOptionItemModel::addUINode(const QModelIndex& parent, const UIAction& action)
{
    UIOptionItem* parentItem = getItem(parent);
    if (!parentItem) { return; }

    UIOptionItem* item = new UIOptionItem(parentItem);
    item->setIndex(action.index);
    item->setType(UINodeType::NTAction);
    item->setText(QString::fromUtf8(action.name.c_str()));
    item->setObjectName(QString::fromUtf8(action.object_name.c_str()));

    UINodeData nodeData;
    nodeData.index       = action.index;
    nodeData.width       = action.width;
    nodeData.name        = action.name;
    nodeData.icon_path   = action.icon_path;
    nodeData.object_name = action.object_name;
    nodeData.short_cut   = action.short_cut;
    nodeData.slot_name   = action.slot_name;
    nodeData.pyscript    = action.pystring;
    item->setNodeData(nodeData);

    int row = parentItem->childCount();
    beginInsertRows(parent, row, row);
    parentItem->appendChild(item);
    endInsertRows();

    if (!action.vChild.empty()) {
        QModelIndex currentIndex = index(row, 0, parent);
        for (const auto& childAction : action.vChild) {
            addUINode(currentIndex, childAction);
        }
    }
}

void UIOptionItemModel::addUINode(const QModelIndex& parent, const UIGroup& group)
{
    UIOptionItem* parentItem = getItem(parent);
    if (!parentItem) { return; }

    QString objName = getObjectName(UINodeType::NTGroup, group.object_name);
    QString name    = group.name.empty() ? objName : QString::fromUtf8(group.name.c_str());

    UIOptionItem* item = new UIOptionItem(parentItem);
    item->setIndex(group.index);
    item->setType(UINodeType::NTGroup);
    item->setText(name);
    item->setObjectName(objName);

    UINodeData nodeData;
    nodeData.index       = group.index;
    nodeData.name        = std::string(name.toUtf8());
    nodeData.object_name = std::string(objName.toUtf8());
    item->setNodeData(nodeData);

    int row = parentItem->childCount();
    beginInsertRows(parent, row, row);
    parentItem->appendChild(item);
    endInsertRows();

    if (!group.vChild.empty()) {
        QModelIndex currentIndex = index(row, 0, parent);
        for (const auto& childGroup : group.vChild) {
            addUINode(currentIndex, childGroup);
        }
    }
}

void UIOptionItemModel::addUINode(const QModelIndex& parent, const UIGroupItem& groupItem)
{
    UIOptionItem* parentItem = getItem(parent);
    if (!parentItem) { return; }

    std::string name   = groupItem.name.empty() ? groupItem.object_name : groupItem.name;
    UIOptionItem* item = new UIOptionItem(parentItem);
    item->setType(UINodeType::NTGroupItem);
    item->setText(QString::fromUtf8(name.c_str()));
    item->setObjectName(QString::fromUtf8(groupItem.object_name.c_str()));

    std::string object_name = std::string(getObjectName(UINodeType::NTGroupItem).toUtf8());
    UINodeData nodeData;
    nodeData.name        = groupItem.name.empty() ? object_name : groupItem.name;
    nodeData.object_name = groupItem.object_name.empty() ? object_name : groupItem.object_name;
    nodeData.icon_path   = groupItem.icon_path;
    nodeData.slot_name   = groupItem.slot_name;
    item->setNodeData(nodeData);

    int row = parentItem->childCount();
    beginInsertRows(parent, row, row);
    parentItem->appendChild(item);
    endInsertRows();
}

void UIOptionItemModel::addUINode(const QModelIndex& parent, const UIActionGroup& actionGroup)
{
    UIOptionItem* parentItem = getItem(parent);
    if (!parentItem) { return; }

    UIOptionItem* item = new UIOptionItem(parentItem);
    item->setIndex(actionGroup.index);
    item->setType(UINodeType::NTActionGroup);
    item->setText(QString::fromUtf8(actionGroup.name.c_str()));
    item->setObjectName(QString::fromUtf8(actionGroup.object_name.c_str()));

    UINodeData nodeData;
    nodeData.index             = actionGroup.index;
    nodeData.row               = actionGroup.row;
    nodeData.column            = actionGroup.column;
    nodeData.frame_object_name = actionGroup.frame_object_name;
    nodeData.name              = actionGroup.name;
    nodeData.object_name       = actionGroup.object_name;
    nodeData.icon_path         = actionGroup.icon_path;
    nodeData.group_type        = actionGroup.group_type;
    item->setNodeData(nodeData);

    int row = parentItem->childCount();
    beginInsertRows(parent, row, row);
    parentItem->appendChild(item);
    endInsertRows();

    if (!actionGroup.vChild.empty()) {
        QModelIndex currentIndex = index(row, 0, parent);
        for (const auto& childGroup : actionGroup.vChild) {
            addUINode(currentIndex, childGroup);
        }
    }
}

void UIOptionItemModel::addUINode(const QModelIndex& parent, const UIActionGroupItem& actionGroupItem)
{
    UIOptionItem* parentItem = getItem(parent);
    if (!parentItem) { return; }

    QString objName = getObjectName(UINodeType::NTGroupItem, actionGroupItem.object_name);
    QString name    = actionGroupItem.name.empty() ? objName : QString::fromUtf8(actionGroupItem.name.c_str());

    UIOptionItem* item = new UIOptionItem(parentItem);
    item->setType(UINodeType::NTActionGroupItem);
    item->setText(name);
    item->setObjectName(objName);

    UINodeData nodeData;
    nodeData.row         = actionGroupItem.row;
    nodeData.column      = actionGroupItem.column;
    nodeData.name        = std::string(name.toUtf8());
    nodeData.object_name = std::string(objName.toUtf8());
    nodeData.slot_name   = actionGroupItem.slot_name;
    item->setNodeData(nodeData);

    int row = parentItem->childCount();
    beginInsertRows(parent, row, row);
    parentItem->appendChild(item);
    endInsertRows();
}

QModelIndex UIOptionItemModel::addUINode(const QModelIndex& parent,
                                         UINodeType type,
                                         int index,
                                         const std::string& name,
                                         const std::string& object_name)
{
    UIOptionItem* parentItem = getItem(parent);
    if (!parentItem) { return QModelIndex(); }

    UIOptionItem* item = new UIOptionItem(parentItem);
    item->setIndex(index);
    item->setType(type);
    item->setText(QString::fromUtf8(name.c_str()));
    item->setObjectName(QString::fromUtf8(object_name.c_str()));

    UINodeData nodeData;
    nodeData.index       = index;
    nodeData.name        = name;
    nodeData.object_name = object_name;
    item->setNodeData(nodeData);

    int row = parentItem->childCount();
    beginInsertRows(parent, row, row);
    parentItem->appendChild(item);
    endInsertRows();

    return createIndex(row, 0, item);
}

void UIOptionItemModel::removeParentItem(const QModelIndex& parent)
{
    if (!parent.isValid()) { return; }

    UIOptionItem* parentItem = getItem(parent);
    if (!parentItem || parentItem == mRootItem) { return; }

    int row = parentItem->row();
    beginRemoveRows(parent.parent(), row, row);
    parentItem->parent()->children().removeAt(row);
    delete parentItem;
    endRemoveRows();
}

QVariant UIOptionItemModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid()) { return QVariant(); }

    UIOptionItem* item = static_cast<UIOptionItem*>(index.internalPointer());
    if (!item) { return QVariant(); }

    switch (role) {
        case Qt::DisplayRole: return item->text();
        case Qt::DecorationRole: return item->iconPath();
        case UINodeTypeRole: return QVariant::fromValue(item->type());
        case UINodeIndexRole: return item->index();
        case UINodeObjNameRole: return item->objectName();
        case UINodeDataRole: return QVariant::fromValue(item->nodeData());
    }

    return QVariant();
}

bool UIOptionItemModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
    if (!index.isValid()) { return false; }
    UIOptionItem* item = static_cast<UIOptionItem*>(index.internalPointer());
    if (!item) { return false; }

    switch (role) {
        case Qt::EditRole:
        {
            QString text = value.toString();
            if (text.isEmpty()) { return false; }
            item->setText(text);

            UINodeData nodeData = item->nodeData();
            nodeData.name       = std::string(text.toUtf8());
            item->setNodeData(nodeData);

            Q_EMIT dataChanged(index, index, {Qt::DisplayRole, Qt::EditRole});
            return true;
        }
        case UINodeTypeRole:
        {
            if (value.canConvert<UINodeType>()) {
                UINodeType nodeType = value.value<UINodeType>();
                item->setType(nodeType);
                Q_EMIT dataChanged(index, index, {role});
                return true;
            }
            return false;
        }
        case UINodeDataRole:
            if (value.canConvert<UINodeData>()) {
                UINodeData data = value.value<UINodeData>();
                item->setNodeData(data);
                Q_EMIT dataChanged(index, index, {role}); // 通知视图数据变化
                return true;
            }
            return false;
        default: break;
    }
    return false;
}

Qt::DropActions UIOptionItemModel::supportedDropActions() const
{
    return Qt::MoveAction;
}

Qt::ItemFlags UIOptionItemModel::flags(const QModelIndex& index) const
{
    Qt::ItemFlags defaultFlags = QAbstractItemModel::flags(index);

    // 添加拖放和编辑的支持
    return defaultFlags | Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled | Qt::ItemIsEditable;
}

QVariant UIOptionItemModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole) { return QVariant("Tree View"); }

    return QVariant();
}

QModelIndex UIOptionItemModel::index(int row, int column, const QModelIndex& parent) const
{
    if (!hasIndex(row, column, parent)) return QModelIndex();

    UIOptionItem* parentItem;

    if (!parent.isValid())
        parentItem = mRootItem;
    else
        parentItem = static_cast<UIOptionItem*>(parent.internalPointer());

    UIOptionItem* childItem = parentItem->child(row);
    if (childItem)
        return createIndex(row, column, childItem);
    else
        return QModelIndex();
}

QModelIndex UIOptionItemModel::parent(const QModelIndex& index) const
{
    if (!index.isValid()) { return QModelIndex(); }

    UIOptionItem* childItem = static_cast<UIOptionItem*>(index.internalPointer());
    if (!childItem) { return QModelIndex(); }

    UIOptionItem* parentItem = childItem->parent();
    if (parentItem == mRootItem) { return QModelIndex(); }
    return createIndex(parentItem->row(), 0, parentItem);
}

int UIOptionItemModel::rowCount(const QModelIndex& parent) const
{
    UIOptionItem* parentItem;
    if (parent.column() > 0) { return 0; }

    if (!parent.isValid()) { parentItem = mRootItem; }
    else {
        parentItem = static_cast<UIOptionItem*>(parent.internalPointer());
    }
    Q_ASSERT(parentItem);
    return parentItem->childCount();
}

int UIOptionItemModel::columnCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent);
    return 1;
}

bool UIOptionItemModel::removeRows(int row, int count, const QModelIndex& parent)
{
    UIOptionItem* parentItem = getItem(parent);
    Q_ASSERT(parentItem);
    beginRemoveRows(parent, row, row + count - 1);
    parentItem->removeChild(row);
    endRemoveRows();
    return true;
}

void UIOptionItemModel::clearModel()
{
    if (mRootItem->childCount() > 0) { mRootItem->children().clear(); }
    Q_EMIT layoutChanged();
}

void UIOptionItemModel::sortItemsByIndex(QList<UIOptionItem*>& itemList)
{
    std::sort(itemList.begin(), itemList.end(), [](const UIOptionItem* a, const UIOptionItem* b) {
        return a->index() < b->index();
    });

    for (auto it = itemList.begin(); it != itemList.end(); ++it) {
        UIOptionItem* node = *it;
        if (node->childCount()) { sortItemsByIndex(node->children()); }
        else {
            continue;
        }
    }
}

void UIOptionItemModel::sort(const QModelIndex& parent)
{
    UIOptionItem* parentItem = getItem(parent);
    if (parentItem) {
        Q_EMIT layoutAboutToBeChanged();
        sortItemsByIndex(parentItem->children());
        Q_EMIT layoutChanged();
    }
}

void UIOptionItemModel::insertChildItem(const QModelIndex& parent, int row, UIOptionItem* item, int itemIndex)
{
    auto* const parentItem = getItem(parent);
    beginInsertRows(parent, row, row);
    parentItem->insertChild(row, item);
    endInsertRows();
}

void UIOptionItemModel::insertChildItem(UIOptionItem* newParent, UIOptionItem* originalParent)
{
    // 遍历原父节点的所有子节点
    for (int i = 0; i < originalParent->childCount(); ++i) {
        UIOptionItem* originalChild = originalParent->child(i);

        UIOptionItem* newChild = new UIOptionItem(*originalChild);
        newChild->setIndex(originalChild->index()); // 保持原索引
        //newChild->setObjectName(getObjectName(newChild->type()));

        // 插入新子节点到当前新父节点中
        beginInsertRows(createIndex(newParent->row(), 0, newParent), i, i);
        newParent->insertChild(i, newChild);
        endInsertRows();

        // 递归处理子节点的子节点
        if (originalChild->childCount() > 0) { insertChildItem(newChild, originalChild); }
    }
}

void UIOptionItemModel::insertItem(const QModelIndex& parent, int row, UIOptionItem* copyItem, int itemIndex)
{
    UIOptionItem* newItem = new UIOptionItem(*copyItem);
    newItem->setIndex(itemIndex);
    if (copyItem->type() == NTPage) { newItem->setObjectName(getObjectName(newItem->type())); }
    auto* const parentItem = getItem(parent);
    beginInsertRows(parent, row, row);
    parentItem->insertChild(row, newItem);
    endInsertRows();

    // 递归插入子节点
    insertChildItem(newItem, copyItem);
}

void UIOptionItemModel::insertItem(const QModelIndex& parent, int row, const QModelIndex& index, int itemIndex)
{
    UIOptionItem* item = getItem(index);
    if (!item) { return; }

    QVariant itemData = data(index, UINodeDataRole);
    if (itemData.canConvert<UINodeData>()) {
        UINodeData data = itemData.value<UINodeData>();
        qDebug() << "Insert item: " << QString::fromUtf8(data.name.c_str());
    }

    UIOptionItem* newItem = new UIOptionItem(*item);
    newItem->setIndex(itemIndex);

    auto* const parentItem = getItem(parent);
    beginInsertRows(parent, row, row);
    parentItem->insertChild(row, newItem);
    endInsertRows();

    // 递归插入子节点
    insertChildItem(newItem, item);
}

void UIOptionItemModel::copyItems(int row, const QModelIndex& parent, const QModelIndexList& toCopy)
{
    auto* const parentItem = getItem(parent);

    QList<UIOptionItem*> newList;
    for (const auto& index : toCopy) {
        UIOptionItem* item = getItem(index);
        if (!item) { continue; }
        //newList.append(new UIOptionItem(*item));

        QVariant itemData = data(index, UINodeDataRole);
        if (itemData.canConvert<UINodeData>()) {
            UINodeData data = itemData.value<UINodeData>();
            qDebug() << "Copy item: " << QString::fromUtf8(data.name.c_str());
        }
    }

    beginInsertRows(parent, row, row + newList.size() - 1);
    parentItem->insertChildren(row, newList);
    endInsertRows();
}

UINodeType UIOptionItemModel::getNodeType(const QModelIndex& index)
{
    if (!index.isValid()) { return UINodeType::NTRoot; }

    const UINodeType dstType = static_cast<UINodeType>(index.data(UINodeTypeRole).toInt());
    return dstType;

    UIOptionItem* item = static_cast<UIOptionItem*>(index.internalPointer());
    if (item) { return item->type(); }
    return UINodeType::NTUnknown;
}

bool UIOptionItemModel::sameNodeType(const QModelIndex& index, UINodeType type) const
{
    if (!index.isValid()) { return false; }

    UIOptionItem* item = static_cast<UIOptionItem*>(index.internalPointer());
    return item && item->type() == type;
}

bool UIOptionItemModel::isContainerNode(const QModelIndex& index) const
{
    if (!index.isValid()) { return false; }

    auto item = static_cast<UIOptionItem*>(index.internalPointer());
    if (item) { return item->type() == NTPanel || item->type() == NTPage; }
    return false;
}

bool UIOptionItemModel::isRenameable(const QModelIndex& index) const
{
    if (!index.isValid()) { return false; }

    auto item = static_cast<UIOptionItem*>(index.internalPointer());
    if (item) { return (item->type() == NTPage || item->type() == NTPanel || item->type() == NTAction); }
    return false;
}

bool UIOptionItemModel::isEditable(const QModelIndex& index) const
{
    if (!index.isValid()) { return false; }

    auto item = static_cast<UIOptionItem*>(index.internalPointer());
    if (item) { return (item->type() == NTAction || item->type() == NTGroup || item->type() == NTActionGroup); }
    return false;
}

QModelIndex UIOptionItemModel::newUIPage()
{
    UIOptionItem* item = new UIOptionItem(mRootItem);
    int newIndex       = getMaxIndex(QModelIndex()) + 1;
    item->setIndex(newIndex);
    item->setType(UINodeType::NTPage);
    item->setText(QStringLiteral("new page"));
    item->setObjectName(getObjectName(UINodeType::NTPage));

    beginInsertRows(QModelIndex(), mRootItem->childCount(), mRootItem->childCount());
    mRootItem->appendChild(item);
    endInsertRows();

    return index(mRootItem->childCount(), 0, QModelIndex());
}

QModelIndex UIOptionItemModel::newUIPanel(int row, const QModelIndex& parent)
{
    UIOptionItem* parentItem = getItem(parent);
    if (!parentItem) { return QModelIndex(); }

    QString name       = QStringLiteral("new panel");
    QString objName    = getObjectName(UINodeType::NTPanel);
    UIOptionItem* item = new UIOptionItem(parentItem);
    int newIndex       = getMaxIndex(parent) + 1;
    item->setIndex(newIndex);
    item->setType(UINodeType::NTPanel);
    item->setText(name);
    item->setObjectName(objName);

    UINodeData nodeData;
    nodeData.index       = newIndex;
    nodeData.name        = std::string(name.toUtf8());
    nodeData.object_name = std::string(objName.toUtf8());
    item->setNodeData(nodeData);

    beginInsertRows(parent, parentItem->childCount(), parentItem->childCount());
    parentItem->appendChild(item);
    endInsertRows();

    return index(parentItem->childCount(), 0, parent);
}

QModelIndex UIOptionItemModel::newPanelItem(const QModelIndex& parent)
{
    return QModelIndex();
}

int UIOptionItemModel::getMaxIndex(const QModelIndex& parent)
{
    int maxIndex             = -1;
    UIOptionItem* parentItem = getItem(parent);
    if (!parentItem) { return maxIndex; }

    for (int row = 0; row < rowCount(parent); ++row) {
        QModelIndex childIndex = index(row, 0, parent);
        if (childIndex.isValid()) {
            int currentIndex = data(childIndex, UINodeIndexRole).toInt();
            if (currentIndex > maxIndex) { maxIndex = currentIndex; }
        }
    }

    return maxIndex;
}

QString UIOptionItemModel::getObjectName(UINodeType type, const std::string& defaultObjName)
{
    if (!defaultObjName.empty()) { return QString::fromUtf8(defaultObjName.c_str()); }

    QString prefix{"obj"};
    switch (type) {
        case UINodeType::NTRoot: prefix += "Root"; break;
        case UINodeType::NTPage: prefix += "Page"; break;
        case UINodeType::NTPanel: prefix += "Panel"; break;
        case UINodeType::NTAction: prefix += "Action"; break;
        case UINodeType::NTGroup: prefix += "Group"; break;
        case UINodeType::NTActionGroup: prefix += "ActionGroup"; break;
        default: return QString();
    }

    for (int attempt = 0; attempt < 10000; ++attempt) {
        int randomNum = 1000 + QRandomGenerator::global()->bounded(9000);
        QString name  = prefix + QString::number(randomNum);
        if (!mObjNames.contains(name)) {
            mObjNames.insert(name);
            return name;
        }
    }
    return QString();
}

void UIOptionItemModel::updateItemObjectName(UIOptionItem* newItem)
{
    // 遍历所有子节点，如果对象名称相同，则修改对象名称
    QList<QString> pageObjNames;

    for (int i = 0; i < this->rowCount(QModelIndex()); ++i) {
        QModelIndex index   = this->index(i, 0, QModelIndex());
        QString objNameData = this->data(index, UINodeObjNameRole).toString();
        pageObjNames.push_back(objNameData);
    }

    if (newItem->type() == NTPage) {
        if (pageObjNames.contains(newItem->objectName())) { newItem->setObjectName(getObjectName(NTPage)); }
    }
}

void UIOptionItemModel::updateItemIndex(QModelIndex& index, int dstIndex)
{
    // 更新相同索引的子项索引，避免索引冲突
    int newIndex       = dstIndex;
    UIOptionItem* item = getItem(index);
    for (auto& child : item->children()) {
        if (child->index() == newIndex) { child->setIndex(++newIndex); }
    }
}

UIOptionItem* UIOptionItemModel::getItem(const QModelIndex& index)
{
    if (index.isValid()) {
        UIOptionItem* item = static_cast<UIOptionItem*>(index.internalPointer());
        return item;
    }
    return mRootItem;
}
} // namespace NCTI