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
import sys,ctypes
import os
from Pub.configLoad import global_scope
from MainWindow import MainWindow
import wx

if __name__ == '__main__':
    if sys.platform == "win32":
        ctypes.windll.user32.SetProcessDPIAware(2)
    m_runtime_path = os.path.dirname(os.path.abspath(__file__))
    app = wx.App(False)
    MainWindow(m_runtime_path).Show()
    app.MainLoop() 
    sys.exit(app.ExitMainLoop())