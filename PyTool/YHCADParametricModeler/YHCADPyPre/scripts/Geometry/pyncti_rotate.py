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


def pyncti_rotate(NCTI, doc, yh_doc=None, point=None, vector=None, angle=None):
    """启动旋转特征的底层交互命令。"""
    if yh_doc is None or not hasattr(yh_doc, "CreateRotation"):
        print("pyncti_rotate: missing CreateRotation interface")
        return 0

    result = yh_doc.CreateRotation()
    if hasattr(doc, "Update"):
        doc.Update()
    return result
