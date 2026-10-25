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

#include "NctiFeatureTreeDlg.h"

#include <QVBoxLayout>
#include <QPushButton>
#include <QTreeWidgetItem>

#include <NctiDocument.h>
#include <NctiBaseModel.h>
#include <NctiBaseView.h>
#include <NctiDocElementPubFun.h>
#include <NctiDisplayModelBody.h>
#include <NctiArgumentObject.h>
#include <NctiCommandManager.h>
#include <NctiBaseUtility.h>
#include <NctiPosition.h>
#include "NctiPyArgObject.h"

namespace NCTI
{
	NctiFeatureTreeDlg::NctiFeatureTreeDlg(QWidget* parent)
		: QDialog(parent)
		, m_TreeWidget(nullptr)
		, m_BtnRemove(nullptr)
		, m_LevelCount(0)
		, m_DocID(-1)
	{
	}

	NctiFeatureTreeDlg::~NctiFeatureTreeDlg()
    {
    }

	bool NctiFeatureTreeDlg::init(PyObject* i_args)
	{
		NctiPyArgObject pyArg(i_args);
		Ncti_Integer size = pyArg.Size();// PyTuple_Size(i_args);
		if (size < 5)
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
		const Ncti_Char* title;
		if (!pyArg.GetStr(2, title))
			return false;
		//arg = PyTuple_GetItem(i_args, 2);
		//if (!PyUnicode_Check(arg))
		//	return false;
		//QString title = PyUnicode_AsUTF8(arg);

		if (!pyArg.GetLong(3, m_LevelCount))
			return false;
		//arg = PyTuple_GetItem(i_args, 3);
		//if (!PyLong_Check(arg))
		//	return false;
		//m_LevelCount = PyLong_AsLong(arg);
		std::vector<const Ncti_Char*> vals;
		if (!pyArg.GetStrList(size - 1, vals))
			return false;
		for (int i = 0; i < vals.size(); ++i)
		{
			m_LevelNames.append(vals[i]);
		}
		//arg = PyTuple_GetItem(i_args, size - 1);
		//if (!PyList_Check(arg))
		//	return false;
		//Ncti_LongLong len = PyList_Size(arg);
		//for (int i = 0; i < len; ++i)
		//{
		//	PyObject* item = PyList_GetItem(arg, i);
		//	if (!PyUnicode_Check(item))
		//		return false;
		//	m_LevelNames.append(PyUnicode_AsUTF8(item));
		//}

		if (m_LevelNames.size() != m_LevelCount)
			return false;
		PyObject* arg = NctiPyCB.GetTupleItem(i_args, 4);
		if (!arg)
			return false;
		if (!NctiPyCB.IsList(arg))
			return false;
		//arg = PyTuple_GetItem(i_args, 4);
		//if (!PyList_Check(arg))
		//	return false;

		this->setWindowTitle(QString(title));
		resize(300, 400);
		QVBoxLayout* layoutMain = new QVBoxLayout(this);
		m_TreeWidget = new QTreeWidget(this);
		m_TreeWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
		layoutMain->addWidget(m_TreeWidget);
		this->setLayout(layoutMain);
		m_TreeWidget->setColumnCount(1);
		m_TreeWidget->setHeaderHidden(true);

		m_BtnRemove = new QPushButton;
		m_BtnRemove->setText(QStringLiteral("移除特征"));
		m_BtnRemove->setObjectName("modetails-ok-button");
		layoutMain->addWidget(m_BtnRemove, 0, Qt::AlignCenter);
		layoutMain->setContentsMargins(10, 0, 10, 10);

		connect(m_TreeWidget, &QTreeWidget::itemClicked, this, &NctiFeatureTreeDlg::onItemClicked);
		connect(m_BtnRemove, &QPushButton::clicked, this, &NctiFeatureTreeDlg::onBtnClicked);


		std::vector<QTreeWidgetItem*> treeWidgetItemVec;
		Ncti_Integer len = NctiPyCB.GetListSize(arg);// PyList_Size(arg);
		for (Ncti_LongLong i = 0; i < len; ++i)
		{
			PyObject* item = NctiPyCB.GetListItem(arg, i);//PyList_GetItem(arg, i);
			//if (!PyUnicode_Check(item))
			if (!NctiPyCB.IsUnicode(item))
				continue;
			QString modelBodyName = NctiPyCB.GetUnicodeStr(item);//PyUnicode_AsUTF8(item);

			QTreeWidgetItem* firstItem = new QTreeWidgetItem(m_TreeWidget);
			treeWidgetItemVec.push_back(firstItem);
			QString text = m_LevelNames[0];
			firstItem->setText(0, text.append("[").append(modelBodyName).append("]"));
			ItemData data1;
			data1.ModelName = modelBodyName;
			if (m_LevelCount > 1)
			{
				PyObject* arg2 = NctiPyCB.GetTupleItem(i_args, 5);
				//if (PyList_Check(arg2))
				if (NctiPyCB.IsList(arg2))
				{
					//if (PyList_Size(arg2) == len)
					if (NctiPyCB.GetListSize(arg2) == len)
					{
						PyObject* childItem = NctiPyCB.GetListItem(arg2, i);//PyList_GetItem(arg2, i);
						//if (PyList_Check(childItem))
						if (NctiPyCB.IsList(childItem))
						{
							Ncti_LongLong len2 = NctiPyCB.GetListSize(childItem);//PyList_Size(childItem);
							for (Ncti_LongLong ii = 0; ii < len2; ++ii)
							{
								ItemData data2;
								data2.ModelName = modelBodyName;
								QTreeWidgetItem* secodeItem = new QTreeWidgetItem(firstItem);
								treeWidgetItemVec.push_back(secodeItem);
								QString text = m_LevelNames[1];

								PyObject* subChildItem = NctiPyCB.GetListItem(childItem, ii);//PyList_GetItem(childItem, ii);
								//if (PyList_Check(subChildItem))
								if (NctiPyCB.IsList(subChildItem))
								{
									std::string str;
									Ncti_LongLong len3 = NctiPyCB.GetListSize(subChildItem);//PyList_Size(subChildItem);
									for (Ncti_LongLong iii = 0; iii < len3; ++iii)
									{
										//long cellID = PyLong_AsLong(PyList_GetItem(subChildItem, iii));
										long cellID = NctiPyCB.GetLong(NctiPyCB.GetListItem(subChildItem, iii));
										data1.CellIDVec.push_back(cellID);
										data2.CellIDVec.push_back(cellID);
										std::vector<NctiPosition> posVec;
										NctiDocElementPubFun::GetFaceAttribPoints(pDocument, modelBodyName.toUtf8().constData(), cellID, posVec);
										data1.CellPosVec.push_back(posVec);
										data2.CellPosVec.push_back(posVec);

										if (!str.empty()) str += ",";
										str += std::to_string(cellID);
									}
									text = text.append("[").append(str.c_str()).append("]");
								}
								//else if (PyLong_Check(subChildItem))
								else if (NctiPyCB.IsLong(subChildItem))
								{
									long cellID = NctiPyCB.GetLong(subChildItem);//PyLong_AsLong(subChildItem);
									data1.CellIDVec.push_back(cellID);
									data2.CellIDVec.push_back(cellID);
									std::vector<NctiPosition> posVec;
									NctiDocElementPubFun::GetFaceAttribPoints(pDocument, modelBodyName.toUtf8().constData(), cellID, posVec);
									data1.CellPosVec.push_back(posVec);
									data2.CellPosVec.push_back(posVec);
									text = text.append("[").append(std::to_string(cellID).c_str()).append("]");
								}
								secodeItem->setText(0, text);
								secodeItem->setData(0, Qt::UserRole, QVariant::fromValue(data2));
							}
						}
					}
				}
			}
			firstItem->setData(0, Qt::UserRole, QVariant::fromValue(data1));
		}

		for (auto pTreeWidgetItem : treeWidgetItemVec)
		{
			pTreeWidgetItem->setFlags(pTreeWidgetItem->flags() | Qt::ItemIsUserCheckable); // 启用勾选
			pTreeWidgetItem->setCheckState(0, Qt::Unchecked); // 初始状态为未勾选
		}
		m_TreeWidget->expandAll();
		return true;
	}

	void NctiFeatureTreeDlg::updateParentState(QTreeWidgetItem* item)
	{
		QTreeWidgetItem* parent = item->parent();
		if (parent) {
			bool allChecked = true;
			bool allUnchecked = true;
			for (int i = 0; i < parent->childCount(); ++i) {
				Qt::CheckState state = parent->child(i)->checkState(0);
				if (state != Qt::Checked) allChecked = false;
				if (state != Qt::Unchecked) allUnchecked = false;
			}
			parent->setCheckState(0, allChecked ? Qt::Checked :
				(allUnchecked ? Qt::Unchecked : Qt::PartiallyChecked));
		}
	}

	void NctiFeatureTreeDlg::updateTree()
	{
		NctiDocument* pDocument = NctiDocumentManager::instance()->GetDocument(m_DocID);
		if (pDocument == nullptr)
			return;
	
		for (int i = m_TreeWidget->topLevelItemCount() - 1; i >= 0; --i)
		{
			QTreeWidgetItem* topItem = m_TreeWidget->topLevelItem(i);
			ItemData data1 = topItem->data(0, Qt::UserRole).value<ItemData>();
			std::vector<NCTI_MODEL_TAG> cellVec;
			NctiDocElementPubFun::GetAllCellVec(pDocument, data1.ModelName.toUtf8().constData(), cellVec);
			std::map<NCTI_MODEL_TAG, std::vector<NctiPosition>> cellPosDict;
			for (auto cell : cellVec)
			{
				std::vector<NctiPosition> pts;
				Ncti_Long cellId = *((Ncti_Long*)cell);
				NctiDocElementPubFun::GetFaceAttribPoints(pDocument, data1.ModelName.toUtf8().constData(), cellId, pts);
				cellPosDict[cell] = pts;
			}

			data1.CellIDVec.clear();
			data1.CellPosVec.clear();
			if (topItem->checkState(0) == Qt::Checked)
			{
				m_TreeWidget->takeTopLevelItem(i);
				continue;
			}
			else
			{
				for (int ii = topItem->childCount() - 1; ii >= 0; --ii)
				{
					QTreeWidgetItem* item = topItem->child(ii);
					if (item->checkState(0) == Qt::Checked)
					{
						topItem->takeChild(ii);
						continue;
					}
					ItemData data2 = item->data(0, Qt::UserRole).value<ItemData>();
					std::vector<std::vector<NctiPosition>> cellPosVec = data2.CellPosVec;
					data2.CellIDVec.clear();
					data2.CellPosVec.clear();
					std::string str;
					for (auto cellPos : cellPosVec)
					{
						for (auto pair : cellPosDict)
						{
							if (NctiBaseUtility::same_points(cellPos, pair.second, 1E-2))
							{
								Ncti_Long cellID = *((Ncti_Long*)pair.first);
								data1.CellIDVec.push_back(cellID);
								data2.CellIDVec.push_back(cellID);
								data1.CellPosVec.push_back(cellPos);
								data2.CellPosVec.push_back(cellPos);
								if (!str.empty()) str += ",";
								str += std::to_string(cellID);
								break;
							}
						}
					}
					QString text = m_LevelNames[1];
					item->setText(0, text.append("[").append(str.c_str()).append("]"));
					item->setData(0, Qt::UserRole, QVariant::fromValue(data2));
				}
			}
			QString text = m_LevelNames[0];
			topItem->setText(0, text.append("[").append(data1.ModelName).append("]"));
			topItem->setData(0, Qt::UserRole, QVariant::fromValue(data1));
		}
	}

	void NctiFeatureTreeDlg::onItemClicked(QTreeWidgetItem* item, int column)
	{
		if (item == nullptr)
			return;
		QVariant data = item->data(column, Qt::UserRole);
		ItemData itemData = data.value<ItemData>();
		
		std::vector<const char*> objNameVec = { itemData.ModelName.toUtf8().constData()};
		std::vector<long> cellIDVec = itemData.CellIDVec;
		if (!cellIDVec.empty())
		{
			for (int i = 1; i < cellIDVec.size(); ++i)
				objNameVec.push_back(objNameVec.front());
		}
		std::string objNamesStr;
		for (auto objName : objNameVec)
		{
			if (!objNamesStr.empty())
				objNamesStr.append(",");
			objNamesStr.append("'");
			objNamesStr.append(objName);
			objNamesStr.append("'");
		}
		std::string cellIDsStr;
		for (auto cellID : cellIDVec)
		{
			if (!cellIDsStr.empty())
				cellIDsStr.append(",");
			cellIDsStr.append(std::to_string(cellID));
		}

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

		Qt::CheckState state = item->checkState(0);
		// 同步子节点状态
		for (int i = 0; i < item->childCount(); ++i) {
			item->child(i)->setCheckState(0, state);
		}
		// 更新父节点状态
		updateParentState(item);

		NctiDocument* pDocument = NctiDocumentManager::instance()->GetDocument(m_DocID);
		if (pDocument == nullptr)
			return;
		NctiBaseModel* pBaseModel = pDocument->GetBaseModel();
		NctiBaseView* pBaseView = pBaseModel->GetActiveBaseView();
		pBaseView->Update();
	}

	void NctiFeatureTreeDlg::onBtnClicked(bool boo)
	{
		NctiDocument* pDocument = NctiDocumentManager::instance()->GetDocument(m_DocID);
		if (pDocument == nullptr)
			return;

		std::map<QString, std::vector<long>> featureDict;
		for (int i = 0; i < m_TreeWidget->topLevelItemCount(); ++i)
		{
			QTreeWidgetItem* topItem = m_TreeWidget->topLevelItem(i);
			if (topItem->checkState(0) == Qt::Checked)
			{
				ItemData data = topItem->data(0, Qt::UserRole).value<ItemData>();
				featureDict[data.ModelName] = data.CellIDVec;
			}
			else
			{
				for (int ii = 0; ii < topItem->childCount(); ++ii)
				{
					QTreeWidgetItem* item = topItem->child(ii);
					if (item->checkState(0) == Qt::Checked)
					{
						ItemData data = item->data(0, Qt::UserRole).value<ItemData>();
						featureDict[data.ModelName].insert(featureDict[data.ModelName].end(),
							data.CellIDVec.begin(), data.CellIDVec.end());
					}
				}
			}
		}

		NctiBaseModel* pBaseModel = pDocument->GetBaseModel();
		NctiCommandManager* pCmdMgr = NctiCommandManager::GetCommandManager(pBaseModel);
		if (m_LevelCount == 1)
		{
			std::vector<NctiDisplayObject*> pDisObjVec;
			for (auto& pair : featureDict)
			{
				NctiDisplayObject* pDisObj = nullptr;
				NctiDocElementPubFun::GetObjectListByName(pDocument, NctiDisplayModelBody::ID, pair.first.toUtf8().constData(), pDisObj);
				if (pDisObj == nullptr)
					continue;
				pDisObjVec.push_back(pDisObj);
			}
			NctiArgumentObject argumentObject;
			argumentObject.SetDisplayObjectVec(pDisObjVec);
			pCmdMgr->RunCommand("cmd_ncti_delete", &argumentObject);
		}
		else
		{
			for (auto& pair : featureDict)
			{
				NctiDisplayObject* pDisObj = nullptr;
				NctiDocElementPubFun::GetObjectListByName(pDocument, NctiDisplayModelBody::ID, pair.first.toUtf8().constData(), pDisObj);
				if (pDisObj == nullptr)
					continue;
				NctiArgumentObject argumentObject;
				argumentObject.SetDisplayObject1(pDisObj);
				std::vector<NCTI_MODEL_TAG> cellIDVec;
				for (auto& cellID : pair.second)
					cellIDVec.push_back(&cellID);
				argumentObject.SetCellVec(cellIDVec);
				pCmdMgr->RunCommand("cmd_ncti_remove_features", &argumentObject);
			}
		}
		updateTree();
	}

}

