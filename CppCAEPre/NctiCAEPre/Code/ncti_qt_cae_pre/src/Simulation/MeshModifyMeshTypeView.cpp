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

#include "MeshModifyMeshTypeView.h"
#include "ui_MeshModifyMeshTypeView.h"
#include <QMessageBox>

#include "NctiDocElementPubFun.h"
#include "NctiDocument.h"
#include "NctiDisplayModelBody.h"
#include "NctiArgumentObject.h"
#include "NctiCommandManager.h"
#include "NctiDisplayDocCustomContainer.h"

namespace NCTI {
	MeshModifyMeshTypeView::MeshModifyMeshTypeView(NctiDocument* i_pDocument, QWidget* parent) 
        : NctiBaseDialog(parent)
        , ui(new Ui::MeshModifyMeshTypeView)
        , m_document(i_pDocument)
        , m_defaultMeshType(-1)
	{
		setup();
	}

	MeshModifyMeshTypeView::~MeshModifyMeshTypeView()
	{
		delete ui;
	}

	int MeshModifyMeshTypeView::getMode()const 
	{
		int nMode = ui->cb_mode->currentIndex();
		return nMode;
	}

	bool MeshModifyMeshTypeView::beforeAccpet()
	{
		if (m_defaultMeshType == getMode())
			return true;
		NctiBaseModel* pBaseModel = m_document->GetBaseModel();
		if (pBaseModel)
		{
			NctiCommandManager* pComMan = NctiCommandManager::GetCommandManager(pBaseModel);
			if (pComMan)
			{
				NctiArgumentObject argumentObject;
				argumentObject.Setm_meshType((EnumMeshDoc)getMode());
				EnumNctiResult result = pComMan->RunCommand("cmd_ncti_mesh_modify_mesh_type", &argumentObject);
			}
		}
		return true;
	}

	void MeshModifyMeshTypeView::setup()
	{
		auto widget = new QWidget(this);
		ui->setupUi(widget);
		setTitle(QStringLiteral("切换网格引擎"));
		setWidget(widget);

		ui->cb_mode->addItem("Gmsh", EnumMeshDoc::NCTI_MESH_GMSH);
		ui->cb_mode->addItem("MeshGems", EnumMeshDoc::NCTI_MESH_MESHGEMS);
		ui->cb_mode->addItem("PanaMesh", EnumMeshDoc::NCTI_MESH_PANAMESH);
		ui->cb_mode->addItem("Netgen", EnumMeshDoc::NCTI_MESH_NETGEN);

		NctiBaseModel* pBaseModel = m_document->GetBaseModel();
		NctiDisplayDocCustomContainer* pContainer = NctiDocElementPubFun::GetCurrenDocCustom(pBaseModel);
		if (pContainer)
		{
			static std::map<std::string, EnumMeshDoc> map = {
			{"ncti_doc_gmsh_type",EnumMeshDoc::NCTI_MESH_GMSH},
			{"ncti_doc_meshgems_type",EnumMeshDoc::NCTI_MESH_MESHGEMS},
			{"ncti_doc_panamesh_type",EnumMeshDoc::NCTI_MESH_PANAMESH},
			{"ncti_doc_netgen_type",EnumMeshDoc::NCTI_MESH_NETGEN},
			};
			m_defaultMeshType = map[pContainer->GetMeshDocType()];
			ui->cb_mode->setCurrentIndex(m_defaultMeshType);
		}

		//ui->cb_2d->setCurrentIndex(m_option.m_type);
		{
			ui->fm_sel->hide();
		}

        connect(ui->confrimBtn, &QPushButton::clicked, this, [this] {
            if (!beforeAccpet()) {
                return;
            }
            accept();
            Q_EMIT finish();
            });

        connect(ui->cancelBtn, &QPushButton::clicked, this, &MeshModifyMeshTypeView::reject);
	}

	void MeshModifyMeshTypeView::popupMessage(const QString& message, const QString& title)
	{
		QMessageBox::information(nullptr, title, message);
	}
}