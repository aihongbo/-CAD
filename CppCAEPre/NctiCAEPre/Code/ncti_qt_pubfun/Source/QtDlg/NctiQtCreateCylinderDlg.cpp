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

#include "NctiQtCreateCylinderDlg.h"

#include "NctiString.h"
#include "NctiBaseModel.h"
#include "NctiDocument.h"
#include "NctiCommandManager.h"
#include "NctiArgumentObject.h"
#include "NctiPosition.h"
using namespace NCTI;

NCTI::NctiQtCreateCylinderDlg::NctiQtCreateCylinderDlg(NctiDocument* i_pDocument, QWidget* i_parent)
	: QWidget(i_parent)
	, m_ui(new Ui::CreateCylinder())
	, m_Document(i_pDocument)
{
	m_ui->setupUi(this);
	this->setFixedSize(this->geometry().size());
	this->setWindowFlags(Qt::MSWindowsFixedSizeDialogHint | Qt::Dialog);
	this->setWindowModality(Qt::WindowModal);//阻挡父亲窗口内其他控件，除非本dialog关闭
	setWindowTitle("CreateCylinder");

	m_ui->lineEditX->setText("10");
	m_ui->lineEditY->setText("20");
	m_ui->lineEditZ->setText("30");

	m_ui->lineEditRadius->setText("5");
	m_ui->lineEditHeight->setText("10");
	connect(m_ui->pushButton_OK, SIGNAL(clicked()), this, SLOT(onOk()));
	connect(m_ui->pushButton_Cancel, SIGNAL(clicked()), this, SLOT(onCanle()));
}

NCTI::NctiQtCreateCylinderDlg::~NctiQtCreateCylinderDlg()
{
	NCTI_DELETE m_ui;
}

void NctiQtCreateCylinderDlg::onCanle()
{
	close();
}

void NctiQtCreateCylinderDlg::onOk()
{
	NctiBaseModel* pBaseModel = m_Document->GetBaseModel();
	NctiCommandManager* pComMan = NctiCommandManager::GetCommandManager(pBaseModel);
	if (pComMan)
	{
		NctiArgumentObject argumentObject;
		NctiPosition pt;
		pt.set_x(m_ui->lineEditX->text().toDouble());
		pt.set_y(m_ui->lineEditY->text().toDouble());
		pt.set_z(m_ui->lineEditZ->text().toDouble());
		argumentObject.SetPt(pt);
		argumentObject.SetRadius(m_ui->lineEditRadius->text().toDouble());
		argumentObject.SetHeight(m_ui->lineEditHeight->text().toDouble());
		EnumNctiResult result = pComMan->RunCommand("cmd_ncti_create_cylinder", &argumentObject);
	}
	close();
}

