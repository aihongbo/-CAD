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

#include "WorkPlaneDlg.h"
#include "NctiBaseModel.h"
#include "NctiCommandManager.h"
#include "NctiCommand.h"
#include "NctiMeasuringTool.h"

#include <QComboBox>
#include <QPushButton>
#include <QListView>
#include <QGroupBox>
#include <QLineEdit>
#include <QLayout>
#include <QLabel>
#include "NctiPosition.h"

namespace NCTI
{
	WorkPlaneDlg* WorkPlaneDlg::mInstance = nullptr;

	void WorkPlaneDlg::GetPositionFun(const NctiPosition& i_pt)
	{
		WorkPlaneDlg* pWorkPlaneDlg = WorkPlaneDlg::instance();
		if (pWorkPlaneDlg)
		{
			pWorkPlaneDlg->m_OriginX = i_pt.x();
			pWorkPlaneDlg->m_OriginY = i_pt.y();
			pWorkPlaneDlg->m_OriginZ = i_pt.z();
			pWorkPlaneDlg->initData();
			pWorkPlaneDlg->PreResult();
		}
	}

	WorkPlaneDlg::WorkPlaneDlg(NctiBaseModel* pBaseModel, QWidget* parent)
        : NctiBaseDialog(parent)
        , m_pBaseModel(pBaseModel)
    {
        init();
		m_OriginX = 0.0;
		m_OriginY = 0.0;
		m_OriginZ = 0.0;
		m_dAngleX = 0.0;
		m_dAngleY = 0.0;
		m_dAngleZ = 1.0;
		NctiMeasuringTool::instance()->SetCalPositionCallback(WorkPlaneDlg::GetPositionFun);
		NctiMeasuringTool::instance()->SetCalMidPositionCallback(WorkPlaneDlg::GetPositionFun);
		NctiMeasuringTool::instance()->SetCalCenterCallback(WorkPlaneDlg::GetPositionFun);
    }

    WorkPlaneDlg::~WorkPlaneDlg()
    {
		NctiMeasuringTool::instance()->ResetAll();
    }

    void WorkPlaneDlg::init()
    {
		auto widget = new QFrame(this);
		widget->setObjectName("WorkPlaneDlg");
		//setTitle(QStringLiteral("WorkPlane"));
		setTitle(QStringLiteral("工作平面"));
		//setTitle(QStringLiteral("WorkPlane"), 30, { 23,0,23,0 });
		this->layout()->setContentsMargins(0, 0, 0, 0);
		this->setWindowFlags(this->windowFlags() | Qt::WindowStaysOnTopHint | Qt::Tool);
		//this->setStyleSheet("background-color: white;");

		QDoubleValidator* latitude = new QDoubleValidator(this);
		latitude->setNotation(QDoubleValidator::StandardNotation);
		latitude->setBottom(0.0);

		m_EditOX = new QLineEdit("0", this);
		m_EditOX->setValidator(latitude);
		m_EditOY = new QLineEdit("0", this);
		m_EditOY->setValidator(latitude);
		m_EditOZ = new QLineEdit("0", this);
		m_EditOZ->setValidator(latitude);

		m_EditRX = new QLineEdit("0", this);
		m_EditRX->setValidator(latitude);
		m_EditRY = new QLineEdit("0", this);
		m_EditRY->setValidator(latitude);
		m_EditRZ = new QLineEdit("0", this);
		m_EditRZ->setValidator(latitude);

		QGroupBox* group1 = new QGroupBox(QStringLiteral("原点："), widget);
		QGroupBox* group2 = new QGroupBox(QStringLiteral("旋转："), widget);
		group1->setObjectName("groupBox_o");
		group2->setObjectName("groupBox_r");

		auto labelOX = new QLabel(QStringLiteral("X："), this);
		auto labelOY = new QLabel(QStringLiteral("Y："), this);
		auto labelOZ = new QLabel(QStringLiteral("Z："), this);

		auto labelRX = new QLabel(QStringLiteral("X："), this);
		auto labelRY = new QLabel(QStringLiteral("Y："), this);
		auto labelRZ = new QLabel(QStringLiteral("Z："), this);

		QVBoxLayout* VLayout1 = new QVBoxLayout(group1);
		VLayout1->setSpacing(10);
		QHBoxLayout* HLayout = new QHBoxLayout();
		VLayout1->addSpacing(8);
		HLayout->addSpacing(3);
		HLayout->addWidget(labelOX);
		HLayout->addWidget(m_EditOX);
		VLayout1->addLayout(HLayout);
		HLayout = new QHBoxLayout();
		HLayout->addSpacing(3);
		HLayout->addWidget(labelOY);
		HLayout->addWidget(m_EditOY);
		VLayout1->addLayout(HLayout);
		HLayout = new QHBoxLayout();
		HLayout->addSpacing(3);
		HLayout->addWidget(labelOZ);
		HLayout->addWidget(m_EditOZ);
		VLayout1->addLayout(HLayout);

		QVBoxLayout* VLayout2 = new QVBoxLayout(group2);
		VLayout2->setSpacing(10);
		HLayout = new QHBoxLayout();
		VLayout2->addSpacing(8);
		HLayout->addSpacing(3);
		HLayout->addWidget(labelRX);
		HLayout->addWidget(m_EditRX);
		VLayout2->addLayout(HLayout);
		HLayout = new QHBoxLayout();
		HLayout->addSpacing(3);
		HLayout->addWidget(labelRY);
		HLayout->addWidget(m_EditRY);
		VLayout2->addLayout(HLayout);
		HLayout = new QHBoxLayout();
		HLayout->addSpacing(3);
		HLayout->addWidget(labelRZ);;
		HLayout->addWidget(m_EditRZ);
		VLayout2->addLayout(HLayout);

		//把两个group和预览键放到一个widget里面去
		QWidget* groupWidget = new QWidget(widget);
		groupWidget->setObjectName("group_Widget");
		QVBoxLayout* groupWidgetLayout = new QVBoxLayout(groupWidget);
		groupWidgetLayout->setContentsMargins(0, 17, 0, 0);
		groupWidgetLayout->addWidget(group1);
		groupWidgetLayout->addSpacing(4);
		groupWidgetLayout->addWidget(group2);

		m_BtnOK = new QPushButton(this);
		m_BtnCancel = new QPushButton(this);
		m_BtnPre = new QPushButton(this);
		m_BtnOK->setText(QStringLiteral("确定"));
		m_BtnCancel->setText(QStringLiteral("取消"));
		m_BtnPre->setText(QStringLiteral("预览"));
		HLayout = new QHBoxLayout();
		HLayout->addSpacing(9);
		HLayout->addWidget(m_BtnPre);
		HLayout->addSpacing(9);
		groupWidgetLayout->addLayout(HLayout);
		groupWidgetLayout->addSpacing(14);
		m_BtnOK->setObjectName("work-plane-ok");
		m_BtnCancel->setObjectName("work-plane-cancel");
		m_BtnPre->setObjectName("work-plane-preview");

		QHBoxLayout* HLayout3 = new QHBoxLayout();
		HLayout3->addStretch();
		HLayout3->addWidget(m_BtnCancel);
		HLayout3->addWidget(m_BtnOK);
		HLayout3->addSpacing(9);

		//HLayout3->addStretch();

		QVBoxLayout* layoutMain = new QVBoxLayout(widget);
		layoutMain->setContentsMargins(2, 0, 1, 0);
		layoutMain->addWidget(groupWidget);
		layoutMain->addSpacing(6);
		layoutMain->addLayout(HLayout3);
		layoutMain->addStretch();
		setLayout(layoutMain);
		connect(m_BtnOK, SIGNAL(clicked(bool)), this, SLOT(ClickOk(bool)));
		connect(m_BtnCancel, SIGNAL(clicked(bool)), this, SLOT(ClickCancel(bool)));
		connect(m_BtnPre, SIGNAL(clicked(bool)), this, SLOT(ClickPre(bool)));

		connect(this->getCloseButton(), &QPushButton::clicked, this, &WorkPlaneDlg::ClickCancel);

		setWidget(widget);
	}

	void WorkPlaneDlg::initData()
	{
		m_EditOX->setText(QString("%1").arg(m_OriginX));
		m_EditOY->setText(QString("%1").arg(m_OriginY));
		m_EditOZ->setText(QString("%1").arg(m_OriginZ));
		m_EditRX->setText(QString("%1").arg(m_dAngleX));
		m_EditRY->setText(QString("%1").arg(m_dAngleY));
		m_EditRZ->setText(QString("%1").arg(m_dAngleZ));
	}

	void WorkPlaneDlg::ClickCancel(bool boo)
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
		//close();
	}

	void WorkPlaneDlg::ClickPre(bool boo)
	{
		PreResult();
	}

	void WorkPlaneDlg::PreResult()
	{
		if (m_pBaseModel)
		{
			NctiCommandManager* pCommandManage = NctiCommandManager::GetCommandManager(m_pBaseModel);
			if (pCommandManage)
			{
				m_OriginX = m_EditOX->text().toDouble();
				m_OriginY = m_EditOY->text().toDouble();
				m_OriginZ = m_EditOZ->text().toDouble();
				m_dAngleX = m_EditRX->text().toDouble();
				m_dAngleY = m_EditRY->text().toDouble();
				m_dAngleZ = m_EditRZ->text().toDouble();
				pCommandManage->ProcessUpdate();
			}
		}
	}

	void WorkPlaneDlg::ClickOk(bool boo)
	{
		m_OriginX = m_EditOX->text().toDouble();
		m_OriginY = m_EditOY->text().toDouble();
		m_OriginZ = m_EditOZ->text().toDouble();
		m_dAngleX = m_EditRX->text().toDouble();
		m_dAngleY = m_EditRY->text().toDouble();
		m_dAngleZ = m_EditRZ->text().toDouble();
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
		//close();
	}

	WorkPlaneDlg* WorkPlaneDlg::instance()
	{
		return mInstance;
	}

	void WorkPlaneDlg::SetInstance(WorkPlaneDlg* pWorkPlaneDlg)
	{
		mInstance = pWorkPlaneDlg;
	}

	void WorkPlaneDlg::ShowDialog(NctiBaseModel* pBaseModel, QWidget* parent)
	{
		WorkPlaneDlg* pInstance = WorkPlaneDlg::instance();
		if (pInstance == nullptr)
		{
			pInstance = new WorkPlaneDlg(pBaseModel, parent);
			pInstance->show();
			WorkPlaneDlg::SetInstance(pInstance);
		}
		else
		{
			if(pInstance->isHidden())
				pInstance->show();
		}
		pInstance->initData();
	}

	void WorkPlaneDlg::DeleteDialog()
	{
		WorkPlaneDlg* pWorkPlaneDlg = WorkPlaneDlg::instance();
		if (pWorkPlaneDlg)
        {
            delete pWorkPlaneDlg;
		}
		WorkPlaneDlg::SetInstance(NULL);
	}

	void WorkPlaneDlg::SetCoordinate(double dOriginX, double dOriginY, double dOriginZ, double dAngleX, double dAngleY, double dAngleZ)
	{
		WorkPlaneDlg* pWorkPlaneDlg = WorkPlaneDlg::instance();
		pWorkPlaneDlg->m_OriginX = dOriginX;
		pWorkPlaneDlg->m_OriginY = dOriginY;
		pWorkPlaneDlg->m_OriginZ = dOriginZ;
		pWorkPlaneDlg->m_dAngleX = dAngleX;
		pWorkPlaneDlg->m_dAngleY = dAngleY;
		pWorkPlaneDlg->m_dAngleZ = dAngleZ;
		pWorkPlaneDlg->initData();
	}

	void WorkPlaneDlg::GetCoordinate(double& dOriginX, double& dOriginY, double& dOriginZ, double& dAngleX, double& dAngleY, double& dAngleZ)
	{
		WorkPlaneDlg* pWorkPlaneDlg = WorkPlaneDlg::instance();
		dOriginX = pWorkPlaneDlg->m_OriginX;
		dOriginY = pWorkPlaneDlg->m_OriginY;
		dOriginZ = pWorkPlaneDlg->m_OriginZ;
		dAngleX = pWorkPlaneDlg->m_dAngleX;
		dAngleY = pWorkPlaneDlg->m_dAngleY;
		dAngleZ = pWorkPlaneDlg->m_dAngleZ;
	}
}

