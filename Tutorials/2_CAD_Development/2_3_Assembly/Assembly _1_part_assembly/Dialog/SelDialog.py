import os
import re
import wx
import wx.lib.scrolledpanel as scrolled

class SelDialog(wx.Dialog):
    def __init__(self, parent=None):
        super().__init__(parent, title="", style=wx.DEFAULT_DIALOG_STYLE | wx.RESIZE_BORDER)
        self.outDict = {}
        self.result = wx.ID_CANCEL

    def initNcti(self, doc, NCTI):
        self.doc = doc
        self.NCTI = NCTI

    def initWidgets(self, dlgTitle, description,selType):
        self.SetTitle(dlgTitle)
        self.SetSize(360, 165)
        
        # 创建主面板和布局
        panel = scrolled.ScrolledPanel(self)
        panel.SetupScrolling()
        main_sizer = wx.BoxSizer(wx.VERTICAL)
        
        # 创建布局
        h_sizer = wx.BoxSizer(wx.HORIZONTAL)

        text = description
        label = wx.StaticText(panel, label = text)
        h_sizer.Add(label, 0, wx.ALIGN_CENTER_VERTICAL | wx.ALL, 10)
        #selType 1:选点  2:选线  3:选面  4:all
        self.selType = selType
        selTxt = '未选择'
        if selType == 1:
            selTxt = '已选择0个点'
        elif selType == 2:
            selTxt = '已选择0条边'
        elif selType == 3:
            selTxt = '已选择0个面'
        else:
            selTxt = '未选择'
        label2 = wx.StaticText(panel, size=(128, 20), label = selTxt)
        h_sizer.Add(label2, 0, wx.ALIGN_CENTER_VERTICAL | wx.ALL, 10)
        self.label2 = label2

        button = wx.Button(panel, label="选择", size=(56, 24))
        button.Bind(wx.EVT_BUTTON, self.FindObjNamesAndIds)
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
    
    def show_modeless_block(self):
        """
        显示对话框，阻塞代码执行，但不阻止父窗口操作
        """
        self._finished = False
        self.Show()  # 非模态显示
        
        # 创建自定义事件循环，等待对话框关闭
        # 使用 wx.GetApp().Yield() 来保持主界面响应
        while not self._finished:
            wx.GetApp().Yield()  # 处理事件，允许父窗口操作
            wx.MilliSleep(10)   # 小睡避免CPU占用过高
        
        return self.result

    def on_ok_button_click(self, event):
        self.result = wx.ID_OK
        self._finished = True
        #self.EndModal(wx.ID_OK)

    def on_cancel_button_click(self, event):
        sel  = self.NCTI.SelectionManager(self.doc)
        sel.ClearSelected()
        self.doc.Update()
        self.result = wx.ID_CANCEL
        self._finished = True
        #self.EndModal(wx.ID_CANCEL)

    # 获取选中实体对象的名字和子元素ID
    def FindObjNamesAndIds(self, event):
        if not hasattr(self, 'doc'):
            return []
        selObjNames = {}
        self.doc.ResetCaseResult()
        sel = self.NCTI.SelectionManager(self.doc)
        if len(sel.ObjectNames) > 0:
            objNames = []
            objIds = []
            nameAndEdgeIds = {}
            for i in range (len(sel.ObjectNames)):
                if i < len(sel.CellIDs):
                    obj_name = sel.ObjectNames[i]
                    objId = sel.CellIDs[i]
                    all_typeId = []
                    if obj_name in nameAndEdgeIds.keys():
                        all_typeId = nameAndEdgeIds[obj_name]
                    else:
                        all_typeId = []
                        #selType 1:选点  2:选线  3:选面  4:all
                        if self.selType == 1:
                            all_typeId = self.doc.FindAllVertexs(obj_name)
                        elif self.selType == 2:
                            all_typeId = self.doc.FindAllEdges(obj_name)
                        elif self.selType == 3:
                            all_typeId = self.doc.FindAllFaces(obj_name)
                        nameAndEdgeIds[obj_name] = all_typeId
                    if objId in all_typeId or self.selType == 4:
                        objNames.append(obj_name)
                        objIds.append(objId)

            selObjNames["names"] = objNames
            selObjNames["CellIDs"] = objIds
            unique = list(set(sel.ObjectNames))

            selTxt = '未选择'
            if self.selType == 1:
                selTxt = '个点'
            elif self.selType == 2:
                selTxt = '条边'
            elif self.selType == 3:
                selTxt = '个面'
            else:
                selTxt = '个对象'

            if len(unique) == 1:
                self.label2.SetLabelText(f'已选择{len(objIds)}{selTxt}')
            else:
                self.label2.SetLabelText(f'已选择{len(unique)}个实体,{len(objIds)}{selTxt}')
        else:
            self.label2.SetLabelText('已选择0条边')
        self.outDict = selObjNames
    