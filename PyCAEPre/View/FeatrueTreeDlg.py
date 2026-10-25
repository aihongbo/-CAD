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
import wx.lib.agw.customtreectrl as CT
from Pub.configLoad import global_scope

class PythonFeatureTreeDlg(wx.Dialog):
    def __init__(self, parent=None):
        style = wx.DEFAULT_DIALOG_STYLE | wx.RESIZE_BORDER
        super().__init__(parent, title="特征列表", style=style)
        
        # 初始化文档和NCTI对象
        global  global_scope
        self.doc = global_scope["doc"]
        self.NCTI = global_scope["NCTI"]
        
        # 创建控件
        self.tree_ctrl = CT.CustomTreeCtrl(self, style=wx.TR_HAS_BUTTONS | wx.TR_HIDE_ROOT | wx.TR_FULL_ROW_HIGHLIGHT)
        self.tree_ctrl.SetBackgroundColour(wx.WHITE)
        
        # 添加移除按钮
        self.btn_remove = wx.Button(self, label="移除特征")
        
        # 布局
        sizer = wx.BoxSizer(wx.VERTICAL)
        sizer.Add(self.tree_ctrl, 1, wx.EXPAND | wx.ALL, 5)
        sizer.Add(self.btn_remove, 0, wx.ALIGN_CENTER | wx.ALL, 5)
        
        self.SetSizerAndFit(sizer)
        self.SetSize(400, 400)
        
        # 绑定事件
    
        self.tree_ctrl.Bind(CT.EVT_TREE_ITEM_CHECKING, self.on_tree_item_checked)
        # self.tree_ctrl.Bind(CT.EVT_TREE_ITEM_CHECKED, self.on_tree_item_checked)
        self.tree_ctrl.Bind(CT.EVT_TREE_ITEM_ACTIVATED, self.on_tree_item_checked)

        self.btn_remove.Bind(wx.EVT_BUTTON, self.on_btn_remove_clicked)
        
        # 设置树形控件属性
        self.tree_ctrl.AddRoot("Root")
        self.tree_ctrl.SetIndent(15)
        
    def init(self, *args_tuple):
        if len(args_tuple) != 2:
            print("FeatureTreeDlg init failed!")
            return
            
        feature_type = args_tuple[0]
        args_data = args_tuple[1]
        
        if not isinstance(args_data, dict):
            print("FeatureTreeDlg init failed!")
            return
            
        root = self.tree_ctrl.GetRootItem()
        
        for key, value in args_data.items():
            body_name = key
            first_item = self.tree_ctrl.AppendItem(root, body_name)
            self.tree_ctrl.SetItemTextColour(first_item, wx.BLUE)
            self.tree_ctrl.CheckItem(first_item, False)
            
            if isinstance(value, list):
                for levs in value:
                    second_item_text = ''
                    if isinstance(levs, list):
                        second_item_text = '[' + ','.join(str(cell) for cell in levs) + ']'
                    elif isinstance(levs, int):
                        second_item_text = f'[{str(levs)}]'
                        
                    second_item = self.tree_ctrl.AppendItem(first_item, second_item_text)
                    self.tree_ctrl.CheckItem(second_item, False)
                    self.tree_ctrl.SetItemData(second_item, levs)
                    
            self.tree_ctrl.SetItemData(first_item, value)
            
        self.tree_ctrl.ExpandAll()
        
    def on_tree_item_checked(self, event):
        item = event.GetItem()
        data = self.tree_ctrl.GetItemData(item)
        cells = []
        
        parent = self.tree_ctrl.GetItemParent(item)
        if not parent.IsOk() or parent == self.tree_ctrl.GetRootItem():
            # 顶层项
            body_name = self.tree_ctrl.GetItemText(item)
            if isinstance(data, list):
                for value in data:
                    if isinstance(value, list):
                        cells.extend(value)
                    else:
                        cells.append(value)
        else:
            # 子项
            body_name = self.tree_ctrl.GetItemText(parent)
            cells = data
            
        self.zoom_cell_ids(body_name, cells)
        
    def on_btn_remove_clicked(self, event):
        body_names = []
        cells_list = []
        items_to_remove = []
        
        root = self.tree_ctrl.GetRootItem()
        child, cookie = self.tree_ctrl.GetFirstChild(root)
        
        while child and child.IsOk():
            body_cells = []
            is_checked = self.tree_ctrl.IsItemChecked(child)
            
            if is_checked:
                body_names.append(self.tree_ctrl.GetItemText(child))
                data = self.tree_ctrl.GetItemData(child)
                for value in data:
                    if isinstance(value, list):
                        body_cells.extend(value)
                    else:
                        body_cells.append(value)
                items_to_remove.append(child)
            else:
                has_checked_child = False
                subchild, subcookie = self.tree_ctrl.GetFirstChild(child)
                
                while subchild and subchild.IsOk():
                    if self.tree_ctrl.IsItemChecked(subchild):
                        has_checked_child = True
                        data = self.tree_ctrl.GetItemData(subchild)
                        if isinstance(data, list):
                            body_cells.extend(data)
                        else:
                            body_cells.append(data)
                        items_to_remove.append(subchild)
                    subchild, subcookie = self.tree_ctrl.GetNextChild(child, subcookie)
                    
                if has_checked_child:
                    body_names.append(self.tree_ctrl.GetItemText(child))
                    
            if body_cells:
                cells_list.append(body_cells)
                
            child, cookie = self.tree_ctrl.GetNextChild(root, cookie)
            
        if len(body_names) == len(cells_list):
            for idx in range(len(body_names)):
                if self.doc:
                    self.doc.RunCommand("cmd_ncti_remove_features", body_names[idx], cells_list[idx])
                    
        self.remove_tree_items(items_to_remove)
        
    def zoom_cell_ids(self, model_name, cell_ids):
        if not self.NCTI:
            return 
        names = []
        cells = []
        sel = self.NCTI.SelectionManager(self.doc)
        sel.ClearSelected()
        
        if isinstance(cell_ids, list):
            for i in cell_ids:
                names.append(model_name)
                cells.append(i)
        else:
            names.append(model_name)
            cells.append(cell_ids)
            
        sel.ObjectNames = names
        sel.CellIDs = cells
        sel.SetSelected()
        
        if self.doc:
            view = self.NCTI.View(self.doc.ID)
            view.Zoom(sel.ObjectNames, sel.CellIDs)
            self.doc.Update()
            
    def remove_tree_items(self, items):
        for item in items:
            self.delete_item_and_children(item)
            
    def delete_item_and_children(self, item):
        if not item.IsOk():
            return
            
        # 递归删除子项
        child, cookie = self.tree_ctrl.GetFirstChild(item)
        while child.IsOk():
            next_child, cookie = self.tree_ctrl.GetNextChild(item, cookie)
            self.delete_item_and_children(child)
            child = next_child
            
        # 删除当前项
        parent = self.tree_ctrl.GetItemParent(item)
        if parent.IsOk():
            self.tree_ctrl.Delete(item)


def InputFeatureTreeDlg(*arg):
    window = PythonFeatureTreeDlg()
    window.init(*arg)
    if window.Show() == wx.ID_OK:
        val = tuple(window)
        print(val)
        return val