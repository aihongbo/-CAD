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

#ifdef NCTI_ENABLE_AIQA_SERVICE

#include "NctiQtDbChatManager.h"
#include <QSqlDatabase>
#include <mutex>
#include <QDebug>
#include <QSqlError>

constexpr const char* KEY_chat_msg = "chat_msg";
constexpr const char* KEY_chat_fav = "chat_fav";
constexpr const char* KEY_ts = "ts";
constexpr const char* KEY_msgID = "msgID";
constexpr const char* KEY_askID = "askID";
constexpr const char* KEY_favID = "favID";
constexpr const char* KEY_isAsk = "isAsk";
constexpr const char* KEY_content = "content";
constexpr const char* KEY_askTs = "askTs";
constexpr const char* KEY_askContent = "askContent";

namespace NCTI
{
	NctiQtDbChatManager::NctiQtDbChatManager(const QString& path)
		: m_Path(path)
	{
		open();
		static std::once_flag once;
		std::call_once(once, [this] {
				initTable();
			});
	}
	NctiQtDbChatManager::~NctiQtDbChatManager()
	{
		close();
	}

	QVariantList NctiQtDbChatManager::getChatMessage(int pageIndex, int countPerPage)
	{
		QSqlQuery query(getConnection());
		query.prepare(QString("SELECT * FROM %1 ORDER BY %2 DESC LIMIT :limit OFFSET :offset")
			.arg(KEY_chat_msg).arg(KEY_msgID));
		query.bindValue(":limit", countPerPage);
		query.bindValue(":offset", pageIndex*countPerPage);

		if (!query.exec()) {
			qDebug() << "Query failed:" << query.lastError().text();
			return {};
		}
		QVariantList list;
		while (query.next())
		{
			QVariantMap map = {
				{KEY_ts,query.value(KEY_ts).toLongLong()},
				{KEY_msgID,query.value(KEY_msgID).toLongLong()},
				{KEY_askID,query.value(KEY_askID).toLongLong()},
				{KEY_isAsk,query.value(KEY_isAsk).toBool()},
				{KEY_content,query.value(KEY_content).toByteArray()},
			};
			list << std::move(map);
		}

		return list;
	}
	bool NctiQtDbChatManager::saveChatMessage(const QVariantList& data)
	{
		auto db = getConnection();
		if (!db.transaction()) {
			return false;
		}

		QSqlQuery query(db);
		query.prepare(QString("INSERT INTO %1 (%2, %3, %4, %5, %6) VALUES (:ts, :msgID, :askID, :isAsk, :content)")
			.arg(KEY_chat_msg).arg(KEY_ts).arg(KEY_msgID).arg(KEY_askID).arg(KEY_isAsk).arg(KEY_content));

		for (auto iter = data.begin(); iter!=data.end(); iter++)
		{
			QVariantMap map = iter->toMap();
			query.bindValue(":ts", map.value(KEY_ts));
			query.bindValue(":msgID", map.value(KEY_msgID));
			query.bindValue(":askID", map.value(KEY_askID));
			query.bindValue(":isAsk", map.value(KEY_isAsk));
			query.bindValue(":content", map.value(KEY_content));
			query.exec();
		}

		if (!db.commit()) {
			return false;
		}
		return true;
	}

	QVariantList NctiQtDbChatManager::getChatFavorites(int pageIndex, int countPerPage)
	{
		QSqlQuery query(getConnection());
		query.prepare(QString(R"(
SELECT chat_msg.content AS askContent, chat_msg.ts AS askTs, chat_fav.content, chat_fav.askID
FROM chat_fav
LEFT JOIN chat_msg ON chat_msg.msgID = chat_fav.askID
ORDER BY chat_fav.askID DECS chat_fav.favID DECS
LIMIT :limit OFFSET ;offset)"));
		query.bindValue(":limit", countPerPage);
		query.bindValue(":offset", pageIndex * countPerPage);

		if (!query.exec()) {
			qDebug() << "Query failed:" << query.lastError().text();
			return {};
		}
		QVariantList data;

		qint64 currentAskID = -1;
		QVariantMap currentFavMap;
		QStringList currentFavContent;

		while (query.next())
		{
			auto askID = query.value(KEY_askID).toLongLong();
			if (currentAskID != askID)
			{
				if (currentAskID != -1)
				{
					currentFavMap.insert(KEY_content, std::move(currentFavContent));
					data.append(std::move(currentFavMap));
					currentFavContent = QStringList();
				}

				currentFavMap = {
					{KEY_askTs,query.value(KEY_askTs)},
					{KEY_askID,query.value(KEY_askID)},
					{KEY_askContent,query.value(KEY_askContent)},
				};
			}
	
			currentFavContent << query.value(KEY_content).toString();
		}

		if (-1 != currentAskID)
		{
			currentFavMap.insert(KEY_content, std::move(currentFavContent));
			data.append(std::move(currentFavMap));
		}
		return data;
	}
	bool NctiQtDbChatManager::saveChatFavorites(const QVariantList& data)
	{
		auto db = getConnection();
		if (!db.transaction()) {
			return false;
		}

		QSqlQuery query(db);
		query.prepare(QString("INSERT INTO %1 (%2, %3, %4) VALUES (:askID, :favID, :content)")
			.arg(KEY_chat_fav).arg(KEY_askID).arg(KEY_favID).arg(KEY_content));

		for (auto iter = data.begin(); iter != data.end(); iter++)
		{
			QVariantMap map = iter->toMap();
			query.bindValue(":askID", map.value(KEY_askID));
			query.bindValue(":favID", map.value(KEY_favID));
			query.bindValue(":content", map.value(KEY_content));
			query.exec();
		}

		if (!db.commit()) {
			return false;
		}
		return true;
	}

	void NctiQtDbChatManager::open()
	{
		auto db = QSqlDatabase::addDatabase("QSQLITE", "NctiQtDbChatManager");
		db.setDatabaseName(m_Path);
	}
	QSqlDatabase NctiQtDbChatManager::getConnection()
	{
		return QSqlDatabase::database("NctiQtDbChatManager");
	}
	void NctiQtDbChatManager::close()
	{
		QSqlDatabase::removeDatabase("NctiQtDbChatManager");
	}
	void NctiQtDbChatManager::initTable()
	{
		QSqlQuery query(getConnection());
		query.exec(QString(R"(
				CREATE TABLE IF NOT EXISTS %1 (
					%2 INTEGER PRIMARY KEY,
					%3 INTEGER NOT NULL,
					%4 INTEGER NOT NULL,
					%5 BOOLEAN NOT NULL, 
					%6 TEXT
				))").arg(KEY_chat_msg).arg(KEY_msgID).arg(KEY_askID).arg(KEY_ts).arg(KEY_isAsk).arg(KEY_content));
		query.exec(QString(R"(
				CREATE TABLE IF NOT EXISTS %1 (
					%2 INTEGER PRIMARY KEY,
					%3 INTEGER NOT NULL,
					%4 INTEGER NOT NULL,
					%5 TEXT
				))").arg(KEY_chat_fav).arg(KEY_favID).arg(KEY_askID).arg(KEY_ts).arg(KEY_content));
	}
};

#endif