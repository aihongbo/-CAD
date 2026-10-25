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

def pyncti_sketch_add_ellipseArc(NCTI,doc,sketch=None,center_point=None,major_axis=None,minor_axis=None,start_angle=None,end_angle=None,):
    if sketch and hasattr(sketch, "AddEllipseArc"):
        ellipse_arc = sketch.AddEllipseArc(
            center_point,
            major_axis,
            minor_axis,
            start_angle,
            end_angle,
        )
        doc.Update()
        return ellipse_arc
    return 0
