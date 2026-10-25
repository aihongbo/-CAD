#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Copyright (c) 2025 粤港澳大湾区（广东）国创中心
PyCAEPre is licensed under Mulan PSL v2.
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

import Function.onCataegoryFile as onCataegoryFile
import Function.onCataegoryModel as onCataegoryModel
import Function.onCataegoryGeometry as onCataegoryGeometry
import Function.onCataegorySimulation as onCataegorySimulation
from functools import partial
from Pub.ImageTransfrom import svg2bmp
from View.FormDialog import InputDialog
from View.FeatrueTreeDlg import InputFeatureTreeDlg
from View.MeshDlg import MeshDialog

class MainWindow(wx.Frame):
    def __init__(self,runtime_path):
        super().__init__(None, title='Python前处理', size=(1280, 960))
        if False == self._init_CAD_Env():
            return
        self.m_runtime_path = runtime_path
        self._init_views()
        self._init_mode()
        self.Center()
        self.NCTI.SetPyInputDialogCallback(InputDialog)
        self.NCTI.SetPyCustomDialogCallbackFun(InputFeatureTreeDlg)
        self.NCTI.SetPyMeshSettingCallbackFun(MeshDialog)
    def _initRibbon(self):
        self.ribbon = RB.RibbonBar(self, style=RB.RIBBON_BAR_DEFAULT_STYLE)
        self._initRibbonPageFile()
        self._initRibbonPageGeneral()
        self._initRibbonPageGeometry()
        self._initRibbonPageSimulation()
        self.ribbon.Realize()
        

    def _initRibbonPageFile(self):
        filePage = RB.RibbonPage(self.ribbon, label='文件')

        asmPanel = RB.RibbonPanel(filePage, label='零件装配',style=RB.RIBBON_PANEL_NO_AUTO_MINIMISE)
        asmBar = RB.RibbonButtonBar(asmPanel)

        self._add_ribbon_bar_button(asmBar, 'ribbon/new_assembly', '创建装配', '创建新的装配体', onCataegoryFile.on_new_assembly_button_click)
        self._add_ribbon_bar_button(asmBar, 'ribbon/new_part', '创建零件', '创建新的零件', onCataegoryFile.on_new_button_click)
        self._add_ribbon_bar_button(asmBar, 'ribbon/add_assembly', '添加装配', '向当前装配添加装配体', onCataegoryFile.on_add_assembly_button_click)
        self._add_ribbon_bar_button(asmBar, 'ribbon/add_part', '添加零件', '向当前装配添加零件', onCataegoryFile.on_add_part_button_click)
        self._add_ribbon_bar_button(asmBar, 'ribbon/import_part', '导入零件', '向当前装配添加零件', onCataegoryFile.on_import_part_button_click)
        self._add_ribbon_bar_button(asmBar, 'ribbon/delete_part', '删除零件', '删除当前装配中的零件', onCataegoryFile.on_delete_part_button_click)
        
        docPanel = RB.RibbonPanel(filePage, label='文档',style=RB.RIBBON_PANEL_NO_AUTO_MINIMISE)
        docBar = RB.RibbonButtonBar(docPanel)
        self._add_ribbon_bar_button(docBar, 'ribbon/open', '打开', '打开已有的文档', onCataegoryFile.on_open_button_click)
        self._add_ribbon_bar_button(docBar, 'ribbon/save', '保存', '保存当前文档', onCataegoryFile.on_save_button_click)
        self._add_ribbon_bar_button(docBar, 'ribbon/close', '关闭', '关闭当前文档', onCataegoryFile.on_close_button_click)
        
        modelPanel = RB.RibbonPanel(filePage, label='模型操作',style=RB.RIBBON_PANEL_NO_AUTO_MINIMISE)
        modelBar = RB.RibbonButtonBar(modelPanel)
        self._add_ribbon_bar_button(modelBar, 'ribbon/import', '导入模型', '导入已有的模型', onCataegoryFile.importFile)
        self._add_ribbon_bar_button(modelBar, 'ribbon/export', '导出模型', '导出当前模型', onCataegoryFile.on_export_button_click)
        self._add_ribbon_bar_button(modelBar, 'ribbon/delete', '删除模型', '删除当前模型', onCataegoryFile.on_delete_button_click)
        historyPanel = RB.RibbonPanel(filePage, label='历史',style=RB.RIBBON_PANEL_NO_AUTO_MINIMISE)
        historyBar = RB.RibbonButtonBar(historyPanel)
        self._add_ribbon_bar_button(historyBar, 'ribbon/undo', '撤回', '', onCataegoryFile.on_undo_button_click)
        self._add_ribbon_bar_button(historyBar, 'ribbon/redo', '重做', '', onCataegoryFile.on_redo_button_click)
        
    def _initRibbonPageGeneral(self):
        general = RB.RibbonPage(self.ribbon, label='常规')

        ssPanel = RB.RibbonPanel(general, label='显隐',style=RB.RIBBON_PANEL_NO_AUTO_MINIMISE)
        ssBar = RB.RibbonButtonBar(ssPanel)
        self._add_ribbon_bar_button(ssBar, 'ribbon/show_all_model', '显示', '显示所有', onCataegoryModel.on_display_all)
        self._add_ribbon_bar_button(ssBar, 'ribbon/hide_select_model', '隐藏', '隐藏已选中', onCataegoryModel.on_hide_selected)
        self._add_ribbon_bar_button(ssBar, 'ribbon/show_select_model', '独显', '仅显示已选中', onCataegoryModel.on_diaplay_selected_only)

        # 方向
        dirPanel = RB.RibbonPanel(general, label='方向轴',style=RB.RIBBON_PANEL_NO_AUTO_MINIMISE)
        sizer = wx.GridSizer(2, 3, 0, 0)
        self._add_bitmap_button(dirPanel, sizer, 'ribbon/xplus', 'X轴正向', onCataegoryModel.on_zoom_view, 3) 
        self._add_bitmap_button(dirPanel, sizer, 'ribbon/yplus', 'Y轴正向', onCataegoryModel.on_zoom_view, 4) 
        self._add_bitmap_button(dirPanel, sizer, 'ribbon/zplus', 'Z轴正向', onCataegoryModel.on_zoom_view, 0) 
        self._add_bitmap_button(dirPanel, sizer, 'ribbon/xminus', 'X轴反向', onCataegoryModel.on_zoom_view, 2) 
        self._add_bitmap_button(dirPanel, sizer, 'ribbon/yminus', 'Y轴反向', onCataegoryModel.on_zoom_view, 5) 
        self._add_bitmap_button(dirPanel, sizer, 'ribbon/zminus', 'Z轴反向', onCataegoryModel.on_zoom_view, 1) 
        dirPanel.SetSizer(sizer)
        sizer.Layout()

        # 视图
        viewPanel = RB.RibbonPanel(general, label='视图',style=RB.RIBBON_PANEL_NO_AUTO_MINIMISE)
        viewBar = RB.RibbonButtonBar(viewPanel)
        self._add_ribbon_bar_button(viewBar, 'ribbon/isometric', '西南视图', '切换到西南视图', onCataegoryModel.on_zoom_view, 6)
        # self._add_ribbon_bar_button(viewBar, 'location', '聚焦', '聚焦')
        self._add_ribbon_bar_button(viewBar, 'ribbon/zoom', '最大化', '最大化', onCataegoryModel.on_zoom_button_click)

        # 显示模式
        displayPanel = RB.RibbonPanel(general, label='显示模式',style=RB.RIBBON_PANEL_NO_AUTO_MINIMISE)
        image = wx.StaticBitmap(displayPanel, wx.ID_ANY, svg2bmp(f'{self.m_runtime_path}/resources/ribbon/display_mode.svg', (28,28)))
        title = wx.StaticText(displayPanel, wx.ID_ANY, '显示模式')
        leftSizer = wx.BoxSizer(wx.VERTICAL)
        leftSizer.Add(image, proportion=0, flag=wx.ALIGN_CENTER_HORIZONTAL)
        leftSizer.AddSpacer(5)
        leftSizer.Add(title, proportion=0, flag=wx.ALIGN_CENTER_HORIZONTAL)
        rightSizer = wx.GridSizer(2, 2, 5, 5)
        self.visualmode_body = self._add_checkbox(displayPanel, rightSizer, '体', onCataegoryModel.on_visual_checkbox_body)
        self.visualmode_face = self._add_checkbox(displayPanel, rightSizer, '面', onCataegoryModel.on_visual_checkbox_face)
        self.visualmode_line = self._add_checkbox(displayPanel, rightSizer, '线', onCataegoryModel.on_visual_checkbox_line)
        self.visualmode_vertex = self._add_checkbox(displayPanel, rightSizer, '点', onCataegoryModel.on_visual_checkbox_vertex)
        sizer = wx.BoxSizer()
        sizer.AddSpacer(5)
        sizer.Add(leftSizer, proportion=0, flag=wx.ALIGN_CENTER_VERTICAL)
        sizer.AddSpacer(5)
        sizer.Add(rightSizer, proportion=0, flag=wx.ALIGN_CENTER_VERTICAL)
        sizer.AddSpacer(5)
        displayPanel.SetSizer(sizer)
        sizer.Layout()

        # 选择模式
        selectPanel = RB.RibbonPanel(general, label='选择模式',style=RB.RIBBON_PANEL_NO_AUTO_MINIMISE)
        image = wx.StaticBitmap(selectPanel, wx.ID_ANY, svg2bmp(f'{self.m_runtime_path}/resources/ribbon/selection_mode.svg', (28,28)))
        title = wx.StaticText(selectPanel, wx.ID_ANY, '选择模式')
        leftSizer = wx.BoxSizer(wx.VERTICAL)
        leftSizer.Add(image, wx.SizerFlags().CentreHorizontal())
        leftSizer.AddSpacer(5)
        leftSizer.Add(title, wx.SizerFlags().CentreHorizontal())
        rightSizer = wx.GridSizer(2, 2, 5, 5)
        self.selmode_body = self._add_checkbox(selectPanel, rightSizer, '体', onCataegoryModel.on_sel_checkbox_body) 
        self.selmode_face = self._add_checkbox(selectPanel, rightSizer, '面', onCataegoryModel.on_sel_checkbox_face) 
        self.selmode_line = self._add_checkbox(selectPanel, rightSizer, '线', onCataegoryModel.on_sel_checkbox_line) 
        self.selmode_vertex = self._add_checkbox(selectPanel, rightSizer, '点', onCataegoryModel.on_sel_checkbox_vertex) 
        sizer = wx.BoxSizer()
        sizer.AddSpacer(5)
        sizer.Add(leftSizer, proportion=0, flag=wx.ALIGN_CENTER_VERTICAL)
        sizer.AddSpacer(5)
        sizer.Add(rightSizer, proportion=0, flag=wx.ALIGN_CENTER_VERTICAL)
        sizer.AddSpacer(5)
        selectPanel.SetSizer(sizer)
        sizer.Layout()
        selBar = RB.RibbonButtonBar(selectPanel)
        self._add_ribbon_bar_button(selBar, 'ribbon/select_all', '全选', '选中全部', onCataegoryModel.on_allsel_button_click)

        findPanel = RB.RibbonPanel(general, label='查找特征',style=RB.RIBBON_PANEL_NO_AUTO_MINIMISE)

        self.findBar = RB.RibbonButtonBar(findPanel)
        self._add_ribbon_bar_button(self.findBar, 'ribbon/ai_recognition', 'AI识别', '', onCataegoryModel.on_airecog_button_click)
        #self._add_ribbon_bar_button(findBar, 'ribbon/fillet_reasoning', '圆角推理', '', onCataegoryModel.on_zoom_button_click)
        #self._add_ribbon_bar_button(findBar, 'ribbon/feature_list', '特征列表', '', onCataegoryModel.on_zoom_button_click)
        self._add_ribbon_bar_button(self.findBar, 'ribbon/search_innerloop', '查找内环', '', onCataegoryModel.on_searchloop_button_click)
        self._add_ribbon_bar_button(self.findBar, 'ribbon/search_connection', '查找连接', '', onCataegoryModel.on_searchface_button_click)
        self._add_ribbon_bar_button(self.findBar, 'ribbon/nonplanar_connection', '非平面连接', '', onCataegoryModel.on_searchnoplaneface_button_click)

        self._add_ribbon_button_menu(self.findBar, 'ribbon/measure', '几何测量', '几何属性测量',self.on_mearsure_dropdown)
        # 创建下拉菜单
        self.mearsure_menu = wx.Menu()
        # 添加菜单项
        item1 = self.mearsure_menu.Append(wx.MenuItem(self.mearsure_menu, wx.ID_ANY, "获取点"))
        item2 = self.mearsure_menu.Append(wx.MenuItem(self.mearsure_menu, wx.ID_ANY, "获取长度"))
        item3 = self.mearsure_menu.Append(wx.MenuItem(self.mearsure_menu, wx.ID_ANY, "获取中点"))
        item4 = self.mearsure_menu.Append(wx.MenuItem(self.mearsure_menu, wx.ID_ANY, "获取圆点"))
        item5 = self.mearsure_menu.Append(wx.MenuItem(self.mearsure_menu, wx.ID_ANY, "获取半径"))
        item6 = self.mearsure_menu.Append(wx.MenuItem(self.mearsure_menu, wx.ID_ANY, "获取向量"))
        item7 = self.mearsure_menu.Append(wx.MenuItem(self.mearsure_menu, wx.ID_ANY, "获取角度"))
        # 绑定事件
        self.Bind(wx.EVT_MENU, onCataegoryModel.on_measure_getpt_click, item1)
        self.Bind(wx.EVT_MENU, onCataegoryModel.on_measure_getlen_click, item2)
        self.Bind(wx.EVT_MENU, onCataegoryModel.on_measure_getmidpt_click, item3)
        self.Bind(wx.EVT_MENU, onCataegoryModel.on_measure_getcenter_click, item4)
        self.Bind(wx.EVT_MENU, onCataegoryModel.on_measure_getradius_click, item5)
        self.Bind(wx.EVT_MENU, onCataegoryModel.on_getvec_button_click, item6)
        self.Bind(wx.EVT_MENU, onCataegoryModel.on_getangle_button_click, item7)

    def _initRibbonPageGeometry(self):
        geometry = RB.RibbonPage(self.ribbon, label='几何')

        ssPanel = RB.RibbonPanel(geometry, label='直接建模',style=RB.RIBBON_PANEL_NO_AUTO_MINIMISE)
        ssBar = RB.RibbonButtonBar(ssPanel)
        self._add_ribbon_bar_button(ssBar, 'Geometry/box', '长方体', '创建长方体', onCataegoryGeometry.on_exec_box_button_click)
        self._add_ribbon_bar_button(ssBar, 'Geometry/cylinder', '圆柱体', '创建圆柱', onCataegoryGeometry.on_exec_cylinder_button_click)
        
        ssPanel = RB.RibbonPanel(geometry, label='几何操作',style=RB.RIBBON_PANEL_NO_AUTO_MINIMISE)
        booleanBar = RB.RibbonButtonBar(ssPanel)
        self._add_ribbon_bar_button(booleanBar, 'Geometry/boolean', '布尔运算', '布尔运算', onCataegoryGeometry.on_exec_boole_button_click)
        self._add_ribbon_bar_button(booleanBar, 'Geometry/fillet', '圆角', '圆角', onCataegoryGeometry.on_exec_fillet_button_click)
        self._add_ribbon_bar_button(booleanBar, 'Geometry/chamfer', '倒角', '倒角', onCataegoryGeometry.on_exec_chamfer_button_click)
        ssPanel = RB.RibbonPanel(geometry, label='矩阵变换',style=RB.RIBBON_PANEL_NO_AUTO_MINIMISE)
        booleanBar = RB.RibbonButtonBar(ssPanel)
        self._add_ribbon_bar_button(booleanBar, 'Geometry/pan', '平移', '平移', onCataegoryGeometry.on_exec_pan_button_click)
        self._add_ribbon_bar_button(booleanBar, 'Geometry/zoom', '缩放', '缩放', onCataegoryGeometry.on_exec_scale_button_click)
        self._add_ribbon_bar_button(booleanBar, 'Geometry/rotate', '旋转', '  旋转', onCataegoryGeometry.on_exec_rotate_button_click)

        ssPanel = RB.RibbonPanel(geometry, label='特征操作',style=RB.RIBBON_PANEL_NO_AUTO_MINIMISE)
        booleanBar = RB.RibbonButtonBar(ssPanel)
        self._add_ribbon_bar_button(booleanBar, 'Geometry/remove_features', '移除特征', '移除特征', onCataegoryGeometry.on_exec_removefeature_button_click)
        self._add_ribbon_bar_button(booleanBar, 'Geometry/removing_faces', '移除面', '移除面', onCataegoryGeometry.on_exec_removeface_button_click)
        self._add_ribbon_bar_button(booleanBar, 'Geometry/extract_cell', '抽取要素', '提取子单元', onCataegoryGeometry.on_exec_extractcell_button_click)
        self._add_ribbon_bar_button(booleanBar, 'Geometry/fill_loop', '填充内环', '填充内环', onCataegoryGeometry.on_exec_fillloop_button_click)
        self._add_ribbon_bar_button(booleanBar, 'Geometry/create_compound', '组合', '创建组合对象', onCataegoryGeometry.on_exec_createcompound_button_click)
        self._add_ribbon_bar_button(booleanBar, 'Geometry/explode_body', '分解', '分解对象', onCataegoryGeometry.on_exec_explodeboldy_button_click)
        self._add_ribbon_bar_button(booleanBar, 'Geometry/sewing_bodies', '缝合', '缝合', onCataegoryGeometry.on_exec_sewingbodies_button_click)
        self._add_ribbon_bar_button(booleanBar, 'Geometry/separating_surface', '分离面', '分离面', onCataegoryGeometry.on_exec_splitface_button_click)
        self._add_ribbon_bar_button(booleanBar, 'Geometry/extrude', '拉伸', '拉伸', onCataegoryGeometry.on_exec_prism_button_click)
        self._add_ribbon_bar_button(booleanBar, 'Geometry/extrude', '补面', '补面', onCataegoryGeometry.on_exec_patching_face_button_click)
        self._add_ribbon_bar_button(booleanBar, 'Geometry/linear_array', '直线阵列', '直线阵列', onCataegoryGeometry.on_exec_geoperiodic_button_click)
        self._add_ribbon_bar_button(booleanBar, 'Geometry/rotate_array', '旋转阵列', '旋转阵列', onCataegoryGeometry.on_exec_rotateperiodic_button_click)
        
        ssPanel = RB.RibbonPanel(geometry, label='查找特征',style=RB.RIBBON_PANEL_NO_AUTO_MINIMISE)
        booleanBar = RB.RibbonButtonBar(ssPanel)
        self._add_ribbon_bar_button(booleanBar, 'Geometry/findfeartures', '查找小特征', '查找小特征', onCataegoryGeometry.on_exec_findsmallfeature_button_click)
        self._add_ribbon_bar_button(booleanBar, 'Geometry/findfillet', '查找圆角', '查找圆角', onCataegoryGeometry.on_exec_findfillets_button_click)
        self._add_ribbon_bar_button(booleanBar, 'Geometry/findlogo', '查找LOGO', '查找LOGO', onCataegoryGeometry.on_exec_findlogos_button_click)
        self._add_ribbon_bar_button(booleanBar, 'Geometry/findhole', '查找孔', '查找孔', onCataegoryGeometry.on_exec_findholes_button_click)

    def _initRibbonPageSimulation(self):
        simulation = RB.RibbonPage(self.ribbon, label='仿真')
        ssPanel = RB.RibbonPanel(simulation, label='创建网格',style=RB.RIBBON_PANEL_NO_AUTO_MINIMISE)
        ssBar = RB.RibbonButtonBar(ssPanel)
        self._add_ribbon_bar_button(ssBar, 'Simulation/create_surface_mesh', '面网格', '创建面网格', onCataegorySimulation.on_mesh_surface_generation)
        self._add_ribbon_bar_button(ssBar, 'Simulation/create_volume_mesh', '体网格', '创建体网格', onCataegorySimulation.on_mesh_volume_generation)
        
        ssPanel = RB.RibbonPanel(simulation, label='边界条件',style=RB.RIBBON_PANEL_NO_AUTO_MINIMISE)
        ssBar = RB.RibbonButtonBar(ssPanel)        
        self._add_ribbon_bar_button(ssBar, 'Simulation/mesh_add_force', '集中力', '创建集中力', onCataegorySimulation.on_single_force)
        self._add_ribbon_bar_button(ssBar, 'Simulation/mesh_add_spc', '单点约束', '创建单点约束', onCataegorySimulation.on_single_constraint)
        self._add_ribbon_bar_button(ssBar, 'Simulation/mesh_add_mat', '材料属性', '材料属性', onCataegorySimulation.on_material_properties)
        

        meshPanel = RB.RibbonPanel(simulation, label='网格拾取',style=RB.RIBBON_PANEL_NO_AUTO_MINIMISE)
        image = wx.StaticBitmap(meshPanel, wx.ID_ANY, svg2bmp(f'{self.m_runtime_path}/resources/Simulation/mesh_setting.svg', (28,28)))
        title = wx.StaticText(meshPanel, wx.ID_ANY, '网格拾取')
        leftSizer = wx.BoxSizer(wx.VERTICAL)
        leftSizer.Add(image, proportion=0, flag=wx.ALIGN_CENTER_HORIZONTAL)
        leftSizer.AddSpacer(5)
        leftSizer.Add(title, proportion=0, flag=wx.ALIGN_CENTER_HORIZONTAL)
        rightSizer = wx.GridSizer(2, 3, 5, 5)
        self.mesh_visual_body = self._add_radiobutton(meshPanel, rightSizer, '几何', onCataegorySimulation.on_set_pickup_mesh, param = 0)
        self.mesh_visual_node = self._add_radiobutton(meshPanel, rightSizer, '节点', onCataegorySimulation.on_set_pickup_mesh, param = 1)
        self.mesh_visual_cell = self._add_radiobutton(meshPanel, rightSizer, '单元', onCataegorySimulation.on_set_pickup_mesh, param = 2)
        self.mesh_visual_face = self._add_radiobutton(meshPanel, rightSizer, '单元面', onCataegorySimulation.on_set_pickup_mesh, param = 3)
        self.mesh_visual_edge = self._add_radiobutton(meshPanel, rightSizer, '单元边', onCataegorySimulation.on_set_pickup_mesh, param = 4)
        sizer = wx.BoxSizer()
        sizer.AddSpacer(5)
        sizer.Add(leftSizer, proportion=0, flag=wx.ALIGN_CENTER_VERTICAL)
        sizer.AddSpacer(5)
        sizer.Add(rightSizer, proportion=0, flag=wx.ALIGN_CENTER_VERTICAL)
        sizer.AddSpacer(5)
        meshPanel.SetSizer(sizer)
        sizer.Layout()        

    # 绑定几何测量的下拉菜单事件
    def on_mearsure_dropdown(self,event):
        #btn_rect = self.findBar.GetButtonRect(dropdown_btn)
        #pos = self.findBar.ClientToScreen(btn_rect.GetBottomLeft())
        self.findBar.PopupMenu(self.mearsure_menu)

    def _init_CAD_Env(self):
        global global_scope
        if "NCTI" in global_scope:
            self.NCTI = global_scope["NCTI"]
            self.doc = global_scope["doc"] 
            return True
        else:
            return False
        
    def _init_views(self):
        # ---------- 1. 创建 RibbonBar ----------
        self._initRibbon()

        # ---------- 2. 主内容区 ----------
        self.center_panel = wx.Panel(self)
        # 装配树
        self.object_view = ObjectTreeView(self.center_panel, self.m_runtime_path)        
        # 渲染窗口
        self.cad_view = RenderView(self.center_panel, self.NCTI, self.doc)
        self.hwnd = self.cad_view.GetHandle()
        # 脚本编辑器
        self.editor_view = EditorView(self.center_panel, self.NCTI, self.doc, self.updateTree, self.m_runtime_path)
        # 日志窗口
        self.log_view = LogView(self.center_panel)
        self.log_view.enableLog()

        # ---------- 3. 布局 ----------
        # 顶部 Sizer 只放 Ribbon
        main_sz = wx.BoxSizer(wx.VERTICAL)
        main_sz.Add(self.ribbon, 0, wx.EXPAND)
        # 中心区域就是 center_panel
        main_sz.Add(self.center_panel, 1, wx.EXPAND)
        self.SetSizer(main_sz)
        self.Layout()
        # AuiManager 只管理 center_panel 里的子控件
        self.mgr = aui.AuiManager(self.center_panel, aui.AUI_MGR_DEFAULT&~aui.AUI_MGR_ALLOW_FLOATING&~aui.AUI_MGR_TRANSPARENT_DRAG)   # 关键点：manager 的 parent 是 center_panel
        self.mgr.AddPane(self.object_view,
                         aui.AuiPaneInfo().Left().Caption("对象树").
                         BestSize(220, -1).MinSize(180, -1).CloseButton(False))
        self.mgr.AddPane(self.cad_view,
                         aui.AuiPaneInfo().CenterPane().Caption("视图").CloseButton(False))
        self.mgr.AddPane(self.editor_view,
                         aui.AuiPaneInfo().Right().Caption("脚本编辑器").
                         BestSize(400, -1).MinSize(300, -1).CloseButton(False))
        self.mgr.AddPane(self.log_view,
                         aui.AuiPaneInfo().Bottom().Caption("日志输出").
                         BestSize(-1, 150).Floatable(False).CloseButton(False))
        self.mgr.Update()
        self.Bind(aui.EVT_AUI_RENDER, self.cad_view.updateView)

    def _add_ribbon_bar_button(self, bar, name, title, tips, handle=None, param=None):
        id = wx.NewIdRef()
        wx.ART_FILE_OPEN
        bar.AddButton(id,  title,  svg2bmp(f'{self.m_runtime_path}/resources/{name}.svg'), help_string=tips)
        if handle is not None:
            if param is not None:
                self.Bind(RB.EVT_RIBBONBUTTONBAR_CLICKED, partial(handle, self, param), id=id)
            else:
                self.Bind(RB.EVT_RIBBONBUTTONBAR_CLICKED, partial(handle, self), id=id)
        return id

    def _add_ribbon_button_menu(self, bar, name, title, tips, handle=None, param=None):
        id = wx.NewIdRef()
        wx.ART_FILE_OPEN
        bar.AddDropdownButton(id,  title,  svg2bmp(f'{self.m_runtime_path}/resources/{name}.svg'), help_string=tips )
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
                self.Bind(wx.EVT_CHECKBOX, partial(handle,self, param), checkbox)
            else:
                self.Bind(wx.EVT_CHECKBOX, partial(handle,self), checkbox)
        return checkbox

    def _add_radiobutton(self, parent, sizer, title, handle=None, param=None):
        radiobutton = wx.RadioButton(parent, label=title)
        sizer.Add(radiobutton)
        if handle is not None:
            if param is not None:
                self.Bind(wx.EVT_RADIOBUTTON, partial(handle,self, param), radiobutton)
            else:
                self.Bind(wx.EVT_RADIOBUTTON, partial(handle), radiobutton)
        return radiobutton

    def _init_mode(self):
        self.selmode_body.SetValue(True)
        self.selmode_face.SetValue(True)
        self.selmode_line.SetValue(True)
        self.selmode_vertex.SetValue(True)

        self.visualmode_body.SetValue(False)
        self.visualmode_face.SetValue(True)
        self.visualmode_line.SetValue(True)
        self.visualmode_vertex.SetValue(False)
        
        self.mesh_visual_body.SetValue(True)
        self.mesh_visual_node.SetValue(False)
        self.mesh_visual_cell.SetValue(False)
        self.mesh_visual_face.SetValue(False)
        self.mesh_visual_edge.SetValue(False)

    # 
    def autoSizeView(self):
        if hasattr(self, 'doc'):            
            self.cad_view.updateView()

    def updateTree(self):
        self.object_view.updateTree(self.NCTI, self.doc)
    def getSelectMode(self):
        return self.selmode_body.GetValue(), self.selmode_face.GetValue(), self.selmode_line.GetValue(), self.selmode_vertex.GetValue()
    def getDisplayMode(self):
        return self.visualmode_body.GetValue(), self.visualmode_face.GetValue(), self.visualmode_line.GetValue(), self.visualmode_vertex.GetValue()
