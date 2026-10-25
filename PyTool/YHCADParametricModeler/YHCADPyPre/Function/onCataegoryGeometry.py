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
from scripts.Geometry.pyncti_boolean import (
    pyncti_boolean_intersection,
    pyncti_boolean_subtraction,
    pyncti_boolean_union,
)
from scripts.Geometry.pyncti_chamfer import pyncti_chamfer
from scripts.Geometry.pyncti_circular_array import pyncti_circular_array
from scripts.Geometry.pyncti_create_box import pyncti_create_box
from scripts.Geometry.pyncti_create_cone import pyncti_create_cone
from scripts.Geometry.pyncti_create_cylinder import pyncti_create_cylinder
from scripts.Geometry.pyncti_create_sphere import pyncti_create_sphere
from scripts.Geometry.pyncti_fillet import pyncti_fillet
from scripts.Geometry.pyncti_linear_array import pyncti_linear_array
from scripts.Geometry.pyncti_prism import pyncti_prism
from scripts.Geometry.pyncti_rotate import pyncti_rotate
from scripts.Geometry.pyncti_shelling import pyncti_shelling
from scripts.Model.pyncti_select_mode import pyncti_select_mode


def _show_geometry_form_dialog(parent, title, fields=None, min_size=(360, 180), variant_selector=None):
    dialog = wx.Dialog(parent, title=title)
    controls = {}
    sizer = wx.BoxSizer(wx.VERTICAL)

    if variant_selector is not None:
        variant_sizer = wx.BoxSizer(wx.HORIZONTAL)
        variant_sizer.Add(wx.StaticText(dialog, label="方式"), 0, wx.ALIGN_CENTER_VERTICAL | wx.RIGHT, 8)
        variant_choice = wx.Choice(dialog, choices=[item[0] for item in variant_selector])
        variant_choice.SetSelection(0)
        variant_sizer.Add(variant_choice, 1, wx.EXPAND)
        sizer.Add(variant_sizer, 0, wx.ALL | wx.EXPAND, 12)

        form_panel = wx.Panel(dialog)
        form_sizer = wx.BoxSizer(wx.VERTICAL)
        form_panel.SetSizer(form_sizer)
        sizer.Add(form_panel, 1, wx.LEFT | wx.RIGHT | wx.BOTTOM | wx.EXPAND, 12)

        def rebuild_fields(field_items):
            controls.clear()
            form_panel.DestroyChildren()
            grid = wx.FlexGridSizer(rows=0, cols=2, vgap=8, hgap=8)
            grid.AddGrowableCol(1, 1)

            for key, label, default_value in field_items:
                if isinstance(default_value, (list, tuple)):
                    control = wx.Choice(form_panel, choices=list(default_value))
                    control.SetSelection(0)
                else:
                    control = wx.TextCtrl(form_panel, value=str(default_value), size=(220, -1))
                controls[key] = control
                grid.Add(wx.StaticText(form_panel, label=label), 0, wx.ALIGN_CENTER_VERTICAL)
                grid.Add(control, 1, wx.EXPAND)

            form_sizer.Clear(False)
            form_sizer.Add(grid, 1, wx.EXPAND)
            form_panel.Layout()

        def rebuild_variant():
            _, field_items = variant_selector[variant_choice.GetSelection()]
            rebuild_fields(field_items)
            dialog.Layout()
            dialog.Fit()

        variant_choice.Bind(wx.EVT_CHOICE, lambda event: rebuild_variant())
        rebuild_variant()
    else:
        grid = wx.FlexGridSizer(rows=0, cols=2, vgap=8, hgap=8)
        grid.AddGrowableCol(1, 1)
        for key, label, default_value in fields or []:
            if isinstance(default_value, (list, tuple)):
                control = wx.Choice(dialog, choices=list(default_value))
                control.SetSelection(0)
            else:
                control = wx.TextCtrl(dialog, value=str(default_value), size=(220, -1))
            controls[key] = control
            grid.Add(wx.StaticText(dialog, label=label), 0, wx.ALIGN_CENTER_VERTICAL)
            grid.Add(control, 1, wx.EXPAND)
        sizer.Add(grid, 1, wx.ALL | wx.EXPAND, 12)

    buttons = dialog.CreateButtonSizer(wx.OK | wx.CANCEL)
    sizer.Add(buttons, 0, wx.ALL | wx.ALIGN_RIGHT, 12)
    dialog.SetSizer(sizer)
    dialog.SetMinSize(min_size)
    dialog.Fit()
    dialog.CenterOnParent()

    if dialog.ShowModal() != wx.ID_OK:
        dialog.Destroy()
        return None

    values = {}
    for key, control in controls.items():
        if isinstance(control, wx.Choice):
            values[key] = control.GetStringSelection()
        else:
            values[key] = control.GetValue()
    if variant_selector is not None:
        values["variant"] = variant_choice.GetStringSelection()
    dialog.Destroy()
    return values


def _parse_point(text):
    values = [item.strip() for item in text.replace("，", ",").split(",")]
    if len(values) == 2:
        values.append("0")
    if len(values) != 3:
        raise ValueError("点坐标格式应为 x,y 或 x,y,z")
    return tuple(float(value) for value in values)


def _parse_vector(text):
    values = [item.strip() for item in text.replace("，", ",").split(",")]
    if len(values) == 2:
        values.append("0")
    if len(values) != 3:
        raise ValueError("向量格式应为 x,y 或 x,y,z")
    vector = tuple(float(value) for value in values)
    if vector == (0.0, 0.0, 0.0):
        raise ValueError("向量不能为 0,0,0")
    return vector


def _get_selection(mainWindow):
    return mainWindow.NCTI.SelectionManager(mainWindow.doc)


def _ensure_yh_doc(mainWindow):
    """确保几何命令使用带有 YH 特征接口的文档包装。"""
    if hasattr(mainWindow, "ensureDefaultDocument"):
        mainWindow.ensureDefaultDocument()
    yh_doc = getattr(mainWindow, "yh_doc", None)
    if yh_doc is None or not hasattr(yh_doc, "CreateBox"):
        wx.MessageBox("YH文档未初始化，请先创建或打开文档", "提示", wx.OK | wx.ICON_INFORMATION)
        return None
    return yh_doc


def on_create_datum_plane(mainWindow, event=None):
    yh_doc = _ensure_yh_doc(mainWindow)
    if yh_doc is None or not hasattr(yh_doc, "CreateFTDatumPlane"):
        return
    result = yh_doc.CreateFTDatumPlane()
    if not result:
        _show_error("基准平面创建失败")
        return
    _after_geometry_command(mainWindow)


def on_create_coordinate_system(mainWindow, event=None):
    yh_doc = _ensure_yh_doc(mainWindow)
    if yh_doc is None or not hasattr(yh_doc, "CreatCoordinateSystem"):
        return
    result = yh_doc.CreatCoordinateSystem()
    if not result:
        _show_error("基准坐标系创建失败")
        return
    _after_geometry_command(mainWindow)


def _after_geometry_command(mainWindow):
    if hasattr(mainWindow, "doc"):
        try:
            mainWindow.doc.Update()
        except Exception as e:
            print(f"_after_geometry_command: doc.Update failed: {e}")
    if hasattr(mainWindow, "updateTree"):
        mainWindow.updateTree()
    if hasattr(mainWindow, "autoSizeView"):
        mainWindow.autoSizeView()


def _show_error(message):
    wx.MessageBox(message, "输入错误", wx.OK | wx.ICON_WARNING)


def on_create_box(mainWindow, event=None):
    if not hasattr(mainWindow, "doc") or _ensure_yh_doc(mainWindow) is None:
        return

    values = _show_geometry_form_dialog(
        mainWindow,
        "创建长方体",
        [
            ("point", "顶点坐标", "0,0,0"),
            ("length", "长", "10"),
            ("width", "宽", "20"),
            ("height", "高", "30"),
        ],
    )
    if values is None:
        return

    try:
        point = _parse_point(values["point"])
        length = float(values["length"])
        width = float(values["width"])
        height = float(values["height"])
        if length <= 0 or width <= 0 or height <= 0:
            raise ValueError("长、宽、高都必须大于 0")
    except ValueError as e:
        _show_error(str(e))
        return

    pt = mainWindow.NCTI.Point(point[0], point[1], point[2])
    result = pyncti_create_box(
        mainWindow.NCTI,
        mainWindow.doc,
        getattr(mainWindow, "YH", None),
        getattr(mainWindow, "yh_doc", None),
        pt,
        length,
        width,
        height,
    )
    _after_geometry_command(mainWindow)


def on_create_cylinder(mainWindow, event=None):
    if not hasattr(mainWindow, "doc") or _ensure_yh_doc(mainWindow) is None:
        return

    values = _show_geometry_form_dialog(
        mainWindow,
        "创建圆柱体",
        [
            ("radius", "半径", "10"),
            ("height", "高度", "20"),
            ("point", "底面原点", "0,0,0"),
            ("normal", "法向", "0,0,1"),
        ],
        min_size=(380, 220),
    )
    if values is None:
        return

    try:
        radius = float(values["radius"])
        height = float(values["height"])
        point = _parse_point(values["point"])
        normal = _parse_vector(values["normal"])
        if radius <= 0 or height <= 0:
            raise ValueError("半径和高度都必须大于 0")
    except ValueError as e:
        _show_error(str(e))
        return

    pt = mainWindow.NCTI.Point(point[0], point[1], point[2])
    n = mainWindow.NCTI.Vector(normal[0], normal[1], normal[2])
    result = pyncti_create_cylinder(
        mainWindow.NCTI,
        mainWindow.doc,
        getattr(mainWindow, "YH", None),
        getattr(mainWindow, "yh_doc", None),
        pt,
        n,
        radius,
        height,
    )
    _after_geometry_command(mainWindow)


def on_create_cone(mainWindow, event=None):
    if not hasattr(mainWindow, "doc") or _ensure_yh_doc(mainWindow) is None:
        return

    values = _show_geometry_form_dialog(
        mainWindow,
        "创建圆锥体",
        [
            ("point", "底面原点", "0,0,0"),
            ("vector", "轴向", "0,0,1"),
            ("bottom_diameter", "底面直径", "20"),
            ("top_diameter", "顶面直径", "0"),
            ("height", "高度", "30"),
        ],
        min_size=(380, 240),
    )
    if values is None:
        return

    try:
        point = _parse_point(values["point"])
        vector = _parse_vector(values["vector"])
        bottom_diameter = float(values["bottom_diameter"])
        top_diameter = float(values["top_diameter"])
        height = float(values["height"])
        if bottom_diameter <= 0 or top_diameter < 0 or height <= 0:
            raise ValueError("直径和高度参数不合法")
    except ValueError as e:
        _show_error(str(e))
        return

    pt = mainWindow.NCTI.Point(point[0], point[1], point[2])
    vec = mainWindow.NCTI.Vector(vector[0], vector[1], vector[2])
    result = pyncti_create_cone(
        mainWindow.NCTI,
        mainWindow.doc,
        getattr(mainWindow, "YH", None),
        getattr(mainWindow, "yh_doc", None),
        pt,
        vec,
        bottom_diameter,
        top_diameter,
        height,
    )
    _after_geometry_command(mainWindow)


def on_create_sphere(mainWindow, event=None):
    if not hasattr(mainWindow, "doc") or _ensure_yh_doc(mainWindow) is None:
        return

    values = _show_geometry_form_dialog(
        mainWindow,
        "创建球体",
        [
            ("point", "球心坐标", "0,0,0"),
            ("radius", "半径", "10"),
        ],
        min_size=(360, 180),
    )
    if values is None:
        return

    try:
        point = _parse_point(values["point"])
        radius = float(values["radius"])
        if radius <= 0:
            raise ValueError("半径必须大于 0")
    except ValueError as e:
        _show_error(str(e))
        return

    pt = mainWindow.NCTI.Point(point[0], point[1], point[2])
    result = pyncti_create_sphere(
        mainWindow.NCTI,
        mainWindow.doc,
        getattr(mainWindow, "YH", None),
        getattr(mainWindow, "yh_doc", None),
        pt,
        radius,
    )
    _after_geometry_command(mainWindow)


def on_fillet(mainWindow, event=None):
    if not hasattr(mainWindow, "doc"):
        return

    yh_doc = _ensure_yh_doc(mainWindow)
    if yh_doc is None:
        return

    # 先切换到边选择模式，再由底层特征命令读取 3D 选择集。
    pyncti_select_mode(mainWindow.NCTI, mainWindow.doc, 2, True)

    values = _show_geometry_form_dialog(
        mainWindow,
        "圆角",
        [("radius", "半径", "0.5")],
    )
    if values is None:
        return

    try:
        radius = float(values["radius"])
        if radius <= 0:
            raise ValueError("半径必须大于 0")
    except ValueError as e:
        _show_error(str(e))
        return

    pyncti_fillet(mainWindow.NCTI, mainWindow.doc, yh_doc, radius)
    _after_geometry_command(mainWindow)


def on_chamfer(mainWindow, event=None):
    if not hasattr(mainWindow, "doc"):
        return

    yh_doc = _ensure_yh_doc(mainWindow)
    if yh_doc is None:
        return

    # 先切换到边选择模式，再由底层特征命令读取 3D 选择集。
    pyncti_select_mode(mainWindow.NCTI, mainWindow.doc, 2, True)

    values = _show_geometry_form_dialog(
        mainWindow,
        "斜角",
        [("distance", "距离", "0.5")],
    )
    if values is None:
        return

    try:
        distance = float(values["distance"])
        if distance <= 0:
            raise ValueError("距离必须大于 0")
    except ValueError as e:
        _show_error(str(e))
        return

    pyncti_chamfer(mainWindow.NCTI, mainWindow.doc, yh_doc, distance)
    _after_geometry_command(mainWindow)


def on_prism(mainWindow, event=None):
    if not hasattr(mainWindow, "doc"):
        return

    sel = _get_selection(mainWindow)
    if len(sel.ObjectNames) == 0:
        wx.MessageBox("请先选择一个对象", "提示", wx.OK | wx.ICON_INFORMATION)
        return

    values = _show_geometry_form_dialog(
        mainWindow,
        "拉伸",
        [
            ("vector", "方向向量", "1,0,0"),
            ("length", "大小", "1"),
        ],
    )
    if values is None:
        return

    try:
        vector = _parse_vector(values["vector"])
        length = float(values["length"])
    except ValueError as e:
        _show_error(str(e))
        return

    vec = mainWindow.NCTI.Vector(vector[0] * length, vector[1] * length, vector[2] * length)
    pyncti_prism(mainWindow.NCTI, mainWindow.doc, getattr(mainWindow, "yh_doc", None), vec, length)
    _after_geometry_command(mainWindow)


def on_rotate(mainWindow, event=None):
    if not hasattr(mainWindow, "doc"):
        return

    yh_doc = _ensure_yh_doc(mainWindow)
    if yh_doc is None:
        return

    result = pyncti_rotate(mainWindow.NCTI, mainWindow.doc, yh_doc)
    if not result:
        _show_error("旋转特征创建失败")
        return
    _after_geometry_command(mainWindow)


def on_boolean(mainWindow, event=None):
    if not hasattr(mainWindow, "doc"):
        return
    yh_doc = _ensure_yh_doc(mainWindow)
    if yh_doc is None:
        return

    if event in ("union", "subtraction", "intersection"):
        mode = {"union": "并集", "subtraction": "差集", "intersection": "交集"}[event]
    else:
        values = _show_geometry_form_dialog(
            mainWindow,
            "布尔运算",
            [("mode", "运算类型", ["并集", "差集", "交集"])],
        )
        if values is None:
            return
        mode = values["mode"]

    if mode == "并集":
        result = pyncti_boolean_union(mainWindow.NCTI, mainWindow.doc, yh_doc)
    elif mode == "交集":
        result = pyncti_boolean_intersection(mainWindow.NCTI, mainWindow.doc, yh_doc)
    else:
        result = pyncti_boolean_subtraction(mainWindow.NCTI, mainWindow.doc, yh_doc)

    if not result:
        _show_error("布尔特征创建失败")
        return
    _after_geometry_command(mainWindow)


def on_boolean_subtraction(mainWindow, event=None):
    if not hasattr(mainWindow, "doc"):
        return
    yh_doc = _ensure_yh_doc(mainWindow)
    if yh_doc is None:
        return

    result = pyncti_boolean_subtraction(mainWindow.NCTI, mainWindow.doc, yh_doc)
    if not result:
        _show_error("布尔差集创建失败")
        return
    _after_geometry_command(mainWindow)


def on_boolean_intersection(mainWindow, event=None):
    if not hasattr(mainWindow, "doc"):
        return
    yh_doc = _ensure_yh_doc(mainWindow)
    if yh_doc is None:
        return

    result = pyncti_boolean_intersection(mainWindow.NCTI, mainWindow.doc, yh_doc)
    if not result:
        _show_error("布尔交集创建失败")
        return
    _after_geometry_command(mainWindow)


def on_array_linear(mainWindow, event=None):
    """调用底层线性阵列交互命令。"""
    if not hasattr(mainWindow, "doc"):
        return
    yh_doc = _ensure_yh_doc(mainWindow)
    if yh_doc is None:
        return

    pyncti_linear_array(mainWindow.NCTI, mainWindow.doc, yh_doc)
    _after_geometry_command(mainWindow)


def on_draft(mainWindow, event=None):
    """调用底层拔模交互命令，当前选择的面作为拔模面。"""
    if not hasattr(mainWindow, "doc"):
        return
    yh_doc = _ensure_yh_doc(mainWindow)
    if yh_doc is None or not hasattr(yh_doc, "Depouille"):
        return

    result = yh_doc.Depouille()
    if not result:
        _show_error("拔模创建失败，请确认选择的是实体面")
        return
    _after_geometry_command(mainWindow)


def on_array_circular(mainWindow, event=None):
    if not hasattr(mainWindow, "doc"):
        return
    yh_doc = _ensure_yh_doc(mainWindow)
    if yh_doc is None:
        return

    pyncti_circular_array(mainWindow.NCTI, mainWindow.doc, yh_doc)
    _after_geometry_command(mainWindow)


def on_shelling(mainWindow, event=None):
    """调用底层抽壳交互命令。"""
    if not hasattr(mainWindow, "doc"):
        return
    yh_doc = _ensure_yh_doc(mainWindow)
    if yh_doc is None:
        return

    result = pyncti_shelling(mainWindow.NCTI, mainWindow.doc, yh_doc)
    if not result:
        _show_error("抽壳创建失败")
        return
    _after_geometry_command(mainWindow)


def on_array_curve(mainWindow, event=None):
    if not hasattr(mainWindow, "doc"):
        return

    print("on_array_curve: miss find python interface")
    return


def on_curve_mirror(mainWindow, event=None):
    if not hasattr(mainWindow, "doc"):
        return

    print("on_curve_mirror: miss find python interface")
    return
