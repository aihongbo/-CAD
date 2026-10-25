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

#include "NctiAiFeatureExtractDlg.h"

#include <QCloseEvent>

#include "ui_NctiAiFeatureExtract.h"
#include "NctiDocument.h"
#include "NctiBaseModel.h"
#include "NctiAiModelSystemObject.h"
#include "NctiDocElementPubFun.h"
#include "NctiDisplayDocCustomContainer.h"
#include "NctiDisplayModelBody.h"
#include "NctiDisplayObjectList.h"
#include "NctiDocViewManager.h"
#include "NctiString.h"
#include "NctiPythonTool.h"

using namespace NCTI;
using namespace Ui;
NctiAiFeatureExtractDlg::NctiAiFeatureExtractDlg(NctiDocument* pDocument, Ncti_Integer i_Type, QWidget *parent) 
    : QWidget(parent)
    , m_pDocument(pDocument)
    , m_Type(i_Type)
    , ui(new Ui::NctiAiFeatureExtract)
    , m_LabelName(nullptr)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::Dialog);
    this->setWindowModality(Qt::NonModal);
    switch (m_Type)
    {
    case 1: {
        ui->title->setObjectName(QStringLiteral("Extract RCorner Feature"));
        setWindowTitle("Extract RCorner Feature");
        m_LabelName = "round_corner_feature";
        break;
    }
    case 2: {
        ui->title->setObjectName(QStringLiteral("Extract Hole Feature"));
        setWindowTitle("Extract Hole Feature");
        m_LabelName = "hole_feature";
        break;
    }
    case 3: {
        ui->title->setObjectName(QStringLiteral("Extract Logo Feature"));
        setWindowTitle("Extract Logo Feature");
        m_LabelName = "logo_feature";
        break;
    }
    default:
        break;
    }
    InitDlg();
    

}

NctiAiFeatureExtractDlg::~NctiAiFeatureExtractDlg()
{
    delete ui;
}

void NctiAiFeatureExtractDlg::closeEvent(QCloseEvent* event)
{
    //todo:临时方法，后续替换
    NctiBaseModel* pBaseModel = m_pDocument->GetBaseModel();
    NctiDocViewManager* pDocView = NctiDocViewManager::GetDocViewManager(pBaseModel);
    NctiDisplayObjectList ObjListResult;
    for (const auto& item : m_topoMeshes)
    {
        ObjListResult.AddData(item);

        NctiDisplayDocCustomContainer* pDocCus = (NctiDisplayDocCustomContainer*)item->GetDocContainer();
        pDocView->RemoveDisplayObjects(pDocCus, &ObjListResult);
    };

    event->accept();
}

void NCTI::NctiAiFeatureExtractDlg::InitDlg()
{
    NctiBaseModel* pBaseModel = m_pDocument->GetBaseModel();
    NctiDisplayDocCustomContainer* pContainer = NctiDocElementPubFun::GetCurrenDocCustom(pBaseModel);
    QStringList horizontalHeaderLabels;
    QStringList verticalHeaderLabels;
    if (!pContainer)
        return;
    if (pBaseModel)
    {
        NctiAiModelSystemObject* aiObject = NctiDocElementPubFun::GetAiModelSystemObject(pBaseModel);
        std::map<std::string, std::vector<AiModelData>> AiModelDataMap = aiObject->GetLabelMap();
        int row = 0;

        for (const auto& v : AiModelDataMap) {
           
            auto Map = v.second;
            if (NctiString::same(v.first, m_LabelName) == false)
            {
                continue;
            }
            for (const auto& var : Map)
            {
                if(row >= ui->tableWidget->rowCount())
                    ui->tableWidget->insertRow(row);

                if (var.type == 1)
                {
                    verticalHeaderLabels << v.first.c_str();
                    std::vector<Ncti_Long> cellIDs;
                    NctiDocElementPubFun::FindFaceByNearestPoint(m_pDocument, var.ObjName.c_str(), var.pts, cellIDs);
                    NctiDisplayAiAttriTopoMesh* pAiTopoMesh = FindAiTopoMeshObject(var.ObjName.c_str());
                    if (!pAiTopoMesh)
                    {
                        pAiTopoMesh = CreateAiTopoMeshObject(var.ObjName.c_str());
                        m_topoMeshes.push_back(pAiTopoMesh);
                    }
                    std::vector<AiFaceAttr> AiFaceAttrVec = pAiTopoMesh->GetFaceAttrs();
                    
                    AiFaceAttr faceAttr = AiFaceAttrVec[cellIDs[0]];
                    ui->tableWidget->setItem(row, 0, new QTableWidgetItem(QString::number(faceAttr.m_Mass, 'g', 16)));
                    ui->tableWidget->setItem(row, 1, new QTableWidgetItem(QString::number(faceAttr.m_Rational, 'g', 16)));
                    double x = faceAttr.m_CenterMass.x();
                    double y = faceAttr.m_CenterMass.y();
                    double z = faceAttr.m_CenterMass.z();
                    ui->tableWidget->setItem(row, 2, new QTableWidgetItem(QString("%1, %2, %3").arg((x, 'g', 16)).arg((y, 'g', 16)).arg((z, 'g', 16))));
                    ui->tableWidget->setItem(row, 3, new QTableWidgetItem(QString::number((int)faceAttr.m_IsPlane)));
                    ui->tableWidget->setItem(row, 4, new QTableWidgetItem(QString::number((int)faceAttr.m_IsCylinder)));
                    ui->tableWidget->setItem(row, 5, new QTableWidgetItem(QString::number((int)faceAttr.m_IsCone)));
                    ui->tableWidget->setItem(row, 6, new QTableWidgetItem(QString::number((int)faceAttr.m_IsSphere)));
                    ui->tableWidget->setItem(row, 7, new QTableWidgetItem(QString::number((int)faceAttr.m_IsTorus)));
                    row++;
                }
            }
        }
    }

    horizontalHeaderLabels << "Mass" << "Rational" << "CenterMass" << "IsPlane" << "IsCylinder" << "IsCone" << "IsSphere" << "IsTorus";
    ui->tableWidget->setHorizontalHeaderLabels(horizontalHeaderLabels);
    ui->tableWidget->setVerticalHeaderLabels(verticalHeaderLabels);

    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

NctiDisplayAiAttriTopoMesh* NCTI::NctiAiFeatureExtractDlg::FindAiTopoMeshObject(const char* c_Name)
{
    NctiDisplayObjectList ObjList;
    NctiBaseModel* pBaseModel = m_pDocument->GetBaseModel();
    NctiDisplayDocCustomContainer* pContainer = NctiDocElementPubFun::GetCurrenDocCustom(pBaseModel);
    if (pContainer)
    {

		pContainer->GetAllDisplayObjectsByType(&ObjList);
		ObjList.Init();
        NctiDisplayObject* pObj = nullptr;
        NctiDisplayObjectList ObjListResult;
        while ((pObj = ObjList.Next()) != nullptr)
        {
            if (pObj->IsTypeName(NctiDisplayAiAttriTopoMesh::ID))
            {
                NctiDisplayAiAttriTopoMesh* pAiAttr = (NctiDisplayAiAttriTopoMesh*)pObj;
                NctiDisplayModelBody* pModelObj = pAiAttr->GetModelBody();
                if (NctiString::same(pModelObj->GetObjName(), c_Name))
                {
                    return (NctiDisplayAiAttriTopoMesh*)pObj;
                }
            }
        }
    }
    return nullptr;
}

NctiDisplayAiAttriTopoMesh* NCTI::NctiAiFeatureExtractDlg::CreateAiTopoMeshObject(const char* c_ObjName)
{
    char chpy[2048];
    // NctiPyCB.RunSimpleString("sys.path.insert(0, \"D:/NctiDebug/Code/NctiCAEPreAPP/Windows/RelWithDebInfo/AAGNet_package_AI4CAD\")");
    NctiString::LocaleSprintf(chpy, "ai = NCTI.AiModel(doc, \"%s\")", c_ObjName);
    NctiPyCB.RunSimpleString(chpy);
	NctiString::LocaleSprintf(chpy, "doc.RunCommand(\"cmd_ncti_create_ai_attr_topo_mesh\", \"%s\", ai)", c_ObjName);
	NctiPyCB.RunSimpleString(chpy);
    return FindAiTopoMeshObject(c_ObjName);
}
