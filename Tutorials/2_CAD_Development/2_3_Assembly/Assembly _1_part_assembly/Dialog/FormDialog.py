import os
import wx
import wx.lib.scrolledpanel as scrolled
import wx.lib.masked as masked
from Pub.configLoad import global_scope
#from View.PreView import PreviewLabel

class DialogData(wx.Dialog):
    def __init__(self, parent=None):
        super().__init__(parent, title="", style=wx.DEFAULT_DIALOG_STYLE | wx.RESIZE_BORDER)
        global  global_scope
        self.doc = global_scope["doc"]
        self.NCTI = global_scope["NCTI"]
        self.LineEditList = []
        self.ComboBoxList = []
        self.PushButtonList = []
        self.outList = []
        
        current_file = os.path.abspath(__file__)
        project_root = os.path.dirname(os.path.dirname(current_file))
        # 设置图标
        if os.path.exists(project_root + '/resources/ncti.ico'):
            self.SetIcon(wx.Icon(project_root + '/resources/ncti.ico', wx.BITMAP_TYPE_ICO))
        self.Bind(wx.EVT_CHAR_HOOK, self.on_esc_press)

    def initWidgets(self, *args):
        self.argsList = list(args)
        if len(self.argsList) % 2 != 0:
            raise ValueError("参数个数必须为偶数")
        
        self.SetTitle(self.argsList[1])
        self.SetSize(600, 350)
        
        # 创建主面板和布局
        panel = scrolled.ScrolledPanel(self)
        panel.SetupScrolling()
        main_sizer = wx.BoxSizer(wx.VERTICAL)
        
        # 创建表单布局
        form_sizer = wx.FlexGridSizer(cols=2, vgap=10, hgap=15)
        form_sizer.AddGrowableCol(1, 1)
        
        for i in range(2, len(self.argsList), 2):
            caption = self.argsList[i]
            value = self.argsList[i + 1]
            self.outList.append(value)
            
            label = wx.StaticText(panel, label=caption)
            
            if isinstance(value, str):
                text_ctrl = wx.TextCtrl(panel, value=str(value))
                text_ctrl.SetSize(100,20)
                self.LineEditList.append(text_ctrl)
                form_sizer.Add(label, 0, wx.ALIGN_CENTER_VERTICAL | wx.ALIGN_LEFT)
                form_sizer.Add(text_ctrl, 1, wx.EXPAND)
            
            elif isinstance(value, int):
                text_ctrl =  masked.NumCtrl(panel, value=value, integerWidth=5, allowNone=False)#wx.TextCtrl(panel, value=str(value))
                text_ctrl.SetSize(100,20)
                self.LineEditList.append(text_ctrl)
                form_sizer.Add(label, 0, wx.ALIGN_CENTER_VERTICAL | wx.ALIGN_LEFT)
                form_sizer.Add(text_ctrl, 1, wx.EXPAND)
            
            elif isinstance(value, float):
                text_ctrl = masked.NumCtrl(panel, value=value, integerWidth=5, fractionWidth=6)#wx.TextCtrl(panel, value=str(value))
                text_ctrl.SetSize(100,20)
                self.LineEditList.append(text_ctrl)
                form_sizer.Add(label, 0, wx.ALIGN_CENTER_VERTICAL | wx.ALIGN_LEFT)
                form_sizer.Add(text_ctrl, 1, wx.EXPAND)
                
            elif isinstance(value, list):
                combo = wx.ComboBox(panel,style=wx.CB_READONLY, choices=value, value=value[0] if value else "")
                combo.SetSize(100,20)
                # combo.SetStyle(wx.CB_DROPDOWN)
                self.ComboBoxList.append(combo)
                self.LineEditList.append(combo)
                form_sizer.Add(label, 0, wx.ALIGN_CENTER_VERTICAL | wx.ALIGN_LEFT)
                form_sizer.Add(combo, 1, wx.EXPAND)
                
            elif isinstance(value, dict):
                if "sel" in value:
                    sel_label = wx.StaticText(panel, label="未选择")
                    button = wx.Button(panel, label="选取")
                    button.Bind(wx.EVT_BUTTON, lambda evt, b=button: self.on_selbutton_clicked(b))
                    
                    h_sizer = wx.BoxSizer(wx.HORIZONTAL)
                    h_sizer.Add(sel_label, 1, wx.EXPAND | wx.RIGHT, 5)
                    h_sizer.Add(button, 0)
                    
                    form_sizer.Add(label, 0, wx.ALIGN_CENTER_VERTICAL | wx.ALIGN_LEFT)
                    form_sizer.Add(h_sizer, 1, wx.EXPAND)
                    
                    self.PushButtonList.append((button, value, sel_label))
                    
                elif "selFile" in value or "selFiles" in value or "selFolder" in value or "saveFile" in value:
                    text_ctrl = wx.TextCtrl(panel, value="", style=wx.TE_READONLY)
                    button = wx.Button(panel, label="选取")
                    button.Bind(wx.EVT_BUTTON, lambda evt, b=button: self.on_selFilebutton_clicked(b))
                    
                    h_sizer = wx.BoxSizer(wx.HORIZONTAL)
                    h_sizer.Add(text_ctrl, 1, wx.EXPAND | wx.RIGHT, 5)
                    h_sizer.Add(button, 0)
                    
                    form_sizer.Add(label, 0, wx.ALIGN_CENTER_VERTICAL | wx.ALIGN_LEFT)
                    form_sizer.Add(h_sizer, 1, wx.EXPAND)
                    self.LineEditList.append(text_ctrl)
                    self.PushButtonList.append((button, value, text_ctrl))
                elif "CheckList" in value: 
                    checkComboBox = wx.CheckListBox(panel, choices=value["CheckList"], style=wx.LB_MULTIPLE)
                    checkComboBox.SetMaxSize(wx.Size(100, 100))
                    self.LineEditList.append(checkComboBox)
                    form_sizer.Add(label, 0, wx.ALIGN_CENTER_VERTICAL | wx.ALIGN_LEFT)
                    form_sizer.Add(checkComboBox, 1, wx.EXPAND)
                    
            elif type(value).__name__ == "Vector" or type(value).__name__ == "Point":
                # 创建X/Y/Z三个输入框
                x_label = wx.StaticText(panel, label="X:")
                x_ctrl = wx.TextCtrl(panel, value=str(value.X))
                
                y_label = wx.StaticText(panel, label="Y:")
                y_ctrl = wx.TextCtrl(panel, value=str(value.Y))
                
                z_label = wx.StaticText(panel, label="Z:")
                z_ctrl = wx.TextCtrl(panel, value=str(value.Z))


                # 添加到LineEditList，顺序为X,Y,Z
                self.LineEditList.extend([x_ctrl, y_ctrl, z_ctrl])
                
                # 创建水平布局
                h_sizer = wx.BoxSizer(wx.HORIZONTAL)
                h_sizer.Add(x_label, 0, wx.ALIGN_CENTER_VERTICAL | wx.RIGHT, 1)
                h_sizer.Add(x_ctrl, 0, wx.EXPAND | wx.RIGHT, 1)
                h_sizer.Add(y_label, 0, wx.ALIGN_CENTER_VERTICAL | wx.RIGHT, 1)
                h_sizer.Add(y_ctrl, 0, wx.EXPAND | wx.RIGHT, 1)
                h_sizer.Add(z_label, 0, wx.ALIGN_CENTER_VERTICAL | wx.RIGHT, 1)
                h_sizer.Add(z_ctrl, 0, wx.EXPAND)
                
                form_sizer.Add(label, 0, wx.ALIGN_CENTER_VERTICAL | wx.ALIGN_LEFT)
                form_sizer.Add(h_sizer, 1, wx.EXPAND)
                
        main_sizer.Add(form_sizer, 1, wx.EXPAND | wx.ALL, 10)
        
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

    def on_esc_press(self, event):
        if event.GetKeyCode() == wx.WXK_ESCAPE:
            self.EndModal(wx.ID_CANCEL)
        else:
            event.Skip() # 放行其他按键

    def on_ok_button_click(self, event):
        pos = -1
        btn_pos = -1
        
        for i in range(len(self.outList)):
            value = self.outList[i]
            
            if isinstance(value, str):
                pos += 1
                self.outList[i] = self.LineEditList[pos].GetValue()

            elif isinstance(value, (int)):
                pos += 1
                self.outList[i] = int(self.LineEditList[pos].GetValue())

            elif isinstance(value, (float)):
                pos += 1
                self.outList[i] = float(self.LineEditList[pos].GetValue())

            elif isinstance(value, list):
                pos += 1
                selected = self.LineEditList[pos].GetValue()
                value.clear()
                value.append(selected)
                
            elif type(value).__name__ == "Vector":
                pos += 1
                value.X = float(self.LineEditList[pos].GetValue())
                pos += 1
                value.Y = float(self.LineEditList[pos].GetValue())
                pos += 1
                value.Z = float(self.LineEditList[pos].GetValue())
                
            elif type(value).__name__ == "Point":
                pos += 1
                value.X = float(self.LineEditList[pos].GetValue())
                pos += 1
                value.Y = float(self.LineEditList[pos].GetValue())
                pos += 1
                value.Z = float(self.LineEditList[pos].GetValue())
                
            elif isinstance(value, dict):
                if "CheckList" in value: 
                    pos += 1
                    selected = self.LineEditList[pos].GetCheckedStrings()
                    self.outList[i]["CheckList"] = list(selected)
                else:
                    btn_pos += 1
                    btn, val, ctrl = self.PushButtonList[btn_pos]
                    self.outList[i] = val
                
        self.EndModal(wx.ID_OK)

    def on_cancel_button_click(self, event):
        self.EndModal(wx.ID_CANCEL)

    def on_selbutton_clicked(self, btn):
        if not hasattr(self, 'doc'):
            return
        self.doc.ResetCaseResult()
        selObjNames = {}
        sel  = self.NCTI.SelectionManager(self.doc)
        if len(sel.ObjectNames) > 0:
            for button, value, ctrl in self.PushButtonList:
                if button == btn:
                    selObjNames["names"] = sel.ObjectNames
                    ctrl.SetLabel("已选择")
                    value.update(selObjNames)
                    break

    def on_selFilebutton_clicked(self, btn):
        if not hasattr(self, 'doc'):
            return
        for button, value, ctrl in self.PushButtonList:
            if button == btn:
                if "selFile" in value and "filter" in value:
                    wildcard = value["filter"]
                    dlg = wx.FileDialog(self, "选择单个文件", os.path.expanduser("~"), "", wildcard, wx.FD_OPEN)
                    if dlg.ShowModal() == wx.ID_OK:
                        path = dlg.GetPath()
                        value["selFile"] = path
                        ctrl.SetValue(path)
                    dlg.Destroy()
                    
                elif "selFiles" in value and "filter" in value:
                    wildcard = value["filter"]
                    dlg = wx.FileDialog(self, "选择多个文件", os.path.expanduser("~"), "", wildcard, wx.FD_OPEN | wx.FD_MULTIPLE)
                    if dlg.ShowModal() == wx.ID_OK:
                        paths = dlg.GetPaths()
                        value["selFiles"] = paths
                        ctrl.SetValue(", ".join(paths))
                    dlg.Destroy()
                    
                elif "selFolder" in value:
                    dlg = wx.DirDialog(self, "选择文件夹", os.path.expanduser("~"), wx.DD_DEFAULT_STYLE)
                    if dlg.ShowModal() == wx.ID_OK:
                        path = dlg.GetPath()
                        value["selFolder"] = path
                        ctrl.SetValue(path)
                    dlg.Destroy()
                    
                elif "saveFile" in value and "filter" in value:
                    wildcard = value["filter"]
                    default_file = os.path.basename(value.get("saveFile", ""))
                    dlg = wx.FileDialog(self, "保存文件", os.path.expanduser("~"), default_file, wildcard, wx.FD_SAVE | wx.FD_OVERWRITE_PROMPT)
                    if dlg.ShowModal() == wx.ID_OK:
                        path = dlg.GetPath()
                        value["saveFile"] = path
                        ctrl.SetValue(path)
                    dlg.Destroy()
                break

def InputDialog(*arg):
    argsList = list(arg)
    if len(argsList) % 2 != 0:
        print(f"输入参数错误: {arg}")
        wx.MessageBox.critical(None, "错误", f"输入参数错误: {arg}")
        return ()
    window = DialogData()
    window.initWidgets(*arg)
    # 对话框增加预览图
    #preview = PreviewLabel(window)

    if window.ShowModal() == wx.ID_OK:
        val = tuple(window.outList)
        #print(val)
        return val
    return {}

if __name__ == "__main__":
    app = wx.App(False)
    window = DialogData()
    window.initWidgets(-1, "六棱柱参数", "内核",["OCC","PS","PK","OD"], "底部中心点坐标", 0.0, "腔体宽度", 30.0, "腔体高度", 50.0, "内嵌颈内径",  4.3, "内嵌颈长度", 30.0, "橡胶层厚度", 10.0, "腔体厚度", 1.0, "内嵌颈厚度", 1.0, "行数", 1.0, "列数", 1.0)
    if window.ShowModal() == wx.ID_OK:
        val = tuple(window.outList)
        print(val)
    app.OnExit()

