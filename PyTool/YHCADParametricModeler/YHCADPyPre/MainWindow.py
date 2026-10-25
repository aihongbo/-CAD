#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Copyright (c) 2025 粤港澳大湾区（广东）国创中心
YHCADPyPre is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details.
"""
from Pub.configLoad import global_scope
import wx
import wx.ribbon as RB
import wx.aui as aui
import wx.stc as stc
from View.RenderView import RenderView
from View.EditorView import EditorView
from View.LogView import LogView
from View.ObjectTreeView import ObjectTreeView

import Function.onCataegoryModel as onCataegoryModel
import Function.onCataegoryFile as onCataegoryFile
import Function.onCataegorySketch as onCataegorySketch
import Function.onCataegoryView as onCataegoryView
import Function.onCataegoryGeometry as onCataegoryGeometry
from functools import partial
from Pub.ImageTransfrom import svg2bmp
from Pub.ribbonTheme import apply_ribbon_theme
from View.FormDialog import InputDialog
from View.FeatrueTreeDlg import InputFeatureTreeDlg
from View.MeshDlg import MeshDialog

class MainWindow(wx.Frame):
    def __init__(self,runtime_path):
        super().__init__(None, title='python炎核CAD', size=(1600, 1000))
        if False == self._init_CAD_Env():
            return
        self.m_runtime_path = runtime_path
        self._init_views()
        self._init_mode()
        self.Center()
        self.NCTI.SetPyInputDialogCallback(InputDialog)
        self.NCTI.SetPyCustomDialogCallbackFun(InputFeatureTreeDlg)
        self.NCTI.SetPyMeshSettingCallbackFun(MeshDialog)
        self.Bind(wx.EVT_CLOSE, self.on_window_close)

    def on_window_close(self, event=None):
        """不等待底层文档命令，直接退出 Python 主窗口。"""
        self.activeSketch = None
        self.yh_doc = None
        self.Hide()
        self.Destroy()
        app = wx.GetApp()
        if app is not None:
            app.ExitMainLoop()

    def _initRibbon(self):
        self.ribbon = RB.RibbonBar(self, style=RB.RIBBON_BAR_DEFAULT_STYLE)
        apply_ribbon_theme(self.ribbon)
        self._initRibbonPageFile()
        self._initRibbonPageGeneral()
        self._initRibbonPageSketch()
        self._initRibbonPageView()
        self.ribbon.Realize()
    def _initRibbonPageFile(self):
        filePage = RB.RibbonPage(self.ribbon, label='菜单')
        file_button_size = RB.RIBBON_BUTTONBAR_BUTTON_LARGE

        filePanel = RB.RibbonPanel(filePage, label='文件', style=RB.RIBBON_PANEL_NO_AUTO_MINIMISE)
        fileBar = RB.RibbonButtonBar(filePanel)
        self._add_ribbon_bar_button(fileBar, 'icon/菜单/打开', '打开', '打开文档', onCataegoryFile.on_open_button_click, size_class=file_button_size)
        self._add_ribbon_bar_button(fileBar, 'icon/菜单/保存', '保存', '保存文档', onCataegoryFile.on_save_button_click, size_class=file_button_size)
        self._add_ribbon_bar_button(fileBar, 'icon/菜单/另存为', '另存为', '另存为', onCataegoryFile.on_save_as_button_click, size_class=file_button_size)
        self._add_ribbon_bar_button(fileBar, 'icon/菜单/导入', '导入', '导入文件', onCataegoryFile.importFile, size_class=file_button_size)
        self._add_ribbon_bar_button(fileBar, 'icon/菜单/导出', '导出', '导出文件', onCataegoryFile.on_export_button_click, size_class=file_button_size)

        editPanel = RB.RibbonPanel(filePage, label='编辑', style=RB.RIBBON_PANEL_NO_AUTO_MINIMISE)
        editBar = RB.RibbonButtonBar(editPanel)
        self._add_ribbon_bar_button(editBar, 'icon/菜单/撤销', '撤销', '撤销', onCataegoryFile.on_undo_button_click, size_class=file_button_size)
        self._add_ribbon_bar_button(editBar, 'icon/菜单/重做', '重做', '重做', onCataegoryFile.on_redo_button_click, size_class=file_button_size)
        self._add_ribbon_bar_button(editBar, 'icon/菜单/清空', '清空', '清空文档', onCataegoryFile.on_clear_button_click, size_class=file_button_size)
        self._add_ribbon_bar_button(editBar, 'icon/菜单/关闭文档', '关闭文档', '关闭当前文档', onCataegoryFile.on_close_button_click, size_class=file_button_size)

    def _initRibbonPageGeneral(self):
        filePage = RB.RibbonPage(self.ribbon, label='常规')
        geometry_button_size = RB.RIBBON_BUTTONBAR_BUTTON_LARGE

        construct_panel = RB.RibbonPanel(filePage, label='构造', style=RB.RIBBON_PANEL_NO_AUTO_MINIMISE)
        construct_bar = RB.RibbonButtonBar(construct_panel)
        self._add_ribbon_bar_button(construct_bar, 'icon/常规/基准平面', '基准平面', '创建基准平面', onCataegoryGeometry.on_create_datum_plane, size_class=geometry_button_size)
        self._add_ribbon_bar_button(construct_bar, 'icon/常规/基准坐标系', '基准坐标系', '创建基准坐标系', onCataegoryGeometry.on_create_coordinate_system, size_class=geometry_button_size)
        self._add_ribbon_bar_button(construct_bar, 'icon/常规/创建草图', '创建草图', '点击创建草图', onCataegoryModel.on_create_sketch_button_click, size_class=geometry_button_size)

        basic_panel = RB.RibbonPanel(filePage, label='基本', style=RB.RIBBON_PANEL_NO_AUTO_MINIMISE)
        basic_bar = RB.RibbonButtonBar(basic_panel)
        self._add_ribbon_bar_button(basic_bar, 'icon/常规/拉伸', '拉伸', '根据当前草图创建拉伸特征', onCataegoryModel.on_create_stretch_button_click, size_class=geometry_button_size)
        self._add_ribbon_bar_button(basic_bar, 'icon/常规/旋转', '旋转', '创建旋转特征', onCataegoryGeometry.on_rotate, size_class=geometry_button_size)
        self._add_ribbon_bar_button(basic_bar, 'icon/常规/圆角', '圆角', '创建圆角特征', onCataegoryGeometry.on_fillet, size_class=geometry_button_size)
        self._add_ribbon_bar_button(basic_bar, 'icon/常规/斜角', '斜角', '创建斜角特征', onCataegoryGeometry.on_chamfer, size_class=geometry_button_size)
        self._add_ribbon_hybrid_button(basic_bar, 'icon/常规/旋转阵列', '旋转阵列', '创建旋转阵列', onCataegoryGeometry.on_array_circular, self.on_geometry_array_dropdown, size_class=geometry_button_size)
        # self._add_ribbon_bar_button(basic_bar, 'ribbon/linear_array', '线性阵列', '创建线性阵列', onCataegoryGeometry.on_array_linear, size_class=geometry_button_size)
        self._add_ribbon_bar_button(basic_bar, 'icon/常规/拔模', '拔模', '创建拔模特征', onCataegoryGeometry.on_draft, size_class=geometry_button_size)
        # self._add_ribbon_bar_button(basic_bar, 'ribbon/shelling', '抽壳', '创建抽壳特征', onCataegoryGeometry.on_shelling, size_class=geometry_button_size)

        boolean_panel = RB.RibbonPanel(filePage, label='布尔', style=RB.RIBBON_PANEL_NO_AUTO_MINIMISE)
        boolean_bar = RB.RibbonButtonBar(boolean_panel)
        self._add_ribbon_bar_button(boolean_bar, 'icon/常规/并集', '并集', '布尔并集', onCataegoryGeometry.on_boolean, param='union', size_class=geometry_button_size)
        self._add_ribbon_bar_button(boolean_bar, 'icon/常规/差集', '差集', '布尔差集', onCataegoryGeometry.on_boolean_subtraction, size_class=geometry_button_size)
        self._add_ribbon_bar_button(boolean_bar, 'icon/常规/交集', '交集', '布尔交集', onCataegoryGeometry.on_boolean_intersection, size_class=geometry_button_size)

        primitive_panel = RB.RibbonPanel(filePage, label='基本体', style=RB.RIBBON_PANEL_NO_AUTO_MINIMISE)
        primitive_bar = RB.RibbonButtonBar(primitive_panel)
        self._add_ribbon_bar_button(primitive_bar, 'icon/常规/长方体', '长方体', '创建长方体', onCataegoryGeometry.on_create_box, size_class=geometry_button_size)
        self._add_ribbon_bar_button(primitive_bar, 'icon/常规/圆柱体', '圆柱体', '创建圆柱体', onCataegoryGeometry.on_create_cylinder, size_class=geometry_button_size)
        self._add_ribbon_bar_button(primitive_bar, 'icon/常规/圆锥体', '圆锥体', '创建圆锥体', onCataegoryGeometry.on_create_cone, size_class=geometry_button_size)
        self._add_ribbon_bar_button(primitive_bar, 'icon/常规/球体', '球体', '创建球体', onCataegoryGeometry.on_create_sphere, size_class=geometry_button_size)

    def _initRibbonPageSketch(self):
        filePage = RB.RibbonPage(self.ribbon, label='草图')
        sketch_button_size = RB.RIBBON_BUTTONBAR_BUTTON_LARGE

        asmPanel = RB.RibbonPanel(filePage, label='操作',style=RB.RIBBON_PANEL_NO_AUTO_MINIMISE)
        asmBar = RB.RibbonButtonBar(asmPanel)

        self._add_ribbon_bar_button(asmBar, 'icon/草图/完成草图', '完成草图', '点击完成草图', onCataegoryModel.on_finish_sketch_button_click)

        asmPanel = RB.RibbonPanel(filePage, label='曲线',style=RB.RIBBON_PANEL_NO_AUTO_MINIMISE)
        asmBar = RB.RibbonButtonBar(asmPanel)

        self._add_ribbon_bar_button(asmBar, 'icon/草图/直线', '直线', '创建直线', onCataegorySketch.on_exec_line_button_click, size_class=sketch_button_size)
        self._add_ribbon_bar_button(asmBar, 'icon/草图/点', '点', '创建点', onCataegorySketch.on_exec_point_button_click, size_class=sketch_button_size)
        self._add_ribbon_bar_button(asmBar, 'icon/草图/圆弧', '圆弧', '创建圆弧', onCataegorySketch.on_exec_point_button_arc, size_class=sketch_button_size)
        self._add_ribbon_hybrid_button(asmBar,'icon/草图/圆','圆','创建圆或椭圆',onCataegorySketch.on_exec_point_button_circle,self.on_circle_dropdown, size_class=sketch_button_size)
        self._add_ribbon_hybrid_button(asmBar,'icon/草图/矩形','矩形','创建矩形',onCataegorySketch.on_exec_point_button_rect,self.on_rectangle_dropdown, size_class=sketch_button_size)
        self._add_ribbon_button_menu(asmBar, 'icon/草图/更多曲线', '更多曲线', '更多曲线功能', self.on_more_curve_dropdown)

        asmPanel = RB.RibbonPanel(filePage, label='编辑',style=RB.RIBBON_PANEL_NO_AUTO_MINIMISE)
        asmBar = RB.RibbonButtonBar(asmPanel)

        self._add_ribbon_bar_button(asmBar, 'icon/草图/修剪', '修剪', '曲线修剪', onCataegorySketch.on_exec_edit_button_curveTrimming, size_class=sketch_button_size)
        self._add_ribbon_hybrid_button(asmBar, 'icon/草图/偏移', '偏移', '曲线偏移', onCataegorySketch.on_exec_edit_button_curveOffset, self.on_curveOffset_dropdown, size_class=sketch_button_size)
        self._add_ribbon_button_menu(asmBar, 'icon/草图/更多编辑', '更多编辑', '更多编辑功能', self.on_more_edit_dropdown)

        asmPanel = RB.RibbonPanel(filePage, label='约束',style=RB.RIBBON_PANEL_NO_AUTO_MINIMISE)
        asmBar = RB.RibbonButtonBar(asmPanel)

        self._add_ribbon_bar_button(asmBar, 'icon/草图/竖直', '竖直', '竖直', onCataegorySketch.on_exec_constraint_button_AddConsYAxis, size_class=sketch_button_size)
        self._add_ribbon_bar_button(asmBar, 'icon/草图/水平', '水平', '水平', onCataegorySketch.on_exec_constraint_button_AddConsXAxis, size_class=sketch_button_size)
        self._add_ribbon_bar_button(asmBar, 'icon/草图/平行', '平行', '平行', onCataegorySketch.on_exec_constraint_button_AddConsParallel, size_class=sketch_button_size)
        self._add_ribbon_bar_button(asmBar, 'icon/草图/垂直', '垂直', '垂直', onCataegorySketch.on_exec_constraint_button_AddConsVertical, size_class=sketch_button_size)
        self._add_ribbon_bar_button(asmBar, 'icon/草图/重合', '重合', '重合', onCataegorySketch.on_exec_constraint_button_AddConsCoincide, size_class=sketch_button_size)
        self._add_ribbon_button_menu(asmBar, 'icon/草图/更多约束', '更多约束', '更多约束功能', self.on_all_constraint_dropdown)

        asmPanel = RB.RibbonPanel(filePage, label='显示与求解',style=RB.RIBBON_PANEL_NO_AUTO_MINIMISE)
        asmBar = RB.RibbonButtonBar(asmPanel)
        self._add_ribbon_bar_button(asmBar, 'icon/草图/显示名称', '显示名称', '显示约束名称', onCataegorySketch.on_exec_display_solve_button_SwitchConsDisplay, size_class=sketch_button_size)
        self._add_ribbon_hybrid_button(asmBar, 'icon/草图/显示约束', '显示约束', '显示约束', onCataegorySketch.on_exec_display_solve_button_ShowCons, self.on_show_cons_dropdown, size_class=sketch_button_size)
        self._add_ribbon_bar_button(asmBar, 'icon/草图/重合全显', '重合全显', '重合约束全显', onCataegorySketch.on_exec_display_solve_button_ShowCoincideCons, size_class=sketch_button_size)

        asmPanel = RB.RibbonPanel(filePage, label='求解',style=RB.RIBBON_PANEL_NO_AUTO_MINIMISE)
        asmBar = RB.RibbonButtonBar(asmPanel)
        self._add_ribbon_bar_button(asmBar, 'icon/草图/约束检查', '约束检查', '约束检查', onCataegorySketch.on_exec_solve_button_GetCheckConsResult, size_class=sketch_button_size)
        self._add_ribbon_bar_button(asmBar, 'icon/草图/主动求解', '主动求解', '主动求解', onCataegorySketch.on_exec_solve_button_RunSolve, size_class=sketch_button_size)
        self._add_ribbon_bar_button(asmBar, 'icon/草图/计算区域', '计算区域', '计算区域', onCataegorySketch.on_exec_solve_button_RunCalCloseArea, size_class=sketch_button_size)
        self._add_ribbon_bar_button(asmBar, 'icon/草图/设置强约束', '设置强约束', '设置强约束', onCataegorySketch.on_exec_solve_button_ConsType, size_class=sketch_button_size)
        self._add_ribbon_button_menu(asmBar, 'icon/草图/求解', '求解', '求解功能', self.on_solve_dropdown)

        asmPanel = RB.RibbonPanel(filePage, label='模式',style=RB.RIBBON_PANEL_NO_AUTO_MINIMISE)
        asmBar = RB.RibbonButtonBar(asmPanel)

        self._add_ribbon_bar_button(asmBar, 'icon/草图/直径半径切换', '直径半径切换', '直径半径切换', onCataegorySketch.on_exec_mode_button_SwitchConsRadius, size_class=sketch_button_size)

    def on_circle_dropdown(self, bar, button_id, event=None):
        menu = wx.Menu()

        item_circle = menu.Append(wx.ID_ANY, "圆")
        item_ellipse = menu.Append(wx.ID_ANY, "椭圆")

        self.Bind(wx.EVT_MENU, partial(onCataegorySketch.on_exec_point_button_circle, self), item_circle)
        self.Bind(wx.EVT_MENU, partial(onCataegorySketch.on_exec_point_button_ellipse, self), item_ellipse)

        self.PopupMenu(menu)
        menu.Destroy()
    def on_rectangle_dropdown(self, bar, button_id, event=None):
        menu = wx.Menu()

        item_rect = menu.Append(wx.ID_ANY, "拐角矩形")
        item_center_rect = menu.Append(wx.ID_ANY, "中心矩形")
        item_parallelogram = menu.Append(wx.ID_ANY, "平行四边形")

        self.Bind(wx.EVT_MENU, partial(onCataegorySketch.on_exec_point_button_rect, self), item_rect)
        self.Bind(wx.EVT_MENU, partial(onCataegorySketch.on_exec_point_button_centerRect, self), item_center_rect)
        self.Bind(wx.EVT_MENU, partial(onCataegorySketch.on_exec_point_button_parallelogram, self), item_parallelogram)

        self.PopupMenu(menu)
        menu.Destroy()
    def on_curveOffset_dropdown(self, bar, button_id, event=None):
        menu = wx.Menu()
        
        item_rect = menu.Append(wx.ID_ANY, "单一")
        item_center_rect = menu.Append(wx.ID_ANY, "链")
        item_parallelogram = menu.Append(wx.ID_ANY, "环")

        self.Bind(wx.EVT_MENU, partial(onCataegorySketch.on_exec_edit_button_curveOffset, self, 1), item_rect)
        self.Bind(wx.EVT_MENU, partial(onCataegorySketch.on_exec_edit_button_curveOffset, self, 2), item_center_rect)
        self.Bind(wx.EVT_MENU, partial(onCataegorySketch.on_exec_edit_button_curveOffset, self, 3), item_parallelogram)

        self.PopupMenu(menu)
        menu.Destroy()

    def on_more_curve_dropdown(self, event=None):
        menu = wx.Menu()

        item_ellipse_arc = menu.Append(wx.ID_ANY, "椭圆弧")
        item_polygon = menu.Append(wx.ID_ANY, "多边形")
        item_spline = menu.Append(wx.ID_ANY, "样条")
        item_center_line = menu.Append(wx.ID_ANY, "中心线")

        self.Bind(wx.EVT_MENU, partial(onCataegorySketch.on_exec_point_button_ellipseArc, self), item_ellipse_arc)
        self.Bind(wx.EVT_MENU, partial(onCataegorySketch.on_exec_point_button_regularPolygon, self), item_polygon)
        self.Bind(wx.EVT_MENU, partial(onCataegorySketch.on_exec_point_button_spline, self), item_spline)
        self.Bind(wx.EVT_MENU, partial(onCataegorySketch.on_exec_point_button_centerLine, self), item_center_line)

        self.PopupMenu(menu)
        menu.Destroy()

    def on_more_edit_dropdown(self, event=None):
        menu = wx.Menu()

        item_partition = menu.Append(wx.ID_ANY, "分割")
        item_chamfer = menu.Append(wx.ID_ANY, "斜角")
        item_radius = menu.Append(wx.ID_ANY, "圆角")
        item_tectonic = menu.Append(wx.ID_ANY, "设置构造线")
        item_fixed = menu.Append(wx.ID_ANY, "锁定图元")
        item_remove_cons = menu.Append(wx.ID_ANY, "移除约束")

        self.Bind(wx.EVT_MENU, partial(onCataegorySketch.on_exec_edit_button_partition, self), item_partition)
        self.Bind(wx.EVT_MENU, partial(onCataegorySketch.on_exec_edit_button_curvechamfer, self), item_chamfer)
        self.Bind(wx.EVT_MENU, partial(onCataegorySketch.on_exec_edit_button_curveRadius, self), item_radius)
        self.Bind(wx.EVT_MENU, partial(onCataegorySketch.on_exec_edit_button_tectonicline, self), item_tectonic)
        self.Bind(wx.EVT_MENU, partial(onCataegorySketch.on_exec_edit_button_fixedCons, self), item_fixed)
        self.Bind(wx.EVT_MENU, partial(onCataegorySketch.on_exec_edit_button_removePointCons, self), item_remove_cons)

        self.PopupMenu(menu)
        menu.Destroy()

    def on_all_constraint_dropdown(self, event=None):
        menu = wx.Menu()

        item_equal = menu.Append(wx.ID_ANY, "相等")
        item_tangent = menu.Append(wx.ID_ANY, "相切")
        item_xpos = menu.Append(wx.ID_ANY, "水平尺寸")
        item_ypos = menu.Append(wx.ID_ANY, "竖直尺寸")
        item_radius = menu.Append(wx.ID_ANY, "半径尺寸")
        item_angle = menu.Append(wx.ID_ANY, "角度尺寸")
        item_length = menu.Append(wx.ID_ANY, "长度尺寸")
        item_distance = menu.Append(wx.ID_ANY, "距离尺寸")
        item_lock = menu.Append(wx.ID_ANY, "锁定尺寸")

        self.Bind(wx.EVT_MENU, partial(onCataegorySketch.on_exec_constraint_button_AddConsEqual, self), item_equal)
        self.Bind(wx.EVT_MENU, partial(onCataegorySketch.on_exec_constraint_button_AddConsTangent, self), item_tangent)
        self.Bind(wx.EVT_MENU, partial(onCataegorySketch.on_exec_constraint_button_AddConsXpos, self), item_xpos)
        self.Bind(wx.EVT_MENU, partial(onCataegorySketch.on_exec_constraint_button_AddConsYpos, self), item_ypos)
        self.Bind(wx.EVT_MENU, partial(onCataegorySketch.on_exec_constraint_button_AddConsRadius, self), item_radius)
        self.Bind(wx.EVT_MENU, partial(onCataegorySketch.on_exec_constraint_button_AddConsAngle, self), item_angle)
        self.Bind(wx.EVT_MENU, partial(onCataegorySketch.on_exec_constraint_button_AddConsLength, self), item_length)
        self.Bind(wx.EVT_MENU, partial(onCataegorySketch.on_exec_constraint_button_SketchConsParallel, self), item_distance)
        self.Bind(wx.EVT_MENU, partial(onCataegorySketch.on_exec_constraint_button_LockSize, self), item_lock)

        self.PopupMenu(menu)
        menu.Destroy()

    def on_show_cons_dropdown(self, bar, button_id, event=None):
        menu = wx.Menu()

        item_show = menu.Append(wx.ID_ANY, "显示约束")
        item_show_weak = menu.Append(wx.ID_ANY, "显示弱约束")
        item_show_strong = menu.Append(wx.ID_ANY, "显示强约束")

        self.Bind(wx.EVT_MENU, partial(onCataegorySketch.on_exec_display_solve_button_ShowCons, self), item_show)
        self.Bind(wx.EVT_MENU, partial(onCataegorySketch.on_exec_display_solve_button_ShowWeakCons, self), item_show_weak)
        self.Bind(wx.EVT_MENU, partial(onCataegorySketch.on_exec_display_solve_button_ShowStrongCons, self), item_show_strong)

        self.PopupMenu(menu)
        menu.Destroy()

    def on_solve_dropdown(self, event=None):
        menu = wx.Menu()

        item_auto_solve = menu.AppendCheckItem(wx.ID_ANY, "求解开/关")
        item_auto_area = menu.AppendCheckItem(wx.ID_ANY, "自动计算区域开/关")
        item_auto_free = menu.AppendCheckItem(wx.ID_ANY, "计算弱约束开/关")
        item_auto_snap = menu.Append(wx.ID_ANY, "捕捉添加约束")
        item_check_cons = menu.Append(wx.ID_ANY, "约束检查")

        item_auto_solve.Check(getattr(self, "_sketch_auto_solve_enabled", True))
        item_auto_area.Check(getattr(self, "_sketch_auto_close_area_enabled", True))
        item_auto_free.Check(getattr(self, "_sketch_auto_free_cons_enabled", True))

        self.Bind(wx.EVT_MENU, partial(onCataegorySketch.on_exec_solve_button_AutoSolve, self), item_auto_solve)
        self.Bind(wx.EVT_MENU, partial(onCataegorySketch.on_exec_solve_button_ArgumentAutoSnap, self), item_auto_snap)
        self.Bind(wx.EVT_MENU, partial(onCataegorySketch.on_exec_solve_button_AutoCalCloseArea, self), item_auto_area)
        self.Bind(wx.EVT_MENU, partial(onCataegorySketch.on_exec_solve_button_AutoCalFreeCons, self), item_auto_free)
        self.Bind(wx.EVT_MENU, partial(onCataegorySketch.on_exec_solve_button_GetCheckConsResult, self), item_check_cons)

        self.PopupMenu(menu)
        menu.Destroy()

    def on_geometry_boolean_dropdown(self, bar, button_id, event=None):
        menu = wx.Menu()

        item_union = menu.Append(wx.ID_ANY, "并集")
        item_subtraction = menu.Append(wx.ID_ANY, "差集")
        item_intersection = menu.Append(wx.ID_ANY, "交集")

        self.Bind(wx.EVT_MENU, partial(onCataegoryGeometry.on_boolean, self), item_union)
        self.Bind(wx.EVT_MENU, partial(onCataegoryGeometry.on_boolean_subtraction, self), item_subtraction)
        self.Bind(wx.EVT_MENU, partial(onCataegoryGeometry.on_boolean_intersection, self), item_intersection)

        self.PopupMenu(menu)
        menu.Destroy()

    def on_geometry_array_dropdown(self, bar, button_id, event=None):
        menu = wx.Menu()

        item_linear = menu.Append(wx.ID_ANY, "直线阵列")
        item_circular = menu.Append(wx.ID_ANY, "旋转阵列")

        self.Bind(wx.EVT_MENU, partial(onCataegoryGeometry.on_array_linear, self), item_linear)
        self.Bind(wx.EVT_MENU, partial(onCataegoryGeometry.on_array_circular, self), item_circular)

        self.PopupMenu(menu)
        menu.Destroy()


    def _initRibbonPageView(self):
        filePage = RB.RibbonPage(self.ribbon, label='视图')
        view_button_size = RB.RIBBON_BUTTONBAR_BUTTON_LARGE

        display_panel = RB.RibbonPanel(filePage, label='显示', style=RB.RIBBON_PANEL_NO_AUTO_MINIMISE)
        display_bar = RB.RibbonButtonBar(display_panel)
        self._add_ribbon_bar_button(display_bar, 'icon/视图/全部显示', '全部显示', '全部显示', onCataegoryView.on_display_all, size_class=view_button_size)
        self._add_ribbon_bar_button(display_bar, 'icon/视图/隐藏所选', '隐藏所选', '隐藏当前选择', onCataegoryView.on_hide_selected, size_class=view_button_size)
        self._add_ribbon_bar_button(display_bar, 'icon/视图/仅显所选', '仅显所选', '仅显示当前选择', onCataegoryView.on_showonly_selected, size_class=view_button_size)

        visual_panel = RB.RibbonPanel(filePage, label='显示模式', style=RB.RIBBON_PANEL_NO_AUTO_MINIMISE)
        visual_bar = RB.RibbonButtonBar(visual_panel)
        self._add_ribbon_bar_button(visual_bar, 'icon/视图/面线', '面线', '显示面和线', onCataegoryView.on_visual_mode, param='face_line', size_class=view_button_size)
        self._add_ribbon_bar_button(visual_bar, 'icon/视图/仅线', '仅线', '仅显示线', onCataegoryView.on_visual_mode, param='line', size_class=view_button_size)
        self._add_ribbon_bar_button(visual_bar, 'icon/视图/仅面', '仅面', '仅显示面', onCataegoryView.on_visual_mode, param='face', size_class=view_button_size)

        select_panel = RB.RibbonPanel(filePage, label='选择', style=RB.RIBBON_PANEL_NO_AUTO_MINIMISE)
        select_bar = RB.RibbonButtonBar(select_panel)
        self._add_ribbon_bar_button(select_bar, 'icon/视图/全选', '全选', '全选', onCataegoryView.on_select_all, size_class=view_button_size)
        self._add_ribbon_bar_button(select_bar, 'icon/视图/体', '体', '选择体', onCataegoryView.on_select_mode, param=0, size_class=view_button_size)
        self._add_ribbon_bar_button(select_bar, 'icon/视图/面', '面', '选择面', onCataegoryView.on_select_mode, param=1, size_class=view_button_size)
        self._add_ribbon_bar_button(select_bar, 'icon/视图/线', '线', '选择线', onCataegoryView.on_select_mode, param=2, size_class=view_button_size)
        self._add_ribbon_bar_button(select_bar, 'icon/视图/点', '点', '选择点', onCataegoryView.on_select_mode, param=3, size_class=view_button_size)

        camera_panel = RB.RibbonPanel(filePage, label='视角', style=RB.RIBBON_PANEL_NO_AUTO_MINIMISE)
        camera_bar = RB.RibbonButtonBar(camera_panel)
        self._add_ribbon_bar_button(camera_bar, 'icon/视图/上', '上', '上视图', onCataegoryView.on_view_xyz, param=0, size_class=view_button_size)
        self._add_ribbon_bar_button(camera_bar, 'icon/视图/下', '下', '下视图', onCataegoryView.on_view_xyz, param=1, size_class=view_button_size)
        self._add_ribbon_bar_button(camera_bar, 'icon/视图/左', '左', '左视图', onCataegoryView.on_view_xyz, param=2, size_class=view_button_size)
        self._add_ribbon_bar_button(camera_bar, 'icon/视图/右', '右', '右视图', onCataegoryView.on_view_xyz, param=3, size_class=view_button_size)
        self._add_ribbon_bar_button(camera_bar, 'icon/视图/前', '前', '前视图', onCataegoryView.on_view_xyz, param=4, size_class=view_button_size)
        self._add_ribbon_bar_button(camera_bar, 'icon/视图/后', '后', '后视图', onCataegoryView.on_view_xyz, param=5, size_class=view_button_size)
        self._add_ribbon_bar_button(camera_bar, 'icon/视图/等轴', '等轴', '等轴视图', onCataegoryView.on_view_xyz, param=6, size_class=view_button_size)

        zoom_panel = RB.RibbonPanel(filePage, label='缩放', style=RB.RIBBON_PANEL_NO_AUTO_MINIMISE)
        zoom_bar = RB.RibbonButtonBar(zoom_panel)
        self._add_ribbon_bar_button(zoom_bar, 'icon/视图/缩放适配', '缩放适配', '缩放到合适范围', onCataegoryView.on_zoom, size_class=view_button_size)

    def _init_CAD_Env(self):
        global global_scope
        if "NCTI" in global_scope:
            self.NCTI = global_scope["NCTI"]
            self.doc = global_scope["doc"]
            self.YH = global_scope.get("YH")
            self.yh_doc = global_scope.get("yh_doc")
            return True
        return False

    def _init_views(self):
        # 初始化 Ribbon 和主工作区
        self._initRibbon()

        self.center_panel = wx.Panel(self)
        self.object_view = ObjectTreeView(self.center_panel, self.m_runtime_path)
        self.cad_view = RenderView(self.center_panel, self.NCTI, self.doc)
        self.hwnd = self.cad_view.GetHandle()
        self.editor_view = EditorView(self.center_panel, self.NCTI, self.doc, self.updateTree, self.m_runtime_path)
        self.log_view = LogView(self.center_panel)
        self.log_view.enableLog()

        main_sz = wx.BoxSizer(wx.VERTICAL)
        main_sz.Add(self.ribbon, 0, wx.EXPAND)
        main_sz.Add(self.center_panel, 1, wx.EXPAND)
        self.SetSizer(main_sz)
        self.Layout()

        self.mgr = aui.AuiManager(
            self.center_panel,
            aui.AUI_MGR_DEFAULT & ~aui.AUI_MGR_ALLOW_FLOATING & ~aui.AUI_MGR_TRANSPARENT_DRAG
        )
        self.mgr.AddPane(
            self.object_view,
            aui.AuiPaneInfo().Left().Caption("对象树").BestSize(220, -1).MinSize(180, -1).CloseButton(False)
        )
        self.mgr.AddPane(
            self.cad_view,
            aui.AuiPaneInfo().CenterPane().Caption("视图").CloseButton(False)
        )
        self.mgr.AddPane(
            self.editor_view,
            aui.AuiPaneInfo().Right().Caption("脚本编辑器").BestSize(400, -1).MinSize(300, -1).CloseButton(False)
        )
        self.mgr.AddPane(
            self.log_view,
            aui.AuiPaneInfo().Bottom().Caption("日志输出").BestSize(-1, 150).Floatable(False).CloseButton(False)
        )
        self.mgr.Update()
        self.Bind(aui.EVT_AUI_RENDER, self.cad_view.updateView)
        wx.CallAfter(self.ensureDefaultDocument)

    def ensureDefaultDocument(self):
        # 程序启动后先准备真实文档和 CAD 视图，草图才能挂到 DocView 容器上。
        yh_module = getattr(self, "YH", None)

        if getattr(self.doc, "ID", -1) != -1:
            if getattr(self, "yh_doc", None) is None and yh_module is not None:
                self.yh_doc = yh_module.YHDocument(self.doc)
            return

        if yh_module is not None:
            print("MainWindow: create default YH OCC part document")
            yh_doc = yh_module.YHDocument()
            result = yh_doc.NewPart("OCC", "DCM")
            if result:
                doc_id = yh_doc.GetID()
                ncti_doc = self.NCTI.Document()
                try:
                    ncti_doc.ID = doc_id
                except Exception as e:
                    print(f"MainWindow: bind YH document ID failed: {e}")
                    return
                self.doc = ncti_doc
                self.yh_doc = yh_doc
                global_scope["doc"] = self.doc
                global_scope["yh_doc"] = self.yh_doc
            else:
                print("MainWindow: YH NewPart failed, fallback NCTI document")
                self.doc.New("OCC", "", "GMSH")
        else:
            print("MainWindow: create default OCC document")
            self.doc.New("OCC", "", "GMSH")

        self.view = self.NCTI.View(self.doc.ID)
        self.view.CreateWindow(self.hwnd)
        self.view.SetWindowVis(True, self.doc.ID)
        self.doc.SetCreateGeGeom(1)
        self.doc.Zoom()
        self.cad_view.updateDoc(self.NCTI, self.doc, self.view)
        self.editor_view.doc = self.doc

        if yh_module is not None:
            if getattr(self, "yh_doc", None) is None:
                print("MainWindow: wrap default document as YHDocument")
                self.yh_doc = yh_module.YHDocument(self.doc)
                if self.yh_doc is None:
                    print(f"MainWindow: YHDocument wrap failed, doc.ID={self.doc.ID}")
            else:
                print("MainWindow: YH document already exists")
        else:
            print("MainWindow: YH module is missing")

        self.autoSizeView()
        self.updateTree()

    def _add_ribbon_bar_button(self, bar, name, title, tips, handle=None, param=None, size_class=None):
        id = wx.NewIdRef()
        bar.AddButton(id, title, svg2bmp(f'{self.m_runtime_path}/resources/{name}.svg'), help_string=tips)
        if size_class is not None:
            bar.SetButtonMinSizeClass(id, size_class)
            bar.SetButtonMaxSizeClass(id, size_class)
        if handle is not None:
            if param is not None:
                self.Bind(RB.EVT_RIBBONBUTTONBAR_CLICKED, partial(handle, self, param), id=id)
            else:
                self.Bind(RB.EVT_RIBBONBUTTONBAR_CLICKED, partial(handle, self), id=id)
        return id

    def _add_ribbon_hybrid_button(self, bar, name, title, tips, click_handle=None, dropdown_handle=None, size_class=None):
        id = wx.NewIdRef()
        bar.AddHybridButton(
            id,
            title,
            svg2bmp(f'{self.m_runtime_path}/resources/{name}.svg'),
            help_string=tips
        )
        if size_class is not None:
            bar.SetButtonMinSizeClass(id, size_class)
            bar.SetButtonMaxSizeClass(id, size_class)

        if click_handle is not None:
            self.Bind(
                RB.EVT_RIBBONBUTTONBAR_CLICKED,
                partial(click_handle, self),
                id=id
            )

        if dropdown_handle is not None:
            self.Bind(
                RB.EVT_RIBBONBUTTONBAR_DROPDOWN_CLICKED,
                lambda event, b=bar, bid=id, h=dropdown_handle: h(b, bid, event),
                id=id
            )

        return id

    def _add_ribbon_button_menu(self, bar, name, title, tips, handle=None, param=None):
        id = wx.NewIdRef()
        bar.AddDropdownButton(id, title, svg2bmp(f'{self.m_runtime_path}/resources/{name}.svg'), help_string=tips)
        if handle is not None:
            if param is not None:
                self.Bind(RB.EVT_RIBBONBUTTONBAR_DROPDOWN_CLICKED, partial(handle, self, param), id=id)
            else:
                self.Bind(RB.EVT_RIBBONBUTTONBAR_DROPDOWN_CLICKED, partial(handle), id=id)
        return id

    def _add_bitmap_button(self, parent, sizer, name, tips, handle=None, param=None):
        btn = wx.BitmapButton(parent, wx.ID_ANY, svg2bmp(f'{self.m_runtime_path}/resources/{name}.svg'))
        btn.SetToolTip(tips)
        btn.SetCanFocus(False)
        sizer.Add(btn)
        if handle is not None:
            if param is not None:
                self.Bind(wx.EVT_BUTTON, partial(handle, self, param), btn)
            else:
                self.Bind(wx.EVT_BUTTON, partial(handle, self), btn)
        return btn

    def _add_checkbox(self, parent, sizer, title, handle=None, param=None):
        checkbox = wx.CheckBox(parent, label=title)
        sizer.Add(checkbox)
        if handle is not None:
            if param is not None:
                self.Bind(wx.EVT_CHECKBOX, partial(handle, self, param), checkbox)
            else:
                self.Bind(wx.EVT_CHECKBOX, partial(handle, self), checkbox)
        return checkbox

    def _add_radiobutton(self, parent, sizer, title, handle=None, param=None):
        radiobutton = wx.RadioButton(parent, label=title)
        sizer.Add(radiobutton)
        if handle is not None:
            if param is not None:
                self.Bind(wx.EVT_RADIOBUTTON, partial(handle, self, param), radiobutton)
            else:
                self.Bind(wx.EVT_RADIOBUTTON, partial(handle), radiobutton)
        return radiobutton

    def _init_mode(self):
        # 草图求解相关开关默认开启。
        self._sketch_auto_solve_enabled = True
        self._sketch_argument_auto_snap_enabled = False
        self._sketch_auto_close_area_enabled = True
        self._sketch_auto_free_cons_enabled = True

    def autoSizeView(self):
        if hasattr(self, 'doc') and hasattr(self, 'cad_view'):
            self.cad_view.updateView()

    def updateTree(self):
        if hasattr(self, 'object_view'):
            self.object_view.updateTree(self.NCTI, self.doc)

    def getSelectMode(self):
        # 默认选择模式：体、面、线、点都允许。
        return True, True, True, True

    def getDisplayMode(self):
        # 默认显示模式：显示面和线。
        return False, True, True, False 

if __name__ == '__main__':
    import sys
    import ctypes
    import os

    if sys.platform == "win32":
        ctypes.windll.user32.SetProcessDPIAware(2)

    app = wx.App(False)
    runtime_path = os.path.dirname(os.path.abspath(__file__))
    MainWindow(runtime_path).Show()
    app.MainLoop()
