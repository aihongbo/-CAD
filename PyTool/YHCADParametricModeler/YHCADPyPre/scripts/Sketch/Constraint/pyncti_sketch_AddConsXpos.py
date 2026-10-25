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

def pyncti_sketch_AddConsXpos(NCTI, doc, sketch=None, value1=None, object1=None, value2=None, object2=None):
    if sketch is not None and hasattr(sketch, "AddConsXpos"):
        if object1 is not None and object2 is None:
            result = sketch.AddConsXpos(value1, object1)
        elif object1 is not None and object2 is not None:
            result = sketch.AddConsXpos(value1, object1, value2, object2)
        else:
            result = sketch.AddConsXpos()
    else:
        print("pyncti_sketch_AddConsXpos: missing active sketch or AddConsXpos")
        return None
    print(f"pyncti_sketch_AddConsXpos: result={result}, type={type(result)}")
    doc.Update()
    return result
