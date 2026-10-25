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

#include "NctiQtScriptExecutor.h"

#include "NctiPythonTool.h"
using namespace NCTI;

NctiQtScriptExecutor::NctiQtScriptExecutor(QObject* parent)
	: QObject(parent)
	, m_state(ExecuteState::ExecuteStateStopped)
{

}

NctiQtScriptExecutor::~NctiQtScriptExecutor()
{

}

void NctiQtScriptExecutor::excuteCommand(const QString& content, bool re)
{
	//Q_EMIT signalMessage(QString("%1").arg(content), NctiQtScriptExecutor::MessageTypeCode);

	if (content.compare("CLEAR", Qt::CaseInsensitive) == 0)
	{
        Q_EMIT signalClear();
	}
	else if (content.compare("ZOOM", Qt::CaseInsensitive) == 0)
	{
        Q_EMIT signalZoom();
	}
	else
	{
		excuteScript(content);
		if (re && getStderrtMessage().isEmpty() && getStdoutMessage().isEmpty()) {
			signalMessage(QStringLiteral("执行完成"), NctiQtScriptExecutor::MessageTypeLog);
			signalMessage("", NctiQtScriptExecutor::MessageTypeNewLine);
		}
	}
}

void NctiQtScriptExecutor::excuteScript(const QString& content)
{
	setState(ExecuteStateRunning);
	m_stdoutMessage.clear();
	m_stderrMessage.clear();
	QByteArray bCmd = content.toUtf8();

	std::string outputStr, errorStr;
	NctiPythonTool::ExcuteScript(bCmd.data(), outputStr, errorStr);
	m_stdoutMessage = QString::fromUtf8(outputStr.c_str());
	m_stderrMessage = QString::fromUtf8(errorStr.c_str());
	if (!m_stdoutMessage.isEmpty())
	{
		Q_EMIT signalMessage(m_stdoutMessage);
	}
	if (!m_stderrMessage.isEmpty())
	{
		Q_EMIT signalMessage(m_stderrMessage, MessageTypeError);
	}
	setState(ExecuteStateStopped);
	if (!m_stdoutMessage.isEmpty() || !m_stderrMessage.isEmpty())
	{
		Q_EMIT signalMessage("", MessageTypeNewLine);
	}
}

void NctiQtScriptExecutor::setState(ExecuteState state)
{
	if (m_state == state) {
		return;
	}
	m_state = state;
	Q_EMIT sigStateChanged(state);
}

NctiQtScriptExecutor::ExecuteState NctiQtScriptExecutor::getState() const
{
	return m_state;
}