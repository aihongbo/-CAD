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

#include "NctiMessageDialog.h"
#include "ui_MessageDialog.h"

#include <QPushButton>
#include <QFileDialog>
#include <QTextStream>
#include <QFile>

enum CloseCode {
    Cancel = 0,
    NoSaveAll,
    NoSave,
    Save
};

namespace NCTI {
    NctiMessageDialog::NctiMessageDialog(QWidget* parent, const QString& docName, bool bMultiDoc)
        : NctiBaseDialog(parent, TitleBarHeight{42})
        , ui(new Ui::MessageDialog)
        , m_docName(docName)
    {
        // 读取并设置QSS样式表
        QFile file(":/style/NctiMessageDialog.qss");
        if (file.open(QFile::ReadOnly | QFile::Text)) {
            QTextStream stream(&file);
            QString styleSheet = stream.readAll();
            setBaseStyleSheet(styleSheet);
            file.close();
        }

        setupUi();

        ui->noSaveAllBtn->setVisible(bMultiDoc);
        
        if (bMultiDoc) {
            connect(ui->noSaveAllBtn, &QPushButton::clicked, this, &NctiMessageDialog::onNoSaveAll);
        }
        connect(ui->noSaveBtn, &QPushButton::clicked, this, &NctiMessageDialog::onNoSave);
        connect(ui->saveBtn, &QPushButton::clicked, this, &NctiMessageDialog::onSave);
    }

    NctiMessageDialog::~NctiMessageDialog()
    {
        delete ui;
    }

    void NctiMessageDialog::setupUi()
    {
        auto widget = new QWidget(this);
        ui->setupUi(widget);

        ui->verticalLayout->setContentsMargins(0, 0, 0, 0);
        ui->verticalLayout->setSpacing(0);

        ui->hBoxTxt->setContentsMargins(0, 0, 0, 0);
        ui->hBoxBtn->setContentsMargins(0, 0, 0, 0);

        QPixmap pixmap(":/images/common/warning.svg");
        ui->iconLabel->setPixmap(pixmap);
        ui->iconLabel->setFixedSize(56, 56);

        ui->frameTxt->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        ui->frameBtn->setFixedHeight(60);
        ui->hBoxBtn->setSpacing(8);
        ui->hBoxBtn->setAlignment(Qt::AlignVCenter);
        ui->noSaveAllBtn->setFixedSize(118, 36);
        ui->noSaveBtn->setFixedSize(90, 36);
        ui->saveBtn->setFixedSize(76, 36);
        
        ui->noSaveAllBtn->setText(QStringLiteral("全部不保存"));
        ui->noSaveBtn->setText(QStringLiteral("取消"));
        ui->saveBtn->setText(QStringLiteral("确定"));
        ui->textLabel->setText(m_docName);
        
        setTitle(QStringLiteral("提示"));

        setWidget(widget);
    }

    int NctiMessageDialog::GetCloseCode()
    {
        return m_closeCode;
    }

    void NctiMessageDialog::onNoSaveAll()
    {
        m_closeCode = CloseCode::NoSaveAll;
        close();
    }

    void NctiMessageDialog::onNoSave()
    {
        m_closeCode = CloseCode::NoSave;
        close();
    }

    void NctiMessageDialog::onSave()
    {
        m_closeCode = CloseCode::Save;
        close();
    }
}

