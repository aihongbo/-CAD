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

def pyncti_add_assembly(NCTI,doc):   
    doc.ResetCaseResult()
    res  = doc.ReturnDialogData(-1, "添加装配文档","对象名称","assemble", "显示名称", "装配")
    if len(res) > 0:
        doc.AddAssemble(res[0], res[1])
        doc.SetCreateGeGeom(1)  # 不生成平台对象（不生成会快）
        doc.Zoom()
