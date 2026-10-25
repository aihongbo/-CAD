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


def pyncti_fillet(NCTI, doc, yh_doc=None, radius=None):
    """创建圆角特征。"""
    if radius is None:
        print("pyncti_fillet: missing radius")
        return 0
    target = yh_doc if yh_doc is not None and hasattr(yh_doc, "FTFillet") else doc
    if not hasattr(target, "FTFillet"):
        print("pyncti_fillet: missing FTFillet interface")
        return 0

    result = target.FTFillet(float(radius))
    if hasattr(doc, "Update"):
        doc.Update()
    return result
