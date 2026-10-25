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

#导出inp文件
def pyncti_export_inp_file(NCTI,doc):
    doc.ResetCaseResult()
    filename = "D:\\ncti_box.inp"
    sel = NCTI.SelectionManager(doc)
    #param2:inp文件路径
    #param3:网格名称数组
    doc.RunCommand("cmd_ncti_mesh_export_inp_file",  filename, sel.ObjectNames)