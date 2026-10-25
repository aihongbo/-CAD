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
def pyncti_geo_periodic(NCTI,doc):
    doc.ResetCaseResult()
    vec = NCTI.Vector(1, 0, 0)
    res  = doc.ReturnDialogData(-1, "直线阵列","方向：", vec, "偏移距离：", "10", "新增数量：", "1")
    sel  = NCTI.SelectionManager(doc)
    if len(res) == 3 and len(sel.ObjectNames) > 0:
        if not hasattr(pyncti_geo_periodic, "counter"):
            pyncti_geo_periodic.counter = 0
        distance = float(res[1])
        count = int(res[2])
        for obj in sel.ObjectNames:
            for i in range(count):
                pan_x = vec.X * (i + 1) * distance
                pan_y = vec.Y * (i + 1) * distance
                pan_z = vec.Z * (i + 1) * distance
                panvec =  NCTI.Vector(pan_x, pan_y, pan_z)
                pyncti_geo_periodic.counter += 1
                newname = f"geoperiodic_obj_{pyncti_geo_periodic.counter}"
                doc.RunCommand("cmd_ncti_copy_body", newname, obj)
                doc.RunCommand("cmd_ncti_pan", newname, panvec)