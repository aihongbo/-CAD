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

namespace NCTI
{
	class NctiQtWebPubFunDelegate
	{
		friend class NctiQtWebPubFun;
	public:
		NctiQtWebPubFunDelegate() {}
		virtual ~NctiQtWebPubFunDelegate() {}

	protected:
		virtual QVariantMap runScript(const QString& content) = 0;
		virtual QVariantMap getChatMessage(int pageIndex, int countPerPage) = 0;
		virtual QVariantMap saveChatMessage(const QVariantList& data) = 0;
		virtual QVariantMap getChatFavorites(int pageIndex, int countPerPage) = 0;
		virtual QVariantMap saveChatFavorites(const QVariantList& data) = 0;
	};
}