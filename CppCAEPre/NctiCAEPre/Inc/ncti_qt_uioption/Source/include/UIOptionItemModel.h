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

#include <QAbstractItemModel>
#include <QList>
#include <QVariant>
#include <QIcon>
#include <QSet>

/**
 * @brief UI节点类型枚举
 * @details 定义了UI树中各种节点的类型
 */
enum UINodeType {
    NTUnknown = 0,     ///< 未知类型
    NTRoot,            ///< 根节点
    NTPage,            ///< 功能分类节点
    NTPanel,           ///< 功能面板节点
    NTAction,          ///< 动作节点
    NTGroup,           ///< 分组节点
    NTGroupItem,       ///< 分组子节点
    NTActionGroup,     ///< 动作分组节点
    NTActionGroupItem  ///< 动作分组子节点
};
Q_DECLARE_METATYPE(UINodeType)

/**
 * @brief UI节点数据结构体
 * @details 存储UI节点的各种属性数据
 */
struct UINodeData
{
    int index{-1};              ///< 节点索引
    int row{-1};                ///< 行数
    int column{-1};             ///< 列数
    int width{0};               ///< 宽度
    std::string name;           ///< 名称
    std::string icon_path;      ///< 图标路径
    std::string object_name;    ///< 对象名称
    std::string short_cut;      ///< 快捷键
    std::string slot_name;      ///< 槽函数名称
    std::string frame_object_name; ///< 框架对象名称
    std::string group_type;     ///< 分组类型
    std::string pyscript;       ///< Python脚本
};
Q_DECLARE_METATYPE(UINodeData)

namespace NCTI {
/**
 * @brief 自定义角色枚举
 * @details 定义了用于存储节点信息的自定义角色
 */
enum Roles {
    UINodeTypeRole    = Qt::UserRole + 101, ///< 用于存储节点类型
    UINodeIndexRole   = Qt::UserRole + 102, ///< 用于存储节点索引
    UINodeObjNameRole = Qt::UserRole + 103, ///< 用于存储对象名称
    UINodeDataRole    = Qt::UserRole + 104  ///< 用于存储节点数据
};

/**
 * @brief UI选项项类
 * @details 表示UI树中的一个节点项，包含节点的各种属性和子节点管理功能
 */
class NCTI_UIOPTION UIOptionItem
{
public:
    /**
     * @brief 构造函数
     * @param parent 父节点指针
     */
    explicit UIOptionItem(UIOptionItem* parent = nullptr);

    /**
     * @brief 拷贝构造函数
     * @param other 另一个UIOptionItem对象
     */
    explicit UIOptionItem(const UIOptionItem& other);

    /**
     * @brief 构造函数
     * @param type 节点类型
     * @param row 行数
     * @param data 节点数据
     */
    explicit UIOptionItem(UINodeType type, const int row, const UINodeData& data);

    /**
     * @brief 析构函数
     */
    ~UIOptionItem() { qDeleteAll(mChildren); }

    /**
     * @brief 获取节点类型
     * @return 节点类型
     */
    UINodeType type() const { return mType; }
    
    /**
     * @brief 设置节点类型
     * @param type 节点类型
     */
    void setType(UINodeType type) { mType = type; }

    /**
     * @brief 获取节点索引
     * @return 节点索引
     */
    int index() const { return mIndex; }
    
    /**
     * @brief 设置节点索引
     * @param index 节点索引
     */
    void setIndex(const int& index) { mIndex = index; }

    /**
     * @brief 获取文本
     * @return 文本字符串
     */
    QString text() const { return mText; }
    
    /**
     * @brief 设置文本
     * @param text 文本字符串
     */
    void setText(const QString& text) { mText = text; }

    /**
     * @brief 获取图标路径
     * @return 图标路径字符串
     */
    QString iconPath() const { return mIconPath; }
    
    /**
     * @brief 设置图标路径
     * @param iconPath 图标路径字符串
     */
    void setIconPath(const QString& iconPath) { mIconPath = iconPath; }

    /**
     * @brief 获取对象名称
     * @return 对象名称字符串
     */
    QString objectName() const { return mObjName; }
    
    /**
     * @brief 设置对象名称
     * @param objName 对象名称字符串
     */
    void setObjectName(const QString& objName) { mObjName = objName; }

    /**
     * @brief 获取节点数据
     * @return UINodeData结构体
     */
    UINodeData nodeData() const { return mNodeData; }
    
    /**
     * @brief 设置节点数据
     * @param data UINodeData结构体
     */
    void setNodeData(const UINodeData& data) { mNodeData = data; }

    /**
     * @brief 获取父节点
     * @return 父节点指针
     */
    UIOptionItem* parent() { return mParentItem; }
    
    /**
     * @brief 设置父节点
     * @param parent 父节点指针
     */
    void setParent(UIOptionItem* parent) { mParentItem = parent; }

    /**
     * @brief 获取子节点
     * @param row 子节点行数
     * @return 子节点指针
     */
    UIOptionItem* child(int row) { return mChildren.value(row); }
    
    /**
     * @brief 获取子节点数量
     * @return 子节点数量
     */
    int childCount() const { return mChildren.count(); }

    /**
     * @brief 添加子节点
     * @param child 子节点指针
     */
    void appendChild(UIOptionItem* child)
    {
        child->setParent(this);
        Q_ASSERT(!mChildren.contains(child));
        mChildren.append(child);
    }
    
    /**
     * @brief 移除子节点
     * @param row 子节点行数
     */
    void removeChild(int row) { delete mChildren.takeAt(row); }

    /**
     * @brief 插入子节点
     * @param index 插入位置
     * @param child 子节点指针
     */
    void insertChild(int index, UIOptionItem* child)
    {
        child->setParent(this);
        Q_ASSERT(!mChildren.contains(child));
        mChildren.insert(index, child);
    }

    /**
     * @brief 插入多个子节点
     * @param index 插入位置
     * @param children 子节点列表
     */
    void insertChildren(int index, QList<UIOptionItem*> children)
    {
        for (auto* const c : children) {
            insertChild(index++, c);
        }
    }

    /**
     * @brief 获取行数
     * @return 行数
     */
    int row() const { return mParentItem ? mParentItem->mChildren.indexOf(const_cast<UIOptionItem*>(this)) : 0; }
    
    /**
     * @brief 获取子节点行数
     * @param child 子节点指针
     * @return 子节点行数
     */
    int childRow(UIOptionItem* child) const { return mChildren.indexOf(child); }

    /**
     * @brief 获取子节点数据列表
     * @return 子节点列表的常量引用
     */
    const QList<UIOptionItem*>& childrenData() const { return mChildren; }
    
    /**
     * @brief 获取子节点列表
     * @return 子节点列表的引用
     */
    QList<UIOptionItem*>& children() { return mChildren; }

private:
    UINodeType mType{UINodeType::NTUnknown}; ///< 节点类型
    int mIndex{-1};                          ///< 节点索引
    QString mIconPath;                       ///< 节点名称
    QString mText;                           ///< 节点名称
    QString mObjName;                        ///< 对象名称(节点的唯一标识符）
    UINodeData mNodeData;                    ///< 节点数据

    UIOptionItem* mParentItem{nullptr};      ///< 父节点
    QList<UIOptionItem*> mChildren;          ///< 子节点
};

// 前向声明
class UIAction;
class UIGroup;
class UIActionGroup;
class UIGroupItem;
class UIActionGroupItem;

/**
 * @brief UI选项项模型类
 * @details 继承自QAbstractItemModel，用于管理UI选项树的数据模型
 */
class NCTI_UIOPTION UIOptionItemModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    /**
     * @brief 构造函数
     * @param parent 父对象指针
     */
    explicit UIOptionItemModel(QObject* parent = nullptr);
    
    /**
     * @brief 析构函数
     */
    ~UIOptionItemModel();

    /**
     * @brief 获取数据
     * @param index 模型索引
     * @param role 角色
     * @return 数据变量
     */
    QVariant data(const QModelIndex& index, int role) const override;
    
    /**
     * @brief 设置数据
     * @param index 模型索引
     * @param value 数据值
     * @param role 角色
     * @return true表示成功，false表示失败
     */
    bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole) override;

    /**
     * @brief 支持的拖放操作
     * @return 拖放操作类型
     */
    Qt::DropActions supportedDropActions() const override;
    
    /**
     * @brief 获取项目标志
     * @param index 模型索引
     * @return 项目标志
     */
    Qt::ItemFlags flags(const QModelIndex& index) const override;
    
    /**
     * @brief 获取表头数据
     * @param section 部分
     * @param orientation 方向
     * @param role 角色
     * @return 表头数据
     */
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    /**
     * @brief 创建索引
     * @param row 行数
     * @param column 列数
     * @param parent 父索引
     * @return 模型索引
     */
    QModelIndex index(int row, int column, const QModelIndex& parent = QModelIndex()) const override;
    
    /**
     * @brief 获取父索引
     * @param index 模型索引
     * @return 父索引
     */
    QModelIndex parent(const QModelIndex& index) const override;

    /**
     * @brief 获取行数
     * @param parent 父索引
     * @return 行数
     */
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    
    /**
     * @brief 获取列数
     * @param parent 父索引
     * @return 列数
     */
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    
    /**
     * @brief 移除行
     * @param row 行数
     * @param count 数量
     * @param parent 父索引
     * @return true表示成功，false表示失败
     */
    bool removeRows(int row, int count, const QModelIndex& parent) override;

    /**
     * @brief 添加UI页面
     * @param index 索引
     * @param name 名称
     * @param object_name 对象名称
     * @return 模型索引
     */
    QModelIndex addUIPage(int index, const std::string& name, const std::string& object_name);
    
    /**
     * @brief 添加UI面板
     * @param pageIndex 页面索引
     * @param object_name 对象名称
     * @param systemModel 是否为系统模型
     */
    void addUIPanels(QModelIndex pageIndex, const std::string& object_name, bool systemModel);

    /**
     * @brief 添加UI节点
     * @param parent 父索引
     * @param action UIAction引用
     */
    void addUINode(const QModelIndex& parent, const UIAction& action);
    
    /**
     * @brief 添加UI节点
     * @param parent 父索引
     * @param group UIGroup引用
     */
    void addUINode(const QModelIndex& parent, const UIGroup& group);
    
    /**
     * @brief 添加UI节点
     * @param parent 父索引
     * @param groupItem UIGroupItem引用
     */
    void addUINode(const QModelIndex& parent, const UIGroupItem& groupItem);
    
    /**
     * @brief 添加UI节点
     * @param parent 父索引
     * @param actionGroup UIActionGroup引用
     */
    void addUINode(const QModelIndex& parent, const UIActionGroup& actionGroup);
    
    /**
     * @brief 添加UI节点
     * @param parent 父索引
     * @param actionGroupItem UIActionGroupItem引用
     */
    void addUINode(const QModelIndex& parent, const UIActionGroupItem& actionGroupItem);
    
    /**
     * @brief 添加UI节点
     * @param parent 父索引
     * @param type 节点类型
     * @param index 索引
     * @param name 名称
     * @param object_name 对象名称
     * @return 模型索引
     */
    QModelIndex addUINode(const QModelIndex& parent,
                          UINodeType type,
                          int index,
                          const std::string& name,
                          const std::string& object_name);

    /**
     * @brief 移除父项
     * @param parent 父索引
     */
    void removeParentItem(const QModelIndex& parent);
    
    /**
     * @brief 清空模型
     */
    void clearModel();

    /**
     * @brief 排序
     * @param parent 父索引
     */
    void sort(const QModelIndex& parent);

    /**
     * @brief 插入子项
     * @param parent 父索引
     * @param row 行数
     * @param item 项指针
     * @param itemIndex 项索引
     */
    void insertChildItem(const QModelIndex& parent, int row, UIOptionItem* item, int itemIndex);
    
    /**
     * @brief 插入子项
     * @param newParent 新父节点
     * @param originalParent 原始父节点
     */
    void insertChildItem(UIOptionItem* newParent, UIOptionItem* originalParent);
    
    /**
     * @brief 插入项
     * @param parent 父索引
     * @param row 行数
     * @param newItem 新项指针
     * @param itemIndex 项索引
     */
    void insertItem(const QModelIndex& parent, int row, UIOptionItem* newItem, int itemIndex);
    
    /**
     * @brief 插入项
     * @param parent 父索引
     * @param row 行数
     * @param copyIndex 复制索引
     * @param itemIndex 项索引
     */
    void insertItem(const QModelIndex& parent, int row, const QModelIndex& copyIndex, int itemIndex);

    /**
     * @brief 复制项
     * @param row 行数
     * @param parent 父索引
     * @param toCopy 待复制索引列表
     */
    void copyItems(int row, const QModelIndex& parent, const QModelIndexList& toCopy);

    /**
     * @brief 获取节点类型
     * @param index 索引
     * @return 节点类型
     */
    UINodeType getNodeType(const QModelIndex& index);
    
    /**
     * @brief 检查节点类型是否相同
     * @param index 索引
     * @param type 节点类型
     * @return true表示相同，false表示不同
     */
    bool sameNodeType(const QModelIndex& index, UINodeType type) const;
    
    /**
     * @brief 检查是否为容器节点
     * @param index 索引
     * @return true表示是容器节点，false表示不是
     */
    bool isContainerNode(const QModelIndex& index) const;
    
    /**
     * @brief 检查是否可重命名
     * @param index 索引
     * @return true表示可重命名，false表示不可重命名
     */
    bool isRenameable(const QModelIndex& index) const;
    
    /**
     * @brief 检查是否可编辑
     * @param index 索引
     * @return true表示可编辑，false表示不可编辑
     */
    bool isEditable(const QModelIndex& index) const;

    /**
     * @brief 创建新UI页面
     * @return 模型索引
     */
    QModelIndex newUIPage();
    
    /**
     * @brief 创建新UI面板
     * @param row 行数
     * @param parent 父索引
     * @return 模型索引
     */
    QModelIndex newUIPanel(int row, const QModelIndex& parent);
    
    /**
     * @brief 创建新面板项
     * @param parent 父索引
     * @return 模型索引
     */
    QModelIndex newPanelItem(const QModelIndex& parent);

    /**
     * @brief 更新项对象名称
     * @param newItem 新项指针
     */
    void updateItemObjectName(UIOptionItem* newItem);
    
    /**
     * @brief 更新项索引
     * @param parentIndex 父索引
     * @param dstIndex 目标索引
     */
    void updateItemIndex(QModelIndex& parentIndex, int dstIndex);
    
    /**
     * @brief 获取项
     * @param index 索引
     * @return 项指针
     */
    UIOptionItem* getItem(const QModelIndex& index);
    
    /**
     * @brief 获取最大索引
     * @param parent 父索引
     * @return 最大索引值
     */
    int getMaxIndex(const QModelIndex& parent);
    
    /**
     * @brief 获取对象名称
     * @param type 节点类型
     * @param defaultObjName 默认对象名称
     * @return 对象名称
     */
    QString getObjectName(UINodeType type, const std::string& defaultObjName = "");

private:
    /**
     * @brief 按索引排序项
     * @param itemList 项列表
     */
    void sortItemsByIndex(QList<UIOptionItem*>& itemList);
    
    UIOptionItem* mRootItem{nullptr}; ///< 根项
    QSet<QString> mObjNames;          ///< 对象名称集合
};
} // namespace NCTI