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
def pyncti_find_holes(NCTI,doc):
    doc.ResetCaseResult()
    res = doc.ReturnDialogData(-1, "查找孔", "最小直径", 0, "最大直径", 10)
    if len(res) > 0:
        minD = res[0]
        maxD = res[1]
        sel = NCTI.SelectionManager(doc)
        holes = doc.FindHoles(sel.ObjectNames,  minD, maxD)
        sel.ClearSelected()
        if holes != None:
            count = 0
            objNames = []
            cellIDs = []
            for key, value in holes.items():
                for ids in value:
                    count += 1
                    for id in ids:
                        objNames.append(key)
                        cellIDs.append(id)
            sel.ObjectNames = objNames
            sel.CellIDs = cellIDs
            print(f"共查找到{count}个孔洞")
            sel.SetSelected()
            doc.ShowFeaturesDialog(3, holes)