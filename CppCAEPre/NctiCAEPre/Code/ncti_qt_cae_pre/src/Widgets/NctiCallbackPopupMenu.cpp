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

#include "NctiCallbackPopupMenu.h"

using namespace NCTI;

#include <QDebug>
#include <QMenu>
#include <QAction>
#include <QString>

#include "NctiCommandManager.h"
#include "NctiTool.h"
#include "NctiDocument.h"
#include "NctiHandler.h"
#include "NctiContextMenu.h"
#include "NctiBaseModel.h"
#include "NctiDisplayObject.h"
#include "ncti_object_def.h"

NCTI::NctiCallbackPopupMenu::NctiCallbackPopupMenu(QWidget* i_pQWidget, NctiDocument* pDoc)
    : m_QWidget(i_pQWidget)
    , m_pDocument(pDoc)
    , m_DisplayObj(nullptr)
{
}

NctiCallbackPopupMenu::~NctiCallbackPopupMenu()
{

}

void NctiCallbackPopupMenu::Execute()
{
	if (m_paMenuInfo == nullptr)
	{
		return;
	}

    std::vector<CallbackMenuData> vMenuData;
	for (Ncti_Integer i = 0; i < m_iNumItem; i++)
	{
		NctiMenuInfo* pMenuInfo = m_paMenuInfo[i];
        if (pMenuInfo) {
            //NCTI_MENU_SEPARATOR，是下划线，text为空
            CallbackMenuData menuData;
            menuData.id = pMenuInfo->GetMenuValue();
            menuData.parent_id = pMenuInfo->GetParentValue();
            menuData.text = pMenuInfo->GetMenuText();
            //qDebug() << "MenuInfo id: " << menuData.id << ", parent_id: " << menuData.parent_id << ", text:" << menuData.text;
            if (!insertMenuData(vMenuData, menuData)) {
                vMenuData.push_back(menuData);
            }
        }
	}

    NctiContextMenu* qMenu = new NctiContextMenu(m_QWidget);
    qMenu->setMinimumWidth(182);
    qMenu->setAttribute(Qt::WA_DeleteOnClose);
    qMenu->setObjectName("callbackPopupMenu");
    createPopupMenu(qMenu, vMenuData);
    QPoint globalPos = QCursor::pos();
    qMenu->exec(globalPos);
    m_DisplayObj = nullptr;
}

bool NctiCallbackPopupMenu::insertMenuData(std::vector<CallbackMenuData>& vMenuData
    , const CallbackMenuData& menuData)
{
    for (auto& v : vMenuData) {
        if (menuData.parent_id < 0) {
            return false;
        }
        if (v.id == menuData.parent_id) {
            v.menuData.push_back(menuData);
            return true;
        }
        if (insertMenuData(v.menuData, menuData)) {
            return true;
        }
    }
    return false;
}

void NctiCallbackPopupMenu::createPopupMenu(QMenu* menu, const std::vector<CallbackMenuData>& vMenuData)
{
    for (auto& v : vMenuData) {
        if (v.menuData.empty()) {
            if (v.text.isEmpty()) {
                menu->addSeparator();
            }
            else {
                QAction* action = new QAction(QIcon(getMenuItemIconUrl(v.id)), v.text, m_QWidget);
                action->setData(v.id);
                connect(action, SIGNAL(triggered()), this, SLOT(onMenuItemClicked()));
                menu->addAction(action);
            }
        }
        else {
            NctiContextMenu* subMenu = new NctiContextMenu(m_QWidget);
            subMenu->setMinimumWidth(132);
            subMenu->setTitle(v.text);
            subMenu->setIcon(QIcon(getMenuItemIconUrl(v.id)));
            createPopupMenu(subMenu, v.menuData);
            menu->addMenu(subMenu);
        }
    }
}


QString NCTI::NctiCallbackPopupMenu::getMenuItemIconUrl(Ncti_Integer i_id)
{
    if (NCTI_POP_MENU_HIDE == i_id) { return QString(":/ContextMenu/hide.svg");}
    if (NCTI_POP_MENU_SHOW == i_id) { return QString(":/ContextMenu/show.svg"); }
    if (NCTI_POP_MENU_SELECT_FACE == i_id) { return QString(":/ContextMenu/selectface.svg"); }
    if (NCTI_POP_MENU_SELECT_LINE == i_id) { return QString(":/ContextMenu/selectedge.svg"); }
    if (NCTI_POP_MENU_SELECT_MARKER == i_id) { return QString(":/ContextMenu/selectpoint.svg"); }
    if (NCTI_POP_MENU_SELECT_BODY == i_id) { return QString(":/ContextMenu/selectbody.svg"); }
    if (NCTI_POP_MENU_LOOP_FACE == i_id) { return QString(":/ContextMenu/search_innerloop.svg"); }
    if (NCTI_POP_MENU_CONNEC_TFACE == i_id) { return QString(":/ContextMenu/search_connection.svg"); }
    if (NCTI_POP_MENU_NO_PLANE_CONNECT_FACE == i_id) { return QString(":/ContextMenu/nonplanar_connection.svg"); }
    if (NCTI_POP_MENU_DELETE == i_id) { return QString(":/ContextMenu/delete.svg"); }
    if (NCTI_POP_MENU_MEASURE == i_id) { return QString(":/ContextMenu/measure.svg"); }
    if (NCTI_POP_MENU_GET_POINT == i_id) { return QString(":/ContextMenu/point.svg"); }
    if (NCTI_POP_MENU_GET_LENGTH == i_id) { return QString(":/ContextMenu/length.svg"); }
    if (NCTI_POP_MENU_GET_MIDPOSITION == i_id) { return QString(":/ContextMenu/midpoint.svg"); }
    if (NCTI_POP_MENU_GET_CENTE == i_id) { return QString(":/ContextMenu/circlepoint.svg"); }
    if (NCTI_POP_MENU_GET_RADIUS == i_id) { return QString(":/ContextMenu/radius.svg"); }
    if (NCTI_POP_MENU_GET_VECTOR == i_id) { return QString(":/ContextMenu/vector.svg"); }
    if (NCTI_POP_MENU_GET_ANGLE == i_id) { return QString(":/ContextMenu/angle.svg"); }
    return QString(":/ContextMenu/preview.svg");
}

void NctiCallbackPopupMenu::onMenuItemClicked()
{
    QAction* action = qobject_cast<QAction*>(sender());
    if (!action) {
        return;
    }
    int id = action->data().toInt();
    SetValue(id);
    if (m_DisplayObj != nullptr)
    {
        m_DisplayObj->Callback(m_pDocument->GetBaseModel()->GetActiveBaseView(), NCTI_DO_CALLBACK_PROCESS_CONTEXT_MENU, nullptr);
        return;
    }
    EnumNctiResult result = NCTI_FAILED;
    NctiCommandManager* pComMgr = NctiCommandManager::GetCommandManager(m_pDocument->GetBaseModel());
    if (pComMgr) {
        NctiTool* pTool = pComMgr->GetActiveTool();
        if (pTool) {
            result = pTool->ProcessContextMenu(NCTI_PROCESS_MENU);
        }
    }
}

void NctiCallbackPopupMenu::RunMenu(const char* psMenuName)
{
    //if (psMenuName) {
    //    qDebug() << "RunMenu: " << psMenuName;
    //}
}

NCTI::NctiMenuInfo** NctiCallbackPopupMenu::GetMenuInfo()
{
	return m_paMenuInfo;
}

int NctiCallbackPopupMenu::GetNumItems()
{
	return m_iNumItem;
}



