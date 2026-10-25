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

#include "NctiDCM3SingleGeometryWidget.h"

#include <QGroupBox>

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
#include "NctiExecuteDCM3CommandTool.h"
#include "NctiCreateConstraintScriptPub.h"

using namespace NCTI;

NctiDCM3SingleGeometryWidget::NctiDCM3SingleGeometryWidget(NctiDocument* i_pDoc, int i_dimType, NctiMode i_mode, const char* i_DimObjName, QWidget* i_parent)
	:NctiDCM3BaseWidget(i_pDoc, i_parent)
	, m_mode(i_mode)
	, m_DimObjName(i_DimObjName)
	, m_pSelBody1(nullptr)
	, m_selCellID1(nullptr)
{
	setDimensionType(i_dimType);
	init();
}

NctiDCM3SingleGeometryWidget::~NctiDCM3SingleGeometryWidget()
{
	if (m_selCellID1)
	{
		NCTI_DELETE m_selCellID1;
		m_selCellID1 = nullptr;
	}
}


void NCTI::NctiDCM3SingleGeometryWidget::setSelLabelText(const QString& i_text)
{
	m_selLabelText = i_text;
	setSelectedText();
}

void NCTI::NctiDCM3SingleGeometryWidget::execute()
{
	if (m_mode != NCTI_MODE_NEW)
		return;

	if (m_pDocument == nullptr || m_pSelBody1 == nullptr)
		return;
	NctiCommandManager* pComMan = NctiCommandManager::GetCommandManager(m_pDocument->GetBaseModel());
	
	NctiDisplayDCM3DimSys* pDimSys = nullptr;
	if (!GetOrCreateDimSys(m_pDocument, pDimSys))
		return;

	NctiDCM3Set* pCurSet = nullptr;
	if (!GetOrCreateSet(m_pDocument, pDimSys, m_pSelBody1, pCurSet))
		return;

	switch (m_dimType)
	{
	case -1://fix
		NctiExecuteDCM3CommandTool::ExecuteFixCommand(pComMan, pDimSys, pCurSet);
		break;
	default:
		break;
	}
}

bool NCTI::NctiDCM3SingleGeometryWidget::GetOrCreateDimSys(NctiDocument* i_pDoc, NctiDisplayDCM3DimSys*& o_pDimSys)
{
	if (i_pDoc == nullptr)
		return false;
	NctiCommandManager* pComMan = NctiCommandManager::GetCommandManager(i_pDoc->GetBaseModel());
	std::vector<NctiDisplayObject*> pObjVec;
	NctiDocElementPubFun::GetObjectByClassID(i_pDoc, NctiDisplayDCM3DimSys::ID, pObjVec);
	if (pObjVec.empty())
	{
		std::string dimSysName = NctiCreateConstraintScriptPub::GetNewName(i_pDoc->GetBaseModel(), NctiDisplayDCM3DimSys::ID, "dcm3_dimsys");
		if (!NctiExecuteDCM3CommandTool::ExecuteCreateDimSysCommand(pComMan, dimSysName.c_str(), o_pDimSys))
			return false;
	}
	else
	{
		o_pDimSys = (NctiDisplayDCM3DimSys*)pObjVec.front();
	}
	return true;
}

bool NCTI::NctiDCM3SingleGeometryWidget::GetOrCreateSet(NctiDocument* i_pDoc, NctiDisplayDCM3DimSys* i_pDimSys, NctiDisplayModelBody* pBody, NctiDCM3Set*& o_pSet)
{
	if (i_pDoc == nullptr || i_pDimSys == nullptr || pBody == nullptr)
		return false;
	NctiCommandManager* pComMan = NctiCommandManager::GetCommandManager(i_pDoc->GetBaseModel());
	for (auto* pGeom : i_pDimSys->GetDCM3GeometryVec())
	{
		if (pGeom->IsTypeName(NctiDCM3Set::ID))
		{
			if (pGeom->GetModelBody() == pBody)
			{
				o_pSet = (NctiDCM3Set*)pGeom;
				break;
			}
		}
	}
	if (o_pSet == nullptr)
	{
		std::string setName = NctiCreateConstraintScriptPub::GetNewName(i_pDoc->GetBaseModel(), NctiDisplayDCM3Geometry::ID, "dcm3_set");
		if (!NctiExecuteDCM3CommandTool::ExecuteCreateSetCommand(pComMan, setName.c_str(), i_pDimSys, pBody, std::vector<NctiDisplayDCM3Geometry*>(), {}, o_pSet))
			return false;
	}
	return true;
}

bool NCTI::NctiDCM3SingleGeometryWidget::GetOrCreateGeometry(NctiDocument* i_pDoc, NctiDisplayDCM3DimSys* i_pDimSys, NctiDCM3Set* i_pSet, Ncti_Long i_CellID, NctiDisplayDCM3Geometry*& o_pGeom)
{
	if (i_pDoc == nullptr || i_pDimSys == nullptr || i_pSet == nullptr)
		return false;
	NctiCommandManager* pComMan = NctiCommandManager::GetCommandManager(i_pDoc->GetBaseModel());
	for (int i = 0; i < i_pSet->num(); ++i)
	{
		long cellID;
		if (i_pSet->get_cell(i_pSet->member(i), cellID))
		{
			if (cellID == i_CellID)
			{
				o_pGeom = i_pSet->member(i);
				return true;
			}
		}
	}

	if (!NctiExecuteDCM3CommandTool::ExecuteCreateGeometryCommand(pComMan, i_pDimSys, i_pSet->GetModelBody(), i_CellID, o_pGeom))
		return false;
	i_pSet->set_cell(o_pGeom, i_CellID);
	std::vector<NctiDisplayDCM3Geometry*> pGeomVec = { o_pGeom };
	if (!NctiExecuteDCM3CommandTool::ExecuteMoveToSetCommand(pComMan, i_pDimSys, i_pSet, pGeomVec))
		return false;

	return true;
}

bool NCTI::NctiDCM3SingleGeometryWidget::GetDimension(NctiDocument* i_pDoc, NctiDisplayDCM3Geometry* i_pGeom1, NctiDisplayDCM3Geometry* i_pGeom2, NctiDisplayDCM3Geometry* i_pGeom3, ncti_DCM3_d_type i_dt, NctiDisplayDCM3Dimension*& o_pDim)
{
	std::vector< NctiDisplayDCM3Geometry*> pGeomVec{ i_pGeom1, i_pGeom2, i_pGeom3 };
	pGeomVec.erase(std::remove(pGeomVec.begin(), pGeomVec.end(), nullptr), pGeomVec.end());
	std::sort(pGeomVec.begin(), pGeomVec.end());
	std::vector<NctiDisplayObject*> pObjVec;
	NctiDocElementPubFun::GetObjectByClassID(i_pDoc, NctiDisplayDCM3Dimension::ID, pObjVec);
	for (auto* pObj : pObjVec)
	{
		NctiDisplayDCM3Dimension* pDim = (NctiDisplayDCM3Dimension*)pObj;
		std::vector< NctiDisplayDCM3Geometry*> pTmpGeomVec = pDim->GetConsGeometries();
		std::sort(pTmpGeomVec.begin(), pTmpGeomVec.end());
		if (pGeomVec == pTmpGeomVec)
		{
			if (pDim->type() == i_dt)
			{
				o_pDim = pDim;
				return true;
			}
		}
	}
	return false;
}



void NCTI::NctiDCM3SingleGeometryWidget::init()
{
	if (!m_DimObjName.empty() && m_pDocument)
	{
		NctiDisplayObject* pObj = nullptr;
		NctiDocElementPubFun::GetObjectListByName(m_pDocument->GetBaseModel(), NctiDisplayDCM3Dimension::ID, m_DimObjName.c_str(), pObj);
		if (pObj)
		{
			NctiDisplayDCM3Dimension* pDim = (NctiDisplayDCM3Dimension*)pObj;
			if (!pDim->GetConsGeometries().empty())
			{
				NctiDisplayDCM3Geometry* pGeom = pDim->GetConsGeometries()[0];
				NctiDCM3Set* pSet = pGeom->get_owner();
				if (pSet)
				{
					m_pSelBody1 = pSet->GetModelBody();
					long ID;
					if (pSet->get_cell(pGeom, ID))
					{
						m_selCellID1 = new long(ID);
					}
				}
			}
		}
	}
	m_mainLayout = new QVBoxLayout(this);
	QGroupBox* group = new QGroupBox("要约束的几何体");
	m_contentLayout = new QVBoxLayout(group);
	QHBoxLayout* hLayout = new QHBoxLayout;
	m_selLabel1 = new QLabel;
	setSelLabelText("选择对象");
	m_selLabel1->setMinimumSize(QSize(260, 20));
	QPushButton* selBtn = new QPushButton("选择");
	hLayout->addWidget(m_selLabel1);
	hLayout->addWidget(selBtn);
	m_contentLayout->addLayout(hLayout);
	if(m_mode != NCTI_MODE_NEW)
		selBtn->setEnabled(false);

	m_mainLayout->addWidget(group);
	connect(selBtn, SIGNAL(clicked(bool)), this, SLOT(selBodyCellClick(bool)));
}

void NCTI::NctiDCM3SingleGeometryWidget::setSelectedText()
{
	if (m_pSelBody1)
	{
		QString text;
		if (m_dimType == -1 || !m_selCellID1)
		{
			text = QString("%1[%2]").arg(m_selLabelText, QString(m_pSelBody1->GetObjName()));
		}
		else
		{
			text = QString("%1[%2][ID:%3]").arg(m_selLabelText, QString(m_pSelBody1->GetObjName()), QString::number(*m_selCellID1));
		}
		m_selLabel1->setText(text);
	
	}
	else
	{
		m_selLabel1->setText(m_selLabelText);
	}
	
}

void NctiDCM3SingleGeometryWidget::selBodyCellClick(bool boo)
{
	m_pSelBody1 = nullptr;
	NCTI_DELETE m_selCellID1;
	m_selCellID1 = nullptr;
	if (m_pDocument)
	{
		std::vector<NctiDisplayObject*> objVec;
		std::vector <std::vector<NCTI_MODEL_TAG>> cellVecVec;
		NctiDocElementPubFun::GetDisplayObjectFromSelManager(m_pDocument, objVec, cellVecVec);
		for (int i = 0; i < objVec.size(); ++i)
		{
			if (objVec[i]->IsTypeName(NctiDisplayModelBody::ID))
			{
				m_pSelBody1 = (NctiDisplayModelBody*)objVec[i];
				if (!cellVecVec[i].empty())
				{
					NctiDisplayDocCustomContainer* pDocCus = (NctiDisplayDocCustomContainer*)m_pSelBody1->GetDocContainer();
					long ID;
					if (pDocCus->get_persistent_tag(m_pSelBody1, cellVecVec[i][0], ID))
					{
						m_selCellID1 = new long(ID);
					}
					break;
				}
			}
		}
	}
	setSelectedText();
}

