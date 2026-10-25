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

def pyncti_sketch_ShowCons(NCTI, doc, sketch=None, show_mode=0, cons_objects=None):
    if sketch is None or not hasattr(sketch, "ShowCons"):
        print("pyncti_sketch_ShowCons: missing active sketch or ShowCons")
        return None

    if cons_objects is not None:
        result = sketch.ShowCons(show_mode, cons_objects)
    else:
        result = sketch.ShowCons(show_mode)

    print(f"pyncti_sketch_ShowCons: show_mode={show_mode}, result={result}, type={type(result)}")
    doc.Update()
    return result
