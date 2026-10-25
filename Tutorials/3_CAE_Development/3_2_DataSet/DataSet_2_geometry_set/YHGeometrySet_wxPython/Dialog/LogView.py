import wx, sys

class LogView(wx.TextCtrl):
    def __init__(self, parent):
        super().__init__(parent, style=wx.TE_READONLY | wx.TE_MULTILINE)
        self.SetBackgroundColour(wx.Colour(244, 250, 255))
        self.SetForegroundColour(wx.Colour(61, 61, 61))
        self._enableLog = False

        # 设置等宽字体
        font = wx.Font(10, wx.FONTFAMILY_TELETYPE, 
                      wx.FONTSTYLE_NORMAL, wx.FONTWEIGHT_NORMAL)
        self.SetFont(font)

        # 绑定右键菜单事件
        self.Bind(wx.EVT_CONTEXT_MENU, self.on_context_menu)
        
        # 创建右键菜单
        self.create_context_menu()

    def create_context_menu(self):
        self.context_menu = wx.Menu()
        self.menu_clear = self.context_menu.Append(wx.ID_ANY, "清空(&L)")
        self.Bind(wx.EVT_MENU, self.on_clear, self.menu_clear)

    def on_context_menu(self, event):
        self.PopupMenu(self.context_menu)

    def on_clear(self, event):
        self.Clear()

    def Destroy(self):
        if self._enableLog:
            sys.stdout = sys.__stdout__
            sys.stderr = sys.__stderr__
        super().Destroy()

    def enableLog(self, enable=True):
        self._enableLog = enable
        if enable:
            sys.stdout = self
            sys.stderr = self
        else:
            sys.stdout = sys.__stdout__
            sys.stderr = sys.__stderr__

    def write(self, msg):               # 文件接口
        if not msg.endswith('\n'):
            msg += '\n'
        if msg != '\n' and not msg.startswith(' >>>'):
            msg = ' >>> ' + msg
        wx.CallAfter(self.AppendText, msg)
