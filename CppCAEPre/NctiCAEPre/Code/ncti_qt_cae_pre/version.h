/*
 * Copyright (c) 2025 粤港澳大湾区（广东）国创中心
 *
 * This file is a part of NctiCAEPre.
 *
 * NctiCAEPre is licensed under Mulan PSL v2.
 * You can use this software according to the terms and conditions of the Mulan PSL v2.
 * You may obtain a copy of Mulan PSL v2 at:
 *          http://license.coscl.org.cn/MulanPSL2
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
 * EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
 * MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
 * See the Mulan PSL v2 for more details.
 *
 */

#pragma once

#define _VERSIONTOSTRING(arg) #arg
#define VERSIONTOSTRING(arg)  _VERSIONTOSTRING(arg)

#define VERSION_MAJOR         1
#define VERSION_MINOR         0
#define VERSION_PATCH         0
#define VERSION_BUILD         1
#define VERSION_SOURCE        5150f2d
#define VERSION_PRERELEASE    alpha
#define VERSION_FULL          VERSION_MAJOR, VERSION_MINOR, VERSION_PATCH, VERSION_BUILD
#define STR_VERSION_FILE      VERSIONTOSTRING(VERSION_MAJOR.VERSION_MINOR.VERSION_PATCH.VERSION_BUILD)
#define STR_VERSION_PRODUCT   VERSIONTOSTRING(VERSION_MAJOR.VERSION_MINOR.VERSION_PATCH.VERSION_BUILD(VERSION_SOURCE))                                                                   
