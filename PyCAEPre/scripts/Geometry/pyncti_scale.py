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
def pyncti_scale(NCTI,doc):
    doc.ResetCaseResult()
    pt = NCTI.Point(0, 0, 0)
    res  = doc.ReturnDialogData(-1, "缩放","点：", pt, "比例：", "1")
    sel  = NCTI.SelectionManager(doc)
    if len(res) == 2 and len(sel.ObjectNames) > 0:
        ratio = int(res[1])
        doc.RunCommand("cmd_ncti_scale", sel.ObjectNames, res[0], ratio)