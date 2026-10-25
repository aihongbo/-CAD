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

#include "AIFeatureRecognizer.h"
#include "NctiHandler.h"
#include "NctiQTPubFun.h"
#include "AiLabelTree.h"

#include <QFileDialog>
namespace NCTI {

AIFeatureRecognizer::AIFeatureRecognizer(MainWindow* mainWindow)
    : MainWindowModule(mainWindow)
{
}

void AIFeatureRecognizer::initialize()
{
    connect(m_mainWindow->Signals(), &MainWindowSignals::featureIdentifier, this, &AIFeatureRecognizer::onFeatureIdentifier);
    connect(m_mainWindow->Signals(), &MainWindowSignals::featureList, this, &AIFeatureRecognizer::onFeatureList);
    connect(m_mainWindow->Signals(), &MainWindowSignals::filletIdentifier, this, &AIFeatureRecognizer::onFilletIdentifier);
    connect(m_mainWindow->Signals(), &MainWindowSignals::holeIdentifier, this, &AIFeatureRecognizer::onHoleIdentifier);
    connect(m_mainWindow->Signals(), &MainWindowSignals::logoIdentifier, this, &AIFeatureRecognizer::onLogoIdentifier);
    connect(m_mainWindow->Signals(), &MainWindowSignals::filletExtract, this, &AIFeatureRecognizer::onFilletExtract);
    connect(m_mainWindow->Signals(), &MainWindowSignals::holeExtract, this, &AIFeatureRecognizer::onHoleExtract);
    connect(m_mainWindow->Signals(), &MainWindowSignals::logoExtract, this, &AIFeatureRecognizer::onLogoExtract);
    connect(m_mainWindow->Signals(), &MainWindowSignals::roundRecognition, this, &AIFeatureRecognizer::onRoundRecognition);
    connect(m_mainWindow->Signals(), &MainWindowSignals::chamferRecognition, this, &AIFeatureRecognizer::onChamferRecognition);
    connect(m_mainWindow->Signals(), &MainWindowSignals::throughHoleRecognition, this, &AIFeatureRecognizer::onThroughHoleRecognition);
    connect(m_mainWindow->Signals(), &MainWindowSignals::topoStructure, this, &AIFeatureRecognizer::onTopoStructure);
    connect(m_mainWindow->Signals(), &MainWindowSignals::edgeAttribute, this, &AIFeatureRecognizer::onEdgeAttribute);
    connect(m_mainWindow->Signals(), &MainWindowSignals::faceAttribute, this, &AIFeatureRecognizer::onFaceAttribute);
    connect(m_mainWindow->Signals(), &MainWindowSignals::uvGrid, this, &AIFeatureRecognizer::onUVGrid);
    connect(m_mainWindow->Signals(), &MainWindowSignals::exportLinkFace, this, &AIFeatureRecognizer::onExportLinkFace);
}


void AIFeatureRecognizer::onAiRecognition()
{
    NctiHandler::AiRecognition(m_mainWindow->getWindowPlatform());
}

void AIFeatureRecognizer::onSelFeatureFace()
{
    NctiHandler::SelFeatureFace(m_mainWindow->getWindowPlatform());
}

void AIFeatureRecognizer::onSearchLoop()
{
    NctiQTPubFun::SearchLoopFace(m_mainWindow->getWindowPlatform());
}

void AIFeatureRecognizer::onSearchConnect()
{
    NctiQTPubFun::SearchConnectFace(m_mainWindow->getWindowPlatform());
}

void AIFeatureRecognizer::onSearchSameConnect()
{
    NctiQTPubFun::SearchSameConnectFace(m_mainWindow->getWindowPlatform());
}

void AIFeatureRecognizer::onSearchNoPlaneConnect()
{
    NctiQTPubFun::SearchNoPlaneConnectFace(m_mainWindow->getWindowPlatform());
}

void AIFeatureRecognizer::onFeatureIdentifier()
{
    NctiDocument* i_pDocument = NctiQTPubFun::GetCurrentViewDocment(m_mainWindow->getWindowPlatform());
    if (!i_pDocument) {
        return;
    }
    NctiQTPubFun::ShowAIModelAddLabelDlg(i_pDocument, m_mainWindow);
}

void AIFeatureRecognizer::onFeatureList()
{
    NctiDocument* i_pDocument = NctiQTPubFun::GetCurrentViewDocment(m_mainWindow->getWindowPlatform());
    if (!i_pDocument) {
        return;
    }
    std::vector<AiLabelTree> setAiLabels;
    std::vector<AiLabelTree> setAiFeatureLabels;
    NctiQTPubFun::ShowAIModelDataListDlg(i_pDocument, m_mainWindow, setAiLabels, setAiFeatureLabels, nullptr);
}

void AIFeatureRecognizer::onFilletIdentifier()
{
    NctiDocument* i_pDocument = NctiQTPubFun::GetCurrentViewDocment(m_mainWindow->getWindowPlatform());
    if (!i_pDocument) {
        return;
    }
    NctiQTPubFun::RCornerRecognition(i_pDocument, m_mainWindow);
}

void AIFeatureRecognizer::onHoleIdentifier()
{
    NctiDocument* i_pDocument = NctiQTPubFun::GetCurrentViewDocment(m_mainWindow->getWindowPlatform());
    if (!i_pDocument) {
        return;
    }
    NctiQTPubFun::HoleRecognition(i_pDocument, m_mainWindow);
}

void AIFeatureRecognizer::onLogoIdentifier()
{
    NctiDocument* i_pDocument = NctiQTPubFun::GetCurrentViewDocment(m_mainWindow->getWindowPlatform());
    if (!i_pDocument) {
        return;
    }
    NctiQTPubFun::LogoRecognition(i_pDocument, m_mainWindow);
}

void AIFeatureRecognizer::onFilletExtract()
{
    NctiDocument* i_pDocument = NctiQTPubFun::GetCurrentViewDocment(m_mainWindow->getWindowPlatform());
    if (!i_pDocument) {
        return;
    }
    NctiQTPubFun::ShowRCornerExtract(i_pDocument, m_mainWindow);
}

void AIFeatureRecognizer::onHoleExtract()
{
    NctiDocument* i_pDocument = NctiQTPubFun::GetCurrentViewDocment(m_mainWindow->getWindowPlatform());
    if (!i_pDocument) {
        return;
    }
    NctiQTPubFun::ShowHoleExtract(i_pDocument, m_mainWindow);
}

void AIFeatureRecognizer::onLogoExtract()
{
    NctiDocument* i_pDocument = NctiQTPubFun::GetCurrentViewDocment(m_mainWindow->getWindowPlatform());
    if (!i_pDocument) {
        return;
    }
    NctiQTPubFun::ShowLogoExtract(i_pDocument, m_mainWindow);
}

void AIFeatureRecognizer::onTopoStructure()
{
    NctiHandler::TopoStructureDisplay(m_mainWindow->getWindowPlatform());
}

void AIFeatureRecognizer::onEdgeAttribute()
{
    NctiDocument* i_pDocument = NctiQTPubFun::GetCurrentViewDocment(m_mainWindow->getWindowPlatform());
    if (!i_pDocument) {
        return;
    }
    NctiQTPubFun::ShowEdgeAttributeDlg(i_pDocument, m_mainWindow);
}

void AIFeatureRecognizer::onFaceAttribute()
{
    NctiDocument* i_pDocument = NctiQTPubFun::GetCurrentViewDocment(m_mainWindow->getWindowPlatform());
    if (!i_pDocument) {
        return;
    }
    NctiQTPubFun::ShowFaceAttributeDlg(i_pDocument, m_mainWindow);
}

void AIFeatureRecognizer::onUVGrid()
{
    NctiHandler::UVGridDisplay(m_mainWindow->getWindowPlatform());
}

void AIFeatureRecognizer::onExportLinkFace()
{
    QString filePath = QFileDialog::getSaveFileName(
        nullptr, 
        QStringLiteral("导出关联面"), 
        "/", 
        tr("STP Files(*.stp)"));

    if (filePath.isEmpty()) {
        return;
    }

    NctiHandler::ExportLinkFace(m_mainWindow->getWindowPlatform(), filePath);
}

void AIFeatureRecognizer::onRoundRecognition()
{
    NctiDocument* i_pDocument = NctiQTPubFun::GetCurrentViewDocment(m_mainWindow->getWindowPlatform());
    if (!i_pDocument) {
        return;
    }
    NctiQTPubFun::ShowRoundRecognitionListDlg(i_pDocument, m_mainWindow);
}

void AIFeatureRecognizer::onChamferRecognition()
{
    NctiDocument* i_pDocument = NctiQTPubFun::GetCurrentViewDocment(m_mainWindow->getWindowPlatform());
    if (!i_pDocument) {
        return;
    }
    NctiQTPubFun::ShowChamferRecognitionListDlg(i_pDocument, m_mainWindow);
}

void AIFeatureRecognizer::onThroughHoleRecognition()
{
    //NctiHandler::HoleRecognition(m_mainWindow->getWindowPlatform());

    NctiDocument* i_pDocument = NctiQTPubFun::GetCurrentViewDocment(m_mainWindow->getWindowPlatform());
    if (!i_pDocument) {
        return;
    }
    NctiQTPubFun::ShowThroughHoleRecognitionListDlg(i_pDocument, m_mainWindow);
}

} // namespace NCTI