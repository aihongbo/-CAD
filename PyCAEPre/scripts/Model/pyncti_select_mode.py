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
def pyncti_select_mode(NCTI,doc,mode,isSelected):
    if mode == 0:
        doc.SetSelBody(isSelected)
        if isSelected == False:
            sel = NCTI.SelectionManager(doc)
            sel.ClearSelected()
        else:
            doc.SetSelFace(True)
            doc.SetSelLine(True)
            doc.SetSelVertex(True)
    else:
        if isSelected == False:
            doc.SetSelBody(isSelected)
        if mode == 1:
            doc.SetSelFace(isSelected)
        if mode == 2:
            doc.SetSelLine(isSelected)
        if mode == 3:
            doc.SetSelVertex(isSelected)
    