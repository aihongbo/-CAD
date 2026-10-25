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
def pyncti_sketch_add_centerLine(NCTI, doc, sketch, start_point, end_point):
    if sketch and hasattr(sketch, "AddCenterLine") and start_point is not None and end_point is not None:
        center_line = sketch.AddCenterLine(start_point, end_point)
        print(f"pyncti_sketch_add_centerLine: center_line={center_line}, type={type(center_line)}")
        doc.Update()
        return center_line
    return None
