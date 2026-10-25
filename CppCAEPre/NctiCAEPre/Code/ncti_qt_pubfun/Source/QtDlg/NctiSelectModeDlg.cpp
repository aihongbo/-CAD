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

#include "NctiSelectModeDlg.h"

#include "NctiDocElementPubFun.h"
using namespace NCTI;

NCTI::NctiSelectModeDlg::NctiSelectModeDlg(NctiDocument* i_pDocument, QWidget* i_parent)
	:QWidget(i_parent)
	, m_ui(new Ui::NctiSelectModeDlg())
	, m_Document(i_pDocument)
{
	m_ui->setupUi(this);
	this->setFixedSize(this->geometry().size());
	this->setWindowFlags(Qt::MSWindowsFixedSizeDialogHint | Qt::Dialog);
	this->setWindowModality(Qt::WindowModal);//阻挡父亲窗口内其他控件，除非本dialog关闭
	setWindowTitle("SelectMode");
	GetCurrentSelMode();
	
	UpdateCtl();
	connect(m_ui->checkBox_body, SIGNAL(clicked()), this, SLOT(onUpdateCtl()));
	connect(m_ui->checkBox_Face, SIGNAL(clicked()), this, SLOT(onUpdateCtl()));
	connect(m_ui->checkBox_Line, SIGNAL(clicked()), this, SLOT(onUpdateCtl()));
	connect(m_ui->checkBox_Marker, SIGNAL(clicked()), this, SLOT(onUpdateCtl()));
	connect(m_ui->pushButton_ok, SIGNAL(clicked()), this, SLOT(onOK()));
	connect(m_ui->pushButton_cancel, SIGNAL(clicked()), this, SLOT(onCanle()));

}

NCTI::NctiSelectModeDlg::~NctiSelectModeDlg()
{
	NCTI_DELETE m_ui;
}

void NCTI::NctiSelectModeDlg::onOK()
{
	m_sel_body = m_ui->checkBox_body->isChecked();
	m_sel_face = m_ui->checkBox_Face->isChecked();
	m_sel_line = m_ui->checkBox_Line->isChecked();
	m_sel_marker = m_ui->checkBox_Marker->isChecked();

	NctiDocElementPubFun::SetSelectBody(m_Document, m_sel_body);
	NctiDocElementPubFun::SetSelectFace(m_Document, m_sel_face);
	NctiDocElementPubFun::SetSelectLine(m_Document, m_sel_line);
	NctiDocElementPubFun::SetSelectMarker(m_Document, m_sel_marker);
	close();
	NctiDocElementPubFun::CancelSelection(m_Document);
}
void NctiSelectModeDlg::onCanle()
{
	close();
}
void NCTI::NctiSelectModeDlg::onUpdateCtl()
{
	m_sel_body = m_ui->checkBox_body->isChecked();
	m_sel_face = m_ui->checkBox_Face->isChecked();
	m_sel_line = m_ui->checkBox_Line->isChecked();
	m_sel_marker = m_ui->checkBox_Marker->isChecked();
	UpdateCtl();
}

void NctiSelectModeDlg::show()
{
	QWidget::show();
	GetCurrentSelMode();

	UpdateCtl();
}

void NCTI::NctiSelectModeDlg::GetCurrentSelMode()
{
	m_sel_body = false;
	m_sel_face = false;
	m_sel_line = false;
	m_sel_marker = false;
	NctiDocElementPubFun::GetSelectMode(m_Document, m_sel_body, m_sel_face, m_sel_line, m_sel_marker);
}

void NCTI::NctiSelectModeDlg::UpdateCtl()
{
	m_ui->checkBox_body->setChecked(m_sel_body);
	if (m_sel_body)
	{
		m_sel_face = true;
		m_sel_line = true;
		m_sel_marker = true;
		m_ui->checkBox_Face->setChecked(m_sel_face);
		m_ui->checkBox_Line->setChecked(m_sel_line);
		m_ui->checkBox_Marker->setChecked(m_sel_marker);
		m_ui->checkBox_Face->setEnabled(false);
		m_ui->checkBox_Line->setEnabled(false);
		m_ui->checkBox_Marker->setEnabled(false);
	}
	else
	{

		//GetCurrentSelMode();
		m_sel_body = false;
		m_ui->checkBox_Face->setChecked(m_sel_face);
		m_ui->checkBox_Line->setChecked(m_sel_line);
		m_ui->checkBox_Marker->setChecked(m_sel_marker);
		m_ui->checkBox_Face->setEnabled(true);
		m_ui->checkBox_Line->setEnabled(true);
		m_ui->checkBox_Marker->setEnabled(true);
	}
}

