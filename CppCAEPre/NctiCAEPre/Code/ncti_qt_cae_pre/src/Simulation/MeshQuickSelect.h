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

#ifndef MESH_QUICK_SELECT_H
#define MESH_QUICK_SELECT_H

#include "ncti_base.h"
#include "NctiGridPickSet.h"
#include "NctiBaseDialog.h"

namespace Ui {
class MeshQuickSelect;
}

namespace NCTI
{
    class SelectModeRoller;
    class NctiQtScriptExecutor;
    class NctiDisplayObject;
    class NctiDocument;
    class NctiMeshBody;

    class MeshQuickSelect : public NctiBaseDialog
    {
        Q_OBJECT

    public:
        /**
         * @brief 构造函数
         * @param i_pDocument 文档指针
         * @param executor 脚本执行器指针
         * @param parent 父窗口指针
         */
        explicit MeshQuickSelect(NctiDocument* i_pDocument, NctiQtScriptExecutor* executor, QWidget* parent = nullptr);
        
        /**
         * @brief 析构函数
         */
        ~MeshQuickSelect();

        double getAngle()const;

        NctiSelectType getOutType()const;
        NctiSelectType getInType()const;

    private:
        /**
         * @brief 设置界面
         */
        void setup();

        Ui::MeshQuickSelect* ui;                        ///< UI界面指针

        NctiDocument* m_document;                      ///< 文档指针
        NctiQtScriptExecutor* m_executor;              ///< 脚本执行器指针
        SelectModeRoller* m_roller;                    ///< 选择模式滚动器
    };
}

#endif // MESH_QUICK_SELECT_H