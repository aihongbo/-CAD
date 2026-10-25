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

#include "CustomActionManager.h"
#include <QCoreApplication>
#include <QStandardPaths>
#include <QDir>
#include <QFile>
#include <QString>
#include <QImage>
#include <QIcon>
#include <QDebug>

CustomActionManager& CustomActionManager::getInst()
{
    static CustomActionManager instance;
    return instance;
}

CustomActionManager::CustomActionManager()
{
    loadCustomDb();
}

bool CustomActionManager::loadCustomDb()
{
    // 获取%APPDATA%对应的目录（Roaming目录）
    QString appDataPath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);

    QString dataDir = QDir(appDataPath).filePath("data");
    if (!QDir().mkpath(dataDir)) {
        qWarning() << "Cannot create data directory:" << dataDir;
        return false;
    }

    QString dbPath = QDir(dataDir).filePath("custom.db");
    if (!mSQLite.connect(dbPath.toUtf8().data())) {
        qDebug() << "connect db failed";
        return false;
    }

    ormpp_not_null not_null{{"action_index", "action_name"}};
    if (!mSQLite.create_datatable<CustomAction>(ormpp_auto_key{"id"}, not_null)) {
        qDebug() << "create CustomAction datatable failed";
        return false;
    }
    return true;
}

bool CustomActionManager::isCustomActionExists(const std::string& action_name)
{
    auto actions = mSQLite.query_s<CustomAction>("action_name=?", action_name);
    return !actions.empty();
}

bool CustomActionManager::updatePyScriptPath(const std::string& originActionName, std::string& actionName)
{
    QString originScriptPath = getPyFilePath(toQString(originActionName));
    if (!QFile::exists(originScriptPath)) { return false; }

    QFileInfo fileInfo(originScriptPath);
    QString newPyScriptPath = QDir(fileInfo.path()).filePath(toQString(actionName) + "." + fileInfo.completeSuffix());
    if (QFile::exists(newPyScriptPath)) { QFile::remove(newPyScriptPath); }

    if (!QFile::copy(originScriptPath, newPyScriptPath)) { return false; }

    return true;
}

QString CustomActionManager::getSaveDir()
{
    const QString DATA_SCRIPTS_PATH = "data/scripts/custom";

    // 获取%APPDATA%对应的目录（Roaming目录）
    QString appDataPath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);

    QString saveDir = QDir(appDataPath).filePath(DATA_SCRIPTS_PATH);
    QDir dir(saveDir);
    if (!dir.exists() && !dir.mkpath(".")) { qWarning() << "Failed to create directory:" << saveDir; }
    return saveDir;
}

QString CustomActionManager::getPyFilePath(const QString& actionName)
{
    return QStringLiteral("%1/%2.py").arg(getSaveDir()).arg(actionName);
}

QString CustomActionManager::getFileFullPath(const QString& filePath)
{
    QFileInfo fileInfo(filePath);
    if (!fileInfo.isAbsolute()) {
        QString fullPath = QStringLiteral("%1/%2").arg(getSaveDir()).arg(filePath);
        fullPath         = QDir::cleanPath(fullPath);
        return fullPath;
    }
    return filePath;
}

QIcon CustomActionManager::getActionIcon(const std::string& name)
{
    std::vector<CustomAction> actions = mSQLite.query_s<CustomAction>("action_name=?", name);
    if (!actions.empty()) {
        CustomAction customAction = actions.at(0);
        return getActionIcon(customAction);
    }
    return QIcon();
}

QIcon CustomActionManager::getActionIcon(const CustomAction& customAction)
{
    QIcon actionIcon;
    if (!customAction.thumbnail.empty()) {
        QPixmap pix;
        pix.loadFromData(reinterpret_cast<const uchar*>(customAction.thumbnail.data()),
                         static_cast<int>(customAction.thumbnail.size()));
        actionIcon = QIcon(pix);
    }
    else {
        actionIcon = QIcon(QString::fromUtf8(customAction.icon_path.c_str()));
    }

    if (actionIcon.isNull()) { actionIcon = QIcon(":/images/custom/icon0.svg"); }

    return actionIcon;
}

std::vector<CustomAction> CustomActionManager::queryWithSort(std::vector<CustomAction>& actions)
{
    std::sort(actions.begin(), actions.end(), [](const CustomAction& a, const CustomAction& b) {
        return a.action_index < b.action_index;
    });
    return actions;
}

std::vector<CustomAction> CustomActionManager::allCustomActions()
{
    auto actions = mSQLite.query_s<CustomAction>("");
    return queryWithSort(actions);
}

int CustomActionManager::getIndexForNewAction()
{
    int index    = -1;
    auto actions = mSQLite.query_s<CustomAction>("");
    for (const auto& action : actions) {
        if (action.action_index > index) { index = action.action_index; }
    }
    return index + 1;
}

bool CustomActionManager::insertRecord(const CustomAction& action)
{
    return mSQLite.insert(action) == 1;
}

bool CustomActionManager::insertRecords(const std::vector<CustomAction>& actions)
{
    return mSQLite.insert(actions) == actions.size();
}

bool CustomActionManager::replaceRecord(const CustomAction& action)
{
    return mSQLite.replace(action) == 1;
}

bool CustomActionManager::deleteRecord(const std::string& action_name)
{
    return mSQLite.delete_records_s<CustomAction>("action_name=?", action_name) == 1;
}

bool CustomActionManager::updateRecord(const CustomAction& action)
{
    return mSQLite.update<CustomAction>(action) == 1;
}

CustomAction CustomActionManager::findByName(const std::string& action_name)
{
    auto actions = mSQLite.query_s<CustomAction>("action_name=?", action_name);
    if (actions.empty()) { return CustomAction(); }
    return actions.at(0);
}

QString CustomActionManager::toQString(const std::string& str)
{
    return QString::fromUtf8(str.c_str());
}

std::string CustomActionManager::toString(const QString& qstr)
{
    QByteArray ba = qstr.toUtf8();
    return ba.toStdString();
}

bool CustomActionManager::isCustomIcon(const QString& path)
{
    QString prefix = ":/images/custom";
    return path.startsWith(prefix);
}

bool CustomActionManager::isCustomIcon(const std::string& path)
{
    return isCustomIcon(toQString(path));
}

QPixmap CustomActionManager::getThumbnail(const std::vector<char>& thumbnail)
{
    if (!thumbnail.empty()) {
        QByteArray byteArray(thumbnail.data(), static_cast<int>(thumbnail.size()));
        QImage image;
        if (image.loadFromData(byteArray)) { return QPixmap::fromImage(image); }
    }
    return QPixmap{};
}

std::vector<char> CustomActionManager::getThumbnail(const std::string& path)
{
    std::vector<char> thumbnail;
    QFile file(toQString(path));
    if (file.open(QIODevice::ReadOnly)) {
        QByteArray data = file.readAll();
        thumbnail       = std::vector<char>(data.begin(), data.end());
    }
    else {
        qCritical() << "Cannot load icon:" << toQString(path);
    }
    return thumbnail;
}
