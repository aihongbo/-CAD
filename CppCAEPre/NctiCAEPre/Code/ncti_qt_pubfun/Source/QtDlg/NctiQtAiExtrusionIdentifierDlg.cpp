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

#include "NctiQtAiExtrusionIdentifierDlg.h"

#include "NctiBaseModel.h"
#include "NctiDocument.h"
#include "NctiSelectionManager.h"
#include "NctiSelectionDataList.h"
#include "NctiSelKeyDo.h"
#include "NctiDisplayObjectList.h"
#include "NctiDisplayObject.h"
#include "NctiDisplayModelBody.h"
#include "NctiQTPubFun.h"

namespace NCTI 
{
    NctiQtAiExtrusionIdentifierDlg* NctiQtAiExtrusionIdentifierDlg::m_instance = nullptr;
    NctiQtAiExtrusionIdentifierDlg::NctiQtAiExtrusionIdentifierDlg(NctiDocument* i_pDocument, QWidget* i_parent, NctiWindowPlatform* i_pPlatform)
        : QWidget(i_parent)
        , m_ui(new Ui::NctiExtrusionIdentifierDlg())
        , m_pDocument(i_pDocument)
        , m_pPlatform(i_pPlatform)
    {
        Init();
    }

    NctiQtAiExtrusionIdentifierDlg::~NctiQtAiExtrusionIdentifierDlg()
    {
        NCTI_DELETE m_ui;
    }

    NctiQtAiExtrusionIdentifierDlg* NctiQtAiExtrusionIdentifierDlg::Instance()
    {
        return m_instance;
    }

    void NctiQtAiExtrusionIdentifierDlg::SetInstance(NctiQtAiExtrusionIdentifierDlg* pNctiQtAiExtrusionIdentifierDlg)
    {
        m_instance = pNctiQtAiExtrusionIdentifierDlg;
    }

    void NctiQtAiExtrusionIdentifierDlg::Init()
    {
        m_ui->setupUi(this);
        this->setWindowFlags(Qt::Dialog);
        this->setWindowModality(Qt::NonModal);

        ResetSelectedMode();

        setWindowTitle(QString::fromUtf16(u"AI模型数据列表"));

        //记为拉伸面按钮
        connect(m_ui->pushButton_extrusionFace, SIGNAL(clicked()), this, SLOT(onExtrusionFaceButtonClick()));

    }

    void NctiQtAiExtrusionIdentifierDlg::onExtrusionFaceButtonClick()
    {
        NctiBaseModel* pBaseModel = m_pDocument->GetBaseModel();
        if (pBaseModel) {
            NctiSelectionManager* pSelMan = NctiSelectionManager::GetSelectionManager(pBaseModel);
            NctiSelectionDataList cSelDataList;
            pSelMan->GetSelected(cSelDataList, NctiSelKeyDo::ID);
            NctiDisplayObjectList cDoBodyList;
            NctiSelKeyDo* pSelKeyDo = NULL;
            cSelDataList.Init();
            while ((pSelKeyDo = (NctiSelKeyDo*)cSelDataList.Next()) != NULL) {
                NctiDisplayObject* pDoOriginal = pSelKeyDo->GetDoOriginal();
                NctiDisplayModelBody* pModelBody = (NctiDisplayModelBody*)pDoOriginal;
                Ncti_Size id = pModelBody->GetObjectId();
                ids.push_back(id);
                //NctiOCCBody* occBody = (NctiOCCBody*)(pModelBody->GetNctiBody());
                //NctiOCCBody* occBody = (NctiOCCBody*)i_TargeBody;
                //TopoDS_Shape TargeShape = *occBody->GetShape();
            }
        }
    }

    void NctiQtAiExtrusionIdentifierDlg::ResetSelectedMode()
    {
        NctiQTPubFun::SelBody(m_pPlatform, false);
        NctiQTPubFun::SelFace(m_pPlatform, true);
        NctiQTPubFun::SelEdge(m_pPlatform, false);
        NctiQTPubFun::SelVertex(m_pPlatform, false);
    }
}