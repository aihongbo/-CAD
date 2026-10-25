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

#include "Dialog.h"
#include <QLabel>
#include "ui_DialogButtonGroup.h"

namespace NCTI {
Dialog::Dialog(QWidget* parent)
    : NctiBaseDialog(parent)
    , m_content(new QFrame(this))
    , m_contentLayout(new QVBoxLayout(m_content))
    , m_delegate(nullptr)
    , m_afterSetupUiBlock(nullptr)
{
    m_content->setLayout(m_contentLayout);
    m_content->setObjectName("dialog-content");
    m_contentLayout->setContentsMargins(0, 0, 0, 0);
    m_contentLayout->setSpacing(0);

    setWidget(m_content);
}

Dialog::~Dialog()
{
    for (auto iter = m_name2Ui.begin(); iter != m_name2Ui.end(); iter++) {
        if (iter.value() == nullptr)
            continue;
        //delete iter.value();
    }
}

void Dialog::addDefaultImageAndLabel()
{
    QWidget* widget     = new QWidget(m_content);
    QHBoxLayout* layout = new QHBoxLayout(widget);
    widget->setObjectName("dialog-content-image-label");
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    widget->setLayout(layout);

    QLabel* image = new QLabel(widget);
    image->setObjectName("dialog-content-image");
    layout->addWidget(image);

    QLabel* label = new QLabel(widget);
    label->setObjectName("dialog-content-label");
    layout->addWidget(label);

    addByWidget(widget->objectName(), widget);
}

void Dialog::addDefaultLabel()
{
    QLabel* label = new QLabel(m_content);
    label->setObjectName("dialog-content-label");
    addByWidget(label->objectName(), label);
}

QLabel* Dialog::getDefaultLabel()
{
    if (contains("dialog-content-label")) {
        return qobject_cast<QLabel*>(getWidget("dialog-content-label"));
    }
    else if (contains("dialog-content-image-label")) {
        return getWidget("dialog-content-image-label")->findChild<QLabel*>("dialog-content-label");
    }
    else {
    }
    return nullptr;
}

void Dialog::addDefaultCancelAndConfire(const QString& cancel, const QString& ok)
{
    Ui::DialogButtonGroup* ui = nullptr;
    QWidget* widget           = nullptr;
    if (addByUi<Ui::DialogButtonGroup, QFrame>("dialog-bottom-button-group", &ui, &widget)) {
        widget->setObjectName("dialog-bottom-button-group");
        ui->pushButton_left->setText(cancel);
        ui->pushButton_right->setText(ok);
        connect(ui->pushButton_left, &QPushButton::clicked, this, &Dialog::reject);
        connect(ui->pushButton_right, &QPushButton::clicked, this, &Dialog::accept);
    }
}

void Dialog::addDefaultConfire(const QString& ok)
{
    Ui::DialogButtonGroup* ui = new Ui::DialogButtonGroup;
    QFrame* frame             = new QFrame(this);
    ui->setupUi(frame);
    ui->pushButton_left->hide();

    if (addByWidget("dialog-bottom-button-group", ui, frame)) {
        ui->pushButton_right->setText(ok);
        connect(ui->pushButton_right, &QPushButton::clicked, this, &Dialog::accept);
    }
    else {
        delete ui;
        delete frame;
    }
}

bool Dialog::addByWidget(const QString& name, void* ui, QWidget* widget)
{
    if (contains(name)) {
        return false;
    }

    addUi(name, ui);
    return addWidget(name, widget);
}

bool Dialog::addByWidget(const QString& name, QWidget* widget)
{
    return addByWidget(name, nullptr, widget);
}

void* Dialog::getUi(const QString& name)
{
    return m_name2Ui.value(name, nullptr);
}

QWidget* Dialog::getWidget(const QString& name)
{
    return m_name2Widget.value(name, nullptr);
}

void Dialog::setDelegate(DialogDelegate* delegate)
{
    m_delegate = delegate;
}

void Dialog::setAfterSetupUiBlock(std::function<void(const QString&, void*, QWidget*)> block)
{
    m_afterSetupUiBlock = block;
}

void Dialog::accept()
{
    if (!beforeAccpet()) {
        return;
    }
    NctiBaseDialog::accept();
}

void Dialog::afterSetupUi(const QString& name, void* ui, QWidget* widget)
{
}

bool Dialog::beforeAccpet()
{
    return true;
}

void Dialog::remove(const QString& name)
{
    removeUi(name);
    removeWidget(name);
}

bool Dialog::addUi(const QString& name, void* ui)
{
    if (contains(name)) {
        return false;
    }

    m_name2Ui.insert(name, ui);
    return true;
}

void Dialog::removeUi(const QString& name)
{
    m_name2Ui.remove(name);
}

bool Dialog::addWidget(const QString& name, QWidget* widget, int index)
{
    if (widget->objectName().isEmpty())
        widget->setObjectName(name);

    m_name2Widget.insert(name, widget);
    if (index == -1) {
        m_contentLayout->addWidget(widget);
    }
    else {
        m_contentLayout->insertWidget(index, widget);
    }
    return true;
}

void Dialog::removeWidget(const QString& name)
{
    auto widget = m_name2Widget.take(name);
    if (!widget) {
        return;
    }
    m_contentLayout->removeWidget(widget);
}

bool Dialog::contains(const QString& name)
{
    return m_name2Ui.contains(name);
}

} // namespace NCTI
