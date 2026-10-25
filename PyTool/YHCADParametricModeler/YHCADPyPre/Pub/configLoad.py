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
import sys
import ctypes
import importlib
import importlib.util
import os
import json

def load_yh_python_module(dllpath):
    major = sys.version_info.major
    minor = sys.version_info.minor
    module_path = os.path.join(dllpath, f"yh_python{major}{minor}.pyd")
    if not os.path.exists(module_path):
        print(f"Warning: YH python module not found: {module_path}")
        return None

    spec = importlib.util.spec_from_file_location("yh_python", module_path)
    if spec is None:
        print(f"Warning: cannot create YH python module spec: {module_path}")
        return None

    module = importlib.util.module_from_spec(spec)
    sys.modules["yh_python"] = module
    spec.loader.exec_module(module)
    return module

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
        dcubed_lic = os.path.join(dllpath, "dcubed.lic")
        if os.path.exists(dcubed_lic):
            os.environ["DCUBED"] = dllpath
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
        YH = load_yh_python_module(dllpath)
        return NCTI, YH
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
init_result = init_NCTI_Config()
if None != init_result:
    NCTI, YH = init_result
    doc = NCTI.Document()
    global_scope["NCTI"] = NCTI
    global_scope["doc"] = doc
    if None != YH:
        global_scope["YH"] = YH
        global_scope["yh_doc"] = YH.YHDocument(doc)
