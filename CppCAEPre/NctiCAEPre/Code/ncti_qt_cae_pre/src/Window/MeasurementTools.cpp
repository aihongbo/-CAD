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

#include "MeasurementTools.h"
#include "NctiMeasuringTool.h"
#include "NctiQTPubFun.h"


namespace NCTI {

MeasurementTools::MeasurementTools(MainWindow* mainWindow)
    : MainWindowModule(mainWindow)
{
}

void MeasurementTools::initialize()
{
}

void MeasurementTools::onMeasuringPt()
{
    NctiDocument* i_pDocument = NctiQTPubFun::GetCurrentViewDocment(m_mainWindow->getWindowPlatform());
    NctiMeasuringTool::instance()->Position(i_pDocument);
}

void MeasurementTools::onMeasuringLen()
{
    NctiDocument* i_pDocument = NctiQTPubFun::GetCurrentViewDocment(m_mainWindow->getWindowPlatform());
    NctiMeasuringTool::instance()->Length(i_pDocument);
}

void MeasurementTools::onMeasuringMid()
{
    NctiDocument* i_pDocument = NctiQTPubFun::GetCurrentViewDocment(m_mainWindow->getWindowPlatform());
    NctiMeasuringTool::instance()->MidPosition(i_pDocument);
}

void MeasurementTools::onMeasuringCenter()
{
    NctiDocument* i_pDocument = NctiQTPubFun::GetCurrentViewDocment(m_mainWindow->getWindowPlatform());
    NctiMeasuringTool::instance()->Center(i_pDocument);
}

void MeasurementTools::onMeasuringRadius()
{
    NctiDocument* i_pDocument = NctiQTPubFun::GetCurrentViewDocment(m_mainWindow->getWindowPlatform());
    NctiMeasuringTool::instance()->Radius(i_pDocument);
}

void MeasurementTools::onMeasuringVector()
{
    NctiDocument* i_pDocument = NctiQTPubFun::GetCurrentViewDocment(m_mainWindow->getWindowPlatform());
    NctiMeasuringTool::instance()->Vector(i_pDocument);
}

void MeasurementTools::onMeasuringAngle()
{
    NctiDocument* i_pDocument = NctiQTPubFun::GetCurrentViewDocment(m_mainWindow->getWindowPlatform());
    NctiMeasuringTool::instance()->Angle(i_pDocument);
}

} // namespace NCTI