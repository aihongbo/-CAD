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

def pyncti_sketch_AddConsParallelSize(NCTI, doc, sketch=None, size=None, object1=None, object2=None):
    if sketch is None or not hasattr(sketch, "AddConsParallelSize") or size is None or object1 is None or object2 is None:
        print("pyncti_sketch_AddConsParallelSize: missing active sketch or AddConsParallelSize")
        return None

    result = sketch.AddConsParallelSize(size, object1, object2)
    print(f"pyncti_sketch_AddConsParallelSize: result={result}, type={type(result)}")

    if result and hasattr(sketch, "RunSolve"):
        try:
            solve_result = sketch.RunSolve()
            print(f"pyncti_sketch_AddConsParallelSize: solve_result={solve_result}, type={type(solve_result)}")
        except Exception as e:
            print(f"pyncti_sketch_AddConsParallelSize: RunSolve failed: {e}")

    try:
        doc.Update()
    except Exception as e:
        print(f"pyncti_sketch_AddConsParallelSize: doc.Update failed: {e}")
    return result
