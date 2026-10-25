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
def pyncti_sketch_add_circle(NCTI, doc, sketch=None, center=None, radius=None):
    if sketch and hasattr(sketch, "AddCircle") and center and radius is not None:
        circle = sketch.AddCircle(center, radius)
        print(f"pyncti_sketch_add_circle: circle={circle}, type={type(circle)}")
        doc.Update()
        return circle
    
    print("pyncti_sketch_add_circle: missing active sketch or points")
    return 0
