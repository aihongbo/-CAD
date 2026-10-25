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

#include "AddLoadingDLLWidget.h"

#include <QHBoxLayout>
#include <QGridLayout>
#include <QFileDialog>
#include <QMessageBox>

namespace NCTI {
AddLoadingDLLWidget::AddLoadingDLLWidget(QWidget* parent)
    : NctiBaseDialog(parent)
{
    initUI();
    show();
    connectSignals();
}

void AddLoadingDLLWidget::initUI()
{
    auto widget = new QFrame(this);
    widget->setObjectName("AddLoadingDLLDlg");
    setTitle("新增插件");
    selectPluginPathLab  = new QLabel("插件路径：", widget);
    selectPluginLab      = new QLabel("插件：", widget);
    selectPluginPathEdit = new QLineEdit(widget);
    selectPluginEdit     = new QLineEdit(widget);
    selectPluginBtn      = new QPushButton("浏览", widget);
    confirmBtn           = new QPushButton("确定", widget);
    cancelBtn            = new QPushButton("取消", widget);

    selectPluginPathLab->setObjectName("selectPluginPath_lab");
    selectPluginLab->setObjectName("selectPlugin_lab");
    selectPluginPathEdit->setObjectName("selectPluginPath_Edit");
    selectPluginEdit->setObjectName("selectPlugin_Edit");
    selectPluginBtn->setObjectName("selectPlugin_Btn");
    confirmBtn->setObjectName("confirm_Btn");
    cancelBtn->setObjectName("cancel_Btn");

    selectPluginPathEdit->setMinimumWidth(280);
    selectPluginEdit->setMinimumWidth(280);
    selectPluginBtn->setFixedSize(65, 25);
    confirmBtn->setFixedSize(65, 25);
    cancelBtn->setFixedSize(65, 25);

    QVBoxLayout* mainLayout = new QVBoxLayout(widget);
    QGridLayout* gridLayout = new QGridLayout();
    QHBoxLayout* btnLayout  = new QHBoxLayout();

    mainLayout->addLayout(gridLayout);
    mainLayout->addLayout(btnLayout);
    gridLayout->addWidget(selectPluginPathLab, 0, 0);
    gridLayout->addWidget(selectPluginPathEdit, 1, 0);
    gridLayout->addWidget(selectPluginLab, 2, 0);
    gridLayout->addWidget(selectPluginEdit, 3, 0);
    gridLayout->addWidget(selectPluginBtn, 3, 1);
    btnLayout->addStretch();
    btnLayout->addWidget(confirmBtn);
    btnLayout->addWidget(cancelBtn);

    setWidget(widget);
}

void AddLoadingDLLWidget::connectSignals()
{
    connect(selectPluginBtn, &QPushButton::clicked, this, &AddLoadingDLLWidget::onSelectPlugin);
    connect(confirmBtn, &QPushButton::clicked, this, &AddLoadingDLLWidget::onConfirm);
    connect(cancelBtn, &QPushButton::clicked, this, &AddLoadingDLLWidget::onCancel);
}

void AddLoadingDLLWidget::onSelectPlugin()
{
    QStringList plugins = QFileDialog::getOpenFileNames(
        this, tr("选择要添加的插件"), "", tr("Dynamic Link Library (*.dll);;All Files (*.*)"));

    if (!plugins.isEmpty()) {
        QStringList paths;
        QStringList fileNames;

        Q_FOREACH (const QString& plugin, plugins) {
            QFileInfo fileInfo(plugin);
            paths.append(fileInfo.absolutePath()); // 插件路径
            fileNames.append(fileInfo.fileName()); // 插件名
        }

        selectPluginPathEdit->setText(paths.join(";"));
        selectPluginEdit->setText(fileNames.join(";"));
    }
}

void AddLoadingDLLWidget::onConfirm()
{
    if (selectPluginPathEdit->text().isEmpty()) {
        QMessageBox::information(this, "提示", "未选择新增插件路径");
        return;
    }

    if (selectPluginEdit->text().isEmpty()) {
        QMessageBox::information(this, "提示", "未选择新增插件");
        return;
    }

    Q_EMIT selectPluginConfirmed(selectPluginPathEdit->text(), selectPluginEdit->text());
    close();
}

void AddLoadingDLLWidget::onCancel()
{
    close();
}
} // namespace NCTI