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

# global_scope = {}

def InputDialog(*arg):
        # 初始化内置参数对话框
        argsList = list(arg)
        if len(argsList) % 2 != 0:
            print(f"输入参数错误: {arg}")
            wx.MessageBox.critical(None, "错误", f"输入参数错误: {arg}")
            return ()
        window = DialogData()
        #global global_scope
        #window.initNcti(global_scope["doc"], global_scope["NCTI"])
        window.initWidgets(*arg)
        if window.ShowModal() == wx.ID_OK:
            val = tuple(window.outList)
            #print(val)
            window.Destroy()
            return val
        window.Destroy()
        return {}

class MainWindow(wx.Frame):
    def __init__(self):
        super().__init__(None, title="CAE开发_数据集合(二)_几何集合", size=(1200, 800))
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
        self.initCaeFunRibbonView()
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

        #显示隐藏
        ssPanel = RB.RibbonPanel(general, label='显示隐藏',style=RB.RIBBON_PANEL_NO_AUTO_MINIMISE)        
        sizer = wx.GridSizer(2, 3, 5, 2)
        self._add_bitmap_button(ssPanel, sizer, 'show_all_model', '显示所有模型', self.on_display_all) 
        self._add_bitmap_button(ssPanel, sizer, 'hide_select_model', '隐藏已选中', self.on_hide_selected) 
        self._add_bitmap_button(ssPanel, sizer, 'show_select_model', '仅显示已选中', self.on_diaplay_selected_only) 
        self._add_bitmap_button(ssPanel, sizer, 'show_select_model', '显示网格', self.on_show_selected_grid) 
        self._add_bitmap_button(ssPanel, sizer, 'hide_select_model', '隐藏选中网格单元', self.on_hide_selected_grid_element) 
        self._add_bitmap_button(ssPanel, sizer, 'show_all_model', '仅显示选中网格单元', self.on_only_show_grid_element) 
        ssPanel.SetSizer(sizer)
        sizer.Layout()

        #simulation = RB.RibbonPage(self.ribbon, label='仿真')
        ssPanel = RB.RibbonPanel(general, label='创建网格',style=RB.RIBBON_PANEL_NO_AUTO_MINIMISE)
        ssBar = RB.RibbonButtonBar(ssPanel)
        self.add_ribbon_bar_button(ssBar, 'Simulation/create_surface_mesh', '面网格', '创建面网格', self.on_mesh_surface_generation)
        self.add_ribbon_bar_button(ssBar, 'Simulation/create_volume_mesh', '体网格', '创建体网格', self.on_mesh_volume_generation)
    
    #CAE开发
    def initCaeFunRibbonView(self):
        general = RB.RibbonPage(self.ribbon, label='CAE开发')

        ssPanel = RB.RibbonPanel(general, label='集合',style=RB.RIBBON_PANEL_NO_AUTO_MINIMISE)
        ssBar = RB.RibbonButtonBar(ssPanel)
        self.add_ribbon_bar_button(ssBar, 'Simulation/geometrySet', '几何Set', '几何Set', self.on_setGeometry)
        #TODO:请参考上一行代码在以下添加几何Set信息按钮，第二个参数用"Simulation/outMsg",最后一个参数用self.on_outMsg
        

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
    
    def _add_bitmap_button(self, parent, sizer, name, tips, handle=None, param=None):
        btn = wx.BitmapButton(parent, wx.ID_ANY, svg2bmp(f'resources/{name}.svg',size=(24, 24)))
        btn.SetToolTip(tips)
        btn.SetCanFocus(False)
        sizer.Add(btn)
        if handle is not None:
            if param is not None:
                self.Bind(wx.EVT_BUTTON, partial(handle, param), btn)
            else:
                self.Bind(wx.EVT_BUTTON, partial(handle), btn)
        return btn
    
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
            self.doc.New("OCC")  # 新建的文档默认调用OCC建模内核
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
            #设置选择模型,不选体
            self.doc.SetSelBody(False)
            self.selmode_body.SetValue(False)
            #设置显示点
            self.doc.SetVisualMode(True, True, True)
            self.visualmode_vertex.SetValue(True)
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
                                     "网格类型": "三角形", 
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

    #显示隐藏
    #显示所有模型
    def on_display_all(self, event = None):
        if False == hasattr(self, 'doc'):
            return   
        sel = self.NCTI.SelectionManager(self.doc)
        sel.ClearSelected()
        view = self.NCTI.View(self.doc.ID)
        view.ShowAll()
    #隐藏已选中
    def on_hide_selected(self, event = None):
        if False == hasattr(self, 'doc'):
            return 
        view = self.NCTI.View(self.doc.ID)
        sel = self.NCTI.SelectionManager(self.doc)
        names = sel.ObjectNames
        ids = sel.CellIDs
        sel.ClearSelected()
        view.SetObjVis(names, 0, ids)
        #sel = self.NCTI.SelectionManager(self.doc)
        #view.SetObjVis(sel.ObjectNames, 0, sel.CellIDs)
    #仅显示已选中
    def on_diaplay_selected_only(self, event = None):
        if False == hasattr(self, 'doc'):
            return   
        view = self.NCTI.View(self.doc.ID)
        sel = self.NCTI.SelectionManager(self.doc)
        view.ShowOnly(sel.ObjectNames, sel.CellIDs)
        sel.ClearSelected() 
    #显示网格
    def on_show_selected_grid(self, event = None):
        if False == hasattr(self, 'doc'):
            return   
        sel = self.NCTI.SelectionManager(self.doc)
        self.doc.ShowGrid()
        sel.ClearSelected()
    #隐藏选中网格单元
    def on_hide_selected_grid_element(self, event = None):
        if False == hasattr(self, 'doc'):
            return   
        sel = self.NCTI.SelectionManager(self.doc)
        self.doc.HideGridElement()
        sel.ClearSelected()
    #仅显示选中网格单元
    def on_only_show_grid_element(self, event = None):
        if False == hasattr(self, 'doc'):
            return   
        sel = self.NCTI.SelectionManager(self.doc)
        self.doc.OnlyShowGridElement()
        sel.ClearSelected()

    #几何Set
    def on_setGeometry(self, event=None):
        if -1 == self.doc.ID:
            wx.MessageBox("请先新建文档！", "提示", wx.OK | wx.ICON_INFORMATION)
            return
        self.doc.ResetCaseResult()  
        sel = self.NCTI.SelectionManager(self.doc)
        res  = self.NCTI.Dialog(-1, "添加修改几何set", 
                            "set名称","_Geo_Set_", 
                            "子单元类型",["节点", "单元", "表面"], 
                            "子对象",["选中子单元","选中对象所有对象对应子单元"],
                          )
        if len(res) < 1:
            return
        sel = self.NCTI.SelectionManager(self.doc)
        if len(sel.ObjectNames) == 0:
            print("请先选择对象！")
            return
        setType = 1 if res[1][0] == "节点" else 2 if res[1][0] == "单元" else 3  #节点、单元、表面
        setName = res[0] #set名称
        subObj = 1 if res[2][0] == "选中对象所有对象对应子单元" else 2  #子对象类型
        if subObj == 1:
            #选中对象所有对象对应子单元
            ObjectNames = list(set(sel.ObjectNames))
            for obj in ObjectNames:
                self.doc.RunCommand("cmd_ncti_mesh_add_set_geometry", setName, obj, setType)
        else:
            #选中子单元
            self.doc.RunCommand("cmd_ncti_mesh_add_set_geometry", setName, sel.ObjectNames[0], setType, sel.CellIDs)
        self.updateTree()
    
    #几何Set信息
    def on_outMsg(self, event=None):
        if -1 == self.doc.ID:
            wx.MessageBox("请先新建文档！", "提示", wx.OK | wx.ICON_INFORMATION)
            return
        self.doc.ResetCaseResult()  
        #TODO:请参考之前学习的内容完成输出各个类型几何Set名称的实现，完成后可删除当前行
        