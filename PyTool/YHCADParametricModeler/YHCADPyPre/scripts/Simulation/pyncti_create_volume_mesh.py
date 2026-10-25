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
# 给选中的实体按给定的网格尺寸和网格类型绘制体网格
def pyncti_create_volume_mesh(NCTI,doc):
    doc.ResetCaseResult()
    sel = NCTI.SelectionManager(doc)
    if len(sel.ObjectNames) > 0: 
        size = 1
        type = 0 #0:triangle,1:QuadDominant,2:FullQuad
        res  = doc.ReturnDialogData(-1, "请输入网格参数","网格尺寸", size,"网格类型", type)
        if len(res) > 0:
            name = sel.ObjectNames
            option = {"MeshSize":res[0],"MeshType":res[1]}
            doc.RunCommand("cmd_ncti_create_volume_mesh", name, option)
        else:
            print("取消")
    else:
        print("没有选择数据")