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

#include "ExtrudeDlg.h"
#include "NctiCommandManager.h"
#include "NctiCommand.h"
#include "NctiMeasuringTool.h"

#include <QComboBox>
#include <QPushButton>
#include <QListView>
#include <QGroupBox>
#include <QLineEdit>
#include <QLayout>
#include <QHBoxLayout>
#include <QLabel>

namespace NCTI
{
	ExtrudeDlg* ExtrudeDlg::mInstance = nullptr;

	void ExtrudeDlg::GetLengthFun(Ncti_Double i_dbl)
	{
		ExtrudeDlg* pInstance = ExtrudeDlg::instance();
		if (pInstance)
		{
			pInstance->m_dHeight = i_dbl;
			pInstance->initData();
			pInstance->PreResult();
		}
		
	}

	ExtrudeDlg::ExtrudeDlg(NctiBaseModel* pBaseModel, QWidget* parent)
        : NctiBaseDialog(parent)
        , m_pBaseModel(pBaseModel)
	{
		init();
        NctiMeasuringTool::instance()->SetCalLengthCallback(ExtrudeDlg::GetLengthFun);
	}
                                                 
	ExtrudeDlg::~ExtrudeDlg()
	{
        NctiMeasuringTool::instance()->ResetAll();
	}

	void ExtrudeDlg::init()
	{
		auto widget = new QFrame(this);
		widget->setObjectName("ExtrudeDlg");
		setTitle(QStringLiteral("拉伸"));
		//setTitle(QStringLiteral("Extrude"), 30, { 23,0,23,0 });
		this->layout()->setContentsMargins(0, 0, 0, 0);
		this->setWindowFlags(this->windowFlags() | Qt::WindowStaysOnTopHint | Qt::Tool);
		//this->setStyleSheet("background-color: white;");

		QDoubleValidator* latitude = new QDoubleValidator(this);
		latitude->setNotation(QDoubleValidator::StandardNotation);
		latitude->setBottom(0.0);


		m_Height = new QLineEdit("5", this);
		m_RemoveMaterial = new QCheckBox("移除材料", this);
		m_Reverse = new QCheckBox("反转", this);
		m_BothSide = new QCheckBox("两边", this);
		m_Angle = new QCheckBox("拔模角度", this);
		m_UseAngle = new QLineEdit("", this);
		m_BtnPreview = new QPushButton(this);
		m_BtnPreview->setText(QStringLiteral("预览"));
		m_BtnOK = new QPushButton(this);
		m_BtnCancel = new QPushButton(this);
		m_BtnOK->setText(QStringLiteral("确定"));
		m_BtnCancel->setText(QStringLiteral("取消"));
		m_Height->setValidator(latitude);
		m_UseAngle->setValidator(latitude);
		m_UseAngle->setEnabled(false);

		//m_RemoveMaterial->setProperty("modetails-checkbox", true);
		//m_Angle->setProperty("modetails-checkbox", true);
		//m_BothSide->setProperty("modetails-checkbox", true);
		//m_Reverse->setProperty("modetails-checkbox", true);
		m_BtnOK->setObjectName("modetails-ok-button");
		m_BtnPreview->setObjectName("modetails-preview-button");
		m_BtnCancel->setObjectName("modetails-cancel-button");
		m_UseAngle->setObjectName("Use_Angle");

		auto labelHeight = new QLabel(QStringLiteral("高度："), this);
		//labelHeight->setObjectName("select-Geo-Kernel");

		QVBoxLayout* layout = new QVBoxLayout(widget);
		layout->setContentsMargins(4, 0, 1, 0);
		QHBoxLayout* HLayout = new QHBoxLayout(this);
		HLayout->addSpacing(8);
		HLayout->addWidget(labelHeight);
		HLayout->addWidget(m_Height);

		//一个widget把QCheckBox，QLabel，QLineEdit，m_BtnPreview排列放好
		QWidget* p_widget = new QWidget;
		p_widget->setObjectName("p_widget");
		QVBoxLayout* p_widgetLayout = new QVBoxLayout(p_widget);
		p_widgetLayout->setContentsMargins(0, 16, 0, 0);
		p_widgetLayout->addLayout(HLayout);
		p_widgetLayout->addSpacing(4);
		HLayout = new QHBoxLayout();
		HLayout->addStretch();
		HLayout->addWidget(m_RemoveMaterial);
		HLayout->addWidget(m_Reverse);
		HLayout->addStretch();
		p_widgetLayout->addLayout(HLayout);
		HLayout = new QHBoxLayout();
		HLayout->addStretch();
		HLayout->addWidget(m_Angle);
		HLayout->addWidget(m_BothSide);
		HLayout->addStretch();
		p_widgetLayout->addLayout(HLayout);
		p_widgetLayout->addSpacing(4);
		HLayout = new QHBoxLayout();
		HLayout->addStretch();
		HLayout->addWidget(m_UseAngle);
		HLayout->addStretch();
		p_widgetLayout->addLayout(HLayout);
		HLayout = new QHBoxLayout();
		HLayout->addSpacing(4);
		HLayout->addWidget(m_BtnPreview);
		HLayout->addSpacing(2);
		p_widgetLayout->addLayout(HLayout);
		p_widgetLayout->addSpacing(14);
		layout->addWidget(p_widget);
		layout->addStretch();
		HLayout = new QHBoxLayout(this);
		HLayout->addStretch();
		HLayout->addWidget(m_BtnCancel);
		HLayout->addWidget(m_BtnOK);
		layout->addLayout(HLayout);
		


		setLayout(layout);
		connect(m_BtnOK, SIGNAL(clicked(bool)), this, SLOT(ClickOk(bool)));
		connect(m_BtnCancel, SIGNAL(clicked(bool)), this, SLOT(ClickCancel(bool)));
		connect(m_BtnPreview, SIGNAL(clicked(bool)), this, SLOT(ClickPreview(bool)));
		connect(m_Angle, SIGNAL(clicked(bool)), this, SLOT(ClickAngle(bool)));

		connect(this->getCloseButton(), &QPushButton::clicked, this, &ExtrudeDlg::ClickCancel);

		setWidget(widget);
	}

	void ExtrudeDlg::initData()
	{
		m_Height->setText(QString("%1").arg(m_dHeight));
		m_RemoveMaterial->setChecked(m_bRemove);
		m_Reverse->setChecked(m_bReverse);
		m_BothSide->setChecked(m_bBothSide);
		m_Angle->setChecked(m_dAngle);
		m_UseAngle->setText(QString("%1").arg(m_dAngle));

		Refresh();
	}

	void ExtrudeDlg::Refresh()
	{
		if (m_Angle->isChecked())
		{
			m_UseAngle->setEnabled(true);
		}
		else
		{
			m_UseAngle->setEnabled(false);
		}
	}

	void ExtrudeDlg::ClickPreview(bool boo)
	{
		PreResult();
	}

	void ExtrudeDlg::PreResult()
	{
		m_dHeight = m_Height->text().toDouble();
		m_bReverse = m_Reverse->isChecked();
		m_bRemove = m_Reverse->isChecked();
		m_bBothSide = m_BothSide->isChecked();
		m_bUseAngle = m_Angle->isChecked();
		m_dAngle = m_UseAngle->text().toDouble();

		if (m_pBaseModel)
		{
			NctiCommandManager* pCommandManage = NctiCommandManager::GetCommandManager(m_pBaseModel);
			if (pCommandManage)
			{
				pCommandManage->ProcessUpdate();
			}
		}
	}

	void ExtrudeDlg::ClickAngle(bool boo)
	{
		Refresh();
	}

	void ExtrudeDlg::ClickOk(bool boo)
	{
		m_dHeight = m_Height->text().toDouble();
		m_bReverse = m_Reverse->isChecked();
		m_bRemove = m_Reverse->isChecked();
		m_bBothSide = m_BothSide->isChecked();
		m_bUseAngle = m_Angle->isChecked();
		m_dAngle = m_UseAngle->text().toDouble();

		if (m_pBaseModel)
		{
			NctiCommandManager* pCommandManage = NctiCommandManager::GetCommandManager(m_pBaseModel);
			if (pCommandManage)
			{
				pCommandManage->ProcessUpdate();
				pCommandManage->ProcessOkButton();
				pCommandManage->CheckTermination();
			}
		}
	}

	void ExtrudeDlg::ClickCancel(bool boo)
	{
		if (m_pBaseModel)
		{
			NctiCommandManager* pCommandManage = NctiCommandManager::GetCommandManager(m_pBaseModel);
			if (pCommandManage)
			{
				pCommandManage->ProcessCancelButton();
				pCommandManage->RequestTermination(NULL);
				pCommandManage->ExitCommand();
			}
		}
	}

	ExtrudeDlg* ExtrudeDlg::instance()
	{
		return mInstance;
	}

	void ExtrudeDlg::SetInstance(ExtrudeDlg* pExtrudeDlg)
	{
		mInstance = pExtrudeDlg;
	}

	void ExtrudeDlg::ShowDialog(NctiBaseModel* pBaseModel, double dHeight, int bReverse, int bRemove, int bBothSide, int bUseAngle, double dAngle, QWidget* parent)
	{
		ExtrudeDlg* pInstance = ExtrudeDlg::instance();
		if (pInstance == nullptr)
		{
			pInstance = new ExtrudeDlg(pBaseModel, parent);
			pInstance->show();
			ExtrudeDlg::SetInstance(pInstance);
		}
		else
		{
			if (pInstance->isHidden())
				pInstance->show();
		}
		pInstance->m_dHeight = dHeight;
		pInstance->m_bReverse = bReverse;
		pInstance->m_bRemove = bRemove;
		pInstance->m_bBothSide = bBothSide;
		pInstance->m_bUseAngle = bUseAngle;
		pInstance->m_dAngle = dAngle;
		pInstance->initData();
	}

	void ExtrudeDlg::DeleteDialog()
	{
		ExtrudeDlg* pExtrudeDlg = ExtrudeDlg::instance();
		delete pExtrudeDlg;
		ExtrudeDlg::SetInstance(NULL);
	}

	void ExtrudeDlg::SetExtrudeData(double dHeight, int bReverse, int bRemove, int bBothSide, int bUseAngle, double dAngle)
	{
		ExtrudeDlg* pInstance = ExtrudeDlg::instance();
		pInstance->m_dHeight = dHeight;
		pInstance->m_bReverse = bReverse;
		pInstance->m_bRemove = bRemove;
		pInstance->m_bBothSide = bBothSide;
		pInstance->m_bUseAngle = bUseAngle;
		pInstance->m_dAngle = dAngle;
		pInstance->initData();
	}

	void ExtrudeDlg::GetExtrudeData(double& dHeight, int& bReverse, int& bRemove, int& bBothSide, int& bUseAngle, double& dAngle)
	{
		ExtrudeDlg* pInstance = ExtrudeDlg::instance();
		dHeight = pInstance->m_dHeight;
		bReverse = pInstance->m_bReverse;
		bRemove = pInstance->m_bRemove;
		bBothSide = pInstance->m_bBothSide;
		bUseAngle = pInstance->m_bUseAngle;
		dAngle = pInstance->m_dAngle;
	}
}