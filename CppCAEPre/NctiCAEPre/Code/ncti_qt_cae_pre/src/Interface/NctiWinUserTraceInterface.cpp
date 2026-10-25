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

#include "NctiWinUserTraceInterface.h"
#include "mainwindow.h"
#include "ObjectTreeManager.h"

#include "NctiSelectionManager.h"
#include "NctiSelectionDataList.h"
#include "NctiSelKeyDo.h"
#include "NctiDisplayDocCustomContainer.h"
#include "NctiUserInterfaceManager.h"

#include <QDebug>

using namespace NCTI;

NctiWinUserTraceInterface::NctiWinUserTraceInterface(MainWindow* i_pMain)
	: NctiSPUserTraceInterface(nullptr)
	, m_MainWindow(i_pMain)
{

}

NCTI::NctiWinUserTraceInterface::~NctiWinUserTraceInterface()
{

}

void NctiWinUserTraceInterface::UndoAndRedoEnd()
{
    m_MainWindow->getObjectTreeMgr()->UpdateTree();
}

void NctiWinUserTraceInterface::UndoAndRedoStart()
{
    m_MainWindow->getObjectTreeMgr()->UpdateTree();
}

void NctiWinUserTraceInterface::NotifySelectionDataChanged()
{
	NctiSelectionManager* pSelMan = NctiSelectionManager::GetSelectionManager(m_UserInterfaceManager);
	NctiSelectionDataList listSelected;
	pSelMan->GetSelected(listSelected, NctiSelKeyDo::ID);
	listSelected.Init();
	NctiSelKeyDo* pSelKeyDo = nullptr;
	//NctiCallBackManager* pCallBackManager = NctiCallBackManager::instance();
	NctiDisplayDocCustomContainer* pDocCus = nullptr;
	std::vector<NCTI_MODEL_TAG> ModelBodyVec;
	std::vector<NctiDisplayObject*> DisplayGModelObjectVec;

    QStringList selectItems;
	while ((pSelKeyDo = (NctiSelKeyDo*)listSelected.Next()) != nullptr)
	{
        if (pSelKeyDo) {
            NctiDisplayObject* pDo = pSelKeyDo->GetDoOriginal();
            if (pDo) {
                selectItems.append(pDo->GetObjName());
            }
        }
	}

    m_MainWindow->getObjectTreeMgr()->selectTreeItems(selectItems);
}

void NctiWinUserTraceInterface::HistoryIsEndByFailed()
{
    m_MainWindow->getObjectTreeMgr()->UpdateTree();
}

void NctiWinUserTraceInterface::HistoryIsEndBySucceeded()
{
    m_MainWindow->getObjectTreeMgr()->UpdateTree();
}

void NctiWinUserTraceInterface::ElementTreeIsChanged(NctiDocViewManager* pDocView)
{
	m_MainWindow->getObjectTreeMgr()->SetTreeIsModify(true);
}
