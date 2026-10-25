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


def pyncti_circular_array(NCTI, doc, yh_doc=None, point=None, vector=None, count=None, angle=None):
    """创建旋转阵列。"""
    if yh_doc is None or not hasattr(yh_doc, "CreateCircularArray"):
        print("pyncti_circular_array: missing CreateCircularArray interface")
        return 0

    if point is None and vector is None and count is None and angle is None:
        result = yh_doc.CreateCircularArray()
    elif point is None or vector is None or count is None or angle is None:
        print("pyncti_circular_array: missing point, vector, count or angle")
        return 0
    else:
        result = yh_doc.CreateCircularArray(point, vector, int(count), float(angle))

    if hasattr(doc, "Update"):
        doc.Update()
    return result
