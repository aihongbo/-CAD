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

#include "MeshAddForceView.h"
#include "ui_MeshAddForceView.h"

#include <QDebug>
#include "NctiMessageBox.h"
#include "NctiQtScriptExecutor.h"
#include "SelectModeRoller.h"

#include "NctiBaseModel.h"
#include "NctiDocument.h"
#include "NctiCommandManager.h"
#include "NctiDocElementPubFun.h"
#include "NctiArgumentObject.h"
#include "NctiDisplayObject.h"
#include "NctiDisplayModelBody.h"

#include "NctiDocViewManager.h"
#include "NctiDisplayGridMesh.h"
#include "NctiMeshManager.h"

namespace NCTI {

    MeshAddForceView::MeshAddForceView(NctiDocument* i_pDocument, NctiQtScriptExecutor* executor, QWidget* parent) 
        : NctiBaseDialog(parent)
        , ui(new Ui::MeshAddForceView)
        , m_document(i_pDocument)
        , m_executor(executor)
        , m_roller(new SelectModeRoller(i_pDocument, SelectModeRoller::SelectMode::Marker, this))
    {
        setup();
    }
    MeshAddForceView::~MeshAddForceView()
    {
        delete ui;
    }

    bool MeshAddForceView::beforeAccpet()
    {
        if (nullptr == m_document) {
            return false;
        }

        QString resultName;
        if (!getResultName(resultName)) {
            popupMessage(QStringLiteral("结果对象名称无效"));
            return false;
        }

        QString sourceName;
        QList<Ncti_LongLong> sourceCellIDList;
        if (!getSourceName(sourceName, sourceCellIDList)) {
            popupMessage(QStringLiteral("选取点对象无效"));
            return false;
        }

        NctiVector direct;
        if (!getDirect(direct)) {
            popupMessage(QStringLiteral("坐标值输入无效"));
            return false;
        }

        Ncti_Double magnitude;
        if (!getMagnitude(magnitude)) {
            popupMessage(QStringLiteral("强度值输入无效"));
            return false;
        }

        QString comment;
        getComment(comment);

        if (nullptr != m_executor) {
            QString script = toScriptString(resultName, sourceName, sourceCellIDList, direct, magnitude, comment);
            m_executor->excuteCommand(script);
        }
        else {
            NctiBaseModel* pBaseModel = m_document->GetBaseModel();
            NctiCommandManager* pComMan = NctiCommandManager::GetCommandManager(pBaseModel);
            if (!pComMan)
                return false;

            std::vector<std::string> args{
                    sourceName.toUtf8().data(),
                    QString::number(magnitude).toUtf8().data(),
                    comment.toUtf8().data()
            };

            NctiArgumentObject argumentObject;
            argumentObject.SetCommandArgumentVec(args);

            std::vector<Ncti_Long> idList;
            for (auto&& value : m_NodeIdx)
                idList.push_back(value);
            argumentObject.SetCellIDVec(idList);

            argumentObject.SetXLen(direct.x());
            argumentObject.SetYLen(direct.y());
            argumentObject.SetZLen(direct.z());
        }
        return true;
    }

    void MeshAddForceView::setup()
    {
        auto widget = new QWidget(this);
        ui->setupUi(widget);
        setTitle(QStringLiteral("集中力"));
        setWidget(widget);

        ui->pushButton_select->setCheckable(true);
        connect(ui->pushButton_select, &QPushButton::clicked, this, [this](bool checked) {
            if (!checked) {
                ui->pushButton_select->setChecked(true);
            }
            std::vector<NctiDisplayObject*> objectVec;
            std::vector<NCTI_MODEL_TAG> selectCells;
            NctiDocElementPubFun::GetDisplayObjectFromSelManager(m_document, objectVec, selectCells);
            setObjectSelection(objectVec, selectCells);

            });

        connect(ui->confrimBtn, &QPushButton::clicked, this, [this] {
            if (!beforeAccpet()) {
                return;
            }
            accept();
            });

        connect(ui->cancelBtn, &QPushButton::clicked, this, &MeshAddForceView::reject);
    }

    void MeshAddForceView::setObjectSelection(const std::vector<NctiDisplayObject*>& objectList, const std::vector<void*>& cellIDList)
    {
        m_selectObjects.clear();
        m_selectCells.clear();
        if (objectList.empty() || cellIDList.empty()) {
            ui->label_count->setText("0");
            ui->pushButton_select->setChecked(false);
            popupMessage(QStringLiteral("点对象数量为 0"));
        }
        else {

            for (auto obj : objectList)
            {
                if (obj->IsTypeName(NctiDisplayGridMesh::ID))
                {
                    m_selectObjects.push_back(obj);
                }
            }
            

            m_selectCells = cellIDList;
            m_NodeIdx.clear();
            if (cellIDList.size() > 0)
            {
                for (int i = 0; i < cellIDList.size(); i++)
                {
                    NctiGridPickSet pick(cellIDList[i]);

                    if (pick.Type() == ELEM_Vertex)
                        m_NodeIdx.push_back(pick.RawData());
                        //m_NodeIdx.push_back(pick.Number());
                }
            }

            ui->label_count->setText(QString::number(m_NodeIdx.size()));
            ui->pushButton_select->setChecked(true);
        }
    }

    bool MeshAddForceView::getSourceName(QString& name, QList<Ncti_LongLong>& cellIDList)
    {
        if (m_selectObjects.empty() || m_NodeIdx.empty()) {
            return false;
        }

        name = m_selectObjects[0]->GetObjName();

        for (int i= 0; i < m_NodeIdx.size(); i++)
        {
            cellIDList.push_back(m_NodeIdx[i]);
        }
        //NctiDisplayModelBody* pModelBody = (NctiDisplayModelBody*)m_selectObjects[0];
        //NctiDisplayDocCustomContainer* pCusDoc = (NctiDisplayDocCustomContainer*)pModelBody->GetDoOwner();
        //for (int i = 0; i < m_selectCells.size(); i++)
        //{
        //    Ncti_Long cellID = -1;
        //    pCusDoc->get_persistent_tag(pModelBody, m_selectCells[i], cellID);
        //    cellIDList.append(cellID);
        //}

        return true;
    }
    bool MeshAddForceView::getResultName(QString& name)
    {
        auto text = ui->lineEdit_result->text();
        if (text.isEmpty()) {
            return false;
        }

        name = std::move(text);
        return true;
    }
    bool MeshAddForceView::getDirect(NctiVector& vector)
    {
        bool ok = false;
        qreal x = ui->lineEdit_x->text().toDouble(&ok);
        if (!ok) {
            return false;
        }

        qreal y = ui->lineEdit_y->text().toDouble(&ok);
        if (!ok) {
            return false;
        }

        qreal z = ui->lineEdit_z->text().toDouble(&ok);
        if (!ok) {
            return false;
        }

        if (x <= 1e-6 && y <= 1e-6 && z <= 1e-6) {
            return false;
        }

        vector.set_x(x);
        vector.set_y(y);
        vector.set_z(z);
        return true;
    }
    bool MeshAddForceView::getMagnitude(Ncti_Double& magnitude)
    {
        bool ok = false;
        Ncti_Double m = ui->lineEdit_strength->text().toDouble(&ok);
        if (!ok) {
            return false;
        }

        magnitude = m;
        return true;
    }
    bool MeshAddForceView::getComment(QString& comment)
    {
        QString c = ui->plainTextEdit_describe->toPlainText();
        if (c.isEmpty()) {
            return false;
        }

        comment = c;
        return true;
    }
    QString MeshAddForceView::toScriptString(const QString& resultName, const QString& sourceName, const QList<Ncti_LongLong>& cellIDList,
        const NctiVector& direct, Ncti_Double magnitude, const QString& comment)
    {
        QString numberListString;
        for (auto&& value : cellIDList) {
            if (!numberListString.isEmpty()) {
                numberListString += ",";
            }
            numberListString += QString::number(value);
        }
        numberListString.prepend('[');
        numberListString.append(']');

        QString vectorString = QString("NCTI.Vector(%1,%2,%3)").arg(direct.x()).arg(direct.y()).arg(direct.z());

        if (comment.isEmpty())
        {
            return QString("doc.RunCommand(\"cmd_ncti_mesh_add_force\", \"%1\", \"%2\", %3, %4, %5)")
                .arg(resultName).arg(sourceName).arg(numberListString).arg(vectorString).arg(magnitude);
        }
        else
        {
            return QString("doc.RunCommand(\"cmd_ncti_mesh_add_force\", \"%1\", \"%2\", %3, %4, %5, \"%6\")")
                .arg(resultName).arg(sourceName).arg(numberListString).arg(vectorString).arg(magnitude).arg(comment);
        }
    }

    void MeshAddForceView::popupMessage(const QString& message, const QString& title)
    {
        MESSAGEBOX_INSTANCE->showMessageBox(message, title, false);
        MESSAGEBOX_INSTANCE->hide();
        MESSAGEBOX_INSTANCE->exec();
    }
}
