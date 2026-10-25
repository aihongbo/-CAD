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

#创建模态分析步
def pyncti_mesh_create_frequency_step(NCTI,doc):
    doc.ResetCaseResult()
    options = {"eigensolver":"Lanczos", "acoustic_coupling": "projection", "normalization": "mass"}
    #重载1：按阶提取
    #param2:分析步名称
    #param3:边界条件名称数组
    #param4:变量输出名称数组
    #param5:频率取值方式，0-按阶提取，1-按范围提取
    #param6:模态的阶数
    #param7:频率输出设置,省略则为默认值
    doc.RunCommand("cmd_ncti_mesh_create_frequency_step", "Step_1",  ["cons"], ["field"], 0, 25,options)