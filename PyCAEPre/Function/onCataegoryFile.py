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
from scripts.File.pyncti_import_file import pyncti_import_file
from scripts.File.pyncti_export_file import pyncti_export_file
from scripts.File.pyncti_new_document import pyncti_new_document
from scripts.File.pyncti_new_assembly import pyncti_new_assembly
from scripts.File.pyncti_add_assembly import pyncti_add_assembly
from scripts.File.pyncti_add_part import pyncti_add_part 
from scripts.File.pyncti_import_part import pyncti_import_part 

from scripts.File.pyncti_delete_part import pyncti_delete_part
from scripts.File.pyncti_delete_objects import pyncti_delete_objects
from scripts.File.pyncti_clear_doc import pyncti_clear_doc
from scripts.File.pyncti_close_doc import pyncti_close_doc
from scripts.File.pyncti_redo import pyncti_redo
from scripts.File.pyncti_undo import pyncti_undo
from scripts.File.pyncti_open_ncti_file import pyncti_open_ncti_file
from scripts.File.pyncti_save_file import pyncti_save_file
from Function.onCataegoryModel import on_visual_checkbox_body,on_visual_checkbox_vertex

def importFile(mainWindow, event = None):
    if False == hasattr(mainWindow, 'doc'):
        return        
    pyncti_import_file(mainWindow.NCTI,mainWindow.doc)
    mainWindow.updateTree()
        

def on_export_button_click(mainWindow, event = None):
    if False == hasattr(mainWindow, 'doc'):
        return
    pyncti_export_file(mainWindow.NCTI,mainWindow.doc)
    
def on_new_button_click(mainWindow, event = None):
    if False == hasattr(mainWindow, 'doc'):
        return
    view = pyncti_new_document(mainWindow.NCTI,mainWindow.doc,mainWindow.hwnd)
    if view == None:
        return
    mainWindow.view = view
    setcolor(mainWindow)
    mainWindow.cad_view.updateDoc(mainWindow.NCTI,mainWindow.doc,mainWindow.view)
    mainWindow.autoSizeView()
    mainWindow.updateTree()

def on_new_assembly_button_click(mainWindow, event = None):
    if False == hasattr(mainWindow, 'doc'):
        return   
    view = pyncti_new_assembly(mainWindow.NCTI,mainWindow.doc,mainWindow.hwnd)
    if view == None:
        return   
    mainWindow.view = view 
    mainWindow.cad_view.updateDoc(mainWindow.NCTI,mainWindow.doc,mainWindow.view)
    mainWindow.autoSizeView()
    setcolor(mainWindow)
    mainWindow.updateTree()

def on_add_assembly_button_click(mainWindow, event = None):
    if False == hasattr(mainWindow, 'doc'):
        return  
    pyncti_add_assembly(mainWindow.NCTI,mainWindow.doc)
    mainWindow.autoSizeView()
    mainWindow.updateTree()

def on_add_part_button_click(mainWindow, event = None):
    if False == hasattr(mainWindow, 'doc'):
        return  
    pyncti_add_part(mainWindow.NCTI,mainWindow.doc)
    mainWindow.autoSizeView()
    mainWindow.updateTree()

def on_import_part_button_click(mainWindow, event = None):
    if False == hasattr(mainWindow, 'doc'):
        return        
    pyncti_import_part(mainWindow.NCTI,mainWindow.doc)
    mainWindow.autoSizeView()
    mainWindow.updateTree()

def on_delete_part_button_click(mainWindow, event = None):
    if False == hasattr(mainWindow, 'doc'):
        return  
    pyncti_delete_part(mainWindow.NCTI,mainWindow.doc)
    mainWindow.updateTree()

def on_delete_button_click(mainWindow, event = None):
    if False == hasattr(mainWindow, 'doc'):
        return      
    pyncti_delete_objects(mainWindow.NCTI,mainWindow.doc)
    mainWindow.updateTree()

def on_undo_button_click(mainWindow, event = None):
    if False == hasattr(mainWindow, 'doc'):
        return        
    pyncti_undo(mainWindow.NCTI,mainWindow.doc)
    mainWindow.updateTree()

def on_redo_button_click(mainWindow, event = None):
    if False == hasattr(mainWindow, 'doc'):
        return        
    pyncti_redo(mainWindow.NCTI,mainWindow.doc)
    mainWindow.updateTree()

def on_close_button_click(mainWindow, event = None):
    if False == hasattr(mainWindow, 'doc'):
        return  
    pyncti_close_doc(mainWindow.NCTI,mainWindow.doc)
    mainWindow.updateTree()

def on_clear_button_click(mainWindow, event = None):
    if False == hasattr(mainWindow, 'doc'):
        return  
    pyncti_clear_doc(mainWindow.NCTI,mainWindow.doc)
    mainWindow.updateTree()

def on_open_button_click(mainWindow, event = None):    
    view = pyncti_open_ncti_file(mainWindow.NCTI,mainWindow.doc,mainWindow.hwnd)   
    if view == None:
        return 
    else:
        mainWindow.view = view  
        setcolor(mainWindow)
        mainWindow.cad_view.updateDoc(mainWindow.NCTI,mainWindow.doc,mainWindow.view)   
        mainWindow.autoSizeView()
        mainWindow.updateTree()

def on_save_button_click(mainWindow, event = None):
    if False == hasattr(mainWindow, 'doc'):
        return
    pyncti_save_file(mainWindow.NCTI,mainWindow.doc) 

def setcolor(mainWindow, event = None):
    if False == hasattr(mainWindow, 'doc') or mainWindow.doc.ID == -1:
        return  
    if False == hasattr(mainWindow, 'view'):
        return  
    seg = mainWindow.doc.Scene()
    modelcolor = mainWindow.NCTI.Color(145.0/255.0,158.0/255.0,186.0/255.0)
    backcolor = mainWindow.NCTI.Color(60.0/255.0,60.0/255.0,60.0/255.0)
    highlightcolor = mainWindow.NCTI.Color(245.0/255.0,128.0/255.0,15.0/255.0)
    vertexcolor = mainWindow.NCTI.Color(248.0/255.0, 203.0/255.0, 22.0/255.0)
    seg.SetFaceColor(modelcolor)
    seg.SetBackFaceColor(backcolor)
    seg.SetHighLightColor(highlightcolor)
    seg.SetMarkerColor(vertexcolor)
    mainWindow.view.SetBackgroundColor(5, 38, 79,81, 90, 146)


def getObjectTreeData(ncti, doc):
    if ncti == None or doc == None:
        return None
    return doc.GetObjectTree(False)
    