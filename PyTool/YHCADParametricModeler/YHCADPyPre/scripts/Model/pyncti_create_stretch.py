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


def pyncti_create_stretch(NCTI, doc, yh_doc=None, sketch=None, distance=None):
    """创建拉伸特征；不传参数时启动底层交互式拉伸工具。"""
    if yh_doc is None:
        print("pyncti_create_stretch: miss yh_doc")
        return 0
    if not hasattr(yh_doc, "CreateStretch"):
        print("pyncti_create_stretch: miss python interface yh_doc.CreateStretch")
        return 0

    try:
        if distance is not None and sketch is not None:
            result = yh_doc.CreateStretch(float(distance), sketch)
        elif distance is not None:
            result = yh_doc.CreateStretch(float(distance))
        else:
            result = yh_doc.CreateStretch()
    except Exception as e:
        print(f"pyncti_create_stretch: CreateStretch failed: {e}")
        return None

    print(f"pyncti_create_stretch: result={result}, type={type(result)}")
    doc.Update()
    return result
