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

#include "NctiExtendFaceDlg.h"

#include "NctiBaseModel.h"
#include "NctiCommandManager.h"
#include "NctiDocument.h"
#include "NctiArgumentObject.h"
#include "NctiDocElementPubFun.h"
#include "NctiBaseGeometryMath.h"
#include "NctiString.h"

using namespace NCTI;

NctiExtendFaceDlg::NctiExtendFaceDlg(NctiDocument* i_pDocument, QWidget* i_parent)
	:NctiBaseSelectObjectDlg(i_pDocument, i_parent)
	, m_ui(new Ui::NctiExtendFace())
	, m_NormalVec(nullptr)
{
	m_ui->setupUi(this);
	this->setWindowFlags(Qt::MSWindowsFixedSizeDialogHint | Qt::Dialog);
	this->setWindowModality(Qt::NonModal);

	m_ui->lineEdit_x->setText("0");
	m_ui->lineEdit_y->setText("0");
	m_ui->lineEdit_z->setText("0");
	m_ui->lineEdit_len->setText("1");

	connect(m_ui->pushButton_OK, SIGNAL(clicked()), this, SLOT(onOk()));
	connect(m_ui->pushButton_Cancel, SIGNAL(clicked()), this, SLOT(onCanle()));
	connect(m_ui->pushButton, SIGNAL(clicked()), this, SLOT(onGetFaceNormal()));

	m_SelMode = SelectMode::Face | SelectMode::Line | SelectMode::Marker;
}

NctiExtendFaceDlg::~NctiExtendFaceDlg()
{
	NCTI_DELETE m_ui;
	delete m_NormalVec;
}

void NCTI::NctiExtendFaceDlg::onGetFaceNormal()
{
	if (m_Document)
	{
		NctiBaseModel* pBaseModel = m_Document->GetBaseModel();
		NctiCommandManager* pComMan = NctiCommandManager::GetCommandManager(pBaseModel);
		if (pComMan)
		{
			std::vector<NctiTopoCell*> geCellVec;
			std::vector<std::string> objNameVec;
			std::vector<Ncti_Long> cellIds;
			NctiDocElementPubFun::GetNameFromSelManager(m_Document, objNameVec, cellIds, geCellVec);
			if (objNameVec.size() == 0 || cellIds.size() == 0)
			{
				return;
			}
			const Ncti_Char* objName = objNameVec[0].c_str();
			Ncti_Long cellId = cellIds[0];

			m_NormalVec = new NctiVector();
			NctiDocElementPubFun::GetNormalByUV(m_Document, objName, cellId, 0.5, 0.5, *m_NormalVec);
			m_ui->lineEdit_x->setText(NctiString::double_to_string(m_NormalVec->x(), 2).c_str());
			m_ui->lineEdit_y->setText(NctiString::double_to_string(m_NormalVec->y(), 2).c_str());
			m_ui->lineEdit_z->setText(NctiString::double_to_string(m_NormalVec->z(), 2).c_str());
		}
	}
}

void NctiExtendFaceDlg::onOk()
{
	if (m_Document)
	{
		NctiBaseModel* pBaseModel = m_Document->GetBaseModel();
		NctiCommandManager* pComMan = NctiCommandManager::GetCommandManager(pBaseModel);
		if (pComMan)
		{
			std::vector<NctiDisplayObject*> selectObjects;
			NctiDocElementPubFun::GetDisplayObjectFromSelManager(m_Document, selectObjects);
			if (selectObjects.size() == 0)
			{
				close();
				rollSelMode();
				return;
			}

			NctiArgumentObject argumentObject;
			if (m_NormalVec == nullptr)
			{
				m_NormalVec = new NctiVector();
				m_NormalVec->set_x(m_ui->lineEdit_x->text().toDouble());
				m_NormalVec->set_y(m_ui->lineEdit_y->text().toDouble());
				m_NormalVec->set_z(m_ui->lineEdit_z->text().toDouble());

				Ncti_Double* normalPtr = reinterpret_cast<Ncti_Double*>(m_NormalVec);
				NctiBaseGeometryMath::Normalize(normalPtr);

			}
			NctiVector dir;
			Ncti_Double len = m_ui->lineEdit_len->text().toDouble();
			dir = *m_NormalVec * len;

			argumentObject.SetDir(dir);

			argumentObject.SetDisplayObject1(selectObjects[0]);

			EnumNctiResult result = pComMan->RunCommand("cmd_ncti_prism", &argumentObject);
		}
	}
	close();
	NctiDocElementPubFun::CancelSelection(m_Document);
	rollSelMode();
}