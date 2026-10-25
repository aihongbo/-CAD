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

#include <QObject>
#include <QTimer>
#include <QFile>
#include <QDir>
#include <QMap>
#include <QDateTime>

namespace NCTI {
/**
* @brief 文件监控类
* @details 监控文件或目录的变化，当文件被修改时发出信号
*/
class FileMoniter : public QObject
{
    Q_OBJECT
public:
    /**
	* @brief 构造函数
	* @param parent 父对象指针
	*/
    explicit FileMoniter(QObject* parent = nullptr);

    /**
	* @brief 析构函数
	*/
    ~FileMoniter();

    /**
	* @brief 开始监控指定文件
	* @param file 要监控的文件
	*/
    void start(const QFile& file);

    /**
	* @brief 开始监控指定目录下的文件
	* @param dir 要监控的目录
	* @param suffixs 文件后缀列表
	*/
    void start(const QDir& dir, const QStringList&);

    /**
	* @brief 停止监控
	*/
    void stop();

    /**
	* @brief 获取被监控的文件列表
	* @return 文件路径列表
	*/
    QStringList getFileList() const;

    /**
	* @brief 文件变化信号
	*/
    Q_SIGNAL void signalChanged();

private:
    /**
	* @brief 启动监控
	*/
    void start();

    /**
	* @brief 添加文件到监控列表
	* @param fileInfo 文件信息
	*/
    void addFile(const QFileInfo& fileInfo);

    /**
	* @brief 定时器超时处理槽函数
	*/
    Q_SLOT void onTimeout();

private:
    QTimer m_timer;                           ///< 定时器
    QMap<QString, QDateTime> m_path2DateTime; ///< 文件路径到修改时间的映射
};
}; // namespace NCTI