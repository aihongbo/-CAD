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

#include "NctiFixConstrWidget.h"
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
using namespace NCTI;

NctiFixConstrWidget::NctiFixConstrWidget(NctiDocument* i_doc, QWidget* i_parent)
	:NctiConstrContentWidget(i_doc, NCTI_DCM_D_UNKNOWN, i_parent)
	, m_selGeom(nullptr)
{
	init();
}

NctiFixConstrWidget::~NctiFixConstrWidget()
{
}

void NCTI::NctiFixConstrWidget::selGeometry()
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
				label->setText(tr("选择曲线 (1)"));
				label->setStyleSheet("color: green;");
				m_selGeom = sketchCurveVec.back();
			}
		}
	}
}

void NCTI::NctiFixConstrWidget::init()
{
	QVBoxLayout* mainLayout = new QVBoxLayout(this);

	QGroupBox* motionGroup = new QGroupBox(tr("要固定的曲线或点"));
	QVBoxLayout* motionLayout = new QVBoxLayout(motionGroup);

    QHBoxLayout* curveLayout1 = new QHBoxLayout();
    QLabel* curveLabel1 = new QLabel(tr("选择曲线或点 (0)"));
	curveLabel1->setObjectName("curve1");
    curveLabel1->setStyleSheet("color: red;");
    curveLayout1->addWidget(curveLabel1);
    QPushButton* curveSelBtn1 = new QPushButton("选择");
    curveLayout1->addWidget(curveSelBtn1);

	motionLayout->addLayout(curveLayout1);
    mainLayout->addWidget(motionGroup);

	connect(curveSelBtn1, SIGNAL(clicked()), this, SLOT(selGeometry()));
}

bool NCTI::NctiFixConstrWidget::apply()
{
	NctiSketchConstrSolver* solver = getSolver();
	NctiSketchConstrManager* pConstrMan = solver->getSketchConstrManager();
	if (pConstrMan)
	{
		NctiHistoryManager* pHisMan = NctiHistoryManager::GetHistoryManager(pConstrMan->GetLCM()->GetBaseModel());
		if (pHisMan && pHisMan->GetActive())
		{
			int iDepth = 0;
			pHisMan->StartState("MSG::Sketch Fix Geometry", iDepth);
		}
		NCTI_API_BEGIN(pHisMan)
			pConstrMan->fixGeometry(m_selGeom);
		NCTI_API_END;
	

		if (pHisMan && pHisMan->GetActive())
		{
			int iDepth = 0;
			pHisMan->NoteState(NCTI_SUCCEEDED, iDepth);
		}
	}
	
	return true;
}

