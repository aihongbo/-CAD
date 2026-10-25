import sys
import os
import ctypes
import importlib
import wx
import wx.aui



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
        super().__init__(None, title="炎核看图工具V1.0(使用wxPython开发)", size=(1200, 800))
        # 初始化成员变量
        self.HWND = -1
        self.NCTI = NCTI
        self.doc = doc
        self.view = None
        self.array_x = 0
        # 初始化主布局
        self.init_main_layout()
        # 获取视图面板的句柄
        self.HWND = self.view_panel.GetHandle()
        # 显示窗口
        self.Centre()
        self.Show()
        # 更新布局以确保正确计算尺寸
        self.Layout()

    def init_main_layout(self):
        # 创建AUI管理器 - 这是整个应用的布局管理器
        self.aui_manager = wx.aui.AuiManager(self)
        # 创建顶部选项卡面板
        top_panel = wx.Panel(self)
        top_sizer = wx.BoxSizer(wx.VERTICAL)
        # 创建选项卡控件
        self.notebook = wx.Notebook(top_panel, wx.ID_ANY, style=wx.NB_TOP)
        self.doc_tab = wx.Panel(self.notebook)
        self.view_tab = wx.Panel(self.notebook)
        self.cad_tab = wx.Panel(self.notebook)
        self.caepre_tab = wx.Panel(self.notebook)
        # 添加选项卡到notebook
        self.notebook.AddPage(self.doc_tab, "   文档")
        self.notebook.AddPage(self.view_tab, "看图")
        # 创建选项卡的工具栏
        doc_toolbar = wx.ToolBar(self.doc_tab, wx.ID_ANY, style=wx.TB_FLAT | wx.TB_TEXT)
        view_toolbar = wx.ToolBar(self.view_tab, wx.ID_ANY, style=wx.TB_FLAT | wx.TB_TEXT)

        # 选项卡按钮列表：选项卡名--按钮--按钮文本
        buttons = [
            (doc_toolbar, self.on_create_doc, "创建文档"),
            (doc_toolbar, self.on_close_doc, "关闭文档"),
            (view_toolbar, self.on_import_file, "导入模型"),
            (view_toolbar, self.on_zoom, "复位模型"),
            (view_toolbar, self.on_clean, "清空文档"),
        ]
        for i in buttons:
            # 添加点击按钮事件、按钮及对应图标，并将响应函数与点击按钮事件绑定
            this_button_id = wx.NewIdRef()
            i[0].AddTool(this_button_id, i[2], wx.Bitmap.FromRGBA(36, 36, *[200//2,220//2,255//2,255]), shortHelp=i[2])
            # 可自行定制图标icon，使用wx.Bitmap({图片文件路径})作为上述方法的第三个"bitmap"参数即可
            i[0].Bind(wx.EVT_TOOL, i[1], id=this_button_id)
            i[0].Realize()

        # 将notebook添加到顶部面板
        top_sizer.Add(self.notebook, 1, wx.EXPAND)
        top_panel.SetSizer(top_sizer)
        # 使用AUI管理器添加所有面板，设置正确的层级关系
        self.aui_manager.AddPane(top_panel,
                                 wx.aui.AuiPaneInfo().Top().
                                 CaptionVisible(False).
                                 CloseButton(False).
                                 Floatable(False).
                                 DockFixed(True).
                                 Layer(0).
                                 Position(0).
                                 BestSize(-1, 100))
        # 创建3D视图区域（使用Panel作为占位符）
        self.view_panel = wx.Panel(self, style=wx.SUNKEN_BORDER)
        self.view_panel.SetBackgroundColour(wx.Colour(200, 220, 255))
        self.aui_manager.AddPane(self.view_panel,
                                 wx.aui.AuiPaneInfo().Center().
                                 CaptionVisible(False).
                                 CloseButton(False).
                                 Floatable(False).
                                 DockFixed(True).
                                 Layer(1).
                                 Position(1))
        self.aui_manager.Update()


    # 创建和关闭文档的响应函数
    def on_create_doc(self, event):
        """创建文档事件处理"""
        if -1 != self.HWND:
            self.doc.New("OCC")  # 新建的文档默认调用OCC建模内核
            self.view = self.NCTI.View(self.doc.ID)
            self.view.CreateWindow(self.HWND)
            # 获取视图面板尺寸
            width, height = self.view_panel.GetSize()
            # 设置窗口可见性和几何尺寸
            self.view.SetWindowVis(True, self.doc.ID)
            self.view.SetGeometry(0, 0, width, height)
            # 更新文档
            self.doc.Update()
            self.doc.Zoom()
    def on_close_doc(self, event):
        self.doc.Close()


    # 导入模型和看图场景的响应函数
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


if __name__ == '__main__':
    # 1，确认炎核开发引擎的安装路径，请按需配置实际路径
    # 以下是当前用户默认设置下安装的路径，一般情况下是可用的：
    dll_path = os.path.join(os.path.expanduser('~'), 'AppData/Local/Programs/YHCppSDK-Community/SDK/bin/RelWithDebInfo')
    # 以下是admin用户默认设置下安装的参考路径，请根据实际用户名确认该路径有效：
    # dll_path = 'C:/Users/Admin/AppData/Local/Programs/YHCppSDK-Community/SDK/bin/RelWithDebInfo'
    # 如果自行安装至如下所示的其它目录，请自行修改，并将目录分隔符号反斜杠"\"修改为正斜杠"/"：
    # dll_path = 'C:/Program Files (x86)/YHCppSDK-Community/SDK/bin/RelWithDebInfo'
    if not os.path.exists(dll_path):
        # messagebox.showerror("安装路径检索错误",
        #                      "操作失败！请检查炎核开发引擎是否已正确安装、其安装路径与dll_path声明是否匹配。", icon='error')
        sys.exit(1)

    # 2，根据指定路径加载炎核开发引擎
    NCTI = init_NCTI_Config(dll_path)
    if None == NCTI:
        sys.exit(1)
    doc = NCTI.Document()

    # 3，准备工作完成，启动wxPython应用界面
    app = wx.App()
    frame = MainWindow(NCTI, doc)
    app.MainLoop()
