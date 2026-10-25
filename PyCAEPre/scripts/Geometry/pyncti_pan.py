#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Copyright (c) 2025 粤港澳大湾区（广东）国创中心
PyCAEPre is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details.
"""
def pyncti_pan(NCTI,doc):
    doc.ResetCaseResult()
    vec = NCTI.Vector(1, 0, 0)
    res  = doc.ReturnDialogData(-1, "平移","向量：", vec, "距离：", "10")
    sel  = NCTI.SelectionManager(doc)
    if len(res) == 2 and len(sel.ObjectNames) > 0:
        distance = float(res[1])
        vec.X = vec.X * distance
        vec.Y = vec.Y * distance
        vec.Z = vec.Z * distance
        doc.RunCommand("cmd_ncti_pan", sel.ObjectNames, vec)