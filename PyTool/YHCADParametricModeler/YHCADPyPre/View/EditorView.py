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
import wx.stc as stc
import keyword
from Pub.ImageTransfrom import svg2bmp 
from Pub.configLoad import global_scope

class _ScriptErrorProxy:
    """兼容脚本里的 YH.Error() 用法。"""
    def __init__(self):
        self.state = 0
        self.message = ""

    def SetErrorState(self, state, message=""):
        self.state = state
        self.message = message

    def __str__(self):
        if self.message:
            return f"Error(state={self.state}, message={self.message})"
        return f"Error(state={self.state})"


class _ScriptYHProxy:
    """给脚本编辑器提供一个更接近 C++ 示例脚本的 YH 代理。"""
    def __init__(self, yh_module, ncti_module, yh_doc=None, host_window=None):
        self._yh_module = yh_module
        self._ncti_module = ncti_module
        self._yh_doc = yh_doc
        self._host_window = host_window

    def __getattr__(self, name):
        if self._yh_module is None:
            raise AttributeError(name)
        return getattr(self._yh_module, name)

    def Point(self, x=0, y=0, z=0):
        return self._ncti_module.Point(x, y, z)

    def Vector(self, x=0, y=0, z=0):
        return self._ncti_module.Vector(x, y, z)

    def Error(self):
        if self._yh_module is not None and hasattr(self._yh_module, "Error"):
            return self._yh_module.Error()
        return _ScriptErrorProxy()

    def SketchWorkPlane(self, *args):
        if self._yh_module is None or not hasattr(self._yh_module, "SketchWorkPlane"):
            raise AttributeError("SketchWorkPlane")

        # 兼容 C++ 项目里常见的单参数写法：YH.SketchWorkPlane(doc)
        if len(args) == 1:
            from scripts.Model.pyncti_create_sketch import pyncti_create_sketch

            sketch = pyncti_create_sketch(
                self._ncti_module,
                args[0],
                self._yh_module,
                self._yh_doc
            )
            if sketch and not isinstance(sketch, int):
                if self._host_window is not None:
                    self._host_window.activeSketch = sketch
                return sketch

            # 某些底层调用可能返回状态码，但草图对象已经存在，此时优先回退到当前活动草图。
            if self._host_window is not None:
                fallback_sketch = getattr(self._host_window, "activeSketch", None)
                if fallback_sketch is not None and not isinstance(fallback_sketch, int):
                    return fallback_sketch
            return sketch

        return self._yh_module.SketchWorkPlane(*args)


class EditorView(wx.Panel):
    def __init__(self, parent, ncti, doc, afterRun, runtime_path):
        super().__init__(parent)
        self.ncti = ncti
        self.doc = doc
        self.afterRun = afterRun
        self.script_scope = {}

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

    def _sync_script_scope(self):
        top_window = wx.GetTopLevelParent(self)
        yh_module = getattr(top_window, "YH", global_scope.get("YH")) if top_window else global_scope.get("YH")
        yh_doc = getattr(top_window, "yh_doc", global_scope.get("yh_doc")) if top_window else global_scope.get("yh_doc")
        active_sketch = getattr(top_window, "activeSketch", None) if top_window else None
        yh_script_proxy = _ScriptYHProxy(yh_module, self.ncti, yh_doc, top_window)

        self.script_scope.update({
            '__builtins__': __builtins__,
            'doc': self.doc,
            'NCTI': self.ncti,
            'YH': yh_script_proxy,
            'yh_doc': yh_doc,
            'activeSketch': active_sketch,
        })

        # 让右侧脚本里最常用的 skt 自动指向当前草图，避免每次重新创建。
        if active_sketch is not None and not isinstance(active_sketch, int):
            self.script_scope['skt'] = active_sketch

        return top_window

    def _sync_back_to_window(self, top_window):
        current_sketch = self.script_scope.get('skt')
        if current_sketch is None or isinstance(current_sketch, int):
            current_sketch = self.script_scope.get('activeSketch')

        if top_window is not None and current_sketch is not None and not isinstance(current_sketch, int):
            top_window.activeSketch = current_sketch
            self.script_scope['activeSketch'] = current_sketch

    def onRunScript(self, event = None):
        script = self.text_ctrl.GetSelectedText()
        if len(script) == 0:
            script = self.text_ctrl.GetText()
        if len(script) == 0:
            return

        # 脚本作用域持久化，避免每次运行都丢失 skt 等局部变量。
        top_window = self._sync_script_scope()
        try:
            exec(script, self.script_scope)
            self._sync_back_to_window(top_window)
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
