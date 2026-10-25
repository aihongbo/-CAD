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

#include "NctiAddMeshSinglePointConstraintDlg.h"

#include "NctiDocElementPubFun.h"
#include "NctiDocument.h"
#include "NctiArgumentObject.h"
#include "NctiCommandManager.h"
#include "NctiPhyParaDef.h"

using namespace NCTI;

NctiAddMeshSinglePointConstraintDlg::NctiAddMeshSinglePointConstraintDlg(NctiDocument* i_pDocument, QWidget* i_parent)
    : NctiBaseSelectObjectDlg(i_pDocument, i_parent)
    , m_ui(new Ui::NctiAddMeshSinglePointConstraint())
{
	m_ui->setupUi(this);
	this->setWindowFlags(Qt::MSWindowsFixedSizeDialogHint | Qt::Dialog);
	this->setWindowModality(Qt::NonModal);

	m_ui->checkBox_u1->setChecked(true);
	m_ui->checkBox_u2->setChecked(true);
	m_ui->checkBox_u3->setChecked(true);
	m_ui->checkBox_rot1->setChecked(true);
	m_ui->checkBox_rot2->setChecked(true);
	m_ui->checkBox_rot3->setChecked(true);

	connect(m_ui->pick_obj_bnt, SIGNAL(clicked()), this, SLOT(getSelection()));
	connect(m_ui->pushButton_OK, SIGNAL(clicked()), this, SLOT(onOk()));
	connect(m_ui->pushButton_Cancel, SIGNAL(clicked()), this, SLOT(onCanle()));

	m_SelMode = SelectMode::Face;
}

NctiAddMeshSinglePointConstraintDlg::~NctiAddMeshSinglePointConstraintDlg()
{
	NCTI_DELETE m_ui;
}

void NctiAddMeshSinglePointConstraintDlg::onOk()
{
	Ncti_Integer component=0;
	if (m_ui->checkBox_u1->isChecked())
		component |= Ncti_Components_U1;
	if (m_ui->checkBox_u2->isChecked())
		component |= Ncti_Components_U2;
	if(m_ui->checkBox_u3->isChecked())
		component |= Ncti_Components_U3;
	if(m_ui->checkBox_rot1->isChecked())
		component |= Ncti_Components_ROT1;
	if(m_ui->checkBox_rot2->isChecked())
		component |= Ncti_Components_ROT2;
	if(m_ui->checkBox_rot3->isChecked())
		component |= Ncti_Components_ROT3;

	if (m_Document && m_ObjNameVec.size() > 0)
	{
		NctiBaseModel* pBaseModel = m_Document->GetBaseModel();
		NctiCommandManager* pComMan = NctiCommandManager::GetCommandManager(pBaseModel);
		if (pComMan)
		{
			NctiArgumentObject argumentObject;

			std::vector<std::string> args{
				std::to_string(component),
				m_ObjNameVec[0],
				m_ui->plainTextEdit->toPlainText().toUtf8().data()
			};
			argumentObject.SetCommandArgumentVec(args);

			argumentObject.SetCellIDVec(m_cellIds);

			EnumNctiResult result = pComMan->RunCommand("cmd_ncti_mesh_add_spc", &argumentObject);
		}
	}
	close();
	NctiDocElementPubFun::CancelSelection(m_Document);
	rollSelMode();
}

void NctiAddMeshSinglePointConstraintDlg::getSelection()
{
	if (!m_Document)
	{
		return;
	}

	std::vector<NctiTopoCell*> geCellVec;
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
