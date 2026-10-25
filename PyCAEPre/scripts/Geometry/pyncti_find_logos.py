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
def pyncti_find_logos(NCTI,doc):
    doc.ResetCaseResult()
    res = doc.ReturnDialogData(-1, "查找LOGO", "宽度", 150, "高度", 3, "最少面数量", 5)
    if len(res) > 0:
        width = res[0]
        height = res[1]
        faceNum = res[2]
        sel = NCTI.SelectionManager(doc)
        logos = doc.FindLogos(sel.ObjectNames,  width, height, faceNum)
        sel.ClearSelected()
        if logos != None:
            count = 0
            objNames = []
            cellIDs = []
            for key, value in logos.items():
                for ids in value:
                    count += 1
                    for id in ids:
                        objNames.append(key)
                        cellIDs.append(id)
            sel.ObjectNames = objNames
            sel.CellIDs = cellIDs
            print(f"共查找到{count}个LOGO")
            sel.SetSelected()
            doc.ShowFeaturesDialog(4, logos)