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

#include "NctiAiRecognitionListDlg.h"

#include <QMessageBox>

#include "NctiDocument.h"
#include "NctiBaseModel.h"
#include "NctiDocElementPubFun.h"
#include "NctiDisplayAiAttriTopoMesh.h"
#include "NctiDisplayDocCustomContainer.h"
#include "NctiDisplayModelBody.h"
#include "NctiDisplayObjectList.h"
#include "NctiAiModelSystemObject.h"
#include "NctiDocViewManager.h"
#include "NctiBaseUtility.h"
#include "NctiString.h"
#include "NctiPosition.h"
#include "NctiTopoShape.h"
#include "NctiTopoFace.h"
#include "NctiTopoEdge.h"
#include "NctiTopoEdgeCurve.h"
#include "NctiDeleteTool.h"
using namespace NCTI;

bool isHandlingChanged = false;

NctiAiRecognitionListDlg::NctiAiRecognitionListDlg(NctiDocument* i_pDocument, QWidget* i_parent, const std::string& i_recogType)
    : QWidget(i_parent)
    , m_ui(new Ui::NctiQtAiRecognitionListDlg())
    , m_pDocument(i_pDocument)
    , m_recogType(i_recogType)
{
    Init();
}

NctiAiRecognitionListDlg::~NctiAiRecognitionListDlg()
{
    NCTI_DELETE m_ui;
}

void NCTI::NctiAiRecognitionListDlg::RefreshButtonClick()
{
    NctiBaseModel* pBaseModel = m_pDocument->GetBaseModel();
    NctiDeleteTool::RemoveFeature(pBaseModel);

    m_AiRecogDatas.clear();
    m_ui->treeWidget->clear();
    m_TreeItem.clear();

    NctiDocViewManager* pDocView = NctiDocViewManager::GetDocViewManager(pBaseModel);
    NctiDisplayObjectList ObjListResult;
    for (const auto& item : m_topoMeshes)
    {
        ObjListResult.AddData(item);

        NctiDisplayDocCustomContainer* pDocCus = (NctiDisplayDocCustomContainer*)item->GetDocContainer();
        pDocView->RemoveDisplayObjects(pDocCus, &ObjListResult);
    };
    m_topoMeshes.clear();

    InitData();
    InitTree();
}

void NCTI::NctiAiRecognitionListDlg::SearchButtonClick()
{
    std::vector<NctiDisplayObject*> displayobj;
    std::vector<NCTI_MODEL_TAG> cells;
    NctiDocElementPubFun::GetDisplayObjectFromSelManager(m_pDocument, displayobj, cells);
    if (cells.size() == 0)
        return;

    Ncti_Integer id = *((Ncti_Integer*)cells[0]);
    QList<QTreeWidgetItem*> items = m_ui->treeWidget->findItems("", Qt::MatchContains | Qt::MatchRecursive);
    for (QTreeWidgetItem* item : items) {
        QString itemTag = item->data(0, Qt::UserRole).toString();
        if (itemTag == QString::number(id)) {
            m_ui->treeWidget->setCurrentItem(item); // 选中节点
            m_ui->treeWidget->scrollToItem(item);  // 滚动到节点
            QTreeWidgetItem* rootItem = item->parent()->parent();
            rootItem->setCheckState(0, Qt::CheckState::Checked);
            return;
        }
    }
    QMessageBox::information(nullptr, "未找到", "未找到标记为 " + QString::number(id) + " 的节点");
}

void NctiAiRecognitionListDlg::Init()
{
    m_ui->setupUi(this);
    this->setWindowFlags(Qt::Dialog);
    this->setWindowModality(Qt::NonModal);

    setWindowTitle(QString::fromUtf16(u"AI识别列表"));

    m_ui->treeWidget->setSelectionMode(QTreeWidget::ExtendedSelection); // 允许多选
    m_ui->treeWidget->setDragDropMode(QTreeWidget::NoDragDrop);
    m_ui->treeWidget->header()->hide();
    m_ui->treeWidget->header()->setSectionResizeMode(QHeaderView::ResizeToContents); // 自适应列宽
    connect(m_ui->treeWidget, &QTreeWidget::itemChanged, this, &NctiAiRecognitionListDlg::onRecogItemClicked);
    connect(m_ui->pushButton_refresh, SIGNAL(clicked()), this, SLOT(RefreshButtonClick()));
    connect(m_ui->pushButton_search, SIGNAL(clicked()), this, SLOT(SearchButtonClick()));

    InitData();
    InitTree();
}

std::vector<Ncti_Long>& GetCellGroup(Ncti_Long cellId, std::vector<std::vector<Ncti_Long>>& cellGroups)
{
    for (auto& group : cellGroups)
    {
        if (std::find(group.begin(), group.end(), cellId) != group.end())
        {
            return group;
        }
    }
    static std::vector<Ncti_Long> emptyResult;
    return emptyResult;
}

void NCTI::NctiAiRecognitionListDlg::InitTree()
{
    for (const AiRecognitionData& recogData : m_AiRecogDatas)
    {
        const std::string& label = recogData.m_LabelName;
        QTreeWidgetItem* labelItem = new QTreeWidgetItem(m_ui->treeWidget, QStringList(label.c_str()));
        labelItem->setFlags(labelItem->flags() | Qt::ItemIsUserCheckable | Qt::ItemIsEditable);
        labelItem->setCheckState(0, Qt::Unchecked);
        labelItem->setExpanded(true);

        for (const AiRecogObject& object : recogData.m_Objects)
        {
            const std::string& objectName = object.m_ObjectName;
            std::vector<Ncti_Long> cellIds = object.m_CellId;

            std::sort(cellIds.begin(), cellIds.end());
            std::vector<std::pair<Ncti_Integer, Ncti_Integer>> topIds;
            GetTopoRelation(objectName.c_str(), topIds);

            std::vector<std::vector<Ncti_Long>> cellGroups;
            GroupCellIdByTopo(cellIds, topIds, cellGroups);

            std::vector<std::map<std::string, std::vector<Ncti_Long>>> cellGroupsByArea;
            //GroupCellIdByArea(faceAttrs, cellGroups, cellGroupsByArea);

            GroupCellIdByRadius(objectName.c_str(), cellGroups, cellGroupsByArea);

            for (size_t i = 0; i < cellGroupsByArea.size(); i++)
            {
                QString groupName = QString("Group%1").arg(i + 1);
                QTreeWidgetItem* groupitem = new QTreeWidgetItem(labelItem);
                groupitem->setFlags(groupitem->flags() | Qt::ItemIsUserCheckable);
                groupitem->setCheckState(0, Qt::Unchecked);
                const std::map<std::string, std::vector<Ncti_Long>>& cellGroupMap = cellGroupsByArea[i];
                for (const auto& cellData : cellGroupMap) 
                {
                    QString areGroupName = QString(cellData.first.c_str());

                    groupName = QString("%1-%2").arg(groupName, areGroupName);
                    QTreeWidgetItem* areaGroupItem = new QTreeWidgetItem(groupitem, QStringList(areGroupName));
                    const std::vector<Ncti_Long>& cellGroup = cellData.second;
                    for (const Ncti_Long& cellId : cellGroup)
                    {
                        QString itemName = QString("%1-%2").arg(objectName.c_str()).arg(cellId);
                        QTreeWidgetItem* item = new QTreeWidgetItem(areaGroupItem, QStringList(itemName));
                        item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
                        item->setCheckState(0, Qt::Unchecked);
                        item->setData(0, Qt::UserRole, QVariant::fromValue(cellId));
                        item->setData(0, Qt::UserRole + 1, objectName.c_str());
                        m_TreeItem.emplace_back(item);
                    }
                }
                groupitem->setText(0, groupName);
            }
        }
    }
}

void NCTI::NctiAiRecognitionListDlg::InitData()
{
    NctiBaseModel* pBaseModel = m_pDocument->GetBaseModel();
    if (pBaseModel)
    {
        NctiAiModelSystemObject* aiObject = NctiDocElementPubFun::GetAiModelSystemObject(pBaseModel);
        if (aiObject == nullptr)
            return;
        const auto& aiModelDataMap = aiObject->GetLabelMap();
        if (aiModelDataMap.find(m_recogType) == aiModelDataMap.end())
        {
            return;
        }
        const auto& roundDataMap = aiModelDataMap.at(m_recogType);

        std::vector<AiRecogObject> recogObjects;

        std::map<std::string, std::vector<CellAttribData>> objectCellMap;
        UpdateObjectCellId(roundDataMap, objectCellMap);
        
        for (const AiModelData& modelData : roundDataMap)
        {
            const std::string& objName = modelData.ObjName;
            if (objectCellMap.find(objName) == objectCellMap.end()) {
                continue;
            }

            const auto& result = std::find_if(recogObjects.begin(), recogObjects.end(), [=](const AiRecogObject& i) {return i.m_ObjectName == modelData.ObjName; });
            if (result == recogObjects.end())
            {
                AiRecogObject recogObject;
                recogObject.m_ObjectName = modelData.ObjName;
                recogObjects.push_back(recogObject);
            }

            const auto& datait = std::find_if(recogObjects.begin(), recogObjects.end(), [=](const AiRecogObject& i) {return i.m_ObjectName == modelData.ObjName; });
            AiRecogObject& recogObject = *datait;

            std::vector<CellAttribData> celldatas = objectCellMap[modelData.ObjName];
            std::vector<NctiPosition> modelPts = modelData.pts;
            Ncti_Long cellId = -1;
            for (CellAttribData& celldata : celldatas)
            {
                if (celldata.hasUsed)
                    continue;

                std::vector<NctiPosition> pts = celldata.attribPoints;
                if (NctiBaseUtility::same_points(modelPts, pts, NCTI_RESABS))
                {
                    cellId = celldata.cellId;
                    celldata.hasUsed = true;
                    break;
                }
            }
            if (cellId == -1)
                continue;

            recogObject.m_CellId.push_back(cellId);
        }
        AiRecognitionData recogData;
        recogData.m_LabelName = m_recogType;
        recogData.m_Objects = recogObjects;
        m_AiRecogDatas.push_back(recogData);
    }
}

void NCTI::NctiAiRecognitionListDlg::UpdateObjectCellId(const std::vector<AiModelData>& aiModelDatas, std::map<std::string, std::vector<CellAttribData>>& o_objectCellMap)
{
    for (const AiModelData& modelData : aiModelDatas)
    {
        std::string objName = modelData.ObjName;
        if (o_objectCellMap.find(objName) != o_objectCellMap.end())
        {
            continue;
        }

        std::vector<NCTI_MODEL_TAG> cellVec;
        NctiDocElementPubFun::GetAllCellVec(m_pDocument, objName.c_str(), cellVec);
        if (cellVec.size() == 0) {
            continue;
        }

        std::vector<CellAttribData> cellAttribVec;
        for (NCTI_MODEL_TAG cell : cellVec)
        {
            Ncti_Long cellId = *((Ncti_Long*)cell);
            std::vector<NctiPosition> pts;
            bool result = NctiDocElementPubFun::GetFaceAttribPoints(m_pDocument, objName.c_str(), cellId, pts);
            CellAttribData cellAttribData{
                cellId,
                pts,
                false
            };
            cellAttribVec.push_back(cellAttribData);
        }
        o_objectCellMap.emplace(objName, cellAttribVec);
    }
}

void NCTI::NctiAiRecognitionListDlg::UpdateParentItemState(QTreeWidgetItem* item)
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

void NCTI::NctiAiRecognitionListDlg::HighLightCells()
{
    std::unordered_map<std::string, std::vector<Ncti_Long>> mapCellID;
    for (const auto& item : m_TreeItem)
    {
        Qt::CheckState checkState = item->checkState(0);
        if (checkState != Qt::Checked) {
            continue;
        }

        Ncti_Long cellId = item->data(0, Qt::UserRole).toInt();
        QString qObjName = item->data(0, Qt::UserRole + 1).toString();
        QByteArray nameBytes = qObjName.toUtf8();
        const char* objName = nameBytes.data();

        auto it = mapCellID.find(objName);
        if (it != mapCellID.end())
        {
            it->second.push_back(cellId);
        }
        else {
            std::vector<Ncti_Long> cells{ cellId };
            mapCellID.emplace(objName, cells);
        }
    }

    NctiDocElementPubFun::SetSelectionByNameAndCellID(m_pDocument, mapCellID);
    m_pDocument->GetBaseModel()->RefreshViews();
}

void NCTI::NctiAiRecognitionListDlg::GroupCellIdByTopo(const std::vector<Ncti_Long>& cellIds, const std::vector<std::pair<Ncti_Integer, Ncti_Integer>>& topIds, std::vector<std::vector<Ncti_Long>>& o_cellGroups)
{
    std::map<Ncti_Long, std::vector<Ncti_Long>> topoIdMap;

    for (const auto& topoPair : topIds)
    {
        Ncti_Long firstId = topoPair.first;
        Ncti_Long nextId = topoPair.second;

        if (topoIdMap.find(firstId) == topoIdMap.end())
        {
            std::vector<Ncti_Long> cellIdVec{ nextId };
            topoIdMap.emplace(firstId, cellIdVec);
        }
        else
        {
            std::vector<Ncti_Long>& cellIdVec = topoIdMap.at(firstId);
            cellIdVec.push_back(nextId);
        }

        if (topoIdMap.find(nextId) == topoIdMap.end())
        {
            std::vector<Ncti_Long> cellIdVec{ firstId };
            topoIdMap.emplace(nextId, cellIdVec);
        }
        else
        {
            std::vector<Ncti_Long>& cellIdVec = topoIdMap.at(nextId);
            cellIdVec.push_back(firstId);
        }
    }

    for (size_t i = 0; i < cellIds.size(); i++)
    {
        Ncti_Long currentCellId = cellIds[i];

        if (topoIdMap.find(currentCellId) == topoIdMap.end())
        {
            continue;
        }
        const std::vector<Ncti_Long>& nextIds = topoIdMap.at(currentCellId);

        for (Ncti_Long nextId : nextIds)
        {
            {
                std::vector<Ncti_Long>& currentGroup = GetCellGroup(currentCellId, o_cellGroups);
                if (currentGroup.empty())
                {
                    auto result = std::find(cellIds.begin() + i, cellIds.end(), nextId);
                    if (result == cellIds.end())
                    {
                        std::vector<Ncti_Long> newGroup{ currentCellId };
                        o_cellGroups.push_back(newGroup);
                    }
                    else
                    {
                        std::vector<Ncti_Long>& group = GetCellGroup(nextId, o_cellGroups);
                        if (group.empty())
                        {
                            std::vector<Ncti_Long> newGroup{ currentCellId, nextId };
                            o_cellGroups.push_back(newGroup);
                        }
                        else
                        {
                            group.push_back(currentCellId);
                        }
                    }
                    continue;
                }
            }

            auto result = std::find(cellIds.begin() + i, cellIds.end(), nextId);
            if (result == cellIds.end())
                continue;

            {
                std::vector<Ncti_Long>& currentGroup = GetCellGroup(currentCellId, o_cellGroups);
                if (!currentGroup.empty())
                {
                    if (std::find(currentGroup.begin(), currentGroup.end(), nextId) != currentGroup.end())
                    {
                        continue;
                    }

                    std::vector<Ncti_Long>& nextIdGroup = GetCellGroup(nextId, o_cellGroups);
                    if (!nextIdGroup.empty()) 
                    {
                        currentGroup.insert(currentGroup.end(), nextIdGroup.begin(), nextIdGroup.end());
                        auto it = std::remove(o_cellGroups.begin(), o_cellGroups.end(), nextIdGroup);
                        o_cellGroups.erase(it, o_cellGroups.end());
                        continue;
                    }

                    currentGroup.push_back(nextId);
                    continue;
                }
            }

            {
                std::vector<Ncti_Long>& currentGroup = GetCellGroup(nextId, o_cellGroups);
                if (currentGroup.empty())
                {
                    std::vector<Ncti_Long> newGroup{ currentCellId,nextId };
                    o_cellGroups.push_back(newGroup);
                    continue;
                }
                else {
                    currentGroup.push_back(currentCellId);
                }
            }
        }
    }
}

void NCTI::NctiAiRecognitionListDlg::GroupCellIdByArea(const std::vector<AiFaceAttr>& faceAttrs, const std::vector<std::vector<Ncti_Long>>& cellGroups, std::vector<std::map<std::string, std::vector<Ncti_Long>>>& o_cellGroups)
{
    Ncti_Double groupCount = 3;
    for (const auto& cellGroup : cellGroups)
    {

        Ncti_Double maxArea = -INFINITY;
        for (Ncti_Long cellId : cellGroup)
        {
            const AiFaceAttr& faceAttr = faceAttrs[cellId];
            Ncti_Double mass = faceAttr.m_Mass;
            if (maxArea < mass)
                maxArea = mass;
        }

        std::map<Ncti_Double, std::string> areaMap;
        for (Ncti_Long i = 0; i < groupCount; i++)
        {
            Ncti_Double maxValue = maxArea / groupCount * (i + 1);
            std::string maxName = NctiString::double_to_string(maxArea / groupCount * (i + 1));
            std::string minName = NctiString::double_to_string(maxArea / groupCount * i);
            std::string groupName = minName + "~" + maxName;
            areaMap.emplace(maxValue, groupName);

        }

        std::map<std::string, std::vector<Ncti_Long>> areaGroup;
        for (Ncti_Long cellId : cellGroup)
        {
            const AiFaceAttr& faceAttr = faceAttrs[cellId];
            Ncti_Double mass = faceAttr.m_Mass;

            for (const auto& areaData : areaMap)
            {
                if (mass < areaData.first || abs(mass - areaData.first) < 10e-10)
                {
                    std::string groupName = areaData.second;
                    if (areaGroup.find(groupName) == areaGroup.end())
                    {
                        std::vector<Ncti_Long> cellids{ cellId };
                        areaGroup.emplace(groupName, cellids);
                    }
                    else
                    {
                        areaGroup[groupName].push_back(cellId);
                    }
                    break;
                }
            }

        }
        o_cellGroups.push_back(areaGroup);
    }
}

void NCTI::NctiAiRecognitionListDlg::GroupCellIdByRadius(const char* c_ObjName, const std::vector<std::vector<Ncti_Long>>& cellGroups, std::vector<std::map<std::string, std::vector<Ncti_Long>>>& o_cellGroups)
{
    for (const auto& cellGroup : cellGroups)
    {
        std::map<std::string, std::vector<Ncti_Long>> radiusGroup;
        for (Ncti_Long cellId : cellGroup)
        {
            Ncti_Double radius = 0.0;
            Ncti_Boolean res = NctiDocElementPubFun::GetCylindricalSurfaceRadius(m_pDocument, c_ObjName, cellId, radius);

            std::string sRadius = res ? NctiString::double_to_string(radius, 3) : "Other";

            if (radiusGroup.find(sRadius) == radiusGroup.end())
            {
                std::vector<Ncti_Long> cellids{ cellId };
                radiusGroup.emplace(sRadius, cellids);
            }
            else
            {
                radiusGroup[sRadius].push_back(cellId);
            }
        }
        o_cellGroups.push_back(radiusGroup);
    }
}

void NCTI::NctiAiRecognitionListDlg::UpdateCheckState(QTreeWidgetItem* item, Qt::CheckState state)
{
    int count = item->childCount();
    for (int i = 0; i < count; i++) {
        QTreeWidgetItem* child = item->child(i);
        child->setCheckState(0, state);
        UpdateCheckState(child, state);
    }
}

void NCTI::NctiAiRecognitionListDlg::GetTopoRelation(const char* c_ObjName, std::vector<std::pair<Ncti_Integer, Ncti_Integer>>& faceTopoIDs)
{
    NctiDisplayObject* pObj = nullptr;
    NctiBaseModel* pBaseModel = m_pDocument->GetBaseModel();
    NctiDocElementPubFun::GetObjectListByName(pBaseModel, NctiDisplayModelBody::ID, c_ObjName, pObj);

    NctiDisplayModelBody* pModelBody = (NctiDisplayModelBody*)pObj;
    NCTI_MODEL_TAG pBody = pModelBody->GetNctiBody();
    NctiDisplayDocCustomContainer* pDocCus = (NctiDisplayDocCustomContainer*)pModelBody->GetDocContainer();

    //NctiDisplayModelBody ModelBodyHelp;
    //ModelBodyHelp.SetNctiBody(pBody);
    //ModelBodyHelp.SetObjName(pModelBody->GetObjName());
    std::vector<Ncti_Integer> faceFIDs;
    std::vector<Ncti_Integer> faceEIDs;
    std::vector<Ncti_Integer> faceIDs;

    NCTI_MODEL_TAG pGECell = nullptr;
    pDocCus->get_gecell(pBody, pBody, pGECell);
    if (!pGECell)
    {
        return;
    }
    NctiTopoShape* pTopoShape = (NctiTopoShape*)pGECell;
    std::vector<NctiTopoShape*> TopoShapeVec = pTopoShape->GetShapeVec();

    for (Ncti_Size i = 0; i < TopoShapeVec.size(); i++)
    {
        if (TopoShapeVec[i]->IsTypeName(NctiTopoFace::ID)) {
            NctiTopoFace* pTopoFace = (NctiTopoFace*)TopoShapeVec[i];
            Ncti_Long id;
            pDocCus->get_persistent_tag(pModelBody, pTopoFace->GetLinkVoid(), id);
            faceIDs.push_back(id);
        }
        if (TopoShapeVec[i]->IsTypeName(NctiTopoEdge::ID))
        {
            NctiTopoEdge* pTopoEdge = (NctiTopoEdge*)TopoShapeVec[i];
            std::vector<NctiTopoEdgeCurve*> EdgeCurveVec = pTopoEdge->Get_m_EdgeCurveVec();
            if (EdgeCurveVec.size() == 2)
            {
                NctiTopoFace* pLeftFace = nullptr;
                NctiTopoFace* pRightFace = nullptr;
                {
                    pLeftFace = EdgeCurveVec[0]->Get_m_TopoFace();
                    pRightFace = EdgeCurveVec[1]->Get_m_TopoFace();
                }
                Ncti_Long idF;
                pDocCus->get_persistent_tag(pModelBody, pLeftFace->GetLinkVoid(), idF);
                Ncti_Long idE;
                pDocCus->get_persistent_tag(pModelBody, pRightFace->GetLinkVoid(), idE);

                faceFIDs.push_back(idF);
                faceEIDs.push_back(idE);

            }
        }
    }

    Ncti_Integer faceCount = faceFIDs.size();
    std::vector<std::string> uniqueLine;
    std::vector<AiEdgeAttr> edgeAttrs;
    for (size_t i = 0; i < faceCount; i++)
    {
        Ncti_Integer startIndex = faceFIDs[i];
        Ncti_Integer endIndex = faceEIDs[i];

        std::string lineName = startIndex > endIndex
            ? NctiString::int_to_string(startIndex) + NctiString::int_to_string(endIndex)
            : NctiString::int_to_string(endIndex) + NctiString::int_to_string(startIndex);

        if (std::find(uniqueLine.begin(), uniqueLine.end(), lineName) != uniqueLine.end())
        {
            continue;
        }
        uniqueLine.push_back(lineName);
        faceTopoIDs.push_back({ startIndex, endIndex });
    }

}

void NctiAiRecognitionListDlg::onRecogItemClicked(QTreeWidgetItem* item, int column)
{
    if (isHandlingChanged)
        return;

    isHandlingChanged = true;
    Qt::CheckState state = item->checkState(column);
    if (state == Qt::Checked || state == Qt::Unchecked)
    {
        int count = item->childCount();
        if (count > 0)
        {
            UpdateCheckState(item, state);
        }
        else
        {
            UpdateParentItemState(item);
        }
    }

    HighLightCells();
    isHandlingChanged = false;
}
