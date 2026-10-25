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
from scripts.Model.pyncti_display_all import pyncti_display_all
from scripts.Model.pyncti_hide_selected import pyncti_hide_selected
from scripts.Model.pyncti_showonly_selected import pyncti_showonly_selected
from scripts.Model.pyncti_select_all import pyncti_select_all
from scripts.Model.pyncti_select_mode import pyncti_select_mode
from scripts.Model.pyncti_visual_mode import pyncti_visual_mode
from scripts.Model.pyncti_zoom import pyncti_zoom
from scripts.Model.pyncti_zoom_view_xyz import pyncti_zoom_view_xyz


def on_display_all(mainWindow, event=None):
    if not hasattr(mainWindow, "doc"):
        return
    pyncti_display_all(mainWindow.NCTI, mainWindow.doc)
    mainWindow.updateTree()


def on_hide_selected(mainWindow, event=None):
    if not hasattr(mainWindow, "doc"):
        return
    pyncti_hide_selected(mainWindow.NCTI, mainWindow.doc)
    mainWindow.updateTree()


def on_showonly_selected(mainWindow, event=None):
    if not hasattr(mainWindow, "doc"):
        return
    pyncti_showonly_selected(mainWindow.NCTI, mainWindow.doc)
    mainWindow.updateTree()


def on_select_all(mainWindow, event=None):
    if not hasattr(mainWindow, "doc"):
        return
    pyncti_select_all(mainWindow.NCTI, mainWindow.doc)


def on_select_mode(mainWindow, mode, event=None):
    if not hasattr(mainWindow, "doc"):
        return
    pyncti_select_mode(mainWindow.NCTI, mainWindow.doc, mode, True)


def on_visual_mode(mainWindow, mode, event=None):
    if not hasattr(mainWindow, "doc"):
        return

    if mode == "face_line":
        pyncti_visual_mode(mainWindow.doc, True, True, False)
    elif mode == "line":
        pyncti_visual_mode(mainWindow.doc, False, True, False)
    elif mode == "face":
        pyncti_visual_mode(mainWindow.doc, True, False, False)


def on_zoom(mainWindow, event=None):
    if not hasattr(mainWindow, "doc"):
        return
    pyncti_zoom(mainWindow.NCTI, mainWindow.doc)


def on_view_xyz(mainWindow, xyz, event=None):
    if not hasattr(mainWindow, "doc"):
        return
    pyncti_zoom_view_xyz(mainWindow.doc, xyz)
