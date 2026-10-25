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
def pyncti_find_fillets(NCTI,doc):
    doc.ResetCaseResult()
    filletTypes = ['全部', '凸圆角', '凹圆角']
    res = doc.ReturnDialogData(-1, "查找圆角", "最小半径", 5, "最大半径", 15, "圆角类型", ['全部', '凸圆角', '凹圆角'])
    if len(res) > 0:
        minRadius = res[0]
        maxRadius = res[1]
        filletType = filletTypes.index(res[2][0])
        sel = NCTI.SelectionManager(doc)
        fillets = doc.FindFillets(sel.ObjectNames,  minRadius, maxRadius, filletType)
        sel.ClearSelected()
        objNames = []
        cellIDs = []
        if fillets != None:
            for key, value in fillets.items():
                for id in value:
                    objNames.append(key)
                    cellIDs.append(id)
            sel.ObjectNames = objNames
            sel.CellIDs = cellIDs
            print(f"共查找到{len(cellIDs)}个倒圆角面")
            sel.SetSelected()
            doc.ShowFeaturesDialog(2, fillets)