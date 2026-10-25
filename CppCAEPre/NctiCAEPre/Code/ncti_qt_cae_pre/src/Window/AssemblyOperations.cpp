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

#include "AssemblyOperations.h"
#include "NctiHandler.h"
#include "NctiWindowPlatform.h"

#include <QMessageBox>

namespace NCTI {

AssemblyOperations::AssemblyOperations(MainWindow* mainWindow)
    : MainWindowModule(mainWindow)
{
}

void AssemblyOperations::initialize()
{
    connect(m_mainWindow->Signals(), &MainWindowSignals::consFix, this, &AssemblyOperations::onConsFix);
    connect(m_mainWindow->Signals(), &MainWindowSignals::consCoincident, this, &AssemblyOperations::onConsCoincident);
    connect(m_mainWindow->Signals(), &MainWindowSignals::consParallel, this, &AssemblyOperations::onConsParallel);
    connect(m_mainWindow->Signals(), &MainWindowSignals::consConcentric, this, &AssemblyOperations::onConsConcentric);
    connect(m_mainWindow->Signals(), &MainWindowSignals::consPerpendicular, this, &AssemblyOperations::onConsPerpendicular);
    connect(m_mainWindow->Signals(), &MainWindowSignals::consDistance, this, &AssemblyOperations::onConsDistance);
    connect(m_mainWindow->Signals(), &MainWindowSignals::consAngle, this, &AssemblyOperations::onConsAngle);
    connect(m_mainWindow->Signals(), &MainWindowSignals::consEqualDistance, this, &AssemblyOperations::onConsEqualDistance);
    connect(m_mainWindow->Signals(), &MainWindowSignals::assExport, this, &AssemblyOperations::onAssExport);
}

void AssemblyOperations::onConsCoincident()
{
    Ncti_Boolean boo = NctiHandler::AssCoincident(m_mainWindow->getWindowPlatform());
    if (boo == false)
        QMessageBox::warning(m_mainWindow, "Command", "Command execution failure");
}

void AssemblyOperations::onConsParallel()
{
    Ncti_Boolean boo = NctiHandler::AssParallel(m_mainWindow->getWindowPlatform());
    if (boo == false)
        QMessageBox::warning(m_mainWindow, "Command", "Command execution failure");
}

void AssemblyOperations::onConsConcentric()
{
    Ncti_Boolean boo = NctiHandler::AssConcentric(m_mainWindow->getWindowPlatform());
    if (boo == false)
        QMessageBox::warning(m_mainWindow, "Command", "Command execution failure");
}

void AssemblyOperations::onConsPerpendicular()
{
    Ncti_Boolean boo = NctiHandler::AssPerpendicular(m_mainWindow->getWindowPlatform());
    if (boo == false)
        QMessageBox::warning(m_mainWindow, "Command", "Command execution failure");
}

void AssemblyOperations::onConsDistance()
{
    Ncti_Boolean boo = NctiHandler::AssDistance(m_mainWindow->getWindowPlatform());
    if (boo == false)
        QMessageBox::warning(m_mainWindow, "Command", "Command execution failure");
}

void AssemblyOperations::onConsAngle()
{
    Ncti_Boolean boo = NctiHandler::AssAngle(m_mainWindow->getWindowPlatform());
    if (boo == false)
        QMessageBox::warning(m_mainWindow, "Command", "Command execution failure");
}

void AssemblyOperations::onConsEqualDistance()
{
    Ncti_Boolean boo = NctiHandler::AssEqualDistance(m_mainWindow->getWindowPlatform());
    if (boo == false)
        QMessageBox::warning(m_mainWindow, "Command", "Command execution failure");
}

void AssemblyOperations::onAssExport()
{
    Ncti_Boolean boo = NctiHandler::AssExport(m_mainWindow->getWindowPlatform());
    if (boo == false)
        QMessageBox::warning(m_mainWindow, "Command", "Command execution failure");
}

void AssemblyOperations::onConsFix()
{
    Ncti_Boolean boo = NctiHandler::AssFix(m_mainWindow->getWindowPlatform());
    if (boo == false)
        QMessageBox::warning(m_mainWindow, "Command", "Command execution failure");
}
} // namespace NCTI