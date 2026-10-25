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

#include "CreateFilletWgt.h"
#include "ui_CreateFilletWgtContent.h"

#include "NctiMessageBox.h"

#include "NctiBaseModel.h"
#include "NctiDocument.h"
#include "NctiCommandManager.h"
#include "NctiArgumentObject.h"
#include "NctiDocElementPubFun.h"
#include "NctiQTPubFun.h"
#include "NctiWindowViewManager.h"
#include "NctiJsonDocument.h"
#include "NctiComModelTool.h"

namespace NCTI {

CreateFilletWgt::CreateFilletWgt(NctiDocument* i_pDocument, QWidget* parent)
    : NctiBaseDialog(parent)
    , ui(new Ui::CreateFilletWgtContent)
    , m_Document(i_pDocument)
{
    initUI();

    connect(ui->obtainEdgeBtn, SIGNAL(clicked()), this, SLOT(onSelEdge()));
    connect(ui->previewBtn, &QPushButton::clicked, this, &CreateFilletWgt::onPreview);
    connect(ui->confrimBtn, &QPushButton::clicked, this, &CreateFilletWgt::onOk);
    connect(ui->cancelBtn, &QPushButton::clicked, this, &CreateFilletWgt::onCanle);
    connect(this, &CreateFilletWgt::sigClose, this, &CreateFilletWgt::onCanle);

    if (i_pDocument) {
        NctiCommandManager* pComMan = NctiCommandManager::GetCommandManager(i_pDocument->GetBaseModel());
        EnumNctiResult result       = pComMan->RunCommand("cmd_ncti_model_create_fillet");
        //UpdateView();
    }
}

CreateFilletWgt::~CreateFilletWgt()
{
    NCTI_DELETE ui;
}

void CreateFilletWgt::initUI()
{
    auto widget = new QWidget(this);
    widget->setObjectName("featureWidget-widget");
    ui->setupUi(widget);

    ui->radiusLabel->setProperty("featureWidget-lab", true);
    ui->edgeInfoLabel->setProperty("featureWidget-lab", true);
    ui->nameLabel->setProperty("featureWidget-lab", true);
    ui->obtainEdgeBtn->setProperty("featureWidget-btn", true);
    ui->radiusLineEdit->setProperty("featureWidget-lineEdit", true);

    ui->previewBtn->setProperty("featureWidget-btn", true);
    ui->cancelBtn->setProperty("featureWidget-btn", true);
    ui->confrimBtn->setObjectName("MessageBox-btn");

    setTitle(QStringLiteral("圆角"));
    setWidget(widget);
}

void CreateFilletWgt::UpdateView()
{
    NctiArgumentObject argumentObject;
    argumentObject.SetDisplayObjectVec(m_SelObjVec);
    argumentObject.SetCellVec(m_SelectCells);
    argumentObject.SetRadius(ui->radiusLineEdit->text().toDouble());

    NctiComModelTool::RunUpdateScriptModelViewFun(m_Document, &argumentObject);
}

void CreateFilletWgt::onOk()
{
    NctiBaseModel* pBaseModel   = m_Document->GetBaseModel();
    NctiCommandManager* pComMan = NctiCommandManager::GetCommandManager(pBaseModel);
    if (pComMan && m_SelectCells.size() > 0) {
        pComMan->ProcessCancelButton();
        pComMan->RequestTermination(NULL);
        pComMan->ExitCommand();

        QString qsRadius = ui->radiusLineEdit->text();
        if (qsRadius.isEmpty()) {
            MESSAGEBOX_INSTANCE->showMessageBox(QStringLiteral("半径输入无效"));
            return;
        }
        auto str = qsRadius.toStdString();
        NctiArgumentObject argumentObject;
        argumentObject.SetDisplayObjectVec(m_SelObjVec);
        argumentObject.SetCellVec(m_SelectCells);
        argumentObject.SetRadius(qsRadius.toDouble());
        EnumNctiResult result = pComMan->RunCommand("cmd_ncti_fillet", &argumentObject);
    }
    close();
}

void CreateFilletWgt::onSelEdge()
{
    NctiDocElementPubFun::GetDisplayObjectFromSelManager(m_Document, m_SelObjVec, m_SelectCells);

    if (m_SelectCells.size() > 0) {
        ui->edgeInfoLabel->setText(
            QStringLiteral("<font color = #1771f8>%1</font>").arg(QString::number(m_SelectCells.size())));
    }
    else {
        MESSAGEBOX_INSTANCE->showMessageBox(QStringLiteral("未选中边"));
    }
}

void CreateFilletWgt::onCanle()
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

void CreateFilletWgt::onPreview()
{
    QString str_Edge = ui->edgeInfoLabel->text();
    if (str_Edge == "0") {
        MESSAGEBOX_INSTANCE->showMessageBox(QStringLiteral("未选中边"));
        return;
    }

    QString qsRadius = ui->radiusLineEdit->text();
    if (qsRadius.isEmpty()) {
        MESSAGEBOX_INSTANCE->showMessageBox(QStringLiteral("半径输入无效"));
        return;
    }

    UpdateView();
}
} // namespace NCTI