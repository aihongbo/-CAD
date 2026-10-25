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
def pyncti_sketch_add_centerRect(NCTI, doc, sketch=None, center_point=None, rect_length=None, rect_width=None):
    if sketch and hasattr(sketch, "AddCenterRect") and center_point is not None and rect_length is not None and rect_width is not None:
        center_rect = sketch.AddCenterRect(center_point, rect_length, rect_width)
        print(f"pyncti_sketch_add_centerRect: center_rect={center_rect}, type={type(center_rect)}")
        doc.Update()
        return center_rect

    print("pyncti_sketch_add_centerRect: missing active sketch or parameters")
    return 0
