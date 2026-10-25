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

#include "NctiDCM3BaseWidget.h"

#include "NctiAddCentralizeForceDlg.h"
#include "NctiDocument.h"
using namespace NCTI;

NctiDCM3BaseWidget::NctiDCM3BaseWidget(NctiDocument* i_pDoc, QWidget* i_parent)
	:QWidget(i_parent)
	, m_pDocument(i_pDoc)
	, m_dimType(-1)
{
}

NctiDCM3BaseWidget::~NctiDCM3BaseWidget()
{
}

void NCTI::NctiDCM3BaseWidget::setDimensionType(int i_dimType)
{
	m_dimType = i_dimType;
}
