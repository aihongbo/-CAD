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

#include "FileMoniter.h"

namespace NCTI {
FileMoniter::FileMoniter(QObject* parent)
    : QObject(parent)
{
    connect(&m_timer, &QTimer::timeout, this, &FileMoniter::onTimeout);
}
FileMoniter::~FileMoniter()
{
    stop();
}

void FileMoniter::start(const QFile& file)
{
    stop();

    if (file.exists()) {
        addFile(QFileInfo(file.fileName()));
    }
    start();
}
void FileMoniter::start(const QDir& dir, const QStringList& suffixs)
{
    stop();

    auto fileInfos = dir.entryInfoList(QDir::Files);
    for (auto&& fileInfo : fileInfos) {
        for (auto&& suffix : suffixs) {
            if (fileInfo.baseName().startsWith(suffix)) {
                addFile(fileInfo);
            }
        }
    }
    start();
}
void FileMoniter::stop()
{
    m_timer.stop();
    m_path2DateTime.clear();
}

QStringList FileMoniter::getFileList() const
{
    return m_path2DateTime.keys();
}

void FileMoniter::start()
{
    m_timer.start(1000);
}
void FileMoniter::addFile(const QFileInfo& fileInfo)
{
    m_path2DateTime.insert(fileInfo.absoluteFilePath(), fileInfo.lastModified());
}

void FileMoniter::onTimeout()
{
    bool changed = false;
    for (auto iter = m_path2DateTime.begin(); iter != m_path2DateTime.end(); iter++) {
        QFileInfo fileInfo(iter.key());
        if (!fileInfo.exists())
            continue;

        if (fileInfo.lastModified() != iter.value()) {
            iter.value() = fileInfo.lastModified();
            changed      = true;
        }
    }

    if (changed) {
        Q_EMIT signalChanged();
    }
}

} // namespace NCTI
