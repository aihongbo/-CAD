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

#include "MeshAddSpcView.h"
#include "ui_MeshAddSpcView.h"

#include <QCheckBox>
#include <QValidator>
#include "NctiMessageBox.h"
#include "SelectModeRoller.h"
#include "NctiQtScriptExecutor.h"

#include "NctiBaseModel.h"
#include "NctiDocument.h"
#include "NctiCommandManager.h"
#include "NctiDocElementPubFun.h"
#include "NctiArgumentObject.h"
#include "NctiDisplayObject.h"
#include "NctiDisplayModelBody.h"
#include "NctiGeometryFunction.h"
#include "NctiPhyParaDef.h"

#include "NctiDocViewManager.h"
#include "NctiDisplayGridMesh.h"
#include "NctiMeshManager.h"

namespace NCTI {

    MeshAddSpcView::MeshAddSpcView(NctiDocument* i_pDocument, NctiQtScriptExecutor* executor, QWidget* parent) 
        : NctiBaseDialog(parent)
        , ui(new Ui::MeshAddSpcView)
        , m_document(i_pDocument)
        , m_executor(executor)
        , m_roller(new SelectModeRoller(i_pDocument, SelectModeRoller::SelectMode::Face, this))
    {
        setup();
    }

    MeshAddSpcView::~MeshAddSpcView()
    {
        delete ui;
    }

    bool MeshAddSpcView::beforeAccpet()
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
        QList<int> sourceCellIDList;
        if (!getSourceName(sourceName, sourceCellIDList)) {
            popupMessage(QStringLiteral("选取对象无效"));
            return false;
        }
		if (m_NodeIdx.empty())
		{
			popupMessage(QStringLiteral("选取对象无效"));
			return false;
        }

        int component;
        if (!getComponent(component)) {
            popupMessage(QStringLiteral("约束选择无效"));
            return false;
        }

        QString comment;
        getComment(comment);
        
        if (m_executor != nullptr) {
            QString script = toScriptString(resultName, sourceName, m_NodeIdx, m_ComponentsVec, m_SizeRangeVec, comment);
            m_executor->excuteCommand(script);
        }
        else {
            NctiBaseModel* pBaseModel = m_document->GetBaseModel();
            NctiCommandManager* pComMan = NctiCommandManager::GetCommandManager(pBaseModel);
            if (!pComMan) {
                return false;
            }

            NctiArgumentObject argumentObject;
            std::vector<std::string> args{
                std::to_string(component),
                sourceName.toUtf8().data(),
                comment.toUtf8().data()
            };
            argumentObject.SetCommandArgumentVec(args);

            std::vector<Ncti_Long> idList;
            for (auto&& value : sourceCellIDList)
                idList.push_back(value);
            argumentObject.SetCellIDVec(idList);
			argumentObject.SetCellIDVec(m_ComponentsVec);
			argumentObject.SetWeigthVec(m_SizeRangeVec);

            EnumNctiResult result = pComMan->RunCommand("cmd_ncti_mesh_add_spc", &argumentObject);
        }
        return true;
    }

    void MeshAddSpcView::setup()
    {
        auto widget = new QWidget(this);
        ui->setupUi(widget);
        setTitle(QStringLiteral("单点约束"));
        setWidget(widget);

        QList<QCheckBox*> checkBoxList = { ui->checkBox_componentX ,ui->checkBox_componentY ,ui->checkBox_componentZ,
            ui->checkBox_componentRotX ,ui->checkBox_componentRotY ,ui->checkBox_componentRotZ };
        QList<QLineEdit*> lineEditList = {
            ui->lineEdit_X, ui->lineEdit_Y, ui->lineEdit_Z, ui->lineEdit_RotX, ui->lineEdit_RotY, ui->lineEdit_RotZ
        };
        for (int i = 0; i < 6; ++i) {
            QCheckBox* checkBox = checkBoxList[i];
            checkBox->setChecked(true);
            checkBox->setProperty("select_mode_checkbox", true);
            QLineEdit* lineEdit = lineEditList[i];
            connect(checkBox, &QCheckBox::stateChanged,
                [lineEdit](int state) {
                    // 根据复选框状态启用/禁用输入框
                    lineEdit->setEnabled(state == Qt::Checked);
                });
        }

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

        connect(ui->cancelBtn, &QPushButton::clicked, this, &MeshAddSpcView::reject);

        const QString regexPattern = "^(-?\\d+)(\\.\\d+)?$";
        for (QLineEdit* lineEdit : lineEditList) {
            #if QT_VERSION_MAJOR >= 6
                lineEdit->setValidator(new QRegularExpressionValidator(QRegularExpression(regexPattern)));
            #else
                lineEdit->setValidator(new QRegExpValidator(QRegExp(regexPattern)));
            #endif
        }
    }

    void MeshAddSpcView::setObjectSelection(const std::vector<NctiDisplayObject*>& objectList, const std::vector<void*>& cellIDList)
    {
        //m_selectObjects = objectList;
        m_selectObjects.clear();
        m_selectCells.clear();
        if (objectList.empty() || cellIDList.empty()) {
            ui->label_count->setText("0");
            ui->pushButton_select->setChecked(false);
            popupMessage(QStringLiteral("对象数量为 0"));
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

    bool MeshAddSpcView::getResultName(QString& name)
    {
        auto text = ui->lineEdit_result->text();
        if (text.isEmpty()) {
            return false;
        }

        name = std::move(text);
        return true;
    }
    bool MeshAddSpcView::getSourceName(QString& name, QList<int>& cellIDList)
    {
        if (m_selectObjects.empty() || m_NodeIdx.empty()) {
            return false;
        }

        name = m_selectObjects[0]->GetObjName();

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
    bool MeshAddSpcView::getComponent(int& component)
    {
        QMap<QCheckBox*, Ncti_Components> checkBoxToComponent =
        {
            {ui->checkBox_componentX,Ncti_Components_U1},
            {ui->checkBox_componentY,Ncti_Components_U2},
            {ui->checkBox_componentZ,Ncti_Components_U3},
            {ui->checkBox_componentRotX,Ncti_Components_ROT1},
            {ui->checkBox_componentRotY,Ncti_Components_ROT2},
            {ui->checkBox_componentRotZ,Ncti_Components_ROT3},
        };

        int c = 0;
        for (auto iter = checkBoxToComponent.begin(); iter != checkBoxToComponent.end(); ++iter)
        {
            if (!iter.key()->isChecked()) {
                continue;
            }
            c |= iter.value();
        }

        if (c == 0)
            return false;
        component = c;
        m_ComponentsVec.clear();
        m_SizeRangeVec.clear();
        if (ui->checkBox_componentX->isChecked())
		{
			m_ComponentsVec.push_back(1);
            m_SizeRangeVec.push_back(ui->lineEdit_X->text().toDouble());
		}
        if (ui->checkBox_componentY->isChecked())
		{
			m_ComponentsVec.push_back(2);
			m_SizeRangeVec.push_back(ui->lineEdit_Y->text().toDouble());
		}
        if (ui->checkBox_componentZ->isChecked())
		{
			m_ComponentsVec.push_back(3);
			m_SizeRangeVec.push_back(ui->lineEdit_Z->text().toDouble());
		}
        if (ui->checkBox_componentRotX->isChecked())
		{
			m_ComponentsVec.push_back(4);
			m_SizeRangeVec.push_back(ui->lineEdit_RotX->text().toDouble());
		}
		if (ui->checkBox_componentRotY->isChecked())
		{
			m_ComponentsVec.push_back(5);
			m_SizeRangeVec.push_back(ui->lineEdit_RotY->text().toDouble());
		}
        if (ui->checkBox_componentRotZ->isChecked())
		{
			m_ComponentsVec.push_back(6);
			m_SizeRangeVec.push_back(ui->lineEdit_RotZ->text().toDouble());
		}
        return true;
    }
    bool MeshAddSpcView::getComment(QString& comment)
    {
        QString c = ui->plainTextEdit_describe->toPlainText();
        if (c.isEmpty()) {
            return false;
        }

        comment = c;
        return true;
    }
    QString MeshAddSpcView::toScriptString(const QString& resultName, const QString& sourceName, const std::vector<Ncti_LongLong>& cellIDList,
        const std::vector<long>& componentVec, const std::vector<double> sizeRangeVec, const QString& comment)
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

        QString componentListString;
        for (auto&& value : componentVec) {
            if (!componentListString.isEmpty()) {
                componentListString += ",";
            }
            componentListString += QString::number(value);
        }
        componentListString.prepend('[');
        componentListString.append(']');

        QString sizeRangeListString;
        for (auto&& value : sizeRangeVec) {
            if (!sizeRangeListString.isEmpty()) {
                sizeRangeListString += ",";
            }
            sizeRangeListString += QString::number(value);
        }
        sizeRangeListString.prepend('[');
        sizeRangeListString.append(']');

        if (comment.isEmpty())
        {
            return QString("doc.RunCommand(\"cmd_ncti_mesh_add_spc\", \"%1\", \"%2\", %3, %4, %5)")
                .arg(resultName).arg(sourceName).arg(numberListString).arg(componentListString).arg(sizeRangeListString);
        }
        else
        {
            return QString("doc.RunCommand(\"cmd_ncti_mesh_add_spc\", \"%1\", \"%2\", %3, %4, %5, \"%6\")")
                .arg(resultName).arg(sourceName).arg(numberListString).arg(componentListString).arg(sizeRangeListString).arg(comment);
        }
    }

    void MeshAddSpcView::popupMessage(const QString& message, const QString& title)
    {
        MESSAGEBOX_INSTANCE->showMessageBox(message, title, false);
        MESSAGEBOX_INSTANCE->hide();
        MESSAGEBOX_INSTANCE->exec();
    }
}
