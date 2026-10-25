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
# 布尔运算
def pyncti_boolean(NCTI,doc):
    doc.ResetCaseResult()
    res  = doc.ReturnDialogData(-1, "布尔", "选择方式：", ["并集", "差集", "交集"])
    sel = NCTI.SelectionManager(doc)
    if len(res) > 0 and len(sel.ObjectNames) > 1:
        size = len(sel.ObjectNames)
        if res[0][0] == "并集":
            doc.RunCommand("cmd_ncti_boolean_unit", "", sel.ObjectNames[size - 2], sel.ObjectNames[size - 1])
        elif res[0][0] == "交集":
            doc.RunCommand("cmd_ncti_boolean_common", "", sel.ObjectNames[size - 2], sel.ObjectNames[size - 1])
        elif res[0][0] == "差集":
            doc.RunCommand("cmd_ncti_boolean_cut", sel.ObjectNames[size - 2], sel.ObjectNames[size - 1])
    else:
        print("请选择两个几何对象进行布尔交集运算")