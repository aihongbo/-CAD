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

#include "MeshSettingView.h"
#include "ui_MeshSettingView.h"
#include <QMessageBox>

#include "NctiDocElementPubFun.h"
#include "NctiDisplayGridMesh.h"
#include "NctiDisplayModelBody.h"
#include "NctiDisplayPolyMesh.h"

namespace NCTI {
	MeshSettingView::MeshSettingView(Ncti_Mesh_Option op,NctiDocument* i_pDocument, QWidget* parent,bool sel, int meshType) 
        : NctiBaseDialog(parent)
        , ui(new Ui::MeshSettingView)
        , m_document(i_pDocument)
	{
		m_sel = sel;
		m_option = op;
		m_meshType = meshType;
		setup();
	}

	MeshSettingView::~MeshSettingView()
	{
		delete ui;
	}

	std::vector<NctiDisplayObject*> MeshSettingView::getObjects() const
	{
		return m_objs;
	}

	const Ncti_Mesh_Option& MeshSettingView::getMeshOption() const
	{
		return m_option;
	}

	bool MeshSettingView::beforeAccpet()
	{
		Ncti_Double max = 0;
		if (!getMax(max)) {
			popupMessage(QStringLiteral("网格尺寸无效"));
			return false;
		}
		if (m_sel)
		{
            int ct = 0;
            if (m_objs.empty()) {
                popupMessage(QStringLiteral("选取对象无效"));
                return false;
            }
		}

		m_option.m_size = max;
		m_option.m_type = ui->cb_2d->currentIndex();
		m_option.m_high = ui->cb_high->isChecked();
        m_option.m_angleTol = ui->sb_angle->value();
        m_option.m_autoCurvature = ui->sb_auto->value();
		m_option.m_bParallel = ui->cb_high_2->isChecked();
		return true;
	}

	void MeshSettingView::setup()
	{
		auto widget = new QWidget(this);
		ui->setupUi(widget);
		setTitle(QStringLiteral("网格设置"));
		setWidget(widget);
		//ui->qw_extra->hide();

		ui->le_size->setText(QString::number(m_option.m_size));
		ui->cb_2d->setCurrentIndex(m_option.m_type);
		ui->cb_high->setChecked(m_option.m_high);
        ui->sb_angle->setValue(m_option.m_angleTol);
        ui->sb_auto->setValue(m_option.m_autoCurvature);
		ui->cb_high_2->setChecked(m_option.m_bParallel);
		if (m_sel)
		{
			updateSelected();
            ui->pb_select->setCheckable(true);
            connect(ui->pb_select, &QPushButton::clicked,this, &MeshSettingView::updateSelected);
		}
		else {
			ui->fm_sel->hide();
		}
		if (m_meshType != 1 && m_meshType != 2) {
			ui->label->hide();
			ui->cb_high_2->hide();
		}

        connect(ui->confrimBtn, &QPushButton::clicked, this, [this] {
            if (!beforeAccpet()) {
                return;
            }
            accept();
            Q_EMIT finish();
            });

        connect(ui->cancelBtn, &QPushButton::clicked, this, &MeshSettingView::reject);
	}

	bool MeshSettingView::getMax(Ncti_Double& max)
	{
		bool ok = false;
		auto value = ui->le_size->text().toDouble(&ok);
		if (ok) {
			max = value;
		}
		return ok;
	}

	void MeshSettingView::updateSelected()
	{
		std::vector<NctiDisplayObject*> tmp;
		m_objs.clear();
        std::vector<NCTI_MODEL_TAG> cellVec;
        NctiDocElementPubFun::GetDisplayObjectFromSelManager(m_document, tmp, cellVec);
		std::map<NctiDisplayObject*, int> map;
		for (auto c: tmp)
		{
			NctiDisplayObject* obj = nullptr;
            if (c->IsTypeName(NctiDisplayGridMesh::ID)) {
                NctiDisplayGridMesh* pSurfaceMesh = (NctiDisplayGridMesh*)c;
                obj = pSurfaceMesh->GetModelBody();
				if (obj)
				{
					NctiDisplayObject* tmp{nullptr};
					NctiDocElementPubFun::GetObjectListByName(m_document, NctiDisplayModelBody::ID, obj->GetObjName(), tmp);
					if (tmp == nullptr)
					{
						popupMessage(QStringLiteral("网格几何不存在！"));
						obj = nullptr;
					}
				}
            }
            else if (c->IsTypeName(NctiDisplayModelBody::ID))
				obj = c;
			else if (c->IsTypeName(NctiDisplayPolyMesh::ID))
				obj = c;
			if (map.find(obj) != map.end())
				continue;
			if (obj)
			{
				map[obj] = 1;
				m_objs.push_back(obj);
			}
		}

        ui->lb_count->setText(QString::number(m_objs.size()));
	}

	void MeshSettingView::popupMessage(const QString& message, const QString& title)
	{
		QMessageBox::information(nullptr, title, message);
	}
}