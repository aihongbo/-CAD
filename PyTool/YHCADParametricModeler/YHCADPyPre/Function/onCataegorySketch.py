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
import json
import wx
from scripts.Sketch.Curve.pyncti_sketch_add_line import pyncti_sketch_add_line
from scripts.Sketch.Curve.pyncti_sketch_add_point import pyncti_sketch_add_point
from scripts.Sketch.Curve.pyncti_sketch_add_arc import pyncti_sketch_add_arc
from scripts.Sketch.Curve.pyncti_sketch_add_ellipseArc import pyncti_sketch_add_ellipseArc
from scripts.Sketch.Curve.pyncti_sketch_add_circle import pyncti_sketch_add_circle
from scripts.Sketch.Curve.pyncti_sketch_add_ellipse import pyncti_sketch_add_ellipse
from scripts.Sketch.Curve.pyncti_sketch_add_regularPolygon import pyncti_sketch_add_regularPolygon
from scripts.Sketch.Curve.pyncti_sketch_add_spline import pyncti_sketch_add_spline
from scripts.Sketch.Curve.pyncti_sketch_add_rect import pyncti_sketch_add_rect
from scripts.Sketch.Curve.pyncti_sketch_add_centerRect import pyncti_sketch_add_centerRect
from scripts.Sketch.Curve.pyncti_sketch_add_parallelogram import pyncti_sketch_add_parallelogram
from scripts.Sketch.Curve.pyncti_sketch_add_centerLine import pyncti_sketch_add_centerLine

from scripts.Sketch.Edit.pyncti_sketch_curveTrimming import pyncti_sketch_curveTrimming
from scripts.Sketch.Edit.pyncti_sketch_curveRadius import pyncti_sketch_curveRadius
from scripts.Sketch.Edit.pyncti_sketch_tectonicline import pyncti_sketch_tectonicline
from scripts.Sketch.Edit.pyncti_sketch_curveOffset import pyncti_sketch_curveOffset
from scripts.Sketch.Edit.pyncti_sketch_curvechamfer import pyncti_sketch_curvechamfer
from scripts.Sketch.Edit.pyncti_sketch_partition import pyncti_sketch_partition
from scripts.Sketch.Edit.pyncti_sketch_fixedCons import pyncti_sketch_fixedCons
from scripts.Sketch.Edit.pyncti_sketch_removePointCons import pyncti_sketch_removePointCons

from scripts.Sketch.Constraint.pyncti_sketch_AddConsXpos import pyncti_sketch_AddConsXpos
from scripts.Sketch.Constraint.pyncti_sketch_AddConsYpos import pyncti_sketch_AddConsYpos
from scripts.Sketch.Constraint.pyncti_sketch_AddConsRadius import pyncti_sketch_AddConsRadius
from scripts.Sketch.Constraint.pyncti_sketch_AddConsAngle import pyncti_sketch_AddConsAngle
from scripts.Sketch.Constraint.pyncti_sketch_AddConsLength import pyncti_sketch_AddConsLength
from scripts.Sketch.Constraint.pyncti_sketch_AddConsParallelSize import pyncti_sketch_AddConsParallelSize
from scripts.Sketch.Constraint.pyncti_sketch_LockSize import pyncti_sketch_LockSize
from scripts.Sketch.Constraint.pyncti_sketch_AddConsYAxis import pyncti_sketch_AddConsYAxis
from scripts.Sketch.Constraint.pyncti_sketch_AddConsXAxis import pyncti_sketch_AddConsXAxis
from scripts.Sketch.Constraint.pyncti_sketch_AddConsParallel import pyncti_sketch_AddConsParallel
from scripts.Sketch.Constraint.pyncti_sketch_AddConsVertical import pyncti_sketch_AddConsVertical
from scripts.Sketch.Constraint.pyncti_sketch_AddConsEqual import pyncti_sketch_AddConsEqual
from scripts.Sketch.Constraint.pyncti_sketch_AddConsCoincide import pyncti_sketch_AddConsCoincide
from scripts.Sketch.Constraint.pyncti_sketch_AddConsTangent import pyncti_sketch_AddConsTangent

from scripts.Sketch.DisplaySolve.pyncti_sketch_SwitchConsDisplay import pyncti_sketch_SwitchConsDisplay
from scripts.Sketch.DisplaySolve.pyncti_sketch_ShowCons import pyncti_sketch_ShowCons
from scripts.Sketch.DisplaySolve.pyncti_sketch_ShowWeakCons import pyncti_sketch_ShowWeakCons
from scripts.Sketch.DisplaySolve.pyncti_sketch_ShowStrongCons import pyncti_sketch_ShowStrongCons
from scripts.Sketch.DisplaySolve.pyncti_sketch_ShowCoincideCons import pyncti_sketch_ShowCoincideCons

from scripts.Sketch.Solve.pyncti_sketch_AutoSolve import pyncti_sketch_AutoSolve
from scripts.Sketch.Solve.pyncti_sketch_AutoCalCloseArea import pyncti_sketch_AutoCalCloseArea
from scripts.Sketch.Solve.pyncti_sketch_AutoCalFreeCons import pyncti_sketch_AutoCalFreeCons
from scripts.Sketch.Solve.pyncti_sketch_GetCheckConsResult import pyncti_sketch_GetCheckConsResult
from scripts.Sketch.Solve.pyncti_sketch_RunSolve import pyncti_sketch_RunSolve
from scripts.Sketch.Solve.pyncti_sketch_RunCalCloseArea import pyncti_sketch_RunCalCloseArea
from scripts.Sketch.Solve.pyncti_sketch_ConsType import pyncti_sketch_ConsType

from scripts.Sketch.Mode.pyncti_sketch_SwitchConsRadius import pyncti_sketch_SwitchConsRadius

def _parse_sketch_point(text):
    values = [item.strip() for item in text.replace("，", ",").split(",")]
    if len(values) == 2:
        values.append("0")
    if len(values) != 3:
        raise ValueError("点坐标格式应为 x,y 或 x,y,z")
    return tuple(float(value) for value in values)

def _parse_sketch_vector(text):
    values = [item.strip() for item in text.replace("，", ",").split(",")]
    if len(values) == 2:
        values.append("0")
    if len(values) != 3:
        raise ValueError("向量格式应为 x,y 或 x,y,z")
    vector = tuple(float(value) for value in values)
    if vector == (0.0, 0.0, 0.0):
        raise ValueError("向量不能为 0,0,0")
    return vector

def _parse_sketch_point_list(text):
    lines = [line.strip() for line in text.replace("\r\n", "\n").split("\n")]
    point_values = [line for line in lines if line]
    if len(point_values) < 2:
        raise ValueError("控制点列表至少需要 2 个点，每行一个点")
    return [_parse_sketch_point(point_text) for point_text in point_values]

def _resolve_sketch_object_names(mainWindow, text):
    object_names = [item.strip() for item in text.replace("，", ",").split(",") if item.strip()]
    if not object_names:
        raise ValueError("请至少输入一个草图对象名称")

    sketch = getattr(mainWindow, "activeSketch", None)
    if sketch is None or not hasattr(sketch, "GetObject"):
        raise ValueError("请先创建草图")

    objects = []
    missing_names = []

    for object_name in object_names:
        try:
            obj = sketch.GetObject(object_name)
        except Exception:
            obj = 0
        if obj is None or obj == 0:
            missing_names.append(object_name)
        else:
            objects.append(obj)

    if missing_names:
        raise ValueError(f"未找到图元名称：{', '.join(missing_names)}")
    return objects

def _resolve_single_sketch_object(mainWindow, text):
    objects = _resolve_sketch_object_names(mainWindow, text)
    if len(objects) != 1:
        raise ValueError("请输入一个对象名称")
    return objects[0]

def _resolve_sketch_object_name_list(mainWindow, text):
    tokens = [item.strip() for item in text.replace("，", ",").split(",") if item.strip()]
    if not tokens:
        raise ValueError("请至少输入一个对象名称")
    return tokens

def _show_input_error(error):
    wx.MessageBox(str(error), "输入错误", wx.OK | wx.ICON_WARNING)

def _require_doc(mainWindow):
    return hasattr(mainWindow, "doc")

def _require_sketch(mainWindow, method_name=None, message="请先创建草图"):
    sketch = getattr(mainWindow, "activeSketch", None)
    if sketch is None:
        wx.MessageBox(message, "提示", wx.OK | wx.ICON_INFORMATION)
        return None
    if method_name and not hasattr(sketch, method_name):
        wx.MessageBox(message, "提示", wx.OK | wx.ICON_INFORMATION)
        return None
    return sketch

def _require_yh_doc(mainWindow, method_name):
    yh_doc = getattr(mainWindow, "yh_doc", None)
    if yh_doc is None or not hasattr(yh_doc, method_name):
        wx.MessageBox("YH文档未初始化", "提示", wx.OK | wx.ICON_INFORMATION)
        return None
    return yh_doc

def _finish_sketch_command(mainWindow, result=None, solve_sketch=None, refresh=False):
    if result:
        mainWindow.lastSketchObject = result
    if solve_sketch is not None:
        _run_sketch_solve(solve_sketch)
    if refresh:
        _refresh_sketch_state(mainWindow)
    else:
        mainWindow.updateTree()

def _refresh_sketch_state(mainWindow):
    """统一刷新草图相关视图。"""
    try:
        mainWindow.doc.Update()
    except Exception:
        pass
    if hasattr(mainWindow, "mgr"):
        mainWindow.mgr.Update()
    cad_view = getattr(mainWindow, "cad_view", None)
    if cad_view is not None and hasattr(cad_view, "updateView"):
        try:
            cad_view.updateView()
        except Exception:
            pass
    mainWindow.updateTree()

def _run_sketch_solve(sketch):
    if sketch is not None and hasattr(sketch, "RunSolve"):
        try:
            sketch.RunSolve()
        except Exception:
            pass

def _get_snap_solve_ctrl_target(mainWindow):
    for target in (getattr(mainWindow, "activeSketch", None), getattr(mainWindow, "yh_doc", None)):
        if (
            target is not None
            and hasattr(target, "GetSnapSolveCtrlMap")
            and hasattr(target, "GetSnapSolveCtrl")
            and hasattr(target, "SetSnapSolveCtrl")
        ):
            return target
    return None

def _show_snap_solve_ctrl_dialog(mainWindow, target):
    try:
        snap_ctrl_map = dict(target.GetSnapSolveCtrlMap())
        snap_name_map = dict(target.GetSnapConsNameMap())
    except Exception as error:
        wx.MessageBox(f"读取捕捉约束控制失败：{error}", "提示", wx.OK | wx.ICON_WARNING)
        return

    if not snap_ctrl_map:
        wx.MessageBox("未读取到捕捉约束控制项", "提示", wx.OK | wx.ICON_INFORMATION)
        return

    old_dialog = getattr(mainWindow, "_snap_solve_ctrl_dialog", None)
    if old_dialog is not None:
        try:
            old_dialog.Raise()
            return
        except Exception:
            mainWindow._snap_solve_ctrl_dialog = None

    dialog = wx.Dialog(mainWindow, title="捕捉添加约束")
    grid = wx.GridSizer(rows=0, cols=2, vgap=8, hgap=28)

    for snap_type, is_checked in snap_ctrl_map.items():
        checkbox = wx.CheckBox(dialog, label=snap_name_map.get(snap_type, snap_type))
        checkbox.SetValue(bool(is_checked))
        checkbox.Bind(
            wx.EVT_CHECKBOX,
            lambda event, item_type=snap_type: target.SetSnapSolveCtrl(item_type, event.IsChecked()),
        )
        grid.Add(checkbox, 0, wx.ALIGN_CENTER_VERTICAL)

    dialog.SetSizerAndFit(grid)

    def on_close(event):
        mainWindow._snap_solve_ctrl_dialog = None
        event.Skip()

    dialog.Bind(wx.EVT_CLOSE, on_close)
    mainWindow._snap_solve_ctrl_dialog = dialog
    dialog.Show()

# def _cross_product(vector_a, vector_b):
#     return (
#         vector_a[1] * vector_b[2] - vector_a[2] * vector_b[1],
#         vector_a[2] * vector_b[0] - vector_a[0] * vector_b[2],
#         vector_a[0] * vector_b[1] - vector_a[1] * vector_b[0],
#     )

def _show_sketch_form_dialog(parent, title, fields=None, min_size=(340, 150), variant_selector=None):
    dialog = wx.Dialog(parent, title=title)
    controls = {}

    sizer = wx.BoxSizer(wx.VERTICAL)

    if variant_selector is not None:
        variant_sizer = wx.BoxSizer(wx.HORIZONTAL)
        variant_sizer.Add(wx.StaticText(dialog, label="创建方式"), 0, wx.ALIGN_CENTER_VERTICAL | wx.RIGHT, 8)
        variant_choice = wx.Choice(dialog, choices=[item[0] for item in variant_selector])
        variant_choice.SetSelection(0)
        variant_sizer.Add(variant_choice, 1, wx.EXPAND)
        sizer.Add(variant_sizer, 0, wx.ALL | wx.EXPAND, 12)

        form_panel = wx.Panel(dialog)
        form_sizer = wx.BoxSizer(wx.VERTICAL)
        form_panel.SetSizer(form_sizer)
        sizer.Add(form_panel, 1, wx.LEFT | wx.RIGHT | wx.BOTTOM | wx.EXPAND, 12)

        current_grid = None

        def rebuild_fields(field_items):
            # 切换创建方式后，重建当前这一组输入框。
            nonlocal current_grid
            controls.clear()
            form_panel.DestroyChildren()
            current_grid = wx.FlexGridSizer(rows=0, cols=2, vgap=8, hgap=8)
            current_grid.AddGrowableCol(1, 1)

            for item in field_items:
                if len(item) == 3:
                    key, label, default_value = item
                    control = wx.TextCtrl(form_panel, value=default_value, size=(180, -1))
                else:
                    raise ValueError("圆弧变体字段格式不正确")

                controls[key] = control
                current_grid.Add(wx.StaticText(form_panel, label=label), 0, wx.ALIGN_CENTER_VERTICAL)
                current_grid.Add(control, 1, wx.EXPAND)

            form_sizer.Clear(False)
            form_sizer.Add(current_grid, 1, wx.EXPAND)
            form_panel.Layout()

        def rebuild_variant():
            # 根据当前下拉框选中的模式，切换到对应字段集合。
            selected_index = variant_choice.GetSelection()
            _, variant_fields = variant_selector[selected_index]
            rebuild_fields(variant_fields)
            dialog.Layout()
            dialog.Fit()

        variant_choice.Bind(wx.EVT_CHOICE, lambda event: rebuild_variant())
        rebuild_variant()
    else:
        grid = wx.FlexGridSizer(rows=0, cols=2, vgap=8, hgap=8)
        grid.AddGrowableCol(1, 1)
        for item in fields or []:
            if len(item) == 3:
                key, label, default_value = item
                control = wx.TextCtrl(dialog, value=default_value, size=(180, -1))
            else:
                raise ValueError("表单字段格式不正确")
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

    result = {}
    for key, control in controls.items():
        if isinstance(control, wx.Choice):
            result[key] = control.GetStringSelection()
        else:
            result[key] = control.GetValue()
    if variant_selector is not None:
        result["variant"] = variant_choice.GetStringSelection()
    dialog.Destroy()
    return result

# 曲线
def on_exec_line_button_click(mainWindow, event=None):
    # 创建直线
    if not _require_doc(mainWindow):
        return
    sketch = getattr(mainWindow, "activeSketch", None)
    if sketch is None or not hasattr(sketch, "AddLine"):
        wx.MessageBox("请先创建草图", "提示", wx.OK | wx.ICON_INFORMATION)
        return

    values = _show_sketch_form_dialog(
        mainWindow,
        "创建直线",
        [
            ("start", "起点", "0,0"),
            ("end", "终点", "100,0"),
        ],
    )
    if values is None:
        return
    try:
        start = _parse_sketch_point(values["start"])
        end = _parse_sketch_point(values["end"])
    except ValueError as e:
        wx.MessageBox(str(e), "输入错误", wx.OK | wx.ICON_WARNING)
        return

    start_point = mainWindow.NCTI.Point(start[0], start[1], start[2])
    end_point = mainWindow.NCTI.Point(end[0], end[1], end[2])
    line = pyncti_sketch_add_line(mainWindow.NCTI, mainWindow.doc, sketch, start_point, end_point)
    if line:
        mainWindow.lastSketchObject = line
    mainWindow.updateTree()

def on_exec_point_button_click(mainWindow, event=None):
    # 创建点
    if not _require_doc(mainWindow):
        return
    sketch = getattr(mainWindow, "activeSketch", None)
    if sketch is None or not hasattr(sketch, "AddPoint"):
        wx.MessageBox("请先创建草图", "提示", wx.OK | wx.ICON_INFORMATION)
        return

    values = _show_sketch_form_dialog(
        mainWindow,
        "创建点",
        [
            ("point", "点坐标", "0,0"),
        ]
    )
    if values is None:
        return
    try:
        point_value = _parse_sketch_point(values["point"])
    except ValueError as e:
        wx.MessageBox(str(e), "输入错误", wx.OK | wx.ICON_WARNING)
        return

    point_data = mainWindow.NCTI.Point(point_value[0], point_value[1], point_value[2])
    point = pyncti_sketch_add_point(mainWindow.NCTI, mainWindow.doc, sketch, point_data)
    if point:
        mainWindow.lastSketchObject = point
    mainWindow.updateTree()

def on_exec_point_button_arc(mainWindow, event=None):
    # 创建圆弧
    if not _require_doc(mainWindow):
        return
    sketch = getattr(mainWindow, "activeSketch", None)
    if sketch is None or not hasattr(sketch, "AddArc"):
        wx.MessageBox("请先创建草图", "提示", wx.OK | wx.ICON_INFORMATION)
        return

    values = _show_sketch_form_dialog(
        mainWindow,
        "创建圆弧",
        min_size=(360, 240),
        variant_selector=[
            ("三点圆弧", [
                ("start", "起点", "0,0"),
                ("end", "终点", "10,0"),
                ("arc_point", "弧上一点", "5,5"),
            ]),
            ("圆心半径圆弧", [
                ("radius", "半径", "5"),
                ("start_angle", "起始角", "0"),
                ("end_angle", "终止角", "60"),
                ("center", "圆心", "0,0"),
            ]),
        ]
    )
    if values is None:
        return

    try:
        if values.get("variant") == "三点圆弧":
            start = _parse_sketch_point(values["start"])
            end = _parse_sketch_point(values["end"])
            arc_point = _parse_sketch_point(values["arc_point"])

            arc = pyncti_sketch_add_arc(
                mainWindow.NCTI,
                mainWindow.doc,
                sketch,
                mainWindow.NCTI.Point(start[0], start[1], start[2]),
                mainWindow.NCTI.Point(end[0], end[1], end[2]),
                mainWindow.NCTI.Point(arc_point[0], arc_point[1], arc_point[2])
            )
        else:
            center = _parse_sketch_point(values["center"])
            radius = float(values["radius"])
            start_angle = float(values["start_angle"])
            end_angle = float(values["end_angle"])

            arc = pyncti_sketch_add_arc(
                mainWindow.NCTI,
                mainWindow.doc,
                sketch,
                radius=radius,
                start_angle=start_angle,
                end_angle=end_angle,
                center_point=mainWindow.NCTI.Point(center[0], center[1], center[2])
            )
    except ValueError as e:
        wx.MessageBox(str(e), "输入错误", wx.OK | wx.ICON_WARNING)
        return

    if arc:
        mainWindow.lastSketchObject = arc
    mainWindow.updateTree()

def on_exec_point_button_ellipseArc(mainWindow, event=None):
    # 创建椭圆弧
    if not _require_doc(mainWindow):
        return
    sketch = getattr(mainWindow, "activeSketch", None)
    if sketch is None or not hasattr(sketch, "AddEllipseArc"):
        wx.MessageBox("请先创建草图", "提示", wx.OK | wx.ICON_INFORMATION)
        return

    values = _show_sketch_form_dialog(
        mainWindow,
        "创建椭圆弧",
        [
            ("center", "圆心", "0,0"),
            ("vectorMajorAxis", "长半轴向量", "50,0"),
            ("vectorMinorAxis", "短半轴向量", "0,20"),
            ("start_angle", "起始角", "0"),
            ("end_angle", "终止角", "90"),
        ],
        min_size=(380, 240),
    )
    if values is None:
        return

    try:
        center = _parse_sketch_point(values["center"])
        vectorMajorAxis = _parse_sketch_vector(values["vectorMajorAxis"])
        vectorMinorAxis = _parse_sketch_vector(values["vectorMinorAxis"])
        start_angle = float(values["start_angle"])
        end_angle = float(values["end_angle"])
    except ValueError as e:
        wx.MessageBox(str(e), "输入错误", wx.OK | wx.ICON_WARNING)
        return

    center_point = mainWindow.NCTI.Point(center[0], center[1], center[2])
    major_axis = mainWindow.NCTI.Vector(vectorMajorAxis[0], vectorMajorAxis[1], vectorMajorAxis[2])
    minor_axis = mainWindow.NCTI.Vector(vectorMinorAxis[0], vectorMinorAxis[1], vectorMinorAxis[2])
    ellipse_arc = pyncti_sketch_add_ellipseArc(
        mainWindow.NCTI,
        mainWindow.doc,
        sketch,
        center_point,
        major_axis,
        minor_axis,
        start_angle,
        end_angle,
    )
    if ellipse_arc:
        mainWindow.lastSketchObject = ellipse_arc
    mainWindow.updateTree()

def on_exec_point_button_circle(mainWindow, event=None):
    # 创建圆
    if not _require_doc(mainWindow):
        return
    sketch = getattr(mainWindow, "activeSketch", None)
    if sketch is None or not hasattr(sketch, "AddCircle"):
        wx.MessageBox("请先创建草图", "提示", wx.OK | wx.ICON_INFORMATION)
        return

    values = _show_sketch_form_dialog(
        mainWindow,
        "创建圆",
        [
            ("center", "圆心", "0,0"),
            ("radius", "半径", "10"),
        ],
    )
    if values is None:
        return
    try:
        center = _parse_sketch_point(values["center"])
        radius = float(values["radius"])
    except ValueError as e:
        wx.MessageBox(str(e), "输入错误", wx.OK | wx.ICON_WARNING)
        return

    center_point = mainWindow.NCTI.Point(center[0], center[1], center[2])
    circle = pyncti_sketch_add_circle(mainWindow.NCTI, mainWindow.doc, sketch, center_point, radius)
    if circle:
        mainWindow.lastSketchObject = circle
    mainWindow.updateTree()

def on_exec_point_button_ellipse(mainWindow, event=None):
    # 创建椭圆
    if not _require_doc(mainWindow):
        return
    sketch = getattr(mainWindow, "activeSketch", None)
    if sketch is None or not hasattr(sketch, "AddEllipse"):
        wx.MessageBox("请先创建草图", "提示", wx.OK | wx.ICON_INFORMATION)
        return

    values = _show_sketch_form_dialog(
        mainWindow,
        "创建椭圆",
        [
            ("center", "圆心", "0,0"),
            ("vectorMajorAxis", "长半轴向量", "2,0"),
            ("vectorMinorAxis", "短半轴向量", "0,1"),
        ],
    )
    if values is None:
        return
    try:
        center = _parse_sketch_point(values["center"])
        vectorMajorAxis = _parse_sketch_vector(values["vectorMajorAxis"])
        vectorMinorAxis = _parse_sketch_vector(values["vectorMinorAxis"])
    except ValueError as e:
        wx.MessageBox(str(e), "输入错误", wx.OK | wx.ICON_WARNING)
        return

    # cross_vector = _cross_product(vectorMajorAxis, vectorMinorAxis)
    # if cross_vector == (0.0, 0.0, 0.0):
    #     wx.MessageBox("长半轴向量与短半轴向量不能共线", "输入错误", wx.OK | wx.ICON_WARNING)
    #     return

    center_point = mainWindow.NCTI.Point(center[0], center[1], center[2])
    vectorMajorAxis_data = mainWindow.NCTI.Vector(vectorMajorAxis[0], vectorMajorAxis[1], vectorMajorAxis[2])
    vectorMinorAxis_data = mainWindow.NCTI.Vector(vectorMinorAxis[0], vectorMinorAxis[1], vectorMinorAxis[2])
    ellipse = pyncti_sketch_add_ellipse(mainWindow.NCTI, mainWindow.doc, sketch, center_point, vectorMajorAxis_data, vectorMinorAxis_data)
    if ellipse:
        mainWindow.lastSketchObject = ellipse
    mainWindow.updateTree()

def on_exec_point_button_rect(mainWindow, event=None):
    # 创建矩形
    if not _require_doc(mainWindow):
        return
    sketch = getattr(mainWindow, "activeSketch", None)
    if sketch is None or not hasattr(sketch, "AddRect"):
        wx.MessageBox("请先创建草图", "提示", wx.OK | wx.ICON_INFORMATION)
        return

    values = _show_sketch_form_dialog(
        mainWindow,
        "创建矩形",
        [
            ("start", "起点", "0,0"),
            ("end", "对角点", "50,30"),
        ]
    )
    if values is None:
        return
    try:
        start = _parse_sketch_point(values["start"])
        end = _parse_sketch_point(values["end"])
    except ValueError as e:
        wx.MessageBox(str(e), "输入错误", wx.OK | wx.ICON_WARNING)
        return

    start_point = mainWindow.NCTI.Point(start[0], start[1], start[2])
    end_point = mainWindow.NCTI.Point(end[0], end[1], end[2])
    rect = pyncti_sketch_add_rect(mainWindow.NCTI, mainWindow.doc, sketch, start_point, end_point)
    if rect:
        mainWindow.lastSketchObject = rect
    mainWindow.updateTree()

def on_exec_point_button_centerRect(mainWindow, event=None):
    # 创建中心矩形
    if not _require_doc(mainWindow):
        return
    sketch = getattr(mainWindow, "activeSketch", None)
    if sketch is None or not hasattr(sketch, "AddCenterRect"):
        wx.MessageBox("请先创建草图", "提示", wx.OK | wx.ICON_INFORMATION)
        return

    values = _show_sketch_form_dialog(
        mainWindow,
        "创建中心矩形",
        [
            ("center", "中心点", "20,20"),
            ("length", "矩形长", "10"),
            ("width", "矩形宽", "6"),
        ]
    )
    if values is None:
        return
    try:
        center = _parse_sketch_point(values["center"])
        rect_length = float(values["length"])
        rect_width = float(values["width"])
    except ValueError as e:
        wx.MessageBox(str(e), "输入错误", wx.OK | wx.ICON_WARNING)
        return

    center_point = mainWindow.NCTI.Point(center[0], center[1], center[2])
    center_rect = pyncti_sketch_add_centerRect(
        mainWindow.NCTI,
        mainWindow.doc,
        sketch,
        center_point,
        rect_length,
        rect_width
    )
    if center_rect:
        mainWindow.lastSketchObject = center_rect
    mainWindow.updateTree()

def on_exec_point_button_parallelogram(mainWindow, event=None):
    # 创建平行四边形
    if not _require_doc(mainWindow):
        return
    sketch = getattr(mainWindow, "activeSketch", None)
    if sketch is None or not hasattr(sketch, "AddParallelogram"):
        wx.MessageBox("请先创建草图", "提示", wx.OK | wx.ICON_INFORMATION)
        return

    values = _show_sketch_form_dialog(
        mainWindow,
        "创建平行四边形",
        [
            ("point1", "第一个点", "20,20"),
            ("point2", "第二个点", "40,20"),
            ("point3", "第三个点", "50,30"),
        ]
    )
    if values is None:
        return
    try:
        point1 = _parse_sketch_point(values["point1"])
        point2 = _parse_sketch_point(values["point2"])
        point3 = _parse_sketch_point(values["point3"])
    except ValueError as e:
        wx.MessageBox(str(e), "输入错误", wx.OK | wx.ICON_WARNING)
        return

    parallelogram = pyncti_sketch_add_parallelogram(
        mainWindow.NCTI,
        mainWindow.doc,
        sketch,
        mainWindow.NCTI.Point(point1[0], point1[1], point1[2]),
        mainWindow.NCTI.Point(point2[0], point2[1], point2[2]),
        mainWindow.NCTI.Point(point3[0], point3[1], point3[2])
    )
    if parallelogram:
        mainWindow.lastSketchObject = parallelogram
    mainWindow.updateTree()

def on_exec_point_button_regularPolygon(mainWindow, event=None):
    # 创建多边形
    if not _require_doc(mainWindow):
        return
    sketch = getattr(mainWindow, "activeSketch", None)
    if sketch is None or not hasattr(sketch, "RegularPolygon"):
        wx.MessageBox("请先创建草图", "提示", wx.OK | wx.ICON_INFORMATION)
        return

    values = _show_sketch_form_dialog(
        mainWindow,
        "创建多边形",
        [
            ("center", "中心点", "0,0"),
            ("radius", "顶点到中心点距离", "50"),
            ("sides", "边数", "6"),
        ],
    )
    if values is None:
        return
    try:
        center = _parse_sketch_point(values["center"])
        radius = float(values["radius"])
        sides = float(values["sides"])
    except ValueError as e:
        wx.MessageBox(str(e), "输入错误", wx.OK | wx.ICON_WARNING)
        return

    center_point = mainWindow.NCTI.Point(center[0], center[1], center[2])
    regularPolygon = pyncti_sketch_add_regularPolygon(mainWindow.NCTI, mainWindow.doc, sketch, center_point, radius, sides)
    if regularPolygon:
        mainWindow.lastSketchObject = regularPolygon
    mainWindow.updateTree()

def on_exec_point_button_spline(mainWindow, event=None):
    # 创建样条
    if not _require_doc(mainWindow):
        return
    sketch = getattr(mainWindow, "activeSketch", None)
    if sketch is None or not hasattr(sketch, "AddSpline"):
        wx.MessageBox("请先创建草图", "提示", wx.OK | wx.ICON_INFORMATION)
        return

    dialog = wx.Dialog(mainWindow, title="创建样条")
    sizer = wx.BoxSizer(wx.VERTICAL)
    sizer.Add(wx.StaticText(dialog, label="控制点列表（每行一个点，格式：x,y 或 x,y,z）"), 0, wx.ALL, 12)

    point_text = wx.TextCtrl(
        dialog,
        value="0,0\n20,10\n40,0",
        style=wx.TE_MULTILINE,
        size=(260, 120)
    )
    sizer.Add(point_text, 1, wx.LEFT | wx.RIGHT | wx.BOTTOM | wx.EXPAND, 12)

    buttons = dialog.CreateButtonSizer(wx.OK | wx.CANCEL)
    sizer.Add(buttons, 0, wx.ALL | wx.ALIGN_RIGHT, 12)
    dialog.SetSizer(sizer)
    dialog.SetMinSize((360, 260))
    dialog.Fit()
    dialog.CenterOnParent()

    if dialog.ShowModal() != wx.ID_OK:
        dialog.Destroy()
        return

    try:
        point_values = _parse_sketch_point_list(point_text.GetValue())
    except ValueError as e:
        dialog.Destroy()
        wx.MessageBox(str(e), "输入错误", wx.OK | wx.ICON_WARNING)
        return

    dialog.Destroy()

    control_points = [
        mainWindow.NCTI.Point(point[0], point[1], point[2])
        for point in point_values
    ]
    spline = pyncti_sketch_add_spline(mainWindow.NCTI, mainWindow.doc, sketch, control_points)
    if spline:
        mainWindow.lastSketchObject = spline
    mainWindow.updateTree()

def on_exec_point_button_centerLine(mainWindow, event=None):
    # 创建中心线
    if not _require_doc(mainWindow):
        return
    sketch = getattr(mainWindow, "activeSketch", None)
    if sketch is None or not hasattr(sketch, "AddCenterLine"):
        wx.MessageBox("请先创建草图", "提示", wx.OK | wx.ICON_INFORMATION)
        return

    values = _show_sketch_form_dialog(
        mainWindow,
        "创建中心线",
        [
            ("start", "起点", "0,0"),
            ("end", "终点", "100,0"),
        ],
    )
    if values is None:
        return
    try:
        start = _parse_sketch_point(values["start"])
        end = _parse_sketch_point(values["end"])
    except ValueError as e:
        wx.MessageBox(str(e), "输入错误", wx.OK | wx.ICON_WARNING)
        return

    start_point = mainWindow.NCTI.Point(start[0], start[1], start[2])
    end_point = mainWindow.NCTI.Point(end[0], end[1], end[2])
    center_line = pyncti_sketch_add_centerLine(mainWindow.NCTI, mainWindow.doc, sketch, start_point, end_point)
    if center_line:
        mainWindow.lastSketchObject = center_line
    mainWindow.updateTree()

# 编辑
def on_exec_edit_button_curveTrimming(mainWindow, event=None):
    # 曲线修剪
    if not _require_doc(mainWindow):
        return
    sketch = getattr(mainWindow, "activeSketch", None)
    if sketch is None or not hasattr(sketch, "CurveTrimming"):
        wx.MessageBox("请先创建草图", "提示", wx.OK | wx.ICON_INFORMATION)
        return

    values = _show_sketch_form_dialog(
        mainWindow,
        "曲线修剪",
        [
            ("trim_point", "修剪点", "10,0"),
        ],
    )
    if values is None:
        return
    try:
        trim_point_value = _parse_sketch_point(values["trim_point"])
    except ValueError as e:
        wx.MessageBox(str(e), "输入错误", wx.OK | wx.ICON_WARNING)
        return

    trim_point = mainWindow.NCTI.Point(trim_point_value[0], trim_point_value[1], trim_point_value[2])
    trim_result = pyncti_sketch_curveTrimming(mainWindow.NCTI, mainWindow.doc, sketch, trim_point)
    if trim_result:
        mainWindow.lastSketchObject = trim_result
    mainWindow.updateTree()

def on_exec_edit_button_curveRadius(mainWindow, event=None):
    # 曲线圆角
    if not _require_doc(mainWindow):
        return
    sketch = getattr(mainWindow, "activeSketch", None)
    if sketch is None or not hasattr(sketch, "CurveRadius"):
        wx.MessageBox("请先创建草图", "提示", wx.OK | wx.ICON_INFORMATION)
        return

    values = _show_sketch_form_dialog(
        mainWindow,
        "曲线圆角",
        min_size=(520, 260),
        variant_selector=[
            ("点+线方式", [
                ("value1", "线1上的点", "77.046467852982758,77.046467852982758,0"),
                ("line1", "线1对象", "a1"),
                ("value2", "线2上的点", "99.647286010333602,77.136951986221860,0"),
                ("line2", "线2对象", "a2"),
            ]),
            ("半径+线方式", [
                ("value1", "圆角半径", "1"),
                ("line1", "线1对象", "a3"),
                ("line2", "线2对象", "a4"),
            ]),
        ],
    )
    if values is None:
        return

    try:
        line1 = _resolve_single_sketch_object(mainWindow, values["line1"])
        line2 = _resolve_single_sketch_object(mainWindow, values["line2"])

        if values.get("variant") == "点+线方式":
            point1_value = _parse_sketch_point(values["value1"])
            point2_value = _parse_sketch_point(values["value2"])
            value1 = mainWindow.NCTI.Point(point1_value[0], point1_value[1], point1_value[2])
            value2 = mainWindow.NCTI.Point(point2_value[0], point2_value[1], point2_value[2])
        else:
            value1 = float(values["value1"])
            value2 = None
    except ValueError as e:
        wx.MessageBox(str(e), "输入错误", wx.OK | wx.ICON_WARNING)
        return

    radius_result = pyncti_sketch_curveRadius(
        mainWindow.NCTI,
        mainWindow.doc,
        sketch,
        value1,
        line1,
        value2,
        line2,
    )
    if radius_result:
        mainWindow.lastSketchObject = radius_result
    mainWindow.updateTree()

def on_exec_edit_button_tectonicline(mainWindow, event=None):
    # 设置构造线
    if not _require_doc(mainWindow):
        return
    sketch = getattr(mainWindow, "activeSketch", None)
    if sketch is None or not hasattr(sketch, "Tectonicline"):
        wx.MessageBox("请先创建草图", "提示", wx.OK | wx.ICON_INFORMATION)
        return

    values = _show_sketch_form_dialog(
        mainWindow,
        "设置构造线",
        [
            ("is_tectonic", "构造线标记(1/0)", "1"),
            ("objects", "对象变量名", "a1"),
        ],
        min_size=(520, 180),
    )
    if values is None:
        return
    try:
        is_tectonic = int(values["is_tectonic"])
        if is_tectonic not in (0, 1):
            raise ValueError("构造线标记只能输入 1 或 0")
        object_names = _resolve_sketch_object_name_list(mainWindow, values["objects"])
    except ValueError as e:
        wx.MessageBox(str(e), "输入错误", wx.OK | wx.ICON_WARNING)
        return

    tectonic_result = pyncti_sketch_tectonicline(mainWindow.NCTI, mainWindow.doc, sketch, is_tectonic, object_names)
    if tectonic_result:
        mainWindow.lastSketchObject = tectonic_result
    mainWindow.updateTree()

def on_exec_edit_button_curveOffset(mainWindow, param=None, event=None):
    # 曲线偏移
    if not _require_doc(mainWindow):
        return
    sketch = getattr(mainWindow, "activeSketch", None)
    if sketch is None or not hasattr(sketch, "CurveOffset"):
        wx.MessageBox("请先创建草图", "提示", wx.OK | wx.ICON_INFORMATION)
        return

    if param in (1, 2, 3):
        offset_result = pyncti_sketch_curveOffset(
            mainWindow.NCTI,
            mainWindow.doc,
            sketch,
            offset_mode=param
        )
        if offset_result:
            mainWindow.lastSketchObject = offset_result
        mainWindow.updateTree()
        return

    values = _show_sketch_form_dialog(
        mainWindow,
        "曲线偏移",
        [
            ("objects", "对象变量名"
            "", "a1"),
            ("distance", "偏移距离", "2"),
        ],
        min_size=(520, 180),
    )
    if values is None:
        return
    try:
        offset_objects = _resolve_sketch_object_names(mainWindow, values["objects"])
        offset_distance = float(values["distance"])
    except ValueError as e:
        wx.MessageBox(str(e), "输入错误", wx.OK | wx.ICON_WARNING)
        return

    offset_result = pyncti_sketch_curveOffset(
        mainWindow.NCTI,
        mainWindow.doc,
        sketch,
        offset_objects=offset_objects,
        offset_distance=offset_distance
    )
    if offset_result:
        mainWindow.lastSketchObject = offset_result
    mainWindow.updateTree()

def on_exec_edit_button_curvechamfer(mainWindow, event=None):
    # 曲线倒角
    if not _require_doc(mainWindow):
        return
    sketch = getattr(mainWindow, "activeSketch", None)
    if sketch is None or not hasattr(sketch, "CurveChamfer"):
        wx.MessageBox("请先创建草图", "提示", wx.OK | wx.ICON_INFORMATION)
        return

    values = _show_sketch_form_dialog(
        mainWindow,
        "曲线倒角",
        min_size=(520, 260),
        variant_selector=[
            ("点+线方式", [
                ("value1", "线1上的点", "77.046467852982758,77.046467852982758,0"),
                ("line1", "线1对象", "a1"),
                ("value2", "线2上的点", "99.647286010333602,77.136951986221860,0"),
                ("line2", "线2对象", "a2"),
            ]),
            ("长度+线方式", [
                ("value1", "线1倒角长度", "1"),
                ("line1", "线1对象", "a3"),
                ("value2", "线2倒角长度", "1"),
                ("line2", "线2对象", "a4"),
            ]),
        ],
    )
    if values is None:
        return

    try:
        line1 = _resolve_single_sketch_object(mainWindow, values["line1"])
        line2 = _resolve_single_sketch_object(mainWindow, values["line2"])

        if values.get("variant") == "点+线方式":
            point1_value = _parse_sketch_point(values["value1"])
            point2_value = _parse_sketch_point(values["value2"])
            value1 = mainWindow.NCTI.Point(point1_value[0], point1_value[1], point1_value[2])
            value2 = mainWindow.NCTI.Point(point2_value[0], point2_value[1], point2_value[2])
        else:
            value1 = float(values["value1"])
            value2 = float(values["value2"])
    except ValueError as e:
        wx.MessageBox(str(e), "输入错误", wx.OK | wx.ICON_WARNING)
        return

    chamfer_result = pyncti_sketch_curvechamfer(
        mainWindow.NCTI,
        mainWindow.doc,
        sketch,
        value1,
        line1,
        value2,
        line2,
    )
    if chamfer_result:
        mainWindow.lastSketchObject = chamfer_result
    mainWindow.updateTree()

def on_exec_edit_button_partition(mainWindow, event=None):
    # 分割
    if not _require_doc(mainWindow):
        return
    sketch = getattr(mainWindow, "activeSketch", None)
    if sketch is None or not hasattr(sketch, "Partition"):
        wx.MessageBox("请先创建草图", "提示", wx.OK | wx.ICON_INFORMATION)
        return

    values = _show_sketch_form_dialog(
        mainWindow,
        "分割曲线",
        min_size=(420, 220),
        variant_selector=[
            ("单点分割", [
                ("point1", "分割点", "5,5"),
            ]),
            ("双点分割", [
                ("point1", "分割点1", "9.7719611851102890,7.1233875286197543,0"),
                ("point2", "分割点2", "-9.8480895324538498,6.7364137066877001,0"),
            ]),
        ],
    )
    if values is None:
        return

    try:
        point1_value = _parse_sketch_point(values["point1"])
        point1 = mainWindow.NCTI.Point(point1_value[0], point1_value[1], point1_value[2])

        point2 = None
        if values.get("variant") == "双点分割":
            point2_value = _parse_sketch_point(values["point2"])
            point2 = mainWindow.NCTI.Point(point2_value[0], point2_value[1], point2_value[2])
    except ValueError as e:
        wx.MessageBox(str(e), "输入错误", wx.OK | wx.ICON_WARNING)
        return

    partition_result = pyncti_sketch_partition(mainWindow.NCTI, mainWindow.doc, sketch, point1, point2)
    if partition_result:
        mainWindow.lastSketchObject = partition_result
    mainWindow.updateTree()

def on_exec_edit_button_fixedCons(mainWindow, event=None):
    # 锁定图元
    if not _require_doc(mainWindow):
        return
    sketch = getattr(mainWindow, "activeSketch", None)
    if sketch is None or not hasattr(sketch, "FixedCons"):
        wx.MessageBox("请先创建草图", "提示", wx.OK | wx.ICON_INFORMATION)
        return

    values = _show_sketch_form_dialog(
        mainWindow,
        "锁定图元",
        [
            ("object", "对象变量名/ObjectName", "a1"),
        ],
        min_size=(520, 180),
    )
    if values is None:
        return
    try:
        sketch_object = _resolve_single_sketch_object(mainWindow, values["object"])
    except ValueError as e:
        wx.MessageBox(str(e), "输入错误", wx.OK | wx.ICON_WARNING)
        return

    fixed_result = pyncti_sketch_fixedCons(mainWindow.NCTI, mainWindow.doc, sketch, sketch_object)
    if fixed_result:
        mainWindow.lastSketchObject = fixed_result
    mainWindow.updateTree()

def on_exec_edit_button_removePointCons(mainWindow, event=None):
    # 移除约束
    if not _require_doc(mainWindow):
        return
    sketch = getattr(mainWindow, "activeSketch", None)
    if sketch is None or not hasattr(sketch, "RemovePointCons"):
        wx.MessageBox("请先创建草图", "提示", wx.OK | wx.ICON_INFORMATION)
        return

    values = _show_sketch_form_dialog(
        mainWindow,
        "移除约束",
        [
            ("point", "约束点坐标", "20,6,0"),
        ],
        min_size=(420, 180),
    )
    if values is None:
        return

    try:
        point_value = _parse_sketch_point(values["point"])
    except ValueError as e:
        wx.MessageBox(str(e), "输入错误", wx.OK | wx.ICON_WARNING)
        return

    point = mainWindow.NCTI.Point(point_value[0], point_value[1], point_value[2])
    remove_result = pyncti_sketch_removePointCons(mainWindow.NCTI, mainWindow.doc, sketch, point)
    if remove_result:
        mainWindow.lastSketchObject = remove_result
    mainWindow.updateTree()

# 约束
def on_exec_constraint_button_AddConsXpos(mainWindow, event=None):
    # 水平尺寸
    if not _require_doc(mainWindow):
        return
    sketch = getattr(mainWindow, "activeSketch", None)
    if sketch is None or not hasattr(sketch, "AddConsXpos"):
        wx.MessageBox("请先创建草图", "提示", wx.OK | wx.ICON_INFORMATION)
        return

    values = _show_sketch_form_dialog(
        mainWindow,
        "水平尺寸",
        min_size=(520, 240),
        variant_selector=[
            ("到原点尺寸", [
                ("index1", "对象点索引", "0"),
                ("object1", "对象", "a1"),
            ]),
            ("两点尺寸", [
                ("index1", "对象1点索引", "0"),
                ("object1", "对象1", "a1"),
                ("index2", "对象2点索引", "1"),
                ("object2", "对象2", "a2"),
            ]),
        ],
    )
    if values is None:
        return

    try:
        index1 = int(values["index1"])
        object1 = _resolve_single_sketch_object(mainWindow, values["object1"])
        if values.get("variant") == "到原点尺寸":
            cons_result = pyncti_sketch_AddConsXpos(mainWindow.NCTI, mainWindow.doc, sketch, value1=index1, object1=object1)
        else:
            index2 = int(values["index2"])
            object2 = _resolve_single_sketch_object(mainWindow, values["object2"])
            cons_result = pyncti_sketch_AddConsXpos(mainWindow.NCTI, mainWindow.doc, sketch, value1=index1, object1=object1, value2=index2, object2=object2)
    except ValueError as e:
        wx.MessageBox(str(e), "输入错误", wx.OK | wx.ICON_WARNING)
        return

    if cons_result:
        mainWindow.lastSketchObject = cons_result
    mainWindow.updateTree()

def on_exec_constraint_button_AddConsYpos(mainWindow, event=None):
    # 竖直尺寸
    if not _require_doc(mainWindow):
        return
    sketch = getattr(mainWindow, "activeSketch", None)
    if sketch is None or not hasattr(sketch, "AddConsYpos"):
        wx.MessageBox("请先创建草图", "提示", wx.OK | wx.ICON_INFORMATION)
        return

    values = _show_sketch_form_dialog(
        mainWindow,
        "竖直尺寸",
        min_size=(520, 240),
        variant_selector=[
            ("到原点尺寸", [
                ("index1", "对象点索引", "0"),
                ("object1", "对象", "a1"),
            ]),
            ("两点尺寸", [
                ("index1", "对象1点索引", "0"),
                ("object1", "对象1", "a1"),
                ("index2", "对象2点索引", "1"),
                ("object2", "对象2", "a2"),
            ]),
        ],
    )
    if values is None:
        return

    try:
        index1 = int(values["index1"])
        object1 = _resolve_single_sketch_object(mainWindow, values["object1"])
        if values.get("variant") == "到原点尺寸":
            cons_result = pyncti_sketch_AddConsYpos(mainWindow.NCTI, mainWindow.doc, sketch, value1=index1, object1=object1)
        else:
            index2 = int(values["index2"])
            object2 = _resolve_single_sketch_object(mainWindow, values["object2"])
            cons_result = pyncti_sketch_AddConsYpos(mainWindow.NCTI, mainWindow.doc, sketch, value1=index1, object1=object1, value2=index2, object2=object2)
    except ValueError as e:
        wx.MessageBox(str(e), "输入错误", wx.OK | wx.ICON_WARNING)
        return

    if cons_result:
        mainWindow.lastSketchObject = cons_result
    mainWindow.updateTree()

def on_exec_constraint_button_AddConsRadius(mainWindow, event=None):
    # 半径尺寸
    if not _require_doc(mainWindow):
        return
    sketch = getattr(mainWindow, "activeSketch", None)
    if sketch is None or not hasattr(sketch, "AddConsRadius"):
        wx.MessageBox("请先创建草图", "提示", wx.OK | wx.ICON_INFORMATION)
        return

    values = _show_sketch_form_dialog(
        mainWindow,
        "半径尺寸",
        [
            ("object1", "圆/圆弧对象", "a1"),
        ],
        min_size=(520, 180),
    )
    if values is None:
        return
    try:
        sketch_object = _resolve_single_sketch_object(mainWindow, values["object1"])
    except ValueError as e:
        wx.MessageBox(str(e), "输入错误", wx.OK | wx.ICON_WARNING)
        return

    cons_result = pyncti_sketch_AddConsRadius(mainWindow.NCTI, mainWindow.doc, sketch, sketch_object)
    if cons_result:
        mainWindow.lastSketchObject = cons_result
    mainWindow.updateTree()

def on_exec_constraint_button_AddConsAngle(mainWindow, event=None):
    # 角度尺寸
    if not _require_doc(mainWindow):
        return
    sketch = getattr(mainWindow, "activeSketch", None)
    if sketch is None or not hasattr(sketch, "AddConsAngle"):
        wx.MessageBox("请先创建草图", "提示", wx.OK | wx.ICON_INFORMATION)
        return

    values = _show_sketch_form_dialog(
        mainWindow,
        "角度尺寸",
        min_size=(520, 220),
        variant_selector=[
            ("与X轴角度", [
                ("object1", "对象", "a1"),
            ]),
            ("两对象角度", [
                ("object1", "对象1", "a1"),
                ("object2", "对象2", "a2"),
            ]),
        ],
    )
    if values is None:
        return

    try:
        object1 = _resolve_single_sketch_object(mainWindow, values["object1"])
        if values.get("variant") == "与X轴角度":
            cons_result = pyncti_sketch_AddConsAngle(mainWindow.NCTI, mainWindow.doc, sketch, object1=object1)
        else:
            object2 = _resolve_single_sketch_object(mainWindow, values["object2"])
            cons_result = pyncti_sketch_AddConsAngle(mainWindow.NCTI, mainWindow.doc, sketch, object1=object1, object2=object2)
    except ValueError as e:
        wx.MessageBox(str(e), "输入错误", wx.OK | wx.ICON_WARNING)
        return

    if cons_result:
        mainWindow.lastSketchObject = cons_result
    mainWindow.updateTree()

def on_exec_constraint_button_AddConsLength(mainWindow, event=None):
    # 长度尺寸
    if not _require_doc(mainWindow):
        return
    sketch = getattr(mainWindow, "activeSketch", None)
    if sketch is None or not hasattr(sketch, "AddConsLength"):
        wx.MessageBox("请先创建草图", "提示", wx.OK | wx.ICON_INFORMATION)
        return

    values = _show_sketch_form_dialog(
        mainWindow,
        "长度尺寸",
        min_size=(520, 240),
        variant_selector=[
            ("到原点尺寸", [
                ("index1", "对象点索引", "0"),
                ("object1", "对象", "a1"),
            ]),
            ("两点尺寸", [
                ("index1", "对象1点索引", "0"),
                ("object1", "对象1", "a1"),
                ("index2", "对象2点索引", "1"),
                ("object2", "对象2", "a2"),
            ]),
        ],
    )
    if values is None:
        return

    try:
        index1 = int(values["index1"])
        object1 = _resolve_single_sketch_object(mainWindow, values["object1"])
        if values.get("variant") == "到原点尺寸":
            cons_result = pyncti_sketch_AddConsLength(mainWindow.NCTI, mainWindow.doc, sketch, value1=index1, object1=object1)
        else:
            index2 = int(values["index2"])
            object2 = _resolve_single_sketch_object(mainWindow, values["object2"])
            cons_result = pyncti_sketch_AddConsLength(mainWindow.NCTI, mainWindow.doc, sketch, value1=index1, object1=object1, value2=index2, object2=object2)
    except ValueError as e:
        wx.MessageBox(str(e), "输入错误", wx.OK | wx.ICON_WARNING)
        return

    if cons_result:
        mainWindow.lastSketchObject = cons_result
    mainWindow.updateTree()

def on_exec_constraint_button_SketchConsParallel(mainWindow, event=None):
    # 距离尺寸
    if not _require_doc(mainWindow):
        return

    sketch = _require_sketch(mainWindow, "AddConsParallelSize", "请先创建草图或确认底层已暴露 AddConsParallelSize")
    if sketch is None:
        return

    values = _show_sketch_form_dialog(
        mainWindow,
        "距离尺寸",
        [
            ("size", "距离值", "10"),
            ("object1", "对象1", "a1"),
            ("object2", "对象2", "a2"),
        ],
        min_size=(520, 180),
    )
    if values is None:
        return

    try:
        size = float(values["size"])
        object1 = _resolve_single_sketch_object(mainWindow, values["object1"])
        object2 = _resolve_single_sketch_object(mainWindow, values["object2"])
    except ValueError as e:
        _show_input_error(e)
        return

    cons_result = pyncti_sketch_AddConsParallelSize(
        mainWindow.NCTI,
        mainWindow.doc,
        sketch,
        size,
        object1,
        object2,
    )
    _finish_sketch_command(mainWindow, cons_result)

def on_exec_constraint_button_LockSize(mainWindow, event=None):
    # 锁定尺寸
    if not _require_doc(mainWindow):
        return
    sketch = _require_sketch(mainWindow, "LockSize")
    if sketch is None:
        return

    values = _show_sketch_form_dialog(
        mainWindow,
        "锁定尺寸",
        [
            ("is_lock", "锁定状态(1锁定/0解锁)", "1"),
            ("constraint_names", "约束名称", "yhc1"),
        ],
        min_size=(560, 190),
    )
    if values is None:
        return
    try:
        is_lock = int(values["is_lock"])
        constraint_names = _resolve_sketch_object_name_list(mainWindow, values["constraint_names"])
    except ValueError as e:
        _show_input_error(e)
        return

    result = pyncti_sketch_LockSize(mainWindow.NCTI, mainWindow.doc, sketch, is_lock, constraint_names)
    _finish_sketch_command(mainWindow, result)

def on_exec_constraint_button_AddConsYAxis(mainWindow, event=None):
    # 竖直
    if not _require_doc(mainWindow):
        return
    sketch = _require_sketch(mainWindow, "AddConsYAxis")
    if sketch is None:
        return

    values = _show_sketch_form_dialog(
        mainWindow,
        "竖直约束",
        min_size=(520, 240),
        variant_selector=[
            ("单线竖直", [
                ("object1", "线对象", "a1"),
            ]),
            ("两点竖直", [
                ("index1", "对象1点索引", "1"),
                ("object1", "对象1", "a1"),
                ("index2", "对象2点索引", "0"),
                ("object2", "对象2", "a2"),
            ]),
        ],
    )
    if values is None:
        return

    try:
        if values.get("variant") == "单线竖直":
            cons_result = pyncti_sketch_AddConsYAxis(
                mainWindow.NCTI,
                mainWindow.doc,
                sketch,
                object1=values["object1"],
            )
        else:
            index1 = int(values["index1"])
            index2 = int(values["index2"])
            cons_result = pyncti_sketch_AddConsYAxis(
                mainWindow.NCTI,
                mainWindow.doc,
                sketch,
                value1=index1,
                object1=values["object1"],
                value2=index2,
                object2=values["object2"],
            )
    except ValueError as e:
        _show_input_error(e)
        return

    _finish_sketch_command(mainWindow, cons_result, refresh=True)

def on_exec_constraint_button_AddConsXAxis(mainWindow, event=None):
    # 水平
    if not _require_doc(mainWindow):
        return
    sketch = _require_sketch(mainWindow, "AddConsXAxis")
    if sketch is None:
        return

    values = _show_sketch_form_dialog(
        mainWindow,
        "水平约束",
        min_size=(520, 240),
        variant_selector=[
            ("单线水平", [
                ("object1", "线对象", "a1"),
            ]),
            ("两点水平", [
                ("index1", "对象1点索引", "1"),
                ("object1", "对象1", "a1"),
                ("index2", "对象2点索引", "0"),
                ("object2", "对象2", "a2"),
            ]),
        ],
    )
    if values is None:
        return

    try:
        if values.get("variant") == "单线水平":
            cons_result = pyncti_sketch_AddConsXAxis(
                mainWindow.NCTI,
                mainWindow.doc,
                sketch,
                object1=values["object1"],
            )
        else:
            index1 = int(values["index1"])
            index2 = int(values["index2"])
            cons_result = pyncti_sketch_AddConsXAxis(
                mainWindow.NCTI,
                mainWindow.doc,
                sketch,
                value1=index1,
                object1=values["object1"],
                value2=index2,
                object2=values["object2"],
            )
    except ValueError as e:
        _show_input_error(e)
        return

    _finish_sketch_command(mainWindow, cons_result, refresh=True)

def on_exec_constraint_button_AddConsParallel(mainWindow, event=None):
    # 平行
    if not _require_doc(mainWindow):
        return
    sketch = _require_sketch(mainWindow, "AddConsParallel")
    if sketch is None:
        return

    values = _show_sketch_form_dialog(
        mainWindow,
        "平行约束",
        [
            ("object1", "对象1", "a1"),
            ("object2", "对象2", "a2"),
        ],
        min_size=(520, 180),
    )
    if values is None:
        return
    try:
        object1 = _resolve_single_sketch_object(mainWindow, values["object1"])
        object2 = _resolve_single_sketch_object(mainWindow, values["object2"])
    except ValueError as e:
        _show_input_error(e)
        return

    cons_result = pyncti_sketch_AddConsParallel(mainWindow.NCTI, mainWindow.doc, sketch, object1, object2)
    _finish_sketch_command(mainWindow, cons_result)

def on_exec_constraint_button_AddConsVertical(mainWindow, event=None):
    # 垂直
    if not _require_doc(mainWindow):
        return
    sketch = _require_sketch(mainWindow, "AddConsVertical")
    if sketch is None:
        return

    values = _show_sketch_form_dialog(
        mainWindow,
        "垂直约束",
        [
            ("object1", "对象1", "a1"),
            ("object2", "对象2", "a2"),
        ],
        min_size=(520, 180),
    )
    if values is None:
        return
    try:
        object1 = _resolve_single_sketch_object(mainWindow, values["object1"])
        object2 = _resolve_single_sketch_object(mainWindow, values["object2"])
    except ValueError as e:
        _show_input_error(e)
        return

    cons_result = pyncti_sketch_AddConsVertical(mainWindow.NCTI, mainWindow.doc, sketch, object1, object2)
    _finish_sketch_command(mainWindow, cons_result)

def on_exec_constraint_button_AddConsEqual(mainWindow, event=None):
    # 相等
    if not _require_doc(mainWindow):
        return
    sketch = _require_sketch(mainWindow, "AddConsEqual")
    if sketch is None:
        return

    values = _show_sketch_form_dialog(
        mainWindow,
        "相等约束",
        [
            ("object1", "对象1", "a1"),
            ("object2", "对象2", "a2"),
        ],
        min_size=(520, 180),
    )
    if values is None:
        return
    try:
        object1 = _resolve_single_sketch_object(mainWindow, values["object1"])
        object2 = _resolve_single_sketch_object(mainWindow, values["object2"])
    except ValueError as e:
        _show_input_error(e)
        return

    cons_result = pyncti_sketch_AddConsEqual(mainWindow.NCTI, mainWindow.doc, sketch, object1, object2)
    _finish_sketch_command(mainWindow, cons_result)

def on_exec_constraint_button_AddConsCoincide(mainWindow, event=None):
    # 重合
    if not _require_doc(mainWindow):
        return
    sketch = _require_sketch(mainWindow, "AddConsCoincide")
    if sketch is None:
        return

    values = _show_sketch_form_dialog(
        mainWindow,
        "重合约束",
        min_size=(520, 240),
        variant_selector=[
            ("与原点重合", [
                ("index1", "对象点索引", "0"),
                ("object1", "对象", "a1"),
            ]),
            ("两点重合", [
                ("index1", "对象1点索引", "1"),
                ("object1", "对象1", "a1"),
                ("index2", "对象2点索引", "0"),
                ("object2", "对象2", "a2"),
            ]),
        ],
    )
    if values is None:
        return

    try:
        index1 = int(values["index1"])
        object1 = _resolve_single_sketch_object(mainWindow, values["object1"])
        if values.get("variant") == "与原点重合":
            cons_result = pyncti_sketch_AddConsCoincide(
                mainWindow.NCTI,
                mainWindow.doc,
                sketch,
                value1=index1,
                object1=object1,
            )
        else:
            index2 = int(values["index2"])
            object2 = _resolve_single_sketch_object(mainWindow, values["object2"])
            cons_result = pyncti_sketch_AddConsCoincide(
                mainWindow.NCTI,
                mainWindow.doc,
                sketch,
                value1=index1,
                object1=object1,
                value2=index2,
                object2=object2,
            )
    except ValueError as e:
        _show_input_error(e)
        return

    _finish_sketch_command(mainWindow, cons_result)

def on_exec_constraint_button_AddConsTangent(mainWindow, event=None):
    # 相切
    if not _require_doc(mainWindow):
        return
    sketch = _require_sketch(mainWindow, "AddConsTangent")
    if sketch is None:
        return

    values = _show_sketch_form_dialog(
        mainWindow,
        "相切约束",
        [
            ("object1", "对象1", "a1"),
            ("object2", "对象2", "a2"),
        ],
        min_size=(520, 180),
    )
    if values is None:
        return
    try:
        object1 = _resolve_single_sketch_object(mainWindow, values["object1"])
        object2 = _resolve_single_sketch_object(mainWindow, values["object2"])
    except ValueError as e:
        _show_input_error(e)
        return

    cons_result = pyncti_sketch_AddConsTangent(mainWindow.NCTI, mainWindow.doc, sketch, object1, object2)
    _finish_sketch_command(mainWindow, cons_result)

# 显示与求解
def on_exec_display_solve_button_SwitchConsDisplay(mainWindow, event=None):
    # 显示名称
    if not _require_doc(mainWindow):
        return

    sketch = getattr(mainWindow, "activeSketch", None)
    pyncti_sketch_SwitchConsDisplay(mainWindow.NCTI, mainWindow.doc, sketch)
    mainWindow.updateTree()

def on_exec_display_solve_button_ShowCons(mainWindow, event=None, show_mode=None):
    # 显示约束开/关
    if not _require_doc(mainWindow):
        return

    sketch = _require_sketch(mainWindow, "ShowCons")
    if sketch is None:
        return

    if show_mode is None:
        current_state = getattr(mainWindow, "_sketch_show_cons_enabled", True)
        next_state = not current_state
        show_mode = 1 if next_state else 0
        mainWindow._sketch_show_cons_enabled = next_state

    pyncti_sketch_ShowCons(mainWindow.NCTI, mainWindow.doc, sketch, show_mode)
    mainWindow.updateTree()

def on_exec_display_solve_button_ShowWeakCons(mainWindow, event=None):
    # 显示弱约束
    if not _require_doc(mainWindow):
        return

    sketch = _require_sketch(mainWindow, "ShowWeakCons")
    if sketch is None:
        return

    current_state = getattr(mainWindow, "_sketch_show_weak_cons_enabled", True)
    next_state = not current_state
    pyncti_sketch_ShowWeakCons(mainWindow.NCTI, mainWindow.doc, sketch, 1 if next_state else 0)
    mainWindow._sketch_show_weak_cons_enabled = next_state
    mainWindow.updateTree()

def on_exec_display_solve_button_ShowStrongCons(mainWindow, event=None):
    # 显示强约束
    if not _require_doc(mainWindow):
        return

    sketch = _require_sketch(mainWindow, "ShowStrongCons")
    if sketch is None:
        return

    current_state = getattr(mainWindow, "_sketch_show_strong_cons_enabled", True)
    next_state = not current_state
    pyncti_sketch_ShowStrongCons(mainWindow.NCTI, mainWindow.doc, sketch, 1 if next_state else 0)
    mainWindow._sketch_show_strong_cons_enabled = next_state
    mainWindow.updateTree()

def on_exec_display_solve_button_ShowCoincideCons(mainWindow, event=None):
    # 重合约束显示开关
    if not _require_doc(mainWindow):
        return

    sketch = _require_sketch(mainWindow, "ShowCoincideCons")
    if sketch is None:
        return

    current_state = getattr(mainWindow, "_sketch_show_coincide_cons_enabled", False)
    next_state = not current_state
    pyncti_sketch_ShowCoincideCons(mainWindow.NCTI, mainWindow.doc, sketch, 1 if next_state else 0)
    mainWindow._sketch_show_coincide_cons_enabled = next_state
    mainWindow.updateTree()

# 求解
def on_exec_solve_button_AutoSolve(mainWindow, event=None):
    # 求解开/关
    if not _require_doc(mainWindow):
        return

    current_state = getattr(mainWindow, "_sketch_auto_solve_enabled", True)
    next_state = not current_state
    auto_solve_result = pyncti_sketch_AutoSolve(
        mainWindow.NCTI,
        mainWindow.doc,
        getattr(mainWindow, "yh_doc", None),
        next_state,
    )
    if auto_solve_result is not None:
        mainWindow._sketch_auto_solve_enabled = next_state
    mainWindow.updateTree()

def on_exec_solve_button_ArgumentAutoSnap(mainWindow, event=None):
    # 捕捉添加约束
    if not _require_doc(mainWindow):
        return

    target = _get_snap_solve_ctrl_target(mainWindow)
    if target is None:
        wx.MessageBox(wx.OK | wx.ICON_INFORMATION,)
        return

    _show_snap_solve_ctrl_dialog(mainWindow, target)

def on_exec_solve_button_AutoCalCloseArea(mainWindow, event=None):
    # 自动计算区域开/关
    if not _require_doc(mainWindow):
        return

    yh_doc = _require_yh_doc(mainWindow, "AutoCalCloseArea")
    if yh_doc is None:
        return

    current_state = getattr(mainWindow, "_sketch_auto_close_area_enabled", True)
    next_state = not current_state
    auto_close_area_result = pyncti_sketch_AutoCalCloseArea(mainWindow.NCTI, mainWindow.doc, yh_doc, next_state)
    if auto_close_area_result is not None:
        mainWindow._sketch_auto_close_area_enabled = next_state
    mainWindow.updateTree()

def on_exec_solve_button_AutoCalFreeCons(mainWindow, event=None):
    # 计算弱约束开/关
    if not _require_doc(mainWindow):
        return

    yh_doc = _require_yh_doc(mainWindow, "AutoCalFreeCons")
    if yh_doc is None:
        return

    current_state = getattr(mainWindow, "_sketch_auto_free_cons_enabled", True)
    next_state = not current_state
    auto_free_cons_result = pyncti_sketch_AutoCalFreeCons(mainWindow.NCTI, mainWindow.doc, yh_doc, next_state)
    if auto_free_cons_result is not None:
        mainWindow._sketch_auto_free_cons_enabled = next_state
    mainWindow.updateTree()

def on_exec_solve_button_GetCheckConsResult(mainWindow, event=None):
    # 约束检查
    if not _require_doc(mainWindow):
        return

    sketch = _require_sketch(mainWindow, "GetCheckConsResult")
    if sketch is None:
        return

    check_result = pyncti_sketch_GetCheckConsResult(mainWindow.NCTI, mainWindow.doc, sketch)
    if check_result is None:
        return

    if bool(check_result):
        wx.MessageBox("约束检查通过", "提示", wx.OK | wx.ICON_INFORMATION)
    else:
        wx.MessageBox("约束检查未通过", "提示", wx.OK | wx.ICON_WARNING)

def on_exec_solve_button_SketchCheck(mainWindow, event=None):
    # 草图检查
    on_exec_solve_button_GetCheckConsResult(mainWindow, event)

def on_exec_solve_button_RunSolve(mainWindow, event=None):
    # 主动求解
    if not _require_doc(mainWindow):
        return

    sketch = getattr(mainWindow, "activeSketch", None)
    pyncti_sketch_RunSolve(mainWindow.NCTI, mainWindow.doc, sketch)
    _refresh_sketch_state(mainWindow)

def on_exec_solve_button_RunCalCloseArea(mainWindow, event=None):
    # 计算区域
    if not _require_doc(mainWindow):
        return

    sketch = getattr(mainWindow, "activeSketch", None)
    pyncti_sketch_RunCalCloseArea(mainWindow.NCTI, mainWindow.doc, sketch)
    _refresh_sketch_state(mainWindow)

def on_exec_solve_button_ConsType(mainWindow, event=None):
    # 设置强约束
    if not _require_doc(mainWindow):
        return

    sketch = getattr(mainWindow, "activeSketch", None)
    pyncti_sketch_ConsType(mainWindow.NCTI, mainWindow.doc, sketch, 1)
    _refresh_sketch_state(mainWindow)

# 模式
def on_exec_mode_button_SwitchConsRadius(mainWindow, event=None):
    # 直径半径切换
    if not _require_doc(mainWindow):
        return

    sketch = getattr(mainWindow, "activeSketch", None)
    pyncti_sketch_SwitchConsRadius(mainWindow.NCTI, mainWindow.doc, sketch)
    _refresh_sketch_state(mainWindow)
