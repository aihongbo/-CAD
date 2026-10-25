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

#include "CreateCuboidWgt.h"
#include "ui_CreateCuboidWgtContent.h"
#include "NctiBaseModel.h"
#include "NctiDocument.h"
#include "NctiCommandManager.h"
#include "NctiArgumentObject.h"
#include "NctiJsonDocument.h"
#include "NctiComModelTool.h"
#include "NctiMeasuringTool.h"
#include "NctiString.h"


namespace NCTI {

CreateCuboidWgt* CreateCuboidWgt::m_Instance = nullptr;

CreateCuboidWgt::CreateCuboidWgt(NctiDocument* i_pDocument, QWidget* parent)
    : NctiBaseDialog(parent)
    , ui(new Ui::CreateCuboidWgtContent)
    , m_Document(i_pDocument)
{
    initUI();
    QSize size = this->size();
    this->setFixedSize(size.width(), size.height() - 32);
    ui->fetchPtBtn->hide();
    ui->coorXLinEdit->setText("0");
    ui->coorYLinEdit->setText("0");
    ui->coorZLinEdit->setText("0");

    ui->directXLinedit->setText("10");
    ui->directYLinedit->setText("20");
    ui->directZLinedit->setText("30");
    connect(ui->previewBtn, &QPushButton::clicked, this, &CreateCuboidWgt::onPreview);
    connect(ui->confrimBtn, &QPushButton::clicked, this, &CreateCuboidWgt::onOk);
    connect(ui->cancelBtn, &QPushButton::clicked, this, &CreateCuboidWgt::onCanle);
    /*connect(ui->coorXLinEdit, &QLineEdit::textChanged, this, &CreateCuboidWgt::onTextChanged);
		connect(ui->coorYLinEdit, &QLineEdit::textChanged, this, &CreateCuboidWgt::onTextChanged);
		connect(ui->coorZLinEdit, &QLineEdit::textChanged, this, &CreateCuboidWgt::onTextChanged);
		connect(ui->directXLinedit, &QLineEdit::textChanged, this, &CreateCuboidWgt::onTextChanged);
		connect(ui->directYLinedit, &QLineEdit::textChanged, this, &CreateCuboidWgt::onTextChanged);
		connect(ui->directZLinedit, &QLineEdit::textChanged, this, &CreateCuboidWgt::onTextChanged);*/
    connect(this, &CreateCuboidWgt::sigClose, this, &CreateCuboidWgt::onCanle);

    if (i_pDocument) {
        auto md = i_pDocument->GetBaseModel();
        if (md)
            md->SetPreviewMode(true);
        NctiCommandManager* pComMan = NctiCommandManager::GetCommandManager(md);
        EnumNctiResult result       = pComMan->RunCommand("cmd_ncti_model_create_box");
        UpdateView();
    }

    NctiMeasuringTool::instance()->SetCalPositionCallback(CreateCuboidWgt::GetPositionFun);
    NctiMeasuringTool::instance()->SetCalMidPositionCallback(CreateCuboidWgt::GetPositionFun);
    NctiMeasuringTool::instance()->SetCalCenterCallback(CreateCuboidWgt::GetPositionFun);
}

CreateCuboidWgt::~CreateCuboidWgt()
{
    NCTI_DELETE ui;
    NctiMeasuringTool::instance()->ResetAll();
}

void CreateCuboidWgt::SetPosition(NctiPosition pt)
{
    ui->coorXLinEdit->setText(NctiString::double_to_string(pt.x(), 15).c_str());
    ui->coorYLinEdit->setText(NctiString::double_to_string(pt.y(), 15).c_str());
    ui->coorZLinEdit->setText(NctiString::double_to_string(pt.z(), 15).c_str());
    // UpdateView();
}

CreateCuboidWgt* CreateCuboidWgt::instance()
{
    return m_Instance;
}

void CreateCuboidWgt::SetInstance(CreateCuboidWgt* pDlg)
{
    m_Instance = pDlg;
}

void CreateCuboidWgt::GetPositionFun(NctiPosition pt)
{
    if (m_Instance == nullptr)
        return;
    m_Instance->SetPosition(pt);
}

void CreateCuboidWgt::initUI()
{
    auto widget = new QWidget(this);
    widget->setObjectName("featureWidget-widget");
    ui->setupUi(widget);

    resize(320, 290);
    ui->coorXLinEdit->setProperty("featureWidget-lineEdit", true);
    ui->coorYLinEdit->setProperty("featureWidget-lineEdit", true);
    ui->coorZLinEdit->setProperty("featureWidget-lineEdit", true);
    ui->directXLinedit->setProperty("featureWidget-lineEdit", true);
    ui->directYLinedit->setProperty("featureWidget-lineEdit", true);
    ui->directZLinedit->setProperty("featureWidget-lineEdit", true);
    ui->coordLab->setProperty("featureWidget-lab", true);
    ui->directXLab->setProperty("featureWidget-lab", true);
    ui->directYLab->setProperty("featureWidget-lab", true);
    ui->directZLab->setProperty("featureWidget-lab", true);

    ui->bottomWgt->setObjectName("FeatureWidget-bottom");
    ui->confrimBtn->setObjectName("MessageBox-btn");
    ui->cancelBtn->setProperty("featureWidget-btn", true);
    ui->fetchPtBtn->setProperty("featureWidget-btn", true);
    ui->previewBtn->setProperty("featureWidget-btn", true);
    setTitle(QStringLiteral("长方体"));
    setWidget(widget);
}

void CreateCuboidWgt::UpdateView()
{
    NCTIJson::JsonObject jsonDB;
    jsonDB.insert("X", ui->coorXLinEdit->text().toDouble());
    jsonDB.insert("Y", ui->coorYLinEdit->text().toDouble());
    jsonDB.insert("Z", ui->coorZLinEdit->text().toDouble());
    jsonDB.insert("XLen", ui->directXLinedit->text().toDouble());
    jsonDB.insert("YLen", ui->directYLinedit->text().toDouble());
    jsonDB.insert("ZLen", ui->directZLinedit->text().toDouble());
    NCTIJson::JsonObject QrootObject;
    QrootObject.insert(Create_Model_Key_Name, jsonDB.object());
    if (!QrootObject.isEmpty()) {
        NCTIJson::JsonDocument jsonDocument;
        jsonDocument.setObject(QrootObject);

        std::string jsonData = jsonDocument.toJson(NCTIJson::JsonDocument::Compact);
        NctiComModelTool::RunUpdateModelViewFun(m_Document, jsonData);
    }
}

void CreateCuboidWgt::onOk()
{
    NctiBaseModel* pBaseModel   = m_Document->GetBaseModel();
    NctiCommandManager* pComMan = NctiCommandManager::GetCommandManager(pBaseModel);
    if (pComMan) {
        pComMan->ProcessCancelButton();
        pComMan->RequestTermination(NULL);
        pComMan->ExitCommand();

        NctiArgumentObject argumentObject;
        NctiPosition pt;
        pt.set_x(ui->coorXLinEdit->text().toDouble());
        pt.set_y(ui->coorYLinEdit->text().toDouble());
        pt.set_z(ui->coorZLinEdit->text().toDouble());
        argumentObject.SetPt(pt);
        argumentObject.SetXLen(ui->directXLinedit->text().toDouble());
        argumentObject.SetYLen(ui->directYLinedit->text().toDouble());
        argumentObject.SetZLen(ui->directZLinedit->text().toDouble());

        pBaseModel->SetPreviewMode(false);
        EnumNctiResult result = pComMan->RunCommand("cmd_ncti_create_box", &argumentObject);
    }
    close();
    SetInstance(nullptr);
}

void CreateCuboidWgt::onCanle()
{
    NctiBaseModel* pBaseModel = m_Document->GetBaseModel();
    NctiCommandManager* pComMan = NctiCommandManager::GetCommandManager(pBaseModel);
    if (pComMan) {
        pComMan->ProcessCancelButton();
        pComMan->RequestTermination(NULL);
        pComMan->ExitCommand();
    }
    close();
    SetInstance(nullptr);
    pBaseModel->SetPreviewMode(false);
}

void CreateCuboidWgt::onTextChanged(const QString& text)
{
    UpdateView();
}

void CreateCuboidWgt::onPreview()
{
    UpdateView();
}

} // namespace NCTI