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

#include "NcitAbnormalObjectTreeDlg.h"

#include <QVBoxLayout>
#include <QTreeWidgetItem>

#include <NctiDocument.h>
#include <NctiBaseModel.h>
#include <NctiBaseView.h>
#include <NctiPosition.h>
#include "NctiPyArgObject.h"

namespace NCTI
{
	NcitAbnormalObjectTreeDlg::NcitAbnormalObjectTreeDlg(QWidget* parent)
		: QDialog(parent)
		, m_TreeWidget(nullptr)
		, m_DocID(-1)
	{
	}

	NcitAbnormalObjectTreeDlg::~NcitAbnormalObjectTreeDlg()
    {
    }

	bool NcitAbnormalObjectTreeDlg::init(PyObject* i_args)
	{
		this->setWindowTitle(QString("异常对象"));
		resize(300, 400);
		QVBoxLayout* layoutMain = new QVBoxLayout(this);
		m_TreeWidget = new QTreeWidget(this);
		m_TreeWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
		// 启用多选
		m_TreeWidget->setSelectionMode(QAbstractItemView::MultiSelection);

		// 或启用扩展选择（推荐，支持 Ctrl、Shift 键）
		m_TreeWidget->setSelectionMode(QAbstractItemView::ExtendedSelection);
		layoutMain->addWidget(m_TreeWidget);
		this->setLayout(layoutMain);
		m_TreeWidget->setColumnCount(1);
		m_TreeWidget->setHeaderHidden(true);

		layoutMain->setContentsMargins(10, 0, 10, 10);
		connect(m_TreeWidget, &QTreeWidget::itemClicked, this, &NcitAbnormalObjectTreeDlg::onItemClicked);

		NctiPyArgObject pyArg(i_args);

		Ncti_LongLong size = pyArg.Size();// PyTuple_Size(i_args);
		if (size < 3)
			return false;
		if (!pyArg.GetLong(1, m_DocID))
			return false;
		//PyObject* arg = PyTuple_GetItem(i_args, 1);
		//if (!PyLong_Check(arg))
		//	return false;
		//m_DocID = PyLong_AsLong(arg);
		NctiDocument* pDocument = NctiDocumentManager::instance()->GetDocument(m_DocID);
		if (pDocument == nullptr)
			return false;

		PyObject* arg = NctiPyCB.GetTupleItem(i_args, 2);
		//{'box': {'折叠的Face': [13, 9, 8, 7, 12, 11, 10, 15, 6, 14, 16, 17]}}		
		if (!arg)
			return false;

		//arg = PyTuple_GetItem(i_args, 2); 
		//if (!PyDict_Check(arg))
		//	return false;

		Ncti_Pysize pos = 0;
		PyObject* key, * value;
		//while (PyDict_Next(arg, &pos, &key, &value))
		while (NctiPyCB.GetDictNext(arg, pos, key, value))
		{
			//if (PyUnicode_Check(key) && PyDict_Check(value))
			if (NctiPyCB.IsUnicode(key) && NctiPyCB.IsDict(value))
			{
				QString strBodyName = NctiPyCB.GetUnicodeStr(key);
				QString strNameLv1 = QString("实体[%1]").arg(strBodyName);

				QTreeWidgetItem* firstItem = new QTreeWidgetItem(m_TreeWidget);
				firstItem->setText(0, strNameLv1);
				ItemCellData data1;
				data1.ModelName = strBodyName;

				Ncti_Pysize cPos = 0;
				PyObject* cKey, * cValue;
				//while (PyDict_Next(value, &cPos, &cKey, &cValue))
				while (NctiPyCB.GetDictNext(value, cPos, cKey, cValue))
				{
					//if (PyUnicode_Check(cKey) && PyList_Check(cValue))
					if (NctiPyCB.IsUnicode(cKey) && NctiPyCB.IsList(cValue))
					{
						QString strNameLv2 = NctiPyCB.GetUnicodeStr(cKey);//PyUnicode_AsUTF8(cKey);
						Ncti_LongLong len = NctiPyCB.GetListSize(cValue);//PyList_Size(cValue);
						QList<long> nIdList;
						for (int i = 0; i < len; ++i)
						{
							PyObject* item = NctiPyCB.GetListItem(cValue, i);//PyList_GetItem(cValue, i);
							//if (PyLong_Check(item))
							if (NctiPyCB.IsLong(item))
							{
								//nIdList.append(PyLong_AsLong(item));
								nIdList.append(NctiPyCB.GetLong(item));
							}
						}
						QTreeWidgetItem* secodeItem = new QTreeWidgetItem(firstItem);

						secodeItem->setText(0, strNameLv2);
						ItemCellData data2;
						data2.ModelName = strBodyName;

						//							std::sort(nIdList.begin(), nIdList.end());
						for (int i = 0; i < nIdList.size(); i++)
						{
							int nId = nIdList.at(i);

							ItemCellData data3;
							data3.ModelName = strBodyName;
							QTreeWidgetItem* thirdItem = new QTreeWidgetItem(secodeItem);
							QString strNameLv3 = QString("子元素[%1]").arg(nId);;

							long cellID = nId;
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

	void NcitAbnormalObjectTreeDlg::onItemClicked(QTreeWidgetItem* item, int column)
	{
		if (item == nullptr)
			return;
		QList<QTreeWidgetItem*> items =m_TreeWidget->selectedItems();
		std::vector<const char*> objNameVec;
		std::vector<long> cellIDVec;

		QStringList strObjNameList;
		QStringList strCellIDList;


		for (int i = 0; i < items.size(); i++)
		{
			QVariant data = items[i]->data(column, Qt::UserRole);
			ItemCellData itemData = data.value<ItemCellData>();
            QByteArray objName = itemData.ModelName.toUtf8();

			std::vector<const char*> objNameVecTemp = {objName.constData()};
			std::vector<long> cellIDVecTemp = itemData.CellIDVec;
			objNameVec.insert(objNameVec.end(), objNameVecTemp.begin(), objNameVecTemp.end());
			cellIDVec.insert(cellIDVec.end(), cellIDVecTemp.begin(), cellIDVecTemp.end());
			for (int i = 0; i < cellIDVecTemp.size(); ++i)
			{
				strObjNameList.push_back(QString("'%1'").arg(itemData.ModelName));
				strCellIDList.push_back(QString("%1").arg(cellIDVecTemp[i]));
			}
		}

		if (cellIDVec.empty())
			return;



			
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

