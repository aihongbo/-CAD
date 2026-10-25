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

#ifndef NctiCommandResultDlg_H
#define NctiCommandResultDlg_H

#include "ncti_base.h"
#include "dcl_ncti_qt_pubfun.h"
#include <qwidget.h>
#include "ui_NctiMeshAddMatrial.h"

class QTableWidget;

namespace NCTI {
    class NctiDisplayObject;
    class NctiDocument;
    
    /**
     * @brief 命令结果对话框类
     * @details 用于显示命令执行结果的对话框
     */
    class DECL_NCTI_QT_PUBFUN NctiCommandResultDlg : public QWidget
    {
        Q_OBJECT
    public:
        /**
         * @brief 构造函数
         * @param i_pDocument 文档指针
         * @param i_parent 父窗口指针
         */
        NctiCommandResultDlg(NctiDocument* i_pDocument, QWidget* i_parent);
        
        /**
         * @brief 析构函数
         */
        ~NctiCommandResultDlg();
        
    private:
        /**
         * @brief 初始化数据
         */
        void InitData();
        
        NctiDocument* m_Document;              ///< 文档指针
        QTableWidget* m_tableView;             ///< 表格视图指针
        std::vector<std::string> m_ObjNameVec;  ///< 对象名称列表
    };
}

#endif // !NctiCommandResultDlg_H