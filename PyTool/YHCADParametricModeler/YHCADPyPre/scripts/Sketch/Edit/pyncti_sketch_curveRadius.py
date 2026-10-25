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

def pyncti_sketch_curveRadius(NCTI, doc, sketch, value1=None, line1=None, value2=None, line2=None):
    if sketch is None or not hasattr(sketch, "CurveRadius") or line1 is None or line2 is None:
        return None

    if value2 is None:
        radius_result = sketch.CurveRadius(value1, line1, line2)
    else:
        radius_result = sketch.CurveRadius(value1, line1, value2, line2)

    print(f"pyncti_sketch_curveRadius: result={radius_result}, type={type(radius_result)}")
    doc.Update()
    return radius_result
