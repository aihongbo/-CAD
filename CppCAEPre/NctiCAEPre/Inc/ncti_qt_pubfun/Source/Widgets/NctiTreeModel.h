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
#include "NctiTreeItem.h"

#include <QAbstractItemModel>
#include <QVariant>

#include <vector>

namespace NCTI {

    /**
     * @brief 树模型数据结构体
     * @details 存储树模型中每个节点的数据信息
     */
    struct NctiTreeModelData
    {
        QString text;                                  ///< 文本
        QString objName;                               ///< 对象名称
        QString typeName;                              ///< 类型名称
        QString iconUrl;                               ///< 图标URL
        void* pObject{ nullptr };                      ///< 对象指针
        std::vector<NctiTreeModelData> vChild;         ///< 子节点列表
    };

    /**
     * @brief 树模型类
     * @details 用于管理树形结构数据的模型类，继承自QAbstractItemModel
     */
    class DECL_NCTI_QT_PUBFUN NctiTreeModel : public QAbstractItemModel
    {
        Q_OBJECT
    public:
        /**
         * @brief 构造函数
         * @param vData 模型数据列表
         * @param parent 父对象指针
         */
        explicit NctiTreeModel(const std::vector<NctiTreeModelData>& vData, QObject* parent = nullptr);
        
        /**
         * @brief 拷贝构造函数
         * @param other 其他树模型引用
         */
        NctiTreeModel(const NctiTreeModel& other) = default;
        
        /**
         * @brief 赋值操作符
         * @param other 其他树模型引用
         * @return 树模型引用
         */
        NctiTreeModel& operator=(const NctiTreeModel& other) = default;
        
        /**
         * @brief 析构函数
         */
        ~NctiTreeModel() override;

        /**
         * @brief 移动方向枚举
         * @details 用作移动项的参数
         */
        enum class MoveDirection { 
            UP,    ///< 向上
            DOWN   ///< 向下
        };

        /**
         * @brief 获取数据
         * @param index 索引
         * @param role 角色
         * @return 数据变量
         */
        QVariant data(const QModelIndex& index, int role) const override;

        /**
         * @brief 获取索引
         * @param row 行号
         * @param column 列号
         * @param parent 父索引
         * @return 模型索引
         */
        QModelIndex index(int row, int column, const QModelIndex& parent) const override;

        /**
         * @brief 获取父索引
         * @param child 子索引
         * @return 父索引
         */
        QModelIndex parent(const QModelIndex& child) const override;

        /**
         * @brief 获取行数
         * @param parent 父索引
         * @return 行数
         */
        int rowCount(const QModelIndex& parent) const override;

        /**
         * @brief 获取列数
         * @param parent 父索引
         * @return 列数
         */
        int columnCount(const QModelIndex& parent) const override;

        /**
         * @brief 插入行
         * @param row 行号
         * @param count 数量
         * @param parent 父索引
         * @return 插入成功返回true，否则返回false
         */
        bool insertRows(int row, int count, const QModelIndex& parent) override;

        /**
         * @brief 移除行
         * @param row 行号
         * @param count 数量
         * @param parent 父索引
         * @return 移除成功返回true，否则返回false
         */
        bool removeRows(int row, int count, const QModelIndex& parent) override;

        /**
         * @brief 设置头部数据
         * @param section 部分
         * @param orientation 方向
         * @param value 值
         * @param role 角色
         * @return 设置成功返回true，否则返回false
         */
        bool setHeaderData(int section, Qt::Orientation orientation, const QVariant& value, int role) override;

        /**
         * @brief 获取头部数据
         * @param section 部分
         * @param orientation 方向
         * @param role 角色
         * @return 头部数据变量
         */
        QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

        /**
         * @brief 支持的拖放操作
         * @return 拖放操作
         */
        Qt::DropActions supportedDropActions() const override;

        /**
         * @brief 标志
         * @param index 索引
         * @return 项标志
         */
        Qt::ItemFlags flags(const QModelIndex& index) const override;

        /**
         * @brief 排序
         * @param column 列号
         * @param order 排序顺序
         */
        void sort(int column, Qt::SortOrder order = Qt::AscendingOrder) override;

        /**
         * @brief 更新数据
         * @param newData 新数据列表
         */
        void updateData(const std::vector<NctiTreeModelData>& newData);

        /**
         * @brief 根据索引获取项
         * @param index 索引
         * @return 树项指针
         */
        NctiTreeItem* itemFromIndex(const QModelIndex& index) const;
        
    private:
        NctiTreeItem* mRootItem{ nullptr };    ///< 根项指针
       
        static QHash<QString, QIcon> mIconCache; ///< 图标缓存

        /**
         * @brief 移动项
         * @param item 项索引
         * @param direction 移动方向
         */
        void moveItem(const QModelIndex& item, MoveDirection direction);

        /**
         * @brief 比较函数类型定义
         */
        typedef bool (*compFunc)(const NctiTreeItem*, const NctiTreeItem*);
        
        /**
         * @brief 排序列项
         * @param itemList 项列表引用
         * @param comp 比较函数
         */
        void sortItems(QList<NctiTreeItem*>& itemList, compFunc comp);

        /**
         * @brief 设置模型数据
         * @param vData 数据列表
         * @param parent 父项指针
         */
        void setupModelData(const std::vector<NctiTreeModelData>& vData, NctiTreeItem* parent);


    };

}