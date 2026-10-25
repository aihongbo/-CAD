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

#include "NctiQtScriptDebugger.h"
#include "NctiQtScriptExecutor.h"

using namespace NCTI;

NctiQtScriptDebugger::NctiQtScriptDebugger(QObject* parent)
	: QObject(parent)
	, m_executor(nullptr)
	, m_currentBreakpointBlockNumber(-1)
	, m_executeState(ExecuteStateStopped)
{

}
NctiQtScriptDebugger::~NctiQtScriptDebugger()
{}

void NctiQtScriptDebugger::setExecutor(NctiQtScriptExecutor* executor)
{
	m_executor = executor;
}
NctiQtScriptExecutor* NctiQtScriptDebugger::getExecutor() const
{
	return m_executor;
}

// 脚本内容
const QString& NctiQtScriptDebugger::getContent() const
{
	return m_content;
}

bool NctiQtScriptDebugger::containsBreakpoint(int blockNumber) const
{
	for (auto iter = m_breakpointList.begin(); iter != m_breakpointList.end(); iter++) {
		if (iter->blockNumber == blockNumber) {
			return true;
		}
	}
	return false;
}
void NctiQtScriptDebugger::addBreakpoint(int blockNumber, bool enable)
{
	if (containsBreakpoint(blockNumber)) {
		return;
	}

	Breakpoint bp;
	bp.blockNumber = blockNumber;
	bp.enable = enable;

	for (auto iter=m_breakpointList.begin(); iter!=m_breakpointList.end(); iter++)
	{
		if (iter->blockNumber > blockNumber) {
			m_breakpointList.insert(iter, std::move(bp));
			Q_EMIT sigBreakpointAdded(blockNumber, enable);
			return;
		}
	}
	m_breakpointList.append(std::move(bp));
	Q_EMIT sigBreakpointAdded(blockNumber, enable);
}
void NctiQtScriptDebugger::removeBreakpoint(int blockNumber)
{
	auto iter = findBreakpoint(blockNumber);
	if (iter == m_breakpointList.end()) {
		return;
	}
	m_breakpointList.erase(iter);
	Q_EMIT sigBreakpointRemoved(blockNumber);
}
void NctiQtScriptDebugger::removeAllBreakpoint()
{
	m_breakpointList.clear();
}
void NctiQtScriptDebugger::enableBreakpoint(int blockNumber, bool enable)
{
	auto iter = findBreakpoint(blockNumber);
	if (iter == m_breakpointList.end() || iter->enable == enable) {
		return;
	}

	iter->enable = enable;
	Q_EMIT sigBreakpointStateChanged(blockNumber, enable);
}
void NctiQtScriptDebugger::enableAllBreakpoint(bool enable)
{
	for (auto iter = m_breakpointList.begin(); iter != m_breakpointList.end(); iter++)
	{
		if (iter->enable == enable) {
			continue;
		}
		iter->enable = enable;
		Q_EMIT sigBreakpointStateChanged(iter->blockNumber, enable);
	}
}
bool NctiQtScriptDebugger::isEnableBreakpoint(int lineNumber)
{
	return findBreakpoint(lineNumber)->enable;
}

// 下一个断点
void NctiQtScriptDebugger::runNextBreakpoint()
{
	setState(ExecuteStateRunning);
	int next = -1;
	for (auto iter = m_breakpointList.begin(); iter !=m_breakpointList.end(); iter++)
	{
		if (iter->blockNumber > m_currentBreakpointBlockNumber && iter->enable) {
			next = iter->blockNumber;
			break;
		}
	}

	if (next != 0)
	{
		QString section = m_content.section('\n', m_currentBreakpointBlockNumber < 0 ? 0 : m_currentBreakpointBlockNumber, next < 0 ? -1 : next - 1);
		if (m_executor) {
			m_executor->excuteCommand(section);
		}
	}
	setCurrentBreakpointBlockNumber(next);
	if (next<0) {
		setState(ExecuteStateStopped);
	}
}
// 下一步，如何处理命令内换行 或者 一些控制流（if for）的断点
void NctiQtScriptDebugger::runNextStep()
{
	setState(ExecuteStateRunning);
	int next = m_currentBreakpointBlockNumber + 1;
	if (next != 0) 
	{
		QString section = m_content.section('\n', m_currentBreakpointBlockNumber < 0 ? 0 : m_currentBreakpointBlockNumber, next < 0 ? -1 : next - 1);
		if (m_executor) {
			m_executor->excuteCommand(section);
		}
	}
	setCurrentBreakpointBlockNumber(next);
	if (next > m_content.count('\n')) {
		setState(ExecuteStateStopped);
	}
}
void NctiQtScriptDebugger::stop()
{
	setCurrentBreakpointBlockNumber(-1);
	setState(ExecuteStateStopped);
}

void NctiQtScriptDebugger::setCurrentBreakpointBlockNumber(int lineNumber)
{
	if (m_currentBreakpointBlockNumber == lineNumber) {
		return;
	}
	int previous = m_currentBreakpointBlockNumber;
	m_currentBreakpointBlockNumber = lineNumber;
	Q_EMIT sigCurrentBreakpointChanged(previous, m_currentBreakpointBlockNumber);
}
int NctiQtScriptDebugger::getCurrentBreakpointBlockNumber() const
{
	return m_currentBreakpointBlockNumber;
}

QList<NctiQtScriptDebugger::Breakpoint>::Iterator NctiQtScriptDebugger::findBreakpoint(int blockNumber)
{
	for (auto iter = m_breakpointList.begin(); iter != m_breakpointList.end(); iter++) {
		if (iter->blockNumber == blockNumber) {
			return iter;
		}
	}
	return m_breakpointList.end();
}
void NctiQtScriptDebugger::setState(ExecuteState state)
{
	if (m_executeState == state) {
		return;
	}
	m_executeState = state;
	Q_EMIT sigExecuteStateChanged(state);
}
