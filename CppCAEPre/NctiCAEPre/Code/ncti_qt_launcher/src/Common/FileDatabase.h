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

#ifndef NCTI_FILEDATABASE_H
#define NCTI_FILEDATABASE_H

#pragma once

#include <fstream>
#include <vector>
#include <chrono>

#include "ormpp/dbng.hpp"
#include "ormpp/sqlite.hpp"
using namespace ormpp;

struct FileDetail;

/**
 * @brief 文件数据库类
 * @details 负责管理文件信息的数据库操作，包括文件记录的增删改查等功能
 */
class FileDatabase 
{
public:
    /**
     * @brief 获取单例实例
     * @return FileDatabase实例指针
     */
    static FileDatabase* getInst();

    /**
     * @brief 初始化数据库
     * @param dbPath 数据库路径
     * @return 初始化成功返回true，否则返回false
     */
    bool initDB(const char* dbPath);

    /**
     * @brief 插入记录
     * @param detail 文件详情
     * @return 插入成功返回true，否则返回false
     */
    bool insertRecord(const FileDetail& detail);
    
    /**
     * @brief 插入多个记录
     * @param details 文件详情列表
     * @return 插入成功返回true，否则返回false
     */
    bool insertRecords(const std::vector<FileDetail>& details);
    
    /**
     * @brief 替换记录
     * @param detail 文件详情
     * @return 替换成功返回true，否则返回false
     */
    bool replaceRecord(const FileDetail & detail);
    
    /**
     * @brief 删除记录
     * @param file_path 文件路径
     * @return 删除成功返回true，否则返回false
     */
    bool deleteRecord(const std::string& file_path);
    
    /**
     * @brief 更新文件详情
     * @param detail 文件详情
     * @return 更新成功返回true，否则返回false
     */
    bool updateDetail(const FileDetail& detail);

    /**
     * @brief 查询并排序
     * @param files 文件列表
     * @return 排序后的文件列表
     */
    std::vector<FileDetail> queryWithSort(std::vector<FileDetail>& files);
    
    /**
     * @brief 查找最近文件
     * @return 最近一周的文件列表
     */
    std::vector<FileDetail> findRecentFiles();
    
    /**
     * @brief 查找所有文件
     * @return 所有文件列表
     */
    std::vector<FileDetail> findAllFiles();
    
    /**
     * @brief 根据类型查找文件
     * @param ncti_type 文件类型
     * @return 指定类型的文件列表
     */
    std::vector<FileDetail> findByType(const std::string& ncti_type);
    
    /**
     * @brief 根据收藏状态查找文件
     * @param favorite 收藏状态(0未收藏，1已收藏)
     * @return 指定收藏状态的文件列表
     */
    std::vector<FileDetail> findByFavorite(int favorite = 1);
    
    /**
     * @brief 根据路径查找文件
     * @param file_path 文件路径
     * @return 指定路径的文件列表
     */
    std::vector<FileDetail> findByPath(const std::string& file_path);
    
    /**
     * @brief 根据文件名查找文件
     * @param fileName 文件名
     * @return 匹配文件名的文件列表
     */
    std::vector<FileDetail> findByName(const std::string& fileName);

private:
    /**
     * @brief 构造函数
     */
    FileDatabase();
    
    /**
     * @brief 禁止拷贝构造
     */
    FileDatabase(const FileDatabase&) = delete;
    
    /**
     * @brief 禁止赋值操作
     */
    FileDatabase& operator=(const FileDatabase&) = delete;
    
    dbng<sqlite> mSQLite;  ///< SQLite数据库实例
};

/**
 * @brief 文件详情结构体
 * @details 存储文件的详细信息
 */
struct FileDetail
{
    int id;                       ///< 数据库ID
    int favorite = -1;            ///< 收藏状态(0未收藏，1已收藏，-1未设置)
    std::string file_name;        ///< 文件名称
    std::string file_path;        ///< 文件本地路径
    std::string ncti_type;        ///< 文件类型[assembly, part]
    std::vector<char> thumbnail;  ///< 缩略图BLOB数据
    int64_t update_time = 0;      ///< 更新时间Unix时间戳
};
REGISTER_AUTO_KEY(FileDetail, id)
REGISTER_CONFLICT_KEY(FileDetail, file_path)

#endif // NCTI_FILEDATABASE_H