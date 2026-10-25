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

#include "CreateCylinderWgt.h"
#include "ui_CreateCylinderWgtContent.h"

#include "NctiBaseModel.h"
#include "NctiDocument.h"
#include "NctiCommandManager.h"
#include "NctiArgumentObject.h"

#include "NctiJsonDocument.h"
#include "NctiComModelTool.h"
#include "NctiDocElementPubFun.h"
#include "NctiTopoVertex.h"
#include "NctiGeomPoint.h"
#include "NctiBaseView.h"

namespace NCTI {

CreateCylinderWgt::CreateCylinderWgt(NctiDocument* i_pDocument, QWidget* parent)
    : NctiBaseDialog(parent)
    , ui(new Ui::CreateCylinderWgtContent)
    , m_Document(i_pDocument)
{
    initUI();
    ui->coorXLinEdit->setText("10");
    ui->coorYLinEdit->setText("20");
    ui->coorZLinEdit->setText("30");

    ui->heigLinEdit->setText("10");
    ui->radiusLinEdit->setText("5");
    connect(ui->confrimBtn, &QPushButton::clicked, this, &CreateCylinderWgt::onOk);
    connect(ui->cancelBtn, &QPushButton::clicked, this, &CreateCylinderWgt::onCanle);
    connect(ui->previewBtn, &QPushButton::clicked, this, &CreateCylinderWgt::onPreview);
    connect(ui->fetchPtBtn, &QPushButton::clicked, this, &CreateCylinderWgt::onPosition);
    connect(this, &CreateCylinderWgt::sigClose, this, &CreateCylinderWgt::onCanle);

    if (i_pDocument) {
        auto md = i_pDocument->GetBaseModel();
        if (md)
            md->SetPreviewMode(true);
        NctiCommandManager* pComMan = NctiCommandManager::GetCommandManager(md);
        EnumNctiResult result       = pComMan->RunCommand("cmd_ncti_model_create_cylinder");
        UpdateView();
    }
}

CreateCylinderWgt::~CreateCylinderWgt()
{
    NCTI_DELETE ui;
}

void CreateCylinderWgt::initUI()
{
    auto widget = new QWidget(this);
    widget->setObjectName("featureWidget-widget");
    ui->setupUi(widget);

    resize(320, 254);
    ui->coorXLinEdit->setProperty("featureWidget-lineEdit", true);
    ui->coorYLinEdit->setProperty("featureWidget-lineEdit", true);
    ui->coorZLinEdit->setProperty("featureWidget-lineEdit", true);
    ui->radiusLinEdit->setProperty("featureWidget-lineEdit", true);
    ui->heigLinEdit->setProperty("featureWidget-lineEdit", true);
    ui->heigLab->setProperty("featureWidget-lab", true);
    ui->coordLab->setProperty("featureWidget-lab", true);
    ui->radiusLab->setProperty("featureWidget-lab", true);

    ui->bottomWgt->setObjectName("FeatureWidget-bottom");
    ui->confrimBtn->setObjectName("MessageBox-btn");
    ui->cancelBtn->setProperty("featureWidget-btn", true);
    ui->fetchPtBtn->setProperty("featureWidget-btn", true);
    ui->previewBtn->setProperty("featureWidget-btn", true);

    setTitle(QStringLiteral("圆柱体"));
    setWidget(widget);
}

void CreateCylinderWgt::UpdateView()
{
    NCTIJson::JsonObject jsonDB;
    jsonDB.insert("X", ui->coorXLinEdit->text().toDouble());
    jsonDB.insert("Y", ui->coorYLinEdit->text().toDouble());
    jsonDB.insert("Z", ui->coorZLinEdit->text().toDouble());
    jsonDB.insert("Radius", ui->radiusLinEdit->text().toDouble());
    jsonDB.insert("Height", ui->heigLinEdit->text().toDouble());
    NCTIJson::JsonObject QrootObject;
    QrootObject.insert(Create_Model_Key_Name, jsonDB.object());
    if (!QrootObject.isEmpty()) {
        NCTIJson::JsonDocument jsonDocument;
        jsonDocument.setObject(QrootObject);

        std::string jsonData = jsonDocument.toJson(NCTIJson::JsonDocument::Compact);
        NctiComModelTool::RunUpdateModelViewFun(m_Document, jsonData);
    }
}

void CreateCylinderWgt::onOk()
{
    NctiBaseModel* pBaseModel = m_Document->GetBaseModel();
    NctiCommandManager* pComMan = NctiCommandManager::GetCommandManager(pBaseModel);
    if (pComMan) {
        pComMan->ProcessCancelButton(); // 预览命令cmd_ncti_model_create_cylinder取消
        pComMan->RequestTermination(NULL);
        pComMan->ExitCommand();

        NctiArgumentObject argumentObject;
        NctiPosition pt;
        pt.set_x(ui->coorXLinEdit->text().toDouble());
        pt.set_y(ui->coorYLinEdit->text().toDouble());
        pt.set_z(ui->coorZLinEdit->text().toDouble());
        argumentObject.SetPt(pt);
        argumentObject.SetRadius(ui->radiusLinEdit->text().toDouble());
        argumentObject.SetHeight(ui->heigLinEdit->text().toDouble());

        pBaseModel->SetPreviewMode(false);

        EnumNctiResult result = pComMan->RunCommand("cmd_ncti_create_cylinder", &argumentObject);
    }
    close();
}

void CreateCylinderWgt::onCanle()
{
    NctiBaseModel* pBaseModel = m_Document->GetBaseModel();
    NctiCommandManager* pComMan = NctiCommandManager::GetCommandManager(pBaseModel);
    if (pComMan) {
        pComMan->ProcessCancelButton();
        pComMan->RequestTermination(NULL);
        pComMan->ExitCommand();
    }
    close();
    pBaseModel->SetPreviewMode(false);
}

void CreateCylinderWgt::onPreview()
{
    UpdateView();
}
void CreateCylinderWgt::onPosition()
{
    std::vector<std::string> names;
    std::vector<Ncti_Long> cellIDs;
    std::vector<NctiTopoCell*> topoCells;

    NctiDocElementPubFun::GetNameFromSelManager(m_Document, names, cellIDs, topoCells);
    for (auto cell : topoCells) {
        if (!cell->IsTypeName(NctiTopoVertex::ID)) {
            continue;
        }

        NctiTopoVertex* vertex = dynamic_cast<NctiTopoVertex*>(cell);
        NctiPosition point     = vertex->Get_m_pGeomPoint()->GetPt() * vertex->Get_m_Tranf();
        ui->coorXLinEdit->setText(QString::number(point.x(), 'f', 7));
        ui->coorYLinEdit->setText(QString::number(point.y(), 'f', 7));
        ui->coorZLinEdit->setText(QString::number(point.z(), 'f', 7));
        break;
    }
}

} // namespace NCTI