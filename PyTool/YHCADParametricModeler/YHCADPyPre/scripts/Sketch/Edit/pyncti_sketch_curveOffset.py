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

def pyncti_sketch_curveOffset(NCTI, doc, sketch, offset_objects=None, offset_distance=None, offset_mode=None):
    if sketch is None or not hasattr(sketch, "CurveOffset"):
        return None

    if offset_mode is not None:
        offset_result = sketch.CurveOffset(offset_mode)
        print(f"pyncti_sketch_curveOffset: offset_mode={offset_mode}, result={offset_result}, type={type(offset_result)}")
        doc.Update()
        return offset_result

    if offset_objects and offset_distance is not None:
        offset_result = sketch.CurveOffset(offset_objects, offset_distance)
        print(f"pyncti_sketch_curveOffset: objects={offset_objects}, distance={offset_distance}, result={offset_result}, type={type(offset_result)}")
        doc.Update()
        return offset_result

    return None
