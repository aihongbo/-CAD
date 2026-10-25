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

#include "MeshQuickSelect.h"
#include "ui_MeshQuickSelect.h"

#include <QRegularExpressionValidator>

#include "NctiQtScriptExecutor.h"
#include "SelectModeRoller.h"

#include "NctiToolMeshGridDo.h"
#include "NctiBaseView.h"
#include "NctiViewerRenderer.h"
#include "NctiDocument.h"
#include "NctiMeshManager.h"
#include "NctiBaseModel.h"

namespace NCTI {

    MeshQuickSelect::~MeshQuickSelect()
    {
        NctiToolMeshGridDo::SetFilterType(getInType());
        NctiToolMeshGridDo::SetFilterAngle(-1);
        delete ui;
    }

    MeshQuickSelect::MeshQuickSelect(NctiDocument* i_pDocument, NctiQtScriptExecutor* executor, QWidget* parent) 
        : NctiBaseDialog(parent)
        , ui(new Ui::MeshQuickSelect)
        , m_document(i_pDocument)
        , m_executor(executor)
        , m_roller(new SelectModeRoller(i_pDocument, SelectModeRoller::SelectMode::All, this))
    {
        setup();
    }

    double MeshQuickSelect::getAngle() const
    {
        return ui->lineEdit_angle->text().toDouble();
    }

    NctiSelectType MeshQuickSelect::getOutType() const
    {
        return (NctiSelectType)ui->comboBox->currentData().toInt();
    }

    NCTI::NctiSelectType MeshQuickSelect::getInType() const
    {
        NctiSelectType stp = ELEM_Cell;
        if (m_document && m_document->GetBaseModel())
        {
            auto view = m_document->GetBaseModel()->GetActiveBaseView();
            if (view->GetRenderCanvas())
                stp = view->GetRenderCanvas()->GetSelectElementType();
            if (stp == ELEM_Entity)
                stp = ELEM_Cell;
        }
        return stp;
    }

    void MeshQuickSelect::setup()
    {
        auto widget = new QWidget(this);
        ui->setupUi(widget);
        setTitle(QStringLiteral("快速选择"));
        setWidget(widget);

        ui->lineEdit_angle->setValidator(new QRegularExpressionValidator(
            QRegularExpression("^(([0-9]+\\.[0-9]*[1-9][0-9]*)|([0-9]*[1-9][0-9]*\\.[0-9]+)|([0-9]*[1-9][0-9]*))$")));
        ui->comboBox->addItem(QStringLiteral("节点"), ELEM_Vertex);
        ui->comboBox->addItem(QStringLiteral("单元"), ELEM_Cell);
        ui->comboBox->addItem(QStringLiteral("单元面"), ELEM_Face);
        ui->comboBox->addItem(QStringLiteral("单元边"), ELEM_Edge);

        connect(ui->lineEdit_angle, &QLineEdit::textChanged, this, [this](const QString&) {
            NctiToolMeshGridDo::SetFilterAngle(getAngle());
            });
        connect(ui->comboBox, &QComboBox::currentTextChanged, this, [this](const QString&) {
            NctiToolMeshGridDo::SetFilterType(getOutType());
            });

        ui->comboBox->setCurrentIndex(ui->comboBox->findData(getInType()));
        ui->lineEdit_angle->setText("0.6");
    }

}




