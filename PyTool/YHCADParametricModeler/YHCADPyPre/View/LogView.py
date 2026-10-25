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
import wx, sys

class LogView(wx.TextCtrl):
    def __init__(self, parent):
        super().__init__(parent, style=wx.TE_READONLY | wx.TE_MULTILINE)
        self.SetBackgroundColour(wx.Colour(255, 255, 255))
        self.SetForegroundColour(wx.Colour(0, 0, 0))
        self._enableLog = False

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
        wx.CallAfter(self.AppendText, msg)
