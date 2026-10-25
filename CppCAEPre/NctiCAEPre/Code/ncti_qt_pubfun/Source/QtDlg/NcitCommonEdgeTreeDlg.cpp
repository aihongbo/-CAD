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

#include "NcitCommonEdgeTreeDlg.h"

#include <QVBoxLayout>
#include <QPushButton>
#include <QTreeWidgetItem>
#include <QString>

#include <NctiDocument.h>
#include <NctiBaseModel.h>
#include <NctiBaseView.h>
#include <NctiDocElementPubFun.h>
#include <NctiPosition.h>
#include "NctiPythonTool.h"

namespace NCTI
{
	NcitCommonEdgeTreeDlg::NcitCommonEdgeTreeDlg(QWidget* parent)
		: QDialog(parent)
		, m_TreeWidget(nullptr)
		, m_DocID(-1)
	{
	}

	NcitCommonEdgeTreeDlg::~NcitCommonEdgeTreeDlg()
    {
    }

	bool NcitCommonEdgeTreeDlg::init(PyObject* i_args)
	{
		this->setWindowTitle(QString("共边"));
		resize(300, 400);
		QVBoxLayout* layoutMain = new QVBoxLayout(this);
		m_TreeWidget = new QTreeWidget(this);
		m_TreeWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
		layoutMain->addWidget(m_TreeWidget);
		this->setLayout(layoutMain);
		m_TreeWidget->setColumnCount(1);
		m_TreeWidget->setHeaderHidden(true);

		layoutMain->setContentsMargins(10, 0, 10, 10);
		connect(m_TreeWidget, &QTreeWidget::itemClicked, this, &NcitCommonEdgeTreeDlg::onItemClicked);
		Ncti_LongLong size = NctiPyCB.Size(i_args);//PyTuple_Size(i_args);
		if (size < 3)
			return false;
		PyObject* arg = NctiPyCB.GetTupleItem(i_args, 1);//PyTuple_GetItem(i_args, 1);
		//if (!PyLong_Check(arg))
		if (!NctiPyCB.IsLong(arg))
			return false;
		m_DocID = NctiPyCB.GetLong(arg);//PyLong_AsLong(arg);
		NctiDocument* pDocument = NctiDocumentManager::instance()->GetDocument(m_DocID);
		if (pDocument == nullptr)
			return false;

		arg = NctiPyCB.GetTupleItem(i_args, 2);//PyTuple_GetItem(i_args, 2);
		//if (!PyDict_Check(arg))
		if (!NctiPyCB.IsDict(arg))
			return false;

		Ncti_Pysize pos = 0;
		PyObject* key, * value;
		//while (PyDict_Next(arg, &pos, &key, &value))
		while (NctiPyCB.GetDictNext(arg, pos, key, value))
		{
			//if (PyUnicode_Check(key) && PyDict_Check(value))
			if (NctiPyCB.IsUnicode(key) && NctiPyCB.IsDict(value))
			{
				QString strBodyName = NctiPyCB.GetUnicodeStr(key);//PyUnicode_AsUTF8(key);
				QString strNameLv1 = QString("实体[%1]").arg(strBodyName);

				QTreeWidgetItem* firstItem = new QTreeWidgetItem(m_TreeWidget);
				firstItem->setText(0, strNameLv1);
				ItemEdgeData data1;
				data1.ModelName = strBodyName;

				Ncti_Pysize cPos = 0;
				PyObject* cKey, * cValue;
				//while (PyDict_Next(value, &cPos, &cKey, &cValue))
				while (NctiPyCB.GetDictNext(value, cPos, cKey, cValue))
				{
					//if (PyLong_Check(cKey) && PyList_Check(cValue))
					if (NctiPyCB.IsLong(cKey) && NctiPyCB.IsList(cValue))
					{
						long nCoNum = NctiPyCB.GetLong(cKey);//PyLong_AsLong(cKey);
						Ncti_LongLong len = NctiPyCB.GetListSize(cValue);//PyList_Size(cValue);
						QList<long> nEdgeIdList;
						for (int i = 0; i < len; ++i)
						{
							PyObject* item = NctiPyCB.GetListItem(cValue, i);//PyList_GetItem(cValue, i);
							//if (PyLong_Check(item))
							if (NctiPyCB.IsLong(item))
							{
								//nEdgeIdList.append(PyLong_AsLong(item));
								nEdgeIdList.append(NctiPyCB.GetLong(item));
							}
						}
						QTreeWidgetItem* secodeItem = new QTreeWidgetItem(firstItem);
						QString strNameLv2;
						if (nCoNum == 1)
							strNameLv2 = QString("单边");
						else
							strNameLv2 = QString("共%1边").arg(nCoNum);
						secodeItem->setText(0, strNameLv2);
						ItemEdgeData data2;
						data2.ModelName = strBodyName;

						std::sort(nEdgeIdList.begin(), nEdgeIdList.end());
						for (int i = 0; i < nEdgeIdList.size(); i++)
						{
							int nEdgeId = nEdgeIdList.at(i);

							ItemEdgeData data3;
							data3.ModelName = strBodyName;
							QTreeWidgetItem* thirdItem = new QTreeWidgetItem(secodeItem);
							QString strNameLv3 = QString("边[%1]").arg(nEdgeId);;

							long cellID = nEdgeId;
							data1.CellIDVec.push_back(cellID);
							data2.CellIDVec.push_back(cellID);
							data3.CellIDVec.push_back(cellID);

							thirdItem->setText(0, strNameLv3);
							thirdItem->setData(0, Qt::UserRole, QVariant::fromValue(data3));
						}
						secodeItem->setData(0, Qt::UserRole, QVariant::fromValue(data2));
					}
				}
				firstItem->setData(0, Qt::UserRole, QVariant::fromValue(data1));
			}
		}

		m_TreeWidget->expandToDepth(0);
		return true;
	}

	void NcitCommonEdgeTreeDlg::onItemClicked(QTreeWidgetItem* item, int column)
	{
		if (item == nullptr)
			return;
		QVariant data = item->data(column, Qt::UserRole);
		ItemEdgeData itemData = data.value<ItemEdgeData>();
		
        QByteArray objName = itemData.ModelName.toUtf8();
        std::vector<const char*> objNameVec = {objName.constData()};
		std::vector<long> cellIDVec = itemData.CellIDVec;
		if (cellIDVec.empty())
			return;

		QStringList strObjNameList;
		QStringList strCellIDList;
		for (int i = 0; i < cellIDVec.size(); ++i)
		{
			strObjNameList.push_back(QString("'%1'").arg(itemData.ModelName));
			strCellIDList.push_back(QString("%1").arg(cellIDVec[i]));
		}
			
		std::string objNamesStr = strObjNameList.join(",").toStdString();
		std::string cellIDsStr = strCellIDList.join(",").toStdString();
		
		std::ostringstream oss;
		oss << "sel = NCTI.SelectionManager(doc)\n";
		oss << "sel.ClearSelected()\n";
		oss << "sel.ObjectNames = [" << objNamesStr << "]\n";
		if(!cellIDsStr.empty())
			oss << "sel.CellIDs = [" << cellIDsStr << "]\n";
		oss << "sel.SetSelected()\n";
		oss << "view = NCTI.View(doc.ID)\n";
		oss << "view.Zoom(sel.ObjectNames,sel.CellIDs)\n";
		NctiPyCB.RunSimpleString(oss.str().c_str());

		NctiDocument* pDocument = NctiDocumentManager::instance()->GetDocument(m_DocID);
		if (pDocument == nullptr)
			return;
		NctiBaseModel* pBaseModel = pDocument->GetBaseModel();
		NctiBaseView* pBaseView = pBaseModel->GetActiveBaseView();
		pBaseView->Update();
	}

}

