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

#include "NctiEdgeAttributeDlg.h"

#include "NctiDocument.h"
#include "NctiArgumentObject.h"
#include "NctiDocElementPubFun.h"
#include "NctiDisplayAiAttriTopoMesh.h"
#include "NctiDisplayObject.h"
#include "NctiString.h"
using namespace NCTI;

NctiEdgeAttributeDlg::NctiEdgeAttributeDlg(NctiDocument* i_pDocument, QWidget* i_parent) 
    : QWidget(i_parent)
    , m_ui(new Ui::NctiEdgeAttribute())
    , m_pDocument(i_pDocument)
{
    m_ui->setupUi(this);
    this->setWindowFlags(Qt::Dialog);
    this->setWindowModality(Qt::NonModal);
    setWindowTitle("Edge Attribute");

    m_ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
    m_ui->tableWidget->resizeColumnsToContents();
    m_ui->tableWidget->setColumnWidth(0, 100);

    connect(m_ui->pushButton_refresh, SIGNAL(clicked()), this, SLOT(onOk()));
}

NctiEdgeAttributeDlg::~NctiEdgeAttributeDlg()
{
    NCTI_DELETE m_ui;
}

void NCTI::NctiEdgeAttributeDlg::onOk()
{
    m_ui->tableWidget->clearContents();

    std::vector<NctiTopoCell*> geCellVec;
    std::vector<std::string> objNameVec;
    std::vector<Ncti_Long> cellIdVec;
    NctiDocElementPubFun::GetNameFromSelManager(m_pDocument, objNameVec, cellIdVec, geCellVec);
    if (cellIdVec.size() == 0)
        return;

    NctiBaseModel* pBaseModel = m_pDocument->GetBaseModel();
    NctiDisplayObject* pObj = nullptr;
    NctiDocElementPubFun::GetObjectListByName(pBaseModel, NctiDisplayAiAttriTopoMesh::ID, objNameVec[0].c_str(), pObj);
    NctiDisplayAiAttriTopoMesh* topoMesh = (NctiDisplayAiAttriTopoMesh*)pObj;
    const std::vector<AiEdgeAttr>& edgeAttrVec = topoMesh->GetEdgeAttrs();
    const std::vector<std::pair<Ncti_Integer, Ncti_Integer>>&  topoIds = topoMesh->GetFaceTopoIDs();

    AiEdgeAttr edgeAttr = edgeAttrVec[cellIdVec[0]];
    Ncti_Integer startIndex = topoIds[cellIdVec[0]].first;
    Ncti_Integer endIndex = topoIds[cellIdVec[0]].second;

    std::vector<std::string> propertyNames{
        "EdgeIndex",
        "convexity",
        "Mass",
        "IsCircle",
        "IsClose",
        "IsEllipse",
        "IsNonRationalBSplineEdgeAttribute",
        "IsRationalBSplineEdgeAttribute",
        "IsLine"
    };

    std::vector<std::string> propertyValues{
        "[" +
        NctiString::int_to_string(startIndex) + "," +
        NctiString::int_to_string(endIndex) + "]",
        NctiString::int_to_string(edgeAttr.m_convexity),
        NctiString::double_to_string(edgeAttr.m_Mass),
        NctiString::double_to_string(edgeAttr.m_IsCircle),
        NctiString::double_to_string(edgeAttr.m_IsClose),
        NctiString::double_to_string(edgeAttr.m_IsEllipse),
        NctiString::double_to_string(edgeAttr.m_IsNonRationalBSplineEdgeAttribute),
        NctiString::double_to_string(edgeAttr.m_IsRationalBSplineEdgeAttribute),
        NctiString::double_to_string(edgeAttr.m_IsLine),
    };

    m_ui->tableWidget->setRowCount(propertyNames.size());
    for (size_t i = 0; i < propertyNames.size(); i++)
    {
        m_ui->tableWidget->setItem(i, 0, new QTableWidgetItem(propertyNames[i].c_str()));
        m_ui->tableWidget->setItem(i, 1, new QTableWidgetItem(propertyValues[i].c_str()));
    }
}
