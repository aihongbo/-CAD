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

#include "CreateBooleanWgt.h"
#include "ui_CreateBooleanWgtContent.h"

#include <QListView>
#include <QThread>
#include "NctiMessageBox.h"

#include "NctiBaseModel.h"
#include "NctiDocument.h"
#include "NctiCommandManager.h"
#include "NctiDocElementPubFun.h"
#include "NctiArgumentObject.h"
#include "NctiDisplayObject.h"
#include "NctiJsonDocument.h"
#include "NctiComModelTool.h"

namespace NCTI {
CreateBooleanWgt::CreateBooleanWgt(NctiDocument* i_pDocument, QWidget* parent)
    : NctiBaseDialog(parent)
    , ui(new Ui::CreateBooleanWgtContent)
    , m_Document(i_pDocument)
    , m_DisplayObject1(nullptr)
    , m_DisplayObject2(nullptr)
{
    initUI();
    connect(ui->selBtn1, SIGNAL(clicked()), this, SLOT(onSelect1()));
    connect(ui->selBtn2, SIGNAL(clicked()), this, SLOT(onSelect2()));
    connect(ui->previewBtn, &QPushButton::clicked, this, &CreateBooleanWgt::onPreview);
    connect(ui->confrimBtn, &QPushButton::clicked, this, &CreateBooleanWgt::onOk);
    connect(ui->cancelBtn, &QPushButton::clicked, this, &CreateBooleanWgt::onCanle);
    connect(this, &CreateBooleanWgt::sigClose, this, &CreateBooleanWgt::onCanle);

    if (i_pDocument) {
        NctiCommandManager* pComMan = NctiCommandManager::GetCommandManager(i_pDocument->GetBaseModel());
        EnumNctiResult result       = pComMan->RunCommand("cmd_ncti_model_create_boolean");
        //UpdateView();
    }
}

CreateBooleanWgt::~CreateBooleanWgt()
{
    NCTI_DELETE ui;
}

void CreateBooleanWgt::initUI()
{
    auto widget = new QWidget(this);
    widget->setObjectName("featureWidget-widget");
    ui->setupUi(widget);

    ui->bodyLabel1->setProperty("featureWidget-lab", true);
    ui->bodyLabel2->setProperty("featureWidget-lab", true);
    ui->bolModeLabel->setProperty("featureWidget-lab", true);
    ui->selBodyLabel1->setProperty("featureWidget-lab", true);
    ui->selBodyLabel2->setProperty("featureWidget-lab", true);

    ui->selBtn1->setProperty("featureWidget-btn", true);
    ui->selBtn2->setProperty("featureWidget-btn", true);

    QListView* listView = new QListView(ui->bolModeCombo);
    listView->setAlternatingRowColors(true);
    ui->bolModeCombo->setView(listView);
    ui->bolModeCombo->setFocusPolicy(Qt::NoFocus);
    ui->bolModeCombo->addItem(QStringLiteral("并集"), 0);
    ui->bolModeCombo->addItem(QStringLiteral("差集"), 1);
    ui->bolModeCombo->addItem(QStringLiteral("交集"), 2);

    ui->bolModeCombo->setProperty("FeatureWidget-combox", true);

    ui->previewBtn->setProperty("featureWidget-btn", true);
    ui->cancelBtn->setProperty("featureWidget-btn", true);
    ui->confrimBtn->setObjectName("MessageBox-btn");
    setTitle(QStringLiteral("布尔"));
    setWidget(widget);
}

void CreateBooleanWgt::UpdateView()
{
    if (!m_DisplayObject1 || !m_DisplayObject2) {
        MESSAGEBOX_INSTANCE->showMessageBox(QStringLiteral("实体对象数量不为 1"));
        return;
    }
    NctiArgumentObject argumentObject;
    argumentObject.SetDisplayObject1(m_DisplayObject1);
    argumentObject.SetDisplayObject2(m_DisplayObject2);

    int booleanModel = ui->bolModeCombo->currentIndex();
    argumentObject.SetRadius(static_cast<double>(booleanModel));

    NctiComModelTool::RunUpdateScriptModelViewFun(m_Document, &argumentObject);
}

void CreateBooleanWgt::onOk()
{
    if (!m_DisplayObject1 || !m_DisplayObject2) {
        MESSAGEBOX_INSTANCE->showMessageBox(QStringLiteral("实体对象数量不为 1"));
        return;
    }
    NctiBaseModel* pBaseModel   = m_Document->GetBaseModel();
    NctiCommandManager* pComMan = NctiCommandManager::GetCommandManager(pBaseModel);
    /*if (pComMan)
        {
            pComMan->ProcessCancelButton();
            pComMan->RequestTermination(NULL);
            pComMan->ExitCommand();

            NctiArgumentObject argumentObject;
            argumentObject.SetDisplayObject1(m_DisplayObject1);
            argumentObject.SetDisplayObject2(m_DisplayObject2);
            if (ui->bolModeCombo->currentIndex() == 0)
                pComMan->RunCommand("cmd_ncti_boolean_unit", &argumentObject);
            else if (ui->bolModeCombo->currentIndex() == 1)
                pComMan->RunCommand("cmd_ncti_boolean_cut", &argumentObject);
            else if (ui->bolModeCombo->currentIndex() == 2)
                pComMan->RunCommand("cmd_ncti_boolean_common", &argumentObject);
        }*/

    if (!pComMan)
        return;

    // 清理当前命令状态
    pComMan->ProcessCancelButton();
    pComMan->RequestTermination(NULL);
    pComMan->ExitCommand();

    // 堆分配参数对象（关键：确保子线程中有效）
    NctiArgumentObject* argumentObject = new NctiArgumentObject();
    argumentObject->SetDisplayObject1(m_DisplayObject1);
    argumentObject->SetDisplayObject2(m_DisplayObject2);

    // 确定布尔运算命令
    std::string cmd;
    switch (ui->bolModeCombo->currentIndex()) {
        case 0:
            cmd = "cmd_ncti_boolean_unit";
            break;
        case 1:
            cmd = "cmd_ncti_boolean_cut";
            break;
        case 2:
            cmd = "cmd_ncti_boolean_common";
            break;
        default:
            delete argumentObject;
            return;
    }

    // 创建子线程
    QThread* thread = new QThread(this);
    connect(thread, &QThread::started, thread, [=]() {
        if (pComMan && argumentObject) {
            pComMan->RunCommand(cmd.c_str(), argumentObject);
        }
        delete argumentObject;
        thread->quit();
    });

    connect(thread, &QThread::finished, thread, &QThread::deleteLater);
    thread->start();

    close();
}

void CreateBooleanWgt::onCanle()
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

void CreateBooleanWgt::onSelect1()
{
    std::vector<NctiDisplayObject*> selectObjects;
    NctiDocElementPubFun::GetDisplayObjectFromSelManager(m_Document, selectObjects);
    if (selectObjects.size() == 1) {
        m_DisplayObject1 = selectObjects[0];
        ui->selBodyLabel1->setText("已选取");
    }
    else {
        MESSAGEBOX_INSTANCE->showMessageBox("实体对象数量不为 1");
    }
}

void CreateBooleanWgt::onSelect2()
{
    std::vector<NctiDisplayObject*> selectObjects;
    NctiDocElementPubFun::GetDisplayObjectFromSelManager(m_Document, selectObjects);
    if (selectObjects.size() == 1) {
        m_DisplayObject2 = selectObjects[0];
        ui->selBodyLabel2->setText("已选取");
    }
    else {
        MESSAGEBOX_INSTANCE->showMessageBox(QStringLiteral("实体对象数量不为 1"));
    }
}
void CreateBooleanWgt::onPreview()
{
    UpdateView();
}
} // namespace NCTI