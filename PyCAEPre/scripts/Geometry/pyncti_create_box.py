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
# 根据用户提供的长方体长、宽、高等参数创建一个长方体

def pyncti_create_box(NCTI,doc):
    doc.ResetCaseResult()
    length = 10.0
    width = 20.0
    height = 30.0
    pt = NCTI.Point(0, 0, 0)

    res = doc.ReturnDialogData(-1, "创建长方体参数", "长", length, "宽", width, "高", height, "顶点坐标", pt)
    if len(res) == 0 : 
        print("用户取消了操作")
    elif res[0] <= 0.0 or res[1] <= 0.0 or res[2] <= 0.0 :
        print("请输入合理的长方体的长、宽和高")
    else :
        length = res[0]
        width = res[1]
        height = res[2]
        pt = res[3]
        doc.RunCommand("cmd_ncti_create_box", "", pt, length, width, height)



    
    

            


