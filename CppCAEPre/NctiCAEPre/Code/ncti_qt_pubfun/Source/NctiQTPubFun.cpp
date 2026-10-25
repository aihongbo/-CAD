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
#include "QCoreApplication"
#ifdef _MSC_VER
#include <Windows.h>
#endif

#include <QFileDialog>
#include <QMessageBox>
#include <QDesktopServices>
#include <QGridLayout>
#include <QDir>
#include <QTextStream>

#include <vector>

#include "NctiArgumentObject.h"
#include "NctiBaseModel.h"
#include "NctiBaseView.h"
#include "NctiBaseUtility.h"
#include "NctiCommandManager.h"
#include "NctiDocument.h"
#include "NctiDocElementPubFun.h"
#include "NctiRenderDrawingKit.h"
#include "NctiSPUserTraceInterface.h"
#include "NctiWindowPlatform.h"
#include "NctiWindowInputFileName.h"
#include "NctiWindowView.h"
#include "NctiDocViewManager.h"
#include "NctiHistoryManager.h"
#include "NctiWindowViewManager.h"
#include "NctiUserInterfaceManager.h"
#include "NctiSelectionManager.h"
#include "NctiSaveFileManager.h"
#include "NctiPluginsManager.h"
#include "NctiTestSystemObject.h"
#include "NctiTestCaseToModelManage.h"

#include "NctiDisplayModelBody.h"
#include "NctiDisplayDocCustomContainer.h"
#include "NctiDisplayDocPart.h"
#include "NctiDisplayDocElement.h"
#include "NctiDisplayDocAssembly.h"
#include "NctiDisplayDocSystemObject.h"
#include "NctiDisplayPolyMesh.h"
#include "NctiDisplayObjectList.h"
#include "NctiDisplayGrid.h"
#include "NctiDisplayGridMesh.h"
#include "NctiDisplayWorkPlane.h"
#include "NctiDisplayDocSketch.h"
#include "NctiDisplaySketchArc.h"
#include "NctiDisplaySketchRect.h"
#include "NctiDisplaySketchCircle.h"
#include "NctiDisplaySketchPolyline.h"
#include "NctiDisplaySketchPolygon.h"
#include "NctiDisplaySketchLine.h"
#include "NctiDisplaySketchSpline.h"
#include "NctiDisplaySketchDot.h"
#include "NctiDisplaySketchCenterLine.h"
#include "NctiDisplaySketchEllipse.h"
#include "NctiDisplaySketchTan2Circles.h"
#include "NctiSketchConstrManager.h"
#include "NctiDisplayGExtrude.h"
#include "NctiDisplayGRevolve.h"
#include "NctiDisplayGSketch.h"
#include "NctiDisplayGSketchGroup.h"
#include "NctiDisplayMaterialAttribute.h"
#include "NctiDisplayConcentratedForces.h"
#include "NctiDisplaySinglePointConstraint.h"
#include "NctiDisplayPressure.h"
#include "NctiDisplayLoadMoment.h"
#include "NctiDisplayLoadGravity.h"
#include "NctiDisplayInertiaRelief.h"
#include "NctiDisplayOutput.h"
#include "NctiDisplayStaticStep.h"
#include "NctiDisplayFrequencyStep.h"
#include "NctiDisplayParticleObject.h"
#include "NctiDisplaySet.h"
#include "NctiDisplaySection.h"
#include "NctiDisplayCoupling.h"
#include "NctiDisplayBuckleStep.h"

#include "NctiViewerRenderer.h"
#include "NctiTopoCell.h"
#include "NctiTopoFace.h"
#include "NctiTopoLoop.h"
#include "NctiTopoEdge.h"
#include "NctiGeomLine.h"
#include "NctiGeomBSplineCurve.h"
#include "NctiGeomElementarySurface.h"
#include "NctiGeometryFunction.h"
#include "NctiCreateModelScriptPub.h"
#include "NctiAIGeoAttributeParser.h"
#include "NctiAiModelSystemObject.h"
#include "NctiDCM3PubFun.h"

#include "NctiString.h"
#include "NctiFile.h"
#include "NctiDesignModel.h"
#include "NctiDeleteTool.h"
#include "NctiImageTool.h"
#include "NctiPythonTool.h"
#include "NctiDebug.h"

#include "NctiInitializeTool.h"
#include "CallbackInterfaces.h"
#include "NctiRenderMaterialKit.h"
#include "NctiRenderSegmentItem.h"
#include "NctiRenderSceneItem.h"
#include "NctiRenderManager.h"

#include "NctiDCM3Set.h"
#include "NctiDisplayDCM3Dimension.h"
#include "NctiParametricModelTool.h"

using namespace NCTI;

void NctiQTPubFun::showErrorMsgBox(NctiErrorType errType)
{
    auto errMsg = NctiInitializeTool().getErrorMessage(errType);
    if (errMsg.empty()) 
        return;

    if (errType == NCTI::ErrroMachineId) {
        errMsg.append("，当前机器码为：");
        errMsg.append(NctiPluginsManager::instance()->GetMachineCode());
    }
    NctiPrintf(errMsg.c_str());

    QMessageBox msgBox;
    msgBox.setIcon(QMessageBox::Warning);
    msgBox.setWindowTitle("错误");
    msgBox.setText(QString::fromUtf8(errMsg.c_str()));

    // 设置最小尺寸
    QSpacerItem* spacer = new QSpacerItem(200, 150, QSizePolicy::Minimum, QSizePolicy::Expanding);
    QGridLayout* layout = (QGridLayout*)msgBox.layout();
    layout->addItem(spacer, layout->rowCount(), 0, 1, layout->columnCount());
    msgBox.exec();
}

NctiWindowPlatform* NctiQTPubFun::CreateNctiViewWindow(QWidget* i_pQWidget)
{   
    int w = 300, h = 300;
    if (i_pQWidget)
    {
        w = i_pQWidget->size().width();
        h = i_pQWidget->size().height();
    }
    auto winPlatform = NCTI_NEW NctiWindowPlatform(w,h);
    if (i_pQWidget) {
        winPlatform->SetParent(i_pQWidget->winId());
        winPlatform->setVisible(true);
    }
    return winPlatform;
}

// 创建装配体文档
NctiDocument* NctiQTPubFun::CreateAssemblyDocument(NctiWindowPlatform* i_pPlatform, 
    EnumModelDoc i_model,
    EnumGCSDoc i_constraintType,
    EnumMeshDoc i_meshType)
{
    if (!i_pPlatform) { return nullptr; }

    Ncti_UInteger id = NctiDocElementPubFun::NewAssemble(i_model, i_constraintType, i_meshType);
	NctiDocument* pDocment = NctiDocumentManager::instance()->GetDocument(id);
    
    NctiDocViewManager* pDocView = NctiDocViewManager::GetDocViewManager(pDocment->GetBaseModel());
    NctiDisplayDocElement* pRoot = pDocView->GetRootDocElement();
    if (pRoot) {
        QString strName = QObject::tr("装配");
        QByteArray byte = strName.toUtf8();
        pRoot->SetDisplayName(byte.data());
    }

    NctiBaseModel* pBaseModel                       = pDocment->GetBaseModel();
    NctiUserInterfaceManager* pUserInterfaceManager = NctiUserInterfaceManager::GetUserInterfaceManager(pBaseModel);
    if (pUserInterfaceManager) {
        auto pTrace = NCTI_NEW NctiSPUserTraceInterface(i_pPlatform);
        if (pTrace) { pUserInterfaceManager->SetTrace(pTrace); }
        auto pFileName = NCTI_NEW NctiWindowInputFileName();
        if (pFileName) { pUserInterfaceManager->SetInputFileName(pFileName); }
    }

    auto mgr = i_pPlatform->CreateViewManager(pDocment);
    AddRenderView(mgr, NCTI_RENDER_VULKAN);

    NctiDocElementPubFun::CreateTestSystemObject(pBaseModel);
	NctiDocElementPubFun::CreateAiModelSystemObject(pBaseModel);
	NctiDocElementPubFun::CreateTestCaseToModelManageObject(pBaseModel);
    return pDocment;
}

// 添加装配体
void NctiQTPubFun::AddAssembly(NctiWindowPlatform* i_pPlatform, 
    EnumModelDoc i_model, 
    EnumGCSDoc i_constraintType,
    EnumMeshDoc i_meshType)
{
    auto view = i_pPlatform->GetCurrentViewManager();
    if (view) {
        NctiDocument* pDocument            = view->GetDocument();
        NctiCommandManager* pComMan        = NctiCommandManager::GetCommandManager(pDocument->GetBaseModel());
        NctiDocViewManager* pDocView       = NctiDocViewManager::GetDocViewManager(pDocument->GetBaseModel());
        NctiDisplayDocElement* pDocElement = pDocView->GetActiveDocElement();
        if (pDocElement->IsTypeName(NctiDisplayDocAssembly::ID)) {
            QString strName = QObject::tr("装配");
            QByteArray byte = strName.toUtf8();
            NctiArgumentObject arg;
            arg.SetDisplayObject1(pDocElement);
			//arg.SetDisplayName(byte.data());
            arg.SetCommandArgumentVec({ byte.data() });
			arg.Setm_ModelDoc(i_model);
			arg.Setm_constraintType(i_constraintType);
			arg.Setm_meshType(i_meshType);
            pComMan->RunCommand("cmd_add_new_assembly", &arg);
        }
    }
}

// 添加零件
void NctiQTPubFun::AddPart(NctiWindowPlatform* i_pPlatform,
                           EnumModelDoc i_model,
                           EnumGCSDoc i_constraintType,
                           EnumMeshDoc i_meshType)
{
    if (!i_pPlatform || !i_pPlatform->GetCurrentViewManager()) return;

    NctiDocument* pDocument            = i_pPlatform->GetCurrentViewManager()->GetDocument();
    NctiCommandManager* pComMan        = NctiCommandManager::GetCommandManager(pDocument->GetBaseModel());
    NctiDocViewManager* pDocView       = NctiDocViewManager::GetDocViewManager(pDocument->GetBaseModel());
    NctiDisplayDocElement* pDocElement = pDocView->GetActiveDocElement();
    NctiDisplayObject* pElement        = pDocElement;
    while (pElement && !pElement->IsTypeName(NctiDisplayDocAssembly::ID)) {
        pElement = pElement->GetDoOwner();
    }
    if (pElement && pElement->IsTypeName(NctiDisplayDocAssembly::ID)) {
        QString strName = QObject::tr("零件");
        QByteArray byte = strName.toUtf8();
        NctiArgumentObject arg;
        arg.SetDisplayObject1(pElement);
        arg.Setm_ModelDoc(i_model);
        arg.Setm_constraintType(i_constraintType);
        arg.Setm_meshType(i_meshType);
		//arg.SetDisplayName(byte.data());
		arg.SetCommandArgumentVec({ byte.data() });
        pComMan->RunCommand("cmd_add_new_part", &arg);
    }
}

// 创建模型文档
NctiDocument* NctiQTPubFun::CreateModelDocument(NctiWindowPlatform* i_pPlatform,
                                                EnumModelDoc i_model,
                                                EnumGCSDoc i_constraintType,
                                                EnumMeshDoc i_meshType)
{
    if (!i_pPlatform) { return nullptr; }

    NctiDocument* pDocment = NctiDocumentManager::instance()->CreateDocument();
    pDocment->NewPartDocument();

    NctiBaseModel* pBaseModel                       = pDocment->GetBaseModel();
    NctiUserInterfaceManager* pUserInterfaceManager = NctiUserInterfaceManager::GetUserInterfaceManager(pBaseModel);
    if (pUserInterfaceManager) {
        auto pTrace = NCTI_NEW NctiSPUserTraceInterface(i_pPlatform);
        if (pTrace) { pUserInterfaceManager->SetTrace(pTrace); }
        auto pFileName = NCTI_NEW NctiWindowInputFileName();
        if (pFileName) { pUserInterfaceManager->SetInputFileName(pFileName); }
    }

    auto mgr = i_pPlatform->CreateViewManager(pDocment);
    AddRenderView(mgr, NCTI_RENDER_VULKAN);

    NctiDocViewManager* pDocViewManager   = NctiDocViewManager::GetDocViewManager(pBaseModel);
    NctiDisplayDocElement* pActiveElement = pDocViewManager->GetRootDocElement();
    if (pActiveElement && pActiveElement->IsTypeName(NctiDisplayDocPart::ID)) {
        NctiHistoryManager* pHisMan                        = NctiHistoryManager::GetHistoryManager(pBaseModel);
        NctiDisplayDocCustomContainer* pDocCustomContainer = nullptr;
        pHisMan->SetActive(false);
        NCTI_API_BEGIN(pHisMan)
        {
            QString strName = QObject::tr("零件");
            QByteArray byte = strName.toUtf8();
            pActiveElement->SetDisplayName(byte.data());
        }
        NctiGeometryFunction::create_model_doc(i_model, pBaseModel, pDocCustomContainer);
        if (pDocCustomContainer) {
            pDocCustomContainer->SetDcmDocType(i_constraintType);
            pDocCustomContainer->SetMeshDocType(i_meshType);
        }
        NCTI_API_END
        pDocViewManager->AddDocument(pDocViewManager->GetRootDocElement(), pDocCustomContainer);
        pHisMan->SetActive(true);
    }
    NctiDocElementPubFun::CreateTestSystemObject(pBaseModel);

    NctiDocElementPubFun::CreateAiModelSystemObject(pBaseModel);
    NctiDocElementPubFun::CreateTestCaseToModelManageObject(pBaseModel);
#if NCTI_PARAM_OPEN
    NctiParametricModelTool::CreateParamManagerObject(pBaseModel);
#endif
    return pDocment;
}

Ncti_Boolean NctiQTPubFun::ImportAssemblyOrPart(NctiWindowPlatform* i_pPlatform, const QString& i_filePath)
{
    if (!i_pPlatform || i_filePath.isNull()) { return false; }

    QByteArray ba   = i_filePath.toUtf8();
    char* cFilePath = ba.data();

    if (NctiFile::exists(cFilePath)) {
        NctiArgumentObject argumentObject;
        argumentObject.SetFilePath(cFilePath);

        NctiBaseModel* pBaseModel   = i_pPlatform->GetCurrentViewManager()->GetDocument()->GetBaseModel();
        NctiCommandManager* pCmdMgr = NctiCommandManager::GetCommandManager(pBaseModel);
        if (pCmdMgr) { pCmdMgr->RunCommand("cmd_import_new_assemblyorpart", &argumentObject); }
    }
    return true;
}

Ncti_Boolean NctiQTPubFun::RemoveAssemblyOrPart(NctiWindowPlatform* i_pPlatform)
{
    if (!i_pPlatform) {
        return false;
    }
    NctiBaseModel* pBaseModel    = i_pPlatform->GetCurrentViewManager()->GetDocument()->GetBaseModel();
    NctiDocViewManager* pDocView = NctiDocViewManager::GetDocViewManager(pBaseModel);
    NctiArgumentObject argumentObject;
    argumentObject.SetDisplayObject1(pDocView->GetActiveDocElement());
    NctiCommandManager* pCmdMgr = NctiCommandManager::GetCommandManager(pBaseModel);
    if (pCmdMgr) { pCmdMgr->RunCommand("cmd_remove_assemblyorpart", &argumentObject); }
    return true;
}

// 关闭模型文档
void NctiQTPubFun::CloseModelDocument(NctiWindowPlatform* i_pPlatform)
{
    if (!i_pPlatform) { return; }

    NctiDocument* pDocument = GetCurrentViewDocment(i_pPlatform);
    if (!pDocument) { return; }

    NctiBaseModel* pBaseModel            = pDocument->GetBaseModel();
    NctiSaveFileManager* saveFileManager = NctiSaveFileManager::instance();
    if (saveFileManager) {
        saveFileManager->DelDocument(pDocument); //删除文档在保存管理器
    }

    NctiSelectionManager* pSelectMgr = NctiSelectionManager::GetSelectionManager(pBaseModel);
    if (pSelectMgr) { pSelectMgr->ResetSelection(true); }
    i_pPlatform->CloseCurrentView();
    i_pPlatform->Close();
    NctiRenderMemoryPool::instance()->FreeMemory();
}

// 获取当前视图文档对象
NctiDocument* NctiQTPubFun::GetCurrentViewDocment(NctiWindowPlatform* i_pPlatform)
{
    if (!i_pPlatform || !i_pPlatform->GetCurrentViewManager()) { return nullptr; }
    return i_pPlatform->GetCurrentViewManager()->GetDocument();
}

// 执行Python脚本文件
void NctiQTPubFun::ExecutePython(QWidget* i_pQWidget)
{
    QString filePath = QFileDialog::getOpenFileName(i_pQWidget, "RunPy", "", "Py Files (*.py)");
    if (!filePath.isEmpty()) {
        // 加载并执行 Python 文件
        QByteArray ba = filePath.toUtf8();
        NctiPyRunSimpleFile(ba.data());
        //FILE* f = NctiFile::get_file_point(ba.data(), "r");
        //if (f) {
        //    PyRun_SimpleFile(f, ba.data());
        //    fclose(f);
        //}
    }
}

// 检查文档是否已经打开
NctiDocument* NctiQTPubFun::CheckDocumentAlreadyOpen(NctiWindowPlatform* i_pPlatform, const QString& i_filePath)
{
    if (i_filePath.isNull()) { return nullptr; }
    NctiDocument* pDocment = GetCurrentViewDocment(i_pPlatform);
    if (pDocment) {
        NctiSaveFileManager* saveFileManager = NctiSaveFileManager::instance();
        if (saveFileManager) {
            NCTI_SaveFileData fileData = saveFileManager->GetDocument(pDocment);
            if (fileData.IsValid()) {
                QByteArray ba = i_filePath.toUtf8();
                Ncti_Char ch[1024];
                NctiString::LocaleSprintf(ch, "print('文件 %s  已打开')", ba.constData());
                NctiPyCB.RunSimpleString(ch);
                return pDocment;
            }
        }
    }
    return nullptr;
}

// 加载NCTI文件
NctiDocument* NctiQTPubFun::LoadNctiFile(NctiWindowPlatform* i_pPlatform, const QString& i_filePath)
{
    if (!i_pPlatform || i_filePath.isNull())
        return nullptr;

    // 检查文档是否已经打开
    NctiDocument* pOpenedDoc = CheckDocumentAlreadyOpen(i_pPlatform, i_filePath);
    if (pOpenedDoc)  
        return pOpenedDoc;

    QByteArray ba = i_filePath.toUtf8();
    //Ncti_UInteger docId = NctiDocElementPubFun::OpenFile(ba.data());//OpenFile中不能初始化窗口的NctiUserInterfaceManager
	NctiDocument* pDocment = NctiDocumentManager::instance()->CreateDocument();
	NctiBaseModel* pBaseModel = pDocment->GetBaseModel();
    NctiUserInterfaceManager* pUserInterfaceManager = NctiUserInterfaceManager::GetUserInterfaceManager(pBaseModel);
    if (pUserInterfaceManager) {
        auto pTrace = NCTI_NEW NctiSPUserTraceInterface(i_pPlatform);
        pUserInterfaceManager->SetTrace(pTrace);
		auto pFileName = NCTI_NEW NctiWindowInputFileName();
		pUserInterfaceManager->SetInputFileName(pFileName);
    }
    //
	pDocment->ReadFile(ba.data());
	pDocment->SetManualModified(false);

    NctiSaveFileManager* saveFileManager = NctiSaveFileManager::instance();
    if (saveFileManager)
        saveFileManager->AddDocument(pDocment, ba.data());

    auto mgr = i_pPlatform->CreateViewManager(pDocment);
    AddRenderView(mgr, NCTI_RENDER_VULKAN);

    NctiDisplayDocSystemObject* pDocSystem = NctiDocViewManager::GetDocViewManager(pBaseModel)->GetDocSystemObject();
    auto view = pBaseModel->GetActiveBaseView();
    if (pDocSystem&& view) {
        NctiPosition pos;
        NctiPosition tar;
        NctiVector up;
        pDocSystem->GetCamera(pos, tar, up);
        if (pos != tar && up.len() != 0) {
            view->SetCameraInfo(pos, tar, up);
        }
        else {
            view->Zoom();
        }
        view->Update();
    }
    return pDocment;
}

bool NctiQTPubFun::GetThumbnail(const std::vector<unsigned char>& i_Buffer,
                                Ncti_Integer i_w,
                                Ncti_Integer i_h,
                                Ncti_Integer i_rowPitch,
                                Ncti_Integer i_wThumbnail,
                                Ncti_Integer i_hThumbnail,
                                DocImage& ImageResult)
{
    Ncti_Integer nHelp = i_w;
    if (nHelp > i_h) { nHelp = i_h; }
    Ncti_Integer cropWidth  = nHelp;
    Ncti_Integer cropHeight = nHelp;
    Ncti_Integer x_offset   = (i_w - cropWidth) / 2;
    Ncti_Integer y_offset   = (i_h - cropHeight) / 2;
    QImage img(i_Buffer.data(), i_w, i_h, i_rowPitch, QImage::Format_RGBA8888);
    QRect cropRect(x_offset, y_offset, cropWidth, cropHeight);
    QImage croppedImage = img.copy(cropRect);
    // 缩放图像为 256x256
    QImage scaledImage = croppedImage.scaled(i_wThumbnail, i_hThumbnail, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    const void* data   = scaledImage.bits();
    int stride_bytes   = scaledImage.bytesPerLine();
    int bytesPerPixel  = scaledImage.depth() / 8;

    ImageResult.w        = i_wThumbnail;
    ImageResult.h        = i_hThumbnail;
    ImageResult.offset   = 0;
    ImageResult.rowPitch = stride_bytes;
    ImageResult.Buffer.resize(i_wThumbnail * i_hThumbnail * bytesPerPixel);
    memcpy(ImageResult.Buffer.data(), data, i_wThumbnail * i_hThumbnail * bytesPerPixel);
    return true;
}

// 保存为NCTI文件
void NctiQTPubFun::SaveAsNctiFile(NctiWindowPlatform* i_pPlatform, const QString& i_filePath, Ncti_Boolean i_SaveAs)
{
    // 参数有效性检查
    if (!i_pPlatform || i_filePath.isNull())
        return;

    // 获取当前文档
    NctiDocument* pDocument = GetCurrentViewDocment(i_pPlatform);
    if (!pDocument) { return; }

    NctiBaseModel* pBaseModel    = pDocument->GetBaseModel();
    NctiHistoryManager* pHisMan  = NctiHistoryManager::GetHistoryManager(pBaseModel);
    NctiDocViewManager* pDocView = NctiDocViewManager::GetDocViewManager(pBaseModel);
    Ncti_Boolean booHis          = pHisMan->GetActive();

    pHisMan->SetActive(false);

    NctiDisplayDocSystemObject* pDocSystem = pDocView->GetDocSystemObject();
    auto view = pDocument->GetBaseModel()->GetActiveBaseView();
    if (pDocSystem&& view&& view->GetRenderCanvas()) {
        NctiPosition pos;
        NctiPosition tar;
        NctiVector up;
        view->GetCameraInfo(pos, tar, up);

        std::vector<unsigned char> o_Buffer;
        Ncti_Integer o_w;
        Ncti_Integer o_h;
        Ncti_Integer o_rowPitch;
        view->GetRenderCanvas()->GetImageData(o_Buffer, o_w, o_h, o_rowPitch);

        DocImage ImageResult;
        if (!NctiImageTool::RunGetThumbnailFun(
                o_Buffer, o_w, o_h, o_rowPitch, _ThumbnailWidth_, _ThumbnailHeight_, ImageResult)) {
            // 获取缩略图失败
            ImageResult.w        = o_w;
            ImageResult.h        = o_h;
            ImageResult.offset   = 0;
            ImageResult.rowPitch = o_rowPitch;
            ImageResult.Buffer   = o_Buffer;
        }

        NCTI_API_BEGIN(pHisMan)
        pDocSystem->SetCamera(pos, tar, up);
        pDocSystem->SetImageResult(ImageResult);
        NCTI_API_END
    }

    pHisMan->SetActive(booHis);

    QByteArray ba = i_filePath.toUtf8();
    pDocument->SaveFile(ba.data(), i_SaveAs);
   // NctiDocElementPubFun::Save(pDocument, ba.data());

    NctiSaveFileManager* saveFileManager = NctiSaveFileManager::instance();
    if (saveFileManager) {
        // 将文档添加到保存管理器
        saveFileManager->AddDocument(pDocument, ba.data());
    }
}

void NctiQTPubFun::ImportModelFile(NctiWindowPlatform* i_pPlatform, const QStringList& i_filePaths, int iImportMode)
{
    if (!i_pPlatform || i_filePaths.isEmpty()) { return; }

    NctiDocument* pDocument = GetCurrentViewDocment(i_pPlatform);
    if (!pDocument) { return; }

    for (const QString& filePath : i_filePaths) {
        QByteArray ba   = filePath.toUtf8();
        const char* cFilePath = ba.data();
        NctiDebug::debug(cFilePath);
        if (NctiFile::exists(cFilePath)) {
            NctiArgumentObject argumentObject;
            argumentObject.SetFilePath(cFilePath);
            if (NctiPluginsManager::instance()->IsImportAssemelFile()) {
                // 装配文件
                argumentObject.SetIntValue(2);
            }

            NctiBaseModel* pBaseModel   = pDocument->GetBaseModel();
            NctiCommandManager* pCmdMgr = NctiCommandManager::GetCommandManager(pBaseModel);
            if (pCmdMgr) { pCmdMgr->RunCommand("cmd_ncti_import_file", &argumentObject); }

            // 更新视图
            pBaseModel->GetActiveBaseView()->Zoom();
            pBaseModel->GetActiveBaseView()->Update();
        }
    }
}

void NctiQTPubFun::ExportModelFile(NctiWindowPlatform* i_pPlatform, const QString& i_filePath)
{
    if (!i_pPlatform || i_filePath.isNull()) { return; }
    NctiDocument* pDocument = GetCurrentViewDocment(i_pPlatform);
    if (!pDocument) { return; }

    NctiBaseModel* pBaseModel   = pDocument->GetBaseModel();
    NctiCommandManager* pComMan = NctiCommandManager::GetCommandManager(pBaseModel);
    if (pComMan) {
        NctiArgumentObject argumentObject;
        QByteArray ba = i_filePath.toUtf8();
        argumentObject.SetFilePath(ba.constData());

        std::vector<std::string> objNameVec;
        std::vector<Ncti_Long> cellIds;
        std::vector<NctiTopoCell*> geCellVec;
        NctiDocElementPubFun::GetNameFromSelManager(pDocument, objNameVec, cellIds, geCellVec);
        if (objNameVec.size() > 0) { argumentObject.SetCommandArgumentVec(objNameVec); }
        argumentObject.SetIntValue(-1);
        EnumNctiResult result = pComMan->RunCommand("cmd_ncti_export_file", &argumentObject);
    }
}

void NctiQTPubFun::ExportFile(NctiWindowPlatform* i_pPlatform, const QString& i_filePath)
{
    if (!i_pPlatform || i_filePath.isNull()) { return; }

    NctiDocument* pDocument     = i_pPlatform->GetCurrentViewManager()->GetDocument();
    NctiBaseModel* pBaseModel   = pDocument->GetBaseModel();
    NctiCommandManager* pComMan = NctiCommandManager::GetCommandManager(pBaseModel);
    if (pComMan) {
        NctiArgumentObject argumentObject;
        QByteArray ba = i_filePath.toUtf8();
        argumentObject.SetFilePath(ba.constData());
        std::vector<std::string> objNameVec;
        std::vector<Ncti_Long> cellIds;
        std::vector<NctiTopoCell*> geCellVec;
        NctiDocElementPubFun::GetNameFromSelManager(pDocument, objNameVec, cellIds, geCellVec);
        if (objNameVec.size() > 0) {
            std::vector<std::string> alone;
            alone.push_back(objNameVec[0]);
            argumentObject.SetCommandArgumentVec(alone);
        }
        argumentObject.SetIntValue(-1);
        EnumNctiResult result = pComMan->RunCommand("cmd_ncti_export_file", &argumentObject);
    }
}

// 撤销
void NctiQTPubFun::onUndo(NctiDocument* i_pDocument)
{
    if (i_pDocument && i_pDocument->IsUndoValid()) { i_pDocument->Undo(); }
}

// 重做
void NctiQTPubFun::onRedo(NctiDocument* i_pDocument)
{
    if (i_pDocument && i_pDocument->IsRedoValid()) { i_pDocument->Redo(); }
}

// 删除
void NctiQTPubFun::onDelete(NctiDocument* i_pDocument)
{
    if (!i_pDocument) { return; }

    std::vector<NctiDisplayObject*> objVec;
    NctiBaseModel* pBaseModel = i_pDocument->GetBaseModel();
    NctiDocElementPubFun::GetDisplayObjectFromSelManager(i_pDocument, objVec);
    if (objVec.empty()) { return; }
    NctiCommandManager* pCmdMgr = NctiCommandManager::GetCommandManager(pBaseModel);
    if (pCmdMgr == nullptr) { return; }
    NctiTypeCommandStatus status = pCmdMgr->QuerryCommandStatus(_NctiCommandDeleteSketchObj_ID_);
    if (status & NCTI_COMMAND_STATUS_EXECUTABLE) {
        pCmdMgr->RunCommand(_NctiCommandDeleteSketchObj_ID_);
        return;
    }
    NctiArgumentObject argumentObject;
    argumentObject.SetDisplayObjectVec(objVec);
    pCmdMgr->RunCommand("cmd_ncti_delete", &argumentObject);
}

// 设置视图方向
void NctiQTPubFun::SetView(NctiWindowPlatform* i_pPlatform, EnumNctiViewMode i_viewtype)
{
    auto doc = GetCurrentViewDocment(i_pPlatform);
    if (!doc)
        return;
    auto pMainView = doc->GetBaseModel()->GetActiveBaseView();
    if (pMainView)
        pMainView->SetViewMode(i_viewtype);
}

// 视图最大化/适应屏幕
void NctiQTPubFun::MaxView(NctiWindowPlatform* i_pPlatform)
{
    auto doc = GetCurrentViewDocment(i_pPlatform);
    if (!doc)
        return;
    auto pMainView = doc->GetBaseModel()->GetActiveBaseView();
    if (pMainView)
    { 
        pMainView->Zoom();
        pMainView->Update();
    }
}

// 设置体选择模式
void NctiQTPubFun::SelBody(NctiWindowPlatform* i_pPlatform, Ncti_Boolean bChecked)
{
    NctiDocument* pDocument = GetCurrentViewDocment(i_pPlatform);
    if (pDocument) {
        Ncti_Boolean body, face, line, vertex;
        GetSel(i_pPlatform, body, face, line, vertex);
        if (body != bChecked) {
            NctiDocElementPubFun::SetSelectBody(pDocument, bChecked);
            NctiDocElementPubFun::CancelSelection(pDocument);
        }
    }
}

// 设置面选择模式
void NctiQTPubFun::SelFace(NctiWindowPlatform* i_pPlatform, Ncti_Boolean bChecked)
{
    NctiDocument* pDocument = GetCurrentViewDocment(i_pPlatform);
    if (pDocument) {
        Ncti_Boolean body, face, line, vertex;
        GetSel(i_pPlatform, body, face, line, vertex);
        if (face != bChecked) {
            NctiDocElementPubFun::SetSelectFace(pDocument, bChecked);
            if (body == true) { NctiDocElementPubFun::CancelSelection(pDocument); }
        }
    }
}

// 设置边选择模式
void NctiQTPubFun::SelEdge(NctiWindowPlatform* i_pPlatform, Ncti_Boolean bChecked)
{
    NctiDocument* pDocument = GetCurrentViewDocment(i_pPlatform);
    if (pDocument) {
        Ncti_Boolean body, face, line, vertex;
        GetSel(i_pPlatform, body, face, line, vertex);
        if (line != bChecked) {
            NctiDocElementPubFun::SetSelectLine(pDocument, bChecked);
            if (body == true) { NctiDocElementPubFun::CancelSelection(pDocument); }
        }
    }
}

// 设置顶点选择模式
void NctiQTPubFun::SelVertex(NctiWindowPlatform* i_pPlatform, Ncti_Boolean bChecked)
{
    NctiDocument* pDocument = GetCurrentViewDocment(i_pPlatform);
    if (pDocument) {
        Ncti_Boolean body, face, line, vertex;
        GetSel(i_pPlatform, body, face, line, vertex);
        if (vertex != bChecked) {
            NctiDocElementPubFun::SetSelectMarker(pDocument, bChecked);
            if (body == true) { NctiDocElementPubFun::CancelSelection(pDocument); }
        }
    }
}

// 获取当前选择模式
void NctiQTPubFun::GetSel(NctiWindowPlatform* i_pPlatform,
                          Ncti_Boolean& o_body,
                          Ncti_Boolean& o_face,
                          Ncti_Boolean& o_edge,
                          Ncti_Boolean& o_vertex)
{
    NctiDocument* pDocument = GetCurrentViewDocment(i_pPlatform);
    if (pDocument) { NctiDocElementPubFun::GetSelectMode(pDocument, o_body, o_face, o_edge, o_vertex); }
}

// 设置显示模式
void NctiQTPubFun::SetVisualMode(NctiWindowPlatform* i_pPlatform,
                                 Ncti_Boolean i_face,
                                 Ncti_Boolean i_edge,
                                 Ncti_Boolean i_vertex)
{
    NctiDocument* pDocument = GetCurrentViewDocment(i_pPlatform);
    NctiDocElementPubFun::CancelSelection(pDocument);
    NctiDocElementPubFun::SetVisualMode(pDocument, i_face, i_edge, i_vertex);
}

// 显示所有对象
void NctiQTPubFun::ShowAll(NctiWindowPlatform* i_pPlatform)
{
    NctiDocument* pDocument = GetCurrentViewDocment(i_pPlatform);
    if (pDocument) { NctiDocElementPubFun::SetVisibilityAllShow(pDocument); }
}

// 隐藏选中对象
void NctiQTPubFun::HideSel(NctiWindowPlatform* i_pPlatform)
{
    NctiDocument* pDocument = GetCurrentViewDocment(i_pPlatform);
    if (pDocument) { NctiDocElementPubFun::SetVisibilityBySel(pDocument, false); }
}

// 仅显示选中对象
void NctiQTPubFun::OnlySelShow(NctiWindowPlatform* i_pPlatform)
{
    NctiDocument* pDocument = GetCurrentViewDocment(i_pPlatform);
    if (pDocument) { NctiDocElementPubFun::SetVisibilityOnlyShowBySel(pDocument); }
}

// 显示帮助文档
void NctiQTPubFun::HelpDoc()
{
    char* cworkingPath                 = new char[NCTI_SIZE_FILE_PATH];
    NctiPluginsManager* pPluginManager = NctiPluginsManager::instance();
    pPluginManager->getCurrentWorkingPath(cworkingPath);
    QString workingPath = QString::fromLocal8Bit(cworkingPath);

    QString path = workingPath + QString::fromLocal8Bit("/readme.txt");
    QDesktopServices::openUrl(QUrl(QUrl::fromLocalFile(path)));
}

// 刷新视图
void NctiQTPubFun::RefreshViews(NctiWindowPlatform* i_pPlatform)
{
    NctiDocument* pDocument = GetCurrentViewDocment(i_pPlatform);
    if (pDocument) { pDocument->GetBaseModel()->RefreshViews(); }
}

void NctiQTPubFun::SearchLoopFace(NctiWindowPlatform* i_pPlatform)
{
    NctiDocument* pDocument = NctiQTPubFun::GetCurrentViewDocment(i_pPlatform);
    if (!pDocument) { return; }

    std::vector<NctiDisplayObject*> ObjVec;
    std::vector<NCTI_MODEL_TAG> CellVec;
    std::unordered_map<std::string, std::vector<Ncti_Long>> ObjNameCellIDMap;
    NctiDocElementPubFun::GetDisplayObjectFromSelManager(pDocument, ObjVec, CellVec);
    NctiDocElementPubFun::SearchLoopFace(pDocument, ObjVec, CellVec, ObjNameCellIDMap);
    if (ObjNameCellIDMap.size() > 0) {
        NctiSelectionManager* pSelMan = NctiSelectionManager::GetSelectionManager(pDocument->GetBaseModel());
        pSelMan->ResetSelection();
        NctiDocElementPubFun::SetSelectionByNameAndCellID(pDocument, ObjNameCellIDMap);
    }
}

void NctiQTPubFun::SearchConnectFace(NctiWindowPlatform* i_pPlatform)
{
    NctiDocument* pDocument = NctiQTPubFun::GetCurrentViewDocment(i_pPlatform);
    if (!pDocument) { return; }

    std::vector<NctiDisplayObject*> ObjVec;
    std::vector<NCTI_MODEL_TAG> CellVec;
    std::unordered_map<std::string, std::vector<Ncti_Long>> ObjNameCellIDMap;
    NctiDocElementPubFun::GetDisplayObjectFromSelManager(pDocument, ObjVec, CellVec);
    NctiDocElementPubFun::SearchConnectFace(pDocument, ObjVec, CellVec, ObjNameCellIDMap);
    if (ObjNameCellIDMap.size() > 0) {
        NctiSelectionManager* pSelMan = NctiSelectionManager::GetSelectionManager(pDocument->GetBaseModel());
        pSelMan->ResetSelection();
        NctiDocElementPubFun::SetSelectionByNameAndCellID(pDocument, ObjNameCellIDMap);
    }
}

void NctiQTPubFun::SearchSameConnectFace(NctiWindowPlatform* i_pPlatform)
{
    NctiDocument* pDocument = NctiQTPubFun::GetCurrentViewDocment(i_pPlatform);
    if (pDocument) { NctiDocElementPubFun::SearchSameConnectFace(i_pPlatform->GetCurrentViewManager()->GetDocument()); }
}

void NctiQTPubFun::SearchNoPlaneConnectFace(NctiWindowPlatform* i_pPlatform)
{
    NctiDocument* pDocument = NctiQTPubFun::GetCurrentViewDocment(i_pPlatform);
    if (!pDocument) { return; }

    std::vector<NctiDisplayObject*> ObjVec;
    std::vector<NCTI_MODEL_TAG> CellVec;
    std::unordered_map<std::string, std::vector<Ncti_Long>> ObjNameCellIDMap;
    NctiDocElementPubFun::GetDisplayObjectFromSelManager(pDocument, ObjVec, CellVec);
    NctiDocElementPubFun::SearchNoPlaneConnectFace(pDocument, ObjVec, CellVec, ObjNameCellIDMap);
    if (ObjNameCellIDMap.size() > 0) {
        NctiSelectionManager* pSelMan = NctiSelectionManager::GetSelectionManager(pDocument->GetBaseModel());
        pSelMan->ResetSelection();
        NctiDocElementPubFun::SetSelectionByNameAndCellID(pDocument, ObjNameCellIDMap);
    }
}

void NctiQTPubFun::ExportLinkFace(NctiWindowPlatform* i_pPlatform, const QString& i_filePath)
{
    if (i_filePath.length() < 1) return;
    NctiDocument* pDocument = i_pPlatform->GetCurrentViewManager()->GetDocument();
    std::vector<NctiDisplayObject*> ObjVec;
    std::vector<std::vector<NCTI_MODEL_TAG>> CellVecVec;
    NctiDocElementPubFun::GetDisplayObjectFromSelManager(pDocument, ObjVec, CellVecVec);
    int iFaceNum = 0;
    for (size_t i = 0; i < CellVecVec.size(); i++) {
        iFaceNum += CellVecVec[i].size();
    }
    if (ObjVec.size() != 1 || iFaceNum < 1 || ObjVec.size() != CellVecVec.size()) return;
    if (!ObjVec[0]->IsTypeName(NctiDisplayModelBody::ID)) return;
    NctiSelectionManager* pSelMan = NctiSelectionManager::GetSelectionManager(pDocument->GetBaseModel());
    pSelMan->ResetSelection();

    bool bMultiple = iFaceNum > 1 ? true : false;
    std::unordered_map<std::string, std::vector<Ncti_Long>> ObjNameCellIDMap;
    int iFile = 0;
    for (size_t j = 0; j < ObjVec.size(); j++) {
        NctiDisplayModelBody* pModelBody       = (NctiDisplayModelBody*)ObjVec[j];
        NctiDisplayDocCustomContainer* pDocCus = (NctiDisplayDocCustomContainer*)pModelBody->GetDocContainer();
        for (size_t i = 0; i < CellVecVec[j].size(); i++) {
            NCTI_MODEL_TAG geCell = nullptr;
            pDocCus->get_gecell(pModelBody->GetNctiBody(), CellVecVec[j][i], geCell);
            NctiTopoCell* pTopoCell = (NctiTopoCell*)geCell;
            std::vector<NCTI_MODEL_TAG> FaceCellVec;
            NctiDocElementPubFun::FindAllLoopFromFace(pDocument->GetBaseModel(), pTopoCell, true, FaceCellVec);

            std::vector<NCTI_MODEL_TAG> sewingBodies;
            for (Ncti_Size i = 0; i < FaceCellVec.size(); i++) {
                //create
                NCTI_MODEL_TAG pNewModelBody           = nullptr;
                NctiGeometryResult ModelFunctionResult = NctiGeometryFunction::extract_cell(
                    pDocCus, pModelBody->GetNctiBody(), FaceCellVec[i], pNewModelBody); //make_face_by_surface
                if (ModelFunctionResult.GetResult() == true && pNewModelBody != nullptr) {
                    sewingBodies.push_back(pNewModelBody);
                }
                //set select
                Ncti_Long id;
                pDocCus->get_persistent_tag(pModelBody, FaceCellVec[i], id);
                ObjNameCellIDMap[pModelBody->GetObjName()].push_back(id);
            }
            //Sewing
            if (sewingBodies.size() > 0) {
                NCTI_MODEL_TAG pSewingModelBody = nullptr;
                Ncti_Sewing_Params i_Params;
                NctiGeometryResult ModelFunctionResult
                    = NctiGeometryFunction::sewing_bodies(pDocCus, sewingBodies, 0.1f, i_Params, pSewingModelBody);
                for (size_t i = 0; i < sewingBodies.size(); i++) {
                    pDocCus->delete_body(sewingBodies[i]);
                }
                if (ModelFunctionResult.GetResult() == false) { return; }
                //export
                QString strFile = i_filePath;
                if (bMultiple) {
                    QString str = strFile.left(strFile.length() - 4);
                    strFile     = QString("%1_%2.stp").arg(str).arg(iFile + 1);
                    iFile++;
                }
                if (QFile::exists(strFile)) QFile::remove(strFile);
                QByteArray ba = strFile.toUtf8();
                std::vector<NCTI_MODEL_TAG> BodyVec;
                BodyVec.push_back(pSewingModelBody);
                NctiGeometryFunction::export_file(pDocCus, ba.data(), BodyVec);
                //clear
                if (pSewingModelBody != nullptr) pDocCus->delete_body(pSewingModelBody);
            }
        }
    }
}

void NctiQTPubFun::FeatureRecognition(NctiWindowPlatform* i_pPlatform)
{
    std::vector<std::string> o_ObjNameVec;
    std::vector<Ncti_Long> o_CellIDVec;
    std::vector<NctiTopoCell*> o_GECellVec;
    NctiDocElementPubFun::GetNameFromSelManager(
        i_pPlatform->GetCurrentViewManager()->GetDocument(), o_ObjNameVec, o_CellIDVec, o_GECellVec);
    if (o_ObjNameVec.size() == 1) {
        NctiPluginsManager* pPluginsManager = NctiPluginsManager::instance();
        char chDll[4096];
        char aiModule[4096];
        const char* chWorkingPath = pPluginsManager->GetTempFullPath();
        NctiString::LocaleSprintf(aiModule, "%s/AI/AAGNet_package_AI4CAD", chWorkingPath);
        NctiString::LocaleSprintf(chDll, "sys.path.insert(0, \"%s\")", aiModule);
        std::string chdll_str(chDll);
        size_t pos = 0;
        while ((pos = chdll_str.find("\\", pos)) != std::string::npos) {
            chdll_str.replace(pos, 1, "/");
            pos += 1; // Handles the case where 'to' is replaced with '//'
        }
        NctiPyCB.RunSimpleString(chdll_str.c_str());

        char chpy[2048];
        NctiPyCB.RunSimpleString("from base_utils import AGGNetInference");
        NctiString::LocaleSprintf(chpy, "ai = NCTI.AiModel(doc, \"%s\")", o_ObjNameVec[0].c_str());
        NctiPyCB.RunSimpleString(chpy);
        NctiPyCB.RunSimpleString("FaceID = ai.FaceID");
        NctiPyCB.RunSimpleString("FaceFID = ai.FaceFID");
        NctiPyCB.RunSimpleString("FaceEID = ai.FaceEID");
        NctiPyCB.RunSimpleString("graph_face_attr = ai.FaceAttr");
        NctiPyCB.RunSimpleString("FacePoints = ai.FacePoints");
        NctiPyCB.RunSimpleString("FaceNormals = ai.FaceNormals");
        NctiPyCB.RunSimpleString("FaceMask = ai.FaceMask");
        NctiPyCB.RunSimpleString("graph_edge_attr = ai.EdgeAttr");

        NctiPyCB.RunSimpleString("AAGNet = AGGNetInference()");
        NctiPyCB.RunSimpleString("face_logits, inst_out, bottom_out = "
                           "AAGNet.AI_model_inference(FaceID,FaceFID,FaceEID,FacePoints,FaceNormals,FaceMask,graph_"
                           "edge_attr,graph_face_attr) ");
        NctiPyCB.RunSimpleString("result_dict = AAGNet.postprocess(face_logits, inst_out, bottom_out,graph_face_attr)");
        NctiPyCB.RunSimpleString("ai.ImportAiResult(result_dict)");

        QMessageBox::information(nullptr, "AI", "AI识别完成。");
    }
}

void NctiQTPubFun::StretchRecognition(NctiWindowPlatform* i_pPlatform, QTextEdit* i_pCommandEdit)
{
    std::vector<NctiDisplayObject*> mdisplayobj;
    std::vector<std::vector<NCTI_MODEL_TAG>> mcells;
    NctiDocument* i_pDocument = i_pPlatform->GetCurrentViewManager()->GetDocument();
    NctiDocElementPubFun::GetDisplayObjectFromSelManager(i_pDocument, mdisplayobj, mcells);
    if (mdisplayobj.size() != 1 || mcells.size() != 1) { return; }

    NctiBaseModel* pBaseModel = i_pDocument->GetBaseModel();
    if (pBaseModel == nullptr) return;

    NctiCommandManager* pComMan = NctiCommandManager::GetCommandManager(pBaseModel);
    if (pComMan == nullptr) return;

    NctiDisplayObject* pObjj = mdisplayobj[0];
    std::vector<NctiDisplayObject*> extrtDisplayobj;
    NctiDisplayModelBody* pModelBody       = (NctiDisplayModelBody*)pObjj;
    NctiDisplayDocCustomContainer* pDocCus = (NctiDisplayDocCustomContainer*)pObjj->GetDocContainer();
    for (int c = 0; c < mcells[0].size(); c++) {
        Ncti_Long CellID = -1;
        NctiArgumentObject splitFaceArg;
        splitFaceArg.SetDisplayObjectVec({pObjj});
        pDocCus->get_persistent_tag(pModelBody, mcells[0][c], CellID);

        splitFaceArg.SetCellIDVec({CellID});
        pComMan->RunCommand("cmd_ncti_extract_cell", &splitFaceArg);
        auto& retObjVec = splitFaceArg.GetDisplayObjectVec();
        std::copy(retObjVec.begin(), retObjVec.end(), std::back_inserter(extrtDisplayobj));
    }

    // 构建组合体
    char newObjName[256];
    static Ncti_Integer sIdx = 0;
    NctiString::LocaleSprintf(newObjName, "COMP_BODY_%d", sIdx++);
    NctiArgumentObject deletOrigArg, buildBodyArg;
    buildBodyArg.SetDesignResultVec({newObjName});
    buildBodyArg.SetDisplayObjectVec(extrtDisplayobj);
    pComMan->RunCommand("cmd_ncti_create_compound", &buildBodyArg);
    deletOrigArg.SetDisplayObjectVec(extrtDisplayobj);
    pComMan->RunCommand("cmd_ncti_delete", &deletOrigArg);

    // AI推理获取相关Id
    char chDll[4096];
    char aiModule[4096];
    NctiPluginsManager* pPluginsManager = NctiPluginsManager::instance();
    const char* chWorkingPath           = pPluginsManager->GetTempFullPath();
    NctiString::LocaleSprintf(aiModule, "%s/AI/AAGNet_package_AI4CAD", chWorkingPath);
    NctiString::LocaleSprintf(chDll, "sys.path.insert(0, \"%s\")", aiModule);
    std::string chdll_str(chDll);
    size_t pos = 0;
    while ((pos = chdll_str.find("\\", pos)) != std::string::npos) {
        chdll_str.replace(pos, 1, "/");
        pos += 1; // Handles the case where 'to' is replaced with '//'
    }

    char chpy[2048];
    NctiPyCB.RunSimpleString(chdll_str.c_str());
    NctiPyCB.RunSimpleString("from base_utils import AGGNetInference");
    NctiString::LocaleSprintf(chpy, "ai = NCTI.AiFunction(doc, \"%s\")", newObjName);
    NctiPyCB.RunSimpleString(chpy);
    NctiPyCB.RunSimpleString("FaceID = ai.GetFaceID()");
    NctiPyCB.RunSimpleString("FaceFID = ai.GetFaceFID()");
    NctiPyCB.RunSimpleString("FaceEID = ai.GetFaceEID()");
    NctiPyCB.RunSimpleString("FacePoints = ai.GetFacePoints()");
    NctiPyCB.RunSimpleString("FaceNormals = ai.GetFaceNormals()");
    NctiPyCB.RunSimpleString("FaceMask = ai.GetFaceMask()");
    NctiPyCB.RunSimpleString("graph_edge_attr = ai.GetEdgeAttr()");
    NctiPyCB.RunSimpleString("graph_face_attr = ai.GetFaceAttr()");
    NctiPyCB.RunSimpleString("AAGNet = AGGNetInference()");
    NctiPyCB.RunSimpleString("seg_pred = "
                       "AAGNet.aag_face_inference(FaceID,FaceFID,FaceEID,FacePoints,FaceNormals,FaceMask,graph_edge_"
                       "attr,graph_face_attr) ");
    NctiPyCB.RunSimpleString("result_dict = AAGNet.postprocess_face(seg_pred)");
    NctiPyCB.RunSimpleString("print(result_dict)");

    char ch[1024];
    NctiString::LocaleSprintf(ch, "aiFunc = NCTI.AiFunction(doc, \"%s\")", pObjj->GetObjName());
    NctiPyCB.RunSimpleString(ch);
    NctiPyCB.RunSimpleString("newObjName = ai.objName");
    NctiPyCB.RunSimpleString("print(newObjName)");
    NctiPyCB.RunSimpleString("aiFunc.GetPrismFaceAttr(result_dict, newObjName)");
    QMessageBox::information(nullptr, "AI", "拉伸识别完成。");
}

std::vector<Ncti_Long> NctiQTPubFun::GetCommonEdge(NctiDisplayObject* pObj, Ncti_Long CellID)
{
    std::vector<Ncti_Long> vetTopoEdges;
    NctiDisplayModelBody* pModelBody       = (NctiDisplayModelBody*)pObj;
    NctiDisplayDocCustomContainer* pDocCus = (NctiDisplayDocCustomContainer*)pModelBody->GetDocContainer();
    NCTI_MODEL_TAG pCell                   = nullptr;
    pDocCus->get_void_from_tag(pModelBody, pCell, CellID);

    NCTI_MODEL_TAG geCell = nullptr;
    pDocCus->get_gecell(pModelBody->GetNctiBody(), pCell, geCell);
    NctiTopoCell* pTopoCell = (NctiTopoCell*)geCell;

    if (pTopoCell == nullptr || !pTopoCell->IsTypeName(NctiTopoFace::ID)) { return vetTopoEdges; }

    NctiTopoFace* pTopoFace                = (NctiTopoFace*)pTopoCell;
    std::vector<NctiTopoLoop*> TopoLoopVec = pTopoFace->Get_m_TopoLoopVec();
    for (Ncti_Size i = 0; i < TopoLoopVec.size(); i++) {
        if (TopoLoopVec[i]->Get_m_Orientation() == Ncti_EXTERNAL) {
            std::vector<NctiTopoEdge*> TopoEdgeVec = TopoLoopVec[i]->Get_m_TopoEdgeVec();
            for (int j = 0; j < TopoEdgeVec.size(); j++) {
                Ncti_Long cellId    = -1;
                NCTI_MODEL_TAG edge = TopoEdgeVec[j]->GetLinkVoid();
                pDocCus->get_persistent_tag(pModelBody, edge, cellId);
                vetTopoEdges.push_back(cellId);
            }
        }
    }
    return vetTopoEdges;
}

void NctiQTPubFun::AIHoleRecognition(NctiWindowPlatform* i_pPlatform)
{
    std::vector<NctiDisplayObject*> objVec;
    NctiDocument* i_pDocument = i_pPlatform->GetCurrentViewManager()->GetDocument();
    NctiDocElementPubFun::GetDisplayObjectFromSelManager(i_pDocument, objVec);
    if (objVec.empty()) { return; }

    // AI推理获取相关Id
    char chDll[4096];
    char aiModule[4096];
    NctiPluginsManager* pPluginsManager = NctiPluginsManager::instance();
    const char* chWorkingPath           = pPluginsManager->GetTempFullPath();
    NctiString::LocaleSprintf(aiModule, "%s/AI/AAGNet_package_AI4CAD", chWorkingPath);
    NctiString::LocaleSprintf(chDll, "sys.path.insert(0, \"%s\")", aiModule);
    std::string chdll_str(chDll);
    size_t pos = 0;
    while ((pos = chdll_str.find("\\", pos)) != std::string::npos) {
        chdll_str.replace(pos, 1, "/");
        pos += 1; // Handles the case where 'to' is replaced with '//'
    }

    auto name = objVec[0]->GetObjName();

    char chpy[2048];
    NctiPyCB.RunSimpleString(chdll_str.c_str());
    NctiPyCB.RunSimpleString("from base_utils import AGGNetInference");

    NctiString::LocaleSprintf(chpy, "aiFunc = NCTI.AiFunction(doc, \"%s\")", name);
    NctiPyCB.RunSimpleString(chpy);
    NctiPyCB.RunSimpleString("PPFaceID = aiFunc.GetFaceID()");
    NctiPyCB.RunSimpleString("PPFaceFID = aiFunc.GetFaceFID()");
    NctiPyCB.RunSimpleString("PPFaceEID = aiFunc.GetFaceEID()");
    NctiPyCB.RunSimpleString("PPFacePoints = aiFunc.GetFacePoints()");
    NctiPyCB.RunSimpleString("PPFaceNormals = aiFunc.GetFaceNormals()");
    NctiPyCB.RunSimpleString("PPFaceMask = aiFunc.GetFaceMask()");
    NctiPyCB.RunSimpleString("PPgraph_edge_attr = aiFunc.GetEdgeAttr()");
    NctiPyCB.RunSimpleString("PPgraph_face_attr = aiFunc.GetFaceAttr()");
    NctiPyCB.RunSimpleString("AAGNet = AGGNetInference()");
    NctiPyCB.RunSimpleString("pp_seg_pred = "
                       "AAGNet.aag_hole_inference(PPFaceID,PPFaceFID,PPFaceEID,PPFacePoints,PPFaceNormals,PPFaceMask,"
                       "PPgraph_edge_attr,PPgraph_face_attr) ");
    NctiPyCB.RunSimpleString("hole_result_dict = AAGNet.postprocess_hole(pp_seg_pred)");
    NctiPyCB.RunSimpleString("print(hole_result_dict)");
    NctiPyCB.RunSimpleString("print(aiFunc.GetHoleFaceAttr(hole_result_dict))");
    QMessageBox::information(nullptr, "AI", "孔识别完成。");

    StretFaceAttributes facesAttrbutes;
    NctiAIGeoAttributeParser::GetStretFaceAttributes(name, facesAttrbutes);
    std::unordered_map<std::string, std::vector<Ncti_Long>> ObjNameCellIDMap;

    for (Ncti_Size i = 0; i < facesAttrbutes.hole_faces.size(); ++i) {
        ObjNameCellIDMap[name].push_back(facesAttrbutes.hole_faces[i]);
    }

    if (ObjNameCellIDMap.size() > 0) {
        NctiSelectionManager* pSelMan = NctiSelectionManager::GetSelectionManager(i_pDocument->GetBaseModel());
        pSelMan->ResetSelection();
        NctiDocElementPubFun::SetSelectionByNameAndCellID(i_pDocument, ObjNameCellIDMap);
    }
}

void NctiQTPubFun::OutputReversal(NctiWindowPlatform* i_pPlatform, QTextEdit* i_pCommandEdit)
{
    NctiDocument* i_pDocument = i_pPlatform->GetCurrentViewManager()->GetDocument();
    NctiBaseModel* pBaseModel = i_pDocument->GetBaseModel();
    if (pBaseModel == nullptr) return;

    NctiCommandManager* pComMan = NctiCommandManager::GetCommandManager(pBaseModel);
    if (pComMan == nullptr) return;

    auto objName                = NctiAIGeoAttributeParser::GetParserCurretObjName();
    const Ncti_Char* newObjName = objName.first.c_str();
    std::string oldObjName      = objName.second;

    StretFaceAttributes facesAttrbutes;
    NctiAIGeoAttributeParser::GetStretFaceAttributes(oldObjName, facesAttrbutes);
    if (1 != facesAttrbutes.bottom_faces.size() || facesAttrbutes.other_faces.size() < 1) {
        std::string errinfo = "The AI inference result is incorrect!";
        NctiPyCB.RaiseAndPrintPyError(errinfo.c_str());
        //PyErr_SetString(PyExc_ValueError, errinfo.c_str());
        //PyErr_Print();
        return;
    }

    double dMaxLength      = 0.0;                            // 最大边长值
    Ncti_Long logstEdgeId  = -1;                             // 拉伸边Id（与底面有连接、最长）
    Ncti_Long bottomFaceId = facesAttrbutes.bottom_faces[0]; //底面Id
    if (!(objName.first.empty())) {
        std::vector<std::vector<Ncti_Long>> vetAdjoinFace = facesAttrbutes.other_faces;

        NctiDisplayObject* pObj = nullptr;
        NctiDocElementPubFun::GetObjectListByName(pBaseModel, newObjName, pObj);
        if (pObj == nullptr) return;

        NctiDisplayModelBody* pNewModelBody       = (NctiDisplayModelBody*)pObj;
        NctiDisplayDocCustomContainer* pNewDocCus = (NctiDisplayDocCustomContainer*)pNewModelBody->GetDocContainer();
        NCTI_MODEL_TAG pBottFaceCell              = nullptr;
        pNewDocCus->get_void_from_tag(pNewModelBody, pBottFaceCell, bottomFaceId);

        NCTI_MODEL_TAG geFaceCell = nullptr;
        pNewDocCus->get_gecell(pNewModelBody->GetNctiBody(), pBottFaceCell, geFaceCell);
        NctiTopoCell* pTTopoCell = static_cast<NctiTopoCell*>(geFaceCell);
        NctiTransf transf        = pTTopoCell->Get_m_Tranf();

        NctiTopoFace* pNctiTopoFace                   = static_cast<NctiTopoFace*>(pTTopoCell);
        NctiGeomSurface* pSurface1                    = pNctiTopoFace->Get_m_GeomSurface();
        NctiGeomElementarySurface* pElementarySurface = static_cast<NctiGeomElementarySurface*>(pSurface1);
        NctiPosition posPlane_                        = pElementarySurface->Get_m_pt();
        NctiUnitVector xDir                           = pElementarySurface->Get_m_XDir();
        NctiUnitVector yDir                           = pElementarySurface->Get_m_YDir();
        for (Ncti_Size i = 0; i < vetAdjoinFace.size(); ++i) {
            if (vetAdjoinFace[i].size() != 2) { continue; }

            std::vector<Ncti_Long> vetEdgeData1 = NctiQTPubFun::GetCommonEdge(pObj, vetAdjoinFace[i][0]);
            std::vector<Ncti_Long> vetEdgeData2 = NctiQTPubFun::GetCommonEdge(pObj, vetAdjoinFace[i][1]);
            for (Ncti_Size j = 0; j < vetEdgeData1.size(); ++j) {
                auto it = std::find(vetEdgeData2.begin(), vetEdgeData2.end(), vetEdgeData1[j]); // 查找共边
                if (it != vetEdgeData2.end()) {
                    NctiPosition o_ptS;
                    NctiPosition o_ptE;
                    NctiVector o_vecS;
                    NctiVector o_vecE;
                    if (NctiDocElementPubFun::GetEndPointsFromEdge(
                            i_pDocument, newObjName, vetEdgeData1[j], o_ptS, o_ptE, o_vecS, o_vecE)) // 获取边的两个端点
                    {
                        // 判断边是否和底面有连接
                        Ncti_Double dFirDis = distance_to_plane(
                            o_ptS, posPlane_ * transf, normalise((xDir * transf) * (yDir * transf)));
                        Ncti_Double dSedDis = distance_to_plane(
                            o_ptE, posPlane_ * transf, normalise((xDir * transf) * (yDir * transf)));
                        if (dFirDis >= 1e-6 && dSedDis >= 1e-6) { continue; }

                        std::function<bool(NctiTopoEdge*, NctiGeomCurve*, double&)> GetLengthOfLineEdge
                            = [&](NctiTopoEdge* pEdge, NctiGeomCurve* geomCurve, double& dLen) {
                                  if (pEdge == nullptr || geomCurve == nullptr) return false;
                                  NctiCreateModelScriptPub::GetGeomFromTrimmedCurve(geomCurve);
                                  if (geomCurve->IsTypeName(NctiGeomLine::ID)) {
                                      NctiPosition ptF, ptL;
                                      pEdge->FirstPt(ptF);
                                      pEdge->LastPt(ptL);
                                      NctiVector vec = ptF - ptL;
                                      dLen           = vec.len();
                                      return true;
                                  }
                                  else if (geomCurve->IsTypeName(NctiGeomBSplineCurve::ID)) {
                                      NctiPosition ptF, ptL;
                                      pEdge->FirstPt(ptF);
                                      pEdge->LastPt(ptL);
                                      NctiVector vec = ptF - ptL;
                                      dLen           = vec.len();
                                      return true;
                                  }
                                  else
                                      return false;
                              };

                        // 获取最长的与底面有连接的边的ID
                        NCTI_MODEL_TAG pCell = nullptr;
                        pNewDocCus->get_void_from_tag(pNewModelBody, pCell, vetEdgeData1[j]);

                        NCTI_MODEL_TAG geCell = nullptr;
                        pNewDocCus->get_gecell(pNewModelBody->GetNctiBody(), pCell, geCell);
                        NctiTopoCell* pTopoCell = (NctiTopoCell*)geCell;
                        NctiTopoEdge* pEdgeCell = (NctiTopoEdge*)pTopoCell;

                        double dLen              = 0.0;
                        NctiGeomCurve* geomCurve = pEdgeCell->Get_m_GeomCurve();
                        if (GetLengthOfLineEdge(pEdgeCell, geomCurve, dLen) && dLen > dMaxLength) {
                            dMaxLength  = dLen;
                            logstEdgeId = vetEdgeData1[j];
                        }
                    }
                }
            }
        }
    }

    std::vector<std::string> strCmdVec;
    std::vector<std::string> strNameVec = {2, newObjName};
    std::vector<Ncti_Long> edgeIDVec    = {bottomFaceId, logstEdgeId};
    if (!NctiCreateModelScriptPub::CreateCurveWirePrimScript(pBaseModel, true, strNameVec, edgeIDVec, strCmdVec))
        return;

    // 删除组装body
    NctiArgumentObject deletLastArg;
    NctiDisplayObject* lastDisObj = nullptr;
    NctiDocElementPubFun::GetObjectListByName(pBaseModel, newObjName, lastDisObj);
    deletLastArg.SetDisplayObjectVec({lastDisObj});
    pComMan->RunCommand("cmd_ncti_delete", &deletLastArg);

    std::string strCmd, strPrismName;
    for (int i = 0; i < strCmdVec.size(); i++) {
        strCmd += strCmdVec[i];
        strCmd += "\n";
    }

    if (facesAttrbutes.hole_faces.size() > 0) {
        std::string strCylinderCmd, strCylinderName;
        size_t nNum                               = facesAttrbutes.hole_faces.size();
        std::string strOrigObjName                = oldObjName;
        std::vector<std::string> strOriginNameVec = {nNum, strOrigObjName};
        NctiCreateModelScriptPub::CreateCylinderScript(
            pBaseModel, strOriginNameVec, facesAttrbutes.hole_faces, strCylinderCmd, strCylinderName);

        size_t ppos = 0;
        int j       = strCmdVec.size() - 2;
        if ((ppos = strCmdVec[j].find("cmd_ncti_prism", ppos)) != std::string::npos) {
            std::vector<std::string> ResultVec = NctiString::stringSplit(strCmdVec[j], ',');
            if (ResultVec.size() > 1) { strPrismName = ResultVec[1]; }
        }

        strCmd += "\n";
        strCmd += strCylinderCmd;

        Ncti_Char cCut[10240];
        Ncti_Char cDel[10240];
        strCylinderName = NctiString::mid(strCylinderName, 0, strCylinderName.size() - 2);
        NctiString::LocaleSprintf(cCut,
                                  "doc.RunCommand(\"cmd_ncti_multi_boolean_cut\", \"result\", [%s], [%s])\n",
                                  strPrismName,
                                  strCylinderName.c_str());
        NctiString::LocaleSprintf(
            cDel, "doc.RunCommand(\"cmd_ncti_delete\", [%s,%s])\n\n", strPrismName, strCylinderName.c_str());
        strCmd += cCut;
        strCmd += cDel;
    }

    i_pCommandEdit->append(strCmd.c_str());
}

static void BaseRecognization(NctiDocument* i_pDocument, const std::string& recognitionName, const std::string& postName) 
{
    std::vector<std::string> o_ObjNameVec;
    std::vector<Ncti_Long> o_CellIDVec;
    std::vector<NctiTopoCell*> o_GECellVec;
    NctiDocElementPubFun::GetNameFromSelManager(i_pDocument, o_ObjNameVec, o_CellIDVec, o_GECellVec);
    if (o_ObjNameVec.size() == 1) {
        NctiPluginsManager* pPluginsManager = NctiPluginsManager::instance();
        char chDll[4096];
        char aiModule[4096];
        const char* chWorkingPath = pPluginsManager->GetTempFullPath();
        NctiString::LocaleSprintf(aiModule, "%s/AI/AAGNet_package_round", chWorkingPath);
        NctiString::LocaleSprintf(chDll, "sys.path.insert(0, \"%s\")", aiModule);
        std::string chdll_str(chDll);
        size_t pos = 0;
        while ((pos = chdll_str.find("\\", pos)) != std::string::npos) {
            chdll_str.replace(pos, 1, "/");
            pos += 1;
        }
        NctiPyCB.RunSimpleString(chdll_str.c_str());

        NctiPyCB.RunSimpleString("from base_utils import AGGNetInference");

        char ch[2048];
        NctiString::LocaleSprintf(ch, "weight_path = r\"%s\"", recognitionName.c_str());
        NctiPyCB.RunSimpleString(ch);
        //NctiPyCB.RunSimpleString("weight_path = r\"weight_round.pth\"");
        NctiPyCB.RunSimpleString("stat_path = r\"attr_stat_ncti_62k.json\"");
        NctiPyCB.RunSimpleString("aag_net = AAGNet = AGGNetInference(weight_path,stat_path)");
        NctiPyCB.RunSimpleString("doc.SetCreateGeGeom(1)");
        NctiPyCB.RunSimpleString("doc.ResetCaseResult()");
        char chpy[2048];
        NctiString::LocaleSprintf(chpy, "ai = NCTI.AiModel(doc, \"%s\")", o_ObjNameVec[0].c_str());
        NctiPyCB.RunSimpleString(chpy);
        NctiPyCB.RunSimpleString("face_id = ai.FaceID");
        NctiPyCB.RunSimpleString("face_f_id = ai.FaceFID");
        NctiPyCB.RunSimpleString("face_e_id = ai.FaceEID");
        NctiPyCB.RunSimpleString("face_points = ai.FacePoints");
        NctiPyCB.RunSimpleString("face_normals = ai.FaceNormals");
        NctiPyCB.RunSimpleString("face_mask = ai.FaceMask");
        NctiPyCB.RunSimpleString("original_graph_edge_attr = ai.EdgeAttr");
        NctiPyCB.RunSimpleString("graph_face_attr = ai.FaceAttr");
        NctiPyCB.RunSimpleString("graph_edge_attr = [sublist[:10] for sublist in original_graph_edge_attr]");

        NctiPyCB.RunSimpleString("seg_out, inst_out, bottom_out = aag_net.AI_model_inference(face_id, face_f_id, face_e_id, face_points,"
            "face_normals, face_mask, graph_edge_attr,"
            "graph_face_attr)");

        //char ch[2048];
        NctiString::LocaleSprintf(ch, "result_dict = aag_net.postprocess_round(seg_out, inst_out, bottom_out, \"%s\")", postName.c_str());
        NctiPyCB.RunSimpleString(ch);
        //NctiPyCB.RunSimpleString("result_dict = aag_net.postprocess_round(seg_out, inst_out, bottom_out)");
        NctiPyCB.RunSimpleString("ai.ImportAiResult(result_dict)");
    }
}

void NctiQTPubFun::RoundRecognition(NctiDocument* i_pDocument)
{
    BaseRecognization(i_pDocument, "weight_round.pth", "round");
}

void NctiQTPubFun::ChamferRecognition(NctiDocument* i_pDocument)
{
    BaseRecognization(i_pDocument, "weight_chamfer.pth", "chamfer");
}

void NctiQTPubFun::ThroughHoleRecognition(NctiDocument* i_pDocument)
{
    BaseRecognization(i_pDocument, "weight_through_hole.pth", "through hole");
}

void NctiQTPubFun::HoleRecognition(NctiWindowPlatform* i_pPlatform)
{
    std::vector<std::string> o_ObjNameVec;
    std::vector<Ncti_Long> o_CellIDVec;
    std::vector<NctiTopoCell*> o_GECellVec;
    NctiDocElementPubFun::GetNameFromSelManager(
        i_pPlatform->GetCurrentViewManager()->GetDocument(), o_ObjNameVec, o_CellIDVec, o_GECellVec);
    if (o_ObjNameVec.size() == 1) {
        NctiPluginsManager* pPluginsManager = NctiPluginsManager::instance();
        char chDll[4096];
        char aiModule[4096];
        const char* chWorkingPath = pPluginsManager->GetTempFullPath();
        NctiString::LocaleSprintf(aiModule, "%s/AI/AAGNet_package_hole", chWorkingPath);
        NctiString::LocaleSprintf(chDll, "sys.path.insert(0, \"%s\")", aiModule);
        std::string chdll_str(chDll);
        size_t pos = 0;
        while ((pos = chdll_str.find("\\", pos)) != std::string::npos) {
            chdll_str.replace(pos, 1, "/");
            pos += 1;
        }
        NctiPyCB.RunSimpleString(chdll_str.c_str());

        char chpy[2048];
        NctiPyCB.RunSimpleString("from base_utils import AGGNetInference");
        NctiString::LocaleSprintf(chpy, "ai = NCTI.AiModel(doc, \"%s\")", o_ObjNameVec[0].c_str());
        NctiPyCB.RunSimpleString(chpy);
        NctiPyCB.RunSimpleString("FaceID = ai.FaceID");
        NctiPyCB.RunSimpleString("FaceFID = ai.FaceFID");
        NctiPyCB.RunSimpleString("FaceEID = ai.FaceEID");
        NctiPyCB.RunSimpleString("graph_face_attr = ai.FaceAttr");
        NctiPyCB.RunSimpleString("FacePoints = ai.FacePoints");
        NctiPyCB.RunSimpleString("FaceNormals = ai.FaceNormals");
        NctiPyCB.RunSimpleString("FaceMask = ai.FaceMask");
        NctiPyCB.RunSimpleString("graph_edge_attr = ai.EdgeAttr");

        NctiPyCB.RunSimpleString("AAGNet = AGGNetInference()");
        NctiPyCB.RunSimpleString("seg_out, seg_out_inst, inst_out, bottom_out = "
                           "AAGNet.AI_model_inference(FaceID,FaceFID,FaceEID,FacePoints,FaceNormals,FaceMask,graph_"
                           "edge_attr,graph_face_attr) ");
        NctiPyCB.RunSimpleString("result_dict = AAGNet.postprocess(seg_out, seg_out_inst, inst_out, bottom_out)");
        NctiPyCB.RunSimpleString("ai.ImportAiResult(result_dict)");

        QMessageBox::information(nullptr, "AI", "孔推理完成。");
    }
}

Ncti_Boolean NctiQTPubFun::RCornerRecognition(NctiDocument* i_pDocument, QWidget* i_pQWidget)
{
    std::vector<NCTI_MODEL_TAG> cells;
    std::vector<NctiDisplayObject*> displayobjVec;
    NctiDocElementPubFun::GetDisplayObjectFromSelManager(i_pDocument, displayobjVec, cells);
    if (displayobjVec.size() == 0) { return false; }
    NctiBaseModel* pBaseModel = i_pDocument->GetBaseModel();
    NctiCommandManager* pComMan = NctiCommandManager::GetCommandManager(pBaseModel);
    if (pComMan) {
        NctiArgumentObject argumentObject;

        std::vector<std::string> args{ "round_corner_feature" };
        argumentObject.SetCommandArgumentVec(args);

        argumentObject.SetCellVec(cells);
        argumentObject.SetDisplayObjectVec(displayobjVec);

        EnumNctiResult result = pComMan->RunCommand("cmd_ncti_ai_model_add_label", &argumentObject);
    }
    NctiDocElementPubFun::CancelSelection(i_pDocument);
    return true;
}

Ncti_Boolean NctiQTPubFun::HoleRecognition(NctiDocument* i_pDocument, QWidget* i_pQWidget)
{
    std::vector<NCTI_MODEL_TAG> cells;
    std::vector<NctiDisplayObject*> displayobjVec;
    NctiDocElementPubFun::GetDisplayObjectFromSelManager(i_pDocument, displayobjVec, cells);
    if (displayobjVec.size() == 0) { return false; }
    NctiBaseModel* pBaseModel = i_pDocument->GetBaseModel();
    NctiCommandManager* pComMan = NctiCommandManager::GetCommandManager(pBaseModel);
    if (pComMan) {
        NctiArgumentObject argumentObject;

        std::vector<std::string> args{ "hole_feature" };
        argumentObject.SetCommandArgumentVec(args);

        argumentObject.SetCellVec(cells);
        argumentObject.SetDisplayObjectVec(displayobjVec);

        EnumNctiResult result = pComMan->RunCommand("cmd_ncti_ai_model_add_label", &argumentObject);
    }
    NctiDocElementPubFun::CancelSelection(i_pDocument);
    return true;
}

Ncti_Boolean NctiQTPubFun::LogoRecognition(NctiDocument* i_pDocument, QWidget* i_pQWidget)
{
    EnumNctiResult result = NCTI_FAILED;

    std::vector<NCTI_MODEL_TAG> cells;
    std::vector<NctiDisplayObject*> displayobjVec;
    NctiDocElementPubFun::GetDisplayObjectFromSelManager(i_pDocument, displayobjVec, cells);
    if (displayobjVec.size() == 0) { return false; }
    NctiBaseModel* pBaseModel = i_pDocument->GetBaseModel();
    NctiCommandManager* pComMan = NctiCommandManager::GetCommandManager(pBaseModel);
    if (pComMan) {
        std::vector<std::string> args{ "logo_feature" };
        NctiArgumentObject argumentObject;
        argumentObject.SetCommandArgumentVec(args);
        argumentObject.SetCellVec(cells);
        argumentObject.SetDisplayObjectVec(displayobjVec);

        result = pComMan->RunCommand("cmd_ncti_ai_model_add_label", &argumentObject);
    }
    NctiDocElementPubFun::CancelSelection(i_pDocument);
    return (result == EnumNctiResult::NCTI_SUCCEEDED);
}


Ncti_Boolean NctiQTPubFun::ShowRemoveFeaturesDlg(NctiDocument* i_pDocument, QWidget* i_pQWidget)
{
    if (nullptr == i_pDocument) return false;
    NctiDeleteTool::RemoveFeature(i_pDocument->GetBaseModel());
    return true;
}

Ncti_Boolean NctiQTPubFun::ShowRemoveFacesDlg(NctiDocument* i_pDocument, QWidget* i_pQWidget)
{
    if (nullptr == i_pDocument) return false;
    NctiDeleteTool::RemoveFace(i_pDocument->GetBaseModel());
    return true;
}

Ncti_Boolean NctiQTPubFun::SelectAll(NctiDocument* i_pDocument, QWidget* i_pQWidget)
{
    if (i_pDocument == nullptr) return false;
    NctiDocElementPubFun::SetSelectAllObjects(i_pDocument->GetBaseModel()->GetActiveBaseView());
    return true;
}

Ncti_Boolean NctiQTPubFun::RunPyScript(NctiWindowPlatform* i_pPlatform, const QString& i_filePath)
{
    QString filePath{i_filePath};

    if (filePath.isEmpty()) {
        filePath = QFileDialog::getOpenFileName(nullptr, QStringLiteral("执行脚本"), "", "Py Files (*.py)");
    }

    if (!filePath.isEmpty()) {
        QByteArray ba = filePath.toUtf8();

        // 加载并执行 Python 文件
		NctiPyRunSimpleFile(ba.data());
        return true;
        //FILE* f = NctiFile::get_file_point(ba.data(), "r");
        //if (f) {
        //    PyRun_SimpleFile(f, ba.data());
        //    fclose(f);
        //    return true;
        //}
    }
    return false;
}

namespace {
void run_python_code_in_thread(NctiWindowPlatform* i_pPlatform,
                               EnumModelDoc i_model,
                               EnumGCSDoc i_constraintType,
                               EnumMeshDoc i_meshType,
                               NctiCommandManager* pComMan,
                               NctiDocViewManager* pDocView,
                               NctiDisplayDocElement* pActiveDoc,
                               QString dirPath)
{
    std::function<void(NctiDisplayDocElement * pDoc, QString strFile)> PyRun = [&](NctiDisplayDocElement* pDoc,
                                                                                   QString strFile) {
        QDir dir(strFile);
        //QStringList fileList = dir.entryList(QDir::Files);// 获取目录中所有文件的列表，不包括子目录
        QStringList fileList
            = dir.entryList(QDir::Files | QDir::NoDotAndDotDot | QDir::AllDirs | QDir::NoSymLinks); //包括所有子目录
        Q_FOREACH(const QString& item, fileList) {
            QString fullPath = dir.absoluteFilePath(item); // 获取完整路径
            QFileInfo fileInfo(fullPath);                  // 创建QFileInfo对象以判断是文件还是目录
            if (fileInfo.isDir())                          // fileInfo.isDir()fileInfo.isFile()
            {
                pDocView->SetActiveDocElement(pDoc);
                NctiQTPubFun::AddAssembly(i_pPlatform, i_model, i_constraintType, i_meshType);
                NctiDisplayDocElement* pNewDoc = pDocView->GetActiveDocElement();
                PyRun(pNewDoc, fullPath);
                //{
                //	NctiArgumentObject arg;
                //	arg.SetDisplayObject1(pActiveDoc);
                //	pComMan->RunCommand("cmd_add_new_assembly", &arg);
                //}
            }
            QString suffix = fileInfo.suffix(); // 获取文件后缀
            if (suffix.toLower() != "py") continue;
            //add part
            {
                NctiArgumentObject arg;
                arg.SetDisplayObject1(pDoc);
                arg.Setm_ModelDoc(i_model);
                arg.Setm_constraintType(i_constraintType);
                arg.Setm_meshType(i_meshType);
                pComMan->RunCommand("cmd_add_new_part", &arg);
            }
            NctiQTPubFun::RunPyScript(i_pPlatform, fullPath);
        }
    };
    PyRun(pActiveDoc, dirPath);
}
} // namespace

Ncti_Boolean NctiQTPubFun::RunBatchPyScript(NctiWindowPlatform* i_pPlatform,
                                            const QString& dirPath,
                                            EnumModelDoc i_model /* = NCTI_GEOM_OCC*/,
                                            EnumGCSDoc i_constraintType /* = NCTI_GCS_DCM*/,
                                            EnumMeshDoc i_meshType /* = NCTI_MESH_GMSH*/)
{
    if (!i_pPlatform || !i_pPlatform->GetCurrentViewManager() || dirPath.isEmpty()) return false;

    NctiDocument* pDocument = i_pPlatform->GetCurrentViewManager()->GetDocument();
    if (!pDocument) return false;
    NctiCommandManager* pComMan       = NctiCommandManager::GetCommandManager(pDocument->GetBaseModel());
    NctiDocViewManager* pDocView      = NctiDocViewManager::GetDocViewManager(pDocument->GetBaseModel());
    NctiDisplayDocElement* pActiveDoc = pDocView->GetActiveDocElement();
    if (!pActiveDoc->IsTypeName(NctiDisplayDocAssembly::ID)) return false;

    run_python_code_in_thread(
        i_pPlatform, i_model, i_constraintType, i_meshType, pComMan, pDocView, pActiveDoc, dirPath);

    return true;
}

Ncti_Boolean NctiQTPubFun::MulticoreBatchScriptRun(NctiWindowPlatform* i_pPlatform, const QString& i_filePath)
{
    auto view = i_pPlatform->GetCurrentViewManager();
    if (!view) return false;
    NctiDocument* pDocument = view->GetDocument();
    if (!pDocument) return false;
    NctiCommandManager* pComMan               = NctiCommandManager::GetCommandManager(pDocument->GetBaseModel());
    NctiDocViewManager* pDocView              = NctiDocViewManager::GetDocViewManager(pDocument->GetBaseModel());
    NctiBaseView* pBaseView                   = pDocument->GetBaseModel()->GetActiveBaseView();
    NctiDisplayDocElement* pActiveAssemblyDoc = pDocView->GetActiveDocElement();
    NctiDisplayObject* pElement               = pActiveAssemblyDoc;
    while (pElement && !pElement->IsTypeName(NctiDisplayDocAssembly::ID)) {
        pElement = pElement->GetDoOwner();
    }
    if (pElement == NULL) { 
        return false;
    }

    pActiveAssemblyDoc = (NctiDisplayDocElement*)pElement;
    if (pActiveAssemblyDoc == nullptr || !pActiveAssemblyDoc->IsTypeName(NctiDisplayDocAssembly::ID)) { 
        return false;
    }

    QString filePath{i_filePath};

    if (filePath.isEmpty()) {
        filePath = QFileDialog::getOpenFileName(nullptr, QStringLiteral("执行脚本"), "", "Py Files (*.py)");
    }
    if (filePath.isEmpty()) return false;
    std::vector<NctiDisplayDocElement*> subDocVec;
    NctiDocElementPubFun::GetAllSubDoc(pActiveAssemblyDoc, subDocVec);

    // clang-format off
        std::vector<RGBAColor> colors = {
            RGBAColor(18, 212, 248),
            RGBAColor(0, 255, 127),
            RGBAColor(20, 255, 20),
            RGBAColor(228, 235, 50),
            RGBAColor(255, 165, 0),
            RGBAColor(255, 192, 203),
            RGBAColor(226, 67, 46),
            RGBAColor(211, 199, 242),
            RGBAColor(187, 74, 216),
            RGBAColor(141, 141, 255)
        };
    // clang-format on

    int iColorNum = colors.size();
    for (int i = 0; i < subDocVec.size(); i++) {
        RGBAColor color;
        if (i >= iColorNum) {
            int c = i % iColorNum;
            color = colors[c];
        }
        else
            color = colors[i];
        std::vector<NctiDisplayObject*> InstanceVec;
        subDocVec[i]->GetInstance(pBaseView, InstanceVec);
        for (Ncti_Size j = 0; j < InstanceVec.size(); j++) {
            NctiDisplayObject* pInstance = InstanceVec[j];
            if (pInstance) {
                pInstance->GetSegKey()->GetMaterialMappingControl()->SetFaceColor(color);
                pInstance->GetSegKey()->GetMaterialMappingControl()->SetLineColor(color);
            }
        }

        pDocView->SetActiveDocElement(subDocVec[i]);
        RunPyScript(i_pPlatform, filePath);
    }
    //
    //pDocView->SetActiveDocElement(pActiveAssemblyDoc);
    return true;
}

QString NctiQTPubFun::GetObjectName(NctiDisplayObject* pObject, int iType)
{
    if (pObject == nullptr) { return QString(); }

    // 获取对象的显示名称
    const Ncti_Char* pName = pObject->GetDisplayName();
    QString strName        = QString::fromUtf8(pName);

    // 如果显示名称为空，且对象是文档元素但不是草图，则尝试获取对象名称
    if (strName.isEmpty() && pObject->IsTypeName(NctiDisplayDocElement::ID)
        && !pObject->IsTypeName(NctiDisplayDocSketch::ID)) {
        pName   = pObject->GetObjName();
        strName = QString::fromUtf8(pName);
    }

    // 如果已经获取到名称，则添加容器信息并返回
    if (!strName.isEmpty()) {
        if (pObject->IsTypeName(NctiDisplayDocElement::ID) && !pObject->IsTypeName(NctiDisplayDocAssembly::ID)) {
            std::string containerInfo = NctiDocElementPubFun::GetCurContainerSimpleMessage(
                static_cast<NctiDisplayDocElement*>(pObject), iType);
            if (!containerInfo.empty()) { strName += QString::fromUtf8(("[" + containerInfo + "]").c_str()); }
        }
        return strName;
    }

    // clang-format off
        static const QHash<const char*, QString> typeNameMap = {
            {NctiDisplayDocAssembly::ID, QObject::tr("Assembly")},
            {NctiDisplayDocSketch::ID, QObject::tr("草图")},
            {NctiDisplayDocPart::ID, QObject::tr("Part")},
            {NctiTestSystemObject::ID, QObject::tr("测试配置")},
            {NctiAiModelSystemObject::ID, QObject::tr("AI配置")},
            {NctiTestCaseToModelManage::ID, QObject::tr("脚本配置")},
            {NctiDisplayDocSystemObject::ID, QObject::tr("系统配置")},
            {NctiDisplayModelBody::ID, QObject::tr("实体")},
            {NctiDisplayParticleObject::ID, QObject::tr("粒子")},
            {NctiDisplaySet::ID, QObject::tr("集合")},
            {NctiDisplayMaterialAttribute::ID, QObject::tr("材料属性")},
            {NctiDisplaySection::ID, QObject::tr("截面")},
            {NctiDisplayCoupling::ID, QObject::tr("耦合")},
            {NctiDisplayConcentratedForces::ID, QObject::tr("集中力")},
            {NctiDisplayPressure::ID, QObject::tr("压力")},
            {NctiDisplayLoadMoment::ID, QObject::tr("力矩")},
            {NctiDisplayLoadGravity::ID, QObject::tr("重力")},
            {NctiDisplayInertiaRelief::ID, QObject::tr("惯性释放")},
            {NctiDisplaySinglePointConstraint::ID, QObject::tr("单点约束")},
            {NctiDisplayOutput::ID, QObject::tr("输出变量")},
            {NctiDisplayStaticStep::ID, QObject::tr("静态分析步")},
            {NctiDisplayFrequencyStep::ID, QObject::tr("模态分析步")},
            {NctiDisplayBuckleStep::ID, QObject::tr("屈曲分析步")},
            {NctiDisplayGridMesh::ID, QObject::tr("非结构化网格")},
            {NctiDisplayPolyMesh::ID, QObject::tr("多边形网格")},
            {NctiDisplayMeshObject::ID, QObject::tr("网格")},
            {NctiDisplayWorkPlane::ID, QObject::tr("工作平面")},
            {NctiDisplayGrid::ID, QObject::tr("参考网格")}, // 修改以避免与其他网格类型冲突
            {NctiDisplaySketchArc::ID, QObject::tr("圆弧")},
            {NctiDisplaySketchRect::ID, QObject::tr("矩形")},
            {NctiDisplaySketchCircle::ID, QObject::tr("圆")},
            {NctiDisplaySketchPolyline::ID, QObject::tr("多段线")},
            {NctiDisplaySketchPolygon::ID, QObject::tr("多边形")},
            {NctiDisplaySketchLine::ID, QObject::tr("直线")},
            {NctiDisplaySketchSpline::ID, QObject::tr("样条线")},
            {NctiDisplaySketchCenterLine::ID, QObject::tr("中心线")},
            {NctiDisplaySketchDot::ID, QObject::tr("点")},
            {NctiDisplayGExtrude::ID, QObject::tr("拉伸体")},
            {NctiDisplayGRevolve::ID, QObject::tr("旋转体")},
            {NctiDisplayGSketch::ID, QObject::tr("组合")},
            {NctiDisplayGSketchGroup::ID, QObject::tr("分组")},
            {NctiDisplaySketchEllipse::ID, QObject::tr("椭圆")},
            {NctiDisplaySketchTan2Circles::ID, QObject::tr("双连接圆")},
            {NctiSketchConstrManager::ID, QObject::tr("约束关系")}
        };
    // clang-format on

    // 遍历映射表查找匹配的类型名称
    for (auto it = typeNameMap.constBegin(); it != typeNameMap.constEnd(); ++it) {
        if (pObject->IsTypeName(it.key())) { return it.value(); }
    }

    // 如果没有找到匹配的类型，返回空字符串
    return QString();
}

QString NCTI::NctiQTPubFun::GetDisplayStr(NctiDisplayObject* pObject, int iType)
{
    if (pObject == nullptr) { return QString(); }

    NctiDocViewManager* pDocView = NctiDocViewManager::GetDocViewManager((NctiManager*)pObject->GetLCM());
    NctiDisplayDocElement* pDocElem = pDocView->GetActiveDocElement();
    if (pDocElem->IsTypeName(NctiDisplayDocAssembly::ID))
    {
        if (pObject->IsTypeName(NctiDisplayDCM3Object::ID))
        {
            if (pObject->IsTypeName(NctiDCM3Set::ID))
            {
                NctiDCM3Set* pSet = (NctiDCM3Set*)pObject;
                if (pSet->status() == NCTI_DCM3_G_FIXED)
                {
                    if (pSet->GetModelBody())
                    {
                        return QString("固定(%1)").arg(pSet->GetModelBody()->GetObjName());
                    }
                }
            }
            else if (pObject->IsTypeName(NctiDisplayDCM3Dimension::ID))
            {
                NctiDisplayDCM3Dimension* pDim = (NctiDisplayDCM3Dimension*)pObject;
                std::string chName = NctiDCM3PubFun::GetConsChName(pDim->type());
                std::vector<NctiDisplayDCM3Geometry*> pGeomVec = pDim->GetConsGeometries();
                std::ostringstream oss;
                oss << chName;
                if (!pGeomVec.empty())
                {
                    oss << "(";
                    int count = 0;
                    for(auto* pGeom : pGeomVec)
                    {
                        if (pGeom->get_owner() && pGeom->get_owner()->GetModelBody())
                        {
                            if (count > 0)
                                oss << ",";
                            oss << pGeom->get_owner()->GetModelBody()->GetObjName();
                            count++;
                        }
                    }
                    oss << ")";
                }
                return QString(oss.str().c_str());
            }
            return QString();
        }
    }
    return GetObjectName(pObject, iType);
}

bool NctiQTPubFun::Explosion(NctiWindowPlatform* i_pPlatform)
{
    auto view = i_pPlatform->GetCurrentViewManager();
    if (!view) return false;

    NctiDocument* pDocument = view->GetDocument();
    if (!pDocument || !pDocument->GetBaseModel() || !pDocument->GetBaseModel()->GetActiveBaseView()) return false;
    NctiViewerRenderer* pRender               = pDocument->GetBaseModel()->GetActiveBaseView()->GetRenderCanvas();
    NctiCommandManager* pComMan               = NctiCommandManager::GetCommandManager(pDocument->GetBaseModel());
    NctiDocViewManager* pDocView              = NctiDocViewManager::GetDocViewManager(pDocument->GetBaseModel());
    NctiDisplayDocElement* pActiveAssemblyDoc = pDocView->GetRootDocElement();
    if (pActiveAssemblyDoc == nullptr) return false;
    std::vector<NctiDisplayDocElement*> subDocVec;
    if (pActiveAssemblyDoc->IsTypeName(NctiDisplayDocAssembly::ID)) {
        NctiDocElementPubFun::GetAllSubDoc(pActiveAssemblyDoc, subDocVec);
    }
    else {
        subDocVec.push_back(pActiveAssemblyDoc);
    }

    std::function<void(NctiDisplayDocElement*, std::vector<NctiDisplayObject*>&)> GetAllObjs
        = [=](NctiDisplayDocElement* pDoc, std::vector<NctiDisplayObject*>& pObjectVec) {
              NctiDisplayObjectList ObjList;
              pDoc->GetAllDisplayObjectsByType(&ObjList);
              NctiDisplayObject* pObj = nullptr;
              ObjList.Init();
              while ((pObj = ObjList.Next()) != nullptr) {
                  if (pObj
                      && (pObj->IsTypeName(NctiDisplayModelBody::ID) || pObj->IsTypeName(NctiDisplayMeshObject::ID))) {
                      pObjectVec.push_back(pObj);
                  }
              }
          };
    std::vector<std::vector<NctiDisplayObject*>> objsVec;
    for (int i = 0; i < subDocVec.size(); i++) {
        std::vector<NctiDisplayObject*> objs;
        GetAllObjs(subDocVec[i], objs);
        objsVec.push_back(objs);
    }
    double dMinDistance = 20;
    double dXDistance = 0, dYDistance = 0, dSite = 0;
    NctiPosition ptSite;
    NctiVector moveVector(0, 1, 0);
    for (int i = 0; i < objsVec.size(); i++) {
        auto docKey = subDocVec[i]->GetFirstDescendant()->GetSegKey();
        for (int j = 0; j < objsVec[i].size(); j++) {
            NctiDisplayObject* pObj = objsVec[i][j];
            NctiPosition ptMax, ptMin;
            if (pObj->IsTypeName(NctiDisplayModelBody::ID)) {
                NctiDisplayModelBody* pModelBody       = (NctiDisplayModelBody*)pObj;
                const std::vector<NctiMeshData> meshDB = pModelBody->GetMeshDataVec();
                if (meshDB.size() == 0) {
                    const std::vector<std::vector<float>> polyLineDB = pModelBody->GetPolyLineVec();
                    NctiDocElementPubFun::GetPolyLineBox(polyLineDB, ptMax, ptMin);
                }
                else {
                    NctiDocElementPubFun::GetMeshDataBox(meshDB, ptMax, ptMin);
                }
            }
            else {
                continue;
            }
            auto objKey = objsVec[i][j]->GetSegKey();
            double dMax = ptMax.y() - ptMin.y();
            if (dXDistance == 0) {
                dXDistance = 0.5 * dMax;
                dSite      = ptMin.y() + dXDistance;
                ptSite     = NctiPosition(
                    0.5 * (ptMax.x() + ptMin.x()), 0.5 * (ptMax.y() + ptMin.y()), 0.5 * (ptMax.z() + ptMin.z()));
                continue;
            }
            dXDistance += dMinDistance;
            NctiPosition pt = NctiPosition(
                0.5 * (ptMax.x() + ptMin.x()), 0.5 * (ptMax.y() + ptMin.y()), 0.5 * (ptMax.z() + ptMin.z()));
            NctiVector vecCenter = ptSite - pt;
            NctiVector vec       = (dXDistance + dSite - ptMin.y()) * moveVector;
            vecCenter.set_y(vec.y());
            vec                 = vecCenter;
            NctiTransf trasMove = TranslateTransf(vec);
            dXDistance += dMax;
            objKey->GetDrawingAttributeControl()->SetModelMat(trasMove);
        }
    }

    pDocument->GetBaseModel()->GetActiveBaseView()->Zoom();
    pDocument->GetBaseModel()->GetActiveBaseView()->Update();
    return true;
}

void NctiQTPubFun::RecoverObject(NctiWindowPlatform* i_pPlatform)
{
    auto view = i_pPlatform->GetCurrentViewManager();
    if (!view) return;

    NctiDocument* pDocument = view->GetDocument();
    if (!pDocument || !pDocument->GetBaseModel() || !pDocument->GetBaseModel()->GetActiveBaseView()) return;
    NctiCommandManager* pComMan               = NctiCommandManager::GetCommandManager(pDocument->GetBaseModel());
    NctiDocViewManager* pDocView              = NctiDocViewManager::GetDocViewManager(pDocument->GetBaseModel());
    NctiDisplayDocElement* pActiveAssemblyDoc = pDocView->GetRootDocElement();
    if (pActiveAssemblyDoc == nullptr) return;
    std::vector<NctiDisplayDocElement*> subDocVec;
    if (pActiveAssemblyDoc->IsTypeName(NctiDisplayDocAssembly::ID)) {
        NctiDocElementPubFun::GetAllSubDoc(pActiveAssemblyDoc, subDocVec);
    }
    else {
        subDocVec.push_back(pActiveAssemblyDoc);
    }
    NctiTransf trasMove = TranslateTransf(NctiVector(0, 0, 1));
    for (int i = 0; i < subDocVec.size(); i++) {
        NctiDisplayObjectList ObjList;
        subDocVec[i]->GetAllDisplayObjectsByType(&ObjList);
        NctiDisplayObject* pObj = nullptr;
        ObjList.Init();
        while ((pObj = ObjList.Next()) != nullptr) {
            if (pObj && (pObj->IsTypeName(NctiDisplayModelBody::ID) || pObj->IsTypeName(NctiDisplayMeshObject::ID))) {
                auto objKey = pObj->GetSegKey();
                objKey->GetDrawingAttributeControl()->UnSetAttr(NctiRenderDrawingKit::e_draw_ModelMat);
            }
        }
    }
    pDocument->GetBaseModel()->GetActiveBaseView()->Update();
}

bool NctiQTPubFun::DocExplosion(NctiWindowPlatform* i_pPlatform, int iType)
{
    auto view = i_pPlatform->GetCurrentViewManager();
    if (!view) return false;

    NctiDocument* pDocument = view->GetDocument();
    if (!pDocument || !pDocument->GetBaseModel() || !pDocument->GetBaseModel()->GetActiveBaseView()) return false;
    NctiViewerRenderer* pRender               = pDocument->GetBaseModel()->GetActiveBaseView()->GetRenderCanvas();
    NctiCommandManager* pComMan               = NctiCommandManager::GetCommandManager(pDocument->GetBaseModel());
    NctiDocViewManager* pDocView              = NctiDocViewManager::GetDocViewManager(pDocument->GetBaseModel());
    NctiDisplayDocElement* pActiveAssemblyDoc = nullptr;
    std::vector<NctiDisplayDocElement*> subDocVec;
    if (iType == 0 || iType == 1) {
        if (iType == 0)
            pActiveAssemblyDoc = pDocView->GetRootDocElement();
        else
            pActiveAssemblyDoc = pDocView->GetActiveDocElement();

        if (pActiveAssemblyDoc == nullptr || !pActiveAssemblyDoc->IsTypeName(NctiDisplayDocAssembly::ID))
            return false;

        NctiDocElementPubFun::GetAllSubDoc(pActiveAssemblyDoc, subDocVec);
    }
    else if (iType == 2) {
        pActiveAssemblyDoc = pDocView->GetActiveDocElement();
        if (pActiveAssemblyDoc == nullptr || !pActiveAssemblyDoc->IsTypeName(NctiDisplayDocAssembly::ID))
            return false;
        
        NctiDocElementPubFun::GetAllSubDoc(pActiveAssemblyDoc, subDocVec, false, true);
    }

    std::function<void(NctiDisplayDocElement*, std::vector<NctiDisplayObject*>&)> GetAllObjs
        = [=](NctiDisplayDocElement* pDoc, std::vector<NctiDisplayObject*>& pObjectVec) {
              NctiDisplayObjectList ObjList;
              pDoc->GetAllDisplayObjectsByType(&ObjList);
              NctiDisplayObject* pObj = nullptr;
              ObjList.Init();
              while ((pObj = ObjList.Next()) != nullptr) {
                  if (pObj
                      && (pObj->IsTypeName(NctiDisplayModelBody::ID) || pObj->IsTypeName(NctiDisplayMeshObject::ID))) {
                      pObjectVec.push_back(pObj);
                  }
              }
          };
    std::vector<std::vector<NctiDisplayObject*>> objsVec;
    for (int i = 0; i < subDocVec.size(); i++) {
        std::vector<NctiDisplayObject*> objs;
        GetAllObjs(subDocVec[i], objs);
        objsVec.push_back(objs);
    }
    double dMinDistance = 20;
    double dXDistance = 0, dYDistance = 0, dSite = 0;
    NctiPosition ptSite;
    NctiVector moveVector(0, 1, 0);
    NctiBaseView* pBaseView = pDocument->GetBaseModel()->GetActiveBaseView();
    for (int i = 0; i < objsVec.size(); i++) {
        NctiPosition ptMax, ptMin;
        bool bNull = true;
        for (int j = 0; j < objsVec[i].size(); j++) {
            NctiDisplayObject* pObj = objsVec[i][j];
            if (pObj->IsTypeName(NctiDisplayModelBody::ID)) {
                NctiDisplayModelBody* pModelBody       = (NctiDisplayModelBody*)pObj;
                const std::vector<NctiMeshData> meshDB = pModelBody->GetMeshDataVec();
                NctiPosition ptMaxTemp, ptMinTemp;
                NctiDocElementPubFun::GetMeshDataBox(meshDB, ptMaxTemp, ptMinTemp);
                if (bNull) {
                    ptMax = ptMaxTemp;
                    ptMin = ptMinTemp;
                }
                else {
                    if (ptMaxTemp.x() > ptMax.x()) { ptMax.set_x(ptMaxTemp.x()); }
                    if (ptMaxTemp.y() > ptMax.y()) { ptMax.set_y(ptMaxTemp.y()); }
                    if (ptMaxTemp.z() > ptMax.z()) { ptMax.set_z(ptMaxTemp.z()); }
                    if (ptMinTemp.x() < ptMin.x()) { ptMin.set_x(ptMinTemp.x()); }
                    if (ptMinTemp.y() < ptMin.y()) { ptMin.set_y(ptMinTemp.y()); }
                    if (ptMinTemp.z() < ptMin.z()) { ptMin.set_z(ptMinTemp.z()); }
                }
            }
            else {
                continue;
            }
            bNull = false;
        }
        if (bNull) continue;
        double dMax = ptMax.y() - ptMin.y();
        if (dXDistance == 0) {
            dXDistance = 0.5 * dMax;
            dSite      = ptMin.y() + dXDistance;
            ptSite     = NctiPosition(
                0.5 * (ptMax.x() + ptMin.x()), 0.5 * (ptMax.y() + ptMin.y()), 0.5 * (ptMax.z() + ptMin.z()));
            continue;
        }
        dXDistance += dMinDistance;
        NctiPosition pt
            = NctiPosition(0.5 * (ptMax.x() + ptMin.x()), 0.5 * (ptMax.y() + ptMin.y()), 0.5 * (ptMax.z() + ptMin.z()));
        NctiVector vecCenter = ptSite - pt;
        NctiVector vec       = (dXDistance + dSite - ptMin.y()) * moveVector;
        vecCenter.set_y(vec.y());
        vec                 = vecCenter;
        NctiTransf trasMove = TranslateTransf(vec);
        dXDistance += dMax;
        std::vector<NctiDisplayObject*> InstanceVec;
        subDocVec[i]->GetInstance(pBaseView, InstanceVec);
        for (Ncti_Size j = 0; j < InstanceVec.size(); j++) {
            NctiDisplayObject* pInstance  = InstanceVec[j];
            NctiRenderSegmentItem* docKey = pInstance->GetSegKey();
            docKey->GetDrawingAttributeControl()->SetModelMat(trasMove);
        }
    }
    pBaseView->Update();
    return true;
}

void NctiQTPubFun::DocRecoverObject(NctiWindowPlatform* i_pPlatform)
{
    auto view = i_pPlatform->GetCurrentViewManager();
    if (!view) return;

    NctiDocument* pDocument = view->GetDocument();
    if (!pDocument || !pDocument->GetBaseModel() || !pDocument->GetBaseModel()->GetActiveBaseView()) return;
    NctiCommandManager* pComMan               = NctiCommandManager::GetCommandManager(pDocument->GetBaseModel());
    NctiDocViewManager* pDocView              = NctiDocViewManager::GetDocViewManager(pDocument->GetBaseModel());
    NctiDisplayDocElement* pActiveAssemblyDoc = pDocView->GetRootDocElement();
    if (pActiveAssemblyDoc == nullptr || !pActiveAssemblyDoc->IsTypeName(NctiDisplayDocAssembly::ID))
        return;
    std::vector<NctiDisplayDocElement*> subDocVec;
    if (pActiveAssemblyDoc->IsTypeName(NctiDisplayDocAssembly::ID)) {
        NctiDocElementPubFun::GetAllSubDoc(pActiveAssemblyDoc, subDocVec);
        NctiDocElementPubFun::GetAllSubDoc(pActiveAssemblyDoc, subDocVec, true, true);
    }
    NctiTransf trasMove     = TranslateTransf(NctiVector(0, 0, 1));
    NctiBaseView* pBaseView = pDocument->GetBaseModel()->GetActiveBaseView();
    for (int i = 0; i < subDocVec.size(); i++) {
        std::vector<NctiDisplayObject*> InstanceVec;
        subDocVec[i]->GetInstance(pBaseView, InstanceVec);
        for (Ncti_Size j = 0; j < InstanceVec.size(); j++) {
            NctiDisplayObject* pInstance  = InstanceVec[j];
            NctiRenderSegmentItem* docKey = pInstance->GetSegKey();
            docKey->GetDrawingAttributeControl()->UnSetAttr(NctiRenderDrawingKit::e_draw_ModelMat);
        }
    }
    pBaseView->Update();
}

ObjCompareList NctiQTPubFun::GetObjectCompareDB(NctiDocument* i_pDocument)
{
    ObjCompareList dbList;
    if (i_pDocument == nullptr) return dbList;

    NctiDocViewManager* pDocView              = NctiDocViewManager::GetDocViewManager(i_pDocument->GetBaseModel());
    NctiBaseView* pBaseView                   = i_pDocument->GetBaseModel()->GetActiveBaseView();
    NctiDisplayDocElement* pActiveAssemblyDoc = pDocView->GetRootDocElement();
    if (pActiveAssemblyDoc == nullptr) return dbList;
    std::vector<NctiDisplayDocElement*> subDocVec;
    if (pActiveAssemblyDoc->IsTypeName(NctiDisplayDocAssembly::ID)) {
        NctiDocElementPubFun::GetAllSubDoc(pActiveAssemblyDoc, subDocVec);
    }
    else {
        subDocVec.push_back(pDocView->GetActiveDocElement());
    }

    std::function<void(NctiDisplayDocElement*, std::vector<NctiDisplayModelBody*>&)> GetAllObjs
        = [=](NctiDisplayDocElement* pDoc, std::vector<NctiDisplayModelBody*>& pObjectVec) {
              NctiDisplayObjectList ObjList;
              pDoc->GetAllDisplayObjectsByType(&ObjList);
              NctiDisplayObject* pObj = nullptr;
              ObjList.Init();
              while ((pObj = ObjList.Next()) != nullptr) {
                  if (pObj && (pObj->IsTypeName(NctiDisplayModelBody::ID))) {
                      pObjectVec.push_back((NctiDisplayModelBody*)pObj);
                  }
              }
          };

    for (int i = 0; i < subDocVec.size(); i++) {
        NctiDisplayDocElement* pDoc = subDocVec[i]->GetFirstDescendant();
        std::string strKernel       = NctiDocElementPubFun::GetCurContainerSimpleMessage(pDoc, 1);
        std::vector<NctiDisplayModelBody*> objs;
        GetAllObjs(pDoc, objs);
        RGBAColor color;

        std::vector<NctiDisplayObject*> InstanceVec;
        subDocVec[i]->GetInstance(pBaseView, InstanceVec);
        for (Ncti_Size j = 0; j < InstanceVec.size(); j++) {
            NctiDisplayObject* pInstance = InstanceVec[j];
            if (pInstance && !pInstance->GetSegKey()->GetMaterialMappingControl()->ShowFaceColor(color)) {
                NctiRenderSceneItem* pSceneItem = pBaseView->GetScene();
                pSceneItem->GetMaterialMappingControl()->ShowFaceColor(color);
            }
        }

        for (int p = 0; p < objs.size(); p++) {
            auto pModelBody = objs[p];
            NctiGeomProp geomProp;
            NctiGeometryResult result = NctiGeometryFunction::extract_prop(
                (NctiDisplayDocCustomContainer*)pDoc, pModelBody->GetNctiBody(), geomProp);

            std::map<int, int> topoMap;
            result = NctiGeometryFunction::dump_topology(
                (NctiDisplayDocCustomContainer*)pDoc, pModelBody->GetNctiBody(), false, topoMap);

            ObjCompareStruct compareDB;
            compareDB.strKernel  = strKernel;
            compareDB.strDocName = subDocVec[i]->GetObjName();
            compareDB.strName    = pModelBody->GetObjName();
            compareDB.color      = QColor(color.red * 255, color.green * 255, color.blue * 255);
            compareDB.dLen       = geomProp.GetWireLength();
            compareDB.dArea      = geomProp.GetArea();
            compareDB.dVolumn    = geomProp.GetVolumn();
            compareDB.dLen       = geomProp.GetWireLength();

            compareDB.iVERTEX       = topoMap[0];
            compareDB.iEDGE         = topoMap[1];
            compareDB.iWIRE         = topoMap[2];
            compareDB.iFACE         = topoMap[3];
            compareDB.iSHELL        = topoMap[4];
            compareDB.iSOLID        = topoMap[5];
            compareDB.iCOMPSOLID    = topoMap[6];
            compareDB.iCOMPOUND     = topoMap[7];
            compareDB.iSHAPE        = topoMap[8];
            compareDB.iFIN          = topoMap[20];
            compareDB.iLAMINAR_EDGE = topoMap[21];
            compareDB.iMEM_USAGE    = topoMap[22];

            dbList.push_back(compareDB);
        }
    }
    return dbList;
}

KernelExecResultList NctiQTPubFun::GetInterfaceResult(NctiDocument* i_pDocument)
{
    KernelExecResultList dbList;
    NctiDocViewManager* pDocView              = NctiDocViewManager::GetDocViewManager(i_pDocument->GetBaseModel());
    NctiDisplayDocElement* pActiveAssemblyDoc = pDocView->GetRootDocElement();
    if (pActiveAssemblyDoc == nullptr) return dbList;
    std::vector<NctiDisplayDocElement*> subDocVec;
    if (pActiveAssemblyDoc->IsTypeName(NctiDisplayDocAssembly::ID)) {
        NctiDocElementPubFun::GetAllSubDoc(pActiveAssemblyDoc, subDocVec);
    }
    else {
        subDocVec.push_back(pDocView->GetActiveDocElement());
    }
    for (int i = 0; i < subDocVec.size(); i++) {
        NctiDisplayDocElement* pDoc = subDocVec[i]->GetFirstDescendant();
        std::string strKernel       = NctiDocElementPubFun::GetCurContainerSimpleMessage(pDoc, 1);
        std::string strDocName      = subDocVec[i]->GetObjName();
        NctiDisplayObjectList ObjList;
        pDoc->GetAllDisplayObjectsByType(&ObjList);
        ObjList.Init();
        NctiDisplayObject* pObj                 = nullptr;
        NctiTestSystemObject* pTestSystemObject = nullptr;
        while ((pObj = ObjList.Next()) != nullptr) {
            if (pObj->IsTypeName(NctiTestSystemObject::ID)) { pTestSystemObject = (NctiTestSystemObject*)pObj; }
        }
        if (pTestSystemObject == nullptr) continue;

        std::vector<KernelExecResult> docList;
        const std::vector<InterfaceResult>& CommandResultVec = pTestSystemObject->GetInterfaceResult();
        for (size_t i = 0; i < CommandResultVec.size(); i++) {
            KernelExecResult res;
            res.strDocName         = strDocName;
            res.strKernel          = strKernel;
            res.Script             = CommandResultVec[i].Script;
            res.error              = CommandResultVec[i].error;
            res.errorArgument      = CommandResultVec[i].errorArgument;
            res.time               = CommandResultVec[i].time;
            res.result             = CommandResultVec[i].result;
            res.funcErrorCode      = CommandResultVec[i].funcErrorCode;
            res.usedPhysicalMemory = CommandResultVec[i].usedPhysicalMemory;
            docList.push_back(res);
        }
        dbList.push_back(docList);
    }
    return dbList;
}

void NctiQTPubFun::AddRenderView(NctiWindowViewManager* pViewManager, EnumRenderType renderModelType)
{
    auto view = pViewManager->GetDocument()->GetBaseModel()->AddBaseView();
    pViewManager->CreateWindowView(view, renderModelType);
    pViewManager->SetViewVisible(true, view);
    NctiInitializeTool().InitDisplay(view);
    pViewManager->OnActivateView(view,true);
}

Ncti_Boolean NctiQTPubFun::ParamTest(NctiDocument* i_pDocument)
{
    if (i_pDocument == nullptr) return false;
    NctiDocViewManager* pDocView      = NctiDocViewManager::GetDocViewManager(i_pDocument->GetBaseModel());
    NctiDisplayDocElement* pActiveDoc = pDocView->GetActiveDocElement()->GetFirstDescendant();
    NctiDisplayObjectList ObjList;
    pActiveDoc->GetAllDisplayObjectsByType(&ObjList, NctiDesignModel::ID);
    ObjList.Init();
    NctiDesignModel* pDesingnModel = nullptr;
    NctiDisplayObject* pObj        = nullptr;
    while ((pObj = ObjList.Next()) != nullptr) {
        if (pObj->IsTypeName(NctiDesignModel::ID)) {
            pDesingnModel = (NctiDesignModel*)pObj;
            break;
        }
    }
    if (pDesingnModel == nullptr) return false;
    NctiDisplayDocCustomContainer* pDocCustomContainer{};
    if (pActiveDoc->IsTypeName(NctiDisplayDocCustomContainer::ID)) {
        pDocCustomContainer = (NctiDisplayDocCustomContainer*)pActiveDoc;
    }
    if (pDocCustomContainer == nullptr
        && pActiveDoc->GetFirstDescendant()->IsTypeName(NctiDisplayDocCustomContainer::ID)) {
        pDocCustomContainer = (NctiDisplayDocCustomContainer*)pActiveDoc->GetFirstDescendant();
    }
    const std::vector<Ncti_Long>& DialogIDs                = pDesingnModel->GetDialogIDs();
    const std::vector<Ncti_Long>& FaceIDsIDs               = pDesingnModel->GetFaceIDs();
    const std::vector<NctiDisplayModelBody*>& ModelObjects = pDesingnModel->GetModelObjects();
    std::vector<NctiDisplayObject*> pObjVec;
    std::vector<std::vector<NCTI_MODEL_TAG>> CellVecVec;

    NctiDocElementPubFun::GetDisplayObjectFromSelManager(i_pDocument, pObjVec, CellVecVec);

    std::vector<Ncti_Long> dIds;
    for (int p = 0; p < pObjVec.size(); p++) {
        NctiDisplayObject* pObj = pObjVec[p];
        for (int i = 0; i < CellVecVec[p].size(); i++) {
            NCTI_MODEL_TAG cell = CellVecVec[p][i];
            Ncti_Long lID;
            NctiDisplayModelBody* pModelBody = (NctiDisplayModelBody*)pObj;
            pDocCustomContainer->get_persistent_tag(pModelBody, cell, lID);

            for (size_t m = 0; m < ModelObjects.size(); m++) {
                if (ModelObjects[m] != pObj) continue;
                if (FaceIDsIDs[m] != lID) continue;
                if (std::find(dIds.begin(), dIds.end(), DialogIDs[m]) == dIds.end()) dIds.push_back(DialogIDs[m]);
            }
        }
    }
    NctiPythonTool::SetDialogIDs(dIds);
    return dIds.size() > 0 ? true : false;
}

