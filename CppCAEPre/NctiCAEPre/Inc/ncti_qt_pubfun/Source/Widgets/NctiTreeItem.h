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

#ifndef NCTI_TREE_ITEM_H
#define NCTI_TREE_ITEM_H
#pragma once

#include "dcl_ncti_qt_pubfun.h"
#include <QString>
#include <QList>
#include <QIcon>
#include <QColor>
#include <QMetaType>

namespace NCTI
{
    /**
     * @brief 树项类
     * @details 用于表示树形结构中的一个节点项，包含名称、图标、颜色等属性
     */
    class DECL_NCTI_QT_PUBFUN NctiTreeItem
    {
    public:
        /**
         * @brief 构造函数
         * @param parent 父项指针
         */
        explicit NctiTreeItem(NctiTreeItem* parent = nullptr);
        
        /**
         * @brief 拷贝构造函数
         * @param other 其他树项引用
         */
        explicit NctiTreeItem(const NctiTreeItem& other);
        
        /**
         * @brief 赋值操作符
         * @param other 其他树项引用
         * @return 树项引用
         */
        NctiTreeItem& operator=(const NctiTreeItem& other);
        
        /**
         * @brief 析构函数
         * @details 清理子项内存
         */
        ~NctiTreeItem();

        /**
         * @brief 获取子项数量
         * @return 子项数量
         */
        int  childCount() const;

        /**
         * @brief 插入子项
         * @param child 子项指针
         */
        void insertChild(NctiTreeItem* child);

        /**
         * @brief 移除子项
         * @param pos 位置索引
         */
        void removeChild(int pos);

        /**
         * @brief 交换子项
         * @param target 目标索引
         * @param dest 目标位置索引
         */
        void swapChilds(int target, int dest);

        /**
         * @brief 获取子项
         * @param pos 位置索引
         * @return 子项指针
         */
        NctiTreeItem* getChildItem(int pos) const;

        /**
         * @brief 获取子项位置
         * @param child 子项指针
         * @return 位置索引
         */
        int getChildPos(NctiTreeItem* child) const;

        /**
         * @brief 获取子项列表
         * @return 子项列表引用
         */
        QList<NctiTreeItem*>& getChildList();

        /**
         * @brief 获取只读子项列表
         * @return 子项列表常量引用
         */
        const QList<NctiTreeItem*>& getChildListRead() const;

        /**
         * @brief 深拷贝项
         * @details 创建当前项的深拷贝，包括所有子项
         * @param child 子项引用
         * @param parent 父项指针
         * @return 树项指针
         */
        NctiTreeItem* deepCopyItem(const NctiTreeItem& child, NctiTreeItem* const parent);

        /**
         * @brief 获取项自身行号
         * @return 项在父项列表中的位置
         */
        int getItemSelfRow() const;

        /**
         * @brief 获取项级别
         * @return 项在模型中的深度，默认为0
         */
        int getItemLevel() const { return mItemLevel;}

        /**
         * @brief 获取项背景色
         * @return 背景色
         */
        QColor getItemBackColor() const { return mRowColor;}
        
        /**
         * @brief 设置项背景色
         * @param color 颜色
         */
        void setItemBackColor(const QColor& color) { mRowColor = color;}

        /**
         * @brief 获取项文本颜色
         * @return 文本颜色
         */
        QColor getItemTextColor() const { return mTextColor;}
        
        /**
         * @brief 设置项文本颜色
         * @param color 颜色
         */
        void setItemTextColor(const QColor& color) { mTextColor = color;}

        /**
         * @brief 获取项图标
         * @return 图标
         */
        QIcon getItemIcon() const { return mIcon;}
        
        /**
         * @brief 设置项图标
         * @param icon 图标
         */
        void setItemIcon(const QIcon& icon) { mIcon = icon;}

        /**
         * @brief 获取项名称
         * @return 名称
         */
        QString getItemName() const { return mName; }
        
        /**
         * @brief 设置项名称
         * @param name 名称
         */
        void setItemName(const QString& name) { mName = name;}

        /**
         * @brief 获取项对象名称
         * @return 对象名称
         */
        QString getItemObjName() const { return mObjName;}
        
        /**
         * @brief 设置项对象名称
         * @param name 对象名称
         */
        void setItemObjName(const QString& name) { mObjName = name;}

        /**
         * @brief 获取项类型名称
         * @return 类型名称
         */
        QString getItemTypeName() const { return mTypeName; }
        
        /**
         * @brief 设置项类型名称
         * @param name 类型名称
         */
        void setItemTypeName(const QString& name) { mTypeName = name; }

        /**
         * @brief 获取对象
         * @return 对象指针
         */
        void* getObject() const { return pObject;}
        
        /**
         * @brief 设置对象
         * @param pObj 对象指针
         */
        void setObject(void* pObj) { pObject = pObj;}

        /**
         * @brief 获取父项
         * @return 父项指针
         */
        NctiTreeItem* getItemParent() const { return mParentItem;}
        
        /**
         * @brief 设置父项
         * @param parent 父项指针
         */
        void setItemParent(NctiTreeItem* parent) { mParentItem = parent;}

        /**
         * @brief 项升序比较
         * @param left 左侧项指针
         * @param right 右侧项指针
         * @return 按name升序排列结果
         */
        static bool itemCompareAsc(const NctiTreeItem* left, const NctiTreeItem* right);

        /**
         * @brief 项降序比较
         * @param left 左侧项指针
         * @param right 右侧项指针
         * @return 按name降序排列结果
         */
        static bool itemCompareDes(const NctiTreeItem* left, const NctiTreeItem* right);

        /**
         * @brief 流输出操作符
         * @details 用于序列化对象到数据流中
         * @param stream 数据流引用
         * @param item 项引用
         * @return 数据流引用
         */
        friend QDataStream& operator<<(QDataStream& stream, const NctiTreeItem& item);
        
        /**
         * @brief 流输入操作符
         * @details 用于从数据流中反序列化对象
         * @param stream 数据流引用
         * @param item 项引用
         * @return 数据流引用
         */
        friend QDataStream& operator>>(QDataStream& stream, NctiTreeItem& item);

    private:
        /**
         * @brief 设置项级别
         * @details 设置项在模型中的深度
         * @param lvl 级别
         */
        void setItemLevel(int lvl) { mItemLevel = lvl; }

    private:
        QList<NctiTreeItem*> mChildItems;          ///< 子项列表，存储所有直接子节点
        NctiTreeItem* mParentItem{ nullptr };      ///< 父项指针，指向直接父节点
        int mItemLevel{ 0 };                       ///< 项级别，表示在树形结构中的深度
        QString mName;                             ///< 名称，显示在树形视图中的主要标识
        QString mObjName;                          ///< 对象名称，用于标识关联的对象
        QString mTypeName;                         ///< 类型名称，表示节点的类型信息
        QIcon mIcon;                               ///< 图标，显示在树形视图中的图标
        QColor mRowColor{ QColor(251, 252, 254) }; ///< 行背景色，用于设置行的背景颜色
        QColor mTextColor{ QColor(82, 85, 90) };   ///< 文本颜色，用于设置文本的颜色
        void* pObject{ nullptr };                  ///< 对象指针，指向与该节点关联的任意类型对象
    };
}
Q_DECLARE_METATYPE(NCTI::NctiTreeItem)

#endif // NCTI_TREE_ITEM_H