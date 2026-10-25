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

#ifndef MeshModifyMeshTypeView_H
#define MeshModifyMeshTypeView_H

#include "ncti_base.h"
#include "NctiBaseDialog.h"
#include "NctiMeshDataDef.h"

namespace Ui {
class MeshModifyMeshTypeView;
}

namespace NCTI
{
    class NctiQtPythonScript;
    class NctiDisplayObject;
    class NctiDocument;
    
    /**
     * @brief 网格引擎设置视图类
     */
    class MeshModifyMeshTypeView : public NctiBaseDialog
    {
        Q_OBJECT

    public:
        /**
         * @brief 构造函数
         * @param i_pDocument 文档指针
         * @param parent 父窗口指针
         */
        explicit MeshModifyMeshTypeView(NctiDocument* i_pDocument, QWidget* parent);
        
        /**
         * @brief 析构函数
         */
        ~MeshModifyMeshTypeView();
        
        /**
         * @brief 获取网格引擎
         * @return  0:Gmsh 1:MeshGems 2:PanaMesh）
         */
        int getMode() const;

    Q_SIGNALS:
         
    protected:
        /**
         * @brief 接受前处理函数
         * @return 处理成功返回true，否则返回false
         */
        bool beforeAccpet();

    private:
        /**
         * @brief 设置界面
         */
        void setup();
        
        /**
         * @brief 弹出消息框
         * @param message 消息内容
         * @param title 标题
         */
        void popupMessage(const QString& message, const QString& title = QStringLiteral("提示"));

    private:
        Ui::MeshModifyMeshTypeView* ui;       ///< UI界面指针
        NctiDocument* m_document;             ///< 文档指针
        Ncti_Integer m_defaultMeshType;
    };
}

#endif // MeshModifyMeshTypeView_H
