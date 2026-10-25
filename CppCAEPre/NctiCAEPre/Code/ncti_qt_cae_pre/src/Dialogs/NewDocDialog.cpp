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

#include "NewDocDialog.h"

#include <QListView>
#include "ui_NewDocDialogContent.h"

#include "ncti_base.h"

namespace NCTI {
NewDocDialog::NewDocDialog(QWidget* parent)
    : NctiBaseDialog(parent, TitleBarHeight{42})
    , ui(new Ui::NewDocDialogContent)

{
    init();
}

NewDocDialog::~NewDocDialog()
{
    delete ui;
}

void NewDocDialog::init()
{
    auto widget = new QWidget(this);
    ui->setupUi(widget);

    QListView* listView = new QListView(ui->comboBox_kernel);
    listView->setAlternatingRowColors(true);
    ui->comboBox_kernel->setView(listView);
    ui->comboBox_kernel->setFocusPolicy(Qt::NoFocus);
    ui->comboBox_kernel->addItem("OCC", EnumModelDoc::NCTI_GEOM_OCC);
    ui->comboBox_kernel->addItem("PK", EnumModelDoc::NCTI_GEOM_PK);
    ui->comboBox_kernel->addItem("OD", EnumModelDoc::NCTI_GEOM_OD);
    ui->comboBox_kernel->addItem("PS", EnumModelDoc::NCTI_GEOM_PS);
    ui->comboBox_kernel->addItem("IDEE", EnumModelDoc::NCTI_GEOM_IDEE);
    ui->comboBox_kernel->addItem("HOOPSExchange", EnumModelDoc::NCTI_GEOM_HC);
    ui->comboBox_kernel->addItem("OTHER", EnumModelDoc::NCTI_GEOM_OTHER);

    listView = new QListView(ui->comboBox_constraint);
    listView->setAlternatingRowColors(true);
    ui->comboBox_constraint->setView(listView);
    ui->comboBox_constraint->setFocusPolicy(Qt::NoFocus);
    ui->comboBox_constraint->addItem("DCM", EnumGCSDoc::NCTI_GCS_DCM);
    ui->comboBox_constraint->addItem("PSCS", EnumGCSDoc::NCTI_GCS_PSCS);
    ui->comboBox_constraint->addItem("HTDCM", EnumGCSDoc::NCTI_GCS_HTGC);

    listView = new QListView(ui->comboBox_mesh);
    listView->setAlternatingRowColors(true);
    ui->comboBox_mesh->setView(listView);
    ui->comboBox_mesh->setFocusPolicy(Qt::NoFocus);
    ui->comboBox_mesh->addItem("Gmsh", EnumMeshDoc::NCTI_MESH_GMSH);
    ui->comboBox_mesh->addItem("MeshGems", EnumMeshDoc::NCTI_MESH_MESHGEMS);
    ui->comboBox_mesh->addItem("PanaMesh", EnumMeshDoc::NCTI_MESH_PANAMESH);
    ui->comboBox_mesh->addItem("Netgen", EnumMeshDoc::NCTI_MESH_NETGEN);

    connect(ui->pushButton_ok, &QPushButton::clicked, this, &QDialog::accept);
    ui->pushButton_ok->setDefault(true);
    ui->pushButton_ok->setAutoDefault(true);

    setTitle(QStringLiteral("创建文档"));
    setWidget(widget);
}

int NewDocDialog::GetGeoKernelIndex()
{
    return ui->comboBox_kernel->currentIndex();
}

int NewDocDialog::GetGeoConstraintIndex()
{
    return ui->comboBox_constraint->currentIndex();
}

std::tuple<int, int, int> NewDocDialog::GetInfo() const
{
    return std::tuple<int, int, int>(ui->comboBox_kernel->currentData().toInt(),
                                     ui->comboBox_constraint->currentData().toInt(),
                                     ui->comboBox_mesh->currentData().toInt());
}

} // namespace NCTI
