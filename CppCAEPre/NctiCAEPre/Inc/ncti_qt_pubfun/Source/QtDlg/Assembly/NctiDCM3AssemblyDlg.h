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

#ifndef NctiDCM3AssemblyDlg_H
#define NctiDCM3AssemblyDlg_H

#include "ncti_base.h"
#include "NctiDCM3BaseWidget.h"
#include "dcl_ncti_qt_pubfun.h"
#include <QWidget>
#include "ui_NctiDCM3Assembly.h"
#include "CallbackInterfaces.h"

namespace NCTI {
    class NctiDisplayObject;
    class NctiDocument;
    class NctiDCM3BaseWidget;
    
    /**
     * @brief 装配约束对话框类
     * @details 用于在两个模型之间添加约束的对话框
     */
    class DECL_NCTI_QT_PUBFUN NctiDCM3AssemblyDlg : public NctiDCM3BaseWidget
    {
        Q_OBJECT
    private:
        /**
         * @brief 构造函数
         * @param i_pDocument 文档指针
         * @param i_parent 父窗口指针
         */
        NctiDCM3AssemblyDlg(QWidget* i_parent = nullptr);
        
        /**
         * @brief 析构函数
         */
        ~NctiDCM3AssemblyDlg();
    public:
        /**
        * @brief 初始化对话框
        * @param i_args Python参数对象指针
        * @return 初始化成功返回true，否则返回false
        */
        bool init(PyObject* i_args);
    protected:
        virtual void execute() override;
    public:
        static NctiDCM3AssemblyDlg* Instance();

    private:
        void clearLayout(QLayout* i_layout);
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
        Ui::NctiDCM3Assembly* m_ui;          ///< UI界面指针

        NctiDCM3BaseWidget* m_contentWidget;
    };
}

#endif // !NctiDCM3AssemblyDlg_H