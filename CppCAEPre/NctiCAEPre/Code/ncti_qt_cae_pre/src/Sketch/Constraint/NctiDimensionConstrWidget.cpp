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

#include "NctiDimensionConstrWidget.h"
#include "NctiDocElementPubFun.h"
#include "NctiDisplayObject.h"
#include "NctiDisplaySketchCurve.h"
#include "NctiDisplaySketchSurface.h"
#include "NctiSketchConstrManager.h"
#include "NctiDisplayObjectLifeCycleManager.h"
#include "NctiHistoryManager.h"
#include "NctiDocument.h"
#include <QVBoxLayout>
#include <QGroupBox>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QMessageBox>
using namespace NCTI;

NctiDimensionConstrWidget::NctiDimensionConstrWidget(NctiDocument* i_doc, ncti_DCM_d_type i_dt, QWidget* i_parent)
	:NctiConstrContentWidget(i_doc, i_dt, i_parent)
	, m_selCurve1(nullptr)
	, m_selCurve2(nullptr)
{
	init();
}

NctiDimensionConstrWidget::~NctiDimensionConstrWidget()
{
}

void NCTI::NctiDimensionConstrWidget::selCurve1()
{
	NctiDocument* doc = getDoc();
	if (doc)
	{
		std::vector<NctiDisplayObject*> selObjVec;
		NctiDocElementPubFun::GetDisplayObjectFromSelManager(doc, selObjVec);

		std::vector<NctiDisplaySketchObject*> sketchCurveVec;
		for (auto obj : selObjVec)
		{
			if (obj->IsTypeName(NctiDisplaySketchCurve::ID)
				|| obj->IsTypeName(NctiDisplaySketchSurface::ID))
				sketchCurveVec.push_back((NctiDisplaySketchObject*)obj);
		}
		if (!sketchCurveVec.empty())
		{
			QLabel* label = findChild<QLabel*>("curve1");
			if (label)
			{
				label->setText(tr("选择曲线1 (1)"));
				label->setStyleSheet("color: green;");
				m_selCurve1 = sketchCurveVec.back();
			}
		}
	}
}

void NCTI::NctiDimensionConstrWidget::selCurve2()
{
	NctiDocument* doc = getDoc();
	if (doc)
	{
		std::vector<NctiDisplayObject*> selObjVec;
		NctiDocElementPubFun::GetDisplayObjectFromSelManager(doc, selObjVec);

		std::vector<NctiDisplaySketchObject*> sketchCurveVec;
		for (auto obj : selObjVec)
		{
			if (obj->IsTypeName(NctiDisplaySketchObject::ID))
				sketchCurveVec.push_back((NctiDisplaySketchObject*)obj);
		}
		if (!sketchCurveVec.empty())
		{
			QLabel* label = findChild<QLabel*>("curve2");
			if (label)
			{
				label->setText(tr("选择曲线2 (1)"));
				label->setStyleSheet("color: green;");
				m_selCurve2 = sketchCurveVec.back();
			}
		}
	}
}

void NCTI::NctiDimensionConstrWidget::init()
{
	QVBoxLayout* mainLayout = new QVBoxLayout(this);

	QGroupBox* motionGroup = new QGroupBox(tr("运动"));
	QVBoxLayout* motionLayout = new QVBoxLayout(motionGroup);

    QHBoxLayout* curveLayout1 = new QHBoxLayout();
    QLabel* curveLabel1 = new QLabel(tr("选择曲线1 (0)"));
	curveLabel1->setObjectName("curve1");
    curveLabel1->setStyleSheet("color: red;");
    curveLayout1->addWidget(curveLabel1);
    QPushButton* curveSelBtn1 = new QPushButton("选择");
    curveLayout1->addWidget(curveSelBtn1);

    QHBoxLayout* curveLayout2 = new QHBoxLayout();
    QLabel* curveLabel2 = new QLabel(tr("选择曲线2 (0)"));
	curveLabel2->setObjectName("curve2");
	curveLabel2->setStyleSheet("color: red;");
    curveLayout2->addWidget(curveLabel2);
    QPushButton* curveSelBtn2 = new QPushButton("选择");
    curveLayout2->addWidget(curveSelBtn2);

	QHBoxLayout* curveLayout3 = new QHBoxLayout();
	QLabel* valueLabel = new QLabel(tr("距离"));
	QLineEdit* valueEdit = new QLineEdit();
	valueEdit->setObjectName("value");
	curveLayout3->addWidget(valueLabel);
	curveLayout3->addWidget(valueEdit);

	motionLayout->addLayout(curveLayout1);
	motionLayout->addLayout(curveLayout2);
	motionLayout->addLayout(curveLayout3);
    mainLayout->addWidget(motionGroup);

	connect(curveSelBtn1, SIGNAL(clicked()), this, SLOT(selCurve1()));
	connect(curveSelBtn2, SIGNAL(clicked()), this, SLOT(selCurve2()));
}

bool NCTI::NctiDimensionConstrWidget::apply()
{
	double value = 0;
	QLineEdit* valueEdit = findChild<QLineEdit*>("value");
	if (valueEdit)
	{
		value = valueEdit->text().toDouble();
	}

	NctiSketchConstrSolver* solver = getSolver();
	NctiSketchConstrManager* pConstrMan = solver->getSketchConstrManager();
	if (pConstrMan)
	{
		NctiHistoryManager* pHisMan = NctiHistoryManager::GetHistoryManager(pConstrMan->GetLCM()->GetBaseModel());
		if (pHisMan && pHisMan->GetActive())
		{
			int iDepth = 0;
			pHisMan->StartState("MSG::Sketch Create Constraint And Solve", iDepth);
		}
		NCTI_API_BEGIN(pHisMan)
			pConstrMan->addConstraint(getConstrType(), m_selCurve1, m_selCurve2, value);
		NCTI_API_END;
		if (solver)
		{
			bool success = solver->solve();
			if (success)
			{
				if (!solver->isOverDefined())
				{
					solver->apply();
				}
				else
				{
					QMessageBox::warning(this, "过约束", "添加该约束将导致过约束");
					if (pHisMan && pHisMan->GetActive())
					{
						int iDepth = 0;
						pHisMan->NoteState(NCTI_FAILED, iDepth);
					}
					return false;
				}
			}
		}

		if (pHisMan && pHisMan->GetActive())
		{
			int iDepth = 0;
			pHisMan->NoteState(NCTI_SUCCEEDED, iDepth);
		}
	}
	
	return true;
}

