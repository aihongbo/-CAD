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
# 选中整个非结构化网络，根据设置的方向和强度设置重力
def pyncti_mesh_add_gravity(NCTI,doc):
    doc.ResetCaseResult()
    sel = NCTI.SelectionManager(doc)
    if len(sel.ObjectNames) > 0: 
        vec = NCTI.Vector(0, 0, -1)
        strength = 45
        res  = doc.ReturnDialogData(-1, "添加重力参数", '方向',vec, '强度', strength)
        if len(res) > 0:
            doc.RunCommand("cmd_ncti_mesh_add_gravity", "graviry", sel.ObjectNames[0], res[0], res[1])
        else:
            print('Cancle')
    else:
        print("没有选择数据")