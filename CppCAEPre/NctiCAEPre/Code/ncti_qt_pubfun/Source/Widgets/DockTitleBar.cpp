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

#include "DockTitleBar.h"

#include <QHBoxLayout>

#include "ElideLabel.h"

namespace NCTI {

	DockTitleBar::DockTitleBar(QWidget* parent, bool bShowCloseBtn, bool bElideTitle)
		: QFrame(parent)
		, m_bShowCloseBtn(bShowCloseBtn)
		, m_bElideTitle(bElideTitle)
	{
		setup();
	}

    DockTitleBar::~DockTitleBar()
	{}

	void DockTitleBar::setTitle(const QString& title)
	{
		m_titleLabel->setText(title);
	}
	void DockTitleBar::skipEliedTitle(const QString& prefix)
	{
		m_titleLabel->skipElide(prefix);
	}

	void DockTitleBar::setup()
	{
		m_titleLabel = new ElideLabel(this);
		m_titleLabel->setObjectName("label_title");
		m_titleLabel->setElide(m_bElideTitle);

		m_questionButton = new QPushButton(this);
		m_questionButton->setObjectName("pushButton_question");
		connect(m_questionButton, SIGNAL(clicked()), this, SIGNAL(signalQuestion()));
		m_questionButton->hide();

        if (m_bShowCloseBtn) {
            m_closeButton = new QPushButton(this);
            m_closeButton->setObjectName("pushButton_close");
            connect(m_closeButton, SIGNAL(clicked()), this, SIGNAL(signalClose()));
        }


		QHBoxLayout* layout = new QHBoxLayout(this);
		layout->setContentsMargins(0, 0, 0, 0);
		layout->setSpacing(0);
		layout->addWidget(m_titleLabel);
		layout->addWidget(m_questionButton);
		if (m_bElideTitle) {
			m_titleLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
		}
		else{
			layout->addStretch(1);
		}
        if (m_bShowCloseBtn) {
            layout->addWidget(m_closeButton);
        }
		setLayout(layout);
	}


}

