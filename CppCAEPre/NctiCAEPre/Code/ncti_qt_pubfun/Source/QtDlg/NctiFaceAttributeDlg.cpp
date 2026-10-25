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

#include "NctiFaceAttributeDlg.h"

#include "NctiDocument.h"
#include "NctiArgumentObject.h"
#include "NctiDocElementPubFun.h"
#include "NctiDisplayAiAttriTopoMesh.h"
#include "NctiDisplayObject.h"
#include "NctiString.h"

using namespace NCTI;

NctiFaceAttributeDlg::NctiFaceAttributeDlg(NctiDocument* i_pDocument, QWidget* i_parent) 
    : QWidget(i_parent)
    , m_ui(new Ui::NctiFaceAttribute())
    , m_pDocument(i_pDocument)
{
    m_ui->setupUi(this);
    this->setWindowFlags(Qt::Dialog);
    this->setWindowModality(Qt::NonModal);
    setWindowTitle("Face Attribute");

    m_ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
    m_ui->tableWidget->resizeColumnsToContents();
    m_ui->tableWidget->setColumnWidth(0, 100);

    connect(m_ui->pushButton_refresh, SIGNAL(clicked()), this, SLOT(onOk()));
}

NctiFaceAttributeDlg::~NctiFaceAttributeDlg()
{
    NCTI_DELETE m_ui;
}

void NCTI::NctiFaceAttributeDlg::onOk()
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
    const std::vector<AiFaceAttr>& faceAttrVec = topoMesh->GetFaceAttrs();

    AiFaceAttr faceAttr = faceAttrVec[cellIdVec[0]];

    std::vector<std::string> propertyNames{
        "FaceIndex",
        "IsPlane",
        "IsCylinder",
        "IsCone",
        "IsSphere",
        "IsTorus",
        "Mass",
        "Rational",
        "CenterMass"
    };

    std::vector<std::string> propertyValues{
        NctiString::int_to_string(cellIdVec[0]),
        NctiString::double_to_string(faceAttr.m_IsPlane),
        NctiString::double_to_string(faceAttr.m_IsCylinder),
        NctiString::double_to_string(faceAttr.m_IsCone),
        NctiString::double_to_string(faceAttr.m_IsSphere),
        NctiString::double_to_string(faceAttr.m_IsTorus),
        NctiString::double_to_string(faceAttr.m_Mass),
        NctiString::double_to_string(faceAttr.m_Rational),
        "[" +
        NctiString::double_to_string(faceAttr.m_CenterMass.x()) + "," +
        NctiString::double_to_string(faceAttr.m_CenterMass.y()) + "," +
        NctiString::double_to_string(faceAttr.m_CenterMass.z()) + "]",        
    };

    m_ui->tableWidget->setRowCount(propertyNames.size());
    for (size_t i = 0; i < propertyNames.size(); i++)
    {
        m_ui->tableWidget->setItem(i, 0, new QTableWidgetItem(propertyNames[i].c_str()));
        m_ui->tableWidget->setItem(i, 1, new QTableWidgetItem(propertyValues[i].c_str()));
    }
}
