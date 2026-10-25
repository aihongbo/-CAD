import sys
import os
import ctypes
import importlib
from functools import partial
from Pub.ImageTransfrom import svg2bmp
from Dialog.LogView import LogView
from Dialog.FormDialog import DialogData # type: ignore
from Dialog.RenderView import RenderView # type: ignore
import wx
import wx.aui
import wx.ribbon as RB

global_scope = {}

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

def init_NCTI_Config(dll_path):
    try:
        # 加载炎核开发引擎的建模内核、渲染引擎、Python接口
        sys.path.insert(0, dll_path)
        os.add_dll_directory(dll_path + '/OCC')  # occ_path
        ctypes.CDLL(dll_path + "/ncti_command.dll")
        ctypes.CDLL(dll_path + "/ncti_occ_plugin.dll")
        ctypes.CDLL(dll_path + "/ncti_render_vulkan.dll")
        NCTI = importlib.import_module("ncti_python")
        if 1 != NCTI.Init(dll_path):
            return None
        return NCTI
    except:
        print("System path error or loading dll failure!")
        return None

class MainWindow(wx.Frame):
    def __init__(self, NCTI, doc):
        super().__init__(None, title="CAD开发_实体建模(三)_实体拉伸操作", size=(1200, 800), style= wx.DEFAULT_FRAME_STYLE)
        # 初始化成员变量
        self.HWND = -1
        self.NCTI = NCTI
        self.doc = doc
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
        NCTI.SetPyInputDialogCallback(InputDialog)

    def init_main_layout(self):
        # 创建RibbonBar
        self.initViewRibbon()

        # 主内容区
        self.center_panel = wx.Panel(self)
        # 渲染窗口
        self.cad_view = RenderView(self.center_panel, self.NCTI, self.doc)
        self.HWND = self.cad_view.GetHandle()

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
        self.initExtrudeFunction()
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

        conPanel = RB.RibbonPanel(filePage, label=' ', style=RB.RIBBON_PANEL_NO_AUTO_MINIMISE)
        conBar = RB.RibbonButtonBar(conPanel)

        self.add_ribbon_bar_button(conBar, 'console', '控制台', '控制台', self.on_console)
        
    def initFeatureRibbonView(self):
        general = RB.RibbonPage(self.ribbon, label='常规')
        
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

    def initExtrudeFunction(self):
        sewingPage = RB.RibbonPage(self.ribbon, label="拉伸")

        editPanel = RB.RibbonPanel(sewingPage, label='实体建模',style=RB.RIBBON_PANEL_MINIMISE_BUTTON)
        editBar = RB.RibbonButtonBar(editPanel)
        self.add_ribbon_bar_button(editBar, 'oblique_circular_cylinder', '斜圆柱', '斜圆柱', self.on_oblique_circular_cylinder)
        # TODO: 请参考上一行代码在以下添加“斜平行六面体”的按钮，第二个参数用“oblique_parallelepiped”

    def add_ribbon_bar_button(self, bar, name, title, tips, handle=None, param=None):
        id = wx.NewIdRef()
        bar.AddButton(id,  title,  svg2bmp(f'resources\\{name}.svg'), help_string=tips)
        if handle is not None:
            if param is not None:
                self.Bind(RB.EVT_RIBBONBUTTONBAR_CLICKED, partial(handle, self, param), id=id)
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

    def init_mode(self):
        self.selmode_body.SetValue(True)
        self.selmode_face.SetValue(True)
        self.selmode_line.SetValue(True)
        self.selmode_vertex.SetValue(True)
    
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

            self.cad_view.updateDoc(self.NCTI, self.doc, self.view)

    def on_close_doc(self, event):
        self.doc.Close()
        self.doc.Delete()

    def on_import_file(self, event):
        """导入文件事件处理"""
        if -1 == self.doc.ID:
            wx.MessageBox("请先新建文档！", "提示", wx.OK | wx.ICON_INFORMATION)
            return
        # 创建文件选择对话框
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
    def on_zoom(self, event):
        self.doc.Zoom()
        self.view.SetViewMode(0)
    def on_clean(self, event):
        self.doc.Clear()
        self.doc.ResetCaseResult()
    def on_undo(self, event):
        self.doc.Undo()
    def on_redo(self, event):
        self.doc.Redo()

    def on_console(self, event=None):
        pane = self.mgr.GetPane(self.log_view)
        if pane.IsShown():
            pane.Show(False)
        else:
            pane.Show(True)
        self.mgr.Update()
    
    def on_oblique_circular_cylinder(self, event):
        self.doc.ResetCaseResult()
        if -1 == self.doc.ID:
            wx.MessageBox("请先新建文档！", "提示", wx.OK | wx.ICON_INFORMATION)
            return
        center = NCTI.Point(0,0,0)
        radius = 1
        circle_n = NCTI.Vector(0,0,1)
        circle_u = NCTI.Vector(1,0,0)
        extrude_dir = NCTI.Vector(0,0,1)
        res = self.doc.ReturnDialogData(-1, "斜圆柱参数设置", "底面圆心", center, "圆柱半径", radius, "圆心法向量", circle_n, "圆心轴向量", circle_u, "拉伸向量", extrude_dir)
        if len(res) == 0 : 
            print("用户取消了操作")
        elif res[1] <= 0.0:
            print("请输入大于0.0的半径")
        else:
            center = res[0]
            radius = res[1]
            circle_n = res[2]
            circle_u = res[3]
            extrude_dir = res[4]

            doc.RunCommand("cmd_ncti_create_circle", "circle_1", center, circle_n, circle_u, radius)
            doc.RunCommand("cmd_ncti_create_plane", "plane_1", "circle_1")
            doc.RunCommand("cmd_ncti_prism", "prism_1", "plane_1", extrude_dir)
            doc.RunCommand("cmd_ncti_delete", ["circle_1","plane_1"])
    
    # TODO: 请参考上述生成斜圆柱体的代码，在下方实现生成“斜平行六面体”的代码

if __name__ == '__main__':
    # 设置DPI感知适应
    if sys.platform == 'win32':
        ctypes.windll.shcore.SetProcessDpiAwareness(2)

    # 1，确认炎核开发引擎的安装路径，请按需配置实际路径
    # 以下是当前用户默认设置下安装的路径，一般情况下是可用的：
    dll_path = os.path.join(os.path.expanduser('~'), 'AppData/Local/Programs/YHCppSDK-Community/SDK/bin/RelWithDebInfo')
    # 以下是admin用户默认设置下安装的参考路径，请根据实际用户名确认该路径有效：
    # dll_path = 'C:/Users/Admin/AppData/Local/Programs/YHCppSDK-Community/SDK/bin/RelWithDebInfo'
    # 如果自行安装至如下所示的其它目录，请自行修改，并将目录分隔符号反斜杠"\"修改为正斜杠"/"：
    # dll_path = 'C:/Program Files (x86)/YHCppSDK-Community/SDK/bin/RelWithDebInfo'
    # dll_path = r'D:\MyProject\GitCode\NCTICAXSDK\Windows\RelWithDebInfo'
    if not os.path.exists(dll_path):
        # messagebox.showerror("安装路径检索错误",
        #                      "操作失败！请检查炎核开发引擎是否已正确安装、其安装路径与dll_path声明是否匹配。", icon='error')
        sys.exit(1)

    # 2，根据指定路径加载炎核开发引擎
    NCTI = init_NCTI_Config(dll_path)
    if None == NCTI:
        sys.exit(1)
    doc = NCTI.Document()
    global_scope["NCTI"] = NCTI
    global_scope["doc"] = doc

    # 3，准备工作完成，启动wxPython应用界面
    app = wx.App()
    frame = MainWindow(NCTI, doc)
    app.MainLoop()
