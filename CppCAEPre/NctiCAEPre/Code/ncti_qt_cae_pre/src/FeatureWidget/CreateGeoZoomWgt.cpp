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

#include "CreateGeoZoomWgt.h"
#include <QVBoxLayout>
#include <QGridLayout>
#include <QHBoxLayout>
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

namespace NCTI {
CreateGeoZoomWgt* CreateGeoZoomWgt::m_Instance = nullptr;

CreateGeoZoomWgt::CreateGeoZoomWgt(NctiDocument* i_pDocument, QWidget* parent)
    : NctiBaseDialog(parent)
    , m_Document(i_pDocument)
{
    initUI();

    connect(selBodyBtn, &QPushButton::clicked, this, &CreateGeoZoomWgt::onSelObject);
    connect(previewBtn, &QPushButton::clicked, this, &CreateGeoZoomWgt::onPreview);
    connect(confrimBtn, &QPushButton::clicked, this, &CreateGeoZoomWgt::onOk);
    connect(cancelBtn, &QPushButton::clicked, this, &CreateGeoZoomWgt::onCanle);
    connect(this, &CreateGeoZoomWgt::sigClose, this, &CreateGeoZoomWgt::onCanle);

    if (i_pDocument) {
        NctiCommandManager* pComMan = NctiCommandManager::GetCommandManager(i_pDocument->GetBaseModel());
        EnumNctiResult result       = pComMan->RunCommand("cmd_ncti_model_create_scale");
    }

    NctiMeasuringTool::instance()->SetCalPositionCallback(CreateGeoZoomWgt::GetPositionFun);
    NctiMeasuringTool::instance()->SetCalMidPositionCallback(CreateGeoZoomWgt::GetPositionFun);
    NctiMeasuringTool::instance()->SetCalCenterCallback(CreateGeoZoomWgt::GetPositionFun);
}

CreateGeoZoomWgt::~CreateGeoZoomWgt()
{
    NctiMeasuringTool::instance()->ResetAll();
}

void CreateGeoZoomWgt::SetPosition(NctiPosition pt)
{
    x_pointLineEdit->setText(NctiString::double_to_string(pt.x(), 15).c_str());
    y_pointLineEdit->setText(NctiString::double_to_string(pt.y(), 15).c_str());
    z_pointLineEdit->setText(NctiString::double_to_string(pt.z(), 15).c_str());
}

CreateGeoZoomWgt* CreateGeoZoomWgt::instance()
{
    return m_Instance;
}

void CreateGeoZoomWgt::SetInstance(CreateGeoZoomWgt* pDlg)
{
    m_Instance = pDlg;
}

void CreateGeoZoomWgt::GetPositionFun(NctiPosition pt)
{
    if (m_Instance == nullptr)
        return;
    m_Instance->SetPosition(pt);
}

void CreateGeoZoomWgt::initUI()
{
    this->setTitle(QStringLiteral("缩放"));
    QWidget* mWidget          = new QWidget(this);
    QVBoxLayout* mLayout      = new QVBoxLayout(mWidget);
    QGridLayout* m_GridLayout = new QGridLayout;
    QHBoxLayout* m_hLayout    = new QHBoxLayout;
    mLayout->addLayout(m_GridLayout);
    mLayout->addLayout(m_hLayout);

    bodyLabel                = new QLabel(QStringLiteral("选取实体："), mWidget);
    selBodyLabel             = new QLabel(QStringLiteral("未选取"), mWidget);
    pointLabel               = new QLabel(QStringLiteral("点："), mWidget);
    proportionalScalingLabel = new QLabel(QStringLiteral("等比缩放"), mWidget);
    proportionLabel          = new QLabel(QStringLiteral("比例："), mWidget);
    //scalingLabel = new QLabel(QStringLiteral("比例缩放："), mWidget);
    selBodyBtn         = new QPushButton(QStringLiteral("取体"), mWidget);
    x_pointLineEdit    = new QLineEdit(mWidget);
    y_pointLineEdit    = new QLineEdit(mWidget);
    z_pointLineEdit    = new QLineEdit(mWidget);
    proportionLineEdit = new QLineEdit(mWidget);
    /*x_scalingLineEdit = new QLineEdit(mWidget);
		y_scalingLineEdit = new QLineEdit(mWidget);
		z_scalingLineEdit = new QLineEdit(mWidget);*/
    previewBtn = new QPushButton(QStringLiteral("预览"), mWidget);
    cancelBtn  = new QPushButton(QStringLiteral("取消"), mWidget);
    confrimBtn = new QPushButton(QStringLiteral("确定"), mWidget);

    bodyLabel->setProperty("featureWidget-lab", true);
    selBodyLabel->setProperty("featureWidget-lab", true);
    pointLabel->setProperty("featureWidget-lab", true);
    proportionalScalingLabel->setProperty("featureWidget-lab", true);
    proportionLabel->setProperty("featureWidget-lab", true);
    //scalingLabel->setProperty("featureWidget-lab", true);
    x_pointLineEdit->setProperty("featureWidget-lineEdit", true);
    y_pointLineEdit->setProperty("featureWidget-lineEdit", true);
    z_pointLineEdit->setProperty("featureWidget-lineEdit", true);
    proportionLineEdit->setProperty("featureWidget-lineEdit", true);
    /*x_scalingLineEdit->setProperty("featureWidget-lineEdit", true);
		y_scalingLineEdit->setProperty("featureWidget-lineEdit", true);
		z_scalingLineEdit->setProperty("featureWidget-lineEdit", true);*/
    selBodyBtn->setProperty("featureWidget-btn", true);
    previewBtn->setProperty("featureWidget-btn", true);
    cancelBtn->setProperty("featureWidget-btn", true);
    confrimBtn->setObjectName("MessageBox-btn");

    x_pointLineEdit->setFixedSize(70, 24);
    y_pointLineEdit->setFixedSize(70, 24);
    z_pointLineEdit->setFixedSize(70, 24);
    proportionLineEdit->setMinimumSize(219, 24);
    /*x_scalingLineEdit->setFixedSize(70, 24);
		y_scalingLineEdit->setFixedSize(70, 24);
		z_scalingLineEdit->setFixedSize(70, 24);*/
    selBodyBtn->setFixedSize(70, 32);
    previewBtn->setFixedSize(88, 32);
    cancelBtn->setFixedSize(88, 32);
    confrimBtn->setFixedSize(88, 32);

    x_pointLineEdit->setText(QStringLiteral("0"));
    y_pointLineEdit->setText(QStringLiteral("0"));
    z_pointLineEdit->setText(QStringLiteral("0"));
    proportionLineEdit->setText(QStringLiteral("1"));
    /*x_scalingLineEdit->setPlaceholderText(QStringLiteral("X分量"));
		y_scalingLineEdit->setPlaceholderText(QStringLiteral("Y分量"));
		z_scalingLineEdit->setPlaceholderText(QStringLiteral("Z分量"));*/

    m_GridLayout->addWidget(bodyLabel, 0, 0);
    m_GridLayout->addWidget(selBodyLabel, 0, 1, 1, 2);
    m_GridLayout->addWidget(selBodyBtn, 0, 3);
    m_GridLayout->addWidget(pointLabel, 1, 0);
    m_GridLayout->addWidget(x_pointLineEdit, 1, 1);
    m_GridLayout->addWidget(y_pointLineEdit, 1, 2);
    m_GridLayout->addWidget(z_pointLineEdit, 1, 3);
    m_GridLayout->addWidget(proportionalScalingLabel, 2, 0);
    m_GridLayout->addWidget(proportionLabel, 3, 0);
    m_GridLayout->addWidget(proportionLineEdit, 3, 1, 1, 3);
    /*m_GridLayout->addWidget(scalingLabel, 2, 0);
		m_GridLayout->addWidget(x_scalingLineEdit, 2, 1);
		m_GridLayout->addWidget(y_scalingLineEdit, 2, 2);
		m_GridLayout->addWidget(z_scalingLineEdit, 2, 3);*/

    m_hLayout->addWidget(previewBtn);
    m_hLayout->addWidget(cancelBtn);
    m_hLayout->addWidget(confrimBtn);

    setWidget(mWidget);
}

bool CreateGeoZoomWgt::UpDate()
{
    if (m_SelObjVec.size() == 0) {
        MESSAGEBOX_INSTANCE->showMessageBox(QStringLiteral("实体对象未选中"));
        return false;
    }

    if (x_pointLineEdit->text().isEmpty() || y_pointLineEdit->text().isEmpty() || z_pointLineEdit->text().isEmpty()) {
        MESSAGEBOX_INSTANCE->showMessageBox(QStringLiteral("点输入无效"));
        return false;
    }
    px = x_pointLineEdit->text().toDouble();
    py = y_pointLineEdit->text().toDouble();
    pz = z_pointLineEdit->text().toDouble();

    if (proportionLineEdit->text().isEmpty()) {
        MESSAGEBOX_INSTANCE->showMessageBox(QStringLiteral("比例输入无效"));
        return false;
    }
    scaleProportion = proportionLineEdit->text().toDouble();

    return true;
}

void CreateGeoZoomWgt::onOk()
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
        pt.set_x(px);
        pt.set_y(py);
        pt.set_z(pz);
        argumentObject.SetPt(pt);
        argumentObject.SetDisplayObjectVec(m_SelObjVec);
        argumentObject.SetScale(scaleProportion);

        EnumNctiResult result = pComMan->RunCommand("cmd_ncti_scale", &argumentObject);
    }
    close();
    SetInstance(nullptr);
}

void CreateGeoZoomWgt::onSelObject()
{
    std::vector<NCTI_MODEL_TAG> selectCells;
    NctiDocElementPubFun::GetDisplayObjectFromSelManager(m_Document, m_SelObjVec, selectCells);

    if (m_SelObjVec.size() == 0) {
        MESSAGEBOX_INSTANCE->showMessageBox(QStringLiteral("实体对象未选中"));
    }
    else {
        selBodyLabel->setText(
            QStringLiteral("已选取对象（<font color = #1771f8>%1</font>）").arg(QString::number(m_SelObjVec.size())));
    }
}

void CreateGeoZoomWgt::onCanle()
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

void CreateGeoZoomWgt::onPreview()
{
    if (!UpDate())
        return;
    NctiArgumentObject argumentObject;
    NctiPosition pt;
    pt.set_x(px);
    pt.set_y(py);
    pt.set_z(pz);
    argumentObject.SetPt(pt);
    argumentObject.SetDisplayObjectVec(m_SelObjVec);
    argumentObject.SetScale(scaleProportion);

    NctiComModelTool::RunUpdateScriptModelViewFun(m_Document, &argumentObject);
}
} // namespace NCTI