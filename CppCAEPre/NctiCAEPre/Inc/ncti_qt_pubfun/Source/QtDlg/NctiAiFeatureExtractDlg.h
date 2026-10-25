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

#ifndef NCTIAIFEATUREEXTRACTDLG_H
#define NCTIAIFEATUREEXTRACTDLG_H
#include <QWidget>
#include "dcl_ncti_qt_pubfun.h"
#include "ncti_base.h"
#include "NctiDisplayAiAttriTopoMesh.h"

namespace Ui {
    class NctiAiFeatureExtract;
}

namespace NCTI {
    class NctiDocument;
    
    /**
     * @brief AI特征提取对话框类
     * @details 用于AI特征提取操作的对话框
     */
    class DECL_NCTI_QT_PUBFUN NctiAiFeatureExtractDlg : public QWidget
    {
        Q_OBJECT

    public:
        /**
         * @brief 构造函数
         * @param i_pDocument 文档指针
         * @param i_Type 类型
         * @param parent 父窗口指针
         */
        NctiAiFeatureExtractDlg(NctiDocument* i_pDocument, Ncti_Integer i_Type, QWidget* parent);
        
        /**
         * @brief 析构函数
         */
        ~NctiAiFeatureExtractDlg();

    protected:
        /**
         * @brief 关闭事件处理
         * @param event 关闭事件指针
         */
        void closeEvent(QCloseEvent* event) override;

    public:
        /**
         * @brief 初始化对话框
         */
        void InitDlg();
        
        /**
         * @brief 查找AI拓扑网格对象
         * @param c_Name 对象名称
         * @return NctiDisplayAiAttriTopoMesh对象指针
         */
        NctiDisplayAiAttriTopoMesh* FindAiTopoMeshObject(const char* c_Name);
        
        /**
         * @brief 创建AI拓扑网格对象
         * @param c_ObjName 对象名称
         * @return NctiDisplayAiAttriTopoMesh对象指针
         */
        NctiDisplayAiAttriTopoMesh* CreateAiTopoMeshObject(const char* c_ObjName);

    private:
        Ui::NctiAiFeatureExtract* ui;                    ///< UI界面指针
        NctiDocument* m_pDocument;                       ///< 文档指针
        Ncti_Integer m_Type;                             ///< 类型
        const Ncti_Char* m_LabelName;                    ///< 标签名称
        std::vector<NctiDisplayAiAttriTopoMesh*> m_topoMeshes;  ///< 拓扑网格对象列表
    };
}

#endif // NCTIAIFEATUREEXTRACTDLG_H