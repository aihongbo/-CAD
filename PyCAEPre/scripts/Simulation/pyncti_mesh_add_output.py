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
#输出
def pyncti_mesh_add_output(NCTI,doc):
    doc.ResetCaseResult()
    field_output = 1
    node_vars = ["U", "UR", "UT", "V", "VR", "VT"]
    element_vars =  ["E", "S"]
    output_options = {}
    node_options = {}
    element_options = {"directions": "YES"}
    #param2:输出的名称
    #param3:输出类型，0-历史变量输出，1-场变量输出
    #param4:节点变量输出数组
    #param5:单元变量输出数组
    #param6:输出设置，可选
    #param7:节点输出设置，可选
    #param8:单元输出设置，可选
    doc.RunCommand("cmd_ncti_mesh_add_output", "field", field_output, node_vars, element_vars, output_options, node_options, element_options)
