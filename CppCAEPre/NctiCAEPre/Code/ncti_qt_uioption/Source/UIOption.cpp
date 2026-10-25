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

#include "UIOption.h"

#include <fstream>

#include <QObject>
#include <QCoreApplication>
#include <QStandardPaths>
#include <QDir>
#include <QDebug>

namespace NCTI {

const static QString uiVersion = "v0.12";

std::string UIOption::GetTabName(UIPageType type)
{
    switch (type) {
    case NCTI::UI_FILE: return "file";
    case NCTI::UI_GENERAL: return "general";
    case NCTI::UI_ASSEMBLY: return "assembly";
    case NCTI::UI_SKETCH: return "sketch";
    case NCTI::UI_GEOMETRY: return "geometry";
    case NCTI::UI_AI: return "ai";
    case NCTI::UI_SIMULATION: return "simulation";
    case NCTI::UI_CUSTOM: return "custom";
    default: break;
    }
    return "unknown";
}

static QString getOptionDir()
{
    // 获取%APPDATA%对应的目录（Roaming目录）
    QString appDataPath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QString dataDir = QDir(appDataPath).filePath("data");
    if (!QDir().mkpath(dataDir)) {
        qWarning() << "Cannot create data directory:" << dataDir;
        return QString{};
    }
    return QDir(dataDir).filePath("uioption");
}

static UIPage createFilePage()
{
    UIPage uiFilePage;
    uiFilePage.object_name = UIOption::GetTabName(UI_FILE);
    
    UIPanel* uiAssembly = uiFilePage.newPanel("assemblyPanel", "assemblyPanel");
    uiAssembly->newActionToPanel("创建装配", "new_assembly", ":/images/file/new_assembly.svg", "newAssembly");
    uiAssembly->newActionToPanel("创建零件", "new_part", ":/images/file/new_part.svg", "newPart");
    uiAssembly->newActionToPanel("添加装配", "add_assembly", ":/images/file/add_assembly.svg", "addAssembly");
    uiAssembly->newActionToPanel("添加零件", "add_part", ":/images/file/add_part.svg", "addPart");
    uiAssembly->newActionToPanel("导入零件", "import_part", ":/images/file/import_part.svg", "importAssemblyOrPart");
    uiAssembly->newActionToPanel("删除零件", "delete_part", ":/images/file/delete_part.svg", "removeAssemblyOrPart");

    UIPanel* uiFile = uiFilePage.newPanel("filePanel", "filePanel");
    uiFile->newActionToPanel("打开", "open", ":/images/file/open.svg", "openNcti");
    uiFile->newActionToPanel("保存", "save", ":/images/file/save.svg", "saveNcti");
    uiFile->newActionToPanel("另存为", "saveas", ":/images/file/saveas.svg", "saveAsNcti");
    uiFile->newActionToPanel("关闭文档", "close", ":/images/file/close.svg", "closeDocument");

    UIPanel* uiImport = uiFilePage.newPanel("importPanel", "importPanel");
    uiImport->newActionToPanel("导入", "import", ":/images/file/import.svg", "importModel");
    uiImport->newActionToPanel("导出", "export", ":/images/file/export.svg", "exportModel");

    UIPanel* uiRedo = uiFilePage.newPanel("redoPanel", "redoPanel");
    uiRedo->newActionToPanel("撤销", "undo", ":/images/file/undo.svg", "undo");
    uiRedo->newActionToPanel("重做", "redo", ":/images/file/redo.svg", "redo");

    UIPanel* uiDelete = uiFilePage.newPanel("deletePanel", "deletePanel");
    uiDelete->newActionToPanel("删除", "delete", ":/images/file/delete.svg", "deleteObject");

    UIPanel* uiScriptPanel = uiFilePage.newPanel("scriptPanel", "scriptPanel");
    auto scriptRun = uiScriptPanel->newActionToPanel("脚本运行", "script_run", ":/images/file/script_run.svg");
    scriptRun->newAction("执行脚本", "normal_run", ":/images/file/script_run.svg", "scriptRun");
    scriptRun->newAction("执行装配体脚本", "assembly_run", ":/images/file/script_run.svg", "batchScriptRun");
    scriptRun->newAction("执行多文档脚本", "multi_doc_run", ":/images/file/script_run.svg", "multicoreBatchScriptRun");
    scriptRun->width = 70;

    uiScriptPanel->newActionToPanel("编辑器", "script_editor", ":/images/file/script_editor.svg", "scriptEdit");
    uiScriptPanel->newActionToPanel("控制台", "console", ":/images/file/console.svg", "console");

    UIPanel* uiObjTreePanel = uiFilePage.newPanel("objTreePanel", "objTreePanel");
    uiObjTreePanel->newActionToPanel("对象树", "object_tree", ":/images/file/object_tree.svg", "objectTree");

    return uiFilePage;
}

static UIPage createGeneralPage()
{
    UIPage uiGeneral;
    uiGeneral.object_name = UIOption::GetTabName(UI_GENERAL);
    
    UIPanel* uiShow = uiGeneral.newPanel("showPanel", "showPanel");
    uiShow->newActionToPanel("显示", "show_all_model", ":/images/view/show_all_model.svg", "showAll");
    uiShow->newActionToPanel("隐藏", "hide_select_model", ":/images/view/hide_select_model.svg", "hideSel");
    uiShow->newActionToPanel("独显", "show_select_model", ":/images/view/show_select_model.svg", "showSel");

    UIPanel* uiSixView = uiGeneral.newPanel("sixViewPanel", "sixViewPanel");
    UIGroup* sixViewGroup = uiSixView->newGroupToPanel();
    sixViewGroup->AddGroupItem(UIGroupItem{ "", "xplus", ":/images/view/xplus.svg", "setView" });
    sixViewGroup->AddGroupItem(UIGroupItem{ "", "xminus", ":/images/view/xminus.svg", "setView" });
    sixViewGroup->AddGroupItem(UIGroupItem{ "", "yplus", ":/images/view/yplus.svg", "setView" });
    sixViewGroup->AddGroupItem(UIGroupItem{ "", "yminus", ":/images/view/yminus.svg", "setView" });
    sixViewGroup->AddGroupItem(UIGroupItem{ "", "zplus", ":/images/view/zplus.svg", "setView" });
    sixViewGroup->AddGroupItem(UIGroupItem{ "", "zminus", ":/images/view/zminus.svg", "setView" });

    UIPanel* uiViewCtrl = uiGeneral.newPanel("viewCtrlPanel", "viewCtrlPanel");
    uiViewCtrl->newActionToPanel("西南视图", "isometric", ":/images/view/isometric.svg", "isometricView");
    uiViewCtrl->newActionToPanel("聚焦", "location", ":/images/view/location.svg", "zoomAll");
    uiViewCtrl->newActionToPanel("最大化", "zoom", ":/images/view/zoom.svg", "maxView");
    uiViewCtrl->newActionToPanel("VTK视图", "vtk_view", ":/images/file/console.svg", "addVtkView");
    uiViewCtrl->newActionToPanel("Vulkan视图", "vulkan_view", ":/images/file/console.svg", "addVulkanView");

    UIPanel* uiViewMode = uiGeneral.newPanel("viewModePanel", "viewModePanel");
    UIActionGroup* viewModeActionGroup = uiViewMode->newActionGroupToPanel(2, 2, "ribbon_group_visualMode",
        "显示模式", "title_visualMode", ":/images/view/display_mode.svg", "check_box");
    viewModeActionGroup->AddGroupItem(UIActionGroupItem{ 1, 1, "体", "visual_body", "visualMode" });
    viewModeActionGroup->AddGroupItem(UIActionGroupItem{ 1, 2, "面", "visual_face", "visualMode" });
    viewModeActionGroup->AddGroupItem(UIActionGroupItem{ 2, 1, "线", "visual_edge", "visualMode" });
    viewModeActionGroup->AddGroupItem(UIActionGroupItem{ 2, 2, "点", "visual_vertex", "visualMode" });

    UIPanel* uiSelectMode = uiGeneral.newPanel("selectModePanel", "selectModePanel");
    UIActionGroup* selectModeActionGroup = uiSelectMode->newActionGroupToPanel(2, 2, "ribbon_group_selectMode",
        "选择模式", "title_selectMode", ":/images/view/selection_mode.svg", "check_box");
    selectModeActionGroup->AddGroupItem(UIActionGroupItem{ 1, 1, "体", "select_body", "selectMode" });
    selectModeActionGroup->AddGroupItem(UIActionGroupItem{ 1, 2, "面", "select_face", "selectMode" });
    selectModeActionGroup->AddGroupItem(UIActionGroupItem{ 2, 1, "线", "select_edge", "selectMode" });
    selectModeActionGroup->AddGroupItem(UIActionGroupItem{ 2, 2, "点", "select_vertex", "selectMode" });
    uiSelectMode->newActionToPanel("全选", "select_all", ":/images/view/select_all.svg", "selectAll");

    UIPanel* uiSetting = uiGeneral.newPanel("settingPanel", "settingPanel");
    uiSetting->newActionToPanel("选项卡", "option", ":/images/general/option.svg", "onOptions");

    return uiGeneral;
}


static UIPage createAssemblyPage()
{
    UIPage uiAssembly;
    uiAssembly.object_name = UIOption::GetTabName(UI_ASSEMBLY);

    UIPanel* uiConstraint = uiAssembly.newPanel("constraintPanel", "constraintPanel");
    uiConstraint->newActionToPanel("固定", "cons_fix", ":/images/assembly/fix.svg", "consFix");
    uiConstraint->newActionToPanel("重合", "cons_coincident", ":/images/assembly/coincident.svg", "consCoincident");
    uiConstraint->newActionToPanel("平行", "cons_parallel", ":/images/assembly/parallel.svg", "consParallel");
    uiConstraint->newActionToPanel("同心", "cons_concentric", ":/images/assembly/concentric.svg", "consConcentric");
    uiConstraint->newActionToPanel("垂直", "cons_perpendicular", ":/images/assembly/perpendicular.svg", "consPerpendicular");
    uiConstraint->newActionToPanel("距离", "cons_distance", ":/images/assembly/distance.svg", "consDistance");
    uiConstraint->newActionToPanel("角度", "cons_angle", ":/images/assembly/angle.svg", "consAngle");
    uiConstraint->newActionToPanel("等距", "cons_equal_distance", ":/images/assembly/equal_distance.svg", "consEqualDistance");

    UIPanel* uiExport = uiAssembly.newPanel("exportPanel", "exportPanel");
    uiExport->newActionToPanel("导出脚本", "ass_export", ":/images/file/export.svg", "assExport");

    return uiAssembly;
}

static UIPage createSketchPage()
{
    UIPage uiSketch;
    uiSketch.object_name = UIOption::GetTabName(UI_SKETCH);

    UIPanel* uiDraftCommon = uiSketch.newPanel("draftCommonPanel", "draftCommonPanel");
    uiDraftCommon->newActionToPanel("新建草图", "draft_new", ":/images/sketch/new.svg", "draftNew");
    uiDraftCommon->newActionToPanel("进入草图", "draft_edit", ":/images/sketch/edit.svg", "draftEdit");
    uiDraftCommon->newActionToPanel("坐标系", "draft_coord", ":/images/sketch/coord.svg", "draftCoord");
    uiDraftCommon->newActionToPanel("删除草图", "draft_delete", ":/images/sketch/coord.svg", "deleteDraft");

    UIPanel* uiDraftGeo = uiSketch.newPanel("draftGeoPanel", "draftGeoPanel");
    uiDraftGeo->newActionToPanel("矩形", "draft_rectangle", ":/images/sketch/rectangle.svg", "draftRectangle");
    uiDraftGeo->newActionToPanel("圆", "draft_circle", ":/images/sketch/circle.svg", "draftCircle");
    uiDraftGeo->newActionToPanel("多边形", "draft_polygon", ":/images/sketch/polygon.svg", "draftPolygon");
    uiDraftGeo->newActionToPanel("椭圆", "draft_ellipse", ":/images/sketch/ellipse.svg", "draftEllipse");
    uiDraftGeo->newActionToPanel("连接两圆", "draft_circle_to_circle", ":/images/sketch/circle_to_circle.svg", "draftCircleToCircle");
    uiDraftGeo->newActionToPanel("直线", "draft_line", ":/images/sketch/line.svg", "draftLine");
    uiDraftGeo->newActionToPanel("圆弧", "draft_arc", ":/images/sketch/arc.svg", "draftArc");
    uiDraftGeo->newActionToPanel("多段线", "draft_wire", ":/images/sketch/wire.svg", "draftWire");
    uiDraftGeo->newActionToPanel("样条线", "draft_bspline", ":/images/sketch/bspline.svg", "draftBspline");
    uiDraftGeo->newActionToPanel("中心线", "draft_centerline", ":/images/sketch/centerline.svg", "draftCenterline");
    uiDraftGeo->newActionToPanel("点", "draft_point", ":/images/sketch/point.svg", "draftPoint");

    UIPanel* uiDraftOperation = uiSketch.newPanel("draftOperationPanel", "draftOperationPanel");
    uiDraftOperation->newActionToPanel("到顶部", "move_to_top", ":/images/sketch/move_to_top.svg", "draftMoveToTop");
    uiDraftOperation->newActionToPanel("到末端", "move_to_bottom", ":/images/sketch/move_to_bottom.svg", "draftMoveToBottom");
    uiDraftOperation->newActionToPanel("向上移", "upside", ":/images/sketch/upside.svg", "draftUpside");
    uiDraftOperation->newActionToPanel("向下移", "downside", ":/images/sketch/downside.svg", "draftDownside");
    uiDraftOperation->newActionToPanel("合并", "bunit", ":/images/sketch/bunit.svg", "draftUnit");
    uiDraftOperation->newActionToPanel("修剪", "bcut", ":/images/sketch/bcut.svg", "draftCut");
    uiDraftOperation->newActionToPanel("构面", "implode", ":/images/sketch/implode.svg", "draftImplode");
    uiDraftOperation->newActionToPanel("拆分", "explode", ":/images/sketch/explode.svg", "draftExplode");

    UIPanel* uiDraftView = uiSketch.newPanel("draftViewPanel", "draftViewPanel");
    uiDraftView->newActionToPanel("重置视图", "reset_view", ":/images/sketch/reset_view.svg", "draftResetView");
    uiDraftView->newActionToPanel("退出", "exit", ":/images/sketch/exit.svg", "draftExit");

    UIPanel* uiDraftBodyOperation = uiSketch.newPanel("draftBodyOperationPanel", "draftBodyOperationPanel");
    uiDraftBodyOperation->newActionToPanel("拉伸特征", "extrude", ":/images/sketch/extrude.svg", "draftExtrude");
    uiDraftBodyOperation->newActionToPanel("旋转特征", "rotate", ":/images/sketch/rotate.svg", "draftRotate");
    uiDraftBodyOperation->newActionToPanel("切换布尔", "boolMode", ":/images/sketch/extrude.svg", "draftFeatureBoolean");

    UIPanel* uiDraftRebuild = uiSketch.newPanel("draftRebuildPanel", "draftRebuildPanel");
    uiDraftRebuild->newActionToPanel("重建草图", "rebuild", ":/images/sketch/rebuild.svg", "draftRebuild");
    uiDraftRebuild->newActionToPanel("生成模型", "modelization", ":/images/sketch/modelization.svg", "draftModelization");

    return uiSketch;
}

static UIPage createGeometryPage()
{
    UIPage uiGeometry;
    uiGeometry.object_name = UIOption::GetTabName(UI_GEOMETRY);

    UIPanel* uiGeoModel = uiGeometry.newPanel("geoModelPanel", "geoModelPanel");
    uiGeoModel->newActionToPanel("长方体", "box", ":/images/geometry/box.svg", "executeBox");
    uiGeoModel->newActionToPanel("圆柱体", "cylinder", ":/images/geometry/cylinder.svg", "executeCylinder");

    UIPanel* uiGeoFeature = uiGeometry.newPanel("geoFeaturePanel", "geoFeaturePanel");
    uiGeoFeature->newActionToPanel("布尔", "boolean", ":/images/geometry/boolean.svg", "executeBoolean");
    uiGeoFeature->newActionToPanel("圆角", "fillet", ":/images/geometry/fillet.svg", "executeFillet");
    uiGeoFeature->newActionToPanel("斜角", "chamfer", ":/images/geometry/chamfer.svg", "executeChamfer");
    uiGeoFeature->newActionToPanel("平移", "pan", ":/images/geometry/pan.svg", "geoPan");
    uiGeoFeature->newActionToPanel("缩放", "zoom", ":/images/geometry/zoom.svg", "geoZoom");
    uiGeoFeature->newActionToPanel("旋转", "rotate", ":/images/geometry/rotate.svg", "geoRotate");

    UIPanel* uiGeoModelOp = uiGeometry.newPanel("geoModelOpPanel", "geoModelOpPanel");
    uiGeoModelOp->newActionToPanel("移除特征", "remove_features", ":/images/geometry/remove_features.svg", "removeFeature");
    uiGeoModelOp->newActionToPanel("移除面", "removing_faces", ":/images/geometry/removing_faces.svg", "removeFace");
    uiGeoModelOp->newActionToPanel("抽取要素", "extract_cell", ":/images/geometry/extract_cell.svg", "executeExtractSubObj");
    uiGeoModelOp->newActionToPanel("填充内环", "fill_loop", ":/images/geometry/fill_loop.svg", "executeFillLoop");
    uiGeoModelOp->newActionToPanel("组合", "create_compound", ":/images/geometry/create_compound.svg", "executeCompound");
    uiGeoModelOp->newActionToPanel("分解", "explode_body", ":/images/geometry/explode_body.svg", "executeExplodeBody");
    uiGeoModelOp->newActionToPanel("缝合", "sewing_bodies", ":/images/geometry/sewing_bodies.svg", "executeSewing");
    uiGeoModelOp->newActionToPanel("分离面", "separating_surface", ":/images/geometry/separating_surface.svg", "executeSeparatFace");
    uiGeoModelOp->newActionToPanel("拉伸", "extrude", ":/images/geometry/extrude.svg", "createExtendFace");
    uiGeoModelOp->newActionToPanel("直线阵列", "linear_array", ":/images/geometry/linear_array.svg", "linearArray");
    uiGeoModelOp->newActionToPanel("旋转阵列", "rotate_array", ":/images/geometry/rotate_array.svg", "rotateArray");
    uiGeoModelOp->newActionToPanel("曲线阵列", "curve_array", ":/images/geometry/curve_array.svg", "curveArray");
    uiGeoModelOp->newActionToPanel("曲线偏移", "curve_offset", ":/images/geometry/curve_offset.svg", "curveOffset");

    return uiGeometry;
}

static UIPage createSimulationPage()
{
    UIPage uiSimulation;
    uiSimulation.object_name = UIOption::GetTabName(UI_SIMULATION);

    UIPanel* uiSimMesh = uiSimulation.newPanel("simMeshPanel", "simMeshPanel");
    uiSimMesh->newActionToPanel("面网格", "create_surface_mesh", ":/images/simulation/create_surface_mesh.svg", "meshFromSurface");
    uiSimMesh->newActionToPanel("体网格", "create_volume_mesh", ":/images/simulation/create_volume_mesh.svg", "meshFromVolume");
    uiSimMesh->newActionToPanel("网格质量", "show_mesh_quality", ":/images/simulation/create_volume_mesh.svg", "meshShowMeshQuality");

    UIPanel* uiSimForce = uiSimulation.newPanel("simForcePanel", "simForcePanel");
    uiSimForce->newActionToPanel("集中力", "mesh_add_force", ":/images/simulation/mesh_add_force.svg", "meshAddForce");

    UIPanel* uiSimSpc = uiSimulation.newPanel("simSpcPanel", "simSpcPanel");
    uiSimSpc->newActionToPanel("单点约束", "mesh_add_spc", ":/images/simulation/mesh_add_spc.svg", "meshAddSpc");

    UIPanel* uiSimMat = uiSimulation.newPanel("simMatPanel", "simMatPanel");
    uiSimMat->newActionToPanel("材料属性", "mesh_add_mat", ":/images/simulation/mesh_add_mat.svg", "meshAddMat");

    UIPanel* uiSimSelect = uiSimulation.newPanel("simSelectPanel", "simSelectPanel");
    UIActionGroup* gridSelectGroup = uiSimSelect->newActionGroupToPanel(2, 3, "ribbon_group_grid_selectMode",
        "网格拾取", "title_grid_selectMode", ":/images/view/selection_mode.svg", "radio_button");
    gridSelectGroup->AddGroupItem(UIActionGroupItem{ 1, 1, "几何", "grid_geo", "meshGridSelect" });
    gridSelectGroup->AddGroupItem(UIActionGroupItem{ 1, 2, "节点", "grid_node", "meshGridSelect" });
    gridSelectGroup->AddGroupItem(UIActionGroupItem{ 1, 3, "单元", "grid_unit", "meshGridSelect" });
    gridSelectGroup->AddGroupItem(UIActionGroupItem{ 2, 1, "单元面", "grid_unit_face", "meshGridSelect" });
    gridSelectGroup->AddGroupItem(UIActionGroupItem{ 2, 2, "单元边", "grid_unit_edge", "meshGridSelect" });

    UIPanel* uiSimUtil = uiSimulation.newPanel("simUtilPanel", "simUtilPanel");
    uiSimUtil->newActionToPanel("快速选择", "mesh_quick_select", ":/images/simulation/mesh_add_mat.svg", "meshQuickSelect");
    uiSimUtil->newActionToPanel("切换引擎", "mesh_modify_mesh_type", ":/images/view/selection_mode.svg", "meshModifyMeshType");

    return uiSimulation;
}

static UIPage createAIPage()
{
    UIPage uiAI;
    uiAI.object_name = UIOption::GetTabName(UI_AI);

    UIPanel* uiIdentifierPanel = uiAI.newPanel("aiIdentifierPanel", "aiIdentifierPanel");
    uiIdentifierPanel->newActionToPanel("特征标识", "feature_identifier", ":/images/ai/feature_identifier.png", "featureIdentifier");
    uiIdentifierPanel->newActionToPanel("特征列表", "feature_list", ":/images/ai/feature_list.png", "featureList");
    uiIdentifierPanel->newActionToPanel("圆角标识", "fillet_identifier", ":/images/ai/fillet_identifier.png", "filletIdentifier");
    uiIdentifierPanel->newActionToPanel("孔标识", "hole_identifier", ":/images/ai/hole_identifier.png", "holeIdentifier");
    uiIdentifierPanel->newActionToPanel("Logo标识", "logo_identifier", ":/images/ai/logo_identifier.png", "logoIdentifier");

    UIPanel* uiDraftGeo = uiAI.newPanel("aiExtractPanel", "aiExtractPanel");
    uiDraftGeo->newActionToPanel("提取圆角", "extract_fillet", ":/images/ai/extract_fillet.png", "filletExtract");
    uiDraftGeo->newActionToPanel("提取孔", "extract_hole", ":/images/ai/extract_hole.png", "holeExtract");
    uiDraftGeo->newActionToPanel("提取Logo", "extract_logo", ":/images/ai/extract_logo.png", "logoExtract");

    UIPanel* uiDraftOperation = uiAI.newPanel("aiReasoningPanel", "aiReasoningPanel");
    uiDraftOperation->newActionToPanel("圆角推理", "fillet_reasoning", ":/images/ai/fillet_reasoning.png", "roundRecognition");
    uiDraftOperation->newActionToPanel("倒角推理", "chamfer_reasoning", ":/images/ai/chamfer_reasoning.png", "chamferRecognition");
    uiDraftOperation->newActionToPanel("圆通孔推理", "hole_reasoning", ":/images/ai/hole_reasoning.png", "throughHoleRecognition");

    UIPanel* uiDraftView = uiAI.newPanel("aiShowPanel", "aiShowPanel");
    uiDraftView->newActionToPanel("图结构", "show_graph_structure", ":/images/ai/show_graph_structure.png", "topoStructure");
    uiDraftView->newActionToPanel("边属性", "show_edge_properties", ":/images/ai/show_edge_properties.png", "edgeAttribute");
    uiDraftView->newActionToPanel("面属性", "show_face_properties", ":/images/ai/show_face_properties.png", "faceAttribute");
    uiDraftView->newActionToPanel("UV网格", "show_uv_mesh", ":/images/ai/show_uv_mesh.png", "uvGrid");
    uiDraftView->newActionToPanel("导出关联面", "fill_loop", ":/images/ai/fill_loop.png", "exportLinkFace");

    return uiAI;
}

static UIPage createCustomPage()
{
    UIPage uiCustom;
    uiCustom.object_name = UIOption::GetTabName(UI_CUSTOM);
    
    UIPanel* uiCustomConfig = uiCustom.newPanel("customConfigPanel", "customConfigPanel");
    uiCustomConfig->newActionToPanel("命令设置", "customSetting", ":/images/common/setting.svg", "openCustomSetting");
    //uiCustomConfig->newActionToPanel("UI配置", "uiOption", ":/images/custom/icon20.svg", "openUIOption");

    UIPanel* uiCustomAdd = uiCustom.newPanel("customAddPanel", "customAddPanel");
    return uiCustom;
}

UIOption::UIOption()
{
    initDefaultUIOption();
}

UIOption::~UIOption()
{
}

void UIOption::initDefaultUIOption()
{
    mDefaultUIRibbon.tabs.clear();
    mDefaultUIRibbon.logo = ":/App/app.png";
    mDefaultUIRibbon.title = "CAE前处理通用架构集成平台";
    mDefaultUIRibbon.version = std::string(uiVersion.toUtf8());
    mDefaultUIRibbon.AddTab("文件", "file", true);
    mDefaultUIRibbon.AddTab("常规", "general", true);
    mDefaultUIRibbon.AddTab("装配", "assembly", true);
    mDefaultUIRibbon.AddTab("草图", "sketch", true);
    mDefaultUIRibbon.AddTab("几何", "geometry", true);
    mDefaultUIRibbon.AddTab("仿真", "simulation", true);
    mDefaultUIRibbon.AddTab("我的", "custom", true);
    mDefaultUIRibbon.AddTab("AI", "ai", false);

    // 创建各个页面并保存到默认UI页面集合中
    mDefaultUIPages.emplace("file", createFilePage());
    mDefaultUIPages.emplace("general", createGeneralPage());
    mDefaultUIPages.emplace("assembly", createAssemblyPage());
    mDefaultUIPages.emplace("sketch", createSketchPage());
    mDefaultUIPages.emplace("geometry", createGeometryPage());
    mDefaultUIPages.emplace("simulation", createSimulationPage());
    mDefaultUIPages.emplace("custom", createCustomPage());
    mDefaultUIPages.emplace("ai", createAIPage());
}

bool UIOption::isVersionUpdated(const std::string& version)
{
    return QString::fromUtf8(version.c_str()) != uiVersion;
}

bool UIOption::LoadUIOption()
{
    mUIRibbon.tabs.clear();

    QString uiUserOptionPath = getUIOptionPath();
    QFileInfo fileInfo(uiUserOptionPath);
    bool isFileExist = fileInfo.exists();
    if (isFileExist) { 
        mUIRibbon = loadUIOption(uiUserOptionPath); 
    }

    if (!isFileExist || isVersionUpdated(mUIRibbon.version)) {
        // 文件不存在或版本不匹配时，使用默认配置文件
        if (!SaveUIOption(mDefaultUIRibbon) || !SaveUIPages(mDefaultUIPages)) {
            return false;
        }
        // 再次加载
        mUIRibbon = loadUIOption(uiUserOptionPath);
    }

    std::sort(mUIRibbon.tabs.begin(), mUIRibbon.tabs.end(), [](const UITabDetail& a, const UITabDetail& b) {
        return a.index < b.index;
    });
    
    return !mUIRibbon.tabs.empty();
}

UIRibbon UIOption::loadUIOption(const QString& jsonPath) const
{
    UIRibbon uiRibbon;

    QFile file(jsonPath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Cannot open JSON file:" << jsonPath;
        return uiRibbon;
    }
    QByteArray jsonData = file.readAll();
    file.close();

    try {
        json j = json::parse(jsonData.constData());
        uiRibbon = j.get<UIRibbon>();
    }
    catch (const json::parse_error& e) {
        qWarning() << "json parse error: " << e.what();
    }
    catch (const std::exception& e) {
        qWarning() << "std::exception: " << e.what();
    }
    return uiRibbon;
}

QString NCTI::UIOption::getUIOptionPath()
{
    QString dataDir = getOptionDir();
    QString uiOptionPath = QStringLiteral("%1/uioption.json").arg(uiVersion);
    return QDir(dataDir).filePath(uiOptionPath);
}

QString NCTI::UIOption::getUIDetailPath(const std::string& objectName)
{
    QString dataDir = getOptionDir();
    QString uiDetailPath = QStringLiteral("%1/%2.json").arg(uiVersion, QString::fromUtf8(objectName.c_str()));
    return QDir(dataDir).filePath(uiDetailPath);
}

QString UIOption::getJsonPath(const std::string& objectName, bool bCheckExists)
{
    QString uiDetailPath = getUIDetailPath(objectName);
    QFileInfo fileInfo(uiDetailPath);
    if (bCheckExists && !fileInfo.exists()) { return {}; }
    return uiDetailPath;
}

UIOption& UIOption::GetInst()
{
    static UIOption instance;
    return instance;
}

UIPage UIOption::LoadUIPage(const std::string& objectName, bool bDefault)
{
    if (bDefault) {
        auto it = mDefaultUIPages.find(objectName);
        if (it != mDefaultUIPages.end()) {
            return it->second;
        }
        return UIPage();
    }
    return loadUIPage(getJsonPath(objectName));
}

UIPage UIOption::loadUIPage(const QString& jsonPath)
{
    if (jsonPath.isEmpty()) { return UIPage(); }

    UIPage uiPage;

    QFile file(jsonPath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Cannot open JSON file:" << jsonPath;
        return uiPage;
    }

    QByteArray jsonData = file.readAll();
    file.close();

    try {
        json j = json::parse(jsonData.constData());
        uiPage = j.get<UIPage>();
    }
    catch (const json::parse_error& e) {
        qWarning() << "json parse error: " << e.what();
    }
    catch (const std::exception& e) {
        qWarning() << "std::exception: " << e.what();
    }
    return uiPage;
}

QString UIOption::GetLogo()
{
    return QString::fromUtf8(mUIRibbon.logo.c_str());
}

QString UIOption::GetTitle()
{
    return QString::fromUtf8(mUIRibbon.title.c_str());
}

QString UIOption::GetVersion()
{
    return uiVersion;
}

std::vector<UITabDetail> UIOption::GetTabs(UIOptionType type)
{
    if (type == UIOptionType::Default) {
        return mDefaultUIRibbon.tabs;
    }

    QString uiOptionPath = getUIOptionPath();
    QFileInfo fileInfo(uiOptionPath);
    if (!fileInfo.exists()) { 
        return std::vector<UITabDetail>(); 
    }

    UIRibbon uiRibbon = loadUIOption(uiOptionPath);
    return uiRibbon.tabs;
}

QStringList UIOption::GetUIOptionFiles()
{
    QStringList uiOptionFiles;
    QString uiOptionPath = getUIOptionPath();
    uiOptionFiles << uiOptionPath;

    UIRibbon uiRibbon = loadUIOption(uiOptionPath);
    for (const auto& v : uiRibbon.tabs) {
        uiOptionFiles << getJsonPath(v.object_name);
    }
    return uiOptionFiles;
}

UIRibbon UIOption::GetUIRibbon() const
{
    return mUIRibbon;
}

bool UIOption::SaveUIOption(const UIRibbon& uiRibbon)
{
    QString uiOptionPath = getUIOptionPath();
    QFileInfo fileInfo(uiOptionPath);
    QDir dir = fileInfo.dir();
    if (!dir.exists()) {
        bool success = dir.mkpath(".");
        if (!success) {
            qWarning() << "Failed to create directory: " << dir.path();
            return false;
        }
    }

    try {
        json j = uiRibbon;
        std::ofstream file(uiOptionPath.toUtf8());
        file << j.dump(4);
    }
    catch (const std::exception& e) {
        qWarning() << "Error: " << e.what();
        return false;
    }
    return true;
}

bool UIOption::SaveUIPages(const std::unordered_map<std::string, UIPage>& uiPages)
{
    for (const auto& [objectName, uiPage] : uiPages) {
        QString savePath = getJsonPath(objectName, false);
        try {
            json j = uiPage;
            std::ofstream file(savePath.toUtf8());
            file << j.dump(4);
        }
        catch (const std::exception& e) {
            qWarning() << "Error: " << e.what();
            return false;
        }
    }
    return true;
}

} // namespace NCTI