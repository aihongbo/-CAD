import os
import re
import wx
import wx.lib.scrolledpanel as scrolled
from Pub.configLoad import global_scope

class ElementDialog(wx.Dialog):
    def __init__(self, parent, mesh_name, show_edges=True):
        super().__init__(parent, title="", style=wx.DEFAULT_DIALOG_STYLE | wx.RESIZE_BORDER)
        self.mesh_name = mesh_name
        self.show_edges = show_edges
        self.obj_elements = []
        global  global_scope
        self.doc = global_scope["doc"]
        self.NCTI = global_scope["NCTI"]

    def initWidgets(self, dlgTitle, description):
        self.SetTitle(dlgTitle)
        self.SetSize(388, 165)
        
        # 创建主面板和布局
        panel = scrolled.ScrolledPanel(self)
        panel.SetupScrolling()
        main_sizer = wx.BoxSizer(wx.VERTICAL)
        
        # 创建布局
        h_sizer = wx.BoxSizer(wx.HORIZONTAL)

        # 获取所有单元编号
        self.obj_elements = self.FindObjAllElementIds()
        
        text = f'{description}(ID范围：{self.obj_elements[0]}-{self.obj_elements[-1]})'
        label = wx.StaticText(panel, label = text)
        h_sizer.Add(label, 0, wx.ALIGN_CENTER_VERTICAL | wx.ALL, 10)

        self.id_ctrl = wx.TextCtrl(panel, size=(128, 20), style=wx.TE_RICH)
        h_sizer.Add(self.id_ctrl, 0, wx.ALIGN_CENTER_VERTICAL | wx.ALL, 10)
        main_sizer.Add(h_sizer, 1, wx.EXPAND | wx.ALL, 10)
        
        # 添加按钮
        btn_sizer = wx.BoxSizer(wx.HORIZONTAL)
        cancel_btn = wx.Button(panel, label="退出")
        ok_btn = wx.Button(panel, label="确定")
        
        cancel_btn.Bind(wx.EVT_BUTTON, self.on_cancel_button_click)
        ok_btn.Bind(wx.EVT_BUTTON, self.on_ok_button_click)
        
        btn_sizer.Add(cancel_btn, 0, wx.RIGHT, 10)
        btn_sizer.Add(ok_btn, 0)
        
        main_sizer.Add(btn_sizer, 0, wx.ALIGN_CENTER | wx.ALL, 10)
        panel.SetSizer(main_sizer)
        self.Layout()
        self.Centre()

    def on_extract_id(self, event):
        input_text = self.id_ctrl.GetValue()
        
        # 匹配整数和浮点数（包括负数）
        pattern = r'[-+]?\d*\.?\d+'
        matches = re.findall(pattern, input_text)

        numbers = []
        for match in matches:
            #提取整数并判断是否属于cellIds
            if '.' not in match and (int(match) in self.obj_elements):
                numbers.append(int(match))
        return numbers

    def on_ok_button_click(self, event):
        if not hasattr(self, 'doc'):
            return
        lstSelId = self.on_extract_id(event)
        if len(lstSelId) == 0:
            print('请输入合理的单元ID！')
            return
        elif len(lstSelId) == 1:
            if self.show_edges:
                edges = self.get_element_edges_count(lstSelId[0])
                print(f"{lstSelId[0]}号单元内边的数量：{edges}")
            else :
                faces = self.get_element_faces_count(lstSelId[0])
                print(f"{lstSelId[0]}号单元内面的数量：{faces}")
        else:
            print('仅支持输入1个单元ID！')
        self.Destroy()

    def on_cancel_button_click(self, event):
        self.Destroy()

    # 获取单元内边的数量
    def get_element_edges_count(self, index):
        # 通过单元编号获取单元
        elem0 = self.NCTI.MeshElement(index)
        return elem0.NumberOfEdge()
        
    def get_element_faces_count(self, index):
        # TODO：请在下一行中参考上一个函数添加获取单元内面数的函数实现，完成后可删除当前行及下行
        return 0
    
    # 获取网格对象的所有的单元ID
    def FindObjAllElementIds(self)->list:
        if not hasattr(self, 'doc'):
            return []
        boxMesh = self.NCTI.GridMesh(self.doc, self.mesh_name)
        return sorted(boxMesh.GetAllVertexs())