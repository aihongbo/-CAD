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

#include "NctiBaseDialog.h"
#include "NctiFramelessManager.h"

#include <memory>
#include <QWidget>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QDebug>
#include <QFile>

namespace NCTI {

class NctiBaseDialog::PrivateData
{
public:
    PrivateData(NctiBaseDialog* parent)
        : q_ptr(parent)
    {
    }
    void setupUi();
    void setTitleHeight(int height);
    void setTitleContentsMargins(const QMargins& margins);
    QWidget* createTitleBar();

private:
    friend class NctiBaseDialog;
    NctiBaseDialog* q_ptr{nullptr};
    PrivateData(const PrivateData&)            = delete;
    PrivateData& operator=(const PrivateData&) = delete;
    
protected:
    int titleBarHeight{24};
    bool bResizable{false};
    QWidget* titleBar{nullptr};
    QLabel* titleLabel{nullptr};
    QPushButton* closeButton{nullptr};
    QVBoxLayout* verticalLayout{nullptr};
    QPushButton* cancleButton{nullptr};
    QPushButton* confrimButton{nullptr};
    NctiFramelessManager* mFramelessManager{nullptr};
};

QWidget* NctiBaseDialog::PrivateData::createTitleBar()
{
    titleBar = new QWidget();
    titleBar->setObjectName(QStringLiteral("nctiBaseDialogTitleBar"));
    titleBar->setFixedHeight(titleBarHeight);

    // 设置标题栏布局
    auto titleBarLayout = new QHBoxLayout(titleBar);
    titleBarLayout->setContentsMargins(0, 0, 9, 0);

    titleLabel = new QLabel("Title", q_ptr);
    titleLabel->setObjectName(QStringLiteral("nctiBaseDialogTitle"));

    closeButton = new QPushButton(q_ptr);
    closeButton->setObjectName(QStringLiteral("nctiBaseDialogCloseButton"));
    closeButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);

    titleBarLayout->addWidget(titleLabel);
    titleBarLayout->addStretch();
    titleBarLayout->addWidget(closeButton);

    return titleBar;
}

void NctiBaseDialog::PrivateData::setupUi()
{
    auto frame = new QFrame(q_ptr);
    frame->setObjectName("nctiBaseDialogFrame");
    frame->setContentsMargins(QMargins{});
    frame->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    
    // 设置布局
    QVBoxLayout* vBoxMainLayout = new QVBoxLayout(frame);
    vBoxMainLayout->setContentsMargins(QMargins{});
    vBoxMainLayout->setAlignment(Qt::AlignTop);
    vBoxMainLayout->setSpacing(0);

    // 创建标题栏
    vBoxMainLayout->addWidget(createTitleBar());

    // 窗口内容布局
    verticalLayout = new QVBoxLayout();
    verticalLayout->setContentsMargins(QMargins{});
    verticalLayout->setAlignment(Qt::AlignTop);
    verticalLayout->setSpacing(0);
    vBoxMainLayout->addLayout(verticalLayout);

    // 设置对话框的主布局并添加QFrame
    auto mainLayout = new QVBoxLayout(q_ptr);
    mainLayout->setContentsMargins(QMargins{});
    mainLayout->addWidget(frame);
    q_ptr->setLayout(mainLayout);

    mFramelessManager = new NctiFramelessManager(q_ptr);
    mFramelessManager->setTitleHeight(titleBarHeight);
    mFramelessManager->setRubberBandOnResize(bResizable);
    mFramelessManager->setResizable(bResizable);
}

void NctiBaseDialog::PrivateData::setTitleHeight(int height)
{
    auto title = q_ptr->findChild<QWidget*>("dialogTitleBar");
    if (title) {
        title->setFixedHeight(height);
    }
    
    if (mFramelessManager) {
        mFramelessManager->setTitleHeight(height);
    }
}

void NctiBaseDialog::PrivateData::setTitleContentsMargins(const QMargins& margins)
{
    auto title = q_ptr->findChild<QWidget*>("dialogTitleBar");
    if (title) {
        title->layout()->setContentsMargins(margins);
    }
}

//-----------------------------------------------------------------------------
// NctiBaseDialog
//-----------------------------------------------------------------------------

NctiBaseDialog::NctiBaseDialog(QWidget* parent, TitleBarHeight height, bool bResizable)
    : QDialog(parent, Qt::FramelessWindowHint)
    , d_ptr(new PrivateData(this))
{
    d_ptr->titleBarHeight = height.value;
    d_ptr->bResizable = bResizable;

    //设置背景透明
    this->setAttribute(Qt::WA_TranslucentBackground);

    if (!bResizable) {
        this->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    }

    // 读取并设置QSS样式表
     QFile file(":/style/NctiBaseDialog.qss");
     if (file.open(QFile::ReadOnly | QFile::Text)) {
         QTextStream stream(&file);
         QString styleSheet = stream.readAll();
         setStyleSheet(styleSheet);
         file.close();
     }

    d_ptr->setupUi();

    connect(d_ptr->closeButton, &QAbstractButton::clicked, this, &NctiBaseDialog::reject);
}

NctiBaseDialog::~NctiBaseDialog()
{
}

QWidget* NctiBaseDialog::getTitleBar()
{
    return d_ptr->titleBar;
}

QLabel* NctiBaseDialog::getTitleLabel()
{
    return d_ptr->titleLabel;
}

void NctiBaseDialog::showCloseButton(bool bVisible)
{
    d_ptr->closeButton->setVisible(bVisible);
}

void NctiBaseDialog::setTitle(const QString& title, int height, const QMargins& margins)
{
    d_ptr->titleLabel->setText(title);
    if (height > 0) {
        d_ptr->setTitleHeight(height);
    }
    d_ptr->setTitleContentsMargins(margins);
}

void NctiBaseDialog::setSize(const QSize& size)
{
    setFixedSize(size);
}

void NctiBaseDialog::setWidget(QWidget* widget)
{
    d_ptr->verticalLayout->addWidget(widget);

    // 确保新添加的控件也能应用到样式表
     if (!this->styleSheet().isEmpty()) {
         widget->setStyleSheet(this->styleSheet());
         // 遍历新控件的所有子控件，将样式表也应用到它们
         for (auto childWidget : widget->findChildren<QWidget*>()) {
             childWidget->setStyleSheet(this->styleSheet());
         }
     }
}

void NctiBaseDialog::reject()
{
    Q_EMIT sigClose();
    QDialog::reject();
}

QVBoxLayout* NctiBaseDialog::getLayout()
{
    return d_ptr->verticalLayout;
}

QPushButton* NctiBaseDialog::getCloseButton() const
{
    return d_ptr->closeButton;
}

void NctiBaseDialog::setBaseStyleSheet(const QString& styleSheet)
{
    if (!styleSheet.isEmpty()) {
        setStyleSheet(styleSheet);
        // 确保标题栏也应用此样式表
        d_ptr->titleBar->setStyleSheet(styleSheet);
    }
}

int NctiBaseDialog::titleBarHeight()
{
    return d_ptr->titleBarHeight;
}

}