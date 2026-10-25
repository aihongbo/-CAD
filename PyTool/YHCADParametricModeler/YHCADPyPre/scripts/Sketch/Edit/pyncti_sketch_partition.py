#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Copyright (c) 2025 粤港澳大湾区（广东）国创中心
YHCADPyPre is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details.
"""

def pyncti_sketch_partition(NCTI, doc, sketch, point1, point2=None):
    if sketch is None or not hasattr(sketch, "Partition") or point1 is None:
        return None

    if point2 is not None:
        partition_result = sketch.Partition(point1, point2)
    else:
        partition_result = sketch.Partition(point1)

    print(f"pyncti_sketch_partition: result={partition_result}, type={type(partition_result)}")
    doc.Update()
    return partition_result
