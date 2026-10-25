import sys,ctypes
import os
from MainWindow import MainWindow
import wx

if __name__ == '__main__':
    if sys.platform == 'win32':
        ctypes.windll.shcore.SetProcessDpiAwareness(2)

    # 准备工作完成，启动wxPython应用界面
    app = wx.App()
    frame = MainWindow()
    app.MainLoop()
    sys.exit(app.ExitMainLoop())