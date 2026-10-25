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

#include "NctiRotateObjectDlg.h"

#include <QString>

#include "NctiDocElementPubFun.h"
#include "NctiSelectionDataList.h"
#include "NctiCommandManager.h"
#include "NctiArgumentObject.h"
#include "NctiDocument.h"
using namespace NCTI;

NCTI::NctiRotateObjectDlg::NctiRotateObjectDlg(NctiDocument* i_pDocument, QWidget* i_parent)
	:QWidget(i_parent)
	, m_ui(new Ui::NctiRotateObjectDlg())
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
	setWindowTitle("MoveObject");
 	connect(m_ui->pick_obj_bnt, SIGNAL(clicked()), this, SLOT(GetSelection()));
 	connect(m_ui->pushButton_ok, SIGNAL(clicked()), this, SLOT(onOK()));
 	connect(m_ui->pushButton_cancel, SIGNAL(clicked()), this, SLOT(onCanle()));
}

NCTI::NctiRotateObjectDlg::~NctiRotateObjectDlg()
{
	NCTI_DELETE m_ui;
}

void NCTI::NctiRotateObjectDlg::onOK()
{
	if(m_Document && m_displayobj.size() > 0)
	{
		NctiBaseModel* pBaseModel = m_Document->GetBaseModel();
		NctiCommandManager* pComMan = NctiCommandManager::GetCommandManager(pBaseModel);
		if (pComMan)
		{
			NctiArgumentObject argumentObject;
			NctiPosition pt;
			pt.set_x(m_ui->lineEdit_x_pt->text().toDouble());
			pt.set_y(m_ui->lineEdit_y_pt->text().toDouble());
			pt.set_z(m_ui->lineEdit_z_pt->text().toDouble());
			argumentObject.SetPt(pt);
			NctiVector vec;
			vec.set_x(m_ui->lineEdit_x_vec->text().toDouble());
			vec.set_y(m_ui->lineEdit_y_vec->text().toDouble());
			vec.set_z(m_ui->lineEdit_z_vec->text().toDouble());
			argumentObject.SetDir(vec);
			argumentObject.SetRadius(m_ui->lineEdit_angle->text().toDouble());
			argumentObject.SetDisplayObjectVec(m_displayobj);

			EnumNctiResult result = pComMan->RunCommand("cmd_ncti_rotate_body", &argumentObject);
		}
	}
	close();
	NctiDocElementPubFun::CancelSelection(m_Document);
	rollSelMode();
}

void NctiRotateObjectDlg::rollSelMode()
{
	NctiDocElementPubFun::SetSelectBody(m_Document, m_selBody);
	NctiDocElementPubFun::SetSelectFace(m_Document, m_selFace);
	NctiDocElementPubFun::SetSelectLine(m_Document, m_selLine);
	NctiDocElementPubFun::SetSelectMarker(m_Document, m_selMarker);
}

void NctiRotateObjectDlg::InitSelMode()
{
	if (m_Document == nullptr)
		return;
	NctiDocElementPubFun::GetSelectMode(m_Document, m_selBody, m_selFace, m_selLine, m_selMarker);
	if (m_selBody == false)
	{
		//取消
		NctiDocElementPubFun::CancelSelection(m_Document);
		//重设为选择对象
		NctiDocElementPubFun::SetSelectBody(m_Document, true);
		NctiDocElementPubFun::SetSelectFace(m_Document, true);
		NctiDocElementPubFun::SetSelectLine(m_Document, true);
		NctiDocElementPubFun::SetSelectMarker(m_Document, true);
	}
	GetSelection();
	m_ui->lineEdit_x_vec->setText("0");
	m_ui->lineEdit_y_vec->setText("0");
	m_ui->lineEdit_z_vec->setText("1");
}

void NctiRotateObjectDlg::onCanle()
{
	close();
	NctiDocElementPubFun::CancelSelection(m_Document);
	rollSelMode();
}

void NctiRotateObjectDlg::GetSelection()
{
	if (m_Document)
	{
		NctiDocElementPubFun::GetDisplayObjectFromSelManager(m_Document, m_displayobj);
		Ncti_Integer nCount = m_displayobj.size();
		
		QString strSel = QString("已选择%1个对象").arg(nCount);
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

void NctiRotateObjectDlg::show()
{
 	QWidget::show();
	InitSelMode();
// 	GetCurrentSelMode();
// 
// 	UpdateCtl();
}

