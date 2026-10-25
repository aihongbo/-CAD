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
def pyncti_sketch_add_arc(NCTI,doc,sketch=None,start_point=None,end_point=None,arc_point=None,
                          radius=None,start_angle=None,end_angle=None,center_point=None):
    if sketch is None or not hasattr(sketch, "AddArc"):
        print("pyncti_sketch_add_arc: missing active sketch")
        return 0

    if start_point and end_point and arc_point:
        arc = sketch.AddArc(start_point, end_point, arc_point)
        print(f"pyncti_sketch_add_arc: arc={arc}, type={type(arc)}")
        doc.Update()
        return arc

    if radius is not None and start_angle is not None and end_angle is not None and center_point:
        arc = sketch.AddArc(radius, start_angle, end_angle, center_point)
        print(f"pyncti_sketch_add_arc: arc={arc}, type={type(arc)}")
        doc.Update()
        return arc

    print("pyncti_sketch_add_arc: missing arc parameters")
    return 0
