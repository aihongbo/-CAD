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

#include "ConsoleHistory.h"


#define HISTORY_MAX_COUNT 20

using namespace NCTI;

ConsoleHistory::ConsoleHistory(QObject *parent)
	: QObject(parent)
	, m_index(-1)
{}
ConsoleHistory::~ConsoleHistory()
{

}

QString ConsoleHistory::previous()
{
	if (m_index+1>=m_contentList.size()) {
		return QString();
	}
	++m_index;
	return m_contentList.value(m_index);
}
QString ConsoleHistory::next()
{
	if (m_index-1<0 || m_index-1>=m_contentList.size()) {
		return QString();
	}
	--m_index;
	return m_contentList.value(m_index);
}
void ConsoleHistory::append(const QString& content)
{
	if (m_contentList.contains(content)) {
		m_contentList.removeOne(content);
	}
	m_contentList.insert(0, content);
	m_index = -1;

	if (m_contentList.size() > HISTORY_MAX_COUNT) {
		m_contentList.removeLast();
	}
}