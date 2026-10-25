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

#include "ObjectTreeManager.h"
#include "NctiDocument.h"
#include "NctiBaseModel.h"
#include "NctiBaseView.h"
#include "NctiDocViewManager.h"
#include "NctiDocElementPubFun.h"
#include "NctiSelectionManager.h"
#include "NctiDisplayDocElement.h"
#include "NctiDisplayBodyGroup.h"
#include "NctiDisplayDocPart.h"
#include "NctiDisplayDocSketch.h"
#include "NctiDisplayDocAssembly.h"
#include "NctiDisplayDocCustomContainer.h"
#include "NctiCommandManager.h"
#include "NctiSelKeyDo.h"
#include "NctiCallbackPopupMenu.h"
#include "NctiDisplayObjectList.h"
#include "NctiUtility.h"

#include <QDockWidget>
#include <QDebug>

#include "NctiQTPubFun.h"

#include "NctiObjectProperty.h"
#include "DockTitleBar.h"

#include "UserInteractionManager.h"
#include "NctiTreeModel.h"
#include "NctiRenderObject.h"
#include "NctiRenderGeometryItem.h"

#include "NctiDisplayDCM3Object.h"
#include "NctiDocTreePubFun.h"

#include "NctiDisplayDCM3Geometry.h"
#include "NctiDisplayDCM3Dimension.h"
#include "NctiDCM3Set.h"

namespace NCTI {

/**
 * @brief 将树数据转换为树模型数据
 * @param db 树数据
 * @param type 树视图类型
 * @return 转换后的树模型数据
 */
static NctiTreeModelData ConvertToTreeModel(const NctiTreeData& db, const NctiTreeViewType& type)
{
    NctiTreeModelData treeData;
    treeData.text     = QString::fromUtf8(db.name.c_str());
    treeData.objName  = QString::fromUtf8(db.name.c_str());
    treeData.typeName = QString::fromUtf8(db.type.c_str());
    treeData.pObject  = db.pObject;
    if (db.pObject != nullptr && type != NctiTreeViewType::Scene) {
        treeData.text = NctiQTPubFun::GetObjectName((NctiDisplayObject*)db.pObject, 1);
    }
    for (const auto& child : db.vChild) {
        treeData.vChild.push_back(ConvertToTreeModel(child, type));
    }
    return treeData;
}

static bool GetTreeModel(const NctiTreeData& db, const NctiTreeViewType& type, NctiTreeModelData& o_treeData)
{

    o_treeData.text = QString::fromUtf8(db.name.c_str());
    o_treeData.objName = QString::fromUtf8(db.name.c_str());
    o_treeData.typeName = QString::fromUtf8(db.type.c_str());
    o_treeData.pObject = db.pObject;
    if (db.pObject != nullptr && type != NctiTreeViewType::Scene) {
        QString str = NctiQTPubFun::GetDisplayStr((NctiDisplayObject*)db.pObject, 1);
        if (str.isEmpty())
            return false;
        o_treeData.text = str;
    }
    for (const auto& child : db.vChild) {
        NctiTreeModelData childTreeData;
        if(GetTreeModel(child, type, childTreeData))
           o_treeData.vChild.push_back(childTreeData);
    }
    return true;
}

static std::vector<NctiTreeData> GetAllDCM3Nodes(const NctiTreeData& i_treeData)
{
    std::vector<NctiTreeData> treeNodes;
    if (i_treeData.pObject != nullptr)
    {
        NctiDisplayObject* pObj = (NctiDisplayObject*)i_treeData.pObject;
        if (pObj->IsTypeName(NctiDisplayDCM3Object::ID))
        {
            treeNodes.push_back(i_treeData);
        }
        else
        {
            for (const NctiTreeData& child : i_treeData.vChild)
            {
                std::vector<NctiTreeData> childNodes = GetAllDCM3Nodes(child);
                treeNodes.insert(treeNodes.end(), childNodes.begin(), childNodes.end());
            }
        }
    }
    else
    {
        for (const NctiTreeData& child : i_treeData.vChild)
        {
            std::vector<NctiTreeData> childNodes = GetAllDCM3Nodes(child);
            treeNodes.insert(treeNodes.end(), childNodes.begin(), childNodes.end());
        }
    }
}

static void RemoveAllDCM3Nodes(NctiTreeData& io_treeData, std::vector<NctiTreeData>& o_removedNodes)
{
    if (io_treeData.pObject != nullptr)
    {
        NctiDisplayObject* pObj = (NctiDisplayObject*)io_treeData.pObject;
        if (pObj->IsTypeName(NctiDisplayDCM3Object::ID))
        {
            o_removedNodes.push_back(io_treeData);
        }
        else
        {
            std::vector<int> removeIndexs;
            for (int i = 0; i < io_treeData.vChild.size(); ++i)
            {
                std::vector<NctiTreeData> childNodes;
                RemoveAllDCM3Nodes(io_treeData.vChild[i], childNodes);
                if (!childNodes.empty())
                    removeIndexs.push_back(i);
                o_removedNodes.insert(o_removedNodes.end(), childNodes.begin(), childNodes.end());
            }
            for (int i = removeIndexs.size() - 1; i >= 0; --i)
            {
                io_treeData.vChild.erase(io_treeData.vChild.cbegin() + removeIndexs[i]);
            }
        }
    }
    else
    {
        std::vector<int> removeIndexs;
        for (int i = 0; i < io_treeData.vChild.size(); ++i)
        {
            std::vector<NctiTreeData> childNodes;
            RemoveAllDCM3Nodes(io_treeData.vChild[i], childNodes);
            if (!childNodes.empty())
                removeIndexs.push_back(i);
            o_removedNodes.insert(o_removedNodes.end(), childNodes.begin(), childNodes.end());
        }
        for (int i = removeIndexs.size() - 1; i >= 0; --i)
        {
            io_treeData.vChild.erase(io_treeData.vChild.cbegin() + removeIndexs[i]);
        }
    }
}

static bool ConvertToAssemblyTree(const NctiTreeData& i_treeData, NctiTreeData& o_assTreeData)
{
    o_assTreeData = i_treeData;
    if (i_treeData.pObject != nullptr)
    {
        NctiDisplayObject* pObj = (NctiDisplayObject*)i_treeData.pObject;
        if (pObj->IsTypeName(NctiDisplayDCM3Object::ID))
        {
            return false;
        }
    }
    std::vector<NctiTreeData> dcm3Nodes;
    RemoveAllDCM3Nodes(o_assTreeData, dcm3Nodes);
    if (!dcm3Nodes.empty())
    {
        NctiTreeData dcm3RootNode;
        dcm3RootNode.name = "约束";
        dcm3RootNode.type = "grp_ncti_dcm3_root";
        dcm3RootNode.vChild.insert(dcm3RootNode.vChild.end(), dcm3Nodes.begin(), dcm3Nodes.end());
        o_assTreeData.vChild.insert(o_assTreeData.vChild.begin(), dcm3RootNode);
    }
    return true;
}
ObjectTreeManager::ObjectTreeManager(MainWindow* mainWindow)
    : MainWindowModule(mainWindow)
{
}

void ObjectTreeManager::initialize()
{
    connect(m_mainWindow->Signals(), &MainWindowSignals::objectTree, this, &ObjectTreeManager::showObjectTree);
}

void ObjectTreeManager::UpdateTree()
{
    if (m_TreeIsModify == false) {
        return;
    }

    if (m_objectTree) {
        m_objectTree->SetModelData(getAssembleData(), NctiTreeViewType::Assemble);
		m_objectTree->SetModelData(getCurrentObjectData(), NctiTreeViewType::Object);
		m_mainWindow->setStatusText();
#ifdef NCTI_SHOW_SCENE_VIEW
        m_objectTree->SetModelData(getSceneData(), NctiTreeViewType::Scene);
#endif // NCTI_SHOW_SCENE_VIEW
    }
    m_TreeIsModify = false;
}

void ObjectTreeManager::initObjectTree()
{
    if (nullptr != m_objectTree) { return; }

    m_objectTree = new NctiObjectTree(m_mainWindow);
    m_objectTree->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
    m_objectTreeDockWidget = new QDockWidget(QStringLiteral("树"), m_mainWindow);
    m_objectTreeDockWidget->setWidget(m_objectTree);
    m_objectTreeDockWidget->setAllowedAreas(Qt::LeftDockWidgetArea);
    m_objectTreeDockWidget->setFeatures(QDockWidget::NoDockWidgetFeatures); // 禁用所有特性

    connect(m_objectTree, &NctiObjectTree::sigTreeItemClicked, this, &ObjectTreeManager::onTreeItemClicked);
    connect(m_objectTree, &NctiObjectTree::sigContextMenuRequested, this, &ObjectTreeManager::onContextMenuRequested);
    connect(m_objectTree, &NctiObjectTree::sigTreeItemSelected, this, &ObjectTreeManager::onTreeItemSelected);
    connect(m_objectTree, &NctiObjectTree::sigSidePanelVisible, this, &ObjectTreeManager::onSidePanelVisible);

    m_objectTreeTitleBar = new DockTitleBar(m_objectTreeDockWidget, false);
    m_objectTreeTitleBar->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    m_objectTreeTitleBar->setTitle(QStringLiteral("装配树"));

    m_objectTreeDockWidget->setTitleBarWidget(m_objectTreeTitleBar);
    m_objectTreeDockWidget->setMinimumWidth(0);
    m_objectTreeDockWidget->hide();
}

void ObjectTreeManager::selectTreeItems(const QStringList& objNames)
{
    if (m_objectTree) {
        int treeIndex = 1; //对象树的索引为1
        m_objectTree->SelectItems(treeIndex, objNames, false);
    }
}

void ObjectTreeManager::SetUIWait(Ncti_Boolean i_boo)
{
    m_bUIWait = i_boo;
    if (i_boo) {
        m_TreeIsModify = false;
    }
}

void ObjectTreeManager::SetTreeModified()
{
    m_TreeIsModify = true;
    UpdateTree();
}

void ObjectTreeManager::SetTreeIsModify(Ncti_Boolean i_boo)
{
    if (!m_bUIWait && i_boo == true) {
        m_TreeIsModify = i_boo;
    }
}

void ObjectTreeManager::onSidePanelVisible(int index, bool visible)
{
    if (visible) {
        if (m_sidePanelVisible && m_objectTreeDockWidth != m_objectTreeDockWidget->width()) {
            m_objectTreeDockWidth = m_objectTreeDockWidget->width();
        }
        m_sidePanelVisible = true;
        m_objectTreeTitleBar->setTitle(getObjectTreeTitle(index));

        m_mainWindow->resizeDocks({ m_objectTreeDockWidget }, { m_objectTreeDockWidth }, Qt::Horizontal);
        m_objectTreeDockWidget->setMaximumWidth(QWIDGETSIZE_MAX);
    }
    else {
        m_sidePanelVisible = false;
        m_objectTreeDockWidth = m_objectTreeDockWidget->width();
        m_objectTreeTitleBar->setTitle(QStringLiteral(""));
        m_mainWindow->resizeDocks({ m_objectTreeDockWidget }, { 40 }, Qt::Horizontal);
        QTimer::singleShot(0, this, [this]() { m_objectTreeDockWidget->setMaximumWidth(40); });
    }
}

/**
 * @brief 对象树处理
 */
void ObjectTreeManager::onObjectTree()
{
    initObjectTree();

    if (m_objectTreeDockWidget) {
        m_mainWindow->addDockWidget(Qt::LeftDockWidgetArea, m_objectTreeDockWidget);
        m_objectTreeDockWidget->show();
        m_mainWindow->resizeDocks({ m_objectTreeDockWidget }, { 300 }, Qt::Horizontal);
        m_objectTreeDockWidth = m_objectTreeDockWidget->width();
    }
}

/**
 * @brief 树项目选择处理
 * @param vObj 选择的对象向量
 */
void ObjectTreeManager::onTreeItemSelected(const std::vector<void*>& vObj)
{
    NctiTreeViewType viewType = m_objectTree->currentTreeViewType();

    NctiDocument* pDoc = m_mainWindow->getCurrentViewDocment();
    if (!pDoc) {
        return;
    }

    NctiBaseModel* pBaseModel = pDoc->GetBaseModel();
    if (!pBaseModel) {
        return;
    }

    NctiSelectionManager* pSelMan = NctiSelectionManager::GetSelectionManager(pBaseModel);
    if (!pSelMan) {
        return;
    }

    if (vObj.empty()) {
        pSelMan->ResetSelection(false);
        pBaseModel->GetActiveBaseView()->Update();
        m_mainWindow->getUserInteractionMgr()->getPropertyView()->SetModelObject(nullptr, viewType);
        return;
    }

    m_mainWindow->getUserInteractionMgr()->getPropertyView()->SetModelObject(vObj[0], viewType);

    if (viewType == NctiTreeViewType::Scene) {
        return;
    }

    //std::vector<NctiDisplayObject*> vDisplayObject;
    std::unordered_map<NctiDisplayObject*, std::vector<Ncti_Long>> vDisObjMap;
    for (auto pObj : vObj) {
        if (pObj == nullptr) {
            continue;
        }

        NctiDisplayObject* pDisObj = static_cast<NctiDisplayObject*>(pObj);
        if (pDisObj->IsTypeName(NctiDisplayDocElement::ID)) {
            continue;
        }

        if (pDisObj->IsTypeName(NctiDisplayBodyGroup::ID)) {
            NctiDisplayObjectList List;
            ((NctiDisplayBodyGroup*)pDisObj)->GetAllMembers(&List);
            List.Init();
            NctiDisplayObject* pObjBody = nullptr;
            while ((pObjBody = List.Next()) != nullptr) {
                if(vDisObjMap.find(pObjBody) == vDisObjMap.end()){
                    vDisObjMap[pObjBody] = {};
                }
            }
        }
        else if (pDisObj->IsTypeName(NctiDisplayDCM3Geometry::ID))
        {
            NctiDisplayDCM3Geometry* pGeom = (NctiDisplayDCM3Geometry*)pDisObj;
            if (pGeom->GetModelBody())
            {
                vDisObjMap[(NctiDisplayObject * )pGeom->GetModelBody()] = {};
            }
        }
        else if (pDisObj->IsTypeName(NctiDisplayDCM3Dimension::ID))
        {
            NctiDisplayDCM3Dimension* pDim= (NctiDisplayDCM3Dimension*)pDisObj;
            if (pDim->GetConsGeometries().size() == 2)
            {
                std::vector< NctiDisplayDCM3Geometry*> pGeomVec = pDim->GetConsGeometries();
                for (auto* pGeom : pGeomVec)
                {
                    if (pGeom && pGeom->get_owner())
                    {
                        if (pGeom->get_owner()->GetModelBody())
                        {
                            long cellID;
                            if (pGeom->get_owner()->get_cell(pGeom, cellID))
                                vDisObjMap[(NctiDisplayObject*)pGeom->get_owner()->GetModelBody()].push_back(cellID);
                            else
                                vDisObjMap[(NctiDisplayObject*)pGeom->get_owner()->GetModelBody()] = {};
                        }
                        
                    }
                }
            }
        }
        else {
            if (vDisObjMap.find(pDisObj) == vDisObjMap.end()) {
                vDisObjMap[pDisObj] = {};
            }
        }
    }

    if (!vDisObjMap.empty()) {
        NctiDocElementPubFun::SetSelectionManager(vDisObjMap, pBaseModel->GetActiveBaseView(), false, true);
        pBaseModel->GetActiveBaseView()->Update();
    }
}

void ObjectTreeManager::onTreeItemClicked(const QString& objName, void* pObj)
{
    NctiTreeViewType viewType = m_objectTree->currentTreeViewType();

    NctiDocument* pDoc = m_mainWindow->getCurrentViewDocment();
    if (!pDoc || !pObj) {
        m_mainWindow->getUserInteractionMgr()->getPropertyView()->SetModelObject(nullptr, viewType);
        return;
    }

    m_mainWindow->getUserInteractionMgr()->getPropertyView()->SetModelObject(pObj, viewType);
        
    if (viewType == NctiTreeViewType::Assemble || viewType == NctiTreeViewType::Object) {
        if (viewType == NctiTreeViewType::Assemble) {
            //qDebug() << "onAssembleTreeItemClicked:" << objName;
        }
        else if (viewType == NctiTreeViewType::Object) {
            //qDebug() << "onObjectTreeItemClicked:" << objName;
        }

        NctiDisplayObject* pDisObj = (NctiDisplayObject*)pObj;
        if (!pDisObj) {
            return;
        }

        NctiBaseModel* pBaseModel = pDoc->GetBaseModel();
        if (!pBaseModel) {
            return;
        }

        NctiDocViewManager* pDocView = NctiDocViewManager::GetDocViewManager(pBaseModel);

        if (pDisObj->IsTypeName(NctiDisplayDocPart::ID) || pDisObj->IsTypeName(NctiDisplayDocAssembly::ID)) {
            pDocView->SetActiveDocElement((NctiDisplayDocElement*)pDisObj);
            m_objectTree->SetModelData(getCurrentObjectData(), NctiTreeViewType::Object);
        }
        else if (pDisObj->IsTypeName(NctiDisplayDocSketch::ID)) {
            pDocView->SetActiveDocSketch((NctiDisplayDocSketch*)pDisObj);
        }
        else if (pDisObj->IsTypeName(NctiDisplayDocCustomContainer::ID)) {
            NctiDocViewManager* pDocView = NctiDocViewManager::GetDocViewManager(pBaseModel);
            pDocView->SetActiveDocElement((NctiDisplayDocElement*)(pDisObj->GetDoOwner()));
            m_objectTree->SetModelData(getCurrentObjectData(), NctiTreeViewType::Object);
        }
        else {
            //NctiSelectionManager* pSelMan = NctiSelectionManager::GetSelectionManager(pBaseModel);
            //NctiDisplayObject* pInstanceObj = pBaseModel->GetActiveBaseView()->GetInstanceFromOriginal(pDisObj);
            //if (pInstanceObj) {
            //	pSelMan->ResetSelection(false);
            //	NctiSelKeyDo cSelData(nullptr, pDisObj, pInstanceObj);
            //	pSelMan->SetSelected(&cSelData, NCTI_SELECT_NO_MOUSE, false);
            //	pBaseModel->GetActiveBaseView()->Update();
            //}
        }
    }
    else if (viewType == NctiTreeViewType::Scene) {
#ifdef NCTI_SHOW_SCENE_VIEW
        m_mainWindow->setStatusText("");
        NctiRenderObject* pRenderObj = static_cast<NctiRenderObject*>(pObj);
        if (pRenderObj && pRenderObj->IsTypeName(NctiRenderGeometryItem::ID)) {
            NctiRenderGeometryItem* pGeometryItem = (NctiRenderGeometryItem*)pRenderObj;
            NctiDisplayObject* pDisObj = NctiUtility::GetSegmentDisplayObject(pGeometryItem);

            NctiBaseModel* pBaseModel = pDoc->GetBaseModel();
            NctiSelectionManager* pSelMan = NctiSelectionManager::GetSelectionManager(pBaseModel);
            NctiDisplayObject* pInstanceObj = pDisObj ? pDisObj->GetActiveInstance() : nullptr;

            pSelMan->ResetSelection();
            NctiSelKeyDo cSelData(pGeometryItem, pDisObj, pInstanceObj);
            pSelMan->SetSelected(&cSelData, NCTI_SELECT_NO_MOUSE);
            pBaseModel->GetActiveBaseView()->Update();

        }
  #endif // NCTI_SHOW_SCENE_VIEW
    }
    m_mainWindow->setStatusText();
}

void ObjectTreeManager::onContextMenuRequested(const QString& objName, void* pObj)
{
    NctiTreeViewType viewType = m_objectTree->currentTreeViewType();
    if (viewType != NctiTreeViewType::Object 
        && viewType != NctiTreeViewType::Assemble) {
        return;
    }

    qDebug() << "onContextMenuRequested:" << objName;
    NctiDisplayObject* pDisObj = (NctiDisplayObject*)pObj;
    if (!pDisObj) {
        return;
    }

    NctiDocument* pDocument   = m_mainWindow->getCurrentViewDocment();
    NctiBaseModel* pBaseModel = pDocument->GetBaseModel();

    if (pDisObj->IsTypeName(NctiDisplayDocElement::ID)) {
        NctiDocViewManager* pDocView = NctiDocViewManager::GetDocViewManager(pBaseModel);
        NctiCommandManager* pComMan  = NctiCommandManager::GetCommandManager(pBaseModel);
        if (pComMan->GetActiveCommand() == nullptr) {
            //pDocView->SetActiveDocElement((NctiDisplayDocElement*)pDisObj);
        }
    }
    else {
        NctiSelectionManager* pSelMan = NctiSelectionManager::GetSelectionManager(pBaseModel);
        auto pInstanceObj = pDisObj->GetActiveInstance();
        if (pInstanceObj) {
            NctiSelKeyDo cSelData(nullptr, pDisObj, pInstanceObj);
            pSelMan->add_selected(&cSelData);
            m_mainWindow->getPopupMenuCallback()->SetDisplayObj(pInstanceObj);
            pInstanceObj->Callback(pBaseModel->GetActiveBaseView(), NCTI_DO_CALLBACK_SHOW_CONTEXT_MENU, nullptr);
            pBaseModel->GetActiveBaseView()->Update();
        }
    }
}

std::vector<NctiTreeModelData> ObjectTreeManager::getAssembleData()
{
    std::vector<NctiTreeModelData> vTreeModelData;
    NctiDocument* pDoc = m_mainWindow->getCurrentViewDocment();
    if (!pDoc) {
        return vTreeModelData;
    }
    NctiTreeData treeData;
    NctiDocTreePubFun::GetObjectTree(pDoc, treeData, false);

    NctiTreeData assTreeData;
    ConvertToAssemblyTree(treeData, assTreeData);

    NctiTreeModelData treeModelData;
    if(GetTreeModel(assTreeData, NctiTreeViewType::Assemble, treeModelData))
        vTreeModelData.push_back(treeModelData);
    return vTreeModelData;
}

std::vector<NctiTreeModelData> ObjectTreeManager::getCurrentObjectData()
{
    std::vector<NctiTreeModelData> vTreeModelData;
    NctiDocument* pDoc = m_mainWindow->getCurrentViewDocment();
    if (!pDoc) {
        return vTreeModelData;
    }
    NctiDocViewManager* pDocView      = NctiDocViewManager::GetDocViewManager(pDoc->GetBaseModel());
    NctiDisplayDocElement* pActiveDoc = pDocView->GetActiveDocElement();

    if (pActiveDoc->IsTypeName(NctiDisplayDocAssembly::ID) 
        || pActiveDoc->IsTypeName(NctiDisplayDocPart::ID)
        || pActiveDoc->IsTypeName(NctiDisplayDocSketch::ID)) {
        NctiTreeData treeData;
        if (pActiveDoc->IsTypeName(NctiDisplayDocSketch::ID)) {
            NctiDisplayDocSketch* pSkecth = (NctiDisplayDocSketch*)pActiveDoc;
            NctiDocTreePubFun::GetOnlyObjectTree(pSkecth->GetDoOwner(), treeData);
        }
        else {
            NctiDocTreePubFun::GetOnlyObjectTree(pActiveDoc, treeData);
        }
        treeData                        = NctiDocTreePubFun::DisOnlyObjectTree(treeData);
        NctiTreeModelData treeModelData = ConvertToTreeModel(treeData, NctiTreeViewType::Object);
        vTreeModelData.push_back(treeModelData);
    }
    return vTreeModelData;
}

std::vector<NctiTreeModelData> ObjectTreeManager::getSceneData()
{
    std::vector<NctiTreeModelData> vTreeModelData;
    NctiDocument* pDoc = m_mainWindow->getCurrentViewDocment();
    if (!pDoc) {
        return vTreeModelData;
    }

    NctiTreeData treeData;
    NctiDocTreePubFun::GetSceneTree(pDoc, treeData);

    NctiTreeModelData treeModelData = ConvertToTreeModel(treeData, NctiTreeViewType::Scene);
    vTreeModelData.push_back(treeModelData);
    return vTreeModelData;
}

QString ObjectTreeManager::getObjectTreeTitle(int index)
{
    if (!m_objectTree) {
        return "";
    }

    NctiTreeViewType viewType = NctiTreeViewType::Normal;
    if (index == 0) {
        viewType = NctiTreeViewType::Assemble;
    }
    else if (index == 1) {
        viewType = NctiTreeViewType::Object;
    }
    else if (index == 2) {
        viewType = NctiTreeViewType::Scene;
    }
    else {
        viewType = m_objectTree->currentTreeViewType();
    }

    switch (viewType) {
        case NCTI::NctiTreeViewType::Assemble: return QStringLiteral("装配树");
        case NCTI::NctiTreeViewType::Object: return QStringLiteral("对象树");
        case NCTI::NctiTreeViewType::Scene: return QStringLiteral("场景树");
        default: break;
    }

    return QString{};
}

void ObjectTreeManager::showObjectTree()
{
    onObjectTree();
    m_objectTree->showCurrentObjectTreeView();
}

} // namespace NCTI