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

#include "PreferenceSettings.h"

#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QStandardPaths>
#include <QApplication>

#include "NctiInitializeTool.h"
#include "NctiConfig.h"
#include "NctiDocument.h"
#include "NctiBaseModel.h"
#include "NctiDocElementPubFun.h"
#include "NctiBaseView.h"

#include "NctiPythonTool.h"
#include "NctiRenderSceneItem.h"
#include "NctiRenderMaterialKit.h"
#include "NctiWindowPlatform.h"

#include "NctiQTPubFun.h"
#include "NctiQtRightSideView.h"

#include "OptionsDlg.h"
#include "UserInteractionManager.h"
#include "UIOptionManager.h"

namespace NCTI {

static std::string toStdString(const QString& value)
{
    QByteArray ba = value.toUtf8();
    return std::string(ba.constData());
}

PreferenceSettings::PreferenceSettings(MainWindow* mainWindow)
    : MainWindowModule(mainWindow)
{
}

void PreferenceSettings::initialize()
{
    connect(m_mainWindow->Signals(), &MainWindowSignals::onOptions, this, &PreferenceSettings::openOptions);
}

void PreferenceSettings::initSelVisualMode()
{
    auto uiOptMgr = m_mainWindow->getUIOptionMgr();
    if (!uiOptMgr) {
        return;
    }

    auto selCheckBoxs    = uiOptMgr->getSelCheckBoxs();
    auto visualCheckBoxs = uiOptMgr->getVisualCheckBoxs();
    if (selCheckBoxs.empty() || visualCheckBoxs.empty()) {
        return;
    }

    bool body = false;
    bool face = true;
    bool edge = true;
    bool vertex = true;
    NctiQTPubFun::GetSel(m_mainWindow->getWindowPlatform(), body, face, edge, vertex);
    selCheckBoxs["select_body"]->setChecked(body);
    selCheckBoxs["select_face"]->setChecked(face);
    selCheckBoxs["select_edge"]->setChecked(edge);
    selCheckBoxs["select_vertex"]->setChecked(vertex);

    NctiDocElementPubFun::GetVisualMode(face, edge, vertex);
    body = face && edge && vertex;
    visualCheckBoxs["visual_body"]->setChecked(body);
    visualCheckBoxs["visual_face"]->setChecked(face);
    visualCheckBoxs["visual_edge"]->setChecked(edge);
    visualCheckBoxs["visual_vertex"]->setChecked(vertex);
    if (body) {
        visualCheckBoxs["visual_face"]->setEnabled(false);
        visualCheckBoxs["visual_edge"]->setEnabled(false);
        visualCheckBoxs["visual_vertex"]->setEnabled(false);
    }
}

void PreferenceSettings::handleBackgroundColorSetting(QColor topColor, QColor bottomColor)
{
    double r_top = static_cast<double>(topColor.red()) / 255.0;
    double g_top = static_cast<double>(topColor.green()) / 255.0;
    double b_top = static_cast<double>(topColor.blue()) / 255.0;

    double r_bottom = static_cast<double>(bottomColor.red()) / 255.0;
    double g_bottom = static_cast<double>(bottomColor.green()) / 255.0;
    double b_bottom = static_cast<double>(bottomColor.blue()) / 255.0;

    auto doc = NctiQTPubFun::GetCurrentViewDocment(m_mainWindow->getWindowPlatform());
    if (doc) {
        NctiBaseView* pBaseView = doc->GetBaseModel()->GetActiveBaseView();
        //背景
        pBaseView->GetScene()->SetBackGround(true);
        pBaseView->GetScene()->SetWindowColor({ r_top, g_top, b_top });
        pBaseView->GetScene()->SetWindowContrastColor({ r_bottom, g_bottom, b_bottom });
        pBaseView->Update();
    }
}

void PreferenceSettings::handleModelColorSetting(QColor faceColor, QColor edgeColor, QColor vertexColor)
{
    auto doc = NctiQTPubFun::GetCurrentViewDocment(m_mainWindow->getWindowPlatform());
    if (doc) {
        NctiBaseView* pBaseView         = doc->GetBaseModel()->GetActiveBaseView();
        NctiRenderSceneItem* pSceneItem = pBaseView->GetScene();
        //模型颜色，点、线、面
        pSceneItem->GetMaterialMappingControl()->SetFaceColor(RGBAColor(faceColor.name().toStdString()));
        pSceneItem->GetMaterialMappingControl()->SetLineColor(RGBAColor(edgeColor.name().toStdString()));
        pSceneItem->GetMaterialMappingControl()->SetVertexColor(RGBAColor(vertexColor.name().toStdString()));
        pBaseView->Update();
    }
}

void PreferenceSettings::handleObjectDisplayMode(bool faceState, bool edgeState, bool vertexState)
{
    NctiQTPubFun::SetVisualMode(m_mainWindow->getWindowPlatform(), faceState, edgeState, vertexState);
    initSelVisualMode();
}

void PreferenceSettings::handleBackups(bool openState, const std::string& path, int time)
{
    // TODO
}

void PreferenceSettings::openOptions()
{
    OptionsDlg dlg(m_mainWindow);
    connect(&dlg, &OptionsDlg::savePushButtonClicked, this, [this] {
        PreferenceSettings::LoadingUIBasedOnJson(m_mainWindow);
    });

    NctiWindowPlatform* platform = m_mainWindow->getWindowPlatform();
    if (NctiQTPubFun::GetCurrentViewDocment(platform)) {
        //对象显示模式同步
        bool face = false;
        bool edge = false;
        bool vertex = false;

        NctiDocElementPubFun::GetVisualMode(face, edge, vertex);
        dlg.setObjectDisplayMode(face, edge, vertex);
        dlg.updateDisplayModeIcon();

        //控制台，脚本编辑器显示同步
        //dlg.setConsoleVisible(m_mainWindow->getUserInteractionMgr()->getConsoleState());
        //dlg.setScriptEditorVisible(m_mainWindow->getUserInteractionMgr()->getScriptEditorState());
    }
    dlg.exec();
}

void PreferenceSettings::LoadingUIBasedOnJson(MainWindow* mainWindow)
{
    if (!mainWindow) {
        return;
    }

    AppConfig* params = AppConfig::GetConfig();

    //控制台
    mainWindow->getUserInteractionMgr()->showCommandConsole(params->Environment.Console);

    //脚本编辑器
    NctiQtRightSideView* rightSideView = mainWindow->getUserInteractionMgr()->getRightSideView();
    if (rightSideView) {
        if (params->Environment.ScriptEditor) {
            rightSideView->changeCurrentView(NctiQtRightSideView::ViewEditor);
        }
        else {
            rightSideView->hideScriptEditor();
        }
    }

    //备份开启或关闭
    if (params->Environment.AutoSaveValid) {
        if (params->Environment.AutoSaveTime > 0 && !params->Environment.AutoSaveFolder.empty()) {
            handleBackups(params->Environment.AutoSaveValid, params->Environment.AutoSaveFolder, params->Environment.AutoSaveTime);
        }
    }

    NctiDocument* pDocument = NctiQTPubFun::GetCurrentViewDocment(mainWindow->getWindowPlatform());
    if (pDocument && pDocument->GetBaseModel()) {
        NctiPythonTool::InitPyDocument(pDocument->GetID());
        auto view = pDocument->GetBaseModel()->GetActiveBaseView();
        NctiInitializeTool().InitDisplay(view);
    }
}

std::string PreferenceSettings::getConfigFile() {
    QString configFilePath = QDir( QString::fromStdString(getConfigDir())).filePath(CONFIG_FILE);
    if (!QFile::exists(configFilePath)) {
        QString srcConfigPath = QDir(QCoreApplication::applicationDirPath()).filePath(CONFIG_FILE);
        if (QFileInfo(srcConfigPath).exists()) {
            QFile::copy(srcConfigPath, configFilePath);
            if (!QFile::exists(configFilePath)) {
                qWarning() << "Failed to copy config file from" << srcConfigPath << "to" << configFilePath;
            }
        }
    }
    return configFilePath.toStdString();
}

std::string  PreferenceSettings::getConfigDir()
{
    QString configDir = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QDir dir(configDir);
    if (!dir.exists()) {
        if (!dir.mkpath(".")) {
            qWarning() << "Failed to create config directory:" << configDir;
            return "";
        }
    }
    return configDir.toStdString();
}

void PreferenceSettings::initDefaultCAE()
{
    AppConfig* params = AppConfig::GetConfig();
    params->ResetToDefault();

#if defined(_MSC_VER)
    params->Plugin.AddPlugin({ "ncti_command.dll" });
    params->Plugin.AddPlugin({ "ncti_gmsh_plugin.dll" });
    params->Plugin.AddPlugin({ "ncti_meshgems_plugin.dll" }, "MeshGems");
    params->Plugin.AddPlugin({ "ncti_occ_plugin.dll" }, "OCC");
    params->Plugin.AddPlugin({ "ncti_render_vulkan.dll" });
    params->Plugin.AddPlugin({ "ncti_vtk_plugin.dll" }, "VTK");
    params->Environment.FunctionPath = "D:/pythonExample/NctiPythonFunction";
    params->Environment.ImportPath = { "D:/Dataexchange/brep/success",
                    "D:/Dataexchange/step",
                    "D:/Dataexchange/iges",
                    "D:/Dataexchange/OCCSetup/occ/success",
                    "D:/Dataexchange/OCCSetup/iges",
                    "D:/Dataexchange/OCCSetup/step" };
#elif defined(__GNUC__) || defined(__clang__)
    params->Plugin.AddPlugin({ "libncti_command.so" });
    params->Plugin.AddPlugin({ "libncti_occ_plugin.so" });
    //params->Plugin.AddPlugin({ "libncti_render_vulkan.so" });
#endif
    params->Renderer.OperatingAxis = true;
    params->Model.BackgroundColor0 = ParamsColor(5, 38, 79);
    params->Model.BackgroundColor1 = ParamsColor(81, 90, 146);
    params->Model.FaceColor = ParamsColor(145, 158, 186);

    params->Model.BackColor = ParamsColor(145, 158, 186);
    params->Model.EdgeColor = ParamsColor(0, 0, 0);
    params->Model.VertexColor = ParamsColor(248, 203, 22);
    params->Model.HighlightColor = ParamsColor(245, 128, 15);
}

} // namespace NCTI