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
def pyncti_split_face(NCTI,doc):
    doc.ResetCaseResult()
    sel  = NCTI.SelectionManager(doc)
    if len(sel.CellIDs) > 0 and len(sel.ObjectNames) > 0:
        if not hasattr(pyncti_split_face, "counter"):
            pyncti_split_face.counter = 0
        else:
            pyncti_split_face.counter += 1

        resnames = []
        cellsize = len(sel.CellIDs)
        for i in range(cellsize):
            idx = cellsize * pyncti_split_face.counter + i
            resnames.append(f"sub_face_{idx}")

        doc.RunCommand("cmd_ncti_split_faces", sel.ObjectNames[0], sel.CellIDs, resnames)