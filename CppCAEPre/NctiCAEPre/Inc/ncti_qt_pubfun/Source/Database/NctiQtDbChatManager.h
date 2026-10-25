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

#ifdef NCTI_ENABLE_AIQA_SERVICE

#include <QString>
#include <QVariantList>
#include <QSqlDatabase>
#include <QSqlQuery>

namespace NCTI
{
	class NctiQtDbChatManager
	{
	public:
		NctiQtDbChatManager(const QString &path);
		~NctiQtDbChatManager();

		Q_DISABLE_COPY_MOVE(NctiQtDbChatManager);

		QVariantList getChatMessage(int pageIndex, int countPerPage);
		bool saveChatMessage(const QVariantList& data);

		QVariantList getChatFavorites(int pageIndex, int countPerPage);
		bool saveChatFavorites(const QVariantList& data);

	private:
		void open();
		void close();
		QSqlDatabase getConnection();
		void initTable();

	private:
		QString m_Path;
	};
};
#endif