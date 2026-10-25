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

def pyncti_sketch_curveTrimming(NCTI, doc, sketch, trim_point, trim_objects=None):
    if sketch and hasattr(sketch, "CurveTrimming") and trim_point is not None:
        if trim_objects:
            trim_result = sketch.CurveTrimming(trim_point, trim_objects)
        else:
            trim_result = sketch.CurveTrimming(trim_point)
        print(f"pyncti_sketch_curveTrimming: trim_result={trim_result}, type={type(trim_result)}")
        doc.Update()
        return trim_result
    return None
