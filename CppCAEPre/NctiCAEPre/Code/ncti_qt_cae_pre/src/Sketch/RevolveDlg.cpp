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

#include "RevolveDlg.h"
#include "NctiCommandManager.h"
#include "NctiCommand.h"

#include <QComboBox>
#include <QPushButton>
#include <QListView>
#include <QGroupBox>
#include <QLineEdit>
#include <QLayout>
#include <QLabel>

namespace NCTI
{
	RevolveDlg* RevolveDlg::mInstance = nullptr;
    RevolveDlg::RevolveDlg(NctiBaseModel* pBaseModel, QWidget* parent)
        : NctiBaseDialog(parent)
        , m_pBaseModel(pBaseModel)
    {
        init();
    }

    RevolveDlg::~RevolveDlg()
    {
    }

    void RevolveDlg::init()
    {
        auto widget = new QFrame(this);
		widget->setObjectName("RevolveDlg");
		setTitle(QStringLiteral("旋转"));
		//setTitle(QStringLiteral("Revolve"), 30, { 23,0,23,0 });
		this->layout()->setContentsMargins(0, 0, 0, 0);
		this->setWindowFlags(this->windowFlags() | Qt::WindowStaysOnTopHint | Qt::Tool);
		//this->setStyleSheet("background-color: white;");

		QDoubleValidator* latitude = new QDoubleValidator(this);
		latitude->setNotation(QDoubleValidator::StandardNotation);
		latitude->setBottom(0.0);

		m_Angle = new QCheckBox("角度", this);
		m_AngleS = new QLineEdit("", this);
		m_AngleE = new QLineEdit("", this);
		m_Remove = new QCheckBox("移除材料", this);
		m_Reverse = new QCheckBox("反向", this);
		m_BtnPreview = new QPushButton(this);
		m_BtnPreview->setText(QStringLiteral("预览"));
		m_BtnOK = new QPushButton(this);
		m_BtnCancel = new QPushButton(this);
		m_BtnOK->setText(QStringLiteral("确定"));
		m_BtnCancel->setText(QStringLiteral("取消"));
		m_AngleS->setValidator(latitude);
		m_AngleE->setValidator(latitude);
		m_AngleS->setReadOnly(true);
		m_AngleE->setReadOnly(true);
		m_Reverse->setEnabled(false);
		auto labelStart = new QLabel(QStringLiteral("起始："), this);
		auto labelEnd =   new QLabel(QStringLiteral("结束："), this);

		// 添加分隔线
		QFrame* line1 = new QFrame();
		line1->setFrameShape(QFrame::HLine);
		line1->setFrameShadow(QFrame::Plain);
		QFrame* line2 = new QFrame();
		line2->setFrameShape(QFrame::HLine);
		line2->setFrameShadow(QFrame::Plain);
		line1->setObjectName("line");
		line2->setObjectName("line");

		m_BtnOK->setObjectName("revolve_ok_button");
		m_BtnPreview->setObjectName("revolve_preview_button");
		m_BtnCancel->setObjectName("revolve_cancel_button");
		m_Angle->setObjectName("Use_Angle");

		QVBoxLayout* layout = new QVBoxLayout(widget);
		QHBoxLayout* HLayout = new QHBoxLayout(this);
		layout->addWidget(line1);
		layout->addWidget(m_Angle);
		HLayout->addWidget(labelStart);
		HLayout->addWidget(m_AngleS);
		layout->addLayout(HLayout);
		HLayout = new QHBoxLayout(this);
		HLayout->addWidget(labelEnd);
		HLayout->addWidget(m_AngleE);
		layout->addLayout(HLayout);
		QHBoxLayout* checkHLayout = new QHBoxLayout(this);
		checkHLayout->addStretch();
		checkHLayout->addWidget(m_Reverse);
		checkHLayout->addWidget(m_Remove);
		checkHLayout->addStretch();
		layout->addLayout(checkHLayout);
		layout->addWidget(m_BtnPreview);
		layout->addWidget(line2);
		HLayout = new QHBoxLayout(this);
		HLayout->addStretch();
		HLayout->addWidget(m_BtnCancel);
		HLayout->addWidget(m_BtnOK);
		layout->addLayout(HLayout);
		layout->addStretch();

		setLayout(layout);
		connect(m_BtnOK, SIGNAL(clicked(bool)), this, SLOT(ClickOk(bool)));
		connect(m_BtnCancel, SIGNAL(clicked(bool)), this, SLOT(ClickCancel(bool)));
		connect(m_BtnPreview, SIGNAL(clicked(bool)), this, SLOT(ClickPreview(bool)));
		connect(m_Angle, SIGNAL(clicked(bool)), this, SLOT(ClickAngle(bool)));

		setWidget(widget);
	}

	void RevolveDlg::initData()
	{
		m_Angle->setChecked(m_bUseAngle);
		m_AngleS->setText(QString("%1").arg(m_dStartAngle));
		m_AngleE->setText(QString("%1").arg(m_dEndAngle));
		m_Remove->setChecked(m_bRemove);
		m_Reverse->setChecked(m_bReverse);
		Refresh();
	}

	void RevolveDlg::Refresh()
	{
		if (m_Angle->isChecked())
		{
			m_AngleS->setReadOnly(false);
			m_AngleE->setReadOnly(false);
			m_Reverse->setEnabled(true);
		}
		else
		{
			m_AngleS->setReadOnly(true);
			m_AngleE->setReadOnly(true);
			m_Reverse->setEnabled(false);
		}
	}

	void RevolveDlg::ClickPreview(bool boo)
	{
		PreResult();
	}

	void RevolveDlg::ClickAngle(bool boo)
	{
		Refresh();
	}

	void RevolveDlg::PreResult()
	{
		m_bUseAngle = m_Angle->isChecked();
		m_dStartAngle = m_AngleS->text().toDouble();
		m_dEndAngle = m_AngleE->text().toDouble();
		m_bRemove = m_Remove->isChecked();
		m_bReverse = m_Reverse->isChecked();
		if (m_pBaseModel)
		{
			NctiCommandManager* pCommandManage = NctiCommandManager::GetCommandManager(m_pBaseModel);
			if (pCommandManage)
			{
				pCommandManage->ProcessUpdate();
			}
		}
	}

	void RevolveDlg::ClickCancel(bool boo)
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

	void RevolveDlg::ClickOk(bool boo)
	{
		m_bUseAngle = m_Angle->isChecked();
		m_dStartAngle = m_AngleS->text().toDouble();
		m_dEndAngle = m_AngleE->text().toDouble();
		m_bRemove = m_Remove->isChecked();
		m_bReverse = m_Reverse->isChecked();

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

	RevolveDlg* RevolveDlg::instance()
	{
		return mInstance;
	}

	void RevolveDlg::SetInstance(RevolveDlg* pRevolveDlg)
	{
		mInstance = pRevolveDlg;
	}

	void RevolveDlg::ShowDialog(NctiBaseModel* pBaseModel, bool bUseAngle, double dStartAngle, double dEndAngle, int bRemove, int bReverse, QWidget* parent)
	{
		RevolveDlg* pInstance = RevolveDlg::instance();
		if (pInstance == nullptr)
		{
			pInstance = new RevolveDlg(pBaseModel, parent);
			pInstance->show();
			RevolveDlg::SetInstance(pInstance);
		}
		else
		{
			if(pInstance->isHidden())
				pInstance->show();
		}

		pInstance->m_bUseAngle = bUseAngle;
		pInstance->m_dStartAngle = dStartAngle;
		pInstance->m_dEndAngle = dEndAngle;
		pInstance->m_bRemove = bRemove;
		pInstance->m_bReverse = bReverse;
		pInstance->initData();
	}

	void RevolveDlg::DeleteDialog()
	{
		RevolveDlg* pInstance = RevolveDlg::instance();
		delete pInstance;
		RevolveDlg::SetInstance(NULL);
	}

	void RevolveDlg::SetRevolveData(bool bUseAngle, double dStartAngle, double dEndAngle, int bRemove, int bReverse)
	{
		RevolveDlg* pInstance = RevolveDlg::instance();
		pInstance->m_bUseAngle = bUseAngle;
		pInstance->m_dStartAngle = dStartAngle;
		pInstance->m_dEndAngle = dEndAngle;
		pInstance->m_bRemove = bRemove;
		pInstance->m_bReverse = bReverse;
		pInstance->initData();
	}

	void RevolveDlg::GetRevolveData(int& iUseAngle, double& dStartAngle, double& dEndAngle, int& iRemove, int& iReverse)
	{
		RevolveDlg* pInstance = RevolveDlg::instance();
		iUseAngle = pInstance->m_bUseAngle;
		dStartAngle = pInstance->m_dStartAngle;
		dEndAngle = pInstance->m_dEndAngle;
		iRemove = pInstance->m_bRemove;
		iReverse = pInstance->m_bReverse;
	}

}

