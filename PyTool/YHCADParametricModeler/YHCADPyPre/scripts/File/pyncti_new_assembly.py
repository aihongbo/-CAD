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

def pyncti_new_assembly(NCTI,doc,hwnd):
    doc.ResetCaseResult()
    res  = doc.ReturnDialogData(-1, "创建装配文档","文档名称","装配")
    if len(res) > 0:
        doc.NewAssemble(res[0])
        view = NCTI.View(doc.ID)
        doc.SetCreateGeGeom(1)  # 不生成平台对象（不生成会快）
        view.CreateWindow(hwnd)
        view.SetWindowVis(True,doc.ID)
        doc.Zoom()
        return view