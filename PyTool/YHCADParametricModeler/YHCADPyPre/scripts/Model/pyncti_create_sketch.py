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
def pyncti_create_sketch(NCTI, doc, YH=None, yh_doc=None):
    if YH and hasattr(YH, "SketchWorkPlane"):
        sketch = YH.SketchWorkPlane(doc)
        print("pyncti_create_sketch: YH.SketchWorkPlane 返回 {}".format(sketch), flush=True)
    elif yh_doc and hasattr(yh_doc, "CreatSketch"):
        sketch = yh_doc.CreatSketch()
        print("pyncti_create_sketch: yh_doc.CreatSketch 返回 {}".format(sketch), flush=True)
    else:
        return 0

    if hasattr(sketch, "Open"):
        try:
            open_result = sketch.Open()
            print("pyncti_create_sketch: Open 返回 {}".format(open_result), flush=True)
        except Exception as error:
            print("pyncti_create_sketch: Open 失败 {}".format(error), flush=True)

    doc.Update()
    return sketch
