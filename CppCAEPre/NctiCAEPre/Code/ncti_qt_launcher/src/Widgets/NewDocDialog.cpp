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

namespace NCTI {
    NewDocDialog::NewDocDialog(QWidget* parent)
        : PopupBaseDialog(parent, false, 42)
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
        ui->comboBox_kernel->addItem("OCC", "OCC");
        ui->comboBox_kernel->addItem("PK", "PK");
        ui->comboBox_kernel->addItem("OD", "OD");
        ui->comboBox_kernel->addItem("PS", "PS");

        listView = new QListView(ui->comboBox_constraint);
        listView->setAlternatingRowColors(true);
        ui->comboBox_constraint->setView(listView);
        ui->comboBox_constraint->setFocusPolicy(Qt::NoFocus);
        ui->comboBox_constraint->addItem("DCM", "DCM");
        ui->comboBox_constraint->addItem("PSCS", "PSCS");
        ui->comboBox_constraint->addItem("HTDCM", "HTGC");

        listView = new QListView(ui->comboBox_mesh);
        listView->setAlternatingRowColors(true);
        ui->comboBox_mesh->setView(listView);
		ui->comboBox_mesh->setFocusPolicy(Qt::NoFocus);
        ui->comboBox_mesh->addItem("Gmsh", "GMSH");
        ui->comboBox_mesh->addItem("MeshGems", "MESHGEMS");
        ui->comboBox_mesh->addItem("PanaMesh", "PANAMESH");
        ui->comboBox_mesh->addItem("Netgen", "NETGEN");

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

    std::tuple<QString, QString, QString> NewDocDialog::GetInfo() const
    {
        return std::tuple<QString, QString, QString>(
            ui->comboBox_kernel->currentData().toString(),
            ui->comboBox_constraint->currentData().toString(),
            ui->comboBox_mesh->currentData().toString()
            );
    }

}

