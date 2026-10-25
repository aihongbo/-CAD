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
# 选中单元面，根据设置的强度设置压力，强度为正值表示压力是由内向外的，强度为负值则是从外向内。
def pyncti_mesh_add_pressure(NCTI,doc):
    doc.ResetCaseResult()
    sel = NCTI.SelectionManager(doc)
    if len(sel.CellIDs) > 0: 
        strength = 2000
        res  = doc.ReturnDialogData(-1, "添加压力参数", '强度', strength)
        if len(res) > 0:
            doc.RunCommand("cmd_ncti_mesh_add_pressure", "Pressure", sel.ObjectNames[0], sel.CellIDs, res[0])
        else:
            print('Cancle')
    else:
        print("没有选择数据")