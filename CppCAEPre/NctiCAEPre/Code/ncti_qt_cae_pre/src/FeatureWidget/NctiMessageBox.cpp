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

#include "NctiMessageBox.h"

#include "SAFramelessHelper.h"

#include <QVBoxLayout>
#include <QVariant>
#include <QPixmap>

namespace NCTI {

NctiMessageBox* NCTI::NctiMessageBox::Instance()
{
    static NctiMessageBox messagebox;
    return &messagebox;
}

NctiMessageBox::NctiMessageBox(QWidget* parent)
    : QDialog(parent)
{
    //setWindowModality(Qt::ApplicationModal);//设置模态窗口
    setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint);

    //设置背景透明
    this->setAttribute(Qt::WA_TranslucentBackground);

    initUI();
    connect(m_pCancelBtn, &QPushButton::clicked, this, &NctiMessageBox::onClose);
    connect(m_pConfrimBtn, &QPushButton::clicked, this, &NctiMessageBox::onClose);
}

NctiMessageBox::~NctiMessageBox()
{
}

void NctiMessageBox::showMessageBox(const QString& text, const QString& title, bool bCanelBtnVisible)
{
    m_pTitleLabel->setText(title);
    m_pTextLabel->setText(text);

    if (!bCanelBtnVisible) {
        m_pCancelBtn->setVisible(false);
    }
    else if (m_pBtnHBoxLayout) {
        m_pCancelBtn->setVisible(true);
        m_pBtnHBoxLayout->setContentsMargins(72, 0, 12, 8);
    }
    exec();
}

void NctiMessageBox::initUI()
{
    auto frame = new QFrame(this);
    frame->setContentsMargins(QMargins{});
    frame->setObjectName("MessageBox-frame");
    frame->setFixedWidth(300);
    
    QVBoxLayout* vBoxLayout = new QVBoxLayout(frame);
    vBoxLayout->setContentsMargins(QMargins{});
    vBoxLayout->setSpacing(4);

    // 创建标题栏
    auto titleBar = new QWidget(frame);
    titleBar->setObjectName(QStringLiteral("MessageBox-title-bar"));
    titleBar->setFixedSize(300, 45);

    // 设置标题栏布局
    auto titleBarLayout = new QHBoxLayout(titleBar);

    m_pTitleLabel = new QLabel(titleBar);
    m_pTitleLabel->setObjectName(QStringLiteral("MessageBox-dialog-title"));

    QPushButton* closeButton = new QPushButton(titleBar);
    closeButton->setObjectName(QStringLiteral("MessageBox-close-button"));
    closeButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
    connect(closeButton, &QAbstractButton::clicked, this, &QDialog::reject);

    titleBarLayout->addWidget(m_pTitleLabel);
    titleBarLayout->addStretch();
    titleBarLayout->addWidget(closeButton);

    vBoxLayout->addWidget(titleBar);

    QWidget* contentWgt = new QWidget(frame);
    contentWgt->setObjectName("MessageBox-contentWgt");
    QHBoxLayout* contentHBoxLayout = new QHBoxLayout(contentWgt);
    contentHBoxLayout->setContentsMargins(18, 2, 12, 18);

    QLabel* iconLabel = new QLabel(contentWgt);
    iconLabel->setFixedSize(52, 52);

    QPixmap pixmap(":/Common/pic-warn.svg");
    iconLabel->setPixmap(pixmap);
    contentHBoxLayout->addWidget(iconLabel);

    m_pTextLabel = new QLabel(contentWgt);
    m_pTextLabel->setObjectName("MessageBox-selModeLab");
    contentHBoxLayout->addWidget(m_pTextLabel);
    vBoxLayout->addWidget(contentWgt);

    m_pBtnHBoxLayout = new QHBoxLayout();
    m_pBtnHBoxLayout->setContentsMargins(152, 0, 12, 2);

    m_pCancelBtn = new QPushButton(QStringLiteral("取消"), frame);
    m_pCancelBtn->resize(76, 32);
    m_pCancelBtn->setObjectName("MessageBox-btn");
    m_pBtnHBoxLayout->addWidget(m_pCancelBtn);

    m_pConfrimBtn = new QPushButton(QStringLiteral("确定"), frame);
    m_pCancelBtn->resize(76, 32);
    m_pConfrimBtn->setObjectName("MessageBox-btn");
    m_pBtnHBoxLayout->addWidget(m_pConfrimBtn);
    vBoxLayout->addLayout(m_pBtnHBoxLayout);

    // 设置对话框的主布局并添加QFrame
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(frame);
    this->setLayout(mainLayout);

    mFramelessHelper = new SAFramelessHelper(this);
    mFramelessHelper->setTitleHeight(45);
    mFramelessHelper->setRubberBandOnResize(false);
}

void NctiMessageBox::onClose()
{
    close();
}
} // namespace NCTI