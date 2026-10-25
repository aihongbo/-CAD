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
import wx

def pyncti_open_ncti_file(NCTI,doc,hwnd):
    doc.ResetCaseResult()
    parent = wx.Frame(None)
    parent.Hide()

    dlg = wx.FileDialog(
        parent=parent,
        message="选取NCTI文件",
        wildcard="NCTI Files|*.ncti",
        style=wx.FD_OPEN | wx.FD_FILE_MUST_EXIST
    )
    path = None
    view = None
    if dlg.ShowModal() == wx.ID_OK:
        path = dlg.GetPath()     # 拿到绝对路径
        doc.Delete()
        doc.SetCreateGeGeom(1)
        doc.Open(path)
        view = NCTI.View(doc.ID)
        view.CreateWindow(hwnd) 
        view.SetWindowVis(True,doc.ID)
        doc.Zoom()
    dlg.Destroy()
    parent.Destroy()
    return view