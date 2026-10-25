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

#include "NctiDCM3AssemblyDlg.h"

#include "NctiAddCentralizeForceDlg.h"
#include "NctiDocElementPubFun.h"
#include "NctiDocument.h"
#include "NctiDCM3BaseWidget.h"
#include "NctiDCM3SingleGeometryWidget.h"
#include "NctiDCM3TwoGeometriesWidget.h"
#include "NctiPyArgObject.h"
using namespace NCTI;
using Mode = NctiDCM3SingleGeometryWidget::NctiMode;
NctiDCM3AssemblyDlg::NctiDCM3AssemblyDlg(QWidget* i_parent)
	:NctiDCM3BaseWidget(nullptr, i_parent)
	, m_ui(new Ui::NctiDCM3Assembly)
	, m_contentWidget(nullptr)
{
	m_ui->setupUi(this);
	this->setWindowFlags(Qt::WindowStaysOnTopHint | Qt::Dialog);
	this->setWindowModality(Qt::NonModal);
	this->adjustSize();

	connect(m_ui->pushButton_OK, SIGNAL(clicked()), this, SLOT(onOk()));
	connect(m_ui->pushButton_Cancel, SIGNAL(clicked()), this, SLOT(onCancel()));
}

NctiDCM3AssemblyDlg::~NctiDCM3AssemblyDlg()
{
	NCTI_DELETE m_ui;
}

bool NCTI::NctiDCM3AssemblyDlg::init(PyObject* i_args)
{
	this->setWindowTitle(QString("装配约束"));
	//this->setMinimumSize(QSize(200, 50));
	NctiPyArgObject pyArg(i_args);

	Ncti_LongLong size = pyArg.Size();// PyTuple_Size(i_args);
	if (size < 3)
		return false;

	long docID;
	long dim_type;
	Mode mode = Mode::NCTI_MODE_NEW;
	std::string dimName;
	if (!pyArg.GetLong(1, docID))
		return false;
	NctiDocument* pDocument = NctiDocumentManager::instance()->GetDocument(docID);
	if (pDocument == nullptr)
		return false;
	m_pDocument = pDocument;

	if (!pyArg.GetLong(2, dim_type))
		return false;
	if (size > 3)
	{
		long value;
		if (!pyArg.GetLong(3, value))
			return false;
		mode = (Mode)value;
	}
	if (size > 4)
	{
		if (!pyArg.GetStr(4, dimName))
			return false;
	}
	
	clearLayout(m_ui->contentLayout);
	m_contentWidget = nullptr;

	static std::map<ncti_DCM3_d_type, QString> sTitleMap
	{
		{NCTI_DCM3_DISTANCE, "距离约束"},
		{NCTI_DCM3_ANGLE, "角度约束"},
		{NCTI_DCM3_COINCIDENT, "重合约束"},
		{NCTI_DCM3_PERPENDICULAR, "垂直约束"},
		{NCTI_DCM3_PARALLEL, "平行约束"},
		{NCTI_DCM3_CONCENTRIC, "同心约束"}
	};
	QString title;
	switch (dim_type)
	{
	case -1://fixed
	{
		m_contentWidget = new NctiDCM3SingleGeometryWidget(m_pDocument, dim_type, mode, dimName.c_str());
		title = QString("固定");
		break;
	}
	default:
		m_contentWidget = new NctiDCM3TwoGeometriesWidget(m_pDocument, dim_type, mode, dimName.c_str());
		title = sTitleMap[(ncti_DCM3_d_type)dim_type];
		break;
	}

	if (m_contentWidget)
	{
		m_ui->contentLayout->addWidget(m_contentWidget);
		if (!title.isEmpty())
			this->setWindowTitle(title);
	}
	

	return true;
}

void NCTI::NctiDCM3AssemblyDlg::execute()
{
	if (m_contentWidget)
		m_contentWidget->execute();
}

NctiDCM3AssemblyDlg* NCTI::NctiDCM3AssemblyDlg::Instance()
{
	static NctiDCM3AssemblyDlg* instance = nullptr;
	if (instance == nullptr)
		instance = new NctiDCM3AssemblyDlg;
	return instance;
}

void NCTI::NctiDCM3AssemblyDlg::clearLayout(QLayout* i_layout)
{
	QLayoutItem* child;
	while ((child = i_layout->takeAt(0)) != nullptr) {
		// 如果是控件
		if (child->widget()) {
			child->widget()->setParent(nullptr);
			child->widget()->deleteLater();
		}
		// 如果是子布局
		else if (child->layout()) {
			clearLayout(child->layout());
		}
		delete child;
	}
}

void NctiDCM3AssemblyDlg::onOk()
{
	execute();
}

void NctiDCM3AssemblyDlg::onCancel()
{
	this->hide();
}