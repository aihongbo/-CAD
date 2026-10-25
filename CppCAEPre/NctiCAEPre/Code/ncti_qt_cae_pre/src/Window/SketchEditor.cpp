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

#include "SketchEditor.h"
#include <QMessageBox>

#include "NctiHandler.h"

#include "NctiWindowPlatform.h"

namespace NCTI {

SketchEditor::SketchEditor(MainWindow* mainWindow)
    : MainWindowModule(mainWindow)
{
}

void SketchEditor::initialize()
{
    connect(m_mainWindow->Signals(), &MainWindowSignals::draftNew, this, &SketchEditor::onDraftNew);
    connect(m_mainWindow->Signals(), &MainWindowSignals::draftEdit, this, &SketchEditor::onDraftEdit);
    connect(m_mainWindow->Signals(), &MainWindowSignals::draftCoord, this, &SketchEditor::onDraftCoord);
    connect(m_mainWindow->Signals(), &MainWindowSignals::deleteDraft, this, &SketchEditor::onDeleteDraft);
    connect(m_mainWindow->Signals(), &MainWindowSignals::draftRectangle, this, &SketchEditor::onDraftRectangle);
    connect(m_mainWindow->Signals(), &MainWindowSignals::draftCircle, this, &SketchEditor::onDraftCircle);
    connect(m_mainWindow->Signals(), &MainWindowSignals::draftPolygon, this, &SketchEditor::onDraftPolygon);
    connect(m_mainWindow->Signals(), &MainWindowSignals::draftEllipse, this, &SketchEditor::onDraftEllipse);
    connect(m_mainWindow->Signals(), &MainWindowSignals::draftCircleToCircle, this, &SketchEditor::onDraftCircleToCircle);
    connect(m_mainWindow->Signals(), &MainWindowSignals::draftLine, this, &SketchEditor::onDraftLine);
    connect(m_mainWindow->Signals(), &MainWindowSignals::draftArc, this, &SketchEditor::onDraftArc);
    connect(m_mainWindow->Signals(), &MainWindowSignals::draftWire, this, &SketchEditor::onDraftWire);
    connect(m_mainWindow->Signals(), &MainWindowSignals::draftBspline, this, &SketchEditor::onDraftBspline);
    connect(m_mainWindow->Signals(), &MainWindowSignals::draftCenterline, this, &SketchEditor::onDraftCenterline);
    connect(m_mainWindow->Signals(), &MainWindowSignals::draftPoint, this, &SketchEditor::onDraftPoint);
    connect(m_mainWindow->Signals(), &MainWindowSignals::draftMoveToTop, this, &SketchEditor::onDraftMoveToTop);
    connect(m_mainWindow->Signals(), &MainWindowSignals::draftMoveToBottom, this, &SketchEditor::onDraftMoveToBottom);
    connect(m_mainWindow->Signals(), &MainWindowSignals::draftUpside, this, &SketchEditor::onDraftUpside);
    connect(m_mainWindow->Signals(), &MainWindowSignals::draftDownside, this, &SketchEditor::onDraftDownside);
    connect(m_mainWindow->Signals(), &MainWindowSignals::draftUnit, this, &SketchEditor::onDraftUnit);
    connect(m_mainWindow->Signals(), &MainWindowSignals::draftCut, this, &SketchEditor::onDraftCut);
    connect(m_mainWindow->Signals(), &MainWindowSignals::draftImplode, this, &SketchEditor::onDraftImplode);
    connect(m_mainWindow->Signals(), &MainWindowSignals::draftExplode, this, &SketchEditor::onDraftExplode);
    connect(m_mainWindow->Signals(), &MainWindowSignals::draftResetView, this, &SketchEditor::onDraftResetView);
    connect(m_mainWindow->Signals(), &MainWindowSignals::draftExit, this, &SketchEditor::onDraftExit);
    connect(m_mainWindow->Signals(), &MainWindowSignals::draftExtrude, this, &SketchEditor::onDraftExtrude);
    connect(m_mainWindow->Signals(), &MainWindowSignals::draftRotate, this, &SketchEditor::onDraftRotate);
    connect(m_mainWindow->Signals(), &MainWindowSignals::draftFeatureBoolean, this, &SketchEditor::onDraftFeatureBoolean);
    connect(m_mainWindow->Signals(), &MainWindowSignals::draftRebuild, this, &SketchEditor::onDraftRebuild);
    connect(m_mainWindow->Signals(), &MainWindowSignals::draftModelization, this, &SketchEditor::onDraftModelization);
    connect(m_mainWindow->Signals(), &MainWindowSignals::draftParallel, this, &SketchEditor::onDraftParallel);
    connect(m_mainWindow->Signals(), &MainWindowSignals::draftPerpendicular, this, &SketchEditor::onDraftPerpendicular);
    connect(m_mainWindow->Signals(), &MainWindowSignals::draftTangent, this, &SketchEditor::onDraftTangent);
    connect(m_mainWindow->Signals(), &MainWindowSignals::draftEqualRadius, this, &SketchEditor::onDraftEqualRadius);
    connect(m_mainWindow->Signals(), &MainWindowSignals::draftFix, this, &SketchEditor::onDraftFix);
    connect(m_mainWindow->Signals(), &MainWindowSignals::draftCoincident, this, &SketchEditor::onDraftCoincident);
    connect(m_mainWindow->Signals(), &MainWindowSignals::draftConcentric, this, &SketchEditor::onDraftConcentric);
    connect(m_mainWindow->Signals(), &MainWindowSignals::draftSymmetric, this, &SketchEditor::onDraftSymmetric);
    connect(m_mainWindow->Signals(), &MainWindowSignals::draftDistance, this, &SketchEditor::onDraftDistance);
    connect(m_mainWindow->Signals(), &MainWindowSignals::draftAngle, this, &SketchEditor::onDraftAngle);
    connect(m_mainWindow->Signals(), &MainWindowSignals::draftRadius, this, &SketchEditor::onDraftRadius);
}

void SketchEditor::onDraftNew()
{
    Ncti_Boolean boo = NctiHandler::SketchNew(m_mainWindow->getWindowPlatform());
    if (boo == false)
        QMessageBox::warning(m_mainWindow, "Command", "Command execution failure");
}

void SketchEditor::onDraftEdit()
{
    Ncti_Boolean boo = NctiHandler::SketchEdit(m_mainWindow->getWindowPlatform());
    if (boo == false)
        QMessageBox::warning(m_mainWindow, "Command", "Command execution failure");
}

void SketchEditor::onDraftCoord()
{
    Ncti_Boolean boo = NctiHandler::SketchCoord(m_mainWindow->getWindowPlatform());
    if (boo == false)
        QMessageBox::warning(m_mainWindow, "Command", "Command execution failure");
}

void SketchEditor::onDeleteDraft()
{
    Ncti_Boolean boo = NctiHandler::SketchDelete(m_mainWindow->getWindowPlatform());
    if (boo == false)
        QMessageBox::warning(m_mainWindow, "Command", "Command execution failure");
}

void SketchEditor::onDraftRectangle()
{
    Ncti_Boolean boo = NctiHandler::SketchRectangle(m_mainWindow->getWindowPlatform());
    if (boo == false)
        QMessageBox::warning(m_mainWindow, "Command", "Command execution failure");
}

void SketchEditor::onDraftCircle()
{
    Ncti_Boolean boo = NctiHandler::SketchCircle(m_mainWindow->getWindowPlatform());
    if (boo == false)
        QMessageBox::warning(m_mainWindow, "Command", "Command execution failure");
}

void SketchEditor::onDraftPolygon()
{
    Ncti_Boolean boo = NctiHandler::SketchPolygon(m_mainWindow->getWindowPlatform());
    if (boo == false)
        QMessageBox::warning(m_mainWindow, "Command", "Command execution failure");
}

void SketchEditor::onDraftEllipse()
{
    Ncti_Boolean boo = NctiHandler::SketchEllipse(m_mainWindow->getWindowPlatform());
    if (boo == false)
        QMessageBox::warning(m_mainWindow, "Command", "Command execution failure");
}

void SketchEditor::onDraftCircleToCircle()
{
    Ncti_Boolean boo = NctiHandler::SketchCircleToCircle(m_mainWindow->getWindowPlatform());
    if (boo == false)
        QMessageBox::warning(m_mainWindow, "Command", "Command execution failure");
}

void SketchEditor::onDraftLine()
{
    Ncti_Boolean boo = NctiHandler::SketchLine(m_mainWindow->getWindowPlatform());
    if (boo == false)
        QMessageBox::warning(m_mainWindow, "Command", "Command execution failure");
}

void SketchEditor::onDraftArc()
{
    Ncti_Boolean boo = NctiHandler::SketchArc(m_mainWindow->getWindowPlatform());
    if (boo == false)
        QMessageBox::warning(m_mainWindow, "Command", "Command execution failure");
}

void SketchEditor::onDraftWire()
{
    Ncti_Boolean boo = NctiHandler::SketchWire(m_mainWindow->getWindowPlatform());
    if (boo == false)
        QMessageBox::warning(m_mainWindow, "Command", "Command execution failure");
}

void SketchEditor::onDraftBspline()
{
    Ncti_Boolean boo = NctiHandler::SketchBspline(m_mainWindow->getWindowPlatform());
    if (boo == false)
        QMessageBox::warning(m_mainWindow, "Command", "Command execution failure");
}

void SketchEditor::onDraftCenterline()
{
    Ncti_Boolean boo = NctiHandler::SketchCenterline(m_mainWindow->getWindowPlatform());
    if (boo == false)
        QMessageBox::warning(m_mainWindow, "Command", "Command execution failure");
}

void SketchEditor::onDraftPoint()
{
    Ncti_Boolean boo = NctiHandler::SketchPoint(m_mainWindow->getWindowPlatform());
    if (boo == false)
        QMessageBox::warning(m_mainWindow, "Command", "Command execution failure");
}

void SketchEditor::onDraftResetView()
{
    Ncti_Boolean boo = NctiHandler::SketchResetView(m_mainWindow->getWindowPlatform());
    if (boo == false)
        QMessageBox::warning(m_mainWindow, "Command", "Command execution failure");
}

void SketchEditor::onDraftExit()
{
    Ncti_Boolean boo = NctiHandler::SketchExit(m_mainWindow->getWindowPlatform());
    if (boo == false)
        QMessageBox::warning(m_mainWindow, "Command", "Command execution failure");
}

void SketchEditor::onDraftExtrude()
{
    Ncti_Boolean boo = NctiHandler::SketchPrism(m_mainWindow->getWindowPlatform());
    if (boo == false)
        QMessageBox::warning(m_mainWindow, "Command", "Command execution failure");
}

void SketchEditor::onDraftRotate()
{
    Ncti_Boolean boo = NctiHandler::SketchRotate(m_mainWindow->getWindowPlatform());
    if (boo == false)
        QMessageBox::warning(m_mainWindow, "Command", "Command execution failure");
}

void SketchEditor::onDraftFeatureBoolean()
{
    Ncti_Boolean boo = NctiHandler::onDraftFeatureBoolean(m_mainWindow->getWindowPlatform());
    if (boo == false)
        QMessageBox::warning(m_mainWindow, "Command", "Command execution failure");
}

void SketchEditor::onDraftModelization()
{
    Ncti_Boolean boo = NctiHandler::SketchModelization(m_mainWindow->getWindowPlatform());
    if (boo == false)
        QMessageBox::warning(m_mainWindow, "Command", "Command execution failure");
}

void SketchEditor::onDraftParallel()
{
    Ncti_Boolean boo = NctiHandler::SketchParallel(m_mainWindow->getWindowPlatform());
    if (boo == false)
        QMessageBox::warning(m_mainWindow, "Command", "Command execution failure");
}

void SketchEditor::onDraftPerpendicular()
{
    Ncti_Boolean boo = NctiHandler::SketchPerpendicular(m_mainWindow->getWindowPlatform());
    if (boo == false)
        QMessageBox::warning(m_mainWindow, "Command", "Command execution failure");
}

void SketchEditor::onDraftTangent()
{
    Ncti_Boolean boo = NctiHandler::SketchTangent(m_mainWindow->getWindowPlatform());
    if (boo == false)
        QMessageBox::warning(m_mainWindow, "Command", "Command execution failure");
}

void SketchEditor::onDraftFix()
{
    Ncti_Boolean boo = NctiHandler::SketchFix(m_mainWindow->getWindowPlatform());
    if (boo == false)
        QMessageBox::warning(m_mainWindow, "Command", "Command execution failure");
}

void SketchEditor::onDraftCoincident()
{
    QMessageBox::warning(m_mainWindow, "Command", "Command not implemented");
}

void SketchEditor::onDraftConcentric()
{
    Ncti_Boolean boo = NctiHandler::SketchConcentric(m_mainWindow->getWindowPlatform());
    if (boo == false)
        QMessageBox::warning(m_mainWindow, "Command", "Command execution failure");
}

void SketchEditor::onDraftEqualRadius()
{
    Ncti_Boolean boo = NctiHandler::SketchEqualRadius(m_mainWindow->getWindowPlatform());
    if (boo == false)
        QMessageBox::warning(m_mainWindow, "Command", "Command execution failure");
}

void SketchEditor::onDraftSymmetric()
{
    QMessageBox::warning(m_mainWindow, "Command", "Command not implemented");
}

void SketchEditor::onDraftDistance()
{
    Ncti_Boolean boo = NctiHandler::SketchDistance(m_mainWindow->getWindowPlatform());
    if (boo == false)
        QMessageBox::warning(m_mainWindow, "Command", "Command execution failure");
}

void SketchEditor::onDraftAngle()
{
    QMessageBox::warning(m_mainWindow, "Command", "Command not implemented");
}

void SketchEditor::onDraftRadius()
{
    QMessageBox::warning(m_mainWindow, "Command", "Command not implemented");
}

void SketchEditor::onDraftRebuild()
{
    Ncti_Boolean boo = NctiHandler::SketchRebuild(m_mainWindow->getWindowPlatform());
    if (boo == false)
        QMessageBox::warning(m_mainWindow, "Command", "Command execution failure");
}

void SketchEditor::onDraftMoveToTop()
{
    Ncti_Boolean boo = NctiHandler::SketchMoveToTop(m_mainWindow->getWindowPlatform());
    if (boo == false)
        QMessageBox::warning(m_mainWindow, "Command", "Command execution failure");
}

void SketchEditor::onDraftMoveToBottom()
{
    Ncti_Boolean boo = NctiHandler::SketchMoveToBottom(m_mainWindow->getWindowPlatform());
    if (boo == false)
        QMessageBox::warning(m_mainWindow, "Command", "Command execution failure");
}

void SketchEditor::onDraftUpside()
{
    Ncti_Boolean boo = NctiHandler::SketchUpside(m_mainWindow->getWindowPlatform());
    if (boo == false)
        QMessageBox::warning(m_mainWindow, "Command", "Command execution failure");
}

void SketchEditor::onDraftDownside()
{
    Ncti_Boolean boo = NctiHandler::SketchDownside(m_mainWindow->getWindowPlatform());
    if (boo == false)
        QMessageBox::warning(m_mainWindow, "Command", "Command execution failure");
}

void SketchEditor::onDraftUnit()
{
    Ncti_Boolean boo = NctiHandler::SketchUnit(m_mainWindow->getWindowPlatform());
    if (boo == false)
        QMessageBox::warning(m_mainWindow, "Command", "Command execution failure");
}

void SketchEditor::onDraftCut()
{
    Ncti_Boolean boo = NctiHandler::SketchCut(m_mainWindow->getWindowPlatform());
    if (boo == false)
        QMessageBox::warning(m_mainWindow, "Command", "Command execution failure");
}

void SketchEditor::onDraftImplode()
{
    Ncti_Boolean boo = NctiHandler::SketchImplode(m_mainWindow->getWindowPlatform());
    if (boo == false)
        QMessageBox::warning(m_mainWindow, "Command", "Command execution failure");
}

void SketchEditor::onDraftExplode()
{
    Ncti_Boolean boo = NctiHandler::SketchExplode(m_mainWindow->getWindowPlatform());
    if (boo == false)
        QMessageBox::warning(m_mainWindow, "Command", "Command execution failure");
}

} // namespace NCTI