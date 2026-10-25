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
def pyncti_sketch_add_ellipse(NCTI, doc, sketch=None, center=None, vectorMajorAxis=None, vectorMinorAxis=None):
    if sketch and hasattr(sketch, "AddEllipse") and center is not None and vectorMajorAxis and vectorMinorAxis:
        ellipse = sketch.AddEllipse(center, vectorMajorAxis, vectorMinorAxis)
        print(f"pyncti_sketch_add_ellipse: ellipse={ellipse}, type={type(ellipse)}")
        doc.Update()
        return ellipse
    
    print("pyncti_sketch_add_ellipse: missing active sketch or points")
    return 0