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

#include "SelectModeRoller.h"
#include <QEvent>
#include <QDebug>

#include "NctiDocElementPubFun.h"
#include "NctiDocument.h"

namespace NCTI {
SelectModeRoller::SelectModeRoller(NctiDocument* i_pDocument, int mode, QObject* parent)
    : QObject(parent)
    , m_doc(i_pDocument)
    , m_mode(mode)
{
    if (parent != nullptr) {
        parent->installEventFilter(this);
    }
}

SelectModeRoller::~SelectModeRoller()
{
}

bool SelectModeRoller::eventFilter(QObject* w, QEvent* e)
{
    if (w == parent()) {
        if (e->type() == QEvent::Show) {
            initMode();
        }
        else if (e->type() == QEvent::DeferredDelete) {
            restoreMode();
        }
    }
    return QObject::eventFilter(w, e);
}

void SelectModeRoller::initMode()
{
    if (m_doc == nullptr ||m_doc->GetBaseModel() == nullptr || m_inited)
        return;
    m_inited = true;

    //NctiDocElementPubFun::CancelSelection(m_Document);
    NctiDocElementPubFun::GetSelectMode(m_doc, m_selBody, m_selFace, m_selLine, m_selMarker);
    //重设为选择对象
    NctiDocElementPubFun::SetSelectBody(m_doc, m_mode & SelectMode::Body);
    NctiDocElementPubFun::SetSelectFace(m_doc, m_mode & SelectMode::Face);
    NctiDocElementPubFun::SetSelectLine(m_doc, m_mode & SelectMode::Line);
    NctiDocElementPubFun::SetSelectMarker(m_doc, m_mode & SelectMode::Marker);
}

void SelectModeRoller::restoreMode()
{
    if (m_doc == nullptr || m_doc->GetBaseModel() == nullptr || m_restored)
        return;
    m_restored = true;

    NctiDocElementPubFun::CancelSelection(m_doc);
    NctiDocElementPubFun::SetSelectBody(m_doc, m_selBody);
    NctiDocElementPubFun::SetSelectFace(m_doc, m_selFace);
    NctiDocElementPubFun::SetSelectLine(m_doc, m_selLine);
    NctiDocElementPubFun::SetSelectMarker(m_doc, m_selMarker);
}

} // namespace NCTI
