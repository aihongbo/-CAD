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
def pyncti_prism(NCTI,doc):
    doc.ResetCaseResult()
    vec = NCTI.Vector(1, 0, 0)
    res  = doc.ReturnDialogData(-1, "拉伸","方向：", vec, "大小：", "1")
    sel  = NCTI.SelectionManager(doc)
    if len(res) == 2 and len(sel.ObjectNames) > 0:
        length = float(res[1])
        vec.X = vec.X * length
        vec.Y = vec.Y * length
        vec.Z = vec.Z * length

        if not hasattr(pyncti_prism, "counter"):
            pyncti_prism.counter = 0
        else:
            pyncti_prism.counter += 1
        resname = f"prism_obj_{pyncti_prism.counter}"
        doc.RunCommand("cmd_ncti_prism", resname, sel.ObjectNames[0], vec)