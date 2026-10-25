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
def pyncti_fillet(NCTI,doc):
    doc.ResetCaseResult()
    res  = doc.ReturnDialogData(-1, "圆角", "半径：", "0.5")
    sel  = NCTI.SelectionManager(doc)
    if len(res) > 0 and len(sel.ObjectNames) > 0:
        size = len(sel.CellIDs)
        radius = [float(res[0])] * size
        doc.RunCommand("cmd_ncti_fillet", sel.ObjectNames[0], radius, sel.CellIDs)