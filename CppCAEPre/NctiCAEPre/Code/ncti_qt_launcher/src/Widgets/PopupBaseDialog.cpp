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

#include "PopupBaseDialog.h"

#include "SAFramelessHelper.h"

#include <QHBoxLayout>
#include <QFrame>
#include <QPushButton>

namespace NCTI {

    class PopupBaseDialog::PrivateData
    {
        NCTI_QT_PUBFUNC_DECLARE_PUBLIC(PopupBaseDialog)
    public:
        PrivateData(PopupBaseDialog* parent) : q_ptr(parent) {}
        void setupUi();
    private: 
        QWidget* createTitleBar();
    protected:
        bool bFeatureWgt{ false };
        int titleBarHeight{ 24 };
        bool bResizable{ false };
        QWidget* titleBar{ nullptr };
        QLabel* titleLabel{ nullptr };
        QPushButton* closeButton{ nullptr };
        QVBoxLayout* verticalLayout{ nullptr };
        QPushButton* cancleButton{ nullptr };
        QPushButton* confrimButton{ nullptr };
        SAFramelessHelper* mFramelessHelper{ nullptr };
    };

    QWidget* PopupBaseDialog::PrivateData::createTitleBar()
    {
        titleBar = new QWidget();
        titleBar->setObjectName(QStringLiteral("popup-dialog-title-bar"));
        titleBar->setFixedHeight(titleBarHeight);

        // 设置标题栏布局  
        auto titleBarLayout = new QHBoxLayout(titleBar);
        titleBarLayout->setContentsMargins(0, 0, 9, 0);

        titleLabel = new QLabel("Title", q_ptr);
        titleLabel->setObjectName(QStringLiteral("popup-dialog-title"));

        closeButton = new QPushButton(q_ptr);
        closeButton->setObjectName(QStringLiteral("popup-dialog-close-button"));
        closeButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);

        titleBarLayout->addWidget(titleLabel);
        titleBarLayout->addStretch();
        titleBarLayout->addWidget(closeButton);

        return titleBar;
    }

    void PopupBaseDialog::PrivateData::setupUi()
    {
        auto frame = new QFrame(q_ptr);
        frame->setObjectName("popup-dialog-frame");
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
        
        // 确定、取消按钮
        if (bFeatureWgt) {
            QHBoxLayout* horizontalLayout = new QHBoxLayout();
            horizontalLayout->setContentsMargins(4, 6, 16, 18);
            horizontalLayout->setSpacing(8);
            horizontalLayout->addStretch();

            cancleButton = new QPushButton(QStringLiteral("取消"), frame);
            cancleButton->setObjectName(QStringLiteral("popup-dialog-cancel-button"));
            cancleButton->setFixedSize(88, 32);
            cancleButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
            horizontalLayout->addWidget(cancleButton);

            confrimButton = new QPushButton(QStringLiteral("确定"), frame);
            confrimButton->setObjectName(QStringLiteral("popup-dialog-ok-button"));
            confrimButton->setFixedSize(88, 32);
            confrimButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
            horizontalLayout->addWidget(confrimButton);
            vBoxMainLayout->addLayout(horizontalLayout);
        }
        
        // 设置对话框的主布局并添加QFrame 
        auto mainLayout = new QVBoxLayout(q_ptr);
        mainLayout->setContentsMargins(QMargins{});
        mainLayout->addWidget(frame);
        q_ptr->setLayout(mainLayout);

        mFramelessHelper = new SAFramelessHelper(q_ptr);
        mFramelessHelper->setTitleHeight(titleBarHeight);
        mFramelessHelper->setRubberBandOnResize(bResizable);
        mFramelessHelper->setWidgetResizable(bResizable);
    }

    //-----------------------------------------------------------------------------
    // PopupBaseDialog
    //-----------------------------------------------------------------------------
    PopupBaseDialog::PopupBaseDialog(QWidget* parent, bool isFeatureWgt, int titleBarHeight, bool bResizable)
        : QDialog(parent, Qt::FramelessWindowHint)
        , d_ptr(new PrivateData(this))
    {
        d_ptr->bFeatureWgt = isFeatureWgt;
        d_ptr->titleBarHeight = titleBarHeight;
        d_ptr->bResizable = bResizable;

        //设置背景透明
        this->setAttribute(Qt::WA_TranslucentBackground);

        if (!bResizable) {
            this->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        }

        d_ptr->setupUi();
        
        connect(d_ptr->closeButton, &QAbstractButton::clicked, this, &PopupBaseDialog::reject);
        
        if (isFeatureWgt) {
            connect(d_ptr->cancleButton, &QPushButton::clicked, this, &PopupBaseDialog::sigCancle);
            connect(d_ptr->confrimButton, &QPushButton::clicked, this, &PopupBaseDialog::sigConfrim);
        }
    }

    PopupBaseDialog::~PopupBaseDialog()
    {
    }

    QWidget* PopupBaseDialog::getTitleBar()
    {
        return d_ptr->titleBar;
    }

    QLabel* PopupBaseDialog::getTitleLabel()
    {
        return d_ptr->titleLabel;
    }

    void PopupBaseDialog::showCloseButton(bool bVisible)
    {
        d_ptr->closeButton->setVisible(bVisible);
    }

    void PopupBaseDialog::setTitle(const QString& title)
    {
        d_ptr->titleLabel->setText(title);
    }

    void PopupBaseDialog::setSize(const QSize& size)
    {
        setFixedSize(size);
    }

    void PopupBaseDialog::setWidget(QWidget* widget)
    {
        d_ptr->verticalLayout->addWidget(widget);
    }

    void PopupBaseDialog::reject()
    {
        Q_EMIT sigClose();
        QDialog::reject();
    }

    int PopupBaseDialog::titleBarHeight()
    {
        return d_ptr->titleBarHeight;
    }

}