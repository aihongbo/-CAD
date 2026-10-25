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

#include "NctiQtCreateBoxDlg.h"

#include "NctiString.h"
#include "NctiBaseModel.h"
#include "NctiDocument.h"
#include "NctiCommandManager.h"
#include "NctiArgumentObject.h"
#include "NctiPosition.h"
using namespace NCTI;

NCTI::NctiQtCreateBoxDlg::NctiQtCreateBoxDlg(NctiDocument* i_pDocument, QWidget* i_parent)
	: QWidget(i_parent)
    , m_ui(new Ui::NctiQtCreateBox())
	, m_Document(i_pDocument)
{
	m_ui->setupUi(this);
	this->setFixedSize(this->geometry().size());
	this->setWindowFlags(Qt::MSWindowsFixedSizeDialogHint | Qt::Dialog);
	this->setWindowModality(Qt::WindowModal);//阻挡父亲窗口内其他控件，除非本dialog关闭
	setWindowTitle("CreateBox");

	m_ui->lineEdit_X->setText("10");
	m_ui->lineEdit_Y->setText("20");
	m_ui->lineEdit_Z->setText("30");

	m_ui->lineEdit_X_P->setText("0");
	m_ui->lineEdit_Y_P->setText("0");
	m_ui->lineEdit_Z_P->setText("0");

	connect(m_ui->pushButton_OK, SIGNAL(clicked()), this, SLOT(onOk()));
	connect(m_ui->pushButton_Cancle, SIGNAL(clicked()), this, SLOT(onCanle()));
}

NCTI::NctiQtCreateBoxDlg::~NctiQtCreateBoxDlg()
{
	NCTI_DELETE m_ui;
}

void NctiQtCreateBoxDlg::onCanle()
{
	close();
}

void NctiQtCreateBoxDlg::onOk()
{
	NctiBaseModel* pBaseModel = m_Document->GetBaseModel();
	NctiCommandManager* pComMan = NctiCommandManager::GetCommandManager(pBaseModel);
	if (pComMan)
	{
		NctiArgumentObject argumentObject;
		NctiPosition pt;
		pt.set_x(m_ui->lineEdit_X_P->text().toDouble());
		pt.set_y(m_ui->lineEdit_Y_P->text().toDouble());
		pt.set_z(m_ui->lineEdit_Z_P->text().toDouble());
		argumentObject.SetPt(pt);
		argumentObject.SetXLen(m_ui->lineEdit_X->text().toDouble());
		argumentObject.SetYLen(m_ui->lineEdit_Y->text().toDouble());
		argumentObject.SetZLen(m_ui->lineEdit_Z->text().toDouble());
		EnumNctiResult result = pComMan->RunCommand("cmd_ncti_create_box", &argumentObject);
	}
	close();
}

