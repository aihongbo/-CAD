#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Copyright (c) 2025 粤港澳大湾区（广东）国创中心
PyCAEPre is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details.
"""
import wx
from functools import partial

class RenderView(wx.Panel):
    def __init__(self, parent, ncti, doc):
        super().__init__(parent)
        self.doc = doc
        self.NCTI = ncti
        self.view = None

        self.Bind(wx.EVT_SIZE, self.updateView)


    def updateView(self, event=None):
        if self.view  == None:
            return
        if event != None:
            event.Skip()
        size = self.Size
        self.view.SetGeometry(0, 0, size.width, size.height)
        wx.CallLater(50, self.doc.Update)
        

    def updateDoc(self, ncti, doc, view):
        self.doc = doc
        self.NCTI = ncti
        self.view = view
