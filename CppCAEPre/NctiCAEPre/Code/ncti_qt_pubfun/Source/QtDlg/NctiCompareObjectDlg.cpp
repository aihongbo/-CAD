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

#include "NctiCompareObjectDlg.h"

#include <QTableWidget>
#include <cmath>

#include "NctiAddCentralizeForceDlg.h"
#include "NctiDocElementPubFun.h"
#include "NctiQTPubFun.h"
#include "NctiString.h"
using namespace NCTI;

NctiCompareObjectDlg::NctiCompareObjectDlg(NctiDocument* i_pDocument, QWidget* i_parent)
	: QWidget(i_parent)
	, m_Document(i_pDocument)
{
	this->setWindowTitle("模型对比");
	this->setMinimumWidth(550);
	this->setMinimumHeight(660);
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

NctiCompareObjectDlg::~NctiCompareObjectDlg()
{
}

void NctiCompareObjectDlg::InitData()
{
	m_tableView->clear();
	m_tableView->clearSpans();

	ObjCompareList db = NctiQTPubFun::GetObjectCompareDB(m_Document);

	m_tableView->setColumnCount(db.size() + 1);
	m_tableView->setRowCount(17);
	std::vector<std::string> strCols;
	strCols.push_back("对比项");
	for (int i = 0; i < db.size(); i++)
	{
		strCols.push_back(db[i].strName);
	}
	for (int c = 0; c < strCols.size(); c++)
	{
		QString strCaption = QString::fromStdString(strCols[c]);
		QTableWidgetItem* item = new QTableWidgetItem(strCaption);
		item->setToolTip(strCaption);
		if (c > 0)
			item->setBackground(db[c - 1].color);
		item->setForeground(QColor(255, 255, 255));
		m_tableView->setHorizontalHeaderItem(c, item);
	}
	std::function<QString(const double&, const double&)> GetCompateDoubleStr =[=](const double& d1, const double& d2)
		{
			double dVal1 = std::round(d1 * 1e6) / 1e6;
			double dVal2 = std::round(d2 * 1e6) / 1e6;
			QString str;
			double dVal = dVal1 - dVal2;
			str = QString::fromStdString(NctiString::double_to_string(dVal1));
			str += "\n";
			if (dVal == 0)
				str += "+0";
			else if (dVal > 0)
				str += "+" + QString::fromStdString(NctiString::double_to_string(dVal));
			else
				str +=  QString::fromStdString(NctiString::double_to_string(dVal));
			return str;
			QString colorVal("<p><span style=\"color: white;\">");
			colorVal.append(str);
			colorVal.append("</span></p>");
			//colorVal.append("\n");
			if (dVal == 0)
			{
				colorVal.append("<p><span style=\"color: green;\">");
				colorVal.append("+0");
				colorVal.append("</span></p>");
			}
			else if (dVal > 0)
			{
				colorVal.append("<p><span style=\"color: red;\">");
				colorVal.append("+" + QString::fromStdString(NctiString::double_to_string(dVal)));
				colorVal.append("</span></p>");
			}
			else
			{
				colorVal.append("<p><span style=\"color: red;\">");
				colorVal.append(QString::fromStdString(NctiString::double_to_string(dVal)));
				colorVal.append("</span></p>");
			}
			return colorVal;
		};
	std::function<QString(const int&, const int&)> GetCompateIntStr =[=](const int& d1, const int& d2)
		{
			QString str;
			int dVal = d1 - d2;
			str = QString::fromStdString(NctiString::int_to_string(d1));
			str += "\n";
			if (dVal == 0)
				str += "+0";
			else if (dVal > 0)
				str += "+" + QString::fromStdString(NctiString::int_to_string(dVal));
			else
				str += QString::fromStdString(NctiString::int_to_string(dVal));
			return str;
			QString colorVal("<p><span style=\"color: white;\">");
			colorVal.append(str);
			colorVal.append("</span></p>");
			//colorVal.append("\n");
			if (dVal == 0)
			{
				colorVal.append("<p><span style=\"color: green;\">");
				colorVal.append("+0");
				colorVal.append("</span></p>");
			}
			else if (dVal > 0)
			{
				colorVal.append("<p><span style=\"color: red;\">");
				colorVal.append("+" + QString::fromStdString(NctiString::int_to_string(dVal)));
				colorVal.append("</span></p>");
			}
			else
			{
				colorVal.append("<p><span style=\"color: red;\">");
				colorVal.append(QString::fromStdString(NctiString::int_to_string(dVal)));
				colorVal.append("</span></p>");
			}
			return colorVal;
		};
	std::vector<std::vector<QString>> strRowsVec;
	strRowsVec.push_back({ "Doc","Kernel" ,"Length" ,"Area" ,"Volumn" ,"VERTEX" ,"EDGE" ,"WIRE" ,"FACE" ,"SHELL" ,"SOLID" ,"COMPSOLID" ,"COMPOUND" ,"SHAPE" ,"FIN" ,"LAMINAR_EDGE" ,"MEM_USAGE" });
	for (int i = 0; i < db.size(); i++)
	{
		ObjCompareStruct data = db[i];
		std::vector<QString> rows;
		rows.push_back(QString::fromStdString(data.strDocName));
		rows.push_back(QString::fromStdString(data.strKernel));
		if (i > 0)
		{
			rows.push_back(GetCompateDoubleStr(data.dLen, db[0].dLen));
			rows.push_back(GetCompateDoubleStr(data.dArea, db[0].dArea));
			rows.push_back(GetCompateDoubleStr(data.dVolumn, db[0].dVolumn));
			rows.push_back(GetCompateIntStr(data.iVERTEX, db[0].iVERTEX));
			rows.push_back(GetCompateIntStr(data.iEDGE, db[0].iEDGE));
			rows.push_back(GetCompateIntStr(data.iWIRE, db[0].iWIRE));
			rows.push_back(GetCompateIntStr(data.iFACE, db[0].iFACE));
			rows.push_back(GetCompateIntStr(data.iSHELL, db[0].iSHELL));
			rows.push_back(GetCompateIntStr(data.iSOLID, db[0].iSOLID));
			rows.push_back(GetCompateIntStr(data.iCOMPSOLID, db[0].iCOMPSOLID));
			rows.push_back(GetCompateIntStr(data.iCOMPOUND, db[0].iCOMPOUND));
			rows.push_back(GetCompateIntStr(data.iSHAPE, db[0].iSHAPE));
			rows.push_back(GetCompateIntStr(data.iFIN, db[0].iFIN));
			rows.push_back(GetCompateIntStr(data.iLAMINAR_EDGE, db[0].iLAMINAR_EDGE));
			rows.push_back(GetCompateIntStr(data.iMEM_USAGE, db[0].iMEM_USAGE));
		}
		else
		{
			rows.push_back(QString::fromStdString(NctiString::double_to_string(data.dLen)));
			rows.push_back(QString::fromStdString(NctiString::double_to_string(data.dArea)));
			rows.push_back(QString::fromStdString(NctiString::double_to_string(data.dVolumn)));
			rows.push_back(QString::fromStdString(NctiString::int_to_string(data.iVERTEX)));
			rows.push_back(QString::fromStdString(NctiString::int_to_string(data.iEDGE)));
			rows.push_back(QString::fromStdString(NctiString::int_to_string(data.iWIRE)));
			rows.push_back(QString::fromStdString(NctiString::int_to_string(data.iFACE)));
			rows.push_back(QString::fromStdString(NctiString::int_to_string(data.iSHELL)));
			rows.push_back(QString::fromStdString(NctiString::int_to_string(data.iSOLID)));
			rows.push_back(QString::fromStdString(NctiString::int_to_string(data.iCOMPSOLID)));
			rows.push_back(QString::fromStdString(NctiString::int_to_string(data.iCOMPOUND)));
			rows.push_back(QString::fromStdString(NctiString::int_to_string(data.iSHAPE)));
			rows.push_back(QString::fromStdString(NctiString::int_to_string(data.iFIN)));
			rows.push_back(QString::fromStdString(NctiString::int_to_string(data.iLAMINAR_EDGE)));
			rows.push_back(QString::fromStdString(NctiString::int_to_string(data.iMEM_USAGE)));
		}
		strRowsVec.push_back(rows);
	}
	for (int c = 0; c < strRowsVec.size(); c++)
	{
		for (int r = 0; r < strRowsVec[c].size(); r++)
		{
			QTableWidgetItem* cell = new QTableWidgetItem(strRowsVec[c][r]);
			cell->setTextAlignment(Qt::AlignCenter);
			//cell->setTextColor(QColor(255, 255, 255));
			//cell->setToolTip(strVal);
			m_tableView->setItem(r, c, cell);
			//QLabel* label = new QLabel();
			//label->setTextInteractionFlags(Qt::TextInteractionFlag::TextBrowserInteraction);
			//QPalette palette;
			//palette.setColor(label->foregroundRole(), Qt::white);
			//label->setPalette(palette);
			//label->setAutoFillBackground(true);
			//label->setText(strRowsVec[c][r]);
			//m_tableView->setCellWidget(r, c, label);
		}
	}
	m_tableView->resizeColumnsToContents();
	m_tableView->resizeRowsToContents();
	
}
