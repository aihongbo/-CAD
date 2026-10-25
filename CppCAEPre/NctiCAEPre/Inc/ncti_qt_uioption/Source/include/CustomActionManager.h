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

#include <nlohmann/json.hpp>
using json = nlohmann::json;
using namespace nlohmann::literals;

#include "ormpp/dbng.hpp"
#include "ormpp/sqlite.hpp"
using namespace ormpp;

#include <QString>
#include <QPixmap>

/**
 * @brief 自定义命令结构体
 * @details 定义了自定义命令的相关信息，包括索引、名称、图标路径、缩略图等
 */
struct CustomAction
{
    int id;                      ///< 数据库ID
    int action_index;            ///< 命令索引
    std::string action_name;     ///< 命令名称
    std::string icon_path;       ///< 图标路径
    std::vector<char> thumbnail; ///< 命令图标

};
REGISTER_AUTO_KEY(CustomAction, id)
REGISTER_CONFLICT_KEY(CustomAction, action_index)

class QIcon;

/**
 * @brief 自定义命令管理器类
 * @details 负责管理自定义命令的增删改查操作，以及与数据库的交互
 */
class NCTI_UIOPTION CustomActionManager
{
public:
    /**
     * @brief 获取单例实例
     * @return CustomActionManager的引用
     */
    static CustomActionManager& getInst();

    /**
     * @brief 检查自定义命令是否存在
     * @param action_name 命令名称
     * @return true表示存在，false表示不存在
     */
    bool isCustomActionExists(const std::string& action_name);

    /**
     * @brief 获取保存目录路径
     * @return 保存目录的QString路径
     */
    QString getSaveDir();

    /**
     * @brief 获取Python脚本文件路径
     * @param actionName 命令名称
     * @return Python脚本文件的QString路径
     */
    QString getPyFilePath(const QString& actionName);

    /**
     * @brief 获取文件完整路径
     * @param filePath 文件相对路径
     * @return 文件完整路径
     */
    QString getFileFullPath(const QString& filePath);

    /**
     * @brief 获取命令图标
     * @param name 命令名称
     * @return QIcon对象
     */
    QIcon getActionIcon(const std::string& name);
    
    /**
     * @brief 获取命令图标
     * @param customAction 自定义命令结构体
     * @return QIcon对象
     */
    QIcon getActionIcon(const CustomAction& customAction);

    /**
     * @brief 获取所有自定义命令
     */
    std::vector<CustomAction> allCustomActions();
    
    /**
     * @brief 获取新命令的索引
     * @return 新命令的索引值
     */
    int getIndexForNewAction();

    /**
     * @brief 插入记录
     * @param action 自定义命令结构体
     * @return true表示成功，false表示失败
     */
    bool insertRecord(const CustomAction& action);
    
    /**
     * @brief 插入多条记录
     * @param action 自定义命令列表
     * @return true表示成功，false表示失败
     */
    bool insertRecords(const std::vector<CustomAction>& action);

    /**
     * @brief 替换记录
     * @param action 自定义命令结构体
     * @return true表示成功，false表示失败
     */
    bool replaceRecord(const CustomAction& action);

    /**
     * @brief 删除记录
     * @param action_name 命令名称
     * @return true表示成功，false表示失败
     */
    bool deleteRecord(const std::string& action_name);

    /**
     * @brief 更新记录
     * @param action 自定义命令结构体
     * @return true表示成功，false表示失败
     */
    bool updateRecord(const CustomAction& action);

    /**
     * @brief 根据名称查找记录
     * @param action_name 命令名称
     * @return 查找到的自定义命令结构体
     */
    CustomAction findByName(const std::string& action_name);

    /**
     * @brief 更新Python脚本路径
     * @param originActionName 原始命令名称
     * @param actionName 新命令名称
     * @return true表示成功，false表示失败
     */
    bool updatePyScriptPath(const std::string& originActionName, std::string& actionName);

    /**
     * @brief std::string转QString工具函数
     * @param str std::string对象
     * @return QString对象
     */
    static QString toQString(const std::string& str);
    
    /**
     * @brief QString转std::string工具函数
     * @param qstr QString对象
     * @return std::string对象
     */
    static std::string toString(const QString& qstr);

    /**
     * @brief 判断是否为自定义图标
     * @param path 图标路径
     * @return true表示是自定义图标，false表示不是
     */
    static bool isCustomIcon(const QString& path);
    
    /**
     * @brief 判断是否为自定义图标
     * @param path 图标路径
     * @return true表示是自定义图标，false表示不是
     */
    static bool isCustomIcon(const std::string& path);

    /**
     * @brief 获取缩略图
     * @param thumbnail 缩略图数据
     * @return QPixmap对象
     */
    static QPixmap getThumbnail(const std::vector<char>& thumbnail);
    
    /**
     * @brief 获取缩略图
     * @param path 图标路径
     * @return 缩略图数据
     */
    static std::vector<char> getThumbnail(const std::string& path);

private:
    /**
     * @brief 构造函数
     */
    CustomActionManager();
    
    /**
     * @brief 禁止拷贝构造
     */
    CustomActionManager(const CustomActionManager&)            = delete;
    
    /**
     * @brief 禁止赋值操作
     */
    CustomActionManager& operator=(const CustomActionManager&) = delete;
    
    /**
     * @brief 加载自定义数据库
     * @return true表示成功，false表示失败
     */
    bool loadCustomDb();
    
    /**
     * @brief 查询并排序
     * @param actions 自定义命令列表
     * @return 排序后的自定义命令列表
     */
    std::vector<CustomAction> queryWithSort(std::vector<CustomAction>& actions);

private:
    dbng<sqlite> mSQLite; ///< SQLite数据库对象
};