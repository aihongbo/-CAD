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

#include "NctiSplitFacesDlg.h"

#include <QString>

#include "NctiDocElementPubFun.h"
#include "NctiCommandManager.h"
#include "NctiArgumentObject.h"
#include "NctiDocument.h"
using namespace NCTI;

NCTI::NctiSplitFacesDlg::NctiSplitFacesDlg(NctiDocument* i_pDocument, QWidget* i_parent)
	:NctiBaseSelectObjectDlg(i_pDocument, i_parent)
	, m_ui(new Ui::NctiSplitFaces())
{
	m_ui->setupUi(this);
	this->setFixedSize(this->geometry().size());
	this->setWindowFlags(Qt::MSWindowsFixedSizeDialogHint | Qt::Dialog);
	this->setWindowModality(Qt::NonModal);//非模态
	setWindowTitle("SplitFeatures");
	connect(m_ui->pick_obj_bnt, SIGNAL(clicked()), this, SLOT(GetSelection()));
	connect(m_ui->pushButton_ok, SIGNAL(clicked()), this, SLOT(onOK()));
	connect(m_ui->pushButton_cancel, SIGNAL(clicked()), this, SLOT(onCanle()));

	m_SelMode = SelectMode::Face;
}

NCTI::NctiSplitFacesDlg::~NctiSplitFacesDlg()
{
	NCTI_DELETE m_ui;
}

void NCTI::NctiSplitFacesDlg::onOK()
{
	if (m_Document && m_displayobj.size() > 0)
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
				if (std::find(disObjs.begin(), disObjs.end(), m_displayobj[i]) != disObjs.end())
					continue;
				disObjs.push_back(m_displayobj[i]);
			}
			if (disObjs.size() == 1)
			{
				argumentObject.SetDisplayObject1(disObjs[0]);
				EnumNctiResult result = pComMan->RunCommand("cmd_ncti_split_faces", &argumentObject);
			}
		}
	}
	close();
	NctiDocElementPubFun::CancelSelection(m_Document);
	rollSelMode();
}

void NCTI::NctiSplitFacesDlg::GetSelection()
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
		}
		else
		{
			m_ui->pick_obj_lab->setStyleSheet("color: green;");
		}

	}
}
