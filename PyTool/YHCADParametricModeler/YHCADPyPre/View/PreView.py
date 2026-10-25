#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Copyright (c) 2025 粤港澳大湾区（广东）国创中心
YHCADPyPre is licensed under Mulan PSL v2.
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
import wx.lib.newevent

# 创建自定义事件用于预览窗口关闭
PreviewClosedEvent, EVT_PREVIEW_CLOSED = wx.lib.newevent.NewEvent()

class PreviewLabel(wx.Frame):
    MIN_WIDTH = 200
    RESIZE_MARGIN = 10
    ASPECT_RATIO = 1.5
    _is_resizing = False
    _resize_start_x = 0
    _original_width = 0
    _original_rect = None
    
    def __init__(self, parent=None):
        # 创建无边框、置顶的窗口
        style = (wx.FRAME_NO_TASKBAR | wx.FRAME_SHAPED | 
                wx.STAY_ON_TOP | wx.NO_BORDER)
        super().__init__(parent, style=style)
        
        # 设置窗口属性
        self.SetTransparent(255)  # 完全不透明
        self._offset = wx.Point(0, 0)
        self.displayLocation = "left"
        self._parent = parent
        self.isLoaded = False #是否已加载图片
        # 初始化图片映射
        self._init_image_mapping()
        
        # 设置鼠标跟踪
        self.SetCursor(wx.Cursor(wx.CURSOR_ARROW))
        self._drag_start_pos = None
        
        # 创建主面板
        self.panel = wx.Panel(self)
        self.panel.SetBackgroundColour(wx.WHITE)
        
        # 创建图片显示控件
        self.image_ctrl = wx.StaticBitmap(self.panel)
        
        # 布局
        sizer = wx.BoxSizer(wx.VERTICAL)
        sizer.Add(self.image_ctrl, 1, wx.EXPAND | wx.ALL, 1)
        self.panel.SetSizer(sizer)
        
        # 设置初始大小
        if parent:
            parent_height = parent.GetSize().height
            self.SetSize(self.MIN_WIDTH, parent_height)
            
        # 绑定事件
        self._bind_events()
        
        # 如果父窗口有closePreview信号，连接它
        if hasattr(parent, 'closePreview'):
            self.Bind(EVT_PREVIEW_CLOSED, self.on_close_preview)
            
    def _init_image_mapping(self):
        """初始化图片映射"""
        current_dir = os.path.dirname(os.path.abspath(__file__))
        resource_dir = os.path.join(current_dir, "..", "resources", "Preview")
        
        self.title_to_image = {
            "创建长方体参数": os.path.join(resource_dir, "create_box.png"),
            "创建圆柱体参数": os.path.join(resource_dir, "create_cylinder.png"),
            "布尔": os.path.join(resource_dir, "boolean.png"),
            "圆角": os.path.join(resource_dir, "fillet.png"),
            "倒角": os.path.join(resource_dir, "chamfer.png"),
            "平移": os.path.join(resource_dir, "pan.png"),
            "缩放": os.path.join(resource_dir, "scale.png"),
            "旋转": os.path.join(resource_dir, "rotate_body.png"),
            "拉伸": os.path.join(resource_dir, "prism.png"),
            "直线阵列": os.path.join(resource_dir, "linear_array.png"),
            "旋转阵列": os.path.join(resource_dir, "rotating_array.png"),
            "查找小特征": os.path.join(resource_dir, "find_small_features.png"),
            "查找圆角": os.path.join(resource_dir, "find_fillets.png"),
            "查找LOGO": os.path.join(resource_dir, "find_logos.png"),
            "查找孔": os.path.join(resource_dir, "find_holes.png"),
            "网格设置": os.path.join(resource_dir, "face_mesh.png"),
            "请输入网格参数": os.path.join(resource_dir, "volume_mesh.png"),
            "添加集中力参数": os.path.join(resource_dir, "add_force.png"),
            "单点约束": os.path.join(resource_dir, "add_spc.png")
        }
        
    def _bind_events(self):
        """绑定所有事件"""
        # 鼠标事件
        self.Bind(wx.EVT_LEFT_DOWN, self.on_mouse_left_down)
        self.Bind(wx.EVT_LEFT_UP, self.on_mouse_left_up)
        self.Bind(wx.EVT_MOTION, self.on_mouse_motion)
        self.Bind(wx.EVT_LEAVE_WINDOW, self.on_mouse_leave)
        
        # 窗口事件
        self.Bind(wx.EVT_SIZE, self.on_size)
        self.Bind(wx.EVT_MOVE, self.on_move)
        
        # 父窗口事件
        if self._parent:
            self._parent.Bind(wx.EVT_SIZE, self.on_parent_resize)
            self._parent.Bind(wx.EVT_MOVE, self.on_parent_move)
            self._parent.Bind(wx.EVT_SHOW, self.on_parent_show)
            self._parent.Bind(wx.EVT_CLOSE, self.on_parent_close)

    def update_preview_image(self):
        """更新预览图片"""
        if not self._parent:
            self.Hide()
            return
        if not self.isLoaded:
            parent_title = self._parent.GetTitle()
            image_path = self.title_to_image.get(parent_title)
            
            if image_path and os.path.exists(image_path):
                try:
                    # 加载图片
                    image = wx.Image(image_path, wx.BITMAP_TYPE_ANY)
                    if image.IsOk():
                        # 缩放图片到合适大小
                        size = self.GetClientSize()
                        if size.height > 0:
                            # 保持宽高比缩放
                            img_height = size.height - 1
                            img_width = int(img_height * self.ASPECT_RATIO)
                            image = image.Scale(img_width, img_height, wx.IMAGE_QUALITY_HIGH)
                            
                            # 设置图片
                            bitmap = wx.Bitmap(image)
                            self.image_ctrl.SetBitmap(bitmap)
                            self.image_ctrl.Show()
                            
                            # 更新面板
                            self.panel.Layout()
                            self.show()
                        else:
                            self.Hide()
                    else:
                        self.Hide()
                    self.isLoaded = True
                except Exception as e:
                    print(f"加载图片失败: {e}")
                    self.Hide()
            else:
                self.Hide()
            
    def set_relative_position(self):
        """设置相对位置"""
        if not self._parent:
            return
            
        if self.displayLocation == "left":
            self._offset = wx.Point(-self.GetSize().width, 0)
        elif self.displayLocation == "right":
            self._offset = wx.Point(self._parent.GetSize().width, 0)
            
    def update_position(self):
        """更新窗口位置"""
        if not self._parent or not self._parent.IsShown():
            self.Hide()
            return
            
        # 获取父窗口信息
        parent_size = self._parent.GetSize()
        parent_pos = self._parent.GetScreenPosition()
        
        # 计算新大小
        new_height = parent_size.height
        new_width = int(new_height * self.ASPECT_RATIO)
        new_width = max(new_width, self.MIN_WIDTH)
        
        # 设置窗口大小
        self.SetSize(new_width, new_height)
        
        # 更新相对位置
        self.set_relative_position()
        
        # 计算新位置
        if self.displayLocation == "left":
            new_pos = wx.Point(parent_pos.x + self._offset.x, parent_pos.y)
        else:  # right
            new_pos = wx.Point(parent_pos.x + self._offset.x, parent_pos.y)
            
        # 移动窗口
        self.Move(new_pos)
        
        # 更新图片
        wx.CallAfter(self.update_preview_image)
        
    def on_mouse_left_down(self, event):
        """鼠标左键按下事件"""
        pos = event.GetPosition()
        width = self.GetSize().width
        
        if self.displayLocation == "left":
            if pos.x < self.RESIZE_MARGIN:
                self._is_resizing = True
                self._resize_start_x = event.GetX()
                self._original_rect = self.GetRect()
                self.SetCursor(wx.Cursor(wx.CURSOR_SIZEWE))
        elif self.displayLocation == "right":
            if width - pos.x < self.RESIZE_MARGIN:
                self._is_resizing = True
                self._resize_start_x = event.GetX()
                self._original_width = width
                self.SetCursor(wx.Cursor(wx.CURSOR_SIZEWE))
                
        event.Skip()
        
    def on_mouse_left_up(self, event):
        """鼠标左键释放事件"""
        if self._is_resizing:
            self._is_resizing = False
            self.SetCursor(wx.Cursor(wx.CURSOR_ARROW))
        event.Skip()
        
    def on_mouse_motion(self, event):
        """鼠标移动事件"""
        if self._is_resizing:
            pos = event.GetPosition()
            if self.displayLocation == "left" and self._original_rect:
                delta_x = pos.x - self._resize_start_x
                new_x = self._original_rect.x + delta_x
                new_width = self._original_rect.width - delta_x
                if new_width >= self.MIN_WIDTH:
                    self.SetDimensions(new_x, self._original_rect.y, 
                                      new_width, self._original_rect.height)
            elif self.displayLocation == "right":
                delta_x = pos.x - self._resize_start_x
                new_width = self._original_width + delta_x
                if new_width >= self.MIN_WIDTH:
                    self.SetSize(new_width, self.GetSize().height)
        else:
            # 更新光标
            self.update_resize_cursor(event.GetPosition())
        event.Skip()
        
    def on_mouse_leave(self, event):
        """鼠标离开窗口事件"""
        if not self._is_resizing:
            self.SetCursor(wx.Cursor(wx.CURSOR_ARROW))
        event.Skip()
        
    def update_resize_cursor(self, pos):
        """更新调整大小的光标"""
        width = self.GetSize().width
        
        if self.displayLocation == "left":
            if pos.x < self.RESIZE_MARGIN:
                self.SetCursor(wx.Cursor(wx.CURSOR_SIZEWE))
            else:
                self.SetCursor(wx.Cursor(wx.CURSOR_ARROW))
        elif self.displayLocation == "right":
            if width - pos.x < self.RESIZE_MARGIN:
                self.SetCursor(wx.Cursor(wx.CURSOR_SIZEWE))
            else:
                self.SetCursor(wx.Cursor(wx.CURSOR_ARROW))
                
    def on_size(self, event):
        """窗口大小改变事件"""
        self.update_preview_image()
        event.Skip()
        
    def on_move(self, event):
        """窗口移动事件"""
        event.Skip()
        
    def on_parent_resize(self, event):
        """父窗口大小改变事件"""
        self.update_position()
        event.Skip()
        
    def on_parent_move(self, event):
        """父窗口移动事件"""
        self.update_position()
        event.Skip()
        
    def on_parent_size(self, event):
        """父窗口大小改变事件"""
        self.update_position()
        event.Skip()
        
    def on_parent_show(self, event):
        """父窗口显示事件"""
        if self._parent.IsShown():
            self.show()
        else:
            self.Hide()
        event.Skip()
        
    def on_parent_close(self, event):
        """父窗口关闭事件"""
        self.Close()
        event.Skip()

    def on_close_preview(self, event):
        """接收关闭预览事件"""
        self.Close()
        
    def show(self):
        """显示窗口"""
        if self._parent and self._parent.IsShown():
            self.update_position()
            super().Show()
            
    def Show(self, show=True):
        """重写Show方法"""
        if show:
            self.show()
        else:
            super().Hide()
            
    def Close(self):
        """关闭窗口"""
        if self._parent:
            try:
                self._parent.Unbind(wx.EVT_SIZE, handler=self.on_parent_resize)
                self._parent.Unbind(wx.EVT_MOVE, handler=self.on_parent_move)
            except:
                pass
        self.Hide()
        self.Destroy()


# 测试代码
if __name__ == "__main__":
    app = wx.App()
    
    # 创建测试父窗口
    parent_frame = wx.Frame(None, title="网格设置", size=(400, 300))
    
    # 创建预览窗口
    preview = PreviewLabel(parent_frame)
    preview.displayLocation = "right"  # 或 "left"
    
    def on_parent_close(event):
        preview.Close()
        event.Skip()
        
    parent_frame.Bind(wx.EVT_CLOSE, on_parent_close)
    
    # 显示窗口
    parent_frame.Show()
    preview.show()
    
    app.MainLoop()