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
# 在有网格的状态下选中节点，对该节点添加固定约束
def pyncti_mesh_add_spc(NCTI,doc):
    doc.ResetCaseResult()
    sel = NCTI.SelectionManager(doc)
    res  = doc.ReturnDialogData(-1, "单点约束", 
                                     "约束名称","constraint", 
                                     "平移XYZ","1,2,3",
                                     "平移自由度", "0,0,0",
                                     "旋转XYZ","4,5,6",
                                     "旋转自由度","0,0,0",
                                     "说明","平移方向X、Y、Z分别代表1，2，3",
                                     "","旋转方向X、Y、Z分别代表4，5，6",
                                     "","每个X、Y、Z对应自由度值，0表示固定")
    if len(res) > 0:
        constName = res[0]
        pan = res[1]
        freedomPan = res[2]
        rot = res[3]
        freedomRot = res[4]
        xyz = pan+rot
        free = freedomPan+freedomRot
        intXYZ = list(map(int, xyz.split(',')))
        intFreedom = list(map(int,free.split(',')))
        doc.RunCommand("cmd_ncti_mesh_add_spc", constName, sel.ObjectNames[0], sel.CellIDs, intXYZ, intFreedom)