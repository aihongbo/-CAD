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

#include "MeshAddMatView.h"
#include "ui_MeshAddMatView.h"

#include <QWidget>
#include "SelectModeRoller.h"
#include "NctiMessageBox.h"
#include "NctiQtScriptExecutor.h"

#include "NctiBaseModel.h"
#include "NctiDocument.h"
#include "NctiCommandManager.h"
#include "NctiDocElementPubFun.h"
#include "NctiArgumentObject.h"
#include "NctiDisplayObject.h"
#include "NctiDisplayModelBody.h"

namespace NCTI {

    MeshAddMatView::MeshAddMatView(NctiDocument* i_pDocument, NctiQtScriptExecutor* executor, QWidget* parent) 
        : NctiBaseDialog(parent)
        , ui(new Ui::MeshAddMatView)
        , m_document(i_pDocument)
        , m_executor(executor)
        , m_roller(new SelectModeRoller(i_pDocument, SelectModeRoller::SelectMode::All, this))
    {
        setup();
    }

    MeshAddMatView::~MeshAddMatView()
    {
        delete ui;
    }

    bool MeshAddMatView::beforeAccpet()
    {
        if (m_document == nullptr) {
            return false;
        }

        QString resultName;
        if (!getResultName(resultName)) {
            popupMessage(QStringLiteral("结果对象名称无效"));
            return false;
        }

        QString sourceName;
        QList<int> sourceCellIDList;
        if (!getSourceName(sourceName)) {
            popupMessage(QStringLiteral("选取实体对象无效"));
            return false;
        }

        QString e;
        if (!getE(e)) {
            popupMessage(QStringLiteral("弹性模量值无效"));
            return false;
        }

        QString g;
        if (!getG(g)) {
            popupMessage(QStringLiteral("剪切模量值无效"));
            return false;
        }

        QString nu;
        if (!getNu(nu)) {
            popupMessage(QStringLiteral("泊松比值无效"));
            return false;
        }

        QString rho;
        if (!getRho(rho)) {
            popupMessage(QStringLiteral("密度值无效"));
            return false;
        }

        QString a;
        if (!getA(a)) {
            popupMessage(QStringLiteral("热膨胀值无效"));
            return false;
        }

        QString comment;
        getComment(comment);

        if (nullptr != m_executor)
        {
            QString script = toScriptString(resultName, sourceName, e, g, nu, rho, a, comment);
            m_executor->excuteCommand(script);
        }
        else
        {
            NctiBaseModel* pBaseModel = m_document->GetBaseModel();
            NctiCommandManager* pComMan = NctiCommandManager::GetCommandManager(pBaseModel);
            if (!pComMan) {
                return false;
            }

            NctiArgumentObject argumentObject;
            std::vector<std::string> args{
                    sourceName.toUtf8().data(),

                    e.toUtf8().data(),
                    g.toUtf8().data(),
                    nu.toUtf8().data(),
                    rho.toUtf8().data(),
                    a.toUtf8().data(),

                    comment.toUtf8().data()
            };

            argumentObject.SetCommandArgumentVec(args);
            EnumNctiResult result = pComMan->RunCommand("cmd_ncti_mesh_add_mat", &argumentObject);
        }
        return true;
    }

    void MeshAddMatView::setup()
    {
        auto widget = new QWidget(this);
        ui->setupUi(widget);
        setTitle(QStringLiteral("材料属性"));
        setWidget(widget);

        ui->pushButton_select->setCheckable(true);
        connect(ui->pushButton_select, &QPushButton::clicked, this, [this](bool checked) {
            if (!checked) {
                ui->pushButton_select->setChecked(true);
            }

            std::vector<NctiDisplayObject*> selectObjects;
            NctiDocElementPubFun::GetDisplayObjectFromSelManager(m_document, selectObjects);
            setObjectSelection(selectObjects);
            });

        connect(ui->confrimBtn, &QPushButton::clicked, this, [this] {
            if (!beforeAccpet()) {
                return;
            }
            accept();
            });

        connect(ui->cancelBtn, &QPushButton::clicked, this, &MeshAddMatView::reject);
    }
    void MeshAddMatView::setObjectSelection(const std::vector<NctiDisplayObject*>& objectList)
    {
        m_selectObjects.clear();
        if (objectList.size() != 1) {
            ui->label_count->setText("0");
            ui->pushButton_select->setChecked(false);
            popupMessage(QStringLiteral("选择的实体对象数量不为 1"));
        }
        else {
            m_selectObjects = objectList;
            ui->label_count->setText(QString::number(m_selectObjects.size()));
            ui->pushButton_select->setChecked(m_selectObjects.size());
        }
    }

    bool MeshAddMatView::getResultName(QString& name)
    {
        auto text = ui->lineEdit_result->text();
        if (text.isEmpty()) {
            return false;
        }

        name = std::move(text);
        return true;
    }
    bool MeshAddMatView::getSourceName(QString& name)
    {
        if (m_selectObjects.empty()) {
            return false;
        }

        name = m_selectObjects[0]->GetObjName();
        return true;
    }
    bool MeshAddMatView::getE(QString& e)
    {
        QString value = ui->lineEdit_e->text();
        if (value.isEmpty()) {
            e = "None";
            return true;
        }

        bool ok = false;
        value.toDouble(&ok);
        if (!ok) {
            return false;
        }

        e = value;
        return true;
    }
    bool MeshAddMatView::getG(QString& g)
    {
        QString value = ui->lineEdit_g->text();
        if (value.isEmpty()) {
            g = "None";
            return true;
        }

        bool ok = false;
        value.toDouble(&ok);
        if (!ok) {
            return false;
        }

        g = value;
        return true;
    }
    bool MeshAddMatView::getNu(QString& nu)
    {
        QString value = ui->lineEdit_nu->text();
        if (value.isEmpty()) {
            nu = "None";
            return true;
        }

        bool ok = false;
        value.toDouble(&ok);
        if (!ok) {
            return false;
        }

        nu = value;
        return true;
    }
    bool MeshAddMatView::getRho(QString& rho)
    {
        QString value = ui->lineEdit_rho->text();
        if (value.isEmpty()) {
            rho = "None";
            return true;
        }

        bool ok = false;
        value.toDouble(&ok);
        if (!ok) {
            return false;
        }

        rho = value;
        return true;
    }
    bool MeshAddMatView::getA(QString& a)
    {
        QString value = ui->lineEdit_a->text();
        if (value.isEmpty()) {
            a = "None";
            return true;
        }

        bool ok = false;
        value.toDouble(&ok);
        if (!ok) {
            return false;
        }

        a = value;
        return true;
    }
    bool MeshAddMatView::getComment(QString& comment)
    {
        QString c = ui->plainTextEdit_comment->toPlainText();
        if (c.isEmpty()) {
            return false;
        }

        comment = c;
        return true;
    }
    QString MeshAddMatView::toScriptString(const QString& resultName, const QString& sourceName, const QString& e,
        const QString& g, const QString& nu, const QString& rho, const QString& a, const QString& comment)
    {
        if (comment.isEmpty())
        {
            return QString("doc.RunCommand(\"cmd_ncti_mesh_add_mat\", \"%1\", \"%2\", %3, %4, %5, %6, %7)")
                .arg(resultName).arg(sourceName).arg(e).arg(g).arg(nu).arg(rho).arg(a);
        }
        else
        {
            return QString("doc.RunCommand(\"cmd_ncti_mesh_add_mat\", \"%1\", \"%2\", %3, %4, %5, %6, %7, \"%8\")")
                .arg(resultName).arg(sourceName).arg(e).arg(g).arg(nu).arg(rho).arg(a).arg(comment);
        }
    }

    void MeshAddMatView::popupMessage(const QString& message, const QString& title)
    {
        MESSAGEBOX_INSTANCE->showMessageBox(message, title, false);
        MESSAGEBOX_INSTANCE->hide();
        MESSAGEBOX_INSTANCE->exec();
    }
}

