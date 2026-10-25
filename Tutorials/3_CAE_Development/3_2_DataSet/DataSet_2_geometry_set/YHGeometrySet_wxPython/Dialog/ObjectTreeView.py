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
import wx.aui as aui
from Pub.ImageTransfrom import svg2bmp
from Pub.configLoad import global_scope

class ObjectTreeView(wx.Panel):
    def __init__(self, parent):
        super().__init__(parent)

        global  global_scope
        self.doc = global_scope["doc"]
        self.NCTI = global_scope["NCTI"]
        self.tree = wx.TreeCtrl(self, size=(200, -1))
        self.imageList = wx.ImageList(16, 16)
        self.imageIdxAssembly = self.imageList.Add(svg2bmp(f'resources/tree/assembly.svg', (16, 16)))
        self.imageIdxPart   = self.imageList.Add(svg2bmp(f'resources/tree/part.svg', (16, 16)))
        self.imageIdxBody   = self.imageList.Add(svg2bmp(f'resources/tree/body.svg', (16, 16)))
        self.imageIdxSel   = self.imageList.Add(svg2bmp(f'resources/tree/selected.svg', (16, 16)))
        self.tree.AssignImageList(self.imageList)

        sizer = wx.BoxSizer(wx.VERTICAL)
        sizer.Add(self.tree, 1, wx.EXPAND)
        self.SetSizer(sizer)

        self.Bind(wx.EVT_TREE_SEL_CHANGED, self._onSelChanged, self.tree)
        self.tree.Bind(wx.EVT_CONTEXT_MENU, self.on_right_click)
        self.create_menu()

    def create_menu(self):
        """创建右击菜单"""
        self.context_menu = wx.Menu()
        
        # 添加菜单项
        id_merge_grid_node = self.context_menu.Append(wx.ID_ANY, "合并节点")
        id_switch_grid_node = self.context_menu.Append(wx.ID_ANY, "切换网格节点显示")
        
        # 绑定菜单事件
        self.Bind(wx.EVT_MENU, self.item_merge_grid_node, id_merge_grid_node)
        self.Bind(wx.EVT_MENU, self.item_switch_grid_node, id_switch_grid_node)

    def getObjectTreeData(self):
        if self.NCTI == None or self.doc == None:
            return None
        return self.doc.GetObjectTree(False)

    def updateTree(self):
        self.tree.DeleteAllItems()
        data = self.getObjectTreeData()
        if data == None:
            return
        actDoc = None
        actDocPtr = self.doc.GetActivateDoc()
        if actDocPtr != None:
            names = self.doc.GetObjectName([actDocPtr])
            if names != None and len(names) > 0 and names[0][0] != '':
                actDoc = names[0][0]
        self.Bind(wx.EVT_TREE_SEL_CHANGED, None, self.tree)
        self._addTreeItem(self.doc, None, data, actDoc)
        self.Bind(wx.EVT_TREE_SEL_CHANGED, self._onSelChanged, self.tree)
        self.tree.ExpandAll()

    def _addTreeItem(self, doc, parent, item, actObj):
        currentTreeItem = None

        displayName = item['name']
        names = doc.GetObjectName([item['obj']])
        if names != None and len(names) > 0 and names[0][1] != '':
            displayName = names[0][1]

        img = None
        if item['type'] == 'doc_assembly':
            img = self.imageIdxAssembly
        elif item['type'] == 'doc_part':
            img = self.imageIdxPart
        else:
            img = self.imageIdxBody
        
        if parent == None:
            currentTreeItem = self.tree.AddRoot(displayName, data=item, image=img, selImage=self.imageIdxSel)
        else:
            currentTreeItem = self.tree.AppendItem(parent, displayName, data=item, image=img, selImage=self.imageIdxSel)
        if actObj!=None and item['name'] == actObj:
            self.tree.SelectItem(currentTreeItem)    
        if 'child' in item:
            for child_item in item['child']:
                self._addTreeItem(doc, currentTreeItem, child_item, actObj)

    def _onSelChanged(self, event):
        item = event.GetItem()
        if item.IsOk():
            data = self.tree.GetItemData(item)
            self.doc.ActivateDoc(data['obj'])
            if data['type'] != 'doc_part' and data['type'] != 'doc_assembly':
                sel = self.NCTI.SelectionManager(self.doc)
                sel.ObjectNames = [data['name']]
                sel.SetSelected()
                self.doc.Update()
        event.Skip()

    def on_right_click(self, event):
        # point = event.GetPosition()
        point = self.tree.ScreenToClient(wx.GetMousePosition())
        # item, flags = self.tree.HitTest(point)
        
        # if item and item.IsOk():            
        selections = self.tree.GetSelections()
        sels = []
        for item in selections:
            data = self.tree.GetItemData(item)
            self.doc.ActivateDoc(data['obj'])
            if data['type'] != 'doc_part' and data['type'] != 'doc_assembly':
                sels.append(data['name'])
        if len(sels) > 0:
            obj = self.NCTI.Object(self.doc)
            types = obj.GetObjectType(sels)
            if types is None:
                return
            bOK = True
            for i in range(len(types)):
                if types[i] != "grp_ncti_grid_mesh":
                    bOK = False
                    break
            if bOK:
                # 显示菜单
                self.PopupMenu(self.context_menu, point)
    
    def item_merge_grid_node(self,event):
        sel = self.NCTI.SelectionManager(self.doc)
        if len(sel.ObjectNames) == 0:
            return
        for name in sel.ObjectNames:
            grid = self.NCTI.GridMesh(self.doc, name)
            grid.MergeGridNode()

    def item_switch_grid_node(self, event):
        selections = self.tree.GetSelections()
        sels = []
        for item in selections:
            data = self.tree.GetItemData(item)
            self.doc.ActivateDoc(data['obj'])
            if data['type'] != 'doc_part' and data['type'] != 'doc_assembly':
                sels.append(data['name'])
        self.on_diaplay_selected_grid_node(sels)

    def on_diaplay_selected_grid_node(self, names):
        for name in names:
            grid = self.NCTI.GridMesh(self.doc, name)
            grid.SwitchGridNode()
        
