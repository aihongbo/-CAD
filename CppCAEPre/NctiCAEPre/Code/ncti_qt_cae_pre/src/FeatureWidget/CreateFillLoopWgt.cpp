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

#include "CreateFillLoopWgt.h"
#include "ui_RemoveFeatureWgtContent.h"

#include "NctiDocElementPubFun.h"
#include "NctiCommandManager.h"
#include "NctiArgumentObject.h"
#include "NctiDocument.h"

namespace NCTI {

CreateFillLoopWgt::CreateFillLoopWgt(NctiDocument* i_pDocument, QWidget* parent)
    : NctiBaseDialog(parent)
    , ui(new Ui::RemoveFeatureWgtContent)
    , m_selectModeRoller(new SelectModeRoller(i_pDocument, 0, this))
    , m_doc(i_pDocument)
{
    initUI();

    connect(ui->SelFaceBtn, &QPushButton::clicked, this, [this] { GetSelection(); });
    connect(ui->confrimBtn, &QPushButton::clicked, this, &CreateFillLoopWgt::onOK);
    connect(ui->cancelBtn, &QPushButton::clicked, this, &CreateFillLoopWgt::onCanle);
}

CreateFillLoopWgt::~CreateFillLoopWgt()
{
    NCTI_DELETE ui;
    NCTI_DELETE m_selectModeRoller;
}

void CreateFillLoopWgt::show()
{
    QWidget::show();
    m_selectModeRoller->initMode();
}

void CreateFillLoopWgt::initUI()
{
    auto widget = new QWidget(this);
    widget->setObjectName("featureWidget-widget");
    ui->setupUi(widget);

    ui->SelFaceBtn->setText(QStringLiteral("选择边"));
    ui->SelFaceBtn->setProperty("featureWidget-btn", true);

    ui->SelFaceLabel->setText(QStringLiteral("已选择<font color = #1771f8>0</font>条边"));
    ui->SelFaceLabel->setProperty("featureWidget-lab", true);
    ui->SelFaceLabel->setGeometry(240, 67, 75, 12);

    setTitle(QStringLiteral("填充内环"));
    setWidget(widget);
}

void CreateFillLoopWgt::onOK()
{
    if (m_doc && m_displayobj.size() > 0) {
        NctiBaseModel* pBaseModel   = m_doc->GetBaseModel();
        NctiCommandManager* pComMan = NctiCommandManager::GetCommandManager(pBaseModel);
        if (pComMan) {
            NctiArgumentObject argumentObject;
            argumentObject.SetCellVec(m_cells);
            std::vector<NctiDisplayObject*> disObjs;
            for (int i = 0; i < m_displayobj.size(); i++) {
                if (std::find(disObjs.begin(), disObjs.end(), m_displayobj[i]) != disObjs.end())
                    continue;
                disObjs.push_back(m_displayobj[i]);
            }
            if (disObjs.size() != 0) {
                argumentObject.SetDisplayObjectVec(disObjs);
                EnumNctiResult result = pComMan->RunCommand("cmd_ncti_fill_loop", &argumentObject);
            }
        }
    }
    close();
    NctiDocElementPubFun::CancelSelection(m_doc);
    m_selectModeRoller->restoreMode();
}

void CreateFillLoopWgt::onCanle()
{
    close();
    NctiDocElementPubFun::CancelSelection(m_doc);
    m_selectModeRoller->restoreMode();
}

void CreateFillLoopWgt::GetSelection()
{
    if (m_doc) {
        NctiDocElementPubFun::GetDisplayObjectFromSelManager(m_doc, m_displayobj, m_cells);
        Ncti_Integer nCount = m_displayobj.size();
        /*QString strSel = QStringLiteral("已选择%1个面").arg(nCount);
			ui->SelFaceLabel->setText(strSel);*/
        nCount == 0
            ? ui->SelFaceLabel->setText(QStringLiteral("已选择<font color = #ff0000>0</font>条边"))
            : ui->SelFaceLabel->setText(QStringLiteral("已选择<font color = #00ff00>%1</font>条边").arg(nCount));
    }
}

} // namespace NCTI