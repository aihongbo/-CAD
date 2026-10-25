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

#ifndef NCTIQTCAEPREAPI_H
#define NCTIQTCAEPREAPI_H

// 导出宏定义
#ifdef NCTI_CAE_PRE_BUILD_DLL
#ifdef EXPORT_NCTI_QT_CAE_PRE
#define NCTI_QT_CAE_PRE_API __declspec(dllexport)
#else
#define NCTI_QT_CAE_PRE_API __declspec(dllimport)
#endif
#else
#define NCTI_QT_CAE_PRE_API
#endif

class QWidget;
#include <QString>

#include "ncti_base.h"

namespace NCTI {

/**
* @struct RunArguments
* @brief Python脚本运行参数结构体
*/
struct RunArguments
{
    QString pyPath;                               ///<py脚本文件路径
    QString file;                                 ///<ncti文件路径
    EnumModelDoc doc    = EnumModelDoc::NCTI_GEOM_OCC; ///<指定几何内核，默认为OCC
    EnumGCSDoc dcmDoc   = EnumGCSDoc::NCTI_GCS_DCM;   ///<指定约束内核，默认为DCM
    EnumMeshDoc meshDoc = EnumMeshDoc::NCTI_MESH_GMSH; ///<指定网格内核，默认为GMSH
    bool isCreateNewDoc = false;                  ///<是否创建新文档，默认为false
    bool isCreateAssembly = false;                ///<是否创建装配体，默认为false
};

/**
 * @class NctiQtCaePre
 * @brief CAE前处理模块的API类
 * @details 提供创建主窗口、关闭主窗口和运行Python脚本等功能接口
 */
class NCTI_QT_CAE_PRE_API NctiQtCaePre
{
public:
    /**
     * @brief 创建CAE前处理主窗口
     * @param[in] i_Parent 父窗口指针
     * @return 创建成功返回主窗口指针，失败返回nullptr
     */
    static QWidget* CreateMainWindow(QWidget* i_Parent);

    /**
     * @brief 关闭CAE前处理主窗口
     * @param[in] i_MainWindow 需要关闭的主窗口指针
     */
    static void CloseMainWindow(QWidget* i_MainWindow);

    /**
     * @brief 运行Python脚本
     * @param[in] i_MainWindow 主窗口指针，脚本将在此窗口环境中运行
     * @param[in] i_Arg 运行脚本的参数配置
     * @return 脚本运行成功返回true，失败返回false
     */
    static bool RunPyScript(QWidget* i_MainWindow, const RunArguments& i_Arg);
};
} // namespace NCTI

#endif //NCTIQTCAEPREAPI_H