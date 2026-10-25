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

def pyncti_sketch_AddConsCoincide(NCTI, doc, sketch, value1=None, object1=None, value2=None, object2=None):
    if sketch is None or not hasattr(sketch, "AddConsCoincide") or object1 is None:
        return None

    if object2 is None:
        cons_result = sketch.AddConsCoincide(value1, object1)
    else:
        cons_result = sketch.AddConsCoincide(value1, object1, value2, object2)

    print(f"pyncti_sketch_AddConsCoincide: result={cons_result}, type={type(cons_result)}")
    if hasattr(sketch, "RunSolve"):
        try:
            solve_result = sketch.RunSolve()
            print(f"pyncti_sketch_AddConsCoincide: solve_result={solve_result}, type={type(solve_result)}")
        except Exception as e:
            print(f"pyncti_sketch_AddConsCoincide: RunSolve failed: {e}")
    doc.Update()
    return cons_result
