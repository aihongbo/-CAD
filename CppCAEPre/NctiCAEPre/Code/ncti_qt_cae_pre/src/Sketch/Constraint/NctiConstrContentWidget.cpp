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

#include "NctiConstrContentWidget.h"
#include "NctiSketchConstrSolver.h"
#include "NctiDocument.h"
#include "NctiDocViewManager.h"
#include "NctiDisplayDocSketch.h"
using namespace NCTI;

NctiConstrContentWidget::NctiConstrContentWidget(NctiDocument* i_doc, ncti_DCM_d_type i_dt, QWidget* i_parent)
	:QWidget(i_parent)
	, m_doc(i_doc)
	, m_constrType(i_dt)
	, m_solver(nullptr)
{
	if (m_doc)
	{
		NctiDocViewManager* pDocViewMan = NctiDocViewManager::GetDocViewManager(m_doc->GetBaseModel());
		if (pDocViewMan != NULL)
		{
			NctiDisplayDocSketch* pSketchDoc = (NctiDisplayDocSketch*)pDocViewMan->GetActiveDocSketch();
			m_solver = new NctiSketchConstrSolver(pSketchDoc);
		}
	}
}

NctiConstrContentWidget::~NctiConstrContentWidget()
{
	if (m_solver)
		delete m_solver;
}

NctiDocument* NCTI::NctiConstrContentWidget::getDoc() const
{
	return m_doc;
}

ncti_DCM_d_type NCTI::NctiConstrContentWidget::getConstrType() const
{
	return m_constrType;
}

NctiSketchConstrSolver* NCTI::NctiConstrContentWidget::getSolver() const
{
	return m_solver;
}


