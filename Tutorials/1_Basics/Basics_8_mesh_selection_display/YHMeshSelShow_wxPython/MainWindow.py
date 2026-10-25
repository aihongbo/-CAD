import sys
import os
import ctypes
import importlib
from Pub.configLoad import global_scope
import wx
import wx.aui
import wx.ribbon as RB
from functools import partial
from Pub.ImageTransfrom import svg2bmp
from Dialog.LogView import LogView
from Dialog.FormDialog import DialogData # type: ignore
from Dialog.ObjectTreeView import ObjectTreeView # type: ignore
from Dialog.RenderView import RenderView # type: ignore
from Dialog.MeshDlg import MeshDialog # type: ignore
from Dialog.GetElementInfo import ElementDialog #type: ignore

# global_scope = {}

def InputDialog(*arg):
        # 初始化内置参数对话框
        argsList = list(arg)
        if len(argsList) % 2 != 0:
            print(f"输入参数错误: {arg}")
            wx.MessageBox.critical(None, "错误", f"输入参数错误: {arg}")
            return ()
        window = DialogData()
        global global_scope
        window.initNcti(global_scope["doc"], global_scope["NCTI"])
        window.initWidgets(*arg)
        if window.ShowModal() == wx.ID_OK:
            val = tuple(window.outList)
            #print(val)
            return val
        return {}

class MainWindow(wx.Frame):
    def __init__(self):
        super().__init__(None, title="基础课_CAD/CAE开发入门(八)_网格选择模式和显示模式", size=(1200, 800))
        # 初始化成员变量
        self.HWND = -1
        global global_scope
        self.NCTI = global_scope["NCTI"]
        self.doc = global_scope["doc"]
        self.view = None
        self.current_obj_name = {}
        self.current_obj_edgeId = []
        self.current_obj_faceId = []
        self.m_runtime_path = os.path.dirname(os.path.abspath(__file__))

        # 设置当前工作目录为程序所在目录
        os.chdir(self.m_runtime_path)

        # 隐藏左上角图标
        hide_icon = wx.Icon(f'resources\\hide.ico', wx.BITMAP_TYPE_ICO)
        self.SetIcon(hide_icon)

        # 初始化主布局
        self.init_main_layout()
        self.init_mode()
        # 设置内置参数对话框——可定制多端参数对话框
        self.NCTI.SetPyInputDialogCallback(InputDialog)
        self.NCTI.SetPyMeshSettingCallbackFun(MeshDialog)

    def init_main_layout(self):
        # 创建RibbonBar
        self.initViewRibbon()

        # 主内容区
        self.center_panel = wx.Panel(self)
        # 渲染窗口
        self.cad_view = RenderView(self.center_panel, self.NCTI, self.doc)
        self.HWND = self.cad_view.GetHandle()

        # 装配树
        self.object_view = ObjectTreeView(self.center_panel)

        # 日志窗口
        self.log_view = LogView(self.center_panel)
        self.log_view.enableLog()
        
        # 设置布局
        # 顶部 Sizer 只放 Ribbon
        main_sz = wx.BoxSizer(wx.VERTICAL)
        main_sz.Add(self.ribbon, 0, wx.EXPAND)
        # 中心区域就是 center_panel
        main_sz.Add(self.center_panel, 1, wx.EXPAND)
        self.SetSizer(main_sz)
        self.Layout()

        # AuiManager 只管理 center_panel 里的子控件
        self.mgr = wx.aui.AuiManager(self.center_panel, wx.aui.AUI_MGR_DEFAULT&~wx.aui.AUI_MGR_ALLOW_FLOATING&~wx.aui.AUI_MGR_TRANSPARENT_DRAG)   # 关键点：manager 的 parent 是 center_panel
        
        dock_art = self.mgr.GetArtProvider()
        dock_art.SetColour(wx.aui.AUI_DOCKART_INACTIVE_CAPTION_TEXT_COLOUR, 
                          wx.Colour(62, 64, 67))
        dock_art.SetColour(wx.aui.AUI_DOCKART_SASH_COLOUR, 
                          wx.Colour(171, 197, 225))  # 活动标题栏颜色
        dock_art.SetColour(wx.aui.AUI_DOCKART_INACTIVE_CAPTION_COLOUR,
                          wx.Colour(171, 197, 225))  # 非活动标题栏颜色
        dock_art.SetColour(wx.aui.AUI_DOCKART_INACTIVE_CAPTION_GRADIENT_COLOUR,
                           wx.Colour(171, 197, 225))
        
        # 设置标题栏大小
        dock_art.SetMetric(wx.aui.AUI_DOCKART_CAPTION_SIZE, 20)

        # 设置边框颜色
        # dock_art.SetColour(wx.aui.AUI_DOCKART_BORDER_COLOUR,
        #                   wx.Colour(255, 0, 0))
        self.mgr.AddPane(self.object_view,
                         wx.aui.AuiPaneInfo().Left().Caption("装配树").
                         BestSize(220, -1).MinSize(180, -1).CloseButton(False))
        
        self.mgr.AddPane(self.cad_view,
                         wx.aui.AuiPaneInfo().CenterPane().Caption("视图").CloseButton(False).PaneBorder(False))
        self.mgr.AddPane(self.log_view,
                          wx.aui.AuiPaneInfo().Bottom().Caption("控制台").
                          BestSize(-1, 150).Floatable(False).CloseButton(True).PaneBorder(False))
        
        self.mgr.Update()
        self.Bind(wx.aui.EVT_AUI_RENDER, self.cad_view.updateView)

        # 显示窗口
        self.Centre()
        self.Show()
        # 更新布局以确保正确计算尺寸
        self.Layout()

    def initViewRibbon(self):
        self.ribbon = RB.RibbonBar(self, style=RB.RIBBON_BAR_DEFAULT_STYLE)
        self.initFileRibbonFile()
        self.initFeatureRibbonView()
        self.ribbon.Realize()

    def initFileRibbonFile(self):
        filePage = RB.RibbonPage(self.ribbon, label="文档")

        asmPanel = RB.RibbonPanel(filePage, label='基础功能',style=RB.RIBBON_PANEL_NO_AUTO_MINIMISE)
        asmBar = RB.RibbonButtonBar(asmPanel)

        self.add_ribbon_bar_button(asmBar, 'create_doc', '创建文档', '创建文档', self.on_create_doc)
        self.add_ribbon_bar_button(asmBar, 'close_doc', '关闭文档', '关闭文档', self.on_close_doc)
        self.add_ribbon_bar_button(asmBar, 'import_model', '导入模型', '导入模型', self.on_import_file)
        self.add_ribbon_bar_button(asmBar, 'restor_mdel', '复位模型', '复位模型', self.on_zoom)
        self.add_ribbon_bar_button(asmBar, 'undo', '撤销', '撤销', self.on_undo)
        self.add_ribbon_bar_button(asmBar, 'redo', '重做', '重做', self.on_redo)
        self.add_ribbon_bar_button(asmBar, 'clean_doc', '清空文档', '清空文档', self.on_clean)
        self.add_ribbon_bar_button(asmBar, 'delete_part', '删除模型', '删除模型', self.on_delete)

        conPanel = RB.RibbonPanel(filePage, label='窗口控制', style=RB.RIBBON_PANEL_NO_AUTO_MINIMISE)
        conBar = RB.RibbonButtonBar(conPanel)

        self.add_ribbon_bar_button(conBar, 'console', '控制台', '控制台', self.on_console)
        self.add_ribbon_bar_button(conBar, 'console', '装配树', '装配树窗口', self.on_objectTree)
        
    def initFeatureRibbonView(self):
        general = RB.RibbonPage(self.ribbon, label='常规')

        # 显示模式
        displayPanel = RB.RibbonPanel(general, label='显示模式',style=RB.RIBBON_PANEL_NO_AUTO_MINIMISE)
        image = wx.StaticBitmap(displayPanel, wx.ID_ANY, svg2bmp(f'resources/display_mode.svg', (28,28)))
        title = wx.StaticText(displayPanel, wx.ID_ANY, '显示模式')
        leftSizer = wx.BoxSizer(wx.VERTICAL)
        leftSizer.Add(image, proportion=0, flag=wx.ALIGN_CENTER_HORIZONTAL)
        leftSizer.AddSpacer(5)
        leftSizer.Add(title, proportion=0, flag=wx.ALIGN_CENTER_HORIZONTAL)
        rightSizer = wx.GridSizer(2, 2, 5, 5)
        self.visualmode_body = self.add_checkbox(displayPanel, rightSizer, '体', self.on_visual_checkbox_body)
        self.visualmode_face = self.add_checkbox(displayPanel, rightSizer, '面', self.on_visual_checkbox_face)
        self.visualmode_line = self.add_checkbox(displayPanel, rightSizer, '线', self.on_visual_checkbox_line)
        self.visualmode_vertex = self.add_checkbox(displayPanel, rightSizer, '点', self.on_visual_checkbox_vertex)
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
        image = wx.StaticBitmap(selectPanel, wx.ID_ANY, svg2bmp(f'resources/selection_mode.svg', (28,28)))
        title = wx.StaticText(selectPanel, wx.ID_ANY, '选择模式')
        leftSizer = wx.BoxSizer(wx.VERTICAL)
        leftSizer.Add(image, wx.SizerFlags().CentreHorizontal())
        leftSizer.AddSpacer(5)
        leftSizer.Add(title, wx.SizerFlags().CentreHorizontal())
        rightSizer = wx.GridSizer(2, 2, 5, 5)
        self.selmode_body = self.add_checkbox(selectPanel, rightSizer, '体', self.on_sel_checkbox_body) 
        self.selmode_face = self.add_checkbox(selectPanel, rightSizer, '面', self.on_sel_checkbox_face) 
        self.selmode_line = self.add_checkbox(selectPanel, rightSizer, '线', self.on_sel_checkbox_line) 
        self.selmode_vertex = self.add_checkbox(selectPanel, rightSizer, '点', self.on_sel_checkbox_vertex) 
        sizer = wx.BoxSizer()
        sizer.AddSpacer(5)
        sizer.Add(leftSizer, proportion=0, flag=wx.ALIGN_CENTER_VERTICAL)
        sizer.AddSpacer(5)
        sizer.Add(rightSizer, proportion=0, flag=wx.ALIGN_CENTER_VERTICAL)
        sizer.AddSpacer(5)
        selectPanel.SetSizer(sizer)
        sizer.Layout()

        #simulation = RB.RibbonPage(self.ribbon, label='仿真')
        ssPanel = RB.RibbonPanel(general, label='创建网格',style=RB.RIBBON_PANEL_NO_AUTO_MINIMISE)
        ssBar = RB.RibbonButtonBar(ssPanel)
        self.add_ribbon_bar_button(ssBar, 'Simulation/create_surface_mesh', '面网格', '创建面网格', self.on_mesh_surface_generation)
        self.add_ribbon_bar_button(ssBar, 'Simulation/create_volume_mesh', '体网格', '创建体网格', self.on_mesh_volume_generation)
        
        meshPanel = RB.RibbonPanel(general, label='网格拾取',style=RB.RIBBON_PANEL_NO_AUTO_MINIMISE)
        image = wx.StaticBitmap(meshPanel, wx.ID_ANY, svg2bmp(f'resources/Simulation/mesh_setting.svg', (28,28)))
        title = wx.StaticText(meshPanel, wx.ID_ANY, '网格拾取')
        leftSizer = wx.BoxSizer(wx.VERTICAL)
        leftSizer.Add(image, proportion=0, flag=wx.ALIGN_CENTER_HORIZONTAL)
        leftSizer.AddSpacer(5)
        leftSizer.Add(title, proportion=0, flag=wx.ALIGN_CENTER_HORIZONTAL)
        rightSizer = wx.GridSizer(2, 3, 5, 5)
        self.mesh_visual_body = self.add_radiobutton(meshPanel, rightSizer, '几何', self.on_set_pickup_mesh, param = 0)
        self.mesh_visual_node = self.add_radiobutton(meshPanel, rightSizer, '节点', self.on_set_pickup_mesh, param = 1)
        self.mesh_visual_cell = self.add_radiobutton(meshPanel, rightSizer, '单元', self.on_set_pickup_mesh, param = 2)
        self.mesh_visual_face = self.add_radiobutton(meshPanel, rightSizer, '单元面', self.on_set_pickup_mesh, param = 3)
        self.mesh_visual_edge = self.add_radiobutton(meshPanel, rightSizer, '单元边', self.on_set_pickup_mesh, param = 4)
        sizer = wx.BoxSizer()
        sizer.AddSpacer(5)
        sizer.Add(leftSizer, proportion=0, flag=wx.ALIGN_CENTER_VERTICAL)
        sizer.AddSpacer(5)
        sizer.Add(rightSizer, proportion=0, flag=wx.ALIGN_CENTER_VERTICAL)
        sizer.AddSpacer(5)
        meshPanel.SetSizer(sizer)
        sizer.Layout()

        boxPanel = RB.RibbonPanel(general, label='演示',style=RB.RIBBON_PANEL_NO_AUTO_MINIMISE)
        boxBar = RB.RibbonButtonBar(boxPanel)
        self.add_ribbon_bar_button(boxBar, 'box', '长方体', '创建长方体', self.on_create_box_in_ReturnDialogData)


        boxPanel = RB.RibbonPanel(general, label='实训案例',style=RB.RIBBON_PANEL_NO_AUTO_MINIMISE)
        boxBar = RB.RibbonButtonBar(boxPanel)
        self.add_ribbon_bar_button(boxBar, 'element_edges', '获取单元内边数', '获取指定单元内边的数量', self.on_get_meshelement_count, True)
        # TODO：请在下一行中完成获取单元内面的数量的功能按钮添加，图标名称值必须传'element_faces'，注意最后一个参数的bool值，完成后可删除当前行

    def add_ribbon_bar_button(self, bar, name, title, tips, handle=None, param=None):
        id = wx.NewIdRef()
        bar.AddButton(id,  title,  svg2bmp(f'resources\\{name}.svg'), help_string=tips)
        if handle is not None:
            if param is not None:
                self.Bind(RB.EVT_RIBBONBUTTONBAR_CLICKED, partial(handle, param), id=id)
            else:
                self.Bind(RB.EVT_RIBBONBUTTONBAR_CLICKED, handler=handle, id=id)
        return id
        
    def add_checkbox(self, parent, sizer, title, handle=None, param=None):
        checkbox = wx.CheckBox(parent, label=title)
        sizer.Add(checkbox)
        if handle is not None:
            if param is not None:
                self.Bind(wx.EVT_CHECKBOX, partial(handle,self, param), checkbox)
            else:
                self.Bind(wx.EVT_CHECKBOX, handle, checkbox)
        return checkbox
    
    def add_radiobutton(self, parent, sizer, title, handle=None, param=None):
        radiobutton = wx.RadioButton(parent, label=title)
        sizer.Add(radiobutton)
        if handle is not None:
            if param is not None:
                self.Bind(wx.EVT_RADIOBUTTON, partial(handle, param), radiobutton)
            else:
                self.Bind(wx.EVT_RADIOBUTTON, partial(handle), radiobutton)
        return radiobutton

    def init_mode(self):
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

    def set_visual_mode(self, isface, isline, isvertex):
        if False == hasattr(self, 'doc'):
            return
        self.doc.SetVisualMode(isface, isline, isvertex)

    def on_visual_checkbox_body(self, event = None):
        if False == hasattr(self, 'doc'):
            return
        state = event.IsChecked()
        if state:
            self.set_visual_mode(1, 1, 1)
            self.visualmode_face.SetValue(True)
            self.visualmode_face.Enable(False)

            self.visualmode_line.SetValue(True)
            self.visualmode_line.Enable(False)

            self.visualmode_vertex.SetValue(True)
            self.visualmode_vertex.Enable(False)
        else:
            self.visualmode_face.Enable(True)
            self.visualmode_line.Enable(True)
            self.visualmode_vertex.Enable(True)

    def on_visual_checkbox_face(self, event = None):
        if False == hasattr(self, 'doc'):
            return
        state = event.IsChecked()
        ischecked_face = 1 if state == True else 0
        ischecked_line = 1 if self.visualmode_line.IsChecked() else 0
        ischecked_vertex = 1 if self.visualmode_vertex.IsChecked() else 0
        self.set_visual_mode(ischecked_face, ischecked_line, ischecked_vertex)

    def on_visual_checkbox_line(self, event = None):
        if False == hasattr(self, 'doc'):
            return
        state = event.IsChecked()
        ischecked_line = 1 if state == True else 0
        ischecked_face = 1 if self.visualmode_face.IsChecked() else 0
        ischecked_vertex = 1 if self.visualmode_vertex.IsChecked() else 0
        self.set_visual_mode(ischecked_face, ischecked_line, ischecked_vertex)

    def on_visual_checkbox_vertex(self, event = None):
        if False == hasattr(self, 'doc'):
            return
        state = event.IsChecked()
        ischecked_vertex = 1 if state == True else 0
        ischecked_line = 1 if self.visualmode_line.IsChecked() else 0
        ischecked_face = 1 if self.visualmode_face.IsChecked() else 0
        self.set_visual_mode(ischecked_face, ischecked_line, ischecked_vertex)
    
    def pyncti_select_mode(self, mode, isSelected):
        if mode == 0:
            self.doc.SetSelBody(isSelected)
            if isSelected == False:
                sel = self.NCTI.SelectionManager(self.doc)
                sel.ClearSelected()
            else:
                self.doc.SetSelFace(True)
                self.doc.SetSelLine(True)
                self.doc.SetSelVertex(True)
        else:
            if isSelected == False:
                self.doc.SetSelBody(isSelected)
            if mode == 1:
                self.doc.SetSelFace(isSelected)
            if mode == 2:
                self.doc.SetSelLine(isSelected)
            if mode == 3:
                self.doc.SetSelVertex(isSelected)
    
    def on_sel_checkbox_body(self, event):
        if False == hasattr(self, 'doc'):
            return
        state = event.IsChecked()
        if hasattr(self, 'doc'):
            self.pyncti_select_mode(0, state == True)
        if state == True:
            self.selmode_face.SetValue(True)
            self.selmode_line.SetValue(True)
            self.selmode_vertex.SetValue(True)

    def on_sel_checkbox_face(self, event):
        if False == hasattr(self, 'doc'):
            return
        state = event.IsChecked()
        if hasattr(self, 'doc'):
            self.pyncti_select_mode(1, state == True)
        if state != True:
            self.selmode_body.SetValue(False)

    def on_sel_checkbox_line(self, event):
        if False == hasattr(self, 'doc'):
            return
        state = event.IsChecked()
        if hasattr(self, 'doc'):
            self.pyncti_select_mode(2, state == True)
        if state != True:
            self.selmode_body.SetValue(False)

    def on_sel_checkbox_vertex(self, event):
        if False == hasattr(self, 'doc'):
            return
        state = event.IsChecked()
        if hasattr(self, 'doc'):
            self.pyncti_select_mode(3, state == True)
        if state != True:
            self.selmode_body.SetValue(False)

    # 文档页签下的基础功能
    def on_create_doc(self, event=None):
        """创建文档事件处理"""
        if -1 != self.HWND:
            self.doc.New("OCC","", "GMSH")  # 新建的文档默认调用OCC建模内核
            self.view = self.NCTI.View(self.doc.ID)
            self.view.CreateWindow(self.HWND)
            # 获取视图面板尺寸
            width, height = self.cad_view.GetSize()
            # 设置窗口可见性和几何尺寸
            self.view.SetWindowVis(True, self.doc.ID)
            self.view.SetGeometry(0, 0, width, height)
            # 更新文档
            self.doc.Update()
            self.doc.Zoom()

            self.cad_view.updateDoc(self.NCTI, self.doc, self.view)

    def on_close_doc(self, event):
        self.doc.Close()
        self.doc.Delete()
        self.updateTree()

    def on_import_file(self, event):
        """导入文件事件处理"""
        if -1 == self.doc.ID:
            wx.MessageBox("请先新建文档！", "提示", wx.OK | wx.ICON_INFORMATION)
            return
        # 创建文件选择对话框
        self.doc.ResetCaseResult()
        self.doc.SetCreateGeGeom(1)
        with wx.FileDialog(
                self,
                message="选取导入模型",
                defaultDir=".",
                defaultFile="",
                wildcard="Stp Files (*.stp)|*.stp|Step Files (*.step)|*.step|IGS Files (*.igs)|*.igs",
                style=wx.FD_OPEN | wx.FD_FILE_MUST_EXIST
        ) as dlg:
            if dlg.ShowModal() == wx.ID_OK:
                file_path = dlg.GetPath()
                self.doc.RunCommand("cmd_ncti_import_file", file_path)
                self.doc.Zoom()
                self.updateTree()
    def on_zoom(self, event):
        self.doc.Zoom()
        self.view.SetViewMode(0)
    def on_clean(self, event):
        self.doc.Clear()
        self.doc.ResetCaseResult()
        self.updateTree()
    def on_delete(self, event):
        self.doc.ResetCaseResult()
        sel = self.NCTI.SelectionManager(self.doc)
        if len(sel.ObjectNames) > 0:
            self.doc.RunCommand("cmd_ncti_delete", sel.ObjectNames)
            self.doc.Update()
            self.updateTree()
    def on_undo(self, event):
        self.doc.Undo()
        self.updateTree()
    def on_redo(self, event):
        self.doc.Redo()
        self.updateTree()

    def on_console(self, event=None):
        pane = self.mgr.GetPane(self.log_view)
        if pane.IsShown():
            pane.Show(False)
        else:
            pane.Show(True)
        self.mgr.Update()

    def on_objectTree(self, event=None):
        pane = self.mgr.GetPane(self.object_view)
        if pane.IsShown():
            pane.Show(False)
        else:
            pane.Show(True)
        self.mgr.Update()
    
    def updateTree(self):
        self.object_view.updateTree()

    # 常规页签下的案例方法
    def on_mesh_surface_generation(self,event = None):
        if False == hasattr(self, 'doc'):
            return
        self.doc.ShowMeshSettingDialog([{"网格命令": "面网格",
                                     "网格尺寸": "1",
                                     "网格类型": "全四边形", 
                                     "角度容差": "0.1",
                                     "曲率自适应": "0",
                                     "二阶网格": 0},self])
        self.updateTree()

    def on_mesh_volume_generation(self,event = None):
        if False == hasattr(self, 'doc'):
            return
        self.doc.ResetCaseResult()
        sel = self.NCTI.SelectionManager(self.doc)
        if len(sel.ObjectNames) > 0: 
            size = 1
            type = 0 #0:triangle,1:QuadDominant,2:FullQuad
            res  = self.doc.ReturnDialogData(-1, "请输入网格参数","网格尺寸", size,"网格类型", type)
            if len(res) > 0:
                name = sel.ObjectNames
                option = {"MeshSize":res[0],"MeshType":res[1]}
                self.doc.RunCommand("cmd_ncti_create_volume_mesh", name, option)
            else:
                print("取消")
        else:
            print("没有选择数据")
        self.updateTree()

    def on_set_pickup_mesh(self, state, event=None):
        if False == hasattr(self, 'doc'):
            return
        if state >= 0 and state < 5:
            sel = self.NCTI.SelectionManager(self.doc)
            sel.SetSelectGrid(state)

    def on_create_box_in_ReturnDialogData(self, event):
        self.doc.ResetCaseResult()
        length = 10.0
        width = 20.0
        height = 30.0
        pt = self.NCTI.Point(0, 0, 0)

        res = self.doc.ReturnDialogData(-1, "创建长方体参数", "长", length, "宽", width, "高", height, "顶点坐标", pt)
        if len(res) == 0 : 
            print("用户取消了操作")
        elif res[0] <= 0.0 or res[1] <= 0.0 or res[2] <= 0.0 :
            print("请输入合理的长方体的长、宽和高")
        else :
            length = res[0]
            width = res[1]
            height = res[2]
            pt = res[3]
            self.doc.RunCommand("cmd_ncti_create_box", "", pt, length, width, height)
            self.updateTree()

    def on_get_meshelement_count(self, show_edges, event=None):
        self.doc.ResetCaseResult()
        sel = self.NCTI.SelectionManager(self.doc)
        if len(sel.ObjectNames) == 1:
            window = ElementDialog(None, sel.ObjectNames[0], show_edges)
            if show_edges:
                window.initWidgets("获取单元内边数", "输入单元ID")
            else:
                window.initWidgets("获取单元内面数", "输入单元ID")
            window.Show()
        else:
            wx.MessageBox("请选中1个网格对象！", "提示", wx.OK | wx.ICON_INFORMATION)