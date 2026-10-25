/*
 * Copyright (c) 2026 粤港澳大湾区（广东）国创中心
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

#ifndef NctSketchConstrDlg_H
#define NctSketchConstrDlg_H

#include "ncti_base.h"
#include "dcl_ncti_qt_pubfun.h"
#include "NctiConstrContentWidget.h"
#include "qdialog.h"

namespace NCTI {
    /**
     * @brief 装配约束对话框类
     * @details 用于在两个模型之间添加约束的对话框
     */
    class NctSketchConstrDlg : public QDialog
    {
        Q_OBJECT
    public:
        /**
         * @brief 构造函数
         * @param i_pDocument 文档指针
         * @param i_parent 父窗口指针
         */
        NctSketchConstrDlg(QWidget* i_parent = nullptr);
        
        /**
         * @brief 析构函数
         */
        ~NctSketchConstrDlg();
    public:
        /**
         * @brief 设置窗口标题
         * @param i_title
         */
        void setTitle(QString i_title);
        /**
         * @brief 设置界面显示内容
         * @param i_content
         */
        void setContent(NctiConstrContentWidget* i_content);
    private:
        void init();
    private Q_SLOTS:
        /**
         * @brief 确定按钮槽函数
         */
        void onOk();

        /**
         * @brief 取消按钮槽函数
         */
        void onCancel();

    private:
        NctiConstrContentWidget* m_content;
    };
}

#endif // !NctSketchConstrDlg_H