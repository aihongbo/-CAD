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

#include "CreateCurveOffsetWgt.h"
#include <QGridLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QVector3D>
#include <QDebug>
#include "NctiMessageBox.h"

#include "NctiDocument.h"
#include "NctiDocElementPubFun.h"
#include "NctiArgumentObject.h"
#include "NctiCommandManager.h"
#include "NctiMeasuringTool.h"
#include "NctiString.h"
#include "NctiComModelTool.h"
using namespace NCTI;

CreateCurveOffsetWgt* CreateCurveOffsetWgt::m_Instance = nullptr;

NCTI::CreateCurveOffsetWgt::CreateCurveOffsetWgt(NctiDocument* i_pDocument, QWidget* parent)
    : NctiBaseDialog(parent)
    , m_Document(i_pDocument)
{
    initUI();

    connect(selectBtn, &QPushButton::clicked, this, &CreateCurveOffsetWgt::onSelect);
    connect(previewBtn, &QPushButton::clicked, this, &CreateCurveOffsetWgt::onPreview);
    connect(confrimBtn, &QPushButton::clicked, this, &CreateCurveOffsetWgt::onOK);
    connect(cancelBtn, &QPushButton::clicked, this, &CreateCurveOffsetWgt::onCanle);
    connect(this, &CreateCurveOffsetWgt::sigClose, this, &CreateCurveOffsetWgt::onCanle);

    if (i_pDocument) {
        NctiCommandManager* pComMan = NctiCommandManager::GetCommandManager(i_pDocument->GetBaseModel());
        EnumNctiResult result       = pComMan->RunCommand("cmd_ncti_model_create_curve_offset");
    }

    NctiMeasuringTool::instance()->SetCalVectorCallback(CreateCurveOffsetWgt::GetVectorFun); // 获取法向量的。
}

NCTI::CreateCurveOffsetWgt::~CreateCurveOffsetWgt()
{
    NctiMeasuringTool::instance()->ResetAll();
}

void NCTI::CreateCurveOffsetWgt::SetVector(NctiVector pVector)
{
    x_offsetDirectionEdit->setText(NctiString::double_to_string(pVector.x(), 15).c_str());
    y_offsetDirectionEdit->setText(NctiString::double_to_string(pVector.y(), 15).c_str());
    z_offsetDirectionEdit->setText(NctiString::double_to_string(pVector.z(), 15).c_str());
}

CreateCurveOffsetWgt* NCTI::CreateCurveOffsetWgt::instance()
{
    return m_Instance;
}

void NCTI::CreateCurveOffsetWgt::SetInstance(CreateCurveOffsetWgt* pDlg)
{
    m_Instance = pDlg;
}

void NCTI::CreateCurveOffsetWgt::GetVectorFun(NctiVector pVector)
{
    if (m_Instance == nullptr)
        return;
    m_Instance->SetVector(pVector);
}

void NCTI::CreateCurveOffsetWgt::initUI()
{
    this->setTitle(QStringLiteral("曲线偏移"));
    QWidget* mWidget          = new QWidget(this);
    QVBoxLayout* mLayout      = new QVBoxLayout(mWidget);
    QGridLayout* m_GridLayout = new QGridLayout;
    QHBoxLayout* m_hLayout    = new QHBoxLayout;
    mLayout->addLayout(m_GridLayout);
    mLayout->addLayout(m_hLayout);

    selectCurveLab        = new QLabel(QStringLiteral("选择曲线："), mWidget);
    selectBodyLab         = new QLabel(QStringLiteral("未选择"), mWidget);
    offsetDirectionLab    = new QLabel(QStringLiteral("偏移方向："), mWidget);
    offsetDistanceLab     = new QLabel(QStringLiteral("偏移距离："), mWidget);
    selectBtn             = new QPushButton(QStringLiteral("选取"), mWidget);
    previewBtn            = new QPushButton(QStringLiteral("预览"), mWidget);
    cancelBtn             = new QPushButton(QStringLiteral("取消"), mWidget);
    confrimBtn            = new QPushButton(QStringLiteral("确定"), mWidget);
    x_offsetDirectionEdit = new QLineEdit(QStringLiteral("0"), mWidget);
    y_offsetDirectionEdit = new QLineEdit(QStringLiteral("0"), mWidget);
    z_offsetDirectionEdit = new QLineEdit(QStringLiteral("1"), mWidget);
    offsetDistanceEdit    = new QLineEdit(QStringLiteral("20"), mWidget);

    selectCurveLab->setProperty("featureWidget-lab", true);
    selectBodyLab->setProperty("featureWidget-lab", true);
    offsetDirectionLab->setProperty("featureWidget-lab", true);
    offsetDistanceLab->setProperty("featureWidget-lab", true);
    x_offsetDirectionEdit->setProperty("featureWidget-lineEdit", true);
    y_offsetDirectionEdit->setProperty("featureWidget-lineEdit", true);
    z_offsetDirectionEdit->setProperty("featureWidget-lineEdit", true);
    offsetDistanceEdit->setProperty("featureWidget-lineEdit", true);
    selectBtn->setProperty("featureWidget-btn", true);
    previewBtn->setProperty("featureWidget-btn", true);
    cancelBtn->setProperty("featureWidget-btn", true);
    confrimBtn->setObjectName("MessageBox-btn");

    x_offsetDirectionEdit->setFixedSize(70, 24);
    y_offsetDirectionEdit->setFixedSize(70, 24);
    z_offsetDirectionEdit->setFixedSize(70, 24);
    offsetDistanceEdit->setMinimumSize(200, 24);
    selectBtn->setFixedSize(70, 32);
    previewBtn->setFixedSize(88, 32);
    cancelBtn->setFixedSize(88, 32);
    confrimBtn->setFixedSize(88, 32);

    m_GridLayout->addWidget(selectCurveLab, 0, 0);
    m_GridLayout->addWidget(selectBodyLab, 0, 1, 1, 2);
    m_GridLayout->addWidget(selectBtn, 0, 3);
    m_GridLayout->addWidget(offsetDirectionLab, 1, 0);
    m_GridLayout->addWidget(x_offsetDirectionEdit, 1, 1);
    m_GridLayout->addWidget(y_offsetDirectionEdit, 1, 2);
    m_GridLayout->addWidget(z_offsetDirectionEdit, 1, 3);
    m_GridLayout->addWidget(offsetDistanceLab, 2, 0);
    m_GridLayout->addWidget(offsetDistanceEdit, 2, 1, 1, 3);
    m_hLayout->addWidget(previewBtn);
    m_hLayout->addWidget(cancelBtn);
    m_hLayout->addWidget(confrimBtn);
    setWidget(mWidget);
}

bool NCTI::CreateCurveOffsetWgt::UpDate()
{
    if (m_SelObjVec.size() == 0) {
        MESSAGEBOX_INSTANCE->showMessageBox(QStringLiteral("实体对象未选中"));
        return false;
    }

    if (x_offsetDirectionEdit->text().isEmpty() || y_offsetDirectionEdit->text().isEmpty()
        || z_offsetDirectionEdit->text().isEmpty()) {
        MESSAGEBOX_INSTANCE->showMessageBox(QStringLiteral("偏移方向输入无效"));
        return false;
    }
    QVector3D Vec(x_offsetDirectionEdit->text().toDouble(),
                  y_offsetDirectionEdit->text().toDouble(),
                  z_offsetDirectionEdit->text().toDouble());
    m_Vector         = Vec;
    double vecLength = m_Vector.length();
    if (vecLength == 0) {
        MESSAGEBOX_INSTANCE->showMessageBox(QStringLiteral("无效向量"));
        return false;
    }

    if (offsetDistanceEdit->text() == "0") {
        MESSAGEBOX_INSTANCE->showMessageBox(QStringLiteral("偏移距离不能为零"));
        return false;
    }
    offsetDistance = offsetDistanceEdit->text().toDouble();

    return true;
}

void NCTI::CreateCurveOffsetWgt::onOK()
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
        argumentObject.SetScale(offsetDistance);
        pComMan->RunCommand("cmd_ncti_offset_object", &argumentObject);
    }
    close();
    SetInstance(nullptr);
}

void NCTI::CreateCurveOffsetWgt::onCanle()
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

void NCTI::CreateCurveOffsetWgt::onSelect()
{
    std::vector<NCTI_MODEL_TAG> selectCells;
    NctiDocElementPubFun::GetDisplayObjectFromSelManager(m_Document, m_SelObjVec, selectCells);

    if (m_SelObjVec.size() == 0) {
        MESSAGEBOX_INSTANCE->showMessageBox(QStringLiteral("实体对象未选中"));
    }
    else {
        selectBodyLab->setText(QStringLiteral("已选取对象"));
    }
}

void NCTI::CreateCurveOffsetWgt::onPreview()
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
    argumentObject.SetScale(offsetDistance);
    NctiComModelTool::RunUpdateScriptModelViewFun(m_Document, &argumentObject);
}
