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


def _run_boolean_command(doc, yh_doc, method_name):
    """启动底层布尔交互命令。"""
    if yh_doc is None or not hasattr(yh_doc, method_name):
        print(f"pyncti_boolean: missing {method_name} interface")
        return 0

    result = getattr(yh_doc, method_name)()
    if hasattr(doc, "Update"):
        doc.Update()
    return result


def pyncti_boolean_union(NCTI, doc, yh_doc=None, object_names=None):
    """布尔并集。"""
    return _run_boolean_command(doc, yh_doc, "FTBooleanUnion")


def pyncti_boolean_subtraction(NCTI, doc, yh_doc=None, target_names=None, tool_names=None):
    """布尔差集。"""
    return _run_boolean_command(doc, yh_doc, "FTBooleanSubtraction")


def pyncti_boolean_intersection(NCTI, doc, yh_doc=None, target_names=None, tool_names=None):
    """布尔交集。"""
    return _run_boolean_command(doc, yh_doc, "FTBooleanIntersection")
