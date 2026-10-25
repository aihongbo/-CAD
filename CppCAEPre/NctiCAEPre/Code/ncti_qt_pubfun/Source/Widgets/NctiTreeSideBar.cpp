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

#include "NctiTreeSideBar.h"
#include "NctiTreeSidePannel.h"

#include <QtEvents>
#include <QToolButton>
#include <QStackedWidget>
#include <QPainter>
#include <QVBoxLayout>
#include <QMap>
#include <QButtonGroup>
#include <QTimer>
#include <QMenu>
#include <QDebug>

constexpr auto side_button_height = 24;

namespace NCTI {

    class NctiTreeSideBar::PrivateData
    {
        NCTI_QT_PUBFUNC_DECLARE_PUBLIC(NctiTreeSideBar)
    public:
        PrivateData(NctiTreeSideBar* parent) : q_ptr(parent) {}
    public:
        NctiTreeSidePanel* mSidePanel = nullptr;
        QVBoxLayout* mVBoxLayout = nullptr;
        QMap<QString, QToolButton*>  mButtonMap;
        QButtonGroup* mButtonGroup = nullptr;
        static constexpr QSize mIconSize = QSize(24, 24);
        static constexpr QSize mFixedSize = QSize(24, 24);
    };

    //==============================================================
    // NctiTreeSideBar
    //==============================================================
    NctiTreeSideBar::NctiTreeSideBar(QWidget* parent)
        : QFrame(parent)
        , d_ptr(new PrivateData(this))
    {
        d_ptr->mVBoxLayout = new QVBoxLayout(this);
        d_ptr->mVBoxLayout->setSpacing(0);
        d_ptr->mVBoxLayout->setContentsMargins(0, 0, 0, 0);
        setLayout(d_ptr->mVBoxLayout);
        d_ptr->mVBoxLayout->setAlignment(Qt::AlignTop); // 确保按钮顶部对齐
        d_ptr->mVBoxLayout->setSizeConstraint(QLayout::SetMinAndMaxSize); // 禁止自动拉伸
    }

    NctiTreeSideBar::~NctiTreeSideBar()
    {
    }

    int NctiTreeSideBar::getCurrentIndex() const
    {
        if (!d_ptr->mSidePanel) {
            return 0;
        }
        return d_ptr->mSidePanel->currentIndex();
    }

    void NctiTreeSideBar::setCurrentIndex(int index)
    {
        if (d_ptr->mSidePanel) {
            d_ptr->mSidePanel->showContentPage(index);
        }
        for (auto it = d_ptr->mButtonMap.begin(); it != d_ptr->mButtonMap.end(); ++it) {
            int id = it.value()->property("sidePanelIndex").toInt();
            it.value()->setChecked(id == index);
        }
    }

    QWidget* NctiTreeSideBar::getCurrentWidget() const
    {
        if (!d_ptr->mSidePanel) {
            return nullptr;
        }
        return d_ptr->mSidePanel->currentWidget();
    }

    QWidget* NctiTreeSideBar::getWidget(int index) const
    {
        if (!d_ptr->mSidePanel) {
            return nullptr;
        }

        if (index < 0 || index >= d_ptr->mSidePanel->count()) {
            return nullptr;
        }
        return d_ptr->mSidePanel->widget(index);
    }

    bool NctiTreeSideBar::uncheckOtherButtons(QToolButton* button) const
    {
        bool checked = false;
        for (auto it = d_ptr->mButtonMap.begin(); it != d_ptr->mButtonMap.end(); ++it) {
            if (it.value() == button) {
                continue;
            }
            if (it.value()->isChecked()) {
                it.value()->setChecked(false);
                checked = true;
            }
        }
        return checked;
    }

    void NctiTreeSideBar::addSideButton(const QIcon& icon, const QString& objName, QWidget* page, int id)
    {
        QToolButton* btn = new QToolButton(this);
        btn->setProperty("objTreeSidebar_toolbutton", true);
        btn->setObjectName(objName);
        btn->setIcon(icon);
        btn->setIconSize(PrivateData::mIconSize);
        btn->setFixedSize(40, 40);
        btn->setToolButtonStyle(Qt::ToolButtonIconOnly);
        btn->setCheckable(true);
        btn->setProperty("sidePanelId", id);
        d_ptr->mVBoxLayout->addWidget(btn);
        d_ptr->mButtonMap.insert(objName, btn);
        int index = d_ptr->mSidePanel->addWidget(page);
        btn->setProperty("sidePanelIndex", index);
        connect(btn, &QToolButton::clicked, this, &NctiTreeSideBar::onButtonClicked);

        // 启用右键菜单
        //btn->setContextMenuPolicy(Qt::CustomContextMenu);
        //connect(btn, &QWidget::customContextMenuRequested, this, &NctiTreeSideBar::showContextMenu);
    }

    void NctiTreeSideBar::setSidePanel(NctiTreeSidePanel* sidePanel)
    {
        d_ptr->mSidePanel = sidePanel;
    }

    QToolButton* NctiTreeSideBar::getButtonByObjName(const QString& objName) const
    {
        auto it = d_ptr->mButtonMap.find(objName);
        return (it != d_ptr->mButtonMap.end()) ? it.value() : nullptr;
    }

    void NctiTreeSideBar::onButtonClicked(bool checked)
    {
        QToolButton* clickedButton = qobject_cast<QToolButton*>(sender());
        if (clickedButton) {
            Q_EMIT sigButtonClicked(clickedButton);
        }
    }

    void NctiTreeSideBar::showContextMenu(const QPoint& pos)
    {
        QToolButton* clickedButton = qobject_cast<QToolButton*>(sender());
        if (!clickedButton) return;

        QMenu contextMenu(this);
        QAction* updateAction = contextMenu.addAction("刷新");
        connect(updateAction, &QAction::triggered, this, &NctiTreeSideBar::updateTreeModel);
        
        contextMenu.exec(clickedButton->mapToGlobal(pos));
    }

}
