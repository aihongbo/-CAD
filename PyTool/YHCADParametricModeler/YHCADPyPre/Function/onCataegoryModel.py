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
from scripts.Model.pyncti_create_sketch import pyncti_create_sketch
from scripts.Model.pyncti_create_stretch import pyncti_create_stretch
from scripts.Model.pyncti_finish_sketch import pyncti_finish_sketch
from scripts.Sketch.Solve.pyncti_sketch_AutoSolve import pyncti_sketch_AutoSolve
import wx

def _ensure_default_document(mainWindow):
    if hasattr(mainWindow, "ensureDefaultDocument"):
        mainWindow.ensureDefaultDocument()

    if getattr(mainWindow, "YH", None) is None:
        return False

    if getattr(mainWindow, "yh_doc", None) is None:
        mainWindow.yh_doc = mainWindow.YH.YHDocument(mainWindow.doc)
    return True

def on_create_sketch_button_click(mainWindow, event=None):
    # 创建草图
    if False == hasattr(mainWindow, 'doc'):
        return
    if not _ensure_default_document(mainWindow):
        return

    sketch = pyncti_create_sketch(
        mainWindow.NCTI,
        mainWindow.doc,
        getattr(mainWindow, "YH", None),
        getattr(mainWindow, "yh_doc", None)
    )
    if sketch:
        mainWindow.activeSketch = sketch
        editor_view = getattr(mainWindow, "editor_view", None)
        if editor_view is not None and hasattr(editor_view, "script_scope"):
            editor_view.script_scope['activeSketch'] = sketch
            editor_view.script_scope['skt'] = sketch
        if not getattr(mainWindow, "_sketch_auto_solve_enabled", False):
            pyncti_sketch_AutoSolve(
                mainWindow.NCTI,
                mainWindow.doc,
                getattr(mainWindow, "yh_doc", None),
                True,
            )
            mainWindow._sketch_auto_solve_enabled = True
        mainWindow.doc.Update()
    mainWindow.updateTree()

def on_finish_sketch_button_click(mainWindow, event=None):
    # 完成草图
    if False == hasattr(mainWindow, 'doc'):
        return

    current_sketch = getattr(mainWindow, "activeSketch", None)
    finish_result = pyncti_finish_sketch(
        mainWindow.NCTI,
        mainWindow.doc,
        current_sketch
    )
    if finish_result is not None:
        mainWindow.lastFinishedSketch = current_sketch
        mainWindow.activeSketch = None
        editor_view = getattr(mainWindow, "editor_view", None)
        if editor_view is not None and hasattr(editor_view, "script_scope"):
            editor_view.script_scope['activeSketch'] = None
            editor_view.script_scope['lastFinishedSketch'] = current_sketch
    mainWindow.updateTree()

def _get_stretch_sketch(mainWindow):
    sketch = getattr(mainWindow, "lastFinishedSketch", None)
    if sketch is not None:
        return sketch

    sketch = getattr(mainWindow, "activeSketch", None)
    if sketch is not None:
        return sketch

    for method_name in ("GetActiveSketch", "GetActivitySketch"):
        if hasattr(mainWindow.doc, method_name):
            sketch = getattr(mainWindow.doc, method_name)()
            if sketch:
                return sketch

    return None

def _show_stretch_dialog(parent):
    dialog = wx.Dialog(parent, title="拉伸")
    main_sizer = wx.BoxSizer(wx.VERTICAL)

    section_box = wx.StaticBoxSizer(wx.VERTICAL, dialog, "截面曲线")
    section_box.Add(wx.StaticText(dialog, label="使用最近完成的草图"), 0, wx.ALL, 8)
    main_sizer.Add(section_box, 0, wx.ALL | wx.EXPAND, 8)

    direction_box = wx.StaticBoxSizer(wx.VERTICAL, dialog, "方向")
    direction_row = wx.BoxSizer(wx.HORIZONTAL)
    sketch_dir = wx.RadioButton(dialog, label="草图方向", style=wx.RB_GROUP)
    custom_dir = wx.RadioButton(dialog, label="指定矢量")
    reverse = wx.CheckBox(dialog, label="反向")
    direction_row.Add(sketch_dir, 0, wx.RIGHT | wx.ALIGN_CENTER_VERTICAL, 12)
    direction_row.Add(custom_dir, 0, wx.RIGHT | wx.ALIGN_CENTER_VERTICAL, 12)
    direction_row.Add(reverse, 0, wx.ALIGN_CENTER_VERTICAL)
    direction_box.Add(direction_row, 0, wx.ALL, 8)

    vector_grid = wx.FlexGridSizer(rows=1, cols=6, vgap=6, hgap=6)
    vector_grid.Add(wx.StaticText(dialog, label="X"), 0, wx.ALIGN_CENTER_VERTICAL)
    vector_x = wx.TextCtrl(dialog, value="0", size=(58, -1))
    vector_grid.Add(vector_x, 0)
    vector_grid.Add(wx.StaticText(dialog, label="Y"), 0, wx.ALIGN_CENTER_VERTICAL)
    vector_y = wx.TextCtrl(dialog, value="0", size=(58, -1))
    vector_grid.Add(vector_y, 0)
    vector_grid.Add(wx.StaticText(dialog, label="Z"), 0, wx.ALIGN_CENTER_VERTICAL)
    vector_z = wx.TextCtrl(dialog, value="1", size=(58, -1))
    vector_grid.Add(vector_z, 0)
    direction_box.Add(vector_grid, 0, wx.LEFT | wx.RIGHT | wx.BOTTOM, 8)
    main_sizer.Add(direction_box, 0, wx.LEFT | wx.RIGHT | wx.BOTTOM | wx.EXPAND, 8)

    limit_box = wx.StaticBoxSizer(wx.VERTICAL, dialog, "拉伸限制")
    limit_grid = wx.FlexGridSizer(rows=2, cols=3, vgap=8, hgap=8)
    limit_grid.AddGrowableCol(1, 1)
    limit_grid.Add(wx.StaticText(dialog, label="起始距离"), 0, wx.ALIGN_CENTER_VERTICAL)
    start_distance = wx.TextCtrl(dialog, value="0.00")
    limit_grid.Add(start_distance, 1, wx.EXPAND)
    limit_grid.Add(wx.StaticText(dialog, label="mm"), 0, wx.ALIGN_CENTER_VERTICAL)
    limit_grid.Add(wx.StaticText(dialog, label="终止距离"), 0, wx.ALIGN_CENTER_VERTICAL)
    end_distance = wx.TextCtrl(dialog, value="10.00")
    limit_grid.Add(end_distance, 1, wx.EXPAND)
    limit_grid.Add(wx.StaticText(dialog, label="mm"), 0, wx.ALIGN_CENTER_VERTICAL)
    limit_box.Add(limit_grid, 0, wx.ALL | wx.EXPAND, 8)
    main_sizer.Add(limit_box, 0, wx.LEFT | wx.RIGHT | wx.BOTTOM | wx.EXPAND, 8)

    boolean_box = wx.StaticBoxSizer(wx.VERTICAL, dialog, "布尔")
    boolean_choice = wx.Choice(dialog, choices=["无", "并集", "交集", "差集"])
    boolean_choice.SetSelection(0)
    boolean_box.Add(boolean_choice, 0, wx.ALL | wx.EXPAND, 8)
    main_sizer.Add(boolean_box, 0, wx.LEFT | wx.RIGHT | wx.BOTTOM | wx.EXPAND, 8)

    buttons = dialog.CreateButtonSizer(wx.OK | wx.CANCEL)
    main_sizer.Add(buttons, 0, wx.ALL | wx.ALIGN_RIGHT, 8)

    def update_vector_state(event=None):
        enabled = custom_dir.GetValue()
        vector_x.Enable(enabled)
        vector_y.Enable(enabled)
        vector_z.Enable(enabled)

    sketch_dir.Bind(wx.EVT_RADIOBUTTON, update_vector_state)
    custom_dir.Bind(wx.EVT_RADIOBUTTON, update_vector_state)
    update_vector_state()

    dialog.SetSizer(main_sizer)
    dialog.Fit()
    dialog.CenterOnParent()

    if dialog.ShowModal() != wx.ID_OK:
        dialog.Destroy()
        return None

    try:
        values = {
            "start_distance": float(start_distance.GetValue()),
            "end_distance": float(end_distance.GetValue()),
            "use_sketch_direction": sketch_dir.GetValue(),
            "reverse": reverse.GetValue(),
            "vector": (
                float(vector_x.GetValue()),
                float(vector_y.GetValue()),
                float(vector_z.GetValue()),
            ),
            "boolean_type": boolean_choice.GetSelection(),
        }
        if values["end_distance"] == 0:
            raise ValueError("终止距离不能为 0")
        if not values["use_sketch_direction"] and values["vector"] == (0.0, 0.0, 0.0):
            raise ValueError("指定矢量不能为 0,0,0")
    except ValueError as e:
        wx.MessageBox(str(e), "输入错误", wx.OK | wx.ICON_WARNING)
        dialog.Destroy()
        return None

    dialog.Destroy()
    return values

def on_create_stretch_button_click(mainWindow, event=None):
    # 拉伸
    if False == hasattr(mainWindow, 'doc'):
        return
    if not _ensure_default_document(mainWindow):
        return

    sketch = _get_stretch_sketch(mainWindow)
    if sketch is None:
        wx.MessageBox("请先创建并完成一个草图", "提示", wx.OK | wx.ICON_INFORMATION)
        return

    values = _show_stretch_dialog(mainWindow)
    if values is None:
        return

    result = pyncti_create_stretch(
        mainWindow.NCTI,
        mainWindow.doc,
        getattr(mainWindow, "yh_doc", None),
        sketch,
        values["end_distance"],
    )
    if result == 0:
        wx.MessageBox("found error", "提示", wx.OK | wx.ICON_INFORMATION)
        return
    if result is None:
        wx.MessageBox("拉伸创建失败，请确认草图存在可拉伸的封闭截面", "提示", wx.OK | wx.ICON_INFORMATION)
        return

    if result:
        if hasattr(result, "SetStartLimit"):
            result.SetStartLimit(values["start_distance"])
        if hasattr(result, "SetEndLimit"):
            result.SetEndLimit(values["end_distance"])
        if hasattr(result, "SetDirection"):
            sketch_dir_value = 1 if values["reverse"] else 0
            vector = mainWindow.NCTI.Vector(*values["vector"])
            point = mainWindow.NCTI.Point(0, 0, 0)
            result.SetDirection(values["use_sketch_direction"], sketch_dir_value, vector, point)
        if hasattr(result, "SetBooleanType"):
            result.SetBooleanType(values["boolean_type"])
        editor_view = getattr(mainWindow, "editor_view", None)
        if editor_view is not None and hasattr(editor_view, "script_scope"):
            editor_view.script_scope['lastStretch'] = result
            editor_view.script_scope['lastFinishedSketch'] = None
        mainWindow.lastFinishedSketch = None
        mainWindow.doc.Update()
    mainWindow.updateTree()
