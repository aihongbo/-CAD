import os
import re
import wx
import wx.lib.scrolledpanel as scrolled

class SelDialog(wx.Dialog):
    def __init__(self, parent=None, hide_cells=True):
        super().__init__(parent, title="", style=wx.DEFAULT_DIALOG_STYLE | wx.RESIZE_BORDER)
        self.hide_cells = hide_cells
        self.obj_faceIds = []
        self.obj_edgeIds = []

    def initNcti(self, doc, NCTI):
        self.doc = doc
        self.NCTI = NCTI

    def initWidgets(self, dlgTitle, description):
        self.SetTitle(dlgTitle)
        self.SetSize(526, 165)
        
        # 创建主面板和布局
        panel = scrolled.ScrolledPanel(self)
        panel.SetupScrolling()
        main_sizer = wx.BoxSizer(wx.VERTICAL)
        
        # 创建布局
        h_sizer = wx.BoxSizer(wx.HORIZONTAL)


        self.obj_edgeIds = self.FindObjAllEdgeIds()
        self.obj_faceIds = self.FindObjAllFaceIds()
        
        text = f'{description}(面范围：{self.obj_faceIds[0]}-{self.obj_faceIds[-1]}，边范围：{self.obj_edgeIds[0]}-{self.obj_edgeIds[-1]}，以","分隔)'
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

    def on_ok_button_click(self, event):
        if not hasattr(self, 'doc'):
            return
        self.doc.ResetCaseResult()
        sel  = self.NCTI.SelectionManager(self.doc)
        if len(sel.ObjectNames) > 0:
            # currObjName = sel.ObjectNames[0]
            lstSelId = self.on_extract_id(event)
            if len(lstSelId) == 0:
                print('请输入合理的ID！')
                return
            

            view = self.NCTI.View(self.doc.ID)
            if len(set(sel.ObjectNames)) == 1:
                lstNames = [sel.ObjectNames[0]] * len(lstSelId)
                if self.hide_cells:
                    # 设置隐藏指定拓扑对象，0：隐藏，1：显示
                    view.SetObjVis(lstNames, 0, lstSelId)
                    sel.ClearSelected()
                    # self.doc.Update()
                else:
                    # 设置仅显选择，注意对象名称列表和ID列表的长度必须相同
                    view.ShowOnly(lstNames, lstSelId)
                    sel.ClearSelected()
                    # self.doc.Update()
            else:
                print(f"请选中同一个实体对象上的拓扑元素！")

        elif len(sel.ObjectNames) == 0:
            print(f"请选中要设置边显示的实体对象！")
        self.Destroy()

    def on_cancel_button_click(self, event):
        sel  = self.NCTI.SelectionManager(self.doc)
        sel.ClearSelected()
        self.doc.Update()
        self.Destroy()

    def on_extract_id(self, event):
        input_text = self.id_ctrl.GetValue()
        
        # 匹配整数和浮点数（包括负数）
        pattern = r'[-+]?\d*\.?\d+'
        matches = re.findall(pattern, input_text)

        numbers = []
        for match in matches:
            #提取整数并判断是否属于cellIds
            if '.' not in match and (int(match) in self.obj_faceIds or int(match) in self.obj_edgeIds):
                numbers.append(int(match))
        return numbers

    # 获取选中实体对象的所有的边ID
    def FindObjAllEdgeIds(self)->list:
        if not hasattr(self, 'doc'):
            return []
        CellIds = []
        self.doc.ResetCaseResult()
        sel  = self.NCTI.SelectionManager(self.doc)
        if len(sel.ObjectNames) > 0:
            CellIds = self.doc.FindAllEdges(sel.ObjectNames[0])
        return CellIds
    
    # 获取选中实体对象的所有的面ID
    def FindObjAllFaceIds(self)->list:
        if not hasattr(self, 'doc'):
            return []
        CellIds = []
        self.doc.ResetCaseResult()
        sel  = self.NCTI.SelectionManager(self.doc)
        if len(sel.ObjectNames) > 0:
            CellIds = self.doc.FindAllFaces(sel.ObjectNames[0])
        return CellIds
