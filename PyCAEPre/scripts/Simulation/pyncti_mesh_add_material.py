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
# 选中非结构化网络， 根据设置的弹性模量、剪切模量、泊松比、密度和热膨胀参数设置对应的材料属性。
def pyncti_mesh_add_material(NCTI,doc):
    doc.ResetCaseResult()
    sel = NCTI.SelectionManager(doc)
    if len(sel.ObjectNames) > 0: 
        elasticModulus = 210000.0
        shearModulus  = 0.0
        PoissonRatio = 0.3
        density = 7.89e-09
        thermalExpansion = 0.0
        res  = doc.ReturnDialogData(-1, "添加材料属性参数", '弹性模量', elasticModulus, '剪切模量', shearModulus, '泊松比', PoissonRatio, '密度', density, '热膨胀', thermalExpansion)
        if len(res) > 0:
            doc.RunCommand("cmd_ncti_mesh_add_mat", "m_mat" ,sel.ObjectNames[0], res[0], res[1], res[2], res[3], res[4])
        else:
            print('用户取消了操作')
    else:
        print("没有选择数据")