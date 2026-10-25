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

#include "SaveDocDialog.h"
#include "ui_SaveDocDialogContent.h"

#include <QPushButton>
#include <QFileDialog>

namespace NCTI {
    SaveDocDialog::SaveDocDialog(QWidget* parent, const QString& docName, ShowType showType)
        : PopupBaseDialog(parent, false, 42)
        , ui(new Ui::SaveDocDialogContent)
        , m_docName(docName)
        , m_showType(showType)
    {
        setupUi();

        if (m_showType == ShowType::NoDoc) {
            ui->noSaveBtn->setVisible(false);
            ui->noSaveAllBtn->setVisible(false);
            ui->saveBtn->setText(QStringLiteral("确定"));
        }
        else {
            ui->noSaveAllBtn->setVisible(m_showType == ShowType::MultiDoc);
        }

        connect(ui->noSaveAllBtn, &QPushButton::clicked, this, &SaveDocDialog::onNoSaveAll);
        connect(ui->noSaveBtn, &QPushButton::clicked, this, &SaveDocDialog::onNoSave);
        connect(ui->saveBtn, &QPushButton::clicked, this, &SaveDocDialog::onSave);
    }

    SaveDocDialog::~SaveDocDialog()
    {
        delete ui;
    }

    void SaveDocDialog::setupUi()
    {
        auto widget = new QWidget(this);
        ui->setupUi(widget);

        ui->verticalLayout->setContentsMargins(0, 0, 0, 0);
        ui->verticalLayout->setSpacing(0);

        ui->hBoxTxt->setContentsMargins(0, 0, 0, 0);
        ui->hBoxBtn->setContentsMargins(0, 0, 0, 0);

        QPixmap pixmap(":/dialog/warning.svg");
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
        ui->noSaveBtn->setText(QStringLiteral("不保存"));
        ui->saveBtn->setText(QStringLiteral("保存"));
        ui->textLabel->setText(m_docName);
        ui->textLabel->setWordWrap(true);
        setTitle(QStringLiteral("提示"));

        // 设置标题栏的样式
        getTitleBar()->setStyleSheet(
            "border-top-left-radius: 8px;"
            "border-top-right-radius: 8px;"
            "border: 1px solid #fbfcfe;"
            "background: #fbfcfe;"
        );

        // 设置标题样式
        getTitleLabel()->setStyleSheet(
            "color: #52555A;"
            "font-family: 'HarmonyOS Sans SC';"
            "font-size: 16px;"
            "margin-left: 16px;"
        );

        setWidget(widget);
    }

    void SaveDocDialog::onNoSaveAll()
    {
        m_saveStatus = SaveStatus::NoSaveAll;
        close();
    }

    void SaveDocDialog::onNoSave()
    {
        m_saveStatus = SaveStatus::NoSave;
        close();
    }

    void SaveDocDialog::onSave()
    {
        m_saveStatus = SaveStatus::Save;
        if (m_showType == ShowType::NoDoc) {
            close();
            return;
        }

        if (!m_savePath.isEmpty()) {
            close();
            return;
        }

        QString filePath = QFileDialog::getSaveFileName(this
            , QStringLiteral("保存")
            , "/"
            , tr("Save File(*.ncti)")
        );

        if (filePath.isEmpty()) {
            return;
        }

        m_savePath = filePath;
        close();
    }

    SaveStatus SaveDocDialog::GetSaveStatus()
    {
        return m_saveStatus;
    }

    void SaveDocDialog::SetSavePath(const QString& path)
    {
        m_savePath = path;
    }

    QString SaveDocDialog::GetSavePath()
    {
        return m_savePath;
    }
}

