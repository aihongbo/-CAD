import sys
import os
import ctypes
import importlib
import wx
import wx.aui
import wx.ribbon as RB
from functools import partial
from Pub.ImageTransfrom import svg2bmp
from Pub.configLoad import global_scope
from Dialog.LogView import LogView
from Dialog.FormDialog import DialogData # type: ignore
from Dialog.ObjectTreeView import ObjectTreeView # type: ignore
from Dialog.RenderView import RenderView # type: ignore
from Dialog.MeshDlg import MeshDialog # type: ignore
import Function.onPartAndAssembly as onPartAndAssembly
import datetime

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
        # window.initNcti(global_scope["doc"], global_scope["NCTI"])
        window.initWidgets(*arg)
        if window.ShowModal() == wx.ID_OK:
            val = tuple(window.outList)
            #print(val)
            return val
        return {}



class MainWindow(wx.Frame):
    def __init__(self):
        super().__init__(None, title="CAD开发_模型装配（一）_部件装配操作", size=(1200, 800))
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

        self.add_ribbon_bar_button(asmBar, 'create_assembly', '创建装配', '创建装配', self.on_create_assembly)
        self.add_ribbon_bar_button(asmBar, 'create_part', '创建零件', '创建零件', self.on_create_part)
        self.add_ribbon_bar_button(asmBar, 'add_assembly', '添加装配', '添加装配', self.on_add_assembly)
        self.add_ribbon_bar_button(asmBar, 'add_part', '添加零件', '添加零件', self.on_add_part)
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
    
    # def add_radiobutton(self, parent, sizer, title, handle=None, param=None):
    #     radiobutton = wx.RadioButton(parent, label=title)
    #     sizer.Add(radiobutton)
    #     if handle is not None:
    #         if param is not None:
    #             self.Bind(wx.EVT_RADIOBUTTON, partial(handle, param), radiobutton)
    #         else:
    #             self.Bind(wx.EVT_RADIOBUTTON, partial(handle), radiobutton)
    #     return radiobutton

    def init_mode(self):
        self.selmode_body.SetValue(True)
        self.selmode_face.SetValue(True)
        self.selmode_line.SetValue(True)
        self.selmode_vertex.SetValue(True)

        self.visualmode_body.SetValue(False)
        self.visualmode_face.SetValue(True)
        self.visualmode_line.SetValue(True)
        self.visualmode_vertex.SetValue(False)

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
    def on_create_assembly(self,event):
        if False == hasattr(self, 'doc'):
            return
        view = onPartAndAssembly.pyncti_new_assembly(self.NCTI,self.doc,self.HWND)
        if view == None:
            return   
        self.view = view 
        self.cad_view.updateDoc(self.NCTI,self.doc,self.view)
        self.cad_view.updateView()
        self.updateTree()

    def on_create_part(self,event):
        if False == hasattr(self, 'doc'):
            return
        view = onPartAndAssembly.pyncti_new_document(self.NCTI,self.doc,self.HWND)
        if view == None:
            return
        self.view = view
        self.cad_view.updateDoc(self.NCTI,self.doc,self.view)
        self.cad_view.updateView()
        self.updateTree()

    def on_add_assembly(self,event):
        if False == hasattr(self, 'doc'):
            return
        self.doc.ResetCaseResult()
        onPartAndAssembly.pyncti_add_assembly(self.NCTI,self.doc)
        self.cad_view.updateView()
        self.updateTree()

    def on_add_part(self, event):
        if False == hasattr(self, 'doc'):
            return
        self.doc.ResetCaseResult()
        onPartAndAssembly.pyncti_add_part(self.NCTI,self.doc)
        self.cad_view.updateView()
        self.updateTree()

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
