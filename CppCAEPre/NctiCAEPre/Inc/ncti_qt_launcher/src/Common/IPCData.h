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

#ifndef INTER_PROCESS_COMMUNICATION_DATA_H
#define INTER_PROCESS_COMMUNICATION_DATA_H

#include "nlohmann/json.hpp"
using json = nlohmann::json;
using namespace nlohmann::literals;

namespace NCTI {
    /**
     * @brief 消息类型枚举
     * @details 定义了进程间通信的各种消息类型
     */
    enum MessageType {
        MT_WINDOW_ID,   ///< 窗口句柄消息
        MT_EXIT,        ///< 程序退出消息
        MT_EXIT_SAVE,   ///< 保存退出消息
        MT_CANCEL,      ///< 取消操作消息
        MT_UPDATE,      ///< 数据更新消息
        MT_DOC_DIRTY,   ///< 文档有修改消息
        MT_DOC_REFRESH, ///< 文档刷新消息
        MT_TASK_DETAIL, ///< 任务详情
        MT_INVALID = -1,///< 无效消息类型
    };
    NLOHMANN_JSON_SERIALIZE_ENUM(MessageType,
        {
            { MT_INVALID, nullptr },
            { MT_WINDOW_ID, "window_id" },
            { MT_EXIT, "exit" },
            { MT_EXIT_SAVE, "exit_save" },
            { MT_CANCEL, "cancel" },
            { MT_UPDATE, "update" },
            { MT_DOC_DIRTY, "doc_dirty" },
            { MT_DOC_REFRESH, "doc_refresh" },
            { MT_TASK_DETAIL, "task_detail" }
        })

    
    /**
     * @brief 任务详情结构体
     * @details 用于存储任务相关信息
     */    
    struct TaskDetail
    {
        std::string type;       ///< 任务类型
        std::string file_path;  ///< 文件路径
        std::string geometry;   ///< 几何类型
        std::string constraint; ///< 约束类型
        std::string mesh;       ///< 网格类型
        NLOHMANN_DEFINE_TYPE_INTRUSIVE(TaskDetail, type, file_path, geometry, constraint, mesh);
    };

    /**
     * @brief 消息数据类
     * @details 用于进程间通信的消息数据结构
     */
    class MessageData
    {
    public:
        MessageType msg_type = MT_INVALID; ///< 消息类型
        int64_t window_id = 0;    ///< 窗口ID
        std::string file_name;    ///< ncti文件名称
        std::string file_path;    ///< ncti文件路径
        std::string project_type; ///< 工程类型
        bool dirty = false;       ///< 文件是否有修改
        bool traversed = false;   ///< 文件是否已处理
        std::string task_type;    ///< 任务类型
        std::string geometry;     ///< 几何类型
        std::string constraint;   ///< 约束类型
        std::string mesh;         ///< 网格类型
    public:
        MessageData() = default;
        NLOHMANN_DEFINE_TYPE_INTRUSIVE(MessageData, msg_type, 
            window_id, file_name, file_path, project_type, dirty, traversed, task_type, geometry, constraint, mesh);
    };
}


#endif // !INTER_PROCESS_COMMUNICATION_DATA_H



