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
import json
from scripts.Model.pyncti_display_all import pyncti_display_all
from scripts.Model.pyncti_hide_selected import pyncti_hide_selected
from scripts.Model.pyncti_showonly_selected import pyncti_showonly_selected
from scripts.Model.pyncti_zoom_view_xyz import pyncti_zoom_view_xyz
from scripts.Model.pyncti_zoom import pyncti_zoom
from scripts.Model.pyncti_visual_mode import pyncti_visual_mode
from scripts.Model.pyncti_select_mode import pyncti_select_mode
from scripts.Model.pyncti_select_all import pyncti_select_all
from scripts.Model.pyncti_search_loop_face import pyncti_search_loop_face
from scripts.Model.pyncti_search_connect_face import pyncti_search_connect_face
from scripts.Model.pyncti_search_noplane_connect_face import pyncti_search_noplane_connect_face
from scripts.Model.pyncti_measure_length import pyncti_measure_length
from scripts.Model.pyncti_measure_point import pyncti_measure_point
from scripts.Model.pyncti_measure_midpoint import pyncti_measure_midpoint
from scripts.Model.pyncti_measure_circle_property import pyncti_measure_circle_property
from scripts.Model.pyncti_measure_vector import pyncti_measure_vector
from scripts.Model.pyncti_measure_angle import pyncti_measure_angle

def on_display_all(mainWindow, event = None):
    if False == hasattr(mainWindow, 'doc'):
        return   
    pyncti_display_all(mainWindow.NCTI,mainWindow.doc)
    
def on_hide_selected(mainWindow, event = None):
    if False == hasattr(mainWindow, 'doc'):
        return 
    pyncti_hide_selected(mainWindow.NCTI,mainWindow.doc)
    
def on_diaplay_selected_only(mainWindow, event = None):
    if False == hasattr(mainWindow, 'doc'):
        return   
    pyncti_showonly_selected(mainWindow.NCTI,mainWindow.doc)
    
def on_zoom_view(mainWindow, xyz, event = None):
    if False == hasattr(mainWindow, 'doc'):
        return
    pyncti_zoom_view_xyz(mainWindow.doc, xyz)

def on_zoom_button_click(mainWindow, event = None):
    if False == hasattr(mainWindow, 'doc'):
        return
    pyncti_zoom(mainWindow.NCTI,mainWindow.doc)

def on_visual_checkbox_body(mainWindow, event = None):
    
    if False == hasattr(mainWindow, 'doc'):
        return
    state = event.IsChecked()
    if state:
        pyncti_visual_mode(mainWindow.doc,1, 1, 1)
        mainWindow.visualmode_face.SetValue(True)
        mainWindow.visualmode_face.Enable(False)

        mainWindow.visualmode_line.SetValue(True)
        mainWindow.visualmode_line.Enable(False)

        mainWindow.visualmode_vertex.SetValue(True)
        mainWindow.visualmode_vertex.Enable(False)
    else:
        mainWindow.visualmode_face.Enable(True)
        mainWindow.visualmode_line.Enable(True)
        mainWindow.visualmode_vertex.Enable(True)

def on_visual_checkbox_face(mainWindow, event = None):
    if False == hasattr(mainWindow, 'doc'):
        return
    state = event.IsChecked()
    ischecked_face = 1 if state == True else 0
    ischecked_line = 1 if mainWindow.visualmode_line.IsChecked() else 0
    ischecked_vertex = 1 if mainWindow.visualmode_vertex.IsChecked() else 0
    pyncti_visual_mode(mainWindow.doc,ischecked_face, ischecked_line, ischecked_vertex)

def on_visual_checkbox_line(mainWindow, event = None):
    if False == hasattr(mainWindow, 'doc'):
        return
    state = event.IsChecked()
    ischecked_line = 1 if state == True else 0
    ischecked_face = 1 if mainWindow.visualmode_face.IsChecked() else 0
    ischecked_vertex = 1 if mainWindow.visualmode_vertex.IsChecked() else 0
    pyncti_visual_mode(mainWindow.doc,ischecked_face, ischecked_line, ischecked_vertex)

def on_visual_checkbox_vertex(mainWindow, event = None):
    if False == hasattr(mainWindow, 'doc'):
        return
    state = event.IsChecked()
    ischecked_vertex = 1 if state == True else 0
    ischecked_line = 1 if mainWindow.visualmode_line.IsChecked() else 0
    ischecked_face = 1 if mainWindow.visualmode_face.IsChecked() else 0
    pyncti_visual_mode(mainWindow.doc, ischecked_face, ischecked_line, ischecked_vertex)

def on_sel_checkbox_body(mainWindow, event = None):
    if False == hasattr(mainWindow, 'doc'):
        return
    state = event.IsChecked()
    pyncti_select_mode(mainWindow.NCTI, mainWindow.doc, 0, state == True)
    if state == True:
        mainWindow.selmode_face.SetValue(True)
        mainWindow.selmode_line.SetValue(True)
        mainWindow.selmode_vertex.SetValue(True)


def on_sel_checkbox_face(mainWindow, event = None):
    if False == hasattr(mainWindow, 'doc'):
        return
    state = event.IsChecked()
    pyncti_select_mode(mainWindow.NCTI, mainWindow.doc, 1, state == True)
    if state != True:
        mainWindow.selmode_body.SetValue(False)

def on_sel_checkbox_line(mainWindow, event = None):
    if False == hasattr(mainWindow, 'doc'):
        return
    state = event.IsChecked()
    pyncti_select_mode(mainWindow.NCTI, mainWindow.doc, 2, state == True)
    if state != True:
        mainWindow.selmode_body.SetValue(False)

def on_sel_checkbox_vertex(mainWindow, event = None):
    if False == hasattr(mainWindow, 'doc'):
        return
    state = event.IsChecked()
    pyncti_select_mode(mainWindow.NCTI, mainWindow.doc, 3, state == True)
    if state != True:
        mainWindow.selmode_body.SetValue(False)

def on_allsel_button_click(mainWindow, event = None):
    if False == hasattr(mainWindow, 'doc'):
        return
    if mainWindow.selmode_body.IsChecked():
        pyncti_select_all(mainWindow.NCTI, mainWindow.doc)

def on_airecog_button_click(mainWindow, event = None):
    if False == hasattr(mainWindow, 'doc'):
        return

def on_searchloop_button_click(mainWindow, event = None):
    if False == hasattr(mainWindow, 'doc'):
        return
    pyncti_search_loop_face(mainWindow.NCTI, mainWindow.doc)

def on_searchface_button_click(mainWindow, event = None):
    if False == hasattr(mainWindow, 'doc'):
        return
    pyncti_search_connect_face(mainWindow.NCTI, mainWindow.doc)

def on_searchnoplaneface_button_click(mainWindow, event = None):
    if False == hasattr(mainWindow, 'doc'):
        return
    pyncti_search_noplane_connect_face(mainWindow.NCTI, mainWindow.doc)

def on_measure_getpt_click(mainWindow, event = None):
    if False == hasattr(mainWindow, 'doc'):
        return
    pt = pyncti_measure_point(mainWindow.NCTI, mainWindow.doc)
    print(f"pt: ({pt.X}, {pt.Y}, {pt.Z})")

def on_measure_getlen_click(mainWindow, event = None):
    if False == hasattr(mainWindow, 'doc'):
        return
    len = pyncti_measure_length(mainWindow.NCTI, mainWindow.doc)
    data = extract_fields(len)
    print(data)

def on_measure_getmidpt_click(mainWindow, event = None):
    if False == hasattr(mainWindow, 'doc'):
        return
    pt = pyncti_measure_midpoint(mainWindow.NCTI, mainWindow.doc)
    print(f"pt: ({pt.X}, {pt.Y}, {pt.Z})")

def extract_fields(s):
    try:
        s = str(s)
        json_str = s.replace("'", '"')
        data = json.loads(json_str)
        return data[0]  # 返回第一个字典对象
    except Exception as e:
        print(f"解析错误: {e}")
        return None

def on_measure_getcenter_click(mainWindow, event = None):
    if False == hasattr(mainWindow, 'doc'):
        return
    property = pyncti_measure_circle_property(mainWindow.NCTI, mainWindow.doc)
    data = extract_fields(property)
    x, y, z = data['pt']
    print(f"center: ({x}, {y}, {z})")

def on_measure_getradius_click(mainWindow, event = None):
    if False == hasattr(mainWindow, 'doc'):
        return
    property = pyncti_measure_circle_property(mainWindow.NCTI, mainWindow.doc)
    data = extract_fields(property)
    print(f"radius: {data['radius']}")

def on_getvec_button_click(mainWindow, event = None):
    if False == hasattr(mainWindow, 'doc'):
        return
    property = pyncti_measure_vector(mainWindow.NCTI, mainWindow.doc)
    print(f"vector: ({property})")

def on_getangle_button_click(mainWindow, event = None):
    if False == hasattr(mainWindow, 'doc'):
        return
    property = pyncti_measure_angle(mainWindow.NCTI, mainWindow.doc)
    print(f"angle: {property}")
