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

#include "FileOperations.h"
#include "NctiBaseModel.h"
#include "NctiBaseView.h"
#include "NctiDocument.h"
#include "NctiQTPubFun.h"
#include "NctiSaveFileManager.h"
#include "NctiWindowPlatform.h"
#include "NctiWindowViewManager.h"
#include "NctiHandler.h"

#include <QFileDialog>
#include <QSettings>
#include <QStandardPaths>
#include <QCoreApplication>

#include "QuestionDialog.h"
#include "NewDocDialog.h"
#include "LoadingSpinnerWidget.h"
#include "IPCManager.h"
#include "ObjectTreeManager.h"
#include "PreferenceSettings.h"
#include "UserInteractionManager.h"
#include "CallbackInterfaces.h"

namespace NCTI {

static std::string toString(const QString& qstr)
{
    QByteArray ba = qstr.toUtf8();
    return ba.toStdString();
}

static QString getLastDir(const QString& key, QStandardPaths::StandardLocation loc = QStandardPaths::DocumentsLocation)
{
    QSettings settings;
    QString dir = settings.value(key).toString();
    if (dir.isEmpty() || !QDir(dir).exists()) {
        dir = QStandardPaths::writableLocation(loc);
    }
    return dir;
}

static void setLastDir(const QString& key, const QString& path)
{
    QSettings settings;
    settings.setValue(key, path);
}

FileOperations::FileOperations(MainWindow* mainWindow)
    : MainWindowModule(mainWindow)
{
}

void FileOperations::initialize()
{
    connect(m_mainWindow->Signals(), &MainWindowSignals::openNcti, this, &FileOperations::onOpenNcti);
    connect(m_mainWindow->Signals(), &MainWindowSignals::saveNcti, this, &FileOperations::onSaveNcti);
    connect(m_mainWindow->Signals(), &MainWindowSignals::saveAsNcti, this, &FileOperations::onSaveAsNcti);
    connect(m_mainWindow->Signals(), &MainWindowSignals::closeDocument, this, &FileOperations::onCloseDocument);
    connect(m_mainWindow->Signals(), &MainWindowSignals::newAssembly, this, &FileOperations::onNewAssembly);
    connect(m_mainWindow->Signals(), &MainWindowSignals::addAssembly, this, &FileOperations::onAddAssembly);
    connect(m_mainWindow->Signals(), &MainWindowSignals::addPart, this, &FileOperations::onAddPart);
    connect(m_mainWindow->Signals(), &MainWindowSignals::importAssemblyOrPart, this, &FileOperations::onImportAssemblyOrPart);
    connect(m_mainWindow->Signals(), &MainWindowSignals::removeAssemblyOrPart, this, &FileOperations::onRemoveAssemblyOrPart);
    connect(m_mainWindow->Signals(), &MainWindowSignals::newPart, this, &FileOperations::onNewPart);
    connect(m_mainWindow->Signals(), &MainWindowSignals::importModel, this, &FileOperations::onImportModel);
    connect(m_mainWindow->Signals(), &MainWindowSignals::exportModel, this, &FileOperations::onExportModel);
    connect(m_mainWindow->Signals(), &MainWindowSignals::undo, this, &FileOperations::onUndo);
    connect(m_mainWindow->Signals(), &MainWindowSignals::redo, this, &FileOperations::onRedo);
    connect(m_mainWindow->Signals(), &MainWindowSignals::deleteObject, this, &FileOperations::onDelete);
    connect(m_mainWindow->Signals(), &MainWindowSignals::scriptRun, this, &FileOperations::onScriptRun);
    connect(m_mainWindow->Signals(), &MainWindowSignals::batchScriptRun, this, &FileOperations::onBatchScriptRun);
    connect(m_mainWindow->Signals(), &MainWindowSignals::multicoreBatchScriptRun, this, &FileOperations::onMulticoreBatchScriptRun);
}

void FileOperations::onOpenNcti(const QString& filePath)
{
    if (filePath.isEmpty()) {
        showModelDialog(OpenDialog, "MainWindow/Open/LastDirectory", QStringLiteral("打开"), "Files(*.ncti)");
        return;
    }
    loadNctiFile(filePath);
}

void FileOperations::onSaveNcti()
{
	auto windowPlatform = m_mainWindow->getWindowPlatform();

	NctiSaveFileManager* saveFileMgr = NctiSaveFileManager::instance();
	if (!windowPlatform || !saveFileMgr) {
		return;
	}

	NCTI_SaveFileData fileData = saveFileMgr->GetDocument(windowPlatform->GetCurrentViewManager()->GetDocument());
	if (fileData.IsValid()) {
		//已经手动保存过或是打开的文件
		QString filePath = QString::fromUtf8(fileData.GetManualPath().c_str());
		NctiQTPubFun::SaveAsNctiFile(windowPlatform, filePath, false);
	} else {
		showModelDialog(SaveDialog, "MainWindow/Save/LastDirectory",  QStringLiteral("保存"), tr("Save File(*.ncti)"));
	}
}

void FileOperations::onSaveAsNcti()
{
	auto windowPlatform = m_mainWindow->getWindowPlatform();
	NctiSaveFileManager* saveFileMgr = NctiSaveFileManager::instance();
	if (!windowPlatform || !saveFileMgr) {
		return;
	}

	showModelDialog(SaveAsDialog, "MainWindow/SaveAs/LastDirectory", QStringLiteral("另存为"), tr("Save File(*.ncti)"));
}

void FileOperations::onNewAssembly()
{
    EnumModelDoc modelDoc{};
    EnumGCSDoc dcmDoc{};
    EnumMeshDoc meshDoc{};

    auto taskInfo = m_mainWindow->getIPCMgr()->GetTaskInfo();
    if (taskInfo) {
        taskInfo->type = "assembly";
        modelDoc       = (EnumModelDoc)taskInfo->geometry;
        dcmDoc         = (EnumGCSDoc)taskInfo->constraint;
        meshDoc        = (EnumMeshDoc)taskInfo->mesh;
    }
    else {
        NewDocDialog dlg(m_mainWindow);
        auto ret = dlg.exec();
        if (ret != QDialog::Accepted) {
            return;
        }
        auto&& [kernel, cons, mesh] = dlg.GetInfo();
        modelDoc                    = (EnumModelDoc)kernel;
        dcmDoc                      = (EnumGCSDoc)cons;
        meshDoc                     = (EnumMeshDoc)mesh;
    }
    newAssembly(modelDoc, dcmDoc, meshDoc);
}

void FileOperations::newAssembly(EnumModelDoc geo, EnumGCSDoc cs, EnumMeshDoc mesh)
{
    // 关闭当前
    onCloseDocument();

    m_mainWindow->initWindowPlatform();

    auto pDoc = NctiQTPubFun::CreateAssemblyDocument(m_mainWindow->getWindowPlatform(), geo, cs, mesh);
    if (pDoc) {
        m_mainWindow->initDocData(pDoc);
        PreferenceSettings::LoadingUIBasedOnJson(m_mainWindow);
    }
}

void FileOperations::onAddAssembly()
{
    NewDocDialog dlg(m_mainWindow);
    auto ret = dlg.exec();
    if (ret != QDialog::Accepted) {
        return;
    }
    auto&& [kernel, cons, mesh] = dlg.GetInfo();
    EnumModelDoc modelDoc       = (EnumModelDoc)kernel;
    EnumGCSDoc dcmDoc           = (EnumGCSDoc)cons;
    EnumMeshDoc meshDoc         = (EnumMeshDoc)mesh;

    m_mainWindow->initWindowPlatform();
    NctiQTPubFun::AddAssembly(m_mainWindow->getWindowPlatform(), modelDoc, dcmDoc, meshDoc);
}

void FileOperations::onAddPart()
{
    NewDocDialog dlg(m_mainWindow);
    auto ret = dlg.exec();
    if (ret != QDialog::Accepted) {
        return;
    }

    auto&& [kernel, constrain, mesh] = dlg.GetInfo();
    m_mainWindow->initWindowPlatform();
    NctiQTPubFun::AddPart(
        m_mainWindow->getWindowPlatform(), (EnumModelDoc)kernel, (EnumGCSDoc)constrain, (EnumMeshDoc)mesh);
}

void FileOperations::onImportAssemblyOrPart()
{
    QString filePath = getFilePathOnOpen();
    if (!filePath.isEmpty()) {
        NctiQTPubFun::ImportAssemblyOrPart(m_mainWindow->getWindowPlatform(), filePath);
    }
}

void FileOperations::onRemoveAssemblyOrPart()
{
    NctiQTPubFun::RemoveAssemblyOrPart(m_mainWindow->getWindowPlatform());
}

void FileOperations::onNewPart()
{
    EnumModelDoc modelDoc{};
    EnumGCSDoc dcmDoc{};
    EnumMeshDoc meshDoc{};

    auto taskInfo = m_mainWindow->getIPCMgr()->GetTaskInfo();
    if (taskInfo) {
        taskInfo->type = "part";
        modelDoc = (EnumModelDoc)taskInfo->geometry;
        dcmDoc = (EnumGCSDoc)taskInfo->constraint;
        meshDoc = (EnumMeshDoc)taskInfo->mesh;
    }
    else {
        NewDocDialog dlg(m_mainWindow);
        auto ret = dlg.exec();
        if (ret != QDialog::Accepted) {
            return;
        }
        auto&& [kernel, cons, mesh] = dlg.GetInfo();
        modelDoc = (EnumModelDoc)kernel;
        dcmDoc = (EnumGCSDoc)cons;
        meshDoc = (EnumMeshDoc)mesh;
    }
    newPart(modelDoc, dcmDoc, meshDoc);
}

void FileOperations::newPart(EnumModelDoc geo, EnumGCSDoc cs, EnumMeshDoc mesh)
{
    // 关闭当前
    onCloseDocument();

    m_mainWindow->initWindowPlatform();

    auto pDoc = NctiQTPubFun::CreateModelDocument(m_mainWindow->getWindowPlatform(), geo, cs, mesh);
    if (pDoc) {
        m_mainWindow->initDocData(pDoc);
        PreferenceSettings::LoadingUIBasedOnJson(m_mainWindow);
    }
}

void FileOperations::onCloseDocument()
{
    NctiDocument* pDoc = NctiQTPubFun::GetCurrentViewDocment(m_mainWindow->getWindowPlatform());
    if (pDoc && pDoc->GetBaseModel()) {
        pDoc->GetBaseModel()->GetFirstBaseView()->RemoveOperator("NctiOperatingKey");
    }
    NctiQTPubFun::CloseModelDocument(m_mainWindow->getWindowPlatform());


    m_mainWindow->closeWindowPlatform();

    m_mainWindow->getObjectTreeMgr()->SetTreeModified();

    m_mainWindow->deleteOperatingKey();
}

void FileOperations::onImportModel()
{
    QString filter{ "GeomeTry(*.igs *.stp *.step *.fbx *.prt );;Mesh(*.obj *.vtk *.vtp *.vtu);;All File(*.*)" };
    showModelDialog(ImportDialog, "MainWindow/Import/LastDirectory", QStringLiteral("导入模型"), filter);
}

void FileOperations::importModels(const QStringList& filePaths)
{
    if (filePaths.isEmpty()) {
        return;
    }

    if (m_mainWindow->initWindowPlatform()) {
        NctiQTPubFun::ImportModelFile(m_mainWindow->getWindowPlatform(), filePaths, 2);
    }
}

void FileOperations::onExportModel()
{
    QString filter{"IGS Files(*.igs);; STP Files(*.stp);; STEP Files(*.step);; "
                             "Brep Files(*.brep);; Sat Files(*.sat);; Prt Files(*.prt)"};
    showModelDialog(ExportDialog, "MainWindow/Export/LastDirectory", QStringLiteral("导出模型"), filter);
}

void FileOperations::onUndo()
{
    NctiDocument* pDocument = NctiQTPubFun::GetCurrentViewDocment(m_mainWindow->getWindowPlatform());
    if (pDocument && pDocument->IsUndoValid())
        NctiQTPubFun::onUndo(pDocument);
}

void FileOperations::onRedo()
{
    NctiDocument* pDocument = NctiQTPubFun::GetCurrentViewDocment(m_mainWindow->getWindowPlatform());
    if (pDocument && pDocument->IsUndoValid())
        NctiQTPubFun::onRedo(pDocument);
}

void FileOperations::onDelete()
{
    NctiDocument* pDocument = NctiQTPubFun::GetCurrentViewDocment(m_mainWindow->getWindowPlatform());
    if (!pDocument) {
        return;
    }
    NctiQTPubFun::onDelete(pDocument);
}

void FileOperations::onStartRecord()
{
    m_isRecording = true;
    NctiHandler::StartRecord();
}

void FileOperations::onEndRecord()
{
	// TODO: 终止录制
	if (!m_isRecording) {
		return;
	}

	QuestionDialog dialog(m_mainWindow);
	int ret = dialog.exec(QStringLiteral("停止录制"), QStringLiteral("是否保存录制？"));
	if (ret == QDialog::DialogCode::Accepted) {
        QString filter{ "Script Files(*.py);;All Files(*.*)" };
		showModelDialog(ScriptSaveDialog, "MainWindow/Script/LastDirectory", QStringLiteral("保存脚本"), filter);
	} 
    else {
		NctiHandler::EndRecord();
	}

    m_isRecording = false;
}

void FileOperations::onScriptRun()
{
    NctiDocument* i_pDocument = NctiQTPubFun::GetCurrentViewDocment(m_mainWindow->getWindowPlatform());
    if (!i_pDocument) {
        return;
    }
    if (m_mainWindow->activeDoc(i_pDocument->GetBaseModel()) == nullptr) {
        return;
    }
    NctiQTPubFun::RunPyScript(m_mainWindow->getWindowPlatform());
}

void FileOperations::onBatchScriptRun()
{
    NewDocDialog dlg(m_mainWindow);
    auto ret = dlg.exec();
    if (ret != QDialog::Accepted) {
        return;
    }
    QString dirPath = QFileDialog::getExistingDirectory(
        nullptr,
        QStringLiteral("选择装配体脚本路径"),
        "", // 可以是起始路径，也可以是空字符串，让对话框显示在默认位置
        QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    
    if (dirPath.isEmpty()) {
        return;
    }

    auto&& [kernel, constrain, mesh] = dlg.GetInfo();
    m_mainWindow->getObjectTreeMgr()->SetUIWait(true);
    LoadingSpinnerWidget::showLoading(m_mainWindow, [=, this]() {
        NctiQTPubFun::RunBatchPyScript(
            m_mainWindow->getWindowPlatform(), dirPath, (EnumModelDoc)kernel, (EnumGCSDoc)constrain, (EnumMeshDoc)mesh);
        m_mainWindow->getObjectTreeMgr()->SetUIWait(false);
        m_mainWindow->getObjectTreeMgr()->SetTreeIsModify(true);
        //UI 操作必须保证在主线程执行
        QMetaObject::invokeMethod(this, [this]() { m_mainWindow->getObjectTreeMgr()->UpdateTree(); }, Qt::QueuedConnection);
    });
}

void FileOperations::onMulticoreBatchScriptRun()
{
    NctiQTPubFun::MulticoreBatchScriptRun(m_mainWindow->getWindowPlatform(), "");
}

void FileOperations::onParamTest()
{
    NctiDocument* i_pDocument = NctiQTPubFun::GetCurrentViewDocment(m_mainWindow->getWindowPlatform());
    if (!i_pDocument) {
        return;
    }

    if (!NctiQTPubFun::ParamTest(i_pDocument))
        return;

    onScriptRun();
}

QString FileOperations::getFilePathOnOpen()
{
	const QString LAST_DIRECTORY_KEY = "MainWindow/Open/LastDirectory";
	QString openNctiDir = getLastDir(LAST_DIRECTORY_KEY);

	QString filePath = QFileDialog::getOpenFileName(
		nullptr, 
		QStringLiteral("打开"), 
		openNctiDir, 
		"Files(*.ncti)");

    if (filePath.isEmpty()) {
        return QString();
    }

    QString currentDir = QFileInfo(filePath).absoluteDir().path();
    if (currentDir != openNctiDir) {
        setLastDir(LAST_DIRECTORY_KEY, currentDir);
    }
	return filePath;
}

QString FileOperations::getFilePathOnSave()
{
	const QString LAST_DIRECTORY_KEY = "MainWindow/Save/LastDirectory";
	QString saveNctiDir = getLastDir(LAST_DIRECTORY_KEY);

	QString filePath = QFileDialog::getSaveFileName(
        nullptr,
		QStringLiteral("保存"), 
		saveNctiDir, 
		tr("Save File(*.ncti)"));

    if (filePath.isEmpty()) {
        return QString();
    }

    QString currentDir = QFileInfo(filePath).absoluteDir().path();
    if (currentDir != saveNctiDir) {
        setLastDir(LAST_DIRECTORY_KEY, currentDir);
    }
	return filePath;
}

QString FileOperations::getFilePathOnSaveAs()
{
	const QString LAST_DIRECTORY_KEY = "MainWindow/SaveAs/LastDirectory";
	QString saveAsNctiDir = getLastDir(LAST_DIRECTORY_KEY);

	QString filePath = QFileDialog::getSaveFileName(
        nullptr,
		QStringLiteral("另存为"), 
		saveAsNctiDir, 
		tr("Save File(*.ncti)"));

    if (filePath.isEmpty()) {
        return QString();
    }

    QString currentDir = QFileInfo(filePath).absoluteDir().path();
    if (currentDir != saveAsNctiDir) {
        setLastDir(LAST_DIRECTORY_KEY, currentDir);
    }
	return filePath;
}

QStringList FileOperations::getFilePathOnImport()
{
	const QString LAST_DIRECTORY_KEY = "MainWindow/Import/LastDirectory";
	QString importModelDir = getLastDir(LAST_DIRECTORY_KEY);

	QStringList filePaths = QFileDialog::getOpenFileNames(
        nullptr,
		QStringLiteral("导入模型"),
		importModelDir,
		"GeomeTry(*.igs *.stp *.step *.fbx *.prt );;Mesh(*.obj *.vtk *.vtp *.vtu);;All File(*.*)");

    if (filePaths.isEmpty()) {
        return QStringList();
    }

    QString currentDir = QFileInfo(filePaths.last()).absoluteDir().path();
    if (currentDir != importModelDir) {
        setLastDir(LAST_DIRECTORY_KEY, currentDir);
    }
	return filePaths;
}

QString FileOperations::getFilePathOnExport()
{
	const QString LAST_DIRECTORY_KEY = "MainWindow/Export/LastDirectory";
	QString exportModelDir = getLastDir(LAST_DIRECTORY_KEY);

	QString filePath = QFileDialog::getSaveFileName(
        nullptr,
		QStringLiteral("导出模型"),
		exportModelDir,
		tr("IGS Files(*.igs);; STP Files(*.stp);; STEP Files(*.step);; "
			"Brep Files(*.brep);; Sat Files(*.sat);; Prt Files(*.prt)"));

    if (filePath.isEmpty()) {
        return QString();
    }

    QString currentDir = QFileInfo(filePath).absoluteDir().path();
    if (currentDir != exportModelDir) {
        setLastDir(LAST_DIRECTORY_KEY, currentDir);
    }
	return filePath;
}

void FileOperations::showModelDialog(DialogType type, const QString& key, const QString& title, const QString& filter)
{
    // set focus to fix the file dialog freezing
    auto uiMgr = m_mainWindow->getUserInteractionMgr();
    if (uiMgr) {
        uiMgr->SetFocus();
    }

    m_currentDialogType = type;
    m_currentDirectoryKey = key;

    QFileDialog dialog(nullptr);
    dialog.setWindowTitle(title);
    dialog.setDirectory(getLastDir(key));
    dialog.setNameFilter(filter);
    dialog.setOption(QFileDialog::DontUseNativeDialog, false);

    switch (type) {
    case OpenDialog:
        dialog.setAcceptMode(QFileDialog::AcceptOpen);
        dialog.setFileMode(QFileDialog::ExistingFile);
        break;
    case ImportDialog:
        dialog.setAcceptMode(QFileDialog::AcceptOpen);
        dialog.setFileMode(QFileDialog::ExistingFiles);
        break;
    case SaveDialog:
    case SaveAsDialog:
    case ExportDialog:
    case ScriptSaveDialog:
        dialog.setAcceptMode(QFileDialog::AcceptSave);
        dialog.setFileMode(QFileDialog::AnyFile);
        dialog.setOption(QFileDialog::DontConfirmOverwrite, false);
        if (type == SaveDialog || type == SaveAsDialog) {
            dialog.setDefaultSuffix("ncti");
        }
        break;
    }

    if (dialog.exec() != QDialog::Accepted) {
        return;
    }

    QStringList selectedFiles = dialog.selectedFiles();

    // 保存目录位置
    if (!selectedFiles.isEmpty()) {
        QString currentDir = QFileInfo(selectedFiles.first()).absoluteDir().path();
        setLastDir(key, currentDir); 
        
        handleSelectedFiles(m_currentDialogType, selectedFiles);
    }
}

void FileOperations::showModelessDialog(DialogType type, const QString& key, const QString& title, const QString& filter)
{
    m_currentDialogType = type;
    m_currentDirectoryKey = key;

    if (m_fileDialog) {
        m_fileDialog->disconnect();
        m_fileDialog->deleteLater();
        m_fileDialog = nullptr;
    }

    m_fileDialog = new QFileDialog(m_mainWindow);
    m_fileDialog->setWindowTitle(title);
    m_fileDialog->setDirectory(getLastDir(key));
    m_fileDialog->setNameFilter(filter);
    m_fileDialog->setOption(QFileDialog::DontUseNativeDialog, false);

    switch (type) {
    case OpenDialog: {
        m_fileDialog->setAcceptMode(QFileDialog::AcceptOpen);
        m_fileDialog->setFileMode(QFileDialog::ExistingFile);
        break;
    }
    case ImportDialog: {
        m_fileDialog->setAcceptMode(QFileDialog::AcceptOpen);
        m_fileDialog->setFileMode(QFileDialog::ExistingFiles);
        break;
    }
    case SaveDialog:
    case SaveAsDialog:
    case ExportDialog:
    case ScriptSaveDialog: {
        m_fileDialog->setAcceptMode(QFileDialog::AcceptSave);
        m_fileDialog->setFileMode(QFileDialog::AnyFile);
        m_fileDialog->setOption(QFileDialog::DontConfirmOverwrite, false);
        if (type == SaveDialog || type == SaveAsDialog) {
            m_fileDialog->setDefaultSuffix("ncti");
        }
        break;
    }
    }

    connect(m_fileDialog, &QFileDialog::finished, this, &FileOperations::onFileDialogFinished);
    
    m_fileDialog->show();
}

void FileOperations::onFileDialogFinished(int result)
{
    if (!m_fileDialog || result != QDialog::Accepted) {
        if (m_fileDialog) {
            m_fileDialog->deleteLater();
            m_fileDialog = nullptr;
        }
        return;
    }

    QStringList selectedFiles = m_fileDialog->selectedFiles();
    m_fileDialog->deleteLater();
    m_fileDialog = nullptr;

    // 保存目录位置
    if (!selectedFiles.isEmpty()) {
        QString currentDir = QFileInfo(selectedFiles.first()).absoluteDir().path();
        setLastDir(m_currentDirectoryKey, currentDir);
        
        handleSelectedFiles(m_currentDialogType, selectedFiles);
    }
}

void FileOperations::handleSelectedFiles(DialogType dialogType, const QStringList& files)
{
    auto windowPlatform = m_mainWindow->getWindowPlatform();

    switch (dialogType) {
    case OpenDialog: {
        loadNctiFile(files.first());

        // 更新文件信息
        QFileInfo fileInfo(files.first());
        QString fileName = fileInfo.completeBaseName();
        if (m_mainWindow->getIPCMgr()) {
            m_mainWindow->getIPCMgr()->UpdateNctiFileInfoToServer(fileName, files.first());
        }
        break;
    }
    case SaveDialog:
    case SaveAsDialog: {
        bool isSaveAs = (dialogType == SaveAsDialog);
        NctiQTPubFun::SaveAsNctiFile(windowPlatform, files.first(), isSaveAs);
        break;
    }
    case ExportDialog: {
        NctiQTPubFun::ExportModelFile(windowPlatform, files.first());
        break;
    }
    case ImportDialog: {
        importModels(files);
        break;
    }
    case ScriptSaveDialog: {
        NctiHandler::EndRecord(files.first());
        break;
    }
    default:
        break;
    }
}

void FileOperations::loadNctiFile(const QString& filePath)
{
    // 关闭当前文档
    onCloseDocument();

    // 初始化窗口平台
    if (m_mainWindow->getWindowPlatform() == nullptr) {
        m_mainWindow->initWindowPlatform();
    }

    // 显示加载状态
    QString statusText = m_mainWindow->getStatusText();
    m_mainWindow->setStatusText("正在加载ncti文件...");
    QCoreApplication::processEvents(QEventLoop::ExcludeUserInputEvents);

    // 加载文件
    NctiDocument* pDoc = NctiQTPubFun::LoadNctiFile(m_mainWindow->getWindowPlatform(), filePath);
    if (pDoc) {
        m_mainWindow->initDocData(pDoc);
        PreferenceSettings::LoadingUIBasedOnJson(m_mainWindow);
    }

    // 恢复状态文本
    m_mainWindow->setStatusText(statusText);
}


} // namespace NCTI