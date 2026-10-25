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

#include "CreateGeoPanWgt.h"

#include <QVBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QVector3D>
#include "NctiMessageBox.h"

#include "NctiDocument.h"
#include "NctiCommandManager.h"
#include "NctiArgumentObject.h"
#include "NctiVector.h"
#include "NctiDocElementPubFun.h"
#include "NctiMeasuringTool.h"
#include "NctiString.h"
#include "NctiComModelTool.h"

namespace NCTI {
CreateGeoPanWgt* CreateGeoPanWgt::m_Instance = nullptr;

CreateGeoPanWgt::CreateGeoPanWgt(NctiDocument* i_pDocument, QWidget* parent)
    : NctiBaseDialog(parent)
    , m_Document(i_pDocument)
{
    initUI();

    connect(selBtn, &QPushButton::clicked, this, &CreateGeoPanWgt::onSelObject);
    connect(previewBtn, &QPushButton::clicked, this, &CreateGeoPanWgt::onPreview);
    connect(confrimBtn, &QPushButton::clicked, this, &CreateGeoPanWgt::onOk);
    connect(cancelBtn, &QPushButton::clicked, this, &CreateGeoPanWgt::onCanle);
    connect(this, &CreateGeoPanWgt::sigClose, this, &CreateGeoPanWgt::onCanle);

    if (i_pDocument) {
        NctiCommandManager* pComMan = NctiCommandManager::GetCommandManager(i_pDocument->GetBaseModel());
        EnumNctiResult result       = pComMan->RunCommand("cmd_ncti_model_create_pan");
    }

    NctiMeasuringTool::instance()->SetCalVectorCallback(CreateGeoPanWgt::GetVectorFun); // 获取法向量的。
}

CreateGeoPanWgt::~CreateGeoPanWgt()
{
    NctiMeasuringTool::instance()->ResetAll();
}

void CreateGeoPanWgt::SetVector(NctiVector pVector)
{
    x_VecLineEdit->setText(NctiString::double_to_string(pVector.x(), 15).c_str());
    y_VecLineEdit->setText(NctiString::double_to_string(pVector.y(), 15).c_str());
    z_VecLineEdit->setText(NctiString::double_to_string(pVector.z(), 15).c_str());
}

CreateGeoPanWgt* CreateGeoPanWgt::instance()
{
    return m_Instance;
}

void CreateGeoPanWgt::SetInstance(CreateGeoPanWgt* pDlg)
{
    m_Instance = pDlg;
}

void CreateGeoPanWgt::GetVectorFun(NctiVector pVector)
{
    if (m_Instance == nullptr)
        return;
    m_Instance->SetVector(pVector);
}

void CreateGeoPanWgt::initUI()
{
    auto widget               = new QWidget(this);
    QVBoxLayout* mLayout      = new QVBoxLayout(widget);
    QGridLayout* m_GridLayout = new QGridLayout;
    QHBoxLayout* m_hLayout    = new QHBoxLayout;
    mLayout->addLayout(m_GridLayout);
    mLayout->addLayout(m_hLayout);

    vectorLab        = new QLabel(QStringLiteral("向量："), widget);
    distanceLable    = new QLabel(QStringLiteral("距离："), widget);
    bodyLabel        = new QLabel(QStringLiteral("选取实体："), widget);
    selBodyLabel     = new QLabel(QStringLiteral("未选取"), widget);
    x_VecLineEdit    = new QLineEdit(widget);
    y_VecLineEdit    = new QLineEdit(widget);
    z_VecLineEdit    = new QLineEdit(widget);
    distanceLineEdit = new QLineEdit(widget);
    selBtn           = new QPushButton(QStringLiteral("取体"), widget);
    previewBtn       = new QPushButton(QStringLiteral("预览"), widget);
    cancelBtn        = new QPushButton(QStringLiteral("取消"), widget);
    confrimBtn       = new QPushButton(QStringLiteral("确定"), widget);

    widget->setObjectName("featureWidget-widget");
    vectorLab->setProperty("featureWidget-lab", true);
    distanceLable->setProperty("featureWidget-lab", true);
    bodyLabel->setProperty("featureWidget-lab", true);
    selBodyLabel->setProperty("featureWidget-lab", true);
    x_VecLineEdit->setProperty("featureWidget-lineEdit", true);
    y_VecLineEdit->setProperty("featureWidget-lineEdit", true);
    z_VecLineEdit->setProperty("featureWidget-lineEdit", true);
    distanceLineEdit->setProperty("featureWidget-lineEdit", true);
    selBtn->setProperty("featureWidget-btn", true);
    previewBtn->setProperty("featureWidget-btn", true);
    cancelBtn->setProperty("featureWidget-btn", true);
    confrimBtn->setObjectName("MessageBox-btn");

    x_VecLineEdit->setFixedSize(70, 24);
    y_VecLineEdit->setFixedSize(70, 24);
    z_VecLineEdit->setFixedSize(70, 24);
    distanceLineEdit->setMinimumSize(219, 24);
    selBtn->setFixedSize(70, 32);
    previewBtn->setFixedSize(88, 32);
    cancelBtn->setFixedSize(88, 32);
    confrimBtn->setFixedSize(88, 32);

    x_VecLineEdit->setText(QStringLiteral("1"));
    y_VecLineEdit->setText(QStringLiteral("0"));
    z_VecLineEdit->setText(QStringLiteral("0"));
    distanceLineEdit->setText(QStringLiteral("10"));

    m_GridLayout->addWidget(bodyLabel, 0, 0);
    m_GridLayout->addWidget(selBodyLabel, 0, 1, 1, 2);
    m_GridLayout->addWidget(selBtn, 0, 3);
    m_GridLayout->addWidget(vectorLab, 1, 0);
    m_GridLayout->addWidget(x_VecLineEdit, 1, 1);
    m_GridLayout->addWidget(y_VecLineEdit, 1, 2);
    m_GridLayout->addWidget(z_VecLineEdit, 1, 3);
    m_GridLayout->addWidget(distanceLable, 2, 0);
    m_GridLayout->addWidget(distanceLineEdit, 2, 1, 1, 3);

    m_hLayout->addWidget(previewBtn);
    m_hLayout->addWidget(cancelBtn);
    m_hLayout->addWidget(confrimBtn);

    setTitle(QStringLiteral("平移"));
    setWidget(widget);
}

bool CreateGeoPanWgt::UpDate()
{
    if (m_SelObjVec.size() == 0) {
        MESSAGEBOX_INSTANCE->showMessageBox(QStringLiteral("实体对象未选中"));
        return false;
    }

    QString X_direction = x_VecLineEdit->text();
    QString Y_direction = y_VecLineEdit->text();
    QString Z_direction = z_VecLineEdit->text();
    QString distance    = distanceLineEdit->text();

    if (X_direction.isEmpty() || Y_direction.isEmpty() || Z_direction.isEmpty()) {
        MESSAGEBOX_INSTANCE->showMessageBox(QStringLiteral("向量输入无效"));
        return false;
    }
    QVector3D vector(X_direction.toDouble(), Y_direction.toDouble(), Z_direction.toDouble());
    double vecLength = vector.length();
    if (vecLength == 0) {
        MESSAGEBOX_INSTANCE->showMessageBox(QStringLiteral("无效向量"));
        return false;
    }
    if (distance.isEmpty()) {
        MESSAGEBOX_INSTANCE->showMessageBox(QStringLiteral("距离输入无效"));
        return false;
    }

    // 归一化向量，得到单位向量
    QVector3D unitVector = vector / vecLength;
    m_Vector             = unitVector * distance.toDouble();

    return true;
}

void CreateGeoPanWgt::onOk()
{
    NctiBaseModel* pBaseModel   = m_Document->GetBaseModel();
    NctiCommandManager* pComMan = NctiCommandManager::GetCommandManager(pBaseModel);
    if (pComMan) {
        pComMan->ProcessCancelButton();
        pComMan->RequestTermination(NULL);
        pComMan->ExitCommand();

        if (!UpDate())
            return;

        NctiVector m_Dir;
        m_Dir.set_x(m_Vector.x());
        m_Dir.set_y(m_Vector.y());
        m_Dir.set_z(m_Vector.z());

        NctiArgumentObject argumentObject;
        argumentObject.SetDisplayObjectVec(m_SelObjVec);
        argumentObject.SetDir(m_Dir);

        EnumNctiResult result = pComMan->RunCommand("cmd_ncti_pan", &argumentObject);
    }
    close();
    SetInstance(nullptr);
}

void CreateGeoPanWgt::onSelObject()
{
    NctiDocElementPubFun::GetDisplayObjectFromSelManager(m_Document, m_SelObjVec);

    if (m_SelObjVec.size() == 0) {
        MESSAGEBOX_INSTANCE->showMessageBox(QStringLiteral("实体对象未选中"));
    }
    else {
        selBodyLabel->setText(
            QStringLiteral("已选取对象（<font color = #1771f8>%1</font>）").arg(QString::number(m_SelObjVec.size())));
    }
}

void CreateGeoPanWgt::onCanle()
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
}

void CreateGeoPanWgt::onPreview()
{
    if (!UpDate())
        return;
    NctiVector m_Dir;
    m_Dir.set_x(m_Vector.x());
    m_Dir.set_y(m_Vector.y());
    m_Dir.set_z(m_Vector.z());

    NctiArgumentObject argumentObject;
    argumentObject.SetDisplayObjectVec(m_SelObjVec);
    argumentObject.SetDir(m_Dir);

    NctiComModelTool::RunUpdateScriptModelViewFun(m_Document, &argumentObject);
}
} // namespace NCTI