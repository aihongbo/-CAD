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

#ifndef _DCL_NCTI_UIOPTION_H
#define _DCL_NCTI_UIOPTION_H

/**
 * @brief UI选项模块导出宏定义
 * @details 根据编译环境和配置定义NCTI_UIOPTION宏，用于控制UI选项模块的导入/导出
 */

#ifndef NCTI_UIOPTION
#ifdef NCTI_DLL
#ifdef EXPORT_NCTI_UIOPTION
#ifdef _MSC_VER
/**
 * @brief Windows平台下的DLL导出定义
 */
#define NCTI_UIOPTION __declspec(dllexport)
#else
/**
 * @brief GCC平台下的符号可见性设置
 */
#define NCTI_UIOPTION __attribute__((visibility("default")))
#endif
#else
#ifdef _MSC_VER
/**
 * @brief Windows平台下的DLL导入定义
 */
#define NCTI_UIOPTION __declspec(dllimport)
#else
/**
 * @brief GCC平台下的符号可见性设置
 */
#define NCTI_UIOPTION __attribute__((visibility("default")))
#endif
#endif
#else
/**
 * @brief 非DLL模式下的空定义
 */
#define NCTI_UIOPTION
#endif //!NCTI_DLL
#endif //!NCTI_UIOPTION

#endif //!_DCL_NCTI_UIOPTION_H