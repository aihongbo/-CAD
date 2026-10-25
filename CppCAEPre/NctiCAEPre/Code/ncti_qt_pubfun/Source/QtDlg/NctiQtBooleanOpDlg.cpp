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

#include "NctiQtBooleanOpDlg.h"

#include <QMessageBox>

#include "NctiString.h"
#include "NctiBaseModel.h"
#include "NctiDocument.h"
#include "NctiCommandManager.h"
#include "NctiArgumentObject.h"
#include "NctiDisplayObject.h"
#include "NctiDocElementPubFun.h"
using namespace NCTI;

NCTI::NctiQtBooleanOpDlg::NctiQtBooleanOpDlg(NctiDocument* i_pDocument, Ncti_Integer i_dlgType, QWidget* i_parent)
	: QWidget(i_parent)
    , m_ui(new Ui::BooleanOpDlg())
	, m_Document(i_pDocument)
	, m_DisplayObject1(nullptr)
	, m_DisplayObject2(nullptr)
	, m_DlgType(i_dlgType)
{
	m_ui->setupUi(this);
	this->setFixedSize(this->geometry().size());
	this->setWindowFlags(Qt::MSWindowsFixedSizeDialogHint | Qt::Dialog);
	this->setWindowModality(Qt::NonModal);
	m_ui->label_Select1->setText("未选取");
	m_ui->label_Select2->setText("未选取");
	
	QString title;
	if (m_DlgType == 0)
	{
		title = "BooleanUnit";
	}
	else if (m_DlgType == 1)
	{
		title = "BooleanCut";
	}
	else if (m_DlgType == 2)
	{
		title = "BooleanCommon";
	}
	setWindowTitle(title);

	connect(m_ui->pushButton_1, SIGNAL(clicked()), this, SLOT(onSelect1()));
	connect(m_ui->pushButton_2, SIGNAL(clicked()), this, SLOT(onSelect2()));
	connect(m_ui->pushButton_OK, SIGNAL(clicked()), this, SLOT(onOk()));
	connect(m_ui->pushButton_Cancel, SIGNAL(clicked()), this, SLOT(onCanle()));
}

NCTI::NctiQtBooleanOpDlg::~NctiQtBooleanOpDlg()
{
	NCTI_DELETE m_ui;
}

void NctiQtBooleanOpDlg::onCanle()
{
	close();
}

void NCTI::NctiQtBooleanOpDlg::onSelect1()
{
	std::vector<NctiDisplayObject*> selectObjects;
	NctiDocElementPubFun::GetDisplayObjectFromSelManager(m_Document, selectObjects);
	if (selectObjects.size() == 1)
	{
		m_DisplayObject1 = selectObjects[0];
		m_ui->label_Select1->setText("已选取");
	}
	else {
		QMessageBox::information(nullptr, "提示", "实体对象数量不为 1");
	}
}

void NCTI::NctiQtBooleanOpDlg::onSelect2()
{
	std::vector<NctiDisplayObject*> selectObjects;
	NctiDocElementPubFun::GetDisplayObjectFromSelManager(m_Document, selectObjects);
	if (selectObjects.size() == 1)
	{
		m_DisplayObject2 = selectObjects[0];
		m_ui->label_Select2->setText("已选取");
	}
	else {
		QMessageBox::information(nullptr, "提示", "实体对象数量不为 1");
	}
}

void NctiQtBooleanOpDlg::onOk()
{
	if (!m_DisplayObject1 || !m_DisplayObject2)
	{
		QMessageBox::information(nullptr, "提示", "实体对象数量不为 1");
		return;
	}
	NctiBaseModel* pBaseModel = m_Document->GetBaseModel();
	NctiCommandManager* pComMan = NctiCommandManager::GetCommandManager(pBaseModel);
	if (pComMan)
	{
		NctiArgumentObject argumentObject;
		argumentObject.SetDisplayObject1(m_DisplayObject1);
		argumentObject.SetDisplayObject2(m_DisplayObject2);
		if(m_DlgType == 0)
			pComMan->RunCommand("cmd_ncti_boolean_unit", &argumentObject);
		else if(m_DlgType == 1)
			pComMan->RunCommand("cmd_ncti_boolean_cut", &argumentObject);
		else if (m_DlgType == 2)
			pComMan->RunCommand("cmd_ncti_boolean_common", &argumentObject);
	}
	close();
}

