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

#include "CreateGeoRotateWgt.h"
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QVector3D>
#include "NctiMessageBox.h"

#include "NctiDocument.h"
#include "NctiDocElementPubFun.h"
#include "NctiArgumentObject.h"
#include "NctiCommandManager.h"
#include "NctiPosition.h"
#include "NctiMeasuringTool.h"
#include "NctiString.h"
#include "NctiComModelTool.h"
#include "NctiBaseModel.h"

namespace NCTI {
CreateGeoRotateWgt* CreateGeoRotateWgt::m_Instance = nullptr;

CreateGeoRotateWgt::CreateGeoRotateWgt(NctiDocument* i_pDocument, QWidget* parent)
    : NctiBaseDialog(parent)
    , m_Document(i_pDocument)
{
    initUI();

    connect(selectBodyBtn, &QPushButton::clicked, this, &CreateGeoRotateWgt::onSelObject);
    connect(previewBtn, &QPushButton::clicked, this, &CreateGeoRotateWgt::onPreview);
    connect(confrimBtn, &QPushButton::clicked, this, &CreateGeoRotateWgt::onOk);
    connect(cancelBtn, &QPushButton::clicked, this, &CreateGeoRotateWgt::onCanle);
    connect(this, &CreateGeoRotateWgt::sigClose, this, &CreateGeoRotateWgt::onCanle);

    NctiMeasuringTool::instance()->SetCalVectorCallback(CreateGeoRotateWgt::GetVectorFun); // 获取法向量的。
    NctiMeasuringTool::instance()->SetCalPositionCallback(CreateGeoRotateWgt::GetPositionFun);
    NctiMeasuringTool::instance()->SetCalMidPositionCallback(CreateGeoRotateWgt::GetPositionFun);
    NctiMeasuringTool::instance()->SetCalCenterCallback(CreateGeoRotateWgt::GetPositionFun);

    if (i_pDocument) {
        auto md = i_pDocument->GetBaseModel();
        if (md)
            md->SetPreviewMode(true);
        NctiCommandManager* pComMan = NctiCommandManager::GetCommandManager(md);
        EnumNctiResult result       = pComMan->RunCommand("cmd_ncti_model_create_rotate");
    }
}

CreateGeoRotateWgt::~CreateGeoRotateWgt()
{
    NctiMeasuringTool::instance()->ResetAll();
}

void CreateGeoRotateWgt::initUI()
{
    setTitle(QStringLiteral("旋转"));
    QWidget* mWidget          = new QWidget(this);
    QVBoxLayout* mLayout      = new QVBoxLayout(mWidget);
    QGridLayout* m_GridLayout = new QGridLayout;
    QHBoxLayout* m_hLayout    = new QHBoxLayout;
    mLayout->addLayout(m_GridLayout);
    mLayout->addLayout(m_hLayout);

    selectLabel     = new QLabel(QStringLiteral("选取实体："), mWidget);
    selectBodyLabel = new QLabel(QStringLiteral("未选取"), mWidget);
    pointLabel      = new QLabel(QStringLiteral("点："), mWidget);
    vectorLabel     = new QLabel(QStringLiteral("向量："), mWidget);
    angleLabel      = new QLabel(QStringLiteral("角度："), mWidget);
    selectBodyBtn   = new QPushButton(QStringLiteral("取体"), mWidget);
    previewBtn      = new QPushButton(QStringLiteral("预览"), mWidget);
    cancelBtn       = new QPushButton(QStringLiteral("取消"), mWidget);
    confrimBtn      = new QPushButton(QStringLiteral("确定"), mWidget);
    x_pLineEdit     = new QLineEdit(mWidget);
    y_pLineEdit     = new QLineEdit(mWidget);
    z_pLineEdit     = new QLineEdit(mWidget);
    x_vecLineEdit   = new QLineEdit(mWidget);
    y_vecLineEdit   = new QLineEdit(mWidget);
    z_vecLineEdit   = new QLineEdit(mWidget);
    angleLineEdit   = new QLineEdit(mWidget);

    selectLabel->setProperty("featureWidget-lab", true);
    selectBodyLabel->setProperty("featureWidget-lab", true);
    pointLabel->setProperty("featureWidget-lab", true);
    vectorLabel->setProperty("featureWidget-lab", true);
    angleLabel->setProperty("featureWidget-lab", true);
    x_pLineEdit->setProperty("featureWidget-lineEdit", true);
    y_pLineEdit->setProperty("featureWidget-lineEdit", true);
    z_pLineEdit->setProperty("featureWidget-lineEdit", true);
    x_vecLineEdit->setProperty("featureWidget-lineEdit", true);
    y_vecLineEdit->setProperty("featureWidget-lineEdit", true);
    z_vecLineEdit->setProperty("featureWidget-lineEdit", true);
    angleLineEdit->setProperty("featureWidget-lineEdit", true);
    selectBodyBtn->setProperty("featureWidget-btn", true);
    previewBtn->setProperty("featureWidget-btn", true);
    cancelBtn->setProperty("featureWidget-btn", true);
    confrimBtn->setObjectName("MessageBox-btn");

    x_pLineEdit->setFixedSize(70, 24);
    y_pLineEdit->setFixedSize(70, 24);
    z_pLineEdit->setFixedSize(70, 24);
    x_vecLineEdit->setFixedSize(70, 24);
    y_vecLineEdit->setFixedSize(70, 24);
    z_vecLineEdit->setFixedSize(70, 24);
    angleLineEdit->setMinimumSize(219, 24);
    selectBodyBtn->setFixedSize(70, 32);
    previewBtn->setFixedSize(88, 32);
    cancelBtn->setFixedSize(88, 32);
    confrimBtn->setFixedSize(88, 32);

    x_pLineEdit->setText(QStringLiteral("0"));
    y_pLineEdit->setText(QStringLiteral("0"));
    z_pLineEdit->setText(QStringLiteral("0"));
    x_vecLineEdit->setText(QStringLiteral("1"));
    y_vecLineEdit->setText(QStringLiteral("0"));
    z_vecLineEdit->setText(QStringLiteral("0"));
    angleLineEdit->setText(QStringLiteral("90"));

    m_GridLayout->addWidget(selectLabel, 0, 0);
    m_GridLayout->addWidget(selectBodyLabel, 0, 1, 1, 2);
    m_GridLayout->addWidget(selectBodyBtn, 0, 3);
    m_GridLayout->addWidget(pointLabel, 1, 0);
    m_GridLayout->addWidget(x_pLineEdit, 1, 1);
    m_GridLayout->addWidget(y_pLineEdit, 1, 2);
    m_GridLayout->addWidget(z_pLineEdit, 1, 3);
    m_GridLayout->addWidget(vectorLabel, 2, 0);
    m_GridLayout->addWidget(x_vecLineEdit, 2, 1);
    m_GridLayout->addWidget(y_vecLineEdit, 2, 2);
    m_GridLayout->addWidget(z_vecLineEdit, 2, 3);
    m_GridLayout->addWidget(angleLabel, 3, 0);
    m_GridLayout->addWidget(angleLineEdit, 3, 1, 1, 3);

    m_hLayout->addWidget(previewBtn);
    m_hLayout->addWidget(cancelBtn);
    m_hLayout->addWidget(confrimBtn);

    setWidget(mWidget);
}

bool CreateGeoRotateWgt::UpDate()
{
    if (m_SelObjVec.size() == 0) {
        MESSAGEBOX_INSTANCE->showMessageBox(QStringLiteral("实体对象未选中"));
        selectBodyLabel->setText(QStringLiteral("未选取"));
        return false;
    }
    if (x_pLineEdit->text().isEmpty() || y_pLineEdit->text().isEmpty() || z_pLineEdit->text().isEmpty()) {
        MESSAGEBOX_INSTANCE->showMessageBox(QStringLiteral("点输入无效"));
        return false;
    }
    px = x_pLineEdit->text().toDouble();
    py = y_pLineEdit->text().toDouble();
    pz = z_pLineEdit->text().toDouble();

    if (x_vecLineEdit->text().isEmpty() || y_vecLineEdit->text().isEmpty() || z_vecLineEdit->text().isEmpty()) {
        MESSAGEBOX_INSTANCE->showMessageBox(QStringLiteral("向量输入无效"));
        return false;
    }
    QVector3D Vec(x_vecLineEdit->text().toDouble(), y_vecLineEdit->text().toDouble(), z_vecLineEdit->text().toDouble());
    m_Vector         = Vec;
    double vecLength = m_Vector.length();
    if (vecLength == 0) {
        MESSAGEBOX_INSTANCE->showMessageBox(QStringLiteral("无效向量"));
        return false;
    }

    if (angleLineEdit->text().isEmpty()) {
        MESSAGEBOX_INSTANCE->showMessageBox(QStringLiteral("角度输入无效"));
        return false;
    }
    m_Angle = angleLineEdit->text().toDouble();

    return true;
}

void CreateGeoRotateWgt::SetPosition(NctiPosition pt)
{
    x_pLineEdit->setText(NctiString::double_to_string(pt.x(), 15).c_str());
    y_pLineEdit->setText(NctiString::double_to_string(pt.x(), 15).c_str());
    z_pLineEdit->setText(NctiString::double_to_string(pt.x(), 15).c_str());
}

void CreateGeoRotateWgt::SetVector(NctiVector pVector)
{
    x_vecLineEdit->setText(NctiString::double_to_string(pVector.x(), 15).c_str());
    y_vecLineEdit->setText(NctiString::double_to_string(pVector.y(), 15).c_str());
    z_vecLineEdit->setText(NctiString::double_to_string(pVector.z(), 15).c_str());
}

CreateGeoRotateWgt* CreateGeoRotateWgt::instance()
{
    return m_Instance;
}

void CreateGeoRotateWgt::SetInstance(CreateGeoRotateWgt* pDlg)
{
    m_Instance = pDlg;
}

void CreateGeoRotateWgt::GetPositionFun(NctiPosition pt)
{
    if (m_Instance == nullptr)
        return;
    m_Instance->SetPosition(pt);
}

void CreateGeoRotateWgt::GetVectorFun(NctiVector pVector)
{
    if (m_Instance == nullptr)
        return;
    m_Instance->SetVector(pVector);
}

void CreateGeoRotateWgt::onOk()
{
    NctiBaseModel* pBaseModel   = m_Document->GetBaseModel();
    NctiCommandManager* pComMan = NctiCommandManager::GetCommandManager(pBaseModel);
    if (pComMan) {
        pComMan->ProcessCancelButton();
        pComMan->RequestTermination(NULL);
        pComMan->ExitCommand();

        if (!UpDate())
            return;
        NctiArgumentObject argumentObject;
        NctiPosition pt;
        NctiVector m_Dir;
        pt.set_x(px);
        pt.set_y(py);
        pt.set_z(pz);
        m_Dir.set_x(m_Vector.x());
        m_Dir.set_y(m_Vector.y());
        m_Dir.set_z(m_Vector.z());
        argumentObject.SetPt(pt);
        argumentObject.SetDisplayObjectVec(m_SelObjVec);
        argumentObject.SetRadius(m_Angle);
        argumentObject.SetDir(m_Dir);
        pBaseModel->SetPreviewMode(false);
        EnumNctiResult result = pComMan->RunCommand("cmd_ncti_rotate_body", &argumentObject);
    }
    close();
    SetInstance(nullptr);
}

void CreateGeoRotateWgt::onSelObject()
{
    std::vector<NCTI_MODEL_TAG> selectCells;
    NctiDocElementPubFun::GetDisplayObjectFromSelManager(m_Document, m_SelObjVec, selectCells);

    if (m_SelObjVec.size() == 0) {
        MESSAGEBOX_INSTANCE->showMessageBox(QStringLiteral("实体对象未选中"));
        selectBodyLabel->setText(QStringLiteral("未选取"));
    }
    else {
        selectBodyLabel->setText(
            QStringLiteral("已选取对象（<font color = #1771f8>%1</font>）").arg(QString::number(m_SelObjVec.size())));
    }
}

void CreateGeoRotateWgt::onCanle()
{
    NctiBaseModel* pBaseModel   = m_Document->GetBaseModel();
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

void CreateGeoRotateWgt::onPreview()
{
    if (!UpDate())
        return;
    NctiArgumentObject argumentObject;
    NctiPosition pt;
    NctiVector m_Dir;
    pt.set_x(px);
    pt.set_y(py);
    pt.set_z(pz);
    m_Dir.set_x(m_Vector.x());
    m_Dir.set_y(m_Vector.y());
    m_Dir.set_z(m_Vector.z());
    argumentObject.SetPt(pt);
    argumentObject.SetDisplayObjectVec(m_SelObjVec);
    argumentObject.SetRadius(m_Angle);
    argumentObject.SetDir(m_Dir);

    NctiComModelTool::RunUpdateScriptModelViewFun(m_Document, &argumentObject);
}

} // namespace NCTI