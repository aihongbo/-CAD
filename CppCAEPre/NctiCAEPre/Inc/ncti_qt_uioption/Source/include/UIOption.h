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

#ifndef UIOption_H
#define UIOption_H
#pragma once

#include "dcl_ncti_uioption.h"

#include <nlohmann/json.hpp>
using json = nlohmann::json;
using namespace nlohmann::literals;

#include <type_traits>
#include <tuple>
#include <unordered_set>

#include <QString>
#include <QObject>
#include <QMetaObject>
#include <QDebug>

namespace NCTI {

/**
* @brief 索引管理接口
*/
class IndexManager
{
protected:
    int m_nextIndex{0};                    ///< 下一个可用索引
    std::unordered_set<int> m_usedIndexes; ///< 已使用的索引集合

public:
    IndexManager()          = default;
    virtual ~IndexManager() = default;

    /**
    * @brief 获取下一个可用索引
    * @return 可用的索引值
    */
    int GetNextIndex()
    {
        while (m_usedIndexes.find(m_nextIndex) != m_usedIndexes.end()) {
            m_nextIndex++;
        }
        int index = m_nextIndex++;
        m_usedIndexes.insert(index);
        return index;
    }

    /**
    * @brief 手动分配索引
    * @param index 要分配的索引值
    * @return 如果索引未被使用则返回true，否则返回false
    */
    bool AllocateIndex(int index)
    {
        if (index < 0 || m_usedIndexes.find(index) != m_usedIndexes.end()) {
            return false;
        }
        m_usedIndexes.insert(index);
        if (index >= m_nextIndex) {
            m_nextIndex = index + 1;
        }
        return true;
    }

    /**
    * @brief 释放索引
    * @param index 要释放的索引值
    */
    void ReleaseIndex(int index)
    {
        m_usedIndexes.erase(index);
        // 如果释放的是当前的下一个索引，可以适当回退
        if (index == m_nextIndex - 1) {
            m_nextIndex--;
            // 继续回退，直到找到一个已使用的索引或回到0
            while (m_nextIndex > 0 && m_usedIndexes.find(m_nextIndex - 1) == m_usedIndexes.end()) {
                m_nextIndex--;
            }
        }
    }

    /**
    * @brief 检查索引是否已使用
    * @param index 要检查的索引值
    * @return 如果索引已使用则返回true，否则返回false
    */
    bool IsIndexUsed(int index) const { return m_usedIndexes.find(index) != m_usedIndexes.end(); }

    /**
    * @brief 重置索引管理器
    */
    void Reset()
    {
        m_nextIndex = 0;
        m_usedIndexes.clear();
    }

    /**
    * @brief 获取已使用的索引数量
    * @return 已使用的索引数量
    */
    size_t GetUsedIndexCount() const { return m_usedIndexes.size(); }
};

/**
* @brief UI页面类型枚举
* @details 定义了各种UI页面的类型，用于区分不同的功能模块
*/
enum UIPageType {
    UI_FILE,              ///< 文件页面
    UI_GENERAL,           ///< 常规页面
    UI_ASSEMBLY,          ///< 装配页面
    UI_SKETCH,            ///< 草图页面
    UI_GEOMETRY,          ///< 几何页面
    UI_AI,                ///< AI页面
    UI_SIMULATION,        ///< 仿真页面
    UI_CUSTOM,            ///< 自定义页面
    UI_INVALID_PAGE = -1, ///< 无效分类页
};

/**
* @brief UI页面类型与JSON序列化映射
*/
NLOHMANN_JSON_SERIALIZE_ENUM(UIPageType,
                             {
                                 {UI_INVALID_PAGE, nullptr},
                                 {UI_FILE, "file"},
                                 {UI_GENERAL, "general"},
                                 {UI_SKETCH, "sketch"},
                                 {UI_GEOMETRY, "geometry"},
                                 {UI_AI, "ai"},
                                 {UI_SIMULATION, "simulation"},
                                 {UI_CUSTOM, "custom"},
                             })

/**
* @brief UI动作结构体
* @details 定义了UI动作的相关属性，如名称、图标、槽函数等
*/
class UIAction
{
public:
    int index = -1;               ///< 显示索引
    std::string name;             ///< 节点名称
    std::string object_name;      ///< 对象名称
    std::string icon_path;        ///< 节点图标路径
    std::string slot_name;        ///< 槽函数名称
    std::string short_cut;        ///< 快捷键
    int width = 0;                ///< 显示最小宽度
    std::string pystring;         ///< python脚本
    std::vector<UIAction> vChild; ///< 子节点列表
    IndexManager indexManager;    ///< 索引管理器

public:
    UIAction* newAction(const std::string& name,
                        const std::string& object_name,
                        const std::string& icon_path,
                        const std::string& slot_name)
    {
        vChild.emplace_back();
        UIAction& act   = vChild.back();
        act.index       = indexManager.GetNextIndex();
        act.name        = name;
        act.object_name = object_name;
        act.icon_path   = icon_path;
        act.slot_name   = slot_name;
        return &act;
    }

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(UIAction,
                                   index,
                                   name,
                                   object_name,
                                   icon_path,
                                   slot_name,
                                   short_cut,
                                   width,
                                   pystring,
                                   vChild);
};

/**
* @brief UI组项结构体
* @details 定义了UI组项的相关属性
*/
class UIGroupItem
{
public:
    std::string name;        ///< 动作名称
    std::string object_name; ///< 对象名称
    std::string icon_path;   ///< 图标路径
    std::string slot_name;   ///< 槽函数名称

public:
    /**
    * @brief 定义JSON序列化相关宏
    */
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(UIGroupItem, name, object_name, icon_path, slot_name);
};

/**
* @brief UI组结构体
* @details 定义了UI组的相关属性
*/
class UIGroup
{
public:
    int index = -1;                  ///< 组索引
    std::string name;                ///< 组名称
    std::string object_name;         ///< 对象名称
    std::vector<UIGroupItem> vChild; ///< 子项列表

public:
    void AddGroupItem(const UIGroupItem& item) { 
        vChild.push_back(item); 
    }

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(UIGroup, index, name, object_name, vChild);
};

/**
* @brief UI动作组项结构体
* @details 定义了UI动作组项的相关属性
*/
class UIActionGroupItem
{
public:
    int row    = -1;         ///< 行数
    int column = -1;         ///< 列数
    std::string name;        ///< 动作名称
    std::string object_name; ///< 对象名称
    std::string slot_name;   ///< 槽函数名称

public:
    /**
    * @brief 定义JSON序列化相关宏
    */
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(UIActionGroupItem, row, column, name, object_name, slot_name);
};

/**
* @brief UI动作组结构体
* @details 定义了UI动作组的相关属性
*/
class UIActionGroup
{
public:
    int index  = -1;                       ///< 动作组索引
    int row    = -1;                       ///< 总行数
    int column = -1;                       ///< 总列数
    std::string frame_object_name;         ///< 对象名称
    std::string name;                      ///< 动作名称
    std::string object_name;               ///< 对象名称
    std::string icon_path;                 ///< 图标路径
    std::string group_type;                ///< 分组类型check_box、radio_button
    std::vector<UIActionGroupItem> vChild; ///< 子项列表

public:
    void AddGroupItem(const UIActionGroupItem& item) { 
        vChild.push_back(item); 
    }

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(UIActionGroup,
                                   index,
                                   row,
                                   column,
                                   frame_object_name,
                                   name,
                                   object_name,
                                   icon_path,
                                   group_type,
                                   vChild);
};

/**
* @brief UI面板结构体
* @details 定义了UI面板的相关属性
*/
class UIPanel
{
public:
    int index = -1;                           ///< 面板索引
    std::string name;                         ///< 面板名称
    std::string object_name;                  ///< 对象名称
    std::vector<UIAction> actions;            ///< 动作列表
    std::vector<UIGroup> groups;              ///< 组列表
    std::vector<UIActionGroup> action_groups; ///< 动作组列表
    IndexManager indexManager;                ///< 索引管理器
    UIAction* newActionToPanel(const std::string& name,
                               const std::string& object_name,
                               const std::string& icon_path = "",
                               const std::string& slot_name = "")
    {
        actions.emplace_back();
        UIAction& a   = actions.back();
        a.index       = indexManager.GetNextIndex();
        a.name        = name;
        a.object_name = object_name;
        a.icon_path   = icon_path;
        a.slot_name   = slot_name;
        return &a;
    }

    UIGroup* newGroupToPanel()
    {
        groups.emplace_back();
        UIGroup& g = groups.back();
        g.index    = indexManager.GetNextIndex();
        return &g;
    }

    UIActionGroup* newActionGroupToPanel(int row,
                                         int col,
                                         const std::string& frame_object_name,
                                         const std::string& name,
                                         const std::string& object_name,
                                         const std::string& icon_path,
                                         const std::string& group_type)
    {
        action_groups.emplace_back();
        UIActionGroup& ag    = action_groups.back();
        ag.index             = indexManager.GetNextIndex();
        ag.row               = row;
        ag.column            = col;
        ag.frame_object_name = frame_object_name;
        ag.name              = name;
        ag.object_name       = object_name;
        ag.icon_path         = icon_path;
        ag.group_type        = group_type;
        return &ag;
    }

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(UIPanel, index, name, object_name, actions, groups, action_groups);
};

/**
* @brief UI页面结构体
* @details 定义了UI页面的相关属性
*/
class UIPage
{
public:
    std::string object_name;     ///< 对象名称
    std::vector<UIPanel> panels; ///< 面板列表
    IndexManager indexManager;   ///< 索引管理器
    UIPanel* newPanel(const std::string& name, const std::string& object_name)
    {
        panels.emplace_back();
        UIPanel& panel    = panels.back();
        panel.index       = indexManager.GetNextIndex();
        panel.name        = name;
        panel.object_name = object_name;
        return &panel;
    }

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(UIPage, object_name, panels);
};

/**
* @brief UI标签页详情结构体
* @details 定义了UI标签页的详细信息
*/
class UITabDetail
{
public:
    int index = -1;          ///< 排序索引
    std::string name;        ///< Tab名称
    std::string object_name; ///< 对象名称
    bool show = true;        ///< 是否显示

    /**
    * @brief 定义JSON序列化相关宏
    */
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(UITabDetail, index, name, object_name, show);
};

/**
* @brief UI功能区结构体
* @details 定义了UI功能区的相关属性
*/
class UIRibbon
{
public:
    std::string logo;              ///< 程序图标
    std::string title;             ///< 程序标题
    std::string version;           ///< 配置版本
    std::vector<UITabDetail> tabs; ///< 分类页
    IndexManager indexManager;     ///< 索引管理器
    void AddTab(const std::string& name, const std::string& obj_name, bool show)
    {
        int index = indexManager.GetNextIndex();
        tabs.push_back(UITabDetail{index, name, obj_name, show});
    }

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(UIRibbon, logo, title, version, tabs);
};

/**
* @brief UI选项类型枚举
* @details 定义了默认和自定义两种UI选项类型
*/
enum class UIOptionType {
    Default, ///< 默认类型
    User     ///< 用户类型
};

/**
* @brief UI选项类
* @details 负责加载和管理UI选项配置
*/
class NCTI_UIOPTION UIOption
{
public:
    /**
    * @brief 获取单例实例
    */
    static UIOption& GetInst();

    /**
    * @brief 加载UI选项
    */
    bool LoadUIOption();

    /**
    * @brief 加载UI页面
    */
    UIPage LoadUIPage(const std::string& objectName, bool bDefault = false);

    /**
    * @brief 获取Logo路径
    */
    QString GetLogo();

    /**
    * @brief 获取标题
    */
    QString GetTitle();

    /**
    * @brief 获取版本
    */
    QString GetVersion();

    /**
    * @brief 获取标签页名称
    */
    static std::string GetTabName(UIPageType type);

    /**
    * @brief 获取UI选项文件路径列表
    */
    QStringList GetUIOptionFiles();

    /**
    * @brief 获取UI功能区配置
    */
    UIRibbon GetUIRibbon() const;

    /**
    * @brief 获取标签页列表
    */
    std::vector<UITabDetail> GetTabs(UIOptionType type);

    /**
    * @brief 保存UI选项
    */
    bool SaveUIOption(const UIRibbon& uiRibbon);

    /**
    * @brief 保存UI页面
    */
    bool SaveUIPages(const std::unordered_map<std::string, UIPage>& uiPages);

private:
    /**
    * @brief 检查版本是否更新
    */
    bool isVersionUpdated(const std::string& version);

    /**
    * @brief 加载UI选项
    */
    UIRibbon loadUIOption(const QString& jsonPath) const;

    /**
    * @brief 加载UI页面
    */
    UIPage loadUIPage(const QString& jsonPath);

    /**
    * @brief 初始化默认UI选项
    */
    void initDefaultUIOption();

    /**
    * @brief 获取UI选项路径
    */
    QString getUIOptionPath();

    /**
    * @brief 获取UI详情路径
    */
    QString getUIDetailPath(const std::string& objectName);

    /**
    * @brief 获取JSON路径
    */
    QString getJsonPath(const std::string& objectName, bool bCheckExists = true);

private:
    UIOption();
    ~UIOption();
    UIRibbon mUIRibbon;
    UIRibbon mDefaultUIRibbon;
    std::unordered_map<std::string, UIPage> mDefaultUIPages;
};
} // namespace NCTI

#endif // !UIOption_H