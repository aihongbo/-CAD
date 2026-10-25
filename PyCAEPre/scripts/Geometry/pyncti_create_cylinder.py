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
# 根据用户提供的圆柱半径、高度等参数创建一个圆柱体
def pyncti_create_cylinder(NCTI,doc):
    doc.ResetCaseResult()
    r = 10.0
    h = 20.0
    angle = 360
    pt = NCTI.Point(0, 0, 0)
    n = NCTI.Vector(0, 0, 1)
    u = NCTI.Vector(1, 0, 0)

    res = doc.ReturnDialogData(-1, "创建圆柱体参数", "圆柱半径", r, "圆柱高度", h, "圆柱生成角度", angle, "圆柱底所在平面原点", pt, "圆柱底面所在平面法向", n, "圆柱底面所在平面u轴", u)
    if len(res) == 0 : 
        print("用户取消了操作")
    elif res[0] <= 0.0 or res[1] <= 0.0 or res[2] <= 0 or res[2] >360 :
        print("请输入合理的圆柱的半径、高度和生成角度")
    else :
        r = res[0]
        h = res[1]
        angle = res[2]
        pt = res[3]
        n = res[4]
        u = res[5]
        doc.RunCommand("cmd_ncti_create_cylinder", "", r, h, pt, n, u, angle)

            


