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

#include "CreateChamferWgt.h"
#include "ui_CreateChamferWgtContent.h"

#include "NctiMessageBox.h"

#include "NctiBaseModel.h"
#include "NctiDocument.h"
#include "NctiCommandManager.h"
#include "NctiArgumentObject.h"
#include "NctiDocElementPubFun.h"

#include "NctiDisplayModelBody.h"
#include "NctiDisplayDocCustomContainer.h"

#include "NctiJsonDocument.h"
#include "NctiComModelTool.h"

namespace NCTI {

CreateChamferWgt::CreateChamferWgt(NctiDocument* i_pDocument, QWidget* parent)
    : NctiBaseDialog(parent)
    , ui(new Ui::CreateChamferWgtContent)
    , m_Document(i_pDocument)
{
    initUI();

    connect(ui->obtainEdgeBtn, SIGNAL(clicked()), this, SLOT(onSelEdge()));
    connect(ui->previewBtn, &QPushButton::clicked, this, &CreateChamferWgt::onPreview);
    connect(ui->confrimBtn, &QPushButton::clicked, this, &CreateChamferWgt::onOk);
    connect(ui->cancelBtn, &QPushButton::clicked, this, &CreateChamferWgt::onCanle);
    connect(this, &CreateChamferWgt::sigClose, this, &CreateChamferWgt::onCanle);

    if (i_pDocument) {
        NctiCommandManager* pComMan = NctiCommandManager::GetCommandManager(i_pDocument->GetBaseModel());
        EnumNctiResult result       = pComMan->RunCommand("cmd_ncti_model_create_chamfer");
        //UpdateView();
    }
}

CreateChamferWgt::~CreateChamferWgt()
{
    NCTI_DELETE ui;
}

void CreateChamferWgt::initUI()
{
    auto widget = new QWidget(this);
    widget->setObjectName("featureWidget-widget");
    ui->setupUi(widget);

    ui->nameLabel->setProperty("featureWidget-lab", true);
    ui->edgeLabel->setProperty("FeatureWidget-categoryLab", true);
    ui->paramLabel->setProperty("FeatureWidget-categoryLab", true);
    ui->angleLabel->setProperty("featureWidget-lab", true);
    ui->distanceLabel->setProperty("featureWidget-lab", true);
    ui->obtainEdgeBtn->setProperty("featureWidget-btn", true);
    ui->angleLineEdit->setProperty("featureWidget-lineEdit", true);
    ui->distanceLineEdit->setProperty("featureWidget-lineEdit", true);
    ui->centeralWidget->setObjectName("FeatureWidget-contentWgt");
    ui->previewBtn->setProperty("featureWidget-btn", true);
    ui->cancelBtn->setProperty("featureWidget-btn", true);
    ui->confrimBtn->setObjectName("MessageBox-btn");

    setTitle(QStringLiteral("倒角"));
    setWidget(widget);
}

void CreateChamferWgt::UpdateView()
{
    auto str2dle = [this](const QString& str) -> Ncti_Boolean {
        Ncti_Boolean ok = false;
        str.toDouble(&ok);
        return ok;
    };

    QString qsAngle    = ui->angleLineEdit->text();
    QString qsDistance = ui->distanceLineEdit->text();

    if (qsAngle.isEmpty() || (!str2dle(qsAngle))) {
        MESSAGEBOX_INSTANCE->showMessageBox(QStringLiteral("角度输入无效"));
        return;
    }
    if (qsDistance.isEmpty() || (!str2dle(qsDistance))) {
        MESSAGEBOX_INSTANCE->showMessageBox(QStringLiteral("距离输入无效"));
        return;
    }

    NctiArgumentObject argumentObject;
    argumentObject.SetDisplayObjectVec(m_SelObjVec);
    argumentObject.SetCellVec(m_SelectCells);
    argumentObject.SetAngle1(qsAngle.toDouble());
    argumentObject.SetRadius(qsDistance.toDouble());

    if (m_SelObjVec.size() > 0) {
        std::vector<NctiPosition> faceMidPt;
        NctiDisplayModelBody* pModelBody       = (NctiDisplayModelBody*)m_SelObjVec[0];
        NctiDisplayDocCustomContainer* pCusDoc = (NctiDisplayDocCustomContainer*)pModelBody->GetDocContainer();
        for (int i = 0, cellSize = m_SelectCells.size(), objSize = m_SelObjVec.size(); i < cellSize && i < objSize;
             ++i) {
            NctiPosition pos;
            Ncti_Long cellID = -1;
            pCusDoc->get_persistent_tag(pModelBody, m_SelectCells[i], cellID);
            NctiDocElementPubFun::GetEdgeMidPoint(m_Document, m_SelObjVec[i]->GetObjName(), cellID, pos);
            faceMidPt.push_back(pos);
        }

        std::vector<Ncti_Long> faceCellID;
        NctiDocElementPubFun::FindFaceByNearestPoint(m_Document, m_SelObjVec[0]->GetObjName(), faceMidPt, faceCellID);
        argumentObject.SetCellIDVec(faceCellID);
    }

    NctiComModelTool::RunUpdateScriptModelViewFun(m_Document, &argumentObject);
}

void CreateChamferWgt::onOk()
{
    auto str2dle = [this](const QString& str) -> Ncti_Boolean {
        Ncti_Boolean ok = false;
        str.toDouble(&ok);
        return ok;
    };

    QString qsAngle    = ui->angleLineEdit->text();
    QString qsDistance = ui->distanceLineEdit->text();

    if (qsAngle.isEmpty() || (!str2dle(qsAngle))) {
        MESSAGEBOX_INSTANCE->showMessageBox(QStringLiteral("角度输入无效"));
        return;
    }
    if (qsDistance.isEmpty() || (!str2dle(qsDistance))) {
        MESSAGEBOX_INSTANCE->showMessageBox(QStringLiteral("距离输入无效"));
        return;
    }

    NctiBaseModel* pBaseModel   = m_Document->GetBaseModel();
    NctiCommandManager* pComMan = NctiCommandManager::GetCommandManager(pBaseModel);
    if (pComMan && m_SelectCells.size() > 0) {
        pComMan->ProcessCancelButton();
        pComMan->RequestTermination(NULL);
        pComMan->ExitCommand();

        NctiArgumentObject argumentObject;
        argumentObject.SetDisplayObjectVec(m_SelObjVec);
        argumentObject.SetCellVec(m_SelectCells);
        argumentObject.SetAngle1(qsAngle.toDouble());
        argumentObject.SetRadius(qsDistance.toDouble());

        if (m_SelObjVec.size() > 0) {
            std::vector<NctiPosition> faceMidPt;
            NctiDisplayModelBody* pModelBody       = (NctiDisplayModelBody*)m_SelObjVec[0];
            NctiDisplayDocCustomContainer* pCusDoc = (NctiDisplayDocCustomContainer*)pModelBody->GetDocContainer();
            for (int i = 0, cellSize = m_SelectCells.size(), objSize = m_SelObjVec.size(); i < cellSize && i < objSize;
                 ++i) {
                NctiPosition pos;
                Ncti_Long cellID = -1;
                pCusDoc->get_persistent_tag(pModelBody, m_SelectCells[i], cellID);
                NctiDocElementPubFun::GetEdgeMidPoint(m_Document, m_SelObjVec[i]->GetObjName(), cellID, pos);
                faceMidPt.push_back(pos);
            }

            std::vector<Ncti_Long> faceCellID;
            NctiDocElementPubFun::FindFaceByNearestPoint(
                m_Document, m_SelObjVec[0]->GetObjName(), faceMidPt, faceCellID);
            argumentObject.SetCellIDVec(faceCellID);
        }

        /*EnumNctiResult result = */ pComMan->RunCommand("cmd_ncti_chamfer", &argumentObject);
    }
    close();
}

void CreateChamferWgt::onSelEdge()
{
    NctiDocElementPubFun::GetDisplayObjectFromSelManager(m_Document, m_SelObjVec, m_SelectCells);

    if (m_SelectCells.size() > 0) {
        ui->nameLabel->setText(
            QStringLiteral("已选边（<font color = #1771f8>%1</font>）").arg(QString::number(m_SelectCells.size())));
    }
    else {
        ui->nameLabel->setText(QStringLiteral("已选边（0）"));
        MESSAGEBOX_INSTANCE->showMessageBox(QStringLiteral("未选中边"));
    }
}

void CreateChamferWgt::onCanle()
{
    NctiBaseModel* pBaseModel   = m_Document->GetBaseModel();
    NctiCommandManager* pComMan = NctiCommandManager::GetCommandManager(pBaseModel);
    if (pComMan) {
        pComMan->ProcessCancelButton();
        pComMan->RequestTermination(NULL);
        pComMan->ExitCommand();
    }

    close();
}
void CreateChamferWgt::onPreview()
{
    QString str_Edge = ui->nameLabel->text();
    if (str_Edge == "已选边（0）") {
        MESSAGEBOX_INSTANCE->showMessageBox(QStringLiteral("未选中边"));
        return;
    }

    auto str2dle = [this](const QString& str) -> Ncti_Boolean {
        Ncti_Boolean ok = false;
        str.toDouble(&ok);
        return ok;
    };
    QString qsDistance = ui->distanceLineEdit->text();
    QString qsAngle    = ui->angleLineEdit->text();
    if (qsDistance.isEmpty() || (!str2dle(qsDistance))) {
        MESSAGEBOX_INSTANCE->showMessageBox(QStringLiteral("距离输入无效"));
        return;
    }
    if (qsAngle.isEmpty() || (!str2dle(qsAngle))) {
        MESSAGEBOX_INSTANCE->showMessageBox(QStringLiteral("角度输入无效"));
        return;
    }

    UpdateView();
}
} // namespace NCTI