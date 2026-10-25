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

#include "NctiRemoveFeaturesDlg.h"

#include <QString>

#include "NctiDocElementPubFun.h"
#include "NctiCommandManager.h"
#include "NctiArgumentObject.h"
#include "NctiDocument.h"
using namespace NCTI;

NCTI::NctiRemoveFeaturesDlg::NctiRemoveFeaturesDlg(NctiDocument* i_pDocument, QWidget* i_parent)
	:QWidget(i_parent)
	, m_ui(new Ui::NctiRemoveFeaturesDlg())
	, m_Document(i_pDocument)
	, m_selBody(false)
	, m_selFace(false)
	,m_selLine(false)
	,m_selMarker(false)
{
	m_ui->setupUi(this);
	this->setFixedSize(this->geometry().size());
	this->setWindowFlags(Qt::MSWindowsFixedSizeDialogHint | Qt::Dialog);
	this->setWindowModality(Qt::NonModal);//非模态
	setWindowTitle("RemoveFeatures");
 	connect(m_ui->pick_obj_bnt, SIGNAL(clicked()), this, SLOT(GetSelection()));
 	connect(m_ui->pushButton_ok, SIGNAL(clicked()), this, SLOT(onOK()));
 	connect(m_ui->pushButton_cancel, SIGNAL(clicked()), this, SLOT(onCanle()));
}

NCTI::NctiRemoveFeaturesDlg::~NctiRemoveFeaturesDlg()
{
	NCTI_DELETE m_ui;
}

void NCTI::NctiRemoveFeaturesDlg::onOK()
{
	if(m_Document && m_displayobj.size() > 0)
	{
		NctiBaseModel* pBaseModel = m_Document->GetBaseModel();
		NctiCommandManager* pComMan = NctiCommandManager::GetCommandManager(pBaseModel);
		if (pComMan)
		{
			NctiArgumentObject argumentObject;
			argumentObject.SetCellVec(m_cells);
			std::vector<NctiDisplayObject*> disObjs;
			for (int i = 0; i < m_displayobj.size(); i++)
			{
				if (std::find(disObjs.begin(), disObjs.end(), m_displayobj[i])!= disObjs.end())
					continue;
				disObjs.push_back(m_displayobj[i]);
			}
			if (disObjs.size() == 1)
			{
				argumentObject.SetDisplayObject1(disObjs[0]);
				EnumNctiResult result = pComMan->RunCommand("cmd_ncti_remove_features", &argumentObject);
			}
		}
	}
	close();
	NctiDocElementPubFun::CancelSelection(m_Document);
	rollSelMode();
}

void NctiRemoveFeaturesDlg::rollSelMode()
{
	NctiDocElementPubFun::SetSelectBody(m_Document, m_selBody);
	NctiDocElementPubFun::SetSelectFace(m_Document, m_selFace);
	NctiDocElementPubFun::SetSelectLine(m_Document, m_selLine);
	NctiDocElementPubFun::SetSelectMarker(m_Document, m_selMarker);
}

void NctiRemoveFeaturesDlg::InitSelMode()
{
	if (m_Document == nullptr)
		return;
	//NctiDocElementPubFun::CancelSelection(m_Document);
	NctiDocElementPubFun::GetSelectMode(m_Document, m_selBody, m_selFace, m_selLine, m_selMarker);
	//重设为选择对象
	NctiDocElementPubFun::SetSelectBody(m_Document, false);
	NctiDocElementPubFun::SetSelectFace(m_Document, true);
	NctiDocElementPubFun::SetSelectLine(m_Document, false);
	NctiDocElementPubFun::SetSelectMarker(m_Document, false);
}

void NctiRemoveFeaturesDlg::onCanle()
{
	close();
	NctiDocElementPubFun::CancelSelection(m_Document);
	rollSelMode();
}

void NctiRemoveFeaturesDlg::GetSelection()
{
	if (m_Document)
	{
		NctiDocElementPubFun::GetDisplayObjectFromSelManager(m_Document, m_displayobj, m_cells);
		Ncti_Integer nCount = m_displayobj.size();
		
		QString strSel = QString("已选择%1个面").arg(nCount);
		m_ui->pick_obj_lab->setText(strSel);
		if (nCount == 0)
		{
			m_ui->pick_obj_lab->setStyleSheet("color: red;");
		//	m_ui->pick_obj_bnt->setStyleSheet("color: red;");
		}
		else
		{
			m_ui->pick_obj_lab->setStyleSheet("color: green;");
		///	m_ui->pick_obj_bnt->setStyleSheet("color: green;");
		}
		
	}
}

void NctiRemoveFeaturesDlg::show()
{
 	QWidget::show();
	InitSelMode();
// 	GetCurrentSelMode();
// 
// 	UpdateCtl();
}

