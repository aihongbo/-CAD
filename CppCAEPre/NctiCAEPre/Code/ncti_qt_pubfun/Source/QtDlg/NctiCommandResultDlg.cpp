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

#include "NctiCommandResultDlg.h"

#include <QTableWidget>
#include <cmath>

#include "NctiAddCentralizeForceDlg.h"
#include "NctiDocElementPubFun.h"
#include "NctiQTPubFun.h"
#include "NctiString.h"
using namespace NCTI;

NctiCommandResultDlg::NctiCommandResultDlg(NctiDocument* i_pDocument, QWidget* i_parent)
    : QWidget(i_parent)
    , m_Document(i_pDocument)
{
    this->setWindowTitle("结果对比");
    this->setMinimumWidth(1080);
    this->setMinimumHeight(600);
    this->setWindowFlags(/*Qt::MSWindowsFixedSizeDialogHint |*/ Qt::Dialog);
    this->setWindowModality(Qt::NonModal);
    m_tableView = new QTableWidget(this);
    //m_tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //m_tableView->verticalHeader()->setVisible(false);
    m_tableView->setWordWrap(true);
    //m_tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    //m_tableView->horizontalHeader()->setStretchLastSection(false);
    //m_tableView->verticalHeader()->setDefaultSectionSize(20);

    QVBoxLayout* VLayout1 = new QVBoxLayout();
    VLayout1->addWidget(m_tableView);

    setLayout(VLayout1);

    InitData();
}

NctiCommandResultDlg::~NctiCommandResultDlg()
{
}

void NctiCommandResultDlg::InitData()
{
    m_tableView->clear();
    m_tableView->clearSpans();

    KernelExecResultList db = NctiQTPubFun::GetInterfaceResult(m_Document);

    std::vector<QString> cloumns = {"DocName",
                                    "Kernel",
                                    "Script",
                                    "Run\nTime",
                                    "run\nresult",
                                    "Error\nInformation",
                                    "Error\nCode",
                                    "CPU\nUsage",
                                    "UsedPhysical\nMemory"};
    int iRow = 0, iMax = 0;
    for (int i = 0; i < db.size(); i++) {
        iRow += db[i].size();
        if (db[i].size() > iMax)
            iMax = db[i].size();
    }
    m_tableView->setColumnCount(cloumns.size());
    m_tableView->setRowCount(iRow);
    for (int c = 0; c < cloumns.size(); c++) {
        QTableWidgetItem* item = new QTableWidgetItem(cloumns[c]);
        //if (c > 0)
        //	item->setBackgroundColor(db[c - 1].color);
        //item->setTextColor(QColor(255, 255, 255));
        m_tableView->setHorizontalHeaderItem(c, item);
    }

    int iNum = 0;
    for (int g = 0; g < iMax; g++) {
        for (int i = 0; i < db.size(); i++) {
            if (db[i].size() <= g)
                continue;
            KernelExecResult& data = db[i][g];
            std::vector<QString> rows;
            rows.push_back(QString::fromStdString(data.strDocName));
            rows.push_back(QString::fromStdString(data.strKernel));
            rows.push_back(QString::fromStdString(data.Script));
            rows.push_back(QString::fromStdString(NctiString::double_to_string(data.time)));
            rows.push_back(QString::fromStdString(NctiString::int_to_string(data.result)));
            rows.push_back(QString::fromStdString(data.error));
            //rows.push_back(QString::fromStdString(data.errorArgument));
            rows.push_back(QString::fromStdString(NctiString::int_to_string(data.funcErrorCode)));
            rows.push_back(QString::fromStdString(NctiString::int_to_string(data.cpuUsage)));
            rows.push_back(QString::fromStdString(NctiString::int_to_string(data.usedPhysicalMemory)));

            for (int c = 0; c < rows.size(); c++) {
                QTableWidgetItem* cell = new QTableWidgetItem(rows[c]);
                cell->setTextAlignment(Qt::AlignCenter);
                //cell->setTextColor(QColor(255, 255, 255));
                cell->setToolTip(rows[c]);
                m_tableView->setItem(iNum, c, cell);
                //QLabel* label = new QLabel();
                //label->setTextInteractionFlags(Qt::TextInteractionFlag::TextBrowserInteraction);
                //QPalette palette;
                //palette.setColor(label->foregroundRole(), Qt::white);
                //label->setPalette(palette);
                //label->setAutoFillBackground(true);
                //label->setText(strRowsVec[c][r]);
                //m_tableView->setCellWidget(r, c, label);
            }
            iNum++;
        }
    }
    m_tableView->resizeColumnsToContents();
    m_tableView->resizeRowsToContents();
}
