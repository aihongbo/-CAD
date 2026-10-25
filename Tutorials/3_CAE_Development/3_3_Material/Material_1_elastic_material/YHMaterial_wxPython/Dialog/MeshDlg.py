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
import os
import wx
import wx.xrc
import wx.lib.scrolledpanel as scrolled
from Pub.configLoad import global_scope

class MeshSettingView(wx.Dialog):
    """网格设置对话框"""
    def __init__(self, args, parent=None):
        style = wx.DEFAULT_DIALOG_STYLE | wx.RESIZE_BORDER
        super().__init__(parent, title="网格设置", style=style)
        
        self.parentMainWindow = parent
        current_file = os.path.abspath(__file__)
        project_root = os.path.dirname(os.path.dirname(current_file))
        if os.path.exists(project_root + '/resources/ncti.ico'):
            self.SetIcon(wx.Icon(project_root + '/resources/ncti.ico', wx.BITMAP_TYPE_ICO))
        # 初始化文档和NCTI对象
        global  global_scope
        self.doc = global_scope["doc"]
        self.NCTI = global_scope["NCTI"]
        if  isinstance(args,list) and len(args) == 2 and isinstance(args[0],dict):
            self.args = args[0]
            self.parentMainWindow = args[1]
        elif isinstance(args,dict) and len(args) == 1:
            self.args = args
        # 创建控件
        self._create_controls()
        
        # 布局
        self._create_layout()
        
        # 绑定事件
        self._bind_events()
        
        # 初始化数据
        self._init_data()
        
        # 设置对话框属性
        self.SetSize(400, 500)
        self.Centre()
        
    def _create_controls(self):
        """创建所有控件"""
        # 创建滚动面板
        self.scroll_panel = scrolled.ScrolledPanel(self)
        self.scroll_panel.SetupScrolling()
        
        # 网格命令标签
        self.lbl_mesh_cmd = wx.StaticText(self.scroll_panel, label="网格命令:")
        
        # 网格尺寸
        self.lbl_size = wx.StaticText(self.scroll_panel, label="网格尺寸:")
        self.le_size = wx.TextCtrl(self.scroll_panel)
        
        # 网格类型
        self.lbl_mesh_type = wx.StaticText(self.scroll_panel, label="网格类型:")
        self.cb_mesh_type = wx.ComboBox(self.scroll_panel, choices=["三角形","混合四边形", "全四边形"], style=wx.CB_READONLY)
        
        # 角度容差
        self.lbl_angle = wx.StaticText(self.scroll_panel, label="角度容差:")
        self.sb_angle = wx.SpinCtrlDouble(self.scroll_panel, min=0, max=180, inc=0.5)
        self.sb_angle.SetDigits(1)  # 设置小数位数
        
        # 曲率自适应
        self.lbl_auto = wx.StaticText(self.scroll_panel, label="曲率自适应:")
        self.sb_auto = wx.SpinCtrl(self.scroll_panel, min=0, max=10)
        
        # 二阶网格
        self.lbl_high = wx.StaticText(self.scroll_panel, label="二阶网格:")
        self.cb_high = wx.CheckBox(self.scroll_panel)
        
        # 选择按钮
        self.pb_select = wx.Button(self.scroll_panel, label="选择对象")
        self.lbl_count = wx.StaticText(self.scroll_panel, label="0")
        
        # 确定和取消按钮
        self.btn_ok = wx.Button(self, label="确定")
        self.btn_cancel = wx.Button(self, label="取消")
        
    def _create_layout(self):
        """创建布局"""
        # 主布局
        main_sizer = wx.BoxSizer(wx.VERTICAL)
        main_sizer.Add(self.scroll_panel, 1, wx.EXPAND | wx.ALL, 5)
        
        # 按钮布局
        btn_sizer = wx.BoxSizer(wx.HORIZONTAL)
        btn_sizer.AddStretchSpacer()
        btn_sizer.Add(self.btn_cancel, 0, wx.RIGHT, 10)
        btn_sizer.Add(self.btn_ok, 0)
        btn_sizer.AddStretchSpacer()
        
        main_sizer.Add(btn_sizer, 0, wx.EXPAND | wx.ALL, 5)
        
        # 滚动面板内部布局
        form_sizer = wx.FlexGridSizer(cols=2, vgap=10, hgap=10)
        form_sizer.AddGrowableCol(1, 1)
        
        # 添加控件到表单
        form_sizer.Add(self.lbl_size, 0, wx.ALIGN_CENTER_VERTICAL | wx.ALIGN_RIGHT)
        form_sizer.Add(self.le_size, 1, wx.EXPAND)
        
        form_sizer.Add(self.lbl_mesh_type, 0, wx.ALIGN_CENTER_VERTICAL | wx.ALIGN_RIGHT)
        form_sizer.Add(self.cb_mesh_type, 1, wx.EXPAND)
        
        form_sizer.Add(self.lbl_angle, 0, wx.ALIGN_CENTER_VERTICAL | wx.ALIGN_RIGHT)
        form_sizer.Add(self.sb_angle, 1, wx.EXPAND)
        
        form_sizer.Add(self.lbl_auto, 0, wx.ALIGN_CENTER_VERTICAL | wx.ALIGN_RIGHT)
        form_sizer.Add(self.sb_auto, 1, wx.EXPAND)
        
        form_sizer.Add(self.lbl_high, 0, wx.ALIGN_CENTER_VERTICAL | wx.ALIGN_RIGHT)
        form_sizer.Add(self.cb_high, 1, wx.EXPAND)
        
        form_sizer.Add(self.pb_select, 0, wx.ALIGN_CENTER_VERTICAL | wx.ALIGN_RIGHT)
        
        # 选择数量布局
        select_sizer = wx.BoxSizer(wx.HORIZONTAL)
        select_sizer.Add(wx.StaticText(self.scroll_panel, label="已选对象数量:"), 0, wx.RIGHT, 5)
        select_sizer.Add(self.lbl_count, 0)
        form_sizer.Add(select_sizer, 1, wx.EXPAND)
        
        # 设置滚动面板布局
        scroll_sizer = wx.BoxSizer(wx.VERTICAL)
        scroll_sizer.Add(form_sizer, 1, wx.EXPAND | wx.ALL, 10)
        self.scroll_panel.SetSizer(scroll_sizer)
        
        self.SetSizer(main_sizer)
        self.Layout()
        
    def _bind_events(self):
        """绑定事件"""
        self.btn_ok.Bind(wx.EVT_BUTTON, self.on_ok_clicked)
        self.btn_cancel.Bind(wx.EVT_BUTTON, self.on_cancel_clicked)
        self.pb_select.Bind(wx.EVT_BUTTON, self.on_select_clicked)
        
    def _init_data(self):
        """初始化数据"""
        if "网格命令" not in self.args:
            wx.MessageBox("请填写网格命令字段！", "输入错误", wx.OK | wx.ICON_WARNING)
            return
            
        if "网格尺寸" in self.args:
            self.le_size.SetValue(str(self.args["网格尺寸"]))
        else:
            wx.MessageBox("请填写网格尺寸字段！", "输入错误", wx.OK | wx.ICON_WARNING)
            return
            
        if "网格类型" in self.args:
            mesh_type = str(self.args["网格类型"])
            if mesh_type in ["三角形", "混合四边形", "全四边形"]:
                self.cb_mesh_type.SetValue(mesh_type)
        else:
            wx.MessageBox("请填写网格类型字段！", "输入错误", wx.OK | wx.ICON_WARNING)
            return
            
        if "角度容差" in self.args:
            self.sb_angle.SetValue(float(self.args["角度容差"]))
        else:
            wx.MessageBox("请填写角度容差字段！", "输入错误", wx.OK | wx.ICON_WARNING)
            return
            
        if "曲率自适应" in self.args:
            self.sb_auto.SetValue(int(self.args["曲率自适应"]))
        else:
            wx.MessageBox("请填写曲率自适应字段！", "输入错误", wx.OK | wx.ICON_WARNING)
            return
            
        if "二阶网格" in self.args:
            self.cb_high.SetValue(int(self.args["二阶网格"]) == 1)
        else:
            wx.MessageBox("请填写二阶网格字段！", "输入错误", wx.OK | wx.ICON_WARNING)
            return
            
    def on_select_clicked(self, event):
        """选择对象按钮点击事件"""
        if self.NCTI and self.doc:
            sel = self.NCTI.SelectionManager(self.doc)
            count = len(sel.ObjectNames) if hasattr(sel, 'ObjectNames') else 0
            self.lbl_count.SetLabel(str(count))
            
    def on_ok_clicked(self, event):
        """确定按钮点击事件"""
        count_text = self.lbl_count.GetLabel()
        try:
            count = int(count_text)
        except ValueError:
            count = 0
            
        if count > 0 and self.NCTI and self.doc:
            sel = self.NCTI.SelectionManager(self.doc)
            if hasattr(sel, 'ObjectNames') and len(sel.ObjectNames) > 0:
                # 获取网格类型
                mesh_type_str = self.cb_mesh_type.GetValue()
                mesh_type = 0
                if mesh_type_str == "混合四边形":
                    mesh_type = 1
                elif mesh_type_str == "全四边形":
                    mesh_type = 2
                    
                # 获取其他参数
                try:
                    mesh_size = float(self.le_size.GetValue())
                except ValueError:
                    wx.MessageBox("网格尺寸必须是数字！", "输入错误", wx.OK | wx.ICON_WARNING)
                    return
                    
                angle_tol = self.sb_angle.GetValue()
                auto_curl = self.sb_auto.GetValue()
                high_order = 1 if self.cb_high.GetValue() else 0
                
                # 确定网格命令
                mesh_cmd = self.args.get("网格命令", "")
                if mesh_cmd == "体网格":
                    mesh_cmd = "cmd_ncti_create_volume_mesh"
                elif mesh_cmd == "面网格":
                    mesh_cmd = "cmd_ncti_create_surface_mesh"
                else:
                    wx.MessageBox("无效的网格命令！", "错误", wx.OK | wx.ICON_ERROR)
                    return
                    
                # 生成网格名称
                mesh_names = ["mesh_" + obj for obj in sel.ObjectNames]
                
                # 执行命令
                if hasattr(self.doc, 'RunCommand'):
                    self.doc.RunCommand(
                        mesh_cmd, 
                        sel.ObjectNames, 
                        mesh_names, 
                        {
                            "MeshSize": mesh_size,
                            "MeshType": mesh_type,
                            "AngleTol": angle_tol,
                            "AutoCurvature": auto_curl,
                            "HighOrder": high_order
                        }
                    )
                if self.parentMainWindow:
                    self.parentMainWindow.updateTree()
                self.Close()
                # self.EndModal(wx.ID_OK)
        else:
            wx.MessageBox("请先选择对象", "提示", wx.OK | wx.ICON_WARNING)
            
    def on_cancel_clicked(self, event):
        """取消按钮点击事件"""
        # self.Destroy()
        self.EndModal(wx.ID_CANCEL)
        
    def closeEvent(self, event):
        """关闭事件"""
        # 如果需要发射关闭信号，可以在这里添加
        # self.closePreview.emit()
        event.Skip()

def MeshDialog(*arg):
    window = MeshSettingView(*arg) 
    #preview = PreviewLabel(window)
    #window.installEventFilter(preview)
    #preview.show()
    window.Show()
    # if window.ShowModal() == wx.ID_OK:
    #     print(print("网格设置：设置成功"))
    #     return True
    # return False

