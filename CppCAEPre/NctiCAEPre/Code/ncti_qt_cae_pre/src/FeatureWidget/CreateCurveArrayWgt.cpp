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

#include "CreateCurveArrayWgt.h"

#include <QGridLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QDebug>
#include "NctiMessageBox.h"

#include "NctiDocument.h"
#include "NctiCommandManager.h"
#include "NctiDocElementPubFun.h"
#include "NctiArgumentObject.h"
#include "NctiDisplayModelBody.h"
#include "NctiDisplayDocCustomContainer.h"
#include "NctiComModelTool.h"

NCTI::CreateCurveArrayWgt::CreateCurveArrayWgt(NctiDocument* i_pDocument, QWidget* parent)
    : NctiBaseDialog(parent)
    , m_pDocument(i_pDocument)
    , m_DisplayObject1(nullptr)
    , m_DisplayObject2(nullptr)
{
    initUI();

    connect(selectCurveBtn, &QPushButton::clicked, this, &CreateCurveArrayWgt::onSelectObject1);
    connect(selectBodyBtn, &QPushButton::clicked, this, &CreateCurveArrayWgt::onSelectObject2);
    connect(previewBtn, &QPushButton::clicked, this, &CreateCurveArrayWgt::onPreview);
    connect(confrimBtn, &QPushButton::clicked, this, &CreateCurveArrayWgt::onOK);
    connect(cancelBtn, &QPushButton::clicked, this, &CreateCurveArrayWgt::onCanle);
    connect(this, &CreateCurveArrayWgt::sigClose, this, &CreateCurveArrayWgt::onCanle);

    if (i_pDocument) {
        NctiCommandManager* pComMan = NctiCommandManager::GetCommandManager(i_pDocument->GetBaseModel());
        EnumNctiResult result       = pComMan->RunCommand("cmd_ncti_model_create_curve_array");
    }
}

void NCTI::CreateCurveArrayWgt::initUI()
{
    this->setTitle(QStringLiteral("曲线阵列"));
    QWidget* mWidget          = new QWidget(this);
    QVBoxLayout* mLayout      = new QVBoxLayout(mWidget);
    QGridLayout* m_GridLayout = new QGridLayout;
    QHBoxLayout* m_hLayout    = new QHBoxLayout;
    mLayout->addLayout(m_GridLayout);
    mLayout->addLayout(m_hLayout);

    selectCurveLab   = new QLabel(QStringLiteral("选择曲线："), mWidget);
    curveSelectedLab = new QLabel(QStringLiteral("未选取"), mWidget);
    selectBodyLab    = new QLabel(QStringLiteral("选择实体："), mWidget);
    bodySelectedLab  = new QLabel(QStringLiteral("未选取"), mWidget);
    newQuantityLab   = new QLabel(QStringLiteral("新增数量"), mWidget);
    selectCurveBtn   = new QPushButton(QStringLiteral("选取"), mWidget);
    selectBodyBtn    = new QPushButton(QStringLiteral("选取"), mWidget);
    previewBtn       = new QPushButton(QStringLiteral("预览"), mWidget);
    cancelBtn        = new QPushButton(QStringLiteral("取消"), mWidget);
    confrimBtn       = new QPushButton(QStringLiteral("确认"), mWidget);
    newQuantityEdit  = new QLineEdit(QStringLiteral("2"), mWidget);

    selectCurveLab->setProperty("featureWidget-lab", true);
    curveSelectedLab->setProperty("featureWidget-lab", true);
    selectBodyLab->setProperty("featureWidget-lab", true);
    bodySelectedLab->setProperty("featureWidget-lab", true);
    newQuantityLab->setProperty("featureWidget-lab", true);
    newQuantityEdit->setProperty("featureWidget-lineEdit", true);
    selectCurveBtn->setProperty("featureWidget-btn", true);
    selectBodyBtn->setProperty("featureWidget-btn", true);
    previewBtn->setProperty("featureWidget-btn", true);
    cancelBtn->setProperty("featureWidget-btn", true);
    confrimBtn->setObjectName("MessageBox-btn");

    newQuantityEdit->setMinimumSize(200, 24);
    selectCurveBtn->setFixedSize(70, 32);
    selectBodyBtn->setFixedSize(70, 32);
    previewBtn->setFixedSize(88, 32);
    cancelBtn->setFixedSize(88, 32);
    confrimBtn->setFixedSize(88, 32);

    m_GridLayout->addWidget(selectCurveLab, 0, 0);
    m_GridLayout->addWidget(curveSelectedLab, 0, 1);
    m_GridLayout->addWidget(selectCurveBtn, 0, 2);
    m_GridLayout->addWidget(selectBodyLab, 1, 0);
    m_GridLayout->addWidget(bodySelectedLab, 1, 1);
    m_GridLayout->addWidget(selectBodyBtn, 1, 2);
    m_GridLayout->addWidget(newQuantityLab, 2, 0);
    m_GridLayout->addWidget(newQuantityEdit, 2, 1, 1, 2);
    m_hLayout->addWidget(previewBtn);
    m_hLayout->addWidget(cancelBtn);
    m_hLayout->addWidget(confrimBtn);
    setWidget(mWidget);
}

bool NCTI::CreateCurveArrayWgt::UpDate()
{
    if (m_DisplayObject1 == nullptr) {
        MESSAGEBOX_INSTANCE->showMessageBox("未选择曲线");
        return false;
    }
    if (m_DisplayObject2 == nullptr) {
        MESSAGEBOX_INSTANCE->showMessageBox("未选择实体对象");
        return false;
    }
    if (newQuantityEdit->text().isEmpty()) {
        MESSAGEBOX_INSTANCE->showMessageBox("新增数量未输入");
        return false;
    }
    newQuantity = newQuantityEdit->text().toInt();
    if (newQuantity < 0) {
        MESSAGEBOX_INSTANCE->showMessageBox("新增数量不能为负数");
        return false;
    }

    return true;
}

void NCTI::CreateCurveArrayWgt::onOK()
{
    NctiBaseModel* pBaseModel   = m_pDocument->GetBaseModel();
    NctiCommandManager* pComMan = NctiCommandManager::GetCommandManager(pBaseModel);
    if (pComMan) {
        pComMan->ProcessCancelButton();
        pComMan->RequestTermination(NULL);
        pComMan->ExitCommand();

        if (!UpDate())
            return;
        NctiArgumentObject argumentObject;
        argumentObject.SetDisplayObject1(m_DisplayObject1);
        argumentObject.SetDisplayObject2(m_DisplayObject2);
        argumentObject.SetIntValue(newQuantity);
        pComMan->RunCommand("cmd_ncti_curve_array", &argumentObject);
    }
    close();
}

void NCTI::CreateCurveArrayWgt::onCanle()
{
    NctiBaseModel* pBaseModel   = m_pDocument->GetBaseModel();
    NctiCommandManager* pComMan = NctiCommandManager::GetCommandManager(pBaseModel);
    if (pComMan) {
        pComMan->ProcessCancelButton();
        pComMan->RequestTermination(NULL);
        pComMan->ExitCommand();
    }
    close();
}

void NCTI::CreateCurveArrayWgt::onSelectObject1()
{
    std::vector<NctiDisplayObject*> selectObjects;
    std::vector<NCTI_MODEL_TAG> selectCells;
    NctiDocElementPubFun::GetDisplayObjectFromSelManager(m_pDocument, selectObjects, selectCells);
    if (selectObjects.size() == 1) {
        m_DisplayObject1 = selectObjects[0];
        curveSelectedLab->setText("已选取");

        return;
    }
    else {
        MESSAGEBOX_INSTANCE->showMessageBox("实体对象不为1");
    }
}

void NCTI::CreateCurveArrayWgt::onSelectObject2()
{
    std::vector<NctiDisplayObject*> selectObjects;
    std::vector<NCTI_MODEL_TAG> selectCells;
    NctiDocElementPubFun::GetDisplayObjectFromSelManager(m_pDocument, selectObjects, selectCells);
    if (selectObjects.size() == 1) {
        m_DisplayObject2 = selectObjects[0];
        bodySelectedLab->setText("已选取");
    }
    else {
        MESSAGEBOX_INSTANCE->showMessageBox("实体对象不为1");
    }
}

void NCTI::CreateCurveArrayWgt::onPreview()
{
    if (!UpDate())
        return;
    NctiArgumentObject argumentObject;
    argumentObject.SetDisplayObject1(m_DisplayObject1);
    argumentObject.SetDisplayObject2(m_DisplayObject2);
    argumentObject.SetIntValue(newQuantity);

    NctiComModelTool::RunUpdateScriptModelViewFun(m_pDocument, &argumentObject);
}
