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

#ifndef DCL_NCTI_QT_PUBFUN_H
#define DCL_NCTI_QT_PUBFUN_H

#ifndef DECL_NCTI_QT_PUBFUN
#ifdef NCTI_DLL

#ifdef EXPORT_NCTI_QT_PUBFUN
#ifdef _MSC_VER
#define DECL_NCTI_QT_PUBFUN __declspec(dllexport)
#else
#define DECL_NCTI_QT_PUBFUN __attribute__((visibility("default")))
#endif 
# else 
#ifdef _MSC_VER
#define DECL_NCTI_QT_PUBFUN __declspec(dllimport)
#else
#define DECL_NCTI_QT_PUBFUN __attribute__((visibility("default")))
#endif 
//#  ifdef _MSC_VER
//#    define NCTILIBNAME "ncti_base.lib"
//#    pragma comment(lib, NCTILIBNAME)
//#  else
//#    define NCTILIBNAME "libncti_base.so"
//#    pragma comment(lib, NCTILIBNAME)
//#endif  
# endif

#else
# define DECL_NCTI_QT_PUBFUN
#endif //!NCTI_DLL
#endif //!DECL_NCTI_QT_PUBFUN

/*
* @brief 类的内部类声明
*/
#ifndef NCTI_QT_PUBFUNC_DECLARE_PRIVATE
#define NCTI_QT_PUBFUNC_DECLARE_PRIVATE(classname)	\
	class PrivateData;							    \
	friend class classname::PrivateData;            \
	std::unique_ptr<PrivateData> d_ptr;
#endif

#ifndef NCTI_QT_PUBFUNC_DECLARE_PUBLIC
#define NCTI_QT_PUBFUNC_DECLARE_PUBLIC(classname)		 \
	friend class classname;								 \
	classname* q_ptr { nullptr };						 \
	PrivateData(const PrivateData&)            = delete; \
	PrivateData& operator=(const PrivateData&) = delete;
#endif

#endif //!DCL_NCTI_QT_PUBFUN_H 