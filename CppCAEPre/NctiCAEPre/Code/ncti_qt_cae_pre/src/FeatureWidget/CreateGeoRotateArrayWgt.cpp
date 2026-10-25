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

#include "CreateGeoRotateArrayWgt.h"
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
using namespace NCTI;

CreateGeoRotateArrayWgt* CreateGeoRotateArrayWgt::m_Instance = nullptr;

NCTI::CreateGeoRotateArrayWgt::CreateGeoRotateArrayWgt(NctiDocument* i_pDocument, QWidget* parent)
    : NctiBaseDialog(parent)
    , m_Document(i_pDocument)
{
    initUI();

    connect(selBodyBtn, &QPushButton::clicked, this, &CreateGeoRotateArrayWgt::onSelObject);
    connect(previewBtn, &QPushButton::clicked, this, &CreateGeoRotateArrayWgt::onPreview);
    connect(confrimBtn, &QPushButton::clicked, this, &CreateGeoRotateArrayWgt::onOk);
    connect(cancelBtn, &QPushButton::clicked, this, &CreateGeoRotateArrayWgt::onCanle);
    connect(this, &CreateGeoRotateArrayWgt::sigClose, this, &CreateGeoRotateArrayWgt::onCanle);

    if (i_pDocument) {
        NctiCommandManager* pComMan = NctiCommandManager::GetCommandManager(i_pDocument->GetBaseModel());
        EnumNctiResult result       = pComMan->RunCommand("cmd_ncti_model_create_rotate_periodic");
    }

    NctiMeasuringTool::instance()->SetCalPositionCallback(CreateGeoRotateArrayWgt::GetPositionFun);
    NctiMeasuringTool::instance()->SetCalMidPositionCallback(CreateGeoRotateArrayWgt::GetPositionFun);
    NctiMeasuringTool::instance()->SetCalCenterCallback(CreateGeoRotateArrayWgt::GetPositionFun);
    NctiMeasuringTool::instance()->SetCalVectorCallback(CreateGeoRotateArrayWgt::GetVectorFun); // 获取法向量的。
}

NCTI::CreateGeoRotateArrayWgt::~CreateGeoRotateArrayWgt()
{
    NctiMeasuringTool::instance()->ResetAll();
}

void NCTI::CreateGeoRotateArrayWgt::SetPosition(NctiPosition Point)
{
    xLineEdit->setText(NctiString::double_to_string(Point.x(), 15).c_str());
    yLineEdit->setText(NctiString::double_to_string(Point.y(), 15).c_str());
    zLineEdit->setText(NctiString::double_to_string(Point.z(), 15).c_str());
}

void NCTI::CreateGeoRotateArrayWgt::SetVector(NctiVector pVector)
{
    xVecLineEdit->setText(NctiString::double_to_string(pVector.x(), 15).c_str());
    yVecLineEdit->setText(NctiString::double_to_string(pVector.y(), 15).c_str());
    zVecLineEdit->setText(NctiString::double_to_string(pVector.z(), 15).c_str());
}

CreateGeoRotateArrayWgt* NCTI::CreateGeoRotateArrayWgt::instance()
{
    return m_Instance;
}

void NCTI::CreateGeoRotateArrayWgt::SetInstance(CreateGeoRotateArrayWgt* pDlg)
{
    m_Instance = pDlg;
}

void NCTI::CreateGeoRotateArrayWgt::GetPositionFun(NctiPosition Point)
{
    if (m_Instance == nullptr)
        return;
    m_Instance->SetPosition(Point);
}

void NCTI::CreateGeoRotateArrayWgt::GetVectorFun(NctiVector pVector)
{
    if (m_Instance == nullptr)
        return;
    m_Instance->SetVector(pVector);
}

void NCTI::CreateGeoRotateArrayWgt::initUI()
{
    this->setTitle(QStringLiteral("旋转阵列"));
    QWidget* mWidget          = new QWidget(this);
    QVBoxLayout* mLayout      = new QVBoxLayout(mWidget);
    QGridLayout* m_GridLayout = new QGridLayout;
    QHBoxLayout* m_hLayout    = new QHBoxLayout;
    mLayout->addLayout(m_GridLayout);
    mLayout->addLayout(m_hLayout);

    selectLabel         = new QLabel(QStringLiteral("选取实体："), mWidget);
    selectBodyLabel     = new QLabel(QStringLiteral("未选取"), mWidget);
    pointLabel          = new QLabel(QStringLiteral("点："), mWidget);
    vecLabel            = new QLabel(QStringLiteral("向量："), mWidget);
    newQuantityLabel    = new QLabel(QStringLiteral("新增数量："), mWidget);
    rotateAngleLabel    = new QLabel(QStringLiteral("旋转角度："), mWidget);
    xLineEdit           = new QLineEdit(QStringLiteral("0"), mWidget);
    yLineEdit           = new QLineEdit(QStringLiteral("0"), mWidget);
    zLineEdit           = new QLineEdit(QStringLiteral("0"), mWidget);
    xVecLineEdit        = new QLineEdit(QStringLiteral("0"), mWidget);
    yVecLineEdit        = new QLineEdit(QStringLiteral("0"), mWidget);
    zVecLineEdit        = new QLineEdit(QStringLiteral("1"), mWidget);
    newQuantityLineEdit = new QLineEdit(QStringLiteral("2"), mWidget);
    rotateAngleLineEdit = new QLineEdit(QStringLiteral("90"), mWidget);
    selBodyBtn          = new QPushButton(QStringLiteral("取体"), mWidget);
    previewBtn          = new QPushButton(QStringLiteral("预览"), mWidget);
    cancelBtn           = new QPushButton(QStringLiteral("取消"), mWidget);
    confrimBtn          = new QPushButton(QStringLiteral("确定"), mWidget);

    selectLabel->setProperty("featureWidget-lab", true);
    selectBodyLabel->setProperty("featureWidget-lab", true);
    pointLabel->setProperty("featureWidget-lab", true);
    vecLabel->setProperty("featureWidget-lab", true);
    newQuantityLabel->setProperty("featureWidget-lab", true);
    rotateAngleLabel->setProperty("featureWidget-lab", true);
    xLineEdit->setProperty("featureWidget-lineEdit", true);
    yLineEdit->setProperty("featureWidget-lineEdit", true);
    zLineEdit->setProperty("featureWidget-lineEdit", true);
    xVecLineEdit->setProperty("featureWidget-lineEdit", true);
    yVecLineEdit->setProperty("featureWidget-lineEdit", true);
    zVecLineEdit->setProperty("featureWidget-lineEdit", true);
    newQuantityLineEdit->setProperty("featureWidget-lineEdit", true);
    rotateAngleLineEdit->setProperty("featureWidget-lineEdit", true);
    selBodyBtn->setProperty("featureWidget-btn", true);
    previewBtn->setProperty("featureWidget-btn", true);
    cancelBtn->setProperty("featureWidget-btn", true);
    confrimBtn->setObjectName("MessageBox-btn");

    xLineEdit->setFixedSize(70, 24);
    yLineEdit->setFixedSize(70, 24);
    zLineEdit->setFixedSize(70, 24);
    xVecLineEdit->setFixedSize(70, 24);
    yVecLineEdit->setFixedSize(70, 24);
    zVecLineEdit->setFixedSize(70, 24);
    newQuantityLineEdit->setMinimumSize(200, 24);
    rotateAngleLineEdit->setMinimumSize(200, 24);
    selBodyBtn->setFixedSize(70, 32);
    previewBtn->setFixedSize(88, 32);
    cancelBtn->setFixedSize(88, 32);
    confrimBtn->setFixedSize(88, 32);

    m_GridLayout->addWidget(selectLabel, 0, 0);
    m_GridLayout->addWidget(selectBodyLabel, 0, 1, 1, 2);
    m_GridLayout->addWidget(selBodyBtn, 0, 3);
    m_GridLayout->addWidget(pointLabel, 1, 0);
    m_GridLayout->addWidget(vecLabel, 2, 0);
    m_GridLayout->addWidget(newQuantityLabel, 3, 0);
    m_GridLayout->addWidget(rotateAngleLabel, 4, 0);
    m_GridLayout->addWidget(xLineEdit, 1, 1);
    m_GridLayout->addWidget(yLineEdit, 1, 2);
    m_GridLayout->addWidget(zLineEdit, 1, 3);
    m_GridLayout->addWidget(xVecLineEdit, 2, 1);
    m_GridLayout->addWidget(yVecLineEdit, 2, 2);
    m_GridLayout->addWidget(zVecLineEdit, 2, 3);
    m_GridLayout->addWidget(newQuantityLineEdit, 3, 1, 1, 3);
    m_GridLayout->addWidget(rotateAngleLineEdit, 4, 1, 1, 3);

    m_hLayout->addWidget(previewBtn);
    m_hLayout->addWidget(cancelBtn);
    m_hLayout->addWidget(confrimBtn);

    setWidget(mWidget);
}

bool NCTI::CreateGeoRotateArrayWgt::UpDate()
{
    if (m_SelObjVec.size() == 0) {
        MESSAGEBOX_INSTANCE->showMessageBox(QStringLiteral("实体对象未选中"));
        return false;
    }
    if (xLineEdit->text().isEmpty() || yLineEdit->text().isEmpty() || zLineEdit->text().isEmpty()) {
        MESSAGEBOX_INSTANCE->showMessageBox(QStringLiteral("点输入无效"));
        return false;
    }
    px = xLineEdit->text().toDouble();
    py = yLineEdit->text().toDouble();
    pz = zLineEdit->text().toDouble();
    if (xVecLineEdit->text().isEmpty() || yVecLineEdit->text().isEmpty() || zVecLineEdit->text().isEmpty()) {
        MESSAGEBOX_INSTANCE->showMessageBox(QStringLiteral("向量输入无效"));
        return false;
    }
    QVector3D Vec(xVecLineEdit->text().toDouble(), yVecLineEdit->text().toDouble(), zVecLineEdit->text().toDouble());
    m_Vector         = Vec;
    double vecLength = m_Vector.length();
    if (vecLength == 0) {
        MESSAGEBOX_INSTANCE->showMessageBox(QStringLiteral("无效向量"));
        return false;
    }

    if (newQuantityLineEdit->text().isEmpty()) {
        MESSAGEBOX_INSTANCE->showMessageBox(QStringLiteral("新增数量未输入"));
        return false;
    }
    newQuantity = newQuantityLineEdit->text().toInt();
    if (newQuantity < 0) {
        MESSAGEBOX_INSTANCE->showMessageBox(QStringLiteral("新增数量不能为负值"));
        return false;
    }

    if (rotateAngleLineEdit->text().isEmpty()) {
        MESSAGEBOX_INSTANCE->showMessageBox(QStringLiteral("旋转角度未输入"));
        return false;
    }
    rotateAngle = rotateAngleLineEdit->text().toInt();
    if (rotateAngle < 0) {
        MESSAGEBOX_INSTANCE->showMessageBox(QStringLiteral("旋转角度不能为负值"));
        return false;
    }

    return true;
}

void NCTI::CreateGeoRotateArrayWgt::onOk()
{
    NctiBaseModel* pBaseModel   = m_Document->GetBaseModel();
    NctiCommandManager* pComMan = NctiCommandManager::GetCommandManager(pBaseModel);
    if (pComMan) {
        pComMan->ProcessCancelButton();
        pComMan->RequestTermination(NULL);
        pComMan->ExitCommand();

        if (!UpDate())
            return;

        NctiPosition pt;
        pt.set_x(px);
        pt.set_y(py);
        pt.set_z(pz);
        NctiVector m_Dir;
        m_Dir.set_x(m_Vector.x());
        m_Dir.set_y(m_Vector.y());
        m_Dir.set_z(m_Vector.z());
        NctiArgumentObject argumentObject;
        argumentObject.SetDisplayObjectVec(m_SelObjVec);
        argumentObject.SetPt(pt);
        argumentObject.SetDir(m_Dir);
        argumentObject.SetIntValue(newQuantity);
        argumentObject.SetFloatValue(rotateAngle);
        pComMan->RunCommand("cmd_ncti_rotate_array", &argumentObject);
    }
    close();
    SetInstance(nullptr);
}

void NCTI::CreateGeoRotateArrayWgt::onSelObject()
{
    NctiDocElementPubFun::GetDisplayObjectFromSelManager(m_Document, m_SelObjVec);

    if (m_SelObjVec.size() == 0) {
        MESSAGEBOX_INSTANCE->showMessageBox(QStringLiteral("实体对象未选中"));
    }
    else {
        selectBodyLabel->setText(
            QStringLiteral("已选取对象（<font color = #1771f8>%1</font>）").arg(QString::number(m_SelObjVec.size())));
    }
}

void NCTI::CreateGeoRotateArrayWgt::onCanle()
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

void NCTI::CreateGeoRotateArrayWgt::onPreview()
{
    if (!UpDate())
        return;

    NctiPosition pt;
    pt.set_x(px);
    pt.set_y(py);
    pt.set_z(pz);
    NctiVector m_Dir;
    m_Dir.set_x(m_Vector.x());
    m_Dir.set_y(m_Vector.y());
    m_Dir.set_z(m_Vector.z());
    NctiArgumentObject argumentObject;
    argumentObject.SetDisplayObjectVec(m_SelObjVec);
    argumentObject.SetPt(pt);
    argumentObject.SetDir(m_Dir);
    argumentObject.SetIntValue(newQuantity);
    argumentObject.SetFloatValue(rotateAngle);
    NctiComModelTool::RunUpdateScriptModelViewFun(m_Document, &argumentObject);
}
