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

#include "NctiVisualModeDlg.h"

#include "NctiDocElementPubFun.h"
#include "NctiDocViewManager.h"
#include "NctiDisplayModelBody.h"
using namespace NCTI;

NCTI::NctiVisualModeDlg::NctiVisualModeDlg(NctiDocument* i_pDocument, QWidget* i_parent)
	:QWidget(i_parent)
	, m_ui(new Ui::NctiVisualModeDlg())
	, m_Document(i_pDocument)
{
	m_ui->setupUi(this);
	this->setFixedSize(this->geometry().size());
	this->setWindowFlags(Qt::MSWindowsFixedSizeDialogHint | Qt::Dialog);
	this->setWindowModality(Qt::WindowModal);//阻挡父亲窗口内其他控件，除非本dialog关闭
	setWindowTitle("SelectMode");
	GetCurrentVisualMode();
	
	UpdateCtl();
	connect(m_ui->checkBox_all, SIGNAL(clicked()), this, SLOT(onUpdateCtl()));
	connect(m_ui->checkBox_Face, SIGNAL(clicked()), this, SLOT(onUpdateCtl()));
	connect(m_ui->checkBox_Line, SIGNAL(clicked()), this, SLOT(onUpdateCtl()));
	connect(m_ui->checkBox_Marker, SIGNAL(clicked()), this, SLOT(onUpdateCtl()));
	connect(m_ui->pushButton_ok, SIGNAL(clicked()), this, SLOT(onOK()));
	connect(m_ui->pushButton_cancel, SIGNAL(clicked()), this, SLOT(onCanle()));

}

NCTI::NctiVisualModeDlg::~NctiVisualModeDlg()
{
	NCTI_DELETE m_ui;
}

void NCTI::NctiVisualModeDlg::onOK()
{
	m_visual_all = m_ui->checkBox_all->isChecked();
	m_visual_face = m_ui->checkBox_Face->isChecked();
	m_visual_line = m_ui->checkBox_Line->isChecked();
	m_visual_marker = m_ui->checkBox_Marker->isChecked();
	close();
	NctiDocElementPubFun::CancelSelection(m_Document);
	NctiDocElementPubFun::SetVisualMode(m_Document, m_visual_face, m_visual_line, m_visual_marker);
}
void NctiVisualModeDlg::onCanle()
{
	NctiDocElementPubFun::CancelSelection(m_Document);
	close();
}
void NCTI::NctiVisualModeDlg::onUpdateCtl()
{
	m_visual_all = m_ui->checkBox_all->isChecked();
	m_visual_face = m_ui->checkBox_Face->isChecked();
	m_visual_line = m_ui->checkBox_Line->isChecked();
	m_visual_marker = m_ui->checkBox_Marker->isChecked();
	UpdateCtl();
}

void NctiVisualModeDlg::show()
{
	QWidget::show();
	GetCurrentVisualMode();
	NctiDocElementPubFun::CancelSelection(m_Document);
	UpdateCtl();
}

void NCTI::NctiVisualModeDlg::GetCurrentVisualMode()
{
	m_visual_all = false;
	m_visual_face = false;
	m_visual_line = false;
	m_visual_marker = false;
	NctiDocElementPubFun::GetVisualMode(m_visual_face, m_visual_line, m_visual_marker);
	m_visual_all = visual_all();
}

void NCTI::NctiVisualModeDlg::UpdateCtl()
{
	m_ui->checkBox_all->setChecked(m_visual_all);
	if (m_visual_all)
	{
		m_visual_face = true;
		m_visual_line = true;
		m_visual_marker = true;
		m_ui->checkBox_Face->setChecked(m_visual_face);
		m_ui->checkBox_Line->setChecked(m_visual_line);
		m_ui->checkBox_Marker->setChecked(m_visual_marker);
		m_ui->checkBox_Face->setEnabled(false);
		m_ui->checkBox_Line->setEnabled(false);
		m_ui->checkBox_Marker->setEnabled(false);
	}
	else
	{

		//GetCurrentSelMode();
		m_visual_all = false;
		m_ui->checkBox_Face->setChecked(m_visual_face);
		m_ui->checkBox_Line->setChecked(m_visual_line);
		m_ui->checkBox_Marker->setChecked(m_visual_marker);
		m_ui->checkBox_Face->setEnabled(true);
		m_ui->checkBox_Line->setEnabled(true);
		m_ui->checkBox_Marker->setEnabled(true);
	}
}

bool NctiVisualModeDlg::visual_all()
{
	return (m_visual_face && m_visual_line && m_visual_marker);
}

