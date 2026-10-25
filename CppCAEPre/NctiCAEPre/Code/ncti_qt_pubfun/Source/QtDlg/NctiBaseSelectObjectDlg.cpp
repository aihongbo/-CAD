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

#include "NctiBaseSelectObjectDlg.h"

#include "NctiDocElementPubFun.h"
using namespace NCTI;

NctiBaseSelectObjectDlg::NctiBaseSelectObjectDlg(NctiDocument* i_pDocument, QWidget* i_parent)
	: QWidget(i_parent)
	, m_Document(i_pDocument)
	, m_selBody(false)
	, m_selFace(false)
	, m_selLine(false)
	, m_selMarker(false)
	, m_SelMode(0)
{
}

NctiBaseSelectObjectDlg::~NctiBaseSelectObjectDlg()
{
}

void NctiBaseSelectObjectDlg::show()
{
	QWidget::show();
	NctiDocElementPubFun::CancelSelection(m_Document);
	InitSelMode();
}

void NctiBaseSelectObjectDlg::InitSelMode()
{
	if (m_Document == nullptr)
		return;
	//NctiDocElementPubFun::CancelSelection(m_Document);
	NctiDocElementPubFun::GetSelectMode(m_Document, m_selBody, m_selFace, m_selLine, m_selMarker);
	//重设为选择对象
	NctiDocElementPubFun::SetSelectBody(m_Document, m_SelMode & SelectMode::Body);
	NctiDocElementPubFun::SetSelectFace(m_Document, m_SelMode & SelectMode::Face);
	NctiDocElementPubFun::SetSelectLine(m_Document, m_SelMode & SelectMode::Line);
	NctiDocElementPubFun::SetSelectMarker(m_Document, m_SelMode & SelectMode::Marker);
}

void NctiBaseSelectObjectDlg::rollSelMode()
{
	NctiDocElementPubFun::SetSelectBody(m_Document, m_selBody);
	NctiDocElementPubFun::SetSelectFace(m_Document, m_selFace);
	NctiDocElementPubFun::SetSelectLine(m_Document, m_selLine);
	NctiDocElementPubFun::SetSelectMarker(m_Document, m_selMarker);
}

void NctiBaseSelectObjectDlg::onCanle()
{
	close();
	NctiDocElementPubFun::CancelSelection(m_Document);
	rollSelMode();
}
