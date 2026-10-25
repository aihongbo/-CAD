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
from scripts.Simulation.pyncti_mesh_surface_generation import pyncti_mesh_surface_generation
from scripts.Simulation.pyncti_mesh_add_force import pyncti_mesh_add_force
from scripts.Simulation.pyncti_mesh_add_spc import pyncti_mesh_add_spc
from scripts.Simulation.pyncti_mesh_add_material import pyncti_mesh_add_material
from scripts.Simulation.pyncti_pickup_mesh import pyncti_pickup_mesh
from scripts.Simulation.pyncti_create_volume_mesh import pyncti_create_volume_mesh

def on_mesh_surface_generation(mainWindow,event = None):
    if False == hasattr(mainWindow, 'doc'):
        return
    pyncti_mesh_surface_generation(mainWindow,mainWindow.NCTI,mainWindow.doc)
    mainWindow.updateTree()

def on_mesh_volume_generation(mainWindow,event = None):
    if False == hasattr(mainWindow, 'doc'):
        return
    pyncti_create_volume_mesh(mainWindow.NCTI,mainWindow.doc)
    mainWindow.updateTree()
    
def on_single_force(mainWindow,event = None):
    if False == hasattr(mainWindow, 'doc'):
        return
    sel = mainWindow.NCTI.SelectionManager(mainWindow.doc)
    if len(sel.CellIDs) == 0:
        wx.MessageBox( "请先选择网格节点","提示")
        return
    pyncti_mesh_add_force(mainWindow.NCTI,mainWindow.doc)
    mainWindow.updateTree()

def on_single_constraint(mainWindow,event = None):
    if False == hasattr(mainWindow, 'doc'):
        return 
    sel = mainWindow.NCTI.SelectionManager(mainWindow.doc)
    if len(sel.CellIDs) == 0:
        wx.MessageBox( "请先选择网格节点","提示")
        return
    pyncti_mesh_add_spc(mainWindow.NCTI,mainWindow.doc)
    mainWindow.updateTree()

def on_material_properties(mainWindow,event = None):
    if False == hasattr(mainWindow, 'doc'):
        return
    sel = mainWindow.NCTI.SelectionManager(mainWindow.doc)
    if len(sel.ObjectNames) == 0:
        wx.MessageBox( "请先选择网格节点","提示")
        return
    pyncti_mesh_add_material(mainWindow.NCTI,mainWindow.doc)
    mainWindow.updateTree()
    
def on_set_pickup_mesh(mainWindow, state,event = None):
    if False == hasattr(mainWindow, 'doc'):
        return
    if state >= 0 and state < 5:
        pyncti_pickup_mesh(mainWindow.NCTI,mainWindow.doc,state)
