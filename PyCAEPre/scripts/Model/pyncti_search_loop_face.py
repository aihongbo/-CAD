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
def pyncti_search_loop_face(NCTI,doc):
    sel = NCTI.SelectionManager(doc)
    if len(sel.CellIDs) > 0 and len(sel.ObjectNames) > 0:
        name = sel.ObjectNames[0]
        loops = doc.SearchLoopFace(sel.ObjectNames[0], sel.CellIDs[0])
        sel.CellIDs = loops
        sel.ObjectNames = [str(name)] * (len(sel.CellIDs))
        sel.SetSelected()