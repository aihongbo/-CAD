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
from wx.lib.agw import ribbon as RB
from wx.svg import SVGimage          # 仅 4.1+ 可用
import os
def svg2bmp(svg_path, size=(24, 24)):
    svg = SVGimage.CreateFromFile(svg_path)
    if svg is None:
        print(f"错误: 无法加载 SVG 文件 {svg_path}")
        return None
    # 返回 wx.Bitmap，无需任何 DC
    return svg.ConvertToScaledBitmap(wx.Size(*size))
    return bp