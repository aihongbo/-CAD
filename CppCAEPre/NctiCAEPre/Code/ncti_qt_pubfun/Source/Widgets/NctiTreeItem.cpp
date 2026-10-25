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

#include "NctiTreeItem.h"
#include <QDebug>

namespace NCTI {

    NctiTreeItem::NctiTreeItem(NctiTreeItem* parent)
        : mParentItem(parent)
        , mItemLevel(parent ? parent->getItemLevel() + 1 : 0)
    {
    }

    NctiTreeItem::NctiTreeItem(const NctiTreeItem& other)
        : mParentItem(other.mParentItem)
        , mItemLevel(other.mItemLevel)
        , mName(other.mName)
        , mObjName(other.mObjName)
        , mIcon(other.mIcon)
        , mRowColor(other.mRowColor)
        , mTextColor(other.mTextColor)
        , pObject(other.pObject)
    {

        for (auto child : other.mChildItems) {
            insertChild(deepCopyItem(*child, this));
        }
    }

    NctiTreeItem& NctiTreeItem::operator=(const NctiTreeItem& other)
    {
        if (this == &other) return *this;

        mParentItem = other.mParentItem;
        mItemLevel = other.mItemLevel;
        mName = other.mName;
        mObjName = other.mObjName;
        mIcon = other.mIcon;
        mRowColor = other.mRowColor;
        mTextColor = other.mTextColor;
        pObject = other.pObject;

        qDeleteAll(mChildItems);
        mChildItems.clear();
        for (auto child : other.mChildItems) {
            insertChild(new NctiTreeItem(*child));
        }
        return *this;
    }

    NctiTreeItem::~NctiTreeItem()
    {
        qDeleteAll(mChildItems);
    }

    int NctiTreeItem::childCount() const
    {
        return mChildItems.size();
    }

    void NctiTreeItem::insertChild(NctiTreeItem* child)
    {
        if (!child) return;

        child->setItemParent(this);
        child->setItemLevel(getItemLevel() + 1);
        mChildItems.append(child);
    }

    void NctiTreeItem::removeChild(int pos)
    {
        if (pos < 0 || pos >= mChildItems.size())
            return;

        delete mChildItems.takeAt(pos);
    }

    void NctiTreeItem::swapChilds(int target, int dest)
    {
        if (target < 0 || target >= mChildItems.size() || dest < 0 || dest >= mChildItems.size())
            return;

        qSwap(mChildItems[target], mChildItems[dest]);
    }

    NctiTreeItem* NctiTreeItem::getChildItem(int pos) const
    {
        return mChildItems.value(pos);
    }

    int NctiTreeItem::getChildPos(NctiTreeItem* child) const
    {
        return mChildItems.indexOf(child);
    }

    QList<NctiTreeItem*>& NctiTreeItem::getChildList()
    {
        return mChildItems;
    }

    const QList<NctiTreeItem*>& NctiTreeItem::getChildListRead() const
    {
        return mChildItems;
    }

    int NctiTreeItem::getItemSelfRow() const
    {
        if (!mParentItem) return 0;
        return mParentItem->getChildPos(const_cast<NctiTreeItem*>(this));
    }

    NctiTreeItem* NctiTreeItem::deepCopyItem(const NctiTreeItem& child, NctiTreeItem* const parent)
    {
        NctiTreeItem* newItem = new NctiTreeItem(child);
        newItem->setItemParent(parent);
        newItem->setItemLevel(parent ? parent->getItemLevel() + 1 : 0);

        for (auto subChild : child.getChildListRead()) {
            newItem->insertChild(deepCopyItem(*subChild, newItem));
        }
        return newItem;
    }

    bool NctiTreeItem::itemCompareAsc(const NctiTreeItem* left, const NctiTreeItem* right)
    {
        return QString::localeAwareCompare(left->getItemName(), right->getItemName()) < 0;
    }

    bool NctiTreeItem::itemCompareDes(const NctiTreeItem* left, const NctiTreeItem* right)
    {
        return QString::localeAwareCompare(left->getItemName(), right->getItemName()) > 0;
    }

    QDataStream& operator<<(QDataStream& stream, const NctiTreeItem& item)
    {
        stream << item.mName << item.mObjName << item.mIcon << item.mRowColor << item.mTextColor;
        stream << reinterpret_cast<quintptr>(item.pObject);
        stream << item.mItemLevel;
        stream << item.mChildItems.size();
        for (auto child : item.mChildItems) {
            stream << *child;
        }
        return stream;
    }

    QDataStream& operator>>(QDataStream& stream, NctiTreeItem& item)
    {
        stream >> item.mName >> item.mObjName >> item.mIcon >> item.mRowColor >> item.mTextColor;
        quintptr objectPtr;
        stream >> objectPtr;
        item.pObject = reinterpret_cast<void*>(objectPtr);
        stream >> item.mItemLevel;

        int size;
        stream >> size;
        item.mChildItems.reserve(size);
        for (int i = 0; i < size; ++i) {
            item.mChildItems[i] = new NctiTreeItem();
            stream >> *item.mChildItems[i];
            item.mChildItems[i]->setItemParent(&item);
            item.mChildItems[i]->setItemLevel(item.mItemLevel + 1);
        }
        return stream;
    }

}