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

#include "RemoveFeatureWgt.h"
#include "ui_RemoveFeatureWgtContent.h"
#include "NctiDocElementPubFun.h"
#include "NctiCommandManager.h"
#include "NctiArgumentObject.h"
#include "NctiDocument.h"

namespace NCTI {

RemoveFeatureWgt::RemoveFeatureWgt(NctiDocument* i_pDocument, int mode, int removeFeature, QWidget* parent)
    : NctiBaseDialog(parent)
    , ui(new Ui::RemoveFeatureWgtContent)
    , m_iRemoveFeature(removeFeature)
    , m_selectModeRoller(new SelectModeRoller(i_pDocument, mode, this))
    , m_doc(i_pDocument)
{
    //setAttribute(Qt::WA_DeleteOnClose);
    initUI();

    connect(ui->SelFaceBtn, &QPushButton::clicked, this, [this] { GetSelection(); });
    connect(ui->confrimBtn, &QPushButton::clicked, this, &RemoveFeatureWgt::onOK);
    connect(ui->cancelBtn, &QPushButton::clicked, this, &RemoveFeatureWgt::onCanle);
}

RemoveFeatureWgt::~RemoveFeatureWgt()
{
    NCTI_DELETE ui;
    NCTI_DELETE m_selectModeRoller;
}

void RemoveFeatureWgt::show()
{
    QWidget::show();
    m_selectModeRoller->initMode();
}

void RemoveFeatureWgt::initUI()
{
    auto widget = new QWidget(this);
    widget->setObjectName("featureWidget-widget");
    ui->setupUi(widget);

    ui->SelFaceBtn->setText(QStringLiteral("选择面"));
    ui->SelFaceBtn->setProperty("featureWidget-btn", true);

    ui->SelFaceLabel->setText(QStringLiteral("已选择<font color = #1771f8>0</font>个面"));
    ui->SelFaceLabel->setProperty("featureWidget-lab", true);
    ui->SelFaceLabel->setGeometry(240, 67, 75, 12);

    m_iRemoveFeature == 0   ? setTitle(QStringLiteral("移除特征"))
    : m_iRemoveFeature == 1 ? setTitle(QStringLiteral("移除面"))
                            : setTitle(QStringLiteral("分离面"));
    setWidget(widget);
}

void RemoveFeatureWgt::onOK()
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
            if (disObjs.size() == 1) {
                argumentObject.SetDisplayObject1(disObjs[0]);
                m_iRemoveFeature == 0   ? pComMan->RunCommand("cmd_ncti_remove_features", &argumentObject)
                : m_iRemoveFeature == 1 ? pComMan->RunCommand("cmd_ncti_remove_faces", &argumentObject)
                                        : pComMan->RunCommand("cmd_ncti_split_faces", &argumentObject);
            }
        }
    }
    close();
    NctiDocElementPubFun::CancelSelection(m_doc);
    m_selectModeRoller->restoreMode();
}

void RemoveFeatureWgt::onCanle()
{
    close();
    NctiDocElementPubFun::CancelSelection(m_doc);
    m_selectModeRoller->restoreMode();
}

void RemoveFeatureWgt::GetSelection()
{
    if (m_doc) {
        NctiDocElementPubFun::GetDisplayObjectFromSelManager(m_doc, m_displayobj, m_cells);
        Ncti_Integer nCount = m_displayobj.size();
        /*QString strSel = QStringLiteral("已选择%1个面").arg(nCount);
			ui->SelFaceLabel->setText(strSel);*/
        nCount == 0
            ? ui->SelFaceLabel->setText(QStringLiteral("已选择<font color = #ff0000>0</font>个面"))
            : ui->SelFaceLabel->setText(QStringLiteral("已选择<font color = #00ff00>%1</font>个面").arg(nCount));
    }
}

} // namespace NCTI