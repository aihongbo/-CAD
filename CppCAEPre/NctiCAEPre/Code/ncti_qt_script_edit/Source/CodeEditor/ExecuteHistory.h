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
	class ExecuteHistory
	{
	private:
		ExecuteHistory();
	public:
		~ExecuteHistory();

		static ExecuteHistory* instance();

		void config(const QString &path);

		QStringList names() const;
		void add(const QString& content, const QString &name=QString());
		QString get(int index = 0) const;

	private:
		void init();
		void writeToFile(const QString &content, const QString &name);
		QString readFromFile(int index) const;
		void readHistory();
		void writeHistory();

	private:
		QString m_historyFilePath;
		QStringList m_historyItemFilePathList;
	};
};