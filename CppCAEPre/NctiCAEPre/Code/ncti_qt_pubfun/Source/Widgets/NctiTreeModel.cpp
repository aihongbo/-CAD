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

#include "NctiTreeModel.h"
#include <QDebug>

namespace NCTI {

    static QString getIconUrl(const QString& typeName, const QString& defaultUrl)
    {
        QString iconUrl;
        if (typeName == "doc_part") { 
            iconUrl = ":/Tree/doc_part.svg"; 
        }
        else if (typeName == "groupsystem") { 
            iconUrl = ":/Tree/systemtype.svg"; 
        }
        else if (typeName == "groupmode") { 
            iconUrl = ":/Tree/modeltype.svg"; 
        }
        else if (typeName == "groupsketch") { 
            iconUrl = ":/Tree/sketchType.svg"; 
        }
        else if (typeName == "groupsimulation") { 
            iconUrl = ":/Tree/simulationtype.svg"; 
        }
        else if (typeName == "doc_occ_custom_container"
            || typeName == "doc_assembly"
            || typeName == "group"
            || typeName == "grp_body_group") {
            iconUrl = ":/Tree/file_custom.svg";
        }
        else if (typeName == "doc_sketch") {
            iconUrl = ":/Tree/sketch.svg";
        }
        else if (typeName == "grp_ncti_display_model_body") {
            iconUrl = ":/Tree/body.svg";
        }
        else if (typeName == "grp_ncti_grid_mesh") {
            iconUrl = ":/Tree/body.svg";
        }
        else if (typeName == "grp_ncti_mesh_object") {
            iconUrl = ":/Tree/body.svg";
        }
        else if (typeName == "grp_ncti_frequency") {
            iconUrl = ":/Tree/body.svg";
        }
        else if (typeName == "grp_ncti_bpo_mat" 
            || typeName == "grp_ncti_bpo_set" 
            || typeName == "grp_ncti_bpo_section" 
            || typeName == "grp_ncti_bpo_cf" 
            || typeName == "grp_ncti_bpo_press" 
            || typeName == "grp_ncti_bpo_moment" 
            || typeName == "grp_ncti_bpo_gravity" 
            || typeName == "grp_ncti_bpo_inertia_relief" 
            || typeName == "grp_ncti_bpo_output" 
            || typeName == "grp_ncti_bpo_spc" 
            || typeName == "grp_ncti_bpo_step" 
            || typeName == "grp_ncti_bpo_frequency_step" 
            || typeName == "grp_ncti_bpo_buckle_step" 
            || typeName == "grp_ncti_bpo_static_step" 
            || typeName == "grp_ncti_bpo_setgrid" 
            || typeName == "grp_ncti_bpo_set_geometry" 
            || typeName == "grp_ncti_bpo_particle" 
			|| typeName == "grp_ncti_bpo_coupling"
			|| typeName == "grp_ncti_bpo_tie") {
            iconUrl = ":/Tree/body.svg";
        }
        else if (typeName == "grp_ncti_doc_system_object"
            || typeName == "grp_ncti_test_system_object"
            || typeName == "grp_ncti_aimodel_system_object"
            || typeName == "grp_ncti_test_case_to_model_manage") {
            iconUrl = ":/Tree/config.svg";
        }
        else if (typeName == "INVALID") {
            iconUrl = ":/Tree/warning.svg";
        }
		else if (typeName == "grp_ncti_dcm3_object")
		{
			iconUrl = ":/Tree/constraint_item.svg";
		}
		else if(typeName == "grp_ncti_dcm3_root")
		{
			iconUrl = ":/Tree/constraint.svg";
		}
		else if(typeName == "overdefined")
		{
			iconUrl = ":/Tree/overdefined.svg";
		}
        return iconUrl.isEmpty() ? defaultUrl : iconUrl;
	}

    QHash<QString, QIcon> NctiTreeModel::mIconCache;
	NctiTreeModel::NctiTreeModel(const std::vector<NctiTreeModelData>& vData, QObject* parent)
		: QAbstractItemModel(parent)
		, mRootItem(new NctiTreeItem(nullptr))
	{
		setupModelData(vData, mRootItem);
	}

	NctiTreeModel::~NctiTreeModel()
	{
		delete mRootItem;
		mRootItem = nullptr;
	}

    void NctiTreeModel::setupModelData(const std::vector<NctiTreeModelData>& vData, NctiTreeItem* parent)
	{
		for (const auto& it : vData) {
			if (it.pObject == nullptr && it.text.count() < 1)
			{
				if (!it.vChild.empty()) {
					setupModelData(it.vChild, parent);
				}
				continue;
			}

            QString text = it.text.isEmpty() ? it.typeName : it.text;
            QString iconUrl = getIconUrl(it.typeName, it.iconUrl);
            QIcon icon;
            if (mIconCache.contains(iconUrl)) {
                icon = mIconCache[iconUrl];
            }
            else {
                icon = QIcon(iconUrl);
                mIconCache[iconUrl] = icon;
            }

            NctiTreeItem* item = new NctiTreeItem(parent);
			item->setItemName(text);
			item->setItemIcon(icon);
			item->setItemObjName(it.objName);
			item->setItemTypeName(it.typeName);
			item->setObject(it.pObject);
			parent->insertChild(item);
			//qDebug() << "text" << it.text << ", typeName:" << it.typeName << ", objName:" << it.objName;
			if (!it.vChild.empty()) {
				setupModelData(it.vChild, item);
			}
		}
	}

	QVariant NctiTreeModel::data(const QModelIndex& index, int role) const
	{
		if (!index.isValid()) return QVariant();

		NctiTreeItem* item = static_cast<NctiTreeItem*>(index.internalPointer());
		switch (role) {
		case Qt::DisplayRole:
			return item->getItemName();
		case Qt::DecorationRole:
			return item->getItemIcon();
		case Qt::BackgroundRole:
			return item->getItemBackColor();
		case Qt::ForegroundRole:
			return item->getItemTextColor();
		case Qt::UserRole:
			return item->getItemObjName();
		default:
			return QVariant();
		}
	}

	QModelIndex NctiTreeModel::index(int row, int column, const QModelIndex& parent) const
	{
		NctiTreeItem* parentItem = itemFromIndex(parent);
		NctiTreeItem* childItem = parentItem->getChildItem(row);
		if (childItem) {
			return createIndex(row, column, childItem);
		}
		return QModelIndex();
	}

	QModelIndex NctiTreeModel::parent(const QModelIndex& child) const
	{
		if (!child.isValid()) return QModelIndex();

		NctiTreeItem* childItem = static_cast<NctiTreeItem*>(child.internalPointer());
		if (!childItem) return QModelIndex();

		NctiTreeItem* parentItem = childItem->getItemParent();
		if (parentItem == mRootItem) {
			return QModelIndex();
		}
		return createIndex(parentItem->getItemSelfRow(), 0, parentItem);
	}

	bool NctiTreeModel::setHeaderData(int section, Qt::Orientation orientation, const QVariant& value, int role)
	{
		bool result = QAbstractItemModel::setHeaderData(section, orientation, value, role);
		if (result) {
			Q_EMIT headerDataChanged(orientation, section, section);
		}
		return result;
	}

	QVariant NctiTreeModel::headerData(int section, Qt::Orientation orientation, int role) const
	{
		Q_UNUSED(section);
		Q_UNUSED(orientation);

		if (role == Qt::DisplayRole)
			return QVariant("");
		else
			return QVariant();
	}

	int NctiTreeModel::rowCount(const QModelIndex& parent) const
	{
		NctiTreeItem* parentItem = nullptr;
		if (!parent.isValid())
			parentItem = mRootItem;
		else {
			parentItem = static_cast<NctiTreeItem*>(parent.internalPointer());
			Q_ASSERT(parentItem);
		}
		return parentItem->childCount();
	}

	int NctiTreeModel::columnCount(const QModelIndex& parent) const
	{
		Q_UNUSED(parent);
		return 1;
	}

	bool NctiTreeModel::insertRows(int row, int count, const QModelIndex& parent)
	{
		NctiTreeItem* parentItem = itemFromIndex(parent);
		beginInsertRows(parent, row, row + count - 1);
		parentItem->insertChild(new NctiTreeItem(parentItem));
		endInsertRows();
		return true;
	}

	bool NctiTreeModel::removeRows(int row, int count, const QModelIndex& parent)
	{
		NctiTreeItem* parentItem = itemFromIndex(parent);
		beginRemoveRows(parent, row, row + count - 1);
		parentItem->removeChild(row);
		endRemoveRows();
		return true;
	}

    void NctiTreeModel::moveItem(const QModelIndex& item, MoveDirection direction)
	{
		if (!item.isValid()) return;

		NctiTreeItem* node = static_cast<NctiTreeItem*>(item.internalPointer());
		int targetItemPos = node->getItemSelfRow();
		NctiTreeItem* parentItem = itemFromIndex(item.parent());
		if (direction == MoveDirection::UP && targetItemPos) {
			beginMoveRows(item.parent(), targetItemPos, targetItemPos, item.parent(), targetItemPos - 1);
			parentItem->swapChilds(targetItemPos, targetItemPos - 1);
			endMoveRows();
		}
		else if (direction == MoveDirection::DOWN && targetItemPos < node->childCount() - 1) {
			beginMoveRows(item.parent(), targetItemPos + 1, targetItemPos + 1, item.parent(), targetItemPos);
			parentItem->swapChilds(targetItemPos, targetItemPos + 1);
			endMoveRows();
		}
	}

	void NctiTreeModel::sort(int column, Qt::SortOrder order)
	{
		Q_UNUSED(column);
		Q_EMIT layoutAboutToBeChanged();
		if (order == Qt::AscendingOrder)
			sortItems(mRootItem->getChildList(), NctiTreeItem::itemCompareAsc);
		else
			sortItems(mRootItem->getChildList(), NctiTreeItem::itemCompareDes);
		Q_EMIT layoutChanged();
	}

	void NctiTreeModel::updateData(const std::vector<NctiTreeModelData>& newData)
	{
		beginResetModel();

		delete mRootItem;
		mRootItem = nullptr;
		mRootItem = new NctiTreeItem(nullptr);

		setupModelData(newData, mRootItem);

		endResetModel();
	}

	void NctiTreeModel::sortItems(QList<NctiTreeItem*>& itemList, NctiTreeModel::compFunc func)
	{
		std::sort(itemList.begin(), itemList.end(), func);
		for (auto it = itemList.begin(); it != itemList.end(); ++it) {
			NctiTreeItem* node = *it;
			if (node->childCount())
				sortItems(node->getChildList(), func);
			else
				continue;
		}
	}

	Qt::DropActions NctiTreeModel::supportedDropActions() const
	{
		return Qt::MoveAction;
	}

	Qt::ItemFlags NctiTreeModel::flags(const QModelIndex& index) const {
		if (!index.isValid()) {
			return Qt::ItemIsDropEnabled;
		}
		return (QAbstractItemModel::flags(index) | Qt::ItemIsDragEnabled);
	}

	NctiTreeItem* NctiTreeModel::itemFromIndex(const QModelIndex& index) const
	{
		if (index.isValid()) {
			return static_cast<NctiTreeItem*>(index.internalPointer());
		}
		return mRootItem;
	}

}