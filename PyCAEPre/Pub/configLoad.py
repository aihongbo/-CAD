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
import json

def init_NCTI_Config():
    jsonData = get_systemConfigJson()
    dllpath = jsonData["dllPath"]
    addKernelPath = jsonData["addKernelPath"]
    loadDLLs = jsonData["loadDLL"]
    #add dll path
    if False == os.path.isabs(dllpath):
        current_dir = os.path.dirname(os.path.abspath(__file__))
        dllpath =  current_dir+"/"+dllpath
    try:
        sys.path.insert(0, dllpath)
        for ker in addKernelPath:
            api_path = dllpath + "/" + ker
            if os.path.exists(api_path):
                os.add_dll_directory(api_path)
            else:
                print(f"Warning: DLL not found: {addDllPath}")
        #add dll
        for loadDll in loadDLLs:
            addDllPath = dllpath + "/" + loadDll
            addDllPath = addDllPath.replace('\\','/')
            if os.path.exists(addDllPath):
                ctypes.CDLL(addDllPath)
            else:
                print(f"Warning: DLL not found: {addDllPath}")
        #init ncti_python
        NCTI = importlib.import_module("ncti_python")
        if 1 != NCTI.Init(dllpath):
            return None
        return NCTI
    except Exception as e:
        print("System path error or loading dll failure!", e)
        return None

def get_systemConfigJson():
    try:
        current_dir = os.path.dirname(os.path.abspath(__file__))
        jsonfile = current_dir + '/' + "systemConfig.json"
        with open(jsonfile, 'r') as file:
            data = json.load(file)
            return data
    except FileNotFoundError:
        print("文件未找到")
        return ""
    except json.JSONDecodeError:
        print("JSON 文件格式错误")
        return ""
    
global_scope = {}
NCTI = init_NCTI_Config()
if None != NCTI:
    global_scope["NCTI"] = NCTI
    global_scope["doc"] = NCTI.Document()
