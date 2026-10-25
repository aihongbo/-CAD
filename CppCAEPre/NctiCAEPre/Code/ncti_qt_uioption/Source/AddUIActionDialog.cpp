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

#include "AddUIActionDialog.h"
#include "ui_AddUIActionDialog.h"

#include <QDebug>
#include <QPushButton>
#include <QPainter>
#include <QFileDialog>
#include <QToolTip>

namespace NCTI {

AddUIActionDialog::AddUIActionDialog(QWidget* parent, const QString& title, const QString& actionName)
    : NctiBaseDialog(parent, TitleBarHeight{42})
    , ui(new Ui::AddUIActionDialog)
    , mOriginActionName(actionName)
{
    setupUi();
    setTitle(title);

    if (!mOriginActionName.isEmpty()) {
        ui->actionEdit->setText(mOriginActionName);
        mEditMode = true;
    }

    connect(ui->noSaveBtn, &QPushButton::clicked, this, &AddUIActionDialog::onNoSave);
    connect(ui->saveBtn, &QPushButton::clicked, this, &AddUIActionDialog::onSave);
}

AddUIActionDialog::~AddUIActionDialog()
{
    delete ui;
}

void AddUIActionDialog::setupUi()
{
    auto widget = new QWidget(this);
    ui->setupUi(widget);

    ui->logo->setText(QStringLiteral("图标路径："));
    ui->logoEdit->setPlaceholderText(QStringLiteral("请输入图标路径"));

    ui->actionName->setText(QStringLiteral("动作名称："));
    ui->actionEdit->setPlaceholderText(QStringLiteral("请输入动作名称"));

    ui->funcName->setText(QStringLiteral("槽函数名称："));
    ui->funcEdit->setPlaceholderText(QStringLiteral("请输入槽函数名称"));

    ui->pyscript->setText(QStringLiteral("python脚本："));
    ui->pyscriptEdit->setPlaceholderText(QStringLiteral("请输入脚本内容"));

    ui->noSaveBtn->setText(QStringLiteral("取消"));
    ui->saveBtn->setText(QStringLiteral("保存"));

    setWidget(widget);
}

int AddUIActionDialog::GetStatus() const
{
    return (mSaveStatus == SaveStatus::Cancel) ? 0 : 1;
}

UIActionData AddUIActionDialog::getData() const
{
    return mUIActionData;
}

void AddUIActionDialog::setData(const UIActionData& data)
{
    ui->logoEdit->setText(data.iconPath);
    ui->actionEdit->setText(data.actionName);
    ui->funcEdit->setText(data.slotName);
    ui->pyscriptEdit->setText(data.pyScript);
    mUIActionData = data;
}

void AddUIActionDialog::onNoSave()
{
    mSaveStatus = SaveStatus::Cancel;
    close();
}

void AddUIActionDialog::onSave()
{
    if (!checkEditEmpty(ui->actionEdit, QStringLiteral("名称不能为空！"))) { return; }
    if (!checkEditEmpty(ui->logoEdit, QStringLiteral("图标路径不能为空！"))) { return; }

    mSaveStatus              = SaveStatus::Save;
    mUIActionData.actionName = ui->actionEdit->text();
    mUIActionData.iconPath   = ui->logoEdit->text();
    mUIActionData.slotName   = ui->funcEdit->text();
    mUIActionData.pyScript   = ui->pyscriptEdit->toPlainText();
    if (mUIActionData.pyScript.isEmpty()) {
        if (!checkEditEmpty(ui->funcEdit, QStringLiteral("函数名称不能为空！"))) { return; }
    }
    close();
}

bool AddUIActionDialog::checkEditEmpty(QLineEdit* edit, const QString& tip)
{
    QString text = edit->text();
    if (text.isEmpty()) {
        QToolTip::showText(edit->mapToGlobal(QPoint(0, 0)), tip);
        return false;
    }
    return true;
}
} // namespace NCTI
