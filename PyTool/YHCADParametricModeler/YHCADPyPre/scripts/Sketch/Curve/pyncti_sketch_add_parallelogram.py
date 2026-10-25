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
def pyncti_sketch_add_parallelogram(NCTI, doc, sketch=None, point1=None, point2=None, point3=None):
    if sketch and hasattr(sketch, "AddParallelogram") and point1 is not None and point2 is not None and point3 is not None:
        parallelogram = sketch.AddParallelogram(point1, point2, point3)
        print(f"pyncti_sketch_add_parallelogram: parallelogram={parallelogram}, type={type(parallelogram)}")
        doc.Update()
        return parallelogram

    print("pyncti_sketch_add_parallelogram: missing active sketch or points")
    return 0
