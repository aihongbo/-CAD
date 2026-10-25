/*
 * Copyright (c) 2026 粤港澳大湾区（广东）国创中心
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

#include "NctSketchConstrDlg.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QStackedWidget>
#include <QStyle>
using namespace NCTI;

NctSketchConstrDlg::NctSketchConstrDlg(QWidget* i_parent) 
	: QDialog(i_parent)
	, m_content(nullptr)
{
	init();
}

NctSketchConstrDlg::~NctSketchConstrDlg()
{
}

void NCTI::NctSketchConstrDlg::init()
{
	this->setWindowFlags(Qt::WindowStaysOnTopHint | Qt::Dialog);
	this->setWindowModality(Qt::NonModal);
	this->adjustSize();

	// 主布局
	QVBoxLayout* mainLayout = new QVBoxLayout(this);
	mainLayout->setSpacing(10);
	mainLayout->setContentsMargins(10, 10, 10, 10);

	QStackedWidget* stackedWidget = new QStackedWidget;
	stackedWidget->setObjectName("content");
	mainLayout->addWidget(stackedWidget);

	QHBoxLayout* buttonLayout = new QHBoxLayout();
	QPushButton* okButton = new QPushButton(tr("确定"));
	okButton->setDefault(true);
	QPushButton* cancelButton = new QPushButton(tr("取消"));
	cancelButton->setDefault(true);
	buttonLayout->addWidget(okButton);
	buttonLayout->addWidget(cancelButton);
	mainLayout->addLayout(buttonLayout);

	connect(okButton, SIGNAL(clicked()), this, SLOT(onOk()));
	connect(cancelButton, SIGNAL(clicked()), this, SLOT(onCancel()));
}

void NCTI::NctSketchConstrDlg::setTitle(QString i_title)
{
	this->setWindowTitle(i_title);
}

void NCTI::NctSketchConstrDlg::setContent(NctiConstrContentWidget* i_content)
{
	QStackedWidget* stackedWidget = findChild<QStackedWidget*>("content");
	if (!stackedWidget)
		return;

	while (stackedWidget->count() > 0)
	{
		QWidget* page = stackedWidget->widget(0);
		stackedWidget->removeWidget(page);
		delete page; 
	}

	m_content = i_content;
	stackedWidget->addWidget(i_content);
}

void NctSketchConstrDlg::onOk()
{
	if (m_content)
		m_content->apply();
	this->accept();
	this->close();
}

void NctSketchConstrDlg::onCancel()
{
	this->hide();
}