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

#include "UIOptionDialog.h"
#include "UIOptionTree.h"
#include "UIOptionItemModel.h"

#include <QSplitter>
#include <QVBoxLayout>
#include <QLabel>
#include <QToolButton>
#include <QPushButton>
#include <QInputDialog>
#include <QMessageBox>
#include <QFileDialog>

namespace NCTI {
UIOptionDialog::UIOptionDialog(QWidget* parent)
    : QDialog(parent)
{
    setupUi();
    initConnections();
    loadSystemTreeData();
    loadCustomTreeData();
}

void UIOptionDialog::setupUi()
{
    setWindowTitle("UI配置对话框");
    setMinimumSize(800, 600);

    mSplitter = new QSplitter(Qt::Horizontal, this);
    mSplitter->addWidget(setupLeftWidget(mSplitter));
    mSplitter->addWidget(setupRightWidget(mSplitter));
    mSplitter->setSizes({400, 400});

    // 设置主布局
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(mSplitter);
}

QWidget* UIOptionDialog::setupLeftWidget(QSplitter* splitter)
{
    // 左侧系统树区域
    QWidget* leftWidget  = new QWidget(splitter);
    QVBoxLayout* vLayout = new QVBoxLayout(leftWidget);
    
    mSystemTitle         = new QLabel(leftWidget);
    mSystemTitle->setText("系统配置");
    vLayout->addWidget(mSystemTitle);

    //mSearchEdit = new QLineEdit(leftWidget);
    //mSearchEdit->setPlaceholderText("请输入搜索内容");
    //vLayout->addWidget(mSearchEdit);
    
    mSystemTree = new UIOptionTree(leftWidget, true);
    vLayout->addWidget(mSystemTree);
    return leftWidget;
}

QWidget* UIOptionDialog::setupRightWidget(QSplitter* splitter)
{
    // 右侧自定义树区域
    QWidget* rightWidget = new QWidget(splitter);
    QVBoxLayout* vLayout = new QVBoxLayout(rightWidget);

    mCustomTitle = new QLabel(rightWidget);
    mCustomTitle->setText("自定义配置");

    QHBoxLayout* logoHLayout = new QHBoxLayout();
    mAppLogo                 = new QLabel(rightWidget);
    mAppLogo->setText("图标：");

    mAppLogoBtn = new QToolButton(rightWidget);
    mAppLogoBtn->setToolButtonStyle(Qt::ToolButtonIconOnly);
    mAppLogoBtn->setIconSize(QSize(24, 24));
    mAppLogoPath = UIOption::GetInst().GetLogo();
    mAppLogoBtn->setIcon(QIcon(mAppLogoPath));

    logoHLayout->addWidget(mAppLogo);
    logoHLayout->addWidget(mAppLogoBtn);
    logoHLayout->addStretch();

    QHBoxLayout* titleHLayout = new QHBoxLayout();
    mAppTitle                 = new QLabel(rightWidget);
    mAppTitle->setText("标题：");
    mAppTitleEdit = new QLineEdit(rightWidget);
    mAppTitleEdit->setPlaceholderText("请输入标题");
    mAppTitleEdit->setText(UIOption::GetInst().GetTitle());
    titleHLayout->addWidget(mAppTitle);
    titleHLayout->addWidget(mAppTitleEdit);

    mCustomTree = new UIOptionTree(rightWidget, false);

    mRestoreBtn = new QPushButton(rightWidget);
    mRestoreBtn->setText("还原配置");
    mUpdateBtn = new QPushButton(rightWidget);
    mUpdateBtn->setText("更新配置");
    QHBoxLayout* buttonHLayout = new QHBoxLayout();
    buttonHLayout->addWidget(mRestoreBtn);
    buttonHLayout->addWidget(mUpdateBtn);
    buttonHLayout->setSpacing(10);

    vLayout->addWidget(mCustomTitle);
    vLayout->addLayout(logoHLayout);
    vLayout->addLayout(titleHLayout);
    vLayout->addWidget(mCustomTree);
    vLayout->addLayout(buttonHLayout);
    return rightWidget;
}

void UIOptionDialog::initConnections()
{
    connect(mRestoreBtn, &QPushButton::clicked, this, &UIOptionDialog::onRestore);
    connect(mUpdateBtn, &QPushButton::clicked, this, &UIOptionDialog::onUpdate);
    connect(mAppLogoBtn, &QPushButton::clicked, this, &UIOptionDialog::onChangeLogo);
}

void UIOptionDialog::loadSystemTreeData()
{
    mSystemTree->loadLocalModel();
    mSystemTree->show();
}

void UIOptionDialog::loadCustomTreeData()
{
    mCustomTree->loadLocalModel();
    mCustomTree->show();
}

void UIOptionDialog::onRestore()
{
    if (mCustomTree) { mCustomTree->loadLocalModel(true); }
}

void UIOptionDialog::onUpdate()
{
    if (!mCustomTree || !mCustomTree->getModel()) {
        QMessageBox::warning(this, "错误", "更新失败");
        return;
    }

    QString appTitle = mAppTitleEdit->text().trimmed();
    mCustomTree->updateLocalModel(mAppLogoPath, appTitle);
    close();
}

void UIOptionDialog::onChangeLogo()
{
    QString logoPath = QFileDialog::getOpenFileName(
        this, "选择图标文件", QDir::homePath(), "图片文件 (*.png *.jpg *.jpeg *.bmp *.gif)");

    if (!logoPath.isEmpty()) {
        QIcon icon(logoPath);
        mAppLogoBtn->setIcon(icon);
        mAppLogoPath = logoPath;
    }
}
} // namespace NCTI
