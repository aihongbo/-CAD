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

#include "MeshQualitySettingView.h"
#include "ui_MeshQualitySettingView.h"
#include <QMessageBox>

#include "NctiDocElementPubFun.h"
#include "NctiDisplayGridMesh.h"
#include "NctiDisplayModelBody.h"

namespace NCTI {
	MeshQualitySettingView::MeshQualitySettingView(NctiDocument* i_pDocument, QWidget* parent,bool sel) 
        : NctiBaseDialog(parent)
        , ui(new Ui::MeshQualitySettingView)
        , m_document(i_pDocument)
	{
		m_sel = sel;
		setup();
	}

	MeshQualitySettingView::~MeshQualitySettingView()
	{
		delete ui;
	}

	std::vector<NctiDisplayObject*> MeshQualitySettingView::getObjects() const
	{
		return m_objs;
	}

	NctiDisplayObject* MeshQualitySettingView::getObject()const
	{
		if (m_objs.empty())
			return nullptr;
		else
		{
			return m_objs[0];
		}
	}

	int MeshQualitySettingView::getMode()const ////0:长宽比 1:扭曲度 2:雅克比 3:最小角度 4:最大角度
	{
		int nMode = ui->cb_mode->currentIndex();
		return nMode;
	}

	bool MeshQualitySettingView::beforeAccpet()
	{
		if (m_sel)
		{
            int ct = 0;
            if (m_objs.empty()) {
                popupMessage(QStringLiteral("选取对象无效"));
                return false;
            }
			if (m_objs.size() > 1)
			{
				popupMessage(QStringLiteral("只能选取一个对象"));
				return false;
			}
		}
		return true;
	}

	void MeshQualitySettingView::setup()
	{
		auto widget = new QWidget(this);
		ui->setupUi(widget);
		setTitle(QStringLiteral("网格质量"));
		setWidget(widget);
		QStringList strModeNameList;
		strModeNameList << "长宽比";
		strModeNameList << "扭曲度";
		strModeNameList << "雅克比";
		strModeNameList << "最小角度";
		strModeNameList << "最大角度";
		ui->cb_mode->addItems(strModeNameList);
		ui->cb_mode->setCurrentText(strModeNameList[0]);

		//ui->cb_2d->setCurrentIndex(m_option.m_type);
		if (m_sel)
		{
			updateSelected();
            ui->pb_select->setCheckable(true);
            connect(ui->pb_select, &QPushButton::clicked,this, &MeshQualitySettingView::updateSelected);
		}
		else {
			ui->fm_sel->hide();
		}

        connect(ui->confrimBtn, &QPushButton::clicked, this, [this] {
            if (!beforeAccpet()) {
                return;
            }
            accept();
            Q_EMIT finish();
            });

        connect(ui->cancelBtn, &QPushButton::clicked, this, &MeshQualitySettingView::reject);
	}

	void MeshQualitySettingView::updateSelected()
	{
		std::vector<NctiDisplayObject*> tmp;
		m_objs.clear();
        std::vector<NCTI_MODEL_TAG> cellVec;
        NctiDocElementPubFun::GetDisplayObjectFromSelManager(m_document, tmp, cellVec);
		for (auto c: tmp)
		{
			NctiDisplayObject* obj = nullptr;
            if (c->IsTypeName(NctiDisplayGridMesh::ID)) 
			{
				obj = c;
                //NctiDisplayGridMesh* pSurfaceMesh = (NctiDisplayGridMesh*)c;
            }
           
			if (obj)
				m_objs.push_back(obj);
		}

        ui->lb_count->setText(QString::number(m_objs.size()));
	}

	void MeshQualitySettingView::popupMessage(const QString& message, const QString& title)
	{
		QMessageBox::information(nullptr, title, message);
	}
}