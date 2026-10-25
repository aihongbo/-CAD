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

#include <QDir>
#include <QObject>

namespace NCTI {
class FileMoniter;

/**
* @brief QSS加载器类
* @details 负责加载和监控QSS样式表文件的变化
*/
class QSSLoader : public QObject
{
    Q_OBJECT
public:
    /**
	* @brief 获取单例实例
	* @return QSSLoader实例指针
	*/
    static QSSLoader* getInstance();

    /**
	* @brief 加载指定目录下的QSS文件
	* @param dir QSS文件所在目录
	* @param suffixs 文件后缀列表
	*/
    void load(const QDir& dir, const QStringList& suffix);

private:
    /**
	* @brief 构造函数
	* @param parent 父对象指针
	*/
    QSSLoader(QObject* parent = nullptr);

    /**
	* @brief 更新样式表
	*/
    Q_SLOT void update();

private:
    static QSSLoader* mInstance; ///< 单例实例
    FileMoniter* m_moniter;       ///< 文件监控器
};
}; // namespace NCTI