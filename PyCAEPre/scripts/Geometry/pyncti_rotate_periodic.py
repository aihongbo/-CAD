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
def pyncti_rotate_periodic(NCTI,doc):
    doc.ResetCaseResult()
    pt = NCTI.Point(0, 0, 0)
    vec = NCTI.Vector(0, 0, 1)
    res  = doc.ReturnDialogData(-1, "旋转阵列", "点：", pt, "向量：", vec, "新增数量：", "2")
    sel  = NCTI.SelectionManager(doc)
    if len(res) == 3 and len(sel.ObjectNames) > 0:
        if not hasattr(pyncti_rotate_periodic, "counter"):
            pyncti_rotate_periodic.counter = 0
        count = int(res[2])
        for obj in sel.ObjectNames:
            for i in range(count):
                angle = (360 / (count + 1)) * (i + 1)
                pyncti_rotate_periodic.counter += 1
                newname = f"rotateperiodic_obj_{pyncti_rotate_periodic.counter}"
                doc.RunCommand("cmd_ncti_copy_body", newname, obj)
                doc.RunCommand("cmd_ncti_rotate_body", newname, res[0], res[1], angle)