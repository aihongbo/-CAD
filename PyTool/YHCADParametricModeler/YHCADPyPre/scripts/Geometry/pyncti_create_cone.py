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


def pyncti_create_cone(NCTI, doc, YH=None, yh_doc=None, point=None, normal=None, bottom_diameter=None, top_diameter=None, height=None):
    """创建圆锥体。"""
    if yh_doc is None:
        print("pyncti_create_cone: miss yh_doc")
        return 0
    if point is None or normal is None or bottom_diameter is None or top_diameter is None or height is None:
        print("pyncti_create_cone: missing point, normal or size")
        return 0

    ft_manager = None
    if YH is not None and hasattr(YH, "FTManager"):
        try:
            ft_manager = YH.FTManager(doc)
        except Exception:
            ft_manager = None

    if ft_manager is not None:
        result = yh_doc.CreateCone(point, normal, float(bottom_diameter), float(top_diameter), float(height), ft_manager)
    else:
        result = yh_doc.CreateCone(point, normal, float(bottom_diameter), float(top_diameter), float(height))
    doc.Update()
    return result
