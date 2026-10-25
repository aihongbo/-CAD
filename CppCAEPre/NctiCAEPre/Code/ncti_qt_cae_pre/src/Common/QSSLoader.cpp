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

#include "QSSLoader.h"
#include "FileMoniter.h"
#include <QApplication>
#include <QDebug>
#include <mutex>

namespace NCTI {
QSSLoader* QSSLoader::mInstance = nullptr;
QSSLoader::QSSLoader(QObject* parent)
    : QObject(parent)
    , m_moniter(new FileMoniter(this))
{
    connect(m_moniter, &FileMoniter::signalChanged, this, &QSSLoader::update);
}
QSSLoader* QSSLoader::getInstance()
{
    static std::once_flag once;
    std::call_once(once, [] { mInstance = new QSSLoader(); });
    return mInstance;
}

void QSSLoader::load(const QDir& dir, const QStringList& suffixs)
{
    m_moniter->start(dir, suffixs);
    update();
}

void QSSLoader::update()
{
    QStringList fileList = m_moniter->getFileList();
    QString content;
    for (auto&& path : fileList) {
        QFile file(path);
        if (!file.exists() || !file.open(QIODevice::ReadOnly))
            continue;

        content += "\n";
        content += file.readAll();
    }

    qApp->setStyleSheet(content);
}
} // namespace NCTI
