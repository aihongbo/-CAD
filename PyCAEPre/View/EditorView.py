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
import wx, sys
import wx.stc as stc
import keyword
from Pub.ImageTransfrom import svg2bmp 

class EditorView(wx.Panel):
    def __init__(self, parent, ncti, doc, afterRun, runtime_path):
        super().__init__(parent)
        self.ncti = ncti
        self.doc = doc
        self.afterRun = afterRun

        # 执行按键
        self.btnRun = wx.BitmapButton(self, bitmap=svg2bmp(f"{runtime_path}/resources/editor/run.svg"))
        self.btnRun.SetToolTip("运行")
        self.btnOpen = wx.BitmapButton(self, bitmap=svg2bmp(f"{runtime_path}/resources/editor/open.svg"))
        self.btnOpen.SetToolTip("打开")
        btnSizer = wx.BoxSizer(wx.HORIZONTAL)
        btnSizer.Add(self.btnRun, 0, wx.ALIGN_LEFT)
        btnSizer.Add(self.btnOpen, 0, wx.ALIGN_LEFT)

        # 1. 脚本编辑器
        self.text_ctrl = stc.StyledTextCtrl(self)
        self.text_ctrl.SetText("# Python脚本\n")
        self._setup_stc_style()

        sizer = wx.BoxSizer(wx.VERTICAL)
        sizer.Add(btnSizer, 0, wx.ALIGN_LEFT)
        sizer.Add(self.text_ctrl, 1, wx.EXPAND)
        self.SetSizer(sizer)
        
        self.btnRun.Bind(wx.EVT_BUTTON, self.onRunScript)
        self.btnOpen.Bind(wx.EVT_BUTTON, self.onOpenFile)

    def _setup_stc_style(self):
        self.text_ctrl.SetLexer(stc.STC_LEX_PYTHON)
        self.text_ctrl.SetKeyWords(0, " ".join(keyword.kwlist))
        self.text_ctrl.StyleSetSpec(stc.STC_P_DEFAULT, "fore:#808080")
        self.text_ctrl.StyleSetSpec(stc.STC_P_COMMENTLINE, "fore:#007F00")
        self.text_ctrl.StyleSetSpec(stc.STC_P_NUMBER, "fore:#007F7F")
        self.text_ctrl.StyleSetSpec(stc.STC_P_STRING, "fore:#7F007F")
        self.text_ctrl.StyleSetSpec(stc.STC_P_CHARACTER, "fore:#7F007F")
        self.text_ctrl.StyleSetSpec(stc.STC_P_WORD, "fore:#00007F,bold")

    def onRunScript(self, event = None):
        script = self.text_ctrl.GetSelectedText()
        if len(script) == 0:
            script = self.text_ctrl.GetText()
        if len(script) == 0:
            return
        
        scope = {
            'doc': self.doc,
            'NCTI': self.ncti,
        }
        try:
            exec(script, scope) 
            print("执行完毕")
        except Exception as e:
            print(f"执行脚本发生了错误: {e}")
            return
        
        self.afterRun()
        

    def onOpenFile(self, event = None):
        dlg = wx.FileDialog(self, "打开Python脚本", wildcard="Python脚本 (*.py)|*.py", style=wx.FD_OPEN | wx.FD_FILE_MUST_EXIST)
        if dlg.ShowModal() == wx.ID_OK:
            path = dlg.GetPath()
            with open(path, 'r', encoding='utf-8') as file:
                content = file.read()
                self.text_ctrl.SetText(content)
        dlg.Destroy()