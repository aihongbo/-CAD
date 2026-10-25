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

#include "NctiAddMaterialDlg.h"

#include "NctiAddCentralizeForceDlg.h"
#include "NctiDocElementPubFun.h"
#include "NctiDocument.h"
#include "NctiArgumentObject.h"
#include "NctiCommandManager.h"
using namespace NCTI;

NctiAddMaterialDlg::NctiAddMaterialDlg(NctiDocument* i_pDocument, QWidget* i_parent)
	: NctiBaseSelectObjectDlg(i_pDocument, i_parent)
	, m_ui(new Ui::NctiMeshAddMatrial())
{
	m_ui->setupUi(this);
	this->setWindowFlags(Qt::MSWindowsFixedSizeDialogHint | Qt::Dialog);
	this->setWindowModality(Qt::NonModal);

	connect(m_ui->pick_obj_bnt, SIGNAL(clicked()), this, SLOT(getSelection()));
	connect(m_ui->pushButton_OK, SIGNAL(clicked()), this, SLOT(onOk()));
	connect(m_ui->pushButton_Cancel, SIGNAL(clicked()), this, SLOT(onCanle())); 
	
	m_SelMode = SelectMode::Body | SelectMode::Face | SelectMode::Line | SelectMode::Marker;
}

NctiAddMaterialDlg::~NctiAddMaterialDlg()
{
	NCTI_DELETE m_ui;
}

void NctiAddMaterialDlg::onOk()
{

	if (m_Document && m_ObjNameVec.size() > 0)
	{
		NctiBaseModel* pBaseModel = m_Document->GetBaseModel();
		NctiCommandManager* pComMan = NctiCommandManager::GetCommandManager(pBaseModel);
		if (pComMan)
		{
			NctiArgumentObject argumentObject;

			std::vector<std::string> args{
				m_ObjNameVec[0],

				m_ui->lineEdit_E->text().toUtf8().data(),
				m_ui->lineEdit_G->text().toUtf8().data(),
				m_ui->lineEdit_nu->text().toUtf8().data(),
				m_ui->lineEdit_rho->text().toUtf8().data(),
				m_ui->lineEdit_a->text().toUtf8().data(),

				m_ui->plainTextEdit->toPlainText().toUtf8().data()
			};

			argumentObject.SetCommandArgumentVec(args);

			EnumNctiResult result = pComMan->RunCommand("cmd_ncti_mesh_add_mat", &argumentObject);
		}
	}
	close();
	NctiDocElementPubFun::CancelSelection(m_Document);
	rollSelMode();
}

void NctiAddMaterialDlg::getSelection()
{
	if (!m_Document)
	{
		return;
	}

	std::vector<NctiTopoCell*> geCellVec;
	std::vector<Ncti_Long> m_cellIds;
	NctiDocElementPubFun::GetNameFromSelManager(m_Document, m_ObjNameVec, m_cellIds, geCellVec);
	Ncti_Integer nCount = m_ObjNameVec.size();

	QString strSel = QString("已选择%1个对象").arg(nCount);
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
