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

#include "NctiQTPubFun.h"

#include "ncti_base.h"
#include "NctiDocument.h"
#include "NctiBaseModel.h"
#include "NctiWindowPlatform.h"
#include "NctiWindowViewManager.h"
#include "NctiPythonTool.h"

#include "NctiCommandResultDlg.h"
#include "NctiCompareObjectDlg.h"
#include "NctiPythonShowDlg.h"
#include "NctiFeatureTreeDlg.h"
#include "NcitCommonEdgeTreeDlg.h"
#include "NcitAbnormalObjectTreeDlg.h"

#include "NctiQtAiExtrusionIdentifierDlg.h"
#include "NctiQtCreateBoxDlg.h"
#include "NctiQtCreateCylinderDlg.h"
#include "NctiQtBooleanOpDlg.h"
#include "NctiQtFilletDlg.h"
#include "NctiQtAiModelAddLabelDlg.h"
#include "NctiQtAIModelDataListDlg.h"
#include "NctiAiRecognitionListDlg.h"
#include "NctiAiFeatureExtractDlg.h"
#include "NctiAddMeshSinglePointConstraintDlg.h"
#include "NctiAddCentralizeForceDlg.h"
#include "NctiAddMaterialDlg.h"

#include "NctiSelectModeDlg.h"
#include "NctiVisualModeDlg.h"
#include "NctiMoveObjectDlg.h"
#include "NctiScaleObjectDlg.h"
#include "NctiRotateObjectDlg.h"

#include "NctiFaceAttributeDlg.h"
#include "NctiEdgeAttributeDlg.h"
#include "NctiFillLoopDlg.h"
#include "NctiExtendFaceDlg.h"
#include "NctiSplitFacesDlg.h"
#include "NctiMeshQualityDlg.h"
#include "NctiDCM3AssemblyDlg.h"

namespace NCTI {
    Ncti_Boolean NctiQTPubFun::ShowExtrusionIdentifierDlg(NctiDocument* i_pDocument,
        QWidget* i_pQWidget,
        NctiWindowPlatform* i_pPlatform)
    {
        NctiQtAiExtrusionIdentifierDlg* dlg = NctiQtAiExtrusionIdentifierDlg::Instance();
        if (dlg == nullptr) {
            dlg = new NctiQtAiExtrusionIdentifierDlg(i_pDocument, i_pQWidget, i_pPlatform);
            dlg->show();
            NctiQtAiExtrusionIdentifierDlg::SetInstance(dlg);
        }
        else {
            if (dlg->isHidden()) dlg->show();
        }

        return true;
    }

    Ncti_Boolean NctiQTPubFun::ShowCreateBoxDlg(NctiDocument* i_pDocument, QWidget* i_pQWidget)
    {
        NctiQtCreateBoxDlg* dlg = new NctiQtCreateBoxDlg(i_pDocument, i_pQWidget);
        dlg->show();
        return true;
    }

    Ncti_Boolean NctiQTPubFun::ShowCreateCylinderDlg(NctiDocument* i_pDocument, QWidget* i_pQWidget)
    {
        NctiQtCreateCylinderDlg* dlg = new NctiQtCreateCylinderDlg(i_pDocument, i_pQWidget);
        dlg->show();
        return true;
    }

    Ncti_Boolean NctiQTPubFun::ShowBooleanUnitDlg(NctiDocument* i_pDocument, QWidget* i_pQWidget)
    {
        NctiQtBooleanOpDlg* dlg = new NctiQtBooleanOpDlg(i_pDocument, 0, i_pQWidget);
        dlg->show();
        return true;
    }

    Ncti_Boolean NctiQTPubFun::ShowBooleanCutDlg(NctiDocument* i_pDocument, QWidget* i_pQWidget)
    {
        NctiQtBooleanOpDlg* dlg = new NctiQtBooleanOpDlg(i_pDocument, 1, i_pQWidget);
        dlg->show();
        return true;
    }

    Ncti_Boolean NctiQTPubFun::ShowBooleanCommonDlg(NctiDocument* i_pDocument, QWidget* i_pQWidget)
    {
        NctiQtBooleanOpDlg* dlg = new NctiQtBooleanOpDlg(i_pDocument, 2, i_pQWidget);
        dlg->show();
        return true;
    }

    Ncti_Boolean NctiQTPubFun::ShowSelectModeDlg(NctiDocument* i_pDocument, QWidget* i_pQWidget)
    {
        NctiSelectModeDlg* dlg = new NctiSelectModeDlg(i_pDocument, i_pQWidget);
        dlg->show();
        return true;
    }

    Ncti_Boolean NctiQTPubFun::ShowMoveObjectDlg(NctiDocument* i_pDocument, QWidget* i_pQWidget)
    {
        NctiMoveObjectDlg* dlg = new NctiMoveObjectDlg(i_pDocument, i_pQWidget);
        dlg->show();
        return true;
    }

    Ncti_Boolean NctiQTPubFun::ShowRotateObjectDlg(NctiDocument* i_pDocument, QWidget* i_pQWidget)
    {
        NctiRotateObjectDlg* dlg = new NctiRotateObjectDlg(i_pDocument, i_pQWidget);
        dlg->show();
        return true;
    }

    Ncti_Boolean NctiQTPubFun::ShowFilletDlg(NctiDocument* i_pDocument, QWidget* i_pQWidget)
    {
        NctiQtFilletDlg* dlg = new NctiQtFilletDlg(i_pDocument, i_pQWidget);
        dlg->show();
        return true;
    }

    Ncti_Boolean NctiQTPubFun::ShowScaleObjectDlg(NctiDocument* i_pDocument, QWidget* i_pQWidget)
    {
        NctiScaleObjectDlg* dlg = new NctiScaleObjectDlg(i_pDocument, i_pQWidget);
        dlg->show();
        return true;
    }

    Ncti_Boolean NctiQTPubFun::ShowFillLoopDlg(NctiDocument* i_pDocument, QWidget* i_pQWidget)
    {
        NctiFillLoopDlg* dlg = new NctiFillLoopDlg(i_pDocument, i_pQWidget);
        dlg->show();
        return true;
    }

    Ncti_Boolean NctiQTPubFun::ShowVisualModeDlg(NctiDocument* i_pDocument, QWidget* i_pQWidget)
    {
        NctiVisualModeDlg* dlg = new NctiVisualModeDlg(i_pDocument, i_pQWidget);
        dlg->show();
        return true;
    }

    Ncti_Boolean NctiQTPubFun::ShowAIModelAddLabelDlg(NctiDocument* i_pDocument, QWidget* i_pQWidget)
    {
        NctiQtAiModelAddLabelDlg* dlg = NctiQtAiModelAddLabelDlg::Instance();
        if (dlg == nullptr) {
            dlg = new NctiQtAiModelAddLabelDlg(i_pDocument, i_pQWidget);
            dlg->show();
            NctiQtAiModelAddLabelDlg::SetInstance(dlg);
        }
        else {
            if (dlg->isHidden()) dlg->show();
        }

        return true;
    }

    Ncti_Boolean NctiQTPubFun::ShowRoundRecognitionListDlg(NctiDocument* i_pDocument, QWidget* i_pQWidget)
    {
        NctiQTPubFun::RoundRecognition(i_pDocument);
        NctiAiRecognitionListDlg* dlg = new NctiAiRecognitionListDlg(i_pDocument, i_pQWidget, "round");
        dlg->show();
        return true;
    }

    Ncti_Boolean NctiQTPubFun::ShowChamferRecognitionListDlg(NctiDocument* i_pDocument, QWidget* i_pQWidget)
    {
        NctiQTPubFun::ChamferRecognition(i_pDocument);
        NctiAiRecognitionListDlg* dlg = new NctiAiRecognitionListDlg(i_pDocument, i_pQWidget, "chamfer");
        dlg->show();
        return true;
    }

    Ncti_Boolean NctiQTPubFun::ShowThroughHoleRecognitionListDlg(NctiDocument* i_pDocument, QWidget* i_pQWidget)
    {
        NctiQTPubFun::ThroughHoleRecognition(i_pDocument);
        NctiAiRecognitionListDlg* dlg = new NctiAiRecognitionListDlg(i_pDocument, i_pQWidget, "through hole");
        dlg->show();
        return true;
    }

    NctiQtAIModelDataListDlg* NctiQTPubFun::ShowAIModelDataListDlg(NctiDocument* i_pDocument, QWidget* i_pQWidget,
        const std::vector<AiLabelTree>& setAiLabels,
        const std::vector<AiLabelTree>& setAiFeatureLabels,
        NctiObjectTree* objectTree)
    {
        NctiQtAIModelDataListDlg* dlg = NctiQtAIModelDataListDlg::Instance();
        if (dlg == nullptr) {
            dlg = new NctiQtAIModelDataListDlg(i_pDocument, i_pQWidget, setAiLabels, setAiFeatureLabels, objectTree);
            dlg->show();
            NctiQtAIModelDataListDlg::SetInstance(dlg);
        }
        else {
            if (dlg->isHidden()) {
                dlg->RefreshModelData(i_pDocument);
                dlg->show();
            }
        }
        return dlg;
    }

    Ncti_Boolean NctiQTPubFun::ShowMeshSinglePointConstraintDlg(NctiDocument* i_pDocument, QWidget* i_pQWidget)
    {
        NctiAddMeshSinglePointConstraintDlg* dlg = new NctiAddMeshSinglePointConstraintDlg(i_pDocument, i_pQWidget);
        dlg->show();
        return true;
    }

    Ncti_Boolean NctiQTPubFun::ShowMeshAddCentralizeForceDlg(NctiDocument* i_pDocument, QWidget* i_pQWidget)
    {
        NctiAddCentralizeForceDlg* dlg = new NctiAddCentralizeForceDlg(i_pDocument, i_pQWidget);
        dlg->show();
        return true;
    }

    Ncti_Boolean NctiQTPubFun::ShowMeshAddMaterialDlg(NctiDocument* i_pDocument, QWidget* i_pQWidget)
    {
        NctiAddMaterialDlg* dlg = new NctiAddMaterialDlg(i_pDocument, i_pQWidget);
        dlg->show();
        return true;
    }

    Ncti_Boolean NctiQTPubFun::ShowFaceAttributeDlg(NctiDocument* i_pDocument, QWidget* i_pQWidget)
    {
        NctiFaceAttributeDlg* dlg = new NctiFaceAttributeDlg(i_pDocument, i_pQWidget);
        dlg->show();
        return true;
    }

    Ncti_Boolean NctiQTPubFun::ShowEdgeAttributeDlg(NctiDocument* i_pDocument, QWidget* i_pQWidget)
    {
        NctiEdgeAttributeDlg* dlg = new NctiEdgeAttributeDlg(i_pDocument, i_pQWidget);
        dlg->show();
        return true;
    }

    Ncti_Boolean NctiQTPubFun::ShowRCornerExtract(NctiDocument* i_pDocument, QWidget* i_pQWidget)
    {
        NctiAiFeatureExtractDlg* dlg = new NctiAiFeatureExtractDlg(i_pDocument, 1, i_pQWidget);
        dlg->show();
        return true;
    }

    Ncti_Boolean NctiQTPubFun::ShowHoleExtract(NctiDocument* i_pDocument, QWidget* i_pQWidget)
    {
        NctiAiFeatureExtractDlg* dlg = new NctiAiFeatureExtractDlg(i_pDocument, 2, i_pQWidget);
        dlg->show();
        return true;
    }

    Ncti_Boolean NctiQTPubFun::ShowLogoExtract(NctiDocument* i_pDocument, QWidget* i_pQWidget)
    {
        NctiAiFeatureExtractDlg* dlg = new NctiAiFeatureExtractDlg(i_pDocument, 3, i_pQWidget);
        dlg->show();
        return true;
    }

    Ncti_Boolean NctiQTPubFun::ShowExtendFace(NctiDocument* i_pDocument, QWidget* i_pQWidget)
    {
        NctiExtendFaceDlg* dlg = new NctiExtendFaceDlg(i_pDocument, i_pQWidget);
        dlg->show();
        return true;
    }

    Ncti_Boolean NctiQTPubFun::ShowSplitFace(NctiDocument* i_pDocument, QWidget* i_pQWidget)
    {
        NctiSplitFacesDlg* dlg = new NctiSplitFacesDlg(i_pDocument, i_pQWidget);
        dlg->show();
        return true;
    }

    void NctiQTPubFun::ShowCompareDlg(NctiWindowPlatform* i_pPlatform, QWidget* i_pQWidget)
    {
        auto view = i_pPlatform->GetCurrentViewManager();
        if (!view) return;

        NctiDocument* pDocument = view->GetDocument();
        if (!pDocument || !pDocument->GetBaseModel() || !pDocument->GetBaseModel()->GetActiveBaseView()) return;

        NctiCompareObjectDlg* dlg = new NctiCompareObjectDlg(pDocument, i_pQWidget);
        dlg->show();
    }

    void NctiQTPubFun::ShowMulticoreBatchScriptCompare(NctiWindowPlatform* i_pPlatform, QWidget* i_pQWidget)
    {
        auto view = i_pPlatform->GetCurrentViewManager();
        if (!view) return;

        NctiDocument* pDocument = view->GetDocument();
        if (!pDocument || !pDocument->GetBaseModel() || !pDocument->GetBaseModel()->GetActiveBaseView()) return;

        NctiCommandResultDlg* dlg = new NctiCommandResultDlg(pDocument, i_pQWidget);
        dlg->show();
    }

    void NctiQTPubFun::RefreshAIModelDataListDlg(NctiWindowPlatform* i_pPlatform)
    {
        auto view = i_pPlatform->GetCurrentViewManager();
        if (!view) return;

        NctiDocument* pDocument = view->GetDocument();
        NctiQtAIModelDataListDlg* dlg = NctiQtAIModelDataListDlg::Instance();
        if (dlg) { dlg->RefreshModelData(pDocument); }
    }

    Ncti_Boolean NctiQTPubFun::PythonShowDlg(void* args, void* o_args, bool bReturn, void* mainWindow)
    {
        if (args == nullptr) return false;
        if (mainWindow == nullptr) {
            NctiPythonShowDlg dlg((PyObject*)args, (Ncti_VariantVleVec*)o_args, bReturn);
            int ret = dlg.exec();
            return (ret == 1);
        }
        else {
            QMainWindow* pMainWin = static_cast<QMainWindow*>(mainWindow);
            NctiPythonShowDlg* pDlg = new NctiPythonShowDlg((PyObject*)args, (Ncti_VariantVleVec*)o_args, bReturn, pMainWin);
            pDlg->setAttribute(Qt::WA_DeleteOnClose);
            pDlg->setModal(false);
            pDlg->show();

            QEventLoop loop;
            int ret = 0;
            QObject::connect(pDlg, &NctiPythonShowDlg::rejected, &loop, &QEventLoop::quit);
            QObject::connect(pDlg, &NctiPythonShowDlg::accepted, [&loop, &ret]() {
                ret = 1;
                loop.quit();
                });
            loop.exec();
            return ret;
        }
    }

    Ncti_Boolean NctiQTPubFun::PythonShowCustomDlg(void* args, void* o_args, bool bReturn, void* mainWindow)
    {
        if (args == nullptr) return false;
        long nDlgId = 0;
        PyObject* pyArgs = (PyObject*)args;
        Ncti_Integer num_args = NctiPyCB.Size(pyArgs);//PyTuple_Size(pyArgs);
        if (num_args >= 1) {
            PyObject* arg0 = NctiPyCB.GetTupleItem(pyArgs, 0);//PyTuple_GetItem(pyArgs, 0);
            //if (PyLong_Check(arg0)) { nDlgId = PyLong_AsLong(arg0); }
            if (NctiPyCB.IsLong(arg0)) { nDlgId = NctiPyCB.GetLong(arg0); }
        }

        QMainWindow* pMainWin = static_cast<QMainWindow*>(mainWindow);

        if (nDlgId == DLGID_MESH_QUALITY) //网格质量
        {
            if (num_args >= 3) {
                int nMode = 0;
                std::vector<std::string> textShowList;
                std::vector<Ncti_Double> dValueVec;

                //文本
                PyObject* argValue2 = NctiPyCB.GetTupleItem(pyArgs, 1);//PyTuple_GetItem(pyArgs, 1);
                //if (PyList_Check(argValue2)) 
                if (NctiPyCB.IsList(argValue2))
                {
                    //for (size_t i = 0; i < PyList_Size(argValue2); i++)
                    for (size_t i = 0; i < NctiPyCB.GetListSize(argValue2); i++)
                    {
                        PyObject* argData = NctiPyCB.GetListItem(argValue2, i);//PyList_GetItem(argValue2, i);
                        //if (PyUnicode_Check(argData))
                        if (NctiPyCB.IsUnicode(argData))
                        {
                            std::string strTemp = NctiPyCB.GetUnicodeStr(argData);//PyUnicode_AsUTF8(argData);
                            textShowList.push_back(strTemp);
                        }
                    }

                    //if (PyList_Size(argValue2) != textShowList.size()) return false;
                    if (NctiPyCB.GetListSize(argValue2) != textShowList.size()) return false;
                }
                else {
                    return false;
                }

                //0:长宽比 1:扭曲度 2:雅克比 3:最小角度 4:最大角度
                PyObject* argMode = NctiPyCB.GetTupleItem(pyArgs, 2);//PyTuple_GetItem(pyArgs, 2);
                //if (PyLong_Check(argMode)) { nMode = PyLong_AsLong(argMode); }
                if (NctiPyCB.IsLong(argMode)) { nMode = NctiPyCB.GetLong(argMode); }
                else {
                    return false;
                }

                PyObject* argValue = NctiPyCB.GetTupleItem(pyArgs, 3);//PyTuple_GetItem(pyArgs, 3);
                //if (PyList_Check(argValue))
                if (NctiPyCB.IsList(argValue))
                {
                    //for (size_t i = 0; i < PyList_Size(argValue); i++)
                    for (size_t i = 0; i < NctiPyCB.GetListSize(argValue); i++)
                    {
                        PyObject* argData = NctiPyCB.GetListItem(argValue, i);//PyList_GetItem(argValue, i);
                        //if (PyFloat_Check(argData))
                        if (NctiPyCB.IsFloat(argData))
                        {
                            Ncti_Double dbl = NctiPyCB.GetDouble(argData);//PyFloat_AsDouble(argData);
                            dValueVec.push_back(dbl);
                        }
                    }
                    //if (PyList_Size(argValue) != dValueVec.size()) return false;
                    if (NctiPyCB.GetListSize(argValue) != dValueVec.size()) return false;
                }
                else {
                    return false;
                }

                NctiMeshQualityDlg* dlg = new NctiMeshQualityDlg(nMode, textShowList, dValueVec, pMainWin);
                dlg->setAttribute(Qt::WA_DeleteOnClose);
                dlg->show();
                return true;
            }
            return false;
        }
        else if (nDlgId == DLGID_FEATURE_TREE) //特征列表
        {
            NctiFeatureTreeDlg* dlg = new NctiFeatureTreeDlg(pMainWin);
            bool res = dlg->init(pyArgs);
            dlg->setAttribute(Qt::WA_DeleteOnClose);
            dlg->show();
            return res;
        }
        else if (nDlgId == DLGID_COMMON_EDGE) //共边显示
        {
            NcitCommonEdgeTreeDlg* dlg = new NcitCommonEdgeTreeDlg(pMainWin);
            bool res = dlg->init(pyArgs);
            dlg->setAttribute(Qt::WA_DeleteOnClose);
            dlg->show();
            return res;
        }
        else if (nDlgId == DLGID_ABNORMAL_OBJECT) //异常的对象显示
        {
            NcitAbnormalObjectTreeDlg* dlg = new NcitAbnormalObjectTreeDlg(pMainWin);
            bool res = dlg->init(pyArgs);
            dlg->setAttribute(Qt::WA_DeleteOnClose);
            dlg->show();
            return res;
        }
        else if (nDlgId == DLGID_DCM3_ASSEMBLY)
        {
            NctiDCM3AssemblyDlg::Instance()->show();
            bool res = NctiDCM3AssemblyDlg::Instance()->init(pyArgs);
            return res;
        }
        return false;
    }

    Ncti_Boolean NctiQTPubFun::ShowMeshQualistyDlg(int nMode, std::vector<std::string> sTextList,
        const std::vector<double>& dValueList,
        std::function<void()> func,
        void* mainWindow)
    {
        QMainWindow* pMainWin = static_cast<QMainWindow*>(mainWindow);
        NctiMeshQualityDlg* dlg = new NctiMeshQualityDlg(nMode, sTextList, dValueList, pMainWin);
        dlg->setCallBack(func);
        dlg->setAttribute(Qt::WA_DeleteOnClose);
        dlg->show();
        return true;
    }

    Ncti_Boolean NctiQTPubFun::ShowSaveDialog(QWidget* i_parent, const QString& i_title, const QString& i_filter, QString& o_filename)
    {
        QFileDialog dialog(i_parent);
        o_filename = dialog.getSaveFileName(i_parent, i_title, "", i_filter);
        return !o_filename.isEmpty();
    }
}