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

#include "NctiQtAiModelAddLabelDlg.h"

#include "ncti_base.h"
#include "NctiBaseModel.h"
#include "NctiDocument.h"
#include "NctiCommandManager.h"
#include "NctiArgumentObject.h"
#include "NctiDocElementPubFun.h"
using namespace NCTI;

NctiQtAiModelAddLabelDlg* NctiQtAiModelAddLabelDlg::m_instance = nullptr;

NctiQtAiModelAddLabelDlg::NctiQtAiModelAddLabelDlg(NctiDocument* i_pDocument, QWidget* i_parent)
    : QWidget(i_parent)
	, m_ui(new Ui::NctiAiAddLabel())
	, m_Document(i_pDocument)
	, m_selBody(false)
	, m_selFace(false)
	, m_selLine(false)
	, m_selMarker(false)
{
	m_ui->setupUi(this);
	this->setWindowFlags(Qt::MSWindowsFixedSizeDialogHint | Qt::Dialog);
	this->setWindowModality(Qt::NonModal);

	connect(m_ui->pick_obj_bnt, SIGNAL(clicked()), this, SLOT(getSelection()));
	connect(m_ui->pushButton_OK, SIGNAL(clicked()), this, SLOT(onOk()));
	connect(m_ui->pushButton_Cancel, SIGNAL(clicked()), this, SLOT(onCanle()));
}

NctiQtAiModelAddLabelDlg::~NctiQtAiModelAddLabelDlg()
{
	NCTI_DELETE m_ui;
}

NctiQtAiModelAddLabelDlg* NCTI::NctiQtAiModelAddLabelDlg::Instance()
{
	return m_instance;
}

void NCTI::NctiQtAiModelAddLabelDlg::SetInstance(NctiQtAiModelAddLabelDlg* pNctiQtAiModelAddLabelDlg)
{
	m_instance = pNctiQtAiModelAddLabelDlg;
}

void NctiQtAiModelAddLabelDlg::onOk()
{
	QLineEdit* labelName = m_ui->lineEdit_LabelName;
	if (labelName->text().isEmpty())
	{
		labelName->setPlaceholderText("please enter label name!");
		return;
	}
	if (m_Document && m_displayobj.size() > 0)
	{
		NctiBaseModel* pBaseModel = m_Document->GetBaseModel();
		NctiCommandManager* pComMan = NctiCommandManager::GetCommandManager(pBaseModel);
		if (pComMan)
		{
			NctiArgumentObject argumentObject;

			std::vector<std::string> args{
				labelName->text().toUtf8().data()
			};
			argumentObject.SetCommandArgumentVec(args);

			argumentObject.SetCellVec(m_cells);
			argumentObject.SetDisplayObjectVec(m_displayobj);

			EnumNctiResult result = pComMan->RunCommand("cmd_ncti_ai_model_add_label", &argumentObject);
		}
	}
	close();
	NctiDocElementPubFun::CancelSelection(m_Document);
	rollSelMode();
}

void NctiQtAiModelAddLabelDlg::onCanle()
{
	this->close();
	NctiDocElementPubFun::CancelSelection(m_Document);
	rollSelMode();
}

void NctiQtAiModelAddLabelDlg::getSelection()
{
	if (!m_Document)
	{
		return;
	}

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

void NctiQtAiModelAddLabelDlg::InitSelMode()
{
	if (m_Document == nullptr)
		return;
	//NctiDocElementPubFun::CancelSelection(m_Document);
	NctiDocElementPubFun::GetSelectMode(m_Document, m_selBody, m_selFace, m_selLine, m_selMarker);
	//重设为选择对象
	NctiDocElementPubFun::SetSelectBody(m_Document, false);
	NctiDocElementPubFun::SetSelectFace(m_Document, true);
	NctiDocElementPubFun::SetSelectLine(m_Document, false);
	NctiDocElementPubFun::SetSelectMarker(m_Document, false);
}

void NctiQtAiModelAddLabelDlg::rollSelMode()
{
	NctiDocElementPubFun::SetSelectBody(m_Document, m_selBody);
	NctiDocElementPubFun::SetSelectFace(m_Document, m_selFace);
	NctiDocElementPubFun::SetSelectLine(m_Document, m_selLine);
	NctiDocElementPubFun::SetSelectMarker(m_Document, m_selMarker);
}

void NctiQtAiModelAddLabelDlg::show()
{
	QWidget::show();
	InitSelMode();
}
