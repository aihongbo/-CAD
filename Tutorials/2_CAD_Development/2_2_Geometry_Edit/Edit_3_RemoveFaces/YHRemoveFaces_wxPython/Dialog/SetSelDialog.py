import os
import re
import wx
import wx.lib.scrolledpanel as scrolled

class SelDialog(wx.Dialog):
    def __init__(self, parent=None):
        super().__init__(parent, title="", style=wx.DEFAULT_DIALOG_STYLE | wx.RESIZE_BORDER)
        self.obj_cellIds = []

    def initNcti(self, doc, NCTI):
        self.doc = doc
        self.NCTI = NCTI

    def initWidgets(self, dlgTitle, description):
        self.SetTitle(dlgTitle)
        self.SetSize(486, 165)
        
        # 创建主面板和布局
        panel = scrolled.ScrolledPanel(self)
        panel.SetupScrolling()
        main_sizer = wx.BoxSizer(wx.VERTICAL)
        
        # 创建布局
        h_sizer = wx.BoxSizer(wx.HORIZONTAL)

        # 获取选中实体对象的所有的面
        self.obj_cellIds = self.FindObjAllFaceIds()
        text = f'{description}(范围：{self.obj_cellIds[0]}-{self.obj_cellIds[-1]}，以","分隔)'
        
        label = wx.StaticText(panel, label = text)
        h_sizer.Add(label, 0, wx.ALIGN_CENTER_VERTICAL | wx.ALL, 10)

        self.id_ctrl = wx.TextCtrl(panel, size=(128, 20), style=wx.TE_RICH)
        h_sizer.Add(self.id_ctrl, 0, wx.ALIGN_CENTER_VERTICAL | wx.ALL, 10)

        button = wx.Button(panel, label="预览", size=(56, 24))
        button.Bind(wx.EVT_BUTTON, self.on_previewbutton_clicked)
        h_sizer.Add(button, 0, wx.ALIGN_CENTER_VERTICAL | wx.ALL, 10)
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
        self.doc.ResetCaseResult()
        sel = self.NCTI.SelectionManager(self.doc)
        self.doc.RunCommand("cmd_ncti_remove_faces", sel.ObjectNames[0], sel.CellIDs)
        self.on_previewbutton_clicked(event, is_print=False)
        self.Destroy()

    def on_cancel_button_click(self, event):
        wx.MessageBox("操作已取消。", "提示", wx.OK | wx.ICON_INFORMATION)
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
            if '.' not in match and (int(match) in self.obj_cellIds):
                numbers.append(int(match))
        return numbers

    def on_previewbutton_clicked(self, event, is_print=True):
        if not hasattr(self, 'doc'):
            return
        self.doc.ResetCaseResult()
        sel  = self.NCTI.SelectionManager(self.doc)
        if len(sel.ObjectNames) > 0:
            currObjName = sel.ObjectNames[0]
            lstSelId = self.on_extract_id(event)
            if len(lstSelId) == 0:
                print('请输入合理的ID！')
                return
            
            sel.ClearSelected()
            sel.CellIDs = lstSelId
            sel.ObjectNames = [str(currObjName)] * (len(lstSelId))
            sel.SetSelected()
            self.doc.Update()
            if is_print:
               print(f"预览面ID：{lstSelId}")

    # 获取选中实体对象的所有的面ID
    def FindObjAllFaceIds(self)->list:
        if not hasattr(self, 'doc'):
            return []
        CellIds = []
        self.doc.ResetCaseResult()
        sel = self.NCTI.SelectionManager(self.doc)
        if len(sel.ObjectNames) > 0:
            CellIds = self.doc.FindAllFaces(sel.ObjectNames[0])
        return CellIds