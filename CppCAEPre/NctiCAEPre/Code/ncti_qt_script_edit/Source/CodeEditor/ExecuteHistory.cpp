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

#include "ExecuteHistory.h"
#include "QDir"
#include <QJsonDocument>
#include <QVariant>
#include <QDateTime>
#include <QCoreApplication>

#define HISTORY_MAX_COUNT 10

using namespace NCTI;
ExecuteHistory::ExecuteHistory()
{
	config(QDir(QCoreApplication::applicationDirPath()).filePath("scriptdata/exechistory.json"));
}

ExecuteHistory::~ExecuteHistory()
{}

ExecuteHistory* ExecuteHistory::instance()
{
	static ExecuteHistory* m_instance = new ExecuteHistory;
	return m_instance;
}

void ExecuteHistory::config(const QString& path)
{
    if (!path.isEmpty()) {
        m_historyFilePath = path;
        QDir().mkpath(QFileInfo(m_historyFilePath).absolutePath());
        init();
    }
}

QStringList ExecuteHistory::names() const
{
	QStringList n;
	for (int index=0; index<m_historyItemFilePathList.count(); ++index)
	{
		n << QFileInfo(m_historyItemFilePathList[index]).fileName();
		/*QFileInfo fileinfo(m_historyItemFilePathList[index]);
		auto&& dt = QDateTime::fromString(fileinfo.completeBaseName(), "yyyy.MM.dd HH.mm.ss.zzz");
		if (dt.isValid()) {
			n << dt.toString("yyyy-MM-dd HH:mm:ss.zzz");
		}
		else {
			n << fileinfo.fileName();
		}*/
	}
	return n;
}
void ExecuteHistory::add(const QString& content, const QString& name)
{
	QString last = get(0);
	if (last.compare(content)!=0) {
		writeToFile(content, name);
		writeHistory();
	}
	
}
QString ExecuteHistory::get(int index) const
{
	return readFromFile(index);
}

void ExecuteHistory::init()
{
	readHistory();
}

void ExecuteHistory::readHistory()
{
	m_historyItemFilePathList.clear();

	QFile file(m_historyFilePath);
	if (file.open(QIODevice::ReadOnly)) 
	{
		auto&& bytes = file.readAll();
		file.close();

		QJsonParseError error;
		auto&& jDoc = QJsonDocument::fromJson(bytes, &error);
		if (error.error == QJsonParseError::NoError) {
			m_historyItemFilePathList = jDoc.toVariant().toStringList();
		}
	}

	// 将上一个的NctiScriptTextEdit加入
	if (m_historyItemFilePathList.isEmpty() 
        || (m_historyItemFilePathList.size() < HISTORY_MAX_COUNT && !m_historyItemFilePathList.last().contains("NctiScriptTextEdit.py")))
	{
		auto path = QDir(QCoreApplication::applicationDirPath()).filePath("NctiScriptTextEdit.py");
		if (QFileInfo(path).exists()) {
			m_historyItemFilePathList.append(path);
		}
	}
}
void ExecuteHistory::writeHistory()
{
	QVariantList temp;
	for (size_t i = 0; i < m_historyItemFilePathList.length(); i++)
	{
		temp.append(m_historyItemFilePathList[i].toUtf8());
	}
	auto&& bytes = QJsonDocument::fromVariant(temp).toJson(QJsonDocument::Indented);

	QFile file(m_historyFilePath);
	if (!file.open(QIODevice::ReadWrite | QIODevice::Truncate)) {
		return;
	}

	file.write(bytes);
	file.close();
}
void ExecuteHistory::writeToFile(const QString& content, const QString &name)
{
	QString filename = QDateTime::currentDateTime().toString("yyyy.MM.dd HH.mm.ss.zzz") + ".py";
	if (!name.isEmpty()) 
	{
		int suffix = 1;
		QDir dir = QFileInfo(m_historyFilePath).dir();
		QString nameloop = name;
		while (dir.exists(nameloop)) {
			nameloop = name;
			auto index = nameloop.lastIndexOf('.');
			if (index != -1) {
				nameloop.insert(index, QString("_%1").arg(suffix));
			}
			else {
				nameloop.append(QString("_%1").arg(suffix));
			}
			++suffix;
		}
		filename = nameloop;
	}

	QString filepath = QFileInfo(m_historyFilePath).dir().filePath(filename);
	QFile file(filepath);
	if (!file.open(QIODevice::ReadWrite | QIODevice::Truncate)) {
		return;
	}
	file.write(content.toUtf8());
	file.close();

	m_historyItemFilePathList.insert(0, filepath);
	auto dirPath = QFileInfo(m_historyFilePath).absolutePath();
	while (m_historyItemFilePathList.size() > HISTORY_MAX_COUNT)
	{
		auto&& path = m_historyItemFilePathList.takeLast();
		QFileInfo fileInfo(path);
		if (!path.isEmpty() && fileInfo.isFile() && fileInfo.absolutePath() == dirPath) {
			QFile(path).remove();
		}
	}
}
QString ExecuteHistory::readFromFile(int index) const
{
	if (index<0 || index>=m_historyItemFilePathList.size()) {
		return QString();
	}

	QFile file(m_historyItemFilePathList.value(index));
	if (!file.open(QIODevice::ReadOnly)) {
		return QString();
	}

	return QString::fromUtf8(file.readAll());
}