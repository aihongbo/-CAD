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

#include "CreateExtractCellWgt.h"
#include "ui_CreateExtractCellWgtContent.h"

#include <QListView>
#include "NctiMessageBox.h"

#include "NctiDocElementPubFun.h"
#include "NctiCommandManager.h"
#include "NctiArgumentObject.h"
#include "NctiDocument.h"
#include "NctiSelKeyDo.h"
#include "NctiSelectionManager.h"
#include "NctiDisplayModelBody.h"
#include "NctiSelectionDataList.h"
#include "NctiDisplayDocCustomContainer.h"

#include "NctiTopoCell.h"
#include "NctiTopoVertex.h"
#include "NctiTopoEdge.h"
#include "NctiTopoFace.h"

namespace NCTI {

CreateExtractCellWgt::CreateExtractCellWgt(NctiDocument* i_pDocument, QWidget* parent)
    : NctiBaseDialog(parent)
    , ui(new Ui::CreateExtractCellWgtContent)
    , m_Document(i_pDocument)
{
    initUI();

    connect(ui->extractBtn, &QPushButton::clicked, this, &CreateExtractCellWgt::onSelected);
    connect(ui->faceRadioBtn, &QRadioButton::toggled, this, &CreateExtractCellWgt::onRadioButtonToggled);
    connect(ui->edgeRadioBtn, &QRadioButton::toggled, this, &CreateExtractCellWgt::onRadioButtonToggled);
    connect(ui->verterxRadioBtn, &QRadioButton::toggled, this, &CreateExtractCellWgt::onRadioButtonToggled);

    connect(ui->cancelBtn, &QPushButton::clicked, this, &CreateExtractCellWgt::onCanle);
    connect(ui->confrimBtn, &QPushButton::clicked, this, &CreateExtractCellWgt::onExtract);
}

CreateExtractCellWgt::~CreateExtractCellWgt()
{
    NCTI_DELETE ui;
}

void CreateExtractCellWgt::show()
{
    QWidget::show();
}

void CreateExtractCellWgt::initUI()
{
    auto widget = new QWidget(this);
    widget->setObjectName("featureWidget-widget");
    ui->setupUi(widget);

    widget->setFixedSize(313, 119);
    ui->extractBtn->setText(QStringLiteral("选取"));
    ui->extractBtn->setProperty("featureWidget-btn", true);

    ui->elementLabel->setText(QStringLiteral("选择面的ID:"));
    ui->elementLabel->setProperty("featureWidget-lab", true);
    ui->faceRadioBtn->setProperty("FeatureWidget-RadioBtn", true);
    ui->edgeRadioBtn->setProperty("FeatureWidget-RadioBtn", true);
    ui->verterxRadioBtn->setProperty("FeatureWidget-RadioBtn", true);

    QListView* listView = new QListView(ui->idCombox);
    listView->setAlternatingRowColors(true);
    ui->idCombox->setView(listView);
    ui->idCombox->setFocusPolicy(Qt::NoFocus);
    ui->idCombox->setProperty("FeatureWidget-combox", true);

    setTitle(QStringLiteral("抽取要素"));
    setWidget(widget);
}

NCTI::CreateExtractCellWgt::ExtType CreateExtractCellWgt::getCurrSelType()
{
    ExtType extType{ExtType::Unknow};
    if (ui->verterxRadioBtn->isChecked()) {
        extType = ExtType::Point;
    }
    else if (ui->edgeRadioBtn->isChecked()) {
        extType = ExtType::Edge;
    }
    else if (ui->faceRadioBtn->isChecked()) {
        extType = ExtType::Face;
    }
    return extType;
}

void CreateExtractCellWgt::getExtTypeId(std::vector<Ncti_Long>& cellIds, ExtType type)
{
    NctiSelectionManager* pSelMan = NctiSelectionManager::GetSelectionManager(m_Document->GetBaseModel());
    NctiSelectionDataList listSelected;
    pSelMan->GetSelected(listSelected, NctiSelKeyDo::ID);
    NctiSelKeyDo* pSelKeyDo = nullptr;
    while ((pSelKeyDo = (NctiSelKeyDo*)listSelected.Next()) != nullptr) {
        NctiDisplayObject* pDo = pSelKeyDo->GetDoOriginal();
        if (pDo->IsTypeName(NctiDisplayModelBody::ID) && pSelKeyDo->GetKey()) {
            NctiDisplayModelBody* pModelBody = (NctiDisplayModelBody*)pDo;

            NCTI_MODEL_TAG cell = nullptr;
            pModelBody->FindModelTagByKey(pSelKeyDo->GetKey(), cell);
            NctiDisplayDocCustomContainer* pDocCus = (NctiDisplayDocCustomContainer*)pModelBody->GetDocContainer();

            Ncti_Long id = -1;
            pDocCus->get_persistent_tag(pModelBody, cell, id);
            NCTI_MODEL_TAG pGECell = nullptr;
            pDocCus->get_gecell(pModelBody->GetNctiBody(), cell, pGECell);

            if (!pGECell) {
                return;
            }

            NctiTopoCell* pTopoGECell = (NctiTopoCell*)pGECell;
            if (pTopoGECell
                && ((type == ExtType::Point && pTopoGECell->IsTypeName(NctiTopoVertex::ID))
                    || (type == ExtType::Edge && pTopoGECell->IsTypeName(NctiTopoEdge::ID))
                    || (type == ExtType::Face && pTopoGECell->IsTypeName(NctiTopoFace::ID)))) {
                cellIds.push_back(id);
            }
        }
    }
}

void CreateExtractCellWgt::onExtract()
{
    if (ui->idCombox->count() < 1) {
        MESSAGEBOX_INSTANCE->showMessageBox(QStringLiteral("输入参数错误"));
        return;
    }

    NctiBaseModel* pBaseModel   = m_Document->GetBaseModel();
    NctiCommandManager* pComMan = NctiCommandManager::GetCommandManager(pBaseModel);
    if (pComMan) {
        std::vector<Ncti_Long> vecCell;
        NctiArgumentObject argumentObject;
        vecCell.emplace_back(ui->idCombox->currentText().toInt());
        argumentObject.SetCellIDVec(vecCell);
        argumentObject.SetDisplayObjectVec(m_SelObjVec);
        EnumNctiResult result = pComMan->RunCommand("cmd_ncti_extract_cell", &argumentObject);
    }
    close();
}

void CreateExtractCellWgt::onSelected()
{
    ui->idCombox->clear();
    std::vector<Ncti_Long> cellIds;
    getExtTypeId(cellIds, getCurrSelType());

    for (int i = 0, iSize = cellIds.size(); i < iSize; ++i) {
        ui->idCombox->addItem(QString::number(cellIds[i]), i);
    }
    NctiDocElementPubFun::GetDisplayObjectFromSelManager(m_Document, m_SelObjVec);
}

void CreateExtractCellWgt::onCanle()
{
    close();
}

void CreateExtractCellWgt::onRadioButtonToggled()
{
    ui->idCombox->clear();

    if (ui->verterxRadioBtn->isChecked()) {
        ui->elementLabel->setText(QStringLiteral("选择点的ID:"));
    }
    else if (ui->edgeRadioBtn->isChecked()) {
        ui->elementLabel->setText(QStringLiteral("选择边的ID:"));
    }
    else if (ui->faceRadioBtn->isChecked()) {
        ui->elementLabel->setText(QStringLiteral("选择面的ID:"));
    }
}

} // namespace NCTI