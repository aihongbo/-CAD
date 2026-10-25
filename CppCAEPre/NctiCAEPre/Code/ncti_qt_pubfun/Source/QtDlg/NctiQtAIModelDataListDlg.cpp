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

#include "NctiQtAIModelDataListDlg.h"

#include <algorithm>
#include <unordered_map>

#include <QMenu>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>

#include "NctiBaseModel.h"
#include "NctiBaseView.h"
#include "NctiDocument.h"
#include "NctiDocElementPubFun.h"
#include "NctiAiModelSystemObject.h"
#include "NctiArgumentObject.h"
#include "NctiCommandManager.h"
#include "NctiPosition.h"
#include "NctiSelectionManager.h"
#include "NctiDisplayModelBody.h"
#include "NctiDisplayDocCustomContainer.h"
#include "NctiGeometryFunction.h"
#include "NctiDisplayObjectList.h"
#include "NctiDisplayDocElement.h"
#include "NctiDisplayBodyGroup.h"
#include "AiLabelTree.h"
#include "NctiObjectTree.h"
#include "NctiTreeItem.h"
#include "NctiJsonDocument.h"

#include "NctiDebug.h"
#include "NctiRenderSceneItem.h"
#include "NctiRenderSegmentItem.h"
#include "NctiRenderVisSelKit.h"
#include "NctiRenderMaterialKit.h"

#define NO_DEFINE_AI_LEBEL "未定义标签实体"

// 注册自定义结构体到 QMetaType 系统
Q_DECLARE_METATYPE(AiModelData)

namespace NCTI
{
	NctiQtAIModelDataListDlg* NctiQtAIModelDataListDlg::m_instance = nullptr;
	QString GetItemName(const QString& key, const AiModelData& modelData, const Ncti_Long& cellID)
	{
		QString typeName;
		if (modelData.type == 0) {
			typeName = "body";
		}
		else if (modelData.type == 1) {
			typeName = "face";
		}

		else if (modelData.type == 2) {
			typeName = "edge";
		}

		else if (modelData.type == 3) {
			typeName = "vertex";
		}

		return QString("%1-%2-%3").arg(modelData.ObjName.c_str()).arg(typeName).arg(cellID);
	}

	NctiQtAIModelDataListDlg::NctiQtAIModelDataListDlg(NctiDocument* i_pDocument, QWidget* i_parent,
		const std::vector<AiLabelTree>& setAiLabels,
		const std::vector<AiLabelTree>& setAiFeatureLabels,
		NctiObjectTree* objectTree)
		: QWidget(i_parent)
        , m_ui(new Ui::NctiAIModelDataList())
		, m_pDocument(i_pDocument)
		, m_oldName("")
		, m_setAiLabels(setAiLabels)
		, m_setAiFeatureLabels(setAiLabels)
		, m_objectTree(objectTree)
	{
		Init();
	}

	NctiQtAIModelDataListDlg::~NctiQtAIModelDataListDlg()
	{
		NCTI_DELETE m_ui;
	}

	NctiQtAIModelDataListDlg* NctiQtAIModelDataListDlg::Instance()
	{
		return m_instance;
	}

	void NctiQtAIModelDataListDlg::SetInstance(NctiQtAIModelDataListDlg* pNctiQtAIModelDataListDlg)
	{
		m_instance = pNctiQtAIModelDataListDlg;
	}

	void NctiQtAIModelDataListDlg::Init()
	{
		m_ui->setupUi(this);
		this->setWindowFlags(Qt::Dialog);
		this->setWindowModality(Qt::NonModal);

		setWindowTitle(QString::fromUtf16(u"AI模型数据列表"));

		//shape widget
		m_ui->shapeTreeWidget->setSelectionMode(QTreeWidget::ExtendedSelection); // 允许多选
		m_ui->shapeTreeWidget->setDragDropMode(QTreeWidget::NoDragDrop);
		m_ui->shapeTreeWidget->header()->hide();
		m_ui->shapeTreeWidget->header()->setSectionResizeMode(QHeaderView::ResizeToContents); // 自适应列宽
		m_ui->shapeTreeWidget->setContextMenuPolicy(Qt::CustomContextMenu);
		connect(m_ui->shapeTreeWidget, &QTreeWidget::itemChanged, this, &NctiQtAIModelDataListDlg::onShapeItemClicked);
		connect(m_ui->shapeTreeWidget, &QTreeWidget::customContextMenuRequested, this, &NctiQtAIModelDataListDlg::onShapeItemMenuShow);

		//body tree widget
		m_ui->bodyTreeWidget->setSelectionMode(QTreeWidget::ExtendedSelection);
		m_ui->bodyTreeWidget->setDragDropMode(QTreeWidget::NoDragDrop);
		m_ui->bodyTreeWidget->header()->hide();
		m_ui->bodyTreeWidget->header()->setSectionResizeMode(QHeaderView::ResizeToContents); // 自适应列宽
		m_ui->bodyTreeWidget->setContextMenuPolicy(Qt::NoContextMenu);
		connect(m_ui->bodyTreeWidget, &QTreeWidget::itemChanged, this, &NctiQtAIModelDataListDlg::onObjectItemClicked);

		//feature tree widget
		m_ui->featureTreeWidget->setSelectionMode(QTreeWidget::ExtendedSelection);
		m_ui->featureTreeWidget->setDragDropMode(QTreeWidget::NoDragDrop);
		m_ui->featureTreeWidget->header()->hide();
		m_ui->featureTreeWidget->header()->setSectionResizeMode(QHeaderView::ResizeToContents); // 自适应列宽
		m_ui->featureTreeWidget->setContextMenuPolicy(Qt::NoContextMenu);
		connect(m_ui->featureTreeWidget, &QTreeWidget::itemChanged, this, &NctiQtAIModelDataListDlg::onFeatureItemClicked);
		
		//刷新按钮
		connect(m_ui->pushButton_refresh, SIGNAL(clicked()), this, SLOT(onRefreshButtonClick()));
		//导出按钮
		connect(m_ui->pushButton_output, SIGNAL(clicked()), this, SLOT(onExportModels()));
		//移除子标签按钮
		connect(m_ui->pushButton_delete_label, SIGNAL(clicked()), this, SLOT(onRemoveSubLabels()));
		//全选标签按钮
		connect(m_ui->pushButton_selectAll, SIGNAL(clicked()), this, SLOT(onSelectAllLabels()));
		//取消全选标签按钮
		connect(m_ui->pushButton_deselectAll, SIGNAL(clicked()), this, SLOT(onDeselectAllLabels()));
		//InitAiLabelTree();
		RefreshModelData(nullptr);
	}

	void NctiQtAIModelDataListDlg::onRefreshButtonClick()
	{
		RefreshModelData(nullptr);
	}

	void NctiQtAIModelDataListDlg::RefreshModelData(NctiDocument* i_pDocument)
	{
		if (i_pDocument)
		{
			if (i_pDocument != m_pDocument)
			{
				m_highlighObjectSet.clear();
				m_pDocument = i_pDocument;
			}
		}
		if (m_pDocument == nullptr)
			return;
		//clock_t start, end;
		//double cpu_time_used;

		m_AiModelDataMap.clear();
		m_vShapeTreeItem.clear();
		m_setAllBodyNames.clear();
		ClearAiLabelType();
        for (auto& item : m_vSegmentItem)
        {
            NCTI_DELETE_OBJECT(item);
        }
        m_vSegmentItem.clear();

		NctiBaseModel* pBaseModel = m_pDocument->GetBaseModel();
		if (pBaseModel == nullptr)
			return;
		NctiAiModelSystemObject* aiObject = NctiDocElementPubFun::GetAiModelSystemObject(pBaseModel);
		if (aiObject == nullptr)
			return;
		m_AiModelDataMap = aiObject->GetLabelMap();

		//GetAllBodyNames() Time
		//start = clock();
		GetAllBodyNames();
		//end = clock();
		//cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
		//std::cout << "GetAllBodyNames() Time used: " << cpu_time_used << " seconds" << std::endl;

		RefreshAiLabelType();
		//InitCellMap();

		m_ui->shapeTreeWidget->clear();
		m_ui->bodyTreeWidget->clear();
		m_ui->featureTreeWidget->clear();

		//阻塞信号槽，减少无效操作
		QSignalBlocker blocker(m_ui->shapeTreeWidget);
		QSignalBlocker blocker1(m_ui->bodyTreeWidget);
		QSignalBlocker blocker2(m_ui->featureTreeWidget);

		//ShowBodyList() Time
		//显示实体数据列表
		//start = clock();
		ShowBodyList();
		//end = clock();
		//cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
		//std::cout << "ShowBodyList() Time used: " << cpu_time_used << " seconds" << std::endl;

		//ShowShapeList() Time
		//显示点线面数据列表
		//start = clock();
		ShowShapeList();
		//end = clock();
		//cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
		//std::cout << "ShowShapeList() Time used: " << cpu_time_used << " seconds" << std::endl;

		
		//打印调试信息
		for (const auto& v : m_AiModelDataMap) {
			NctiPrintf("AiModelDataMap key: %s Size: %%zu", v.first.c_str(), v.second.size());
		}

		m_pDocument->GetBaseModel()->RefreshViews();
	}

	void NctiQtAIModelDataListDlg::onObjectItemClicked(QTreeWidgetItem* item, int column)
	{
		auto v = m_pDocument->GetBaseModel()->GetActiveBaseView()->GetScene();
		if (v)
			v->SetDispEnable(false);
		CheckedBodyItem(item, column);
		if (v)
			v->SetDispEnable(true);
	}

	void NctiQtAIModelDataListDlg::onShapeItemClicked(QTreeWidgetItem* item, int column)
	{
		if (m_oldName != "") {

			std::string name = item->text(0).toUtf8().data();
			RenameShapeItem(name);
			m_oldName = "";
			return;
		}

		CheckedShapeItem(item, column);
	}
	void NctiQtAIModelDataListDlg::onFeatureItemClicked(QTreeWidgetItem* item, int column)
	{
		CheckedFeatureItem(item, column);
	}

	void NctiQtAIModelDataListDlg::onShapeItemMenuShow(const QPoint& point)
	{
		QTreeWidgetItem* curItem = m_ui->shapeTreeWidget->currentItem();
		if (curItem == nullptr || curItem->childCount() == 0)
		{
			return;
		}

		QMenu* menu = new QMenu(m_ui->shapeTreeWidget);
		QAction* renameAct = new QAction("rename");
		QAction* deleteAct = new QAction("delete");

		connect(renameAct, &QAction::triggered, this, &NctiQtAIModelDataListDlg::onShapeItemRename);
		connect(deleteAct, &QAction::triggered, this, &NctiQtAIModelDataListDlg::onShapeItemRemove);

		menu->addAction(renameAct);
		menu->addAction(deleteAct);
		menu->exec(QCursor::pos());
	}

	void NctiQtAIModelDataListDlg::onExportModels()
	{
		QString prefix = m_ui->lineEditPrefix->text();
		if (m_ui->tabWidget->currentIndex() == 1)
		{
			m_setOutputBodyNames.clear();
			//检查是否有未标签的
			// 遍历所有顶级节点
			for (int i = 0; i < m_ui->bodyTreeWidget->topLevelItemCount(); ++i) {
				TraverseItemToExport(m_ui->bodyTreeWidget->topLevelItem(i), "", prefix, 0);
			}
			if (m_setAllBodyNames == m_setOutputBodyNames) {
				QString selectedPath = QFileDialog::getExistingDirectory(this, "Select Directory");
				if (selectedPath.isEmpty())
					return;

				for (int i = 0; i < m_ui->bodyTreeWidget->topLevelItemCount(); ++i) {
					TraverseItemToExport(m_ui->bodyTreeWidget->topLevelItem(i), selectedPath, prefix, 1);
				}
			}
			else {
				bool isConfirm = ShowConfirmDialog(this, "确认导出", "还有未标签的零件，是否确认导出？");
				if (isConfirm) {
					QString selectedPath = QFileDialog::getExistingDirectory(this, "Select Directory");
					if (selectedPath.isEmpty())
						return;
					for (int i = 0; i < m_ui->bodyTreeWidget->topLevelItemCount(); ++i) {
						TraverseItemToExport(m_ui->bodyTreeWidget->topLevelItem(i), selectedPath, prefix, 1);
					}
					NctiDebug::debug("Write OutputFeature file success!");
					QMessageBox::information(NULL, "结果", "完成导出", QMessageBox::Yes, QMessageBox::Yes);
				}
			}
		}
		else if (m_ui->tabWidget->currentIndex() == 2)
		{
			QString selectedPath = QFileDialog::getExistingDirectory(this, "Select Directory");
			if (selectedPath.isEmpty())
				return;
			//输出模型特征到一个模型文件
			std::vector<NCTI_MODEL_TAG> pOutputDataVec;
			std::vector<AiModelData> setAiModel; //std::set会报错const比较方法错误
			for (int i = 0; i < m_ui->featureTreeWidget->topLevelItemCount(); ++i) {
				TraverseFeatureItemToExport(m_ui->featureTreeWidget->topLevelItem(i), pOutputDataVec, setAiModel);
			}
			if (!pOutputDataVec.empty())
			{
				ExportModels(selectedPath, pOutputDataVec, prefix + "output_features");
			}

			//输出json
			//第1层
			NCTIJson::JsonObject outputJson;
			JsonValue titleValue("features");
			outputJson.insert("title", titleValue);
			//第2层
			NCTIJson::JsonObject contentJson;
			//第3层
			//将相同标签的model信息放到同一标签下的数组
			for (auto& modelPair : m_AiModelDataMap)
			{
				std::string labelName = modelPair.first;
				int type = -10;
				if (m_mapAiLabelType.find(labelName) != m_mapAiLabelType.end()) {
					type = m_mapAiLabelType[labelName];
					if (type != 4) {
						continue;
					}
				}
				JsonArray labelArrayObject;
				for (auto& model : modelPair.second)
				{
					if (std::find(setAiModel.begin(), setAiModel.end(), model) == setAiModel.end()) {
						continue;
					}
					NctiDisplayObject* pDisplayObj = nullptr;
					NctiDocElementPubFun::GetObjectListByName(m_pDocument, NctiDisplayModelBody::ID, model.ObjName.c_str(), pDisplayObj);
					Ncti_Size originalID = 0;
					NctiDocElementPubFun::GetGeometryOriginalID((NctiDisplayModelBody*)pDisplayObj, originalID);
					NCTIJson::JsonObject lableJson;
					lableJson.insert("partName", model.ObjName);
					lableJson.insert("originalId", static_cast<Json::Value::UInt64>(originalID));

					std::vector<Ncti_Integer> cellIds;
					Json::Value featureOriginalArrayObject, idArrayObject;
					for (const auto& id : model.featureIds)
					{
						cellIds.push_back(id);
						idArrayObject.append(id);
					}
					std::vector<Ncti_Size> featureOriginalIds;
					NctiDocElementPubFun::GetFeatureOriginalID((NctiDisplayModelBody*)pDisplayObj, cellIds, featureOriginalIds);
					for (const auto& id : featureOriginalIds)
					{
						Json::Value idValue = static_cast<Json::UInt64>(id);
						featureOriginalArrayObject.append(idValue);
					}

					lableJson.insert("originalIds", featureOriginalArrayObject);
					lableJson.insert("cells", idArrayObject);
					labelArrayObject.push_back(lableJson.object());
				}
				contentJson.insert(labelName, labelArrayObject);
			}
	
			outputJson.insert("content", contentJson.object());

			NCTIJson::JsonDocument jsonDocument;
			jsonDocument.setObject(outputJson);

			std::string jsonData = jsonDocument.toJson(NCTIJson::JsonDocument::Compact);
			bool writeSuccess = WriteStringFile(QString(jsonData.c_str()), selectedPath, QString(prefix + "OutputFeature.json"));
			if (writeSuccess)
			{
				NctiDebug::debug("Write OutputFeature file success! ");
				QMessageBox::information(NULL, "结果", "完成导出", QMessageBox::Yes, QMessageBox::Yes);
			}
			else
			{
				NctiDebug::debug("Write OutputFeature file failed! ");
				QMessageBox::information(NULL, "结果", "导出失败", QMessageBox::Yes, QMessageBox::Yes);
			}
		}
		else //0
		{
			QString selectedPath = QFileDialog::getExistingDirectory(this, "Select Directory");
			if (selectedPath.isEmpty())
				return;
			std::map<QString, std::pair<QString, NCTI_MODEL_TAG>> bodyMap;
			for (int i = 0; i < m_ui->shapeTreeWidget->topLevelItemCount(); ++i) {
				TraverseFeatureItemBodyToExport(m_ui->shapeTreeWidget->topLevelItem(i), bodyMap);
			}
			bool writeSuccess = false;
			std::vector<NCTI_MODEL_TAG> pOutputDataVec;
			for (auto& outPair : bodyMap)
			{
				pOutputDataVec.clear();
				pOutputDataVec.push_back(outPair.second.second);
				QString outputName = prefix + outPair.second.first + "-" + outPair.first;
				ExportModels(selectedPath, pOutputDataVec, outputName);

				//输出json，每一个json文件对应一个body name，用body name命名
				//第1层
				NCTIJson::JsonObject outputJson;
				JsonValue titleValue("single_features");
				outputJson.insert("title", titleValue);
				//第2层
				NCTIJson::JsonObject contentJson;
				//第3层
				for (const auto& item : m_vShapeTreeItem)
				{
					Qt::CheckState checkState = item->checkState(0);
					if (checkState != Qt::Checked) {
						continue;
					}

					AiModelData modelData = qvariant_cast<AiModelData>(item->data(0, Qt::UserRole));
					if (modelData.type <= 0 || modelData.type > 3) {
						continue;
					}
					if (modelData.ObjName != outPair.first.toStdString())
						continue;

					QString labelNameQString = item->text(0);
					std::string labelName = labelNameQString.toStdString();
					Json::Value idArrayObject;
					for (const auto& id : modelData.featureIds)
					{
						contentJson.insert(labelName, id);
						break;
					}
				}

				outputJson.insert("content", contentJson.object());

				NCTIJson::JsonDocument jsonDocument;
				jsonDocument.setObject(outputJson);

				std::string jsonData = jsonDocument.toJson(NCTIJson::JsonDocument::Compact);
				writeSuccess = WriteStringFile(QString(jsonData.c_str()), selectedPath, outputName + ".json");
			}
			
			if (writeSuccess)
			{
				NctiDebug::debug("Write OutputSingleFeature file success!");
				QMessageBox::information(NULL, "结果", "完成导出", QMessageBox::Yes, QMessageBox::Yes);
			}
			else
			{
				NctiDebug::debug("Write OutputSingleFeature file failed!");
				QMessageBox::information(NULL, "结果", "导出失败", QMessageBox::Yes, QMessageBox::Yes);
			}
		}
	}

	void NctiQtAIModelDataListDlg::onRemoveSubLabels()
	{
		RemoveCheckedBodyItem();
	}

	void NctiQtAIModelDataListDlg::onSelectAllLabels()
	{
		//阻塞信号槽，减少无效操作
		QSignalBlocker blocker(m_ui->shapeTreeWidget);
		QSignalBlocker blocker1(m_ui->bodyTreeWidget);
		QSignalBlocker blocker2(m_ui->featureTreeWidget);
		auto v = m_pDocument->GetBaseModel()->GetActiveBaseView()->GetScene();
		if (v)
			v->SetDispEnable(false);
		if (m_ui->tabWidget->currentIndex() == 1)
		{
			for (int i = 0; i < m_ui->bodyTreeWidget->topLevelItemCount(); ++i) {
				TraverseItemToSelect(m_ui->bodyTreeWidget->topLevelItem(i), 1);
			}
		}
		else if (m_ui->tabWidget->currentIndex() == 2)
		{
			for (int i = 0; i < m_ui->featureTreeWidget->topLevelItemCount(); ++i) {
				TraverseItemToSelect(m_ui->featureTreeWidget->topLevelItem(i), 1);
			}
		}
		else
		{
			for (int i = 0; i < m_ui->shapeTreeWidget->topLevelItemCount(); ++i) {
				TraverseItemToSelect(m_ui->shapeTreeWidget->topLevelItem(i), 1);
			}
		}
		HighLightBodys();
		if (v)
			v->SetDispEnable(true);
	}

	void NctiQtAIModelDataListDlg::onDeselectAllLabels()
	{
		//阻塞信号槽，减少无效操作
		QSignalBlocker blocker(m_ui->shapeTreeWidget);
		QSignalBlocker blocker1(m_ui->bodyTreeWidget);
		QSignalBlocker blocker2(m_ui->featureTreeWidget);
		auto v = m_pDocument->GetBaseModel()->GetActiveBaseView()->GetScene();
		if (v)
			v->SetDispEnable(false);
		if (m_ui->tabWidget->currentIndex() == 1)
		{
			for (int i = 0; i < m_ui->bodyTreeWidget->topLevelItemCount(); ++i) {
				TraverseItemToSelect(m_ui->bodyTreeWidget->topLevelItem(i), 0);
			}
		}
		else if (m_ui->tabWidget->currentIndex() == 2)
		{
			for (int i = 0; i < m_ui->featureTreeWidget->topLevelItemCount(); ++i) {
				TraverseItemToSelect(m_ui->featureTreeWidget->topLevelItem(i), 0);
			}
		}
		else
		{
			for (int i = 0; i < m_ui->shapeTreeWidget->topLevelItemCount(); ++i) {
				TraverseItemToSelect(m_ui->shapeTreeWidget->topLevelItem(i), 0);
			}
		}
		m_highlighObjectSet.clear();
		HighLightBodys();
		if (v)
			v->SetDispEnable(true);
	}

	void NctiQtAIModelDataListDlg::UpdateParentItemState(QTreeWidgetItem* item)
	{
		QTreeWidgetItem* parent = item->parent();

		//如果是主节点
		if (parent == nullptr) return;

		//选中子节点个数
		int selectedCount = 0;
		int childCount = parent->childCount();
		for (int i = 0; i < childCount; i++) {
			QTreeWidgetItem* chileItem = parent->child(i);
			if (chileItem->checkState(0) == Qt::Checked) {
				selectedCount++;
			}
		}

		if (selectedCount <= 0) {
			//选中状态
			parent->setCheckState(0, Qt::Unchecked);
		}
		else if (selectedCount > 0 && selectedCount < childCount) {
			//部分选中状态
			parent->setCheckState(0, Qt::PartiallyChecked);
		}
		else if (selectedCount == childCount) {
			//未选中状态
			parent->setCheckState(0, Qt::Checked);
		}
	}

	void NctiQtAIModelDataListDlg::ShowBodyList()
	{
		if (m_AiModelDataMap.empty()) {
			return;
		}

		std::vector<QString> bodyNames;

		for (const auto& modelPair : m_AiModelDataMap) {
			std::string labelName = modelPair.first;
			int type = -10;
			if (m_mapAiLabelType.find(labelName) != m_mapAiLabelType.end()) {
				type = m_mapAiLabelType[labelName];
				if (type > 0) {
					continue;
				}
			}
			if (modelPair.second.empty()) {
				continue;
			}
			if (labelName == std::string(NO_DEFINE_AI_LEBEL))
				continue;
			QString key = labelName.c_str();
			//添加标签节点
			AddTreeItem(key, modelPair.second, type);
		}
	}

	void NctiQtAIModelDataListDlg::ShowShapeList()
	{
		m_mapModelCellID.clear();
		m_vVertexName.clear();
		//ClearVertex();

		//显示AI标注的点线面
		m_ui->shapeTreeWidget->clear();
		//AI标注的特征
		m_ui->featureTreeWidget->clear();

		if (m_AiModelDataMap.empty()) {
			return;
		}

		for (const auto& modelPair : m_AiModelDataMap) {
			std::string labelName = modelPair.first;
			int type = -10;
			if (m_mapAiLabelType.find(labelName) != m_mapAiLabelType.end()) {
				type = m_mapAiLabelType[labelName];
				if (type <= 0) {
					continue;
				}
				else {
					QString key = labelName.c_str();
					AddTreeItem(key, modelPair.second, type);
				}
			}

		}

	}

	void NctiQtAIModelDataListDlg::AddTreeItem(const QString& key, const std::vector<AiModelData>& vModelData, const int objectType)
	{
		QTreeWidgetItem* treeKeyItem = nullptr;
		bool isFind = false;
		int childItemCount = 0;
		if (objectType == 4)
		{
			//查找是否已经有了标签项
			for (int i = 0; i < m_ui->featureTreeWidget->topLevelItemCount(); ++i) {
				auto oldKey = m_ui->featureTreeWidget->topLevelItem(i)->text(0);
				if (key == oldKey) {
					isFind = true;
					childItemCount = m_ui->featureTreeWidget->topLevelItem(i)->childCount();
					treeKeyItem = m_ui->featureTreeWidget->topLevelItem(i);
					break;
				}
			}
			if (!isFind) {
				treeKeyItem = new QTreeWidgetItem(m_ui->featureTreeWidget, QStringList(key));
				treeKeyItem->setFlags(treeKeyItem->flags() | Qt::ItemIsUserCheckable | Qt::ItemIsEditable);
				treeKeyItem->setCheckState(0, Qt::Unchecked); // 设置初始状态为未选中
			}
		}
		else if (objectType > 0 && objectType < 4) {
			//查找是否已经有了标签项
			for (int i = 0; i < m_ui->shapeTreeWidget->topLevelItemCount(); ++i) {
				auto oldKey = m_ui->shapeTreeWidget->topLevelItem(i)->text(0);
				if (key == oldKey) {
					isFind = true;
					childItemCount = m_ui->shapeTreeWidget->topLevelItem(i)->childCount();
					treeKeyItem = m_ui->shapeTreeWidget->topLevelItem(i);
					break;
				}
			}
			if (!isFind) {
				treeKeyItem = new QTreeWidgetItem(m_ui->shapeTreeWidget, QStringList(key));
				treeKeyItem->setFlags(treeKeyItem->flags() | Qt::ItemIsUserCheckable | Qt::ItemIsEditable);
				treeKeyItem->setCheckState(0, Qt::Unchecked); // 设置初始状态为未选中
			}

		}
		//objectType <= 0
		else {
			//查找是否已经有了标签项
			for (int i = 0; i < m_ui->bodyTreeWidget->topLevelItemCount(); ++i) {
				auto oldKey = m_ui->bodyTreeWidget->topLevelItem(i)->text(0);
				if (key == oldKey) {
					isFind = true;
					childItemCount = m_ui->bodyTreeWidget->topLevelItem(i)->childCount();
					treeKeyItem = m_ui->bodyTreeWidget->topLevelItem(i);
					break;
				}
			}
			if (!isFind) {
				treeKeyItem = new QTreeWidgetItem(m_ui->bodyTreeWidget, QStringList(key));
				treeKeyItem->setFlags(treeKeyItem->flags() | Qt::ItemIsUserCheckable | Qt::ItemIsEditable);
				treeKeyItem->setCheckState(0, Qt::Unchecked); // 设置初始状态为未选中
			}

		}
		//start = clock();
		for (const auto& modelData : vModelData) {
			//clock_t oneTimeStart = clock();
			//double oneTimeSeconds;
			if (modelData.type == 4) {
				//子节点内是否已经添加过相同的内容
				bool isFind = false;

				for (int i = 0; i < treeKeyItem->childCount(); ++i) {
					AiModelData modelDataAdded = qvariant_cast<AiModelData>(treeKeyItem->child(i)->data(0, Qt::UserRole));
					if (modelData == modelDataAdded) {
						isFind = true;
						break;
					}
				}
				if (!isFind) {
					treeKeyItem->setExpanded(true);
					std::string itemName = key.toStdString();
					if (++childItemCount > 1) {
						itemName += std::to_string(childItemCount);
					}
					QTreeWidgetItem* item = new QTreeWidgetItem(treeKeyItem, QStringList(itemName.c_str()));
					item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
					item->setCheckState(0, Qt::Unchecked); // 设置初始状态为未选中
					item->setData(0, Qt::UserRole, QVariant::fromValue(modelData));  // 设置自定义数据
					m_vShapeTreeItem.emplace_back(item);
				}
			}
			else if (modelData.type > 0 && modelData.type < 4) {
				//旧点线面列表
				{
					//std::vector<CellAttribData> celldatas = m_cellAttribDataMap[modelData.ObjName];
					//std::vector<NctiPosition> modelPts = modelData.pts;
					//Ncti_Long cellId = -1;
					//for (CellAttribData& celldata : celldatas) {
					//	if (celldata.hasUsed)
					//		continue;

					//	std::vector<NctiPosition> pts = celldata.attribPoints;
					//	if (NctiBaseUtility::same_points(modelPts, pts, NCTI_RESABS)) {
					//		cellId = celldata.cellId;
					//		celldata.hasUsed = true;
					//		break;
					//	}
					//}

					//if (cellId == -1) {
					//	if (modelData.type == 1 || modelData.type == 2) {
					//		//todo: 直接使用RemoveItem无法移除点，需要创建新点才能移除旧点
					//		QString segItemName = QString("%1-%2").arg(modelData.ObjName.c_str()).arg(cellId);
					//		NctiBaseView* pBaseView = m_pDocument->GetBaseModel()->GetFirstBaseView();
					//		auto pScenceItem = pBaseView->GetScene();
					//		NctiRenderSegmentItem* pSegItem = pScenceItem->Subsegment(segItemName.toStdString().c_str());
					//		pScenceItem->RemoveItem(pSegItem);
					//	}
					//	continue;
					//}

					//m_mapModelCellID.emplace(modelData, cellId);


				//	if (modelData.type == 1 || modelData.type == 2) {
				//		//根据名称和坐标，创建点

				//		QString segItemName = QString("%1-%2").arg(modelData.ObjName.c_str()).arg(cellId);
				//		CreateVertex(segItemName, modelData.pts[0]);
				//		m_vVertexName.emplace_back(segItemName);

				//	}
				//	QString itemName = GetItemName(key, modelData, cellId);
				//	QTreeWidgetItem* item = new QTreeWidgetItem(treeKeyItem, QStringList(itemName));
				//	item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
				//	item->setCheckState(0, Qt::Unchecked); // 设置初始状态为未选中
				//	item->setData(0, Qt::UserRole, QVariant::fromValue(modelData));  // 设置自定义数据
				//	m_vShapeTreeItem.emplace_back(item);
				}
				//新单特征页
				{
					treeKeyItem->setExpanded(true);
					std::string itemName = key.toStdString();
					if (++childItemCount > 1) {
						itemName += std::to_string(childItemCount);
					}
					QTreeWidgetItem* item = new QTreeWidgetItem(treeKeyItem, QStringList(itemName.c_str()));

					item->setFlags(item->flags() | Qt::ItemIsUserCheckable);

					item->setCheckState(0, Qt::Unchecked);

					item->setData(0, Qt::UserRole, QVariant::fromValue(modelData));

					m_vShapeTreeItem.emplace_back(item);

				}
			}
			else {
				//start = clock();

				//double addTreeItemPartTime;
				treeKeyItem->setExpanded(true);
				std::string itemName = key.toStdString();
				if (++childItemCount > 1) {
					itemName += std::to_string(childItemCount);
				}
				QTreeWidgetItem* item = new QTreeWidgetItem(treeKeyItem, QStringList(itemName.c_str()));

				item->setFlags(item->flags() | Qt::ItemIsUserCheckable); //25% time

				item->setCheckState(0, Qt::Unchecked); // 设置初始状态为未选中 //35% time

				item->setData(0, Qt::UserRole, QVariant::fromValue(modelData));  // 设置自定义数据 // 40% time

				//clock_t addTreeItemPartStart = clock();

				m_vShapeTreeItem.emplace_back(item);

				//clock_t addTreeItemPartEnd = clock();

				//end = clock();
				//cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
				//addTreeItemPartTime = ((double)(addTreeItemPartEnd - addTreeItemPartStart)) / CLOCKS_PER_SEC;
				//std::cout << "addTreeItem Time used: " << cpu_time_used << " seconds" << std::endl;
				//std::cout << "addTreeItemPart Time used: " << addTreeItemPartTime << " seconds" << std::endl;
				//std::cout << "add treeKeyItem time percent of oneTime: " << addTreeItemPartTime / cpu_time_used * 100.0 << " %" << std::endl;
			}
			//clock_t oneTimeEnd = clock();
			//oneTimeSeconds = ((double)(oneTimeEnd - oneTimeStart)) / CLOCKS_PER_SEC;
			//std::cout << "oneTime Time used: " << oneTimeSeconds << " seconds" << std::endl;
			//std::cout << "add treeKeyItem time percent of oneTime: " << cpu_time_used / oneTimeSeconds * 100.0 << " %" << std::endl;
		}
		//end = clock();
		//cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
		//std::cout << "for vModelData Time used: " << cpu_time_used << " seconds" << std::endl;
	}

	void NctiQtAIModelDataListDlg::HighLightBodys()
	{
		NctiBaseModel* pBaseModel = m_pDocument->GetBaseModel();
		if (m_highlighObjectSet.empty()) {
			if (pBaseModel) {
				NctiSelectionManager* pSelMan = NctiSelectionManager::GetSelectionManager(pBaseModel);
				pSelMan->ResetSelection();
				m_pDocument->GetBaseModel()->RefreshViews();
			}
		}
		else {
			if (pBaseModel) {
				//将指定实体高亮
				std::vector<NctiDisplayObject*> displayObjectVec(m_highlighObjectSet.begin(), m_highlighObjectSet.end());
				NctiDocElementPubFun::SetSelectionManager(displayObjectVec, pBaseModel->GetActiveBaseView());
				m_pDocument->GetBaseModel()->RefreshViews();
			}
		}
	}

	void NctiQtAIModelDataListDlg::SetHighLightBodys(QTreeWidgetItem* item)
	{
		if (!item)
			return;
		AiModelData modelData = qvariant_cast<AiModelData>(item->data(0, Qt::UserRole));
		if (modelData.type > 0) {
			return;
		}
		std::set<NctiDisplayObject*> displayObjectSet;
		//选中体
		NctiDisplayObject* pObj = nullptr;
		NctiDocElementPubFun::GetObjectListByName(m_pDocument, NctiDisplayModelBody::ID, modelData.ObjName.c_str(), pObj);
		if (pObj) {
			displayObjectSet.insert(pObj);
		}
		else {
			NctiDocElementPubFun::GetObjectListByName(m_pDocument, NctiDisplayBodyGroup::ID, modelData.ObjName.c_str(), pObj);
			if (pObj)
			{
				NctiDisplayObjectList List;
				((NctiDisplayBodyGroup*)pObj)->GetAllMembers(&List);
				List.Init();
				NctiDisplayObject* pObjBody = nullptr;
				while ((pObjBody = List.Next()) != nullptr)
				{
					displayObjectSet.insert(pObjBody);
				}
			}
		}

		if (item->checkState(0) == Qt::Checked) {
			for (auto& obj : displayObjectSet)
			{
				m_highlighObjectSet.insert(obj);
			}
		}
		else if (item->checkState(0) != Qt::Checked){
			for (auto& obj : displayObjectSet)
			{
				m_highlighObjectSet.erase(obj);
			}
		}
	}

	void NctiQtAIModelDataListDlg::HighLightFeatures()
	{
		std::unordered_map<std::string, std::vector<Ncti_Long>> mapCellID;
		for (const auto& item : m_vShapeTreeItem)
		{
			Qt::CheckState checkState = item->checkState(0);
			if (checkState != Qt::Checked) {
				continue;
			}

			AiModelData modelData = qvariant_cast<AiModelData>(item->data(0, Qt::UserRole));
			if (modelData.type > 0 && modelData.type <= 4)
			{

				for (const auto& id : modelData.featureIds)
				{
					Ncti_Long vCellID = id;
					auto it = mapCellID.find(modelData.ObjName);
					if (it != mapCellID.end())
					{
						it->second.push_back(vCellID);
					}
					else {
						std::vector<Ncti_Long> cells{ vCellID };
						mapCellID.emplace(modelData.ObjName, cells);
					}
				}
			}
		}

		NctiDocElementPubFun::SetSelectionByNameAndCellID(m_pDocument, mapCellID);
		m_pDocument->GetBaseModel()->RefreshViews();
	}

	Ncti_Long NctiQtAIModelDataListDlg::GetCellIdByModelData(const AiModelData& data)
	{
		auto it = m_mapModelCellID.find(data);
		if (it != m_mapModelCellID.end())
		{
			return it->second;
		}
		return -1;
	}

	void NctiQtAIModelDataListDlg::HighLightShapes()
	{
		std::unordered_map<std::string, std::vector<Ncti_Long>> mapCellID;
		for (const auto& item : m_vShapeTreeItem)
		{
			Qt::CheckState checkState = item->checkState(0);
			if (checkState != Qt::Checked) {
				continue;
			}

			AiModelData modelData = qvariant_cast<AiModelData>(item->data(0, Qt::UserRole));
			if (modelData.type == 0) {
				continue;
			}

			//选中点线面
			Ncti_Long vCellID = GetCellIdByModelData(modelData);
			if (vCellID == -1)
				continue;

			auto it = mapCellID.find(modelData.ObjName);
			if (it != mapCellID.end())
			{
				it->second.push_back(vCellID);
			}
			else {
				std::vector<Ncti_Long> cells{ vCellID };
				mapCellID.emplace(modelData.ObjName, cells);
			}
		}

		NctiDocElementPubFun::SetSelectionByNameAndCellID(m_pDocument, mapCellID);


		std::vector<QString> vShow;
		for (const auto& kv : mapCellID)
		{
			QString objName = kv.first.c_str();
			for (const auto& id : kv.second)
			{
				vShow.emplace_back(QString("%1-%2").arg(objName).arg(id));
			}
		}

		//根据名称显示点
		for (const auto& name : m_vVertexName)
		{
			ShowVertex(name, std::find(vShow.begin(), vShow.end(), name) != vShow.end());
		}

		m_pDocument->GetBaseModel()->RefreshViews();
	}

	bool NctiQtAIModelDataListDlg::CreateVertex(const QString& segItemName, const NctiPosition& pos)
	{
		NctiBaseView* pBaseView = m_pDocument->GetBaseModel()->GetFirstBaseView();
        auto pScenceItem = pBaseView->GetScene();
		NctiRenderSegmentItem* pSegItem = pBaseView->NewPreviewKey(segItemName.toStdString().c_str());
		if (pSegItem)
		{
			pSegItem->InsertVertex(pos);
			pSegItem->GetMaterialMappingControl()->SetVertexColor(RGBAColor(64, 64, 64));
			pSegItem->GetVisibilityControl()->SetVertexs(false);
			m_vSegmentItem.emplace_back(pSegItem);
			return true;
		}
		return false;
	}

	bool NctiQtAIModelDataListDlg::ShowVertex(const QString& segItemName, bool bShow)
	{
		NctiBaseView* pBaseView = m_pDocument->GetBaseModel()->GetFirstBaseView();
		NctiRenderSegmentItem* pSegItem = pBaseView->NewPreviewKey(segItemName.toStdString().c_str());
		if (pSegItem)
		{
			pSegItem->GetVisibilityControl()->SetVertexs(bShow);
			return true;
		}
		return false;
	}

	void NctiQtAIModelDataListDlg::InitCellMap()
	{
		m_cellAttribDataMap.clear();
		for (const auto& v : m_AiModelDataMap) {

			if (v.second.empty()) {
				continue;
			}

			for (const auto& modelData : v.second)
			{
				const Ncti_Char* objName = modelData.ObjName.c_str();
				if (m_cellAttribDataMap.find(modelData.ObjName) != m_cellAttribDataMap.end())
				{
					continue;
				}

				std::vector<NCTI_MODEL_TAG> cellVec;
				NctiDocElementPubFun::GetAllCellVec(m_pDocument, objName, cellVec);

				std::vector<CellAttribData> cellAttribVec;
				for (NCTI_MODEL_TAG cell : cellVec)
				{
					Ncti_Long cellId = *((Ncti_Long*)cell);
					std::vector<NctiPosition> pts;
					bool result = NctiDocElementPubFun::GetFaceAttribPoints(m_pDocument, objName, cellId, pts);
					CellAttribData cellAttribData{
						cellId,
						pts,
						false
					};
					cellAttribVec.push_back(cellAttribData);
				}

				m_cellAttribDataMap.emplace(modelData.ObjName, cellAttribVec);
			}
		}
	}

	void NctiQtAIModelDataListDlg::ClearVertex()
	{
		for (const auto& name : m_vVertexName)
		{
			ShowVertex(name, false);
		}
		m_vVertexName.clear();
		m_pDocument->GetBaseModel()->RefreshViews();
	}

	void NctiQtAIModelDataListDlg::RenameShapeItem(std::string& newLabel)
	{
		NctiBaseModel* pBaseModel = m_pDocument->GetBaseModel();
		if (pBaseModel)
		{
			NctiAiModelSystemObject* aiObject = NctiDocElementPubFun::GetAiModelSystemObject(pBaseModel);
			aiObject->RenameLabel(m_oldName, newLabel);
		}
	}

	void NctiQtAIModelDataListDlg::CheckedShapeItem(QTreeWidgetItem* item, int column)
	{
		// 只处理第一列
		if (column != 0)
		{
			return;
		}

		Qt::CheckState state = item->checkState(column);
		if (state == Qt::Checked || state == Qt::Unchecked) {

			int count = item->childCount();
			if (count > 0) {
				for (int i = 0; i < count; i++) {
					item->child(i)->setCheckState(0, state);
				}
			}
			else {
				//是子节点
				UpdateParentItemState(item);
			}
		}

		//HighLightShapes();
		HighLightFeatures();
	}

	void NctiQtAIModelDataListDlg::CheckedFeatureItem(QTreeWidgetItem* item, int column)
	{
		// 只处理第一列
		if (column != 0)
		{
			return;
		}

		Qt::CheckState state = item->checkState(column);
		if (state == Qt::Checked || state == Qt::Unchecked) {

			int count = item->childCount();
			if (count > 0) {
				for (int i = 0; i < count; i++) {
					item->child(i)->setCheckState(0, state);
				}
			}
			else {
				//是子节点
				UpdateParentItemState(item);
			}
		}

		HighLightFeatures();
	}

	void NctiQtAIModelDataListDlg::onShapeItemRename()
	{
		m_oldName = m_ui->shapeTreeWidget->currentItem()->text(0).toUtf8().data();
		m_ui->shapeTreeWidget->editItem(m_ui->shapeTreeWidget->currentItem());
	}

	void NctiQtAIModelDataListDlg::onShapeItemRemove()
	{
		QTreeWidgetItem* item = m_ui->shapeTreeWidget->currentItem();
		const std::string& removeLabel = item->text(0).toUtf8().data();
		NctiBaseModel* pBaseModel = m_pDocument->GetBaseModel();
		if (pBaseModel)
		{
			NctiAiModelSystemObject* aiObject = NctiDocElementPubFun::GetAiModelSystemObject(pBaseModel);
			aiObject->RemoveLabel(removeLabel);
		}

		for (size_t i = 0; i < item->childCount(); i++)
		{
			QTreeWidgetItem* childItem = item->child(i);
			auto it = m_vShapeTreeItem.begin();
			while (it != m_vShapeTreeItem.end() || *it == childItem)
			{
				m_vShapeTreeItem.erase(it);
				break;
			}
		}

		m_ui->shapeTreeWidget->removeItemWidget(item, 0);
		
		delete item;
	}

	NctiDisplayDocCustomContainer* NctiQtAIModelDataListDlg::GetDocModelContainer()
	{
		NctiBaseModel* pBaseModel = m_pDocument->GetBaseModel();
		NctiDisplayDocCustomContainer* pContainer = NctiDocElementPubFun::GetCurrenDocCustom(pBaseModel);
		return pContainer;
	}
	void NctiQtAIModelDataListDlg::GetAllBodyNames()
	{
		//获取所有实体
		NctiDisplayDocCustomContainer* pContainer = GetDocModelContainer();
		if (pContainer == nullptr)
			return;
		NctiDisplayObjectList cDoPropDoList;
		Ncti_Integer num = pContainer->GetAllDisplayObjectsByType(&cDoPropDoList, NctiDisplayModelBody::ID);

		pContainer->GetAllDisplayObjectsByType(&cDoPropDoList);
		cDoPropDoList.Init();
		NctiDisplayObject* pObj = nullptr;
		NctiDisplayObjectList ObjListResult;
		while ((pObj = cDoPropDoList.Next()) != nullptr)
		{
			if (pObj->IsTypeName(NctiDisplayModelBody::ID))
			{
				NctiDisplayModelBody* pBody = (NctiDisplayModelBody*)pObj;
				if (pBody)
				{
					std::string objectName = pBody->GetObjName() ? pBody->GetObjName() : "";
					m_setAllBodyNames.insert(objectName);
				}
			}
		}
	}

	void NctiQtAIModelDataListDlg::GetAllLabledObjectNames()
	{
		//group就遍历获取所有object
	}

	void NctiQtAIModelDataListDlg::ClearAiLabelType()
	{
		m_mapAiLabelType.clear();
	}

	void NctiQtAIModelDataListDlg::RefreshAiLabelType()
	{
		for (auto& aiModelPair : m_AiModelDataMap)
		{
			std::string labelName = aiModelPair.first;
			if (m_mapAiLabelType.find(labelName) == m_mapAiLabelType.end())
			{
				const std::vector<AiModelData>& aiModelVec = aiModelPair.second;
				if (!aiModelVec.empty())
				{
					m_mapAiLabelType[labelName] = aiModelVec[0].type;
				}
			}
		}
	}

	void NctiQtAIModelDataListDlg::CheckedBodyItem(QTreeWidgetItem* item, int column)
	{

		// 只处理第一列
		if (column != 0)
		{
			return;
		}

		Qt::CheckState state = item->checkState(column);
		if (state == Qt::Checked || state == Qt::Unchecked) {

			int count = item->childCount();
			if (count > 0) {
				for (int i = 0; i < count; i++) {
					item->child(i)->setCheckState(0, state);
				}
			}
			else {
				//是子节点
				UpdateParentItemState(item);
			}
		}
		SetHighLightBodys(item);
		HighLightBodys();
	}	

	void NctiQtAIModelDataListDlg::InitAiLabelTree()
	{

	}

	void NctiQtAIModelDataListDlg::TraverseItemToExport(QTreeWidgetItem* item, const QString& selectedPath, const QString& prefix, const int useType)
	{
		if (item) {
			NctiDisplayObject* pDisplayObj = nullptr;
			AiModelData modelData = qvariant_cast<AiModelData>(item->data(0, Qt::UserRole));
			if (!modelData.ObjName.empty()) {
				QString labelName = item->text(0);
				bool checked = item->checkState(0) == Qt::Checked;
				if (modelData.type == -1) {
					NctiDocElementPubFun::GetObjectListByName(m_pDocument, NctiDisplayBodyGroup::ID, modelData.ObjName.c_str(), pDisplayObj);
					NctiDisplayObjectList List;
					((NctiDisplayBodyGroup*)pDisplayObj)->GetAllMembers(&List); //包含了组Group
					List.Init();
					NctiDisplayObject* pObjBody = nullptr;
					std::vector<NctiDisplayObject*> pDisplayObjectVec;
					std::vector<NCTI_MODEL_TAG> pOutputDataVec;
					while ((pObjBody = List.Next()) != nullptr) {
						if (std::find(pDisplayObjectVec.begin(), pDisplayObjectVec.end(), pObjBody) == pDisplayObjectVec.end()) {
							pDisplayObjectVec.push_back(pObjBody);
							if (useType == 1) {
								if (checked) {
									if (pObjBody->IsTypeName(NctiDisplayModelBody::ID)) {
										pOutputDataVec.push_back(((NctiDisplayModelBody*)pObjBody)->GetNctiBody());
									}
								}
							}
							else { //0
								if (pObjBody->IsTypeName(NctiDisplayModelBody::ID)) {
									m_setOutputBodyNames.insert(pObjBody->GetObjName());
								}
							}
						}
					}
					if (useType == 1) {
						ExportModels(selectedPath, pOutputDataVec, prefix + labelName);
					}
				}
				else {
					NctiDocElementPubFun::GetObjectListByName(m_pDocument, NctiDisplayModelBody::ID, modelData.ObjName.c_str(), pDisplayObj);
					if (pDisplayObj) {
						std::vector< NCTI_MODEL_TAG> pOutputDataVec{ ((NctiDisplayModelBody*)pDisplayObj)->GetNctiBody() };
						if (useType == 1 && checked) {
							ExportModels(selectedPath, pOutputDataVec, prefix + labelName);
						}
						else { //0
							m_setOutputBodyNames.insert(pDisplayObj->GetObjName());
						}
					}
				}
			}
			// 递归遍历当前节点的子节点
			for (int i = 0; i < item->childCount(); ++i) {
				TraverseItemToExport(item->child(i), selectedPath, prefix, useType);
			}
		}
	}

	void NctiQtAIModelDataListDlg::TraverseFeatureItemToExport(QTreeWidgetItem* item, std::vector<NCTI_MODEL_TAG>& pOutputDataVec, std::vector<AiModelData>& setAiModel)
	{
		if (!item)
			return;
		NctiDisplayDocCustomContainer* pContainer = GetDocModelContainer();
		if (pContainer) {
			bool checked = item->checkState(0) == Qt::Checked;
			if (checked) {
				std::string labelName = item->text(0).toStdString();
				AiModelData modelData = qvariant_cast<AiModelData>(item->data(0, Qt::UserRole));
				if (std::find(setAiModel.begin(), setAiModel.end(), modelData) == setAiModel.end()) {
					setAiModel.push_back(modelData);
				}
				NctiDisplayObject* pDisplayObj = nullptr;
				NctiDocElementPubFun::GetObjectListByName(m_pDocument, NctiDisplayModelBody::ID, modelData.ObjName.c_str(), pDisplayObj);
				if (pDisplayObj) {
					NctiDisplayModelBody* pModelBody = (NctiDisplayModelBody*)pDisplayObj;
					for (const auto id : modelData.featureIds) {
						NCTI_MODEL_TAG modelFace = nullptr;
						pContainer->get_void_from_tag(pModelBody, modelFace, id);
						if (modelFace == nullptr)
							continue;
						NCTI_MODEL_TAG pResultBody = nullptr;
						NctiGeometryResult ModelFunctionResult = NctiGeometryFunction::extract_cell(pContainer, pModelBody->GetNctiBody(), modelFace, pResultBody);
						pOutputDataVec.push_back(pResultBody);
					}
				}
			}
		}

		// 递归遍历当前节点的子节点
		for (int i = 0; i < item->childCount(); ++i) {
			TraverseFeatureItemToExport(item->child(i), pOutputDataVec, setAiModel);
		}
	}

	void NctiQtAIModelDataListDlg::TraverseFeatureItemBodyToExport(QTreeWidgetItem* item, std::map<QString, std::pair<QString, NCTI_MODEL_TAG>>& objectMap)
	{
		if (!item)
			return;
		Qt::CheckState checkState = item->checkState(0);
		if (checkState == Qt::Checked) {
			NctiDisplayDocCustomContainer* pContainer = GetDocModelContainer();
			if (pContainer) {
				AiModelData modelData = qvariant_cast<AiModelData>(item->data(0, Qt::UserRole));
				NctiDisplayObject* pDisplayObj = nullptr;
				NctiDocElementPubFun::GetObjectListByName(m_pDocument, NctiDisplayModelBody::ID, modelData.ObjName.c_str(), pDisplayObj);
				QStringList qList;
				if (pDisplayObj) {
					qList.append(modelData.ObjName.c_str());
					QString name = GetObjectTreeItemName(qList);
					if (pDisplayObj) {
						std::pair<QString, NCTI_MODEL_TAG> pairBody{ name, ((NctiDisplayModelBody*)pDisplayObj)->GetNctiBody() };
						objectMap.insert(std::pair<QString, std::pair<QString, NCTI_MODEL_TAG>>(QString(modelData.ObjName.c_str()), pairBody ));
					}
				}
			}
		}
		// 递归遍历当前节点的子节点
		for (int i = 0; i < item->childCount(); ++i) {
			TraverseFeatureItemBodyToExport(item->child(i), objectMap);
		}
	}

	void NctiQtAIModelDataListDlg::ExportModels(const QString& directory, std::vector<NCTI_MODEL_TAG>& i_vModels, const QString& modelName)
	{
			QString qFile = "\\" + modelName + ".stp";
			QString qPath = directory + qFile;
			//DEBUG [
			NctiDebug::debug(modelName.toStdString().c_str());
			NctiDebug::debug(qPath.toStdString().c_str());
			//]
			QByteArray ba = qPath.toUtf8();
			NctiGeometryFunction::export_file(GetDocModelContainer(), ba.data(), i_vModels);
	}

	void NctiQtAIModelDataListDlg::TraverseItemToSelect(QTreeWidgetItem* item, const int useType)
	{
		if (!item)
			return;
		if (useType == 0)
		{
			item->setCheckState(0, Qt::Unchecked);
		}
		else
		{
			item->setCheckState(0, Qt::Checked);
		}
		SetHighLightBodys(item);
		// 递归遍历当前节点的子节点
		for (int i = 0; i < item->childCount(); ++i) {
			TraverseItemToSelect(item->child(i), useType);
		}
	}

	void NctiQtAIModelDataListDlg::RemoveCheckedBodyItem()
	{
		bool isRemoveAction = false;
		for (auto iter = m_vShapeTreeItem.begin(); iter != m_vShapeTreeItem.end(); ++iter) {
			
			Qt::CheckState checkState = (*iter)->checkState(0);
			if (checkState != Qt::Checked) {
				continue;
			}
			AiModelData modelData = qvariant_cast<AiModelData>((*iter)->data(0, Qt::UserRole));

			isRemoveAction = true;
			QString labelName;
			if ((*iter)->parent()) {
				labelName = (*iter)->parent()->text(0);
			}
			else {
				labelName = (*iter)->text(0);
			}
			//删除子节点
			if ((*iter)->parent()) {
				(*iter)->parent()->removeChild((*iter));
			}
			delete (*iter);
			//注意先删除迭代器指向的内容，再移除迭代器！
			m_vShapeTreeItem.erase(iter);

			//移除数据
			RemoveAiModelData(labelName, modelData);

            Q_EMIT sigRemoveLabelItem(QString(modelData.ObjName.c_str()));

			break;
		}
		//因为迭代器发生了变化，所以不用一个循环遍历而要用递归，每次执行用新的迭代器
		if (isRemoveAction) {
			RemoveCheckedBodyItem();
		}
		RefreshModelData(nullptr);
	} 

	bool NctiQtAIModelDataListDlg::BodyIsLabeled(const AiModelData& i_modelData)
	{
		//一个实体已经被标记为某个标签，不允许再标记为其他标签
		for (auto iter = m_vShapeTreeItem.begin(); iter != m_vShapeTreeItem.end(); ++iter) {

			AiModelData modelData = qvariant_cast<AiModelData>((*iter)->data(0, Qt::UserRole));
			if (modelData.type > 0) {
				continue;
			}
			if (modelData.ObjName == i_modelData.ObjName) {
				return true;
			}
		}
		return false;
	}

	void NctiQtAIModelDataListDlg::RemoveAiModelData(const QString& i_label, const AiModelData& i_modelData)
	{
		if (m_pDocument == nullptr)
			return;
		//把选中的实体打标签
		NctiBaseModel* pBaseModel = m_pDocument->GetBaseModel();
		NctiCommandManager* pComMan = NctiCommandManager::GetCommandManager(pBaseModel);
		if (pComMan)
		{
			std::string featureIdsString = IdsToString(i_modelData.featureIds);
			NctiArgumentObject argumentObject;
			std::vector<std::string> args{
				i_label.toStdString(),
				i_modelData.ObjName,
				std::to_string(i_modelData.type),
				featureIdsString,
				std::to_string(i_modelData.faceType),
				std::to_string(i_modelData.objectId)
			};

			std::vector<NCTI_MODEL_TAG> cellsVec;
			argumentObject.SetCommandArgumentVec(args);

			EnumNctiResult result = pComMan->RunCommand("cmd_ncti_ai_model_remove_label", &argumentObject);
		}
	}

	bool NctiQtAIModelDataListDlg::ShowConfirmDialog(QWidget* parent, const QString& title, const QString& text)
	{
		QMessageBox msgBox;
		msgBox.setIcon(QMessageBox::Question);
		msgBox.setWindowTitle(title);
		msgBox.setText(text);
		msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
		msgBox.setDefaultButton(QMessageBox::No); // 默认取消

		int ret = msgBox.exec(); // 模态对话框，阻塞当前流程

		return (ret == QMessageBox::Yes); // 返回 true 表示确定，false 表示取消
	}

	std::string NctiQtAIModelDataListDlg::IdsToString(const std::set<Ncti_Integer>& featureIds)
	{
		std::string result;
		for (const auto& ele : featureIds)
		{
			result += std::to_string(ele);
			result += ",";
		}
		result = result.substr(0, result.size() - 1);
		return result;
	}
	
    bool NctiQtAIModelDataListDlg::WriteStringFile(const QString& content, const QString& directory, const QString& fileName)
    {
        QString filePath = directory + "\\" + fileName;
        QFile file(filePath);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream out(&file);
#if QT_VERSION_MAJOR >= 6
            out.setEncoding(QStringConverter::Utf8);
#else
            out.setCodec("UTF-8");
#endif
            file.write(content.toUtf8());
            out.flush();
            file.close();
            return true;
        }
        return false;
    }

	QString NctiQtAIModelDataListDlg::GetObjectTreeItemName(QStringList& objectNames)
	{
		QString name;
		if (m_objectTree)
		{
			QModelIndexList selectIndex = m_objectTree->GetIndexListByNames(1, objectNames);
			for (auto& modelIndex : selectIndex)
			{
				NctiTreeItem* item = m_objectTree->GetItemByIndex(1, modelIndex);
				if (item)
				{
					name = item->getItemName();
				}
			}
		}

		return name;
	}


}//namespace NCTI
