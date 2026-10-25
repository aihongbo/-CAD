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
def pyncti_sketch_add_line(NCTI, doc, sketch=None, start_point=None, end_point=None):
    if sketch and hasattr(sketch, "AddLine") and start_point and end_point:
        line = sketch.AddLine(start_point, end_point)
        print(f"pyncti_sketch_add_line: line={line}, type={type(line)}")
        doc.Update()
        return line
    print("pyncti_sketch_add_line: missing active sketch or points")
    return 0
