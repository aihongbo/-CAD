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

#include "CreateLinearArrayWgt.h"
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
#include "NctiMeasuringTool.h"
#include "NctiString.h"
#include "NctiComModelTool.h"
#include "NctiDocViewManager.h"
#include "NctiHistoryManager.h"

namespace NCTI {
CreateLinearArrayWgt* CreateLinearArrayWgt::m_Instance = nullptr;

CreateLinearArrayWgt::CreateLinearArrayWgt(NctiDocument* i_pDocument, QWidget* parent)
    : NctiBaseDialog(parent)
    , m_Document(i_pDocument)
{
    initUI();

    connect(selBodyBtn, &QPushButton::clicked, this, &CreateLinearArrayWgt::onSelObject);
    connect(previewBtn, &QPushButton::clicked, this, &CreateLinearArrayWgt::onPreview);
    connect(confrimBtn, &QPushButton::clicked, this, &CreateLinearArrayWgt::onOk);
    connect(cancelBtn, &QPushButton::clicked, this, &CreateLinearArrayWgt::onCanle);
    connect(this, &CreateLinearArrayWgt::sigClose, this, &CreateLinearArrayWgt::onCanle);

    if (i_pDocument) {
        NctiCommandManager* pComMan = NctiCommandManager::GetCommandManager(i_pDocument->GetBaseModel());
        EnumNctiResult result       = pComMan->RunCommand("cmd_ncti_model_create_linear_periodic");
    }

    NctiMeasuringTool::instance()->SetCalVectorCallback(CreateLinearArrayWgt::GetVectorFun); // 获取法向量的。
}

CreateLinearArrayWgt::~CreateLinearArrayWgt()
{
    NctiMeasuringTool::instance()->ResetAll();
}

void CreateLinearArrayWgt::SetVector(NctiVector pVector)
{
    X_directionEdit->setText(NctiString::double_to_string(pVector.x(), 15).c_str());
    Y_directionEdit->setText(NctiString::double_to_string(pVector.y(), 15).c_str());
    Z_directionEdit->setText(NctiString::double_to_string(pVector.z(), 15).c_str());
}

CreateLinearArrayWgt* CreateLinearArrayWgt::instance()
{
    return m_Instance;
}

void CreateLinearArrayWgt::SetInstance(CreateLinearArrayWgt* pDlg)
{
    m_Instance = pDlg;
}

void CreateLinearArrayWgt::GetVectorFun(NctiVector pVector)
{
    if (m_Instance == nullptr)
        return;
    m_Instance->SetVector(pVector);
}

void CreateLinearArrayWgt::initUI()
{
    this->setTitle(QStringLiteral("直线阵列"));
    QWidget* mWidget          = new QWidget(this);
    QVBoxLayout* mLayout      = new QVBoxLayout(mWidget);
    QGridLayout* m_GridLayout = new QGridLayout;
    QHBoxLayout* m_hLayout    = new QHBoxLayout;
    mLayout->addLayout(m_GridLayout);
    mLayout->addLayout(m_hLayout);

    selectLabel      = new QLabel(QStringLiteral("选取实体："), mWidget);
    selectBodyLabel  = new QLabel(QStringLiteral("未选取"), mWidget);
    directionLabel   = new QLabel(QStringLiteral("方向："), mWidget);
    offsetRangeLabel = new QLabel(QStringLiteral("偏移距离："), mWidget);
    newQuantityLabel = new QLabel(QStringLiteral("新增数量："), mWidget);
    X_directionEdit  = new QLineEdit(QStringLiteral("1"), mWidget);
    Y_directionEdit  = new QLineEdit(QStringLiteral("0"), mWidget);
    Z_directionEdit  = new QLineEdit(QStringLiteral("0"), mWidget);
    offsetRangeEdit  = new QLineEdit(QStringLiteral("10"), mWidget);
    newQuantityEdit  = new QLineEdit(QStringLiteral("1"), mWidget);
    selBodyBtn       = new QPushButton(QStringLiteral("取体"), mWidget);
    previewBtn       = new QPushButton(QStringLiteral("预览"), mWidget);
    cancelBtn        = new QPushButton(QStringLiteral("取消"), mWidget);
    confrimBtn       = new QPushButton(QStringLiteral("确定"), mWidget);

    selectLabel->setProperty("featureWidget-lab", true);
    selectBodyLabel->setProperty("featureWidget-lab", true);
    directionLabel->setProperty("featureWidget-lab", true);
    offsetRangeLabel->setProperty("featureWidget-lab", true);
    newQuantityLabel->setProperty("featureWidget-lab", true);
    X_directionEdit->setProperty("featureWidget-lineEdit", true);
    Y_directionEdit->setProperty("featureWidget-lineEdit", true);
    Z_directionEdit->setProperty("featureWidget-lineEdit", true);
    offsetRangeEdit->setProperty("featureWidget-lineEdit", true);
    newQuantityEdit->setProperty("featureWidget-lineEdit", true);
    selBodyBtn->setProperty("featureWidget-btn", true);
    previewBtn->setProperty("featureWidget-btn", true);
    cancelBtn->setProperty("featureWidget-btn", true);
    confrimBtn->setObjectName("MessageBox-btn");

    X_directionEdit->setFixedSize(70, 24);
    Y_directionEdit->setFixedSize(70, 24);
    Z_directionEdit->setFixedSize(70, 24);
    offsetRangeEdit->setMinimumSize(200, 24);
    newQuantityEdit->setMinimumSize(200, 24);
    selBodyBtn->setFixedSize(70, 32);
    previewBtn->setFixedSize(88, 32);
    cancelBtn->setFixedSize(88, 32);
    confrimBtn->setFixedSize(88, 32);

    m_GridLayout->addWidget(selectLabel, 0, 0);
    m_GridLayout->addWidget(selectBodyLabel, 0, 1, 1, 2);
    m_GridLayout->addWidget(selBodyBtn, 0, 3);
    m_GridLayout->addWidget(directionLabel, 1, 0);
    m_GridLayout->addWidget(offsetRangeLabel, 2, 0);
    m_GridLayout->addWidget(newQuantityLabel, 3, 0);
    m_GridLayout->addWidget(X_directionEdit, 1, 1);
    m_GridLayout->addWidget(Y_directionEdit, 1, 2);
    m_GridLayout->addWidget(Z_directionEdit, 1, 3);
    m_GridLayout->addWidget(offsetRangeEdit, 2, 1, 1, 3);
    m_GridLayout->addWidget(newQuantityEdit, 3, 1, 1, 3);

    m_hLayout->addWidget(previewBtn);
    m_hLayout->addWidget(cancelBtn);
    m_hLayout->addWidget(confrimBtn);

    setWidget(mWidget);
}

bool CreateLinearArrayWgt::UpDate()
{
    if (m_SelObjVec.size() == 0) {
        MESSAGEBOX_INSTANCE->showMessageBox(QStringLiteral("实体对象未选中"));
        return false;
    }
    if (X_directionEdit->text().isEmpty() || Y_directionEdit->text().isEmpty() || Z_directionEdit->text().isEmpty()) {
        MESSAGEBOX_INSTANCE->showMessageBox(QStringLiteral("向量输入无效"));
        return false;
    }
    QVector3D vector(
        X_directionEdit->text().toDouble(), Y_directionEdit->text().toDouble(), Z_directionEdit->text().toDouble());
    double vecLength = vector.length();
    if (vecLength == 0) {
        MESSAGEBOX_INSTANCE->showMessageBox(QStringLiteral("无效向量"));
        return false;
    }
    // 归一化向量，得到单位向量
    m_Vector = vector / vecLength;

    if (offsetRangeEdit->text().isEmpty()) {
        MESSAGEBOX_INSTANCE->showMessageBox(QStringLiteral("偏移距离未输入"));
        return false;
    }
    offsetRange = offsetRangeEdit->text().toDouble();
    if (offsetRange == 0) {
        MESSAGEBOX_INSTANCE->showMessageBox(QStringLiteral("偏移距离不能为0"));
        return false;
    }
    m_Vector = m_Vector * offsetRange;

    if (newQuantityEdit->text().isEmpty()) {
        MESSAGEBOX_INSTANCE->showMessageBox(QStringLiteral("新增数量未输入"));
        return false;
    }
    newQuantity = newQuantityEdit->text().toInt();
    if (newQuantity < 0) {
        MESSAGEBOX_INSTANCE->showMessageBox(QStringLiteral("新增数量不能为负值"));
        return false;
    }

    return true;
}
void CreateLinearArrayWgt::onOk()
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
        argumentObject.SetIntValue(newQuantity);
        pComMan->RunCommand("cmd_ncti_linear_array", &argumentObject);
    }
    close();
    SetInstance(nullptr);
}
void CreateLinearArrayWgt::onSelObject()
{
    std::vector<NCTI_MODEL_TAG> selectCells;
    NctiDocElementPubFun::GetDisplayObjectFromSelManager(m_Document, m_SelObjVec, selectCells);

    if (m_SelObjVec.size() == 0) {
        MESSAGEBOX_INSTANCE->showMessageBox(QStringLiteral("实体对象未选中"));
    }
    else {
        selectBodyLabel->setText(
            QStringLiteral("已选取对象（<font color = #1771f8>%1</font>）").arg(QString::number(m_SelObjVec.size())));
    }
}
void CreateLinearArrayWgt::onCanle()
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
void CreateLinearArrayWgt::onPreview()
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
    argumentObject.SetIntValue(newQuantity);

    NctiComModelTool::RunUpdateScriptModelViewFun(m_Document, &argumentObject);
}
} // namespace NCTI
