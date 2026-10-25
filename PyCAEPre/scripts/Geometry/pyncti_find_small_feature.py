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
def pyncti_find_small_feature(NCTI,doc):
    doc.ResetCaseResult()
    sel = NCTI.SelectionManager(doc)
    if len(sel.ObjectNames) == 0:
        print(f"请先选择几何对象")
        return
    res  = doc.ReturnDialogData(-1, "查找小特征", "查找类型：", ["体", "面"], "阈值：", "0.05")
    if len(res) == 2:
        type = 0
        tolerance = float(res[1])
        if res[0][0] == "面":
            type = 1
        features = doc.FindSmallFeatures(sel.ObjectNames, type, tolerance)
        sel.ClearSelected()
        if  features != None:
            if type == 0:
                sel.ObjectNames = features
                print(f"共查找到{len(features)}个体特征")
            else:
                objNames = []
                cellIDs = []
                for key, value in features.items():
                    for id in value:
                        objNames.append(key)
                        cellIDs.append(id)
                sel.ObjectNames = objNames
                sel.CellIDs = cellIDs
                print(f"共查找到{len(cellIDs)}个面特征")
            sel.SetSelected()
            doc.ShowFeaturesDialog(type, features)