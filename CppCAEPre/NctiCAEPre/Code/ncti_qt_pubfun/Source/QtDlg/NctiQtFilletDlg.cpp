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

#include "NctiQtFilletDlg.h"

#include <QMessageBox>
#include <QLineEdit>

#include "NctiString.h"
#include "NctiBaseModel.h"
#include "NctiDocument.h"
#include "NctiCommandManager.h"
#include "NctiArgumentObject.h"
#include "NctiDocElementPubFun.h"
using namespace NCTI;

NCTI::NctiQtFilletDlg::NctiQtFilletDlg(NctiDocument* i_pDocument, QWidget* i_parent)
	: QWidget(i_parent)
    , m_ui(new Ui::Fillet())
	, m_Document(i_pDocument)
{
	m_ui->setupUi(this);
	this->setFixedSize(this->geometry().size());
	this->setWindowFlags(Qt::MSWindowsFixedSizeDialogHint | Qt::Dialog);
	this->setWindowModality(Qt::NonModal);
	setWindowTitle("Fillet");
	connect(m_ui->pushButton_SelEdge, SIGNAL(clicked()), this, SLOT(onSelEdge()));
	connect(m_ui->pushButton_OK, SIGNAL(clicked()), this, SLOT(onOk()));
	connect(m_ui->pushButton_Cancel, SIGNAL(clicked()), this, SLOT(onCanle()));
}

NCTI::NctiQtFilletDlg::~NctiQtFilletDlg()
{
	NCTI_DELETE m_ui;
}

void NCTI::NctiQtFilletDlg::onSelEdge()
{
	NctiDocElementPubFun::GetDisplayObjectFromSelManager(m_Document, m_SelObjVec, m_SelectCells);
	
	if (m_SelectCells.size() > 0)
	{
		m_ui->label_EdgeCount->setText(QString::number(m_SelectCells.size()));
	
	}
	else {
		QMessageBox::information(nullptr, "提示", "未选中边");
	}
}

void NctiQtFilletDlg::onCanle()
{
	close();
}

void NctiQtFilletDlg::onOk()
{
	NctiBaseModel* pBaseModel = m_Document->GetBaseModel();
	NctiCommandManager* pComMan = NctiCommandManager::GetCommandManager(pBaseModel);
	if (pComMan && m_SelectCells.size() > 0)
	{
		QString qsRadius = m_ui->lineEditRadius->text();
		NctiArgumentObject argumentObject;
		argumentObject.SetDisplayObjectVec(m_SelObjVec);
		argumentObject.SetCellVec(m_SelectCells);
		argumentObject.SetRadius(qsRadius.toDouble());
		EnumNctiResult result = pComMan->RunCommand("cmd_ncti_fillet", &argumentObject);
	}
	close();
}

