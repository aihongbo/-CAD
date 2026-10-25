/*
 * Copyright (c) 2026 粤港澳大湾区（广东）国创中心
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

#include "NctiDCM3TwoGeometriesWidget.h"

#include <QLineEdit>
#include <QComboBox>
#include <QMessageBox>

#include "NctiAddCentralizeForceDlg.h"
#include "NctiDocElementPubFun.h"
#include "NctiDocument.h"
#include "NctiCommandManager.h"
#include "NctiDisplayModelBody.h"
#include "NctiDisplayDocCustomContainer.h"
#include "NctiDisplayDCM3DimSys.h"
#include "NctiDisplayDCM3Dimension.h"
#include "NctiDisplayDCM3Geometry.h"
#include "NctiDCM3Set.h"
#include "NctiCreateConstraintScriptPub.h"
#include "NctiExecuteDCM3CommandTool.h"
#include "NctiDCM3PubFun.h"
#include "NctiDCM3Def.h"
#include "NctiString.h"
#include "CallbackInterfaces.h"

using namespace NCTI;

NctiDCM3TwoGeometriesWidget::NctiDCM3TwoGeometriesWidget(NctiDocument* i_pDoc, int i_dimType, NctiMode i_mode, const char* i_DimObjName, QWidget* i_parent)
	:NctiDCM3SingleGeometryWidget(i_pDoc, i_dimType, i_mode, i_DimObjName, i_parent)
	, m_pSelBody2(nullptr)
	, m_selCellID2(nullptr)
{
	init();
}

NctiDCM3TwoGeometriesWidget::~NctiDCM3TwoGeometriesWidget()
{
	if (m_selCellID2)
	{
		NCTI_DELETE m_selCellID2;
		m_selCellID2 = nullptr;
	}
}

void NCTI::NctiDCM3TwoGeometriesWidget::setSelLabelTexts(const QString& i_text1, const QString& i_text2)
{
	setSelLabelText(i_text1);
	m_selLabelText2 = i_text2;
	setSelectedText();
}


void NCTI::NctiDCM3TwoGeometriesWidget::execute()
{
	if (m_mode == NCTI_MODE_READ)
		return;
	if (!m_pDocument || !m_pSelBody1 || !m_pSelBody2 || !m_selCellID1 || !m_selCellID2)
		return;
	NctiBaseModel* pBaseModel = m_pDocument->GetBaseModel();
	NctiCommandManager* pComMan = NctiCommandManager::GetCommandManager(pBaseModel);

	NctiDisplayDCM3DimSys* pDimSys = nullptr;
	if (!GetOrCreateDimSys(m_pDocument, pDimSys))
		return;

	NctiDCM3Set* pSet1 = nullptr;
	NctiDCM3Set* pSet2 = nullptr;
	if (!GetOrCreateSet(m_pDocument, pDimSys, m_pSelBody1, pSet1))
	{
		QMessageBox::information(this, "提示", "创建刚性集失败！");
		return;
	}
	if (!GetOrCreateSet(m_pDocument, pDimSys, m_pSelBody2, pSet2))
	{
		QMessageBox::information(this, "提示", "创建刚性集失败！");
		return;
	}
	if (pSet1 == pSet2)
	{
		QMessageBox::information(this, "提示", "同一刚性集无法约束！");
		return;
	}

	NctiDisplayDCM3Geometry* pGeom1 = nullptr;
	NctiDisplayDCM3Geometry* pGeom2 = nullptr;
	if (!GetOrCreateGeometry(m_pDocument, pDimSys, pSet1, *m_selCellID1, pGeom1))
	{
		QMessageBox::information(this, "提示", "创建约束几何失败！");
		return;
	}
	if (!GetOrCreateGeometry(m_pDocument, pDimSys, pSet2, *m_selCellID2, pGeom2))
	{
		QMessageBox::information(this, "提示", "创建约束几何失败！");
		return;
	}

	NctiDisplayDCM3Dimension* pDim = nullptr;
	if (GetDimension(m_pDocument, pGeom1, pGeom2, nullptr, (ncti_DCM3_d_type)m_dimType, pDim))
	{//约束已存在
		ncti_DCM3_alignment_type alignType = NctiDCM3PubFun::GetAlignmentType(pGeom1, pGeom2, (ncti_DCM3_d_type)m_dimType);
		switch (alignType)
		{
		case NCTI::NCTI_DCM3_ALIGNMENT:
			if (!NctiExecuteDCM3CommandTool::ExecuteEditAlignmentCommand(pComMan, pDim, (ncti_DCM3_alignment)(m_alignBox->currentIndex() + 1)))
				return;
			break;
		case NCTI::NCTI_DCM3_ORIENTATION:
			if (!NctiExecuteDCM3CommandTool::ExecuteEditSurfOrientCommand(pComMan, pDim, (ncti_DCM3_surface_orientation)(m_alignBox->currentIndex() + 1)))
				return;
			break;
		case NCTI::NCTI_DCM3_TAN_ALIGNMENT:
			break;
		default:
			break;
		}
		if (!NctiExecuteDCM3CommandTool::ExecuteEvaluateCommand(pComMan, pDimSys, std::vector< NctiDisplayDCM3Geometry*>()))
			return;
		std::vector<ncti_DCM3_constraint_data> overConsVec;
		ncti_DCM3_d_node_status status;
		if (!NctiDCM3PubFun::StatusD(pBaseModel, pDimSys, pDim->dcmnode(), status))
		{
			QMessageBox::information(this, "提示", "无法检查是否过约束！");
			return;
		}
		if (status == NCTI_DCM3_D_OVER_DEFINED)
		{
			QMessageBox::information(this, "提示", "修改对齐方式将导致过约束！");
		}
	}
	else
	{
		double value = 0;
		if (m_valueEidt)
			value = m_valueEidt->text().toDouble();
		if (m_dimType == NCTI_DCM3_ANGLE)
			value = value / 180. * M_PI;

		std::string dimName = NctiCreateConstraintScriptPub::GetNewName(pBaseModel, NctiDisplayDCM3Dimension::ID, "dcm3_dim");
		if (!NctiExecuteDCM3CommandTool::ExecuteCreateDimensionCommand(pComMan, dimName.c_str(), (ncti_DCM3_d_type)m_dimType, value, pDim))
			return;

		ncti_DCM3_alignment_type alignType = NctiDCM3PubFun::GetAlignmentType(pGeom1, pGeom2, (ncti_DCM3_d_type)m_dimType);
		switch (alignType)
		{
		case NCTI::NCTI_DCM3_ALIGNMENT:
			if (!NctiExecuteDCM3CommandTool::ExecuteEditAlignmentCommand(pComMan, pDim, (ncti_DCM3_alignment)(m_alignBox->currentIndex() + 1)))
				return;
			break;
		case NCTI::NCTI_DCM3_ORIENTATION:
			if (!NctiExecuteDCM3CommandTool::ExecuteEditSurfOrientCommand(pComMan, pDim, (ncti_DCM3_surface_orientation)(m_alignBox->currentIndex() + 1)))
				return;
			break;
		case NCTI::NCTI_DCM3_TAN_ALIGNMENT:
			break;
		default:
			break;
		}

		if (!NctiExecuteDCM3CommandTool::ExecuteAdddCommand(pComMan, pDimSys, pDim, pGeom1, pGeom2, nullptr, nullptr))
			return;

		if (!NctiExecuteDCM3CommandTool::ExecuteEvaluateCommand(pComMan, pDimSys, std::vector< NctiDisplayDCM3Geometry*>()))
			return;

		ncti_DCM3_d_node_status status;
		if (!NctiDCM3PubFun::StatusD(pBaseModel, pDimSys, pDim->dcmnode(), status))
		{
			QMessageBox::information(this, "提示", "无法检查是否过约束！");
			return;
		}
		if (status == NCTI_DCM3_D_OVER_DEFINED)
		{
			/*NctiExecuteDCM3CommandTool::ExecuteEraseDimensionCommand(pComMan, pDimSys, pDim);
			Ncti_Char script[256];
			NctiString::LocaleSprintf(script, "doc.RunCommand(\"cmd_ncti_delete\", [\"%s\"])", pDim->GetObjName());
			NctiPyCB.RunSimpleString(script);*/
			QMessageBox::information(this, "提示", "添加该约束将导致过约束！");
		}
	}
}


void NCTI::NctiDCM3TwoGeometriesWidget::init()
{
	NctiDisplayDCM3Dimension* pDim = nullptr;
	if (!m_DimObjName.empty() && m_pDocument)
	{
		NctiDisplayObject* pObj = nullptr;
		NctiDocElementPubFun::GetObjectListByName(m_pDocument->GetBaseModel(), NctiDisplayDCM3Dimension::ID, m_DimObjName.c_str(), pObj);
		if (pObj)
		{
			pDim = (NctiDisplayDCM3Dimension*)pObj;
			if (pDim->GetConsGeometries().size() >= 2)
			{
				NctiDisplayDCM3Geometry* pGeom = pDim->GetConsGeometries()[1];
				NctiDCM3Set* pSet = pGeom->get_owner();
				if (pSet)
				{
					m_pSelBody2 = pSet->GetModelBody();
					long ID;
					if (pSet->get_cell(pGeom, ID))
					{
						m_selCellID2 = new long(ID);
					}
				}
			}
		}
	}

	m_selLabel2 = new QLabel;
	setSelLabelTexts("选择对象", "选择对象");
	m_selLabel2->setMinimumSize(QSize(260, 20));
	QPushButton* selBtn = new QPushButton("选择");
	QHBoxLayout* hLayout1 = new QHBoxLayout;
	hLayout1->addWidget(m_selLabel2);
	hLayout1->addWidget(selBtn);
	m_contentLayout->addLayout(hLayout1);

	QLabel* alignLabel = new QLabel("对齐方式");
	m_alignBox = new QComboBox();
	QStringList alignTypes({ "正向", "反向" });
	m_alignBox->addItems(alignTypes);
	QHBoxLayout* hLayout2 = new QHBoxLayout;
	hLayout2->addWidget(alignLabel);
	hLayout2->addWidget(m_alignBox);
	m_contentLayout->addLayout(hLayout2);

	m_valueEidt = nullptr;
	std::vector<int> valDimTypeVec = { NCTI_DCM3_DISTANCE , NCTI_DCM3_ANGLE };
	if (std::find(valDimTypeVec.begin(), valDimTypeVec.end(), m_dimType) != valDimTypeVec.end())
	{
		QLabel* valLabel = new QLabel;
		if (m_dimType == NCTI_DCM3_DISTANCE)
			valLabel->setText("距离");
		else if(m_dimType == NCTI_DCM3_ANGLE)
			valLabel->setText("角度");
		m_valueEidt = new QLineEdit;
		QHBoxLayout* hLayout3 = new QHBoxLayout;
		hLayout3->addWidget(valLabel);
		hLayout3->addWidget(m_valueEidt);
		m_contentLayout->addLayout(hLayout3);
	}
	if (m_mode == NCTI_MODE_EDIT || m_mode == NCTI_MODE_READ)
	{
		selBtn->setEnabled(false);
	}
	if (m_mode == NCTI_MODE_READ)
	{
		m_alignBox->setEnabled(false);
		if(m_valueEidt)
			m_valueEidt->setEnabled(false);
	}
	if (pDim)
	{
		if (m_valueEidt)
		{
			double value = pDim->value();
			if (pDim->type() == NCTI_DCM3_ANGLE)
				value = value * 180.;
			m_valueEidt->setText(QString::number(value));
		}
		if (pDim->GetConsGeometries().size() == 2)
		{
			int index = 0;
			ncti_DCM3_alignment_type alignType = NctiDCM3PubFun::GetAlignmentType(pDim->GetConsGeometries()[0], pDim->GetConsGeometries()[1], pDim->type());
			switch (alignType)
			{
			case NCTI::NCTI_DCM3_ALIGNMENT:
				if (pDim->alignment() == NCTI_DCM3_ALIGNMENT_ANTI_ALIGN)
					index = 1;
				break;
			case NCTI::NCTI_DCM3_ORIENTATION:
				if (pDim->surf_orient() == NCTI_DCM3_SURFACE_ORIENTATION_ANTI_ALIGN)
					index = 1;
				break;
			case NCTI::NCTI_DCM3_TAN_ALIGNMENT:
				break;
			default:
				break;
			}
			m_alignBox->setCurrentIndex(index);
		}
	}
	connect(selBtn, SIGNAL(clicked(bool)), this, SLOT(selBodyCellClick(bool)));
}

void NCTI::NctiDCM3TwoGeometriesWidget::setSelectedText()
{
	if (m_pSelBody2 && m_selCellID2)
	{
		QString text = QString("%1[%2][ID:%3]").arg(m_selLabelText2, QString(m_pSelBody2->GetObjName()), QString::number(*m_selCellID2));
		m_selLabel2->setText(text);
	}
	else if (m_pSelBody2)
	{
		QString text = QString("%1[%2]").arg(m_selLabelText2, QString(m_pSelBody2->GetObjName()));
		m_selLabel2->setText(text);
	}
	else
	{
		m_selLabel2->setText(m_selLabelText2);
	}
	
}

void NctiDCM3TwoGeometriesWidget::selBodyCellClick(bool boo)
{
	m_pSelBody2 = nullptr;
	NCTI_DELETE m_selCellID2;
	m_selCellID2 = nullptr;
	if (m_pDocument)
	{
		std::vector<NctiDisplayObject*> objVec;
		std::vector <std::vector<NCTI_MODEL_TAG>> cellVecVec;
		NctiDocElementPubFun::GetDisplayObjectFromSelManager(m_pDocument, objVec, cellVecVec);
		for (int i = 0; i < objVec.size(); ++i)
		{
			if (objVec[i]->IsTypeName(NctiDisplayModelBody::ID))
			{
				if (!cellVecVec[i].empty())
				{
					m_pSelBody2 = (NctiDisplayModelBody*)objVec[i];
					NctiDisplayDocCustomContainer* pDocCus = (NctiDisplayDocCustomContainer*)m_pSelBody2->GetDocContainer();
					long ID;
					if (pDocCus->get_persistent_tag(m_pSelBody2, cellVecVec[i][0], ID))
					{
						m_selCellID2 = NCTI_NEW long(ID);
					}
					break;
				}
			}
		}
	}
	setSelectedText();
}

