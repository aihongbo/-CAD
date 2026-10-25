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
import sys
import ctypes
import importlib
import os

def init_NCTI_Config(dll_path):
    try:
        # 加载炎核开发引擎的建模内核、渲染引擎、Python接口
        sys.path.insert(0, dll_path)
        os.add_dll_directory(dll_path + '/OCC')  # occ_path
        ctypes.CDLL(dll_path + "/ncti_command.dll")
        ctypes.CDLL(dll_path + "/ncti_occ_plugin.dll")
        ctypes.CDLL(dll_path + "/ncti_doc_occ.dll")
        ctypes.CDLL(dll_path + "/ncti_render_vulkan.dll")
        ctypes.CDLL(dll_path + "/ncti_gmsh_plugin.dll")
        NCTI = importlib.import_module("ncti_python")
        if 1 != NCTI.Init(dll_path):
            return None
        return NCTI
    except:
        print("System path error or loading dll failure!")
        return None


# 1，确认炎核开发引擎的安装路径，请按需配置实际路径
# 以下是当前用户默认设置下安装的路径，一般情况下是可用的：
dll_path = os.path.join(os.path.expanduser('~'), 'AppData/Local/Programs/YHCppSDK-Community/SDK/bin/RelWithDebInfo')
# 以下是admin用户默认设置下安装的参考路径，请根据实际用户名确认该路径有效：
# dll_path = 'C:/Users/Admin/AppData/Local/Programs/YHCppSDK-Community/SDK/bin/RelWithDebInfo'
# 如果自行安装至如下所示的其它目录，请自行修改，并将目录分隔符号反斜杠"\"修改为正斜杠"/"：
# dll_path = 'C:/Program Files (x86)/YHCppSDK-Community/SDK/bin/RelWithDebInfo'
#if not os.path.exists(dll_path):
    # messagebox.showerror("安装路径检索错误",
    #                      "操作失败！请检查炎核开发引擎是否已正确安装、其安装路径与dll_path声明是否匹配。", icon='error')
    #sys.exit(1)

# 2，根据指定路径加载炎核开发引擎
# global global_scope
# if None == global_scope["NCTI"]:
#     sys.exit(1)
# doc = NCTI.Document()
# global_scope["NCTI"] = NCTI
# global_scope["doc"] = doc
if not os.path.exists(dll_path):
    # messagebox.showerror("安装路径检索错误",
    #                      "操作失败！请检查炎核开发引擎是否已正确安装、其安装路径与dll_path声明是否匹配。", icon='error')
    sys.exit(1)

global_scope = {}
NCTI = init_NCTI_Config(dll_path)
if None != NCTI:
    global_scope["NCTI"] = NCTI
    global_scope["doc"] = NCTI.Document()
else:
    sys.exit(1)