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

#include "FileDatabase.h"
#include <QDebug>

namespace {
    static std::vector<char> readThumbnail(const std::string& path)
    {
        std::ifstream file(path, std::ios::binary | std::ios::ate);
        if (!file) return {};

        size_t size = file.tellg();
        file.seekg(0);

        std::vector<char> buffer(size);
        file.read(buffer.data(), size);
        return buffer;
    }
}

FileDatabase* FileDatabase::getInst()
{
    static FileDatabase inst;
    return &inst;
}

FileDatabase::FileDatabase()
{
}

bool FileDatabase::initDB(const char* dbPath)
{
    if (!mSQLite.connect(dbPath)) {
        qDebug() << "connect db failed";
        return false;
    }

    ormpp_not_null not_null{ {"file_name", "file_path"} };
    if (!mSQLite.create_datatable<FileDetail>(ormpp_auto_key{ "id" }, not_null)) {
        qDebug() << "create FileDetail datatable failed";
        return false;
    }
    return true;
}

bool FileDatabase::insertRecord(const FileDetail& detail)
{
    return mSQLite.insert(detail) == 1;
}

bool FileDatabase::insertRecords(const std::vector<FileDetail>& details)
{
    return mSQLite.insert(details) == details.size();
}

bool FileDatabase::replaceRecord(const FileDetail& detail)
{
    return mSQLite.replace(detail) == 1;
}

bool FileDatabase::deleteRecord(const std::string& file_path)
{
    return mSQLite.delete_records_s<FileDetail>("file_path=?", file_path);
}

bool FileDatabase::updateDetail(const FileDetail& detail)
{
    auto files = mSQLite.query_s<FileDetail>("file_path=?", detail.file_path);
    if (files.empty()) {
        return false;
    }
    
    FileDetail updatedDetail = detail;
    updatedDetail.id = files[0].id;
    return mSQLite.update<FileDetail>(updatedDetail) == 1;
}

std::vector<FileDetail> FileDatabase::queryWithSort(std::vector<FileDetail>& files)
{
    // 按 update_time 降序排列（最新时间在前）
    std::sort(files.begin(), files.end(),
        [](const FileDetail& a, const FileDetail& b) {
            return a.update_time > b.update_time;
        }
    );
    return files;
}

std::vector<FileDetail> FileDatabase::findRecentFiles()
{
    const auto now = std::chrono::system_clock::now();
    const auto week_ago = now - std::chrono::hours(24 * 7);
    const int64_t timestamp = std::chrono::duration_cast<std::chrono::seconds>(                                                             
        week_ago.time_since_epoch()).count();

    auto files = mSQLite.query_s< FileDetail>("update_time>?", timestamp);
    return queryWithSort(files);
}


std::vector<FileDetail> FileDatabase::findAllFiles() 
{
    auto files = mSQLite.query_s<FileDetail>("");
    return queryWithSort(files);
}

std::vector<FileDetail> FileDatabase::findByType(const std::string& ncti_type)
{
    auto files = mSQLite.query_s<FileDetail>("ncti_type=?", ncti_type);
    return queryWithSort(files);
}

std::vector<FileDetail> FileDatabase::findByFavorite(int favorite)
{
    auto files = mSQLite.query_s<FileDetail>("favorite=?", favorite);
    return queryWithSort(files);
}

std::vector<FileDetail> FileDatabase::findByPath(const std::string& file_path)
{
    auto files = mSQLite.query_s<FileDetail>("file_path=?", file_path);
    return queryWithSort(files);
}

std::vector<FileDetail> FileDatabase::findByName(const std::string& fileName)
{
    std::string pattern = "%" + fileName + "%";
    auto files = mSQLite.query_s<FileDetail>("file_name LIKE ?", pattern);
    return queryWithSort(files);
}






