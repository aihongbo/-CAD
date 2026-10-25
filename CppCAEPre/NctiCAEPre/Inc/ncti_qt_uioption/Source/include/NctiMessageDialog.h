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
#include "NctiBaseDialog.h"

namespace Ui {
    class MessageDialog;
}

namespace NCTI {
    /**
     * @brief 通知对话框类
     * @details 用于显示通知信息的对话框
     */
    class NCTI_UIOPTION NctiMessageDialog : public NctiBaseDialog
    {
        Q_OBJECT
    public:
        /**
         * @brief 构造函数
         * @param parent 父窗口指针
         * @param docName 文档名称
         * @param bMultiDoc 是否为多文档
         */
        explicit NctiMessageDialog(QWidget* parent, const QString& docName, bool bMultiDoc = false);
        
        /**
         * @brief 析构函数
         */
        ~NctiMessageDialog();
        
        /**
         * @brief 设置界面
         */
        void setupUi();
        
        /**
         * @brief 获取关闭代码
         * @return 关闭代码
         */
        int GetCloseCode();
        
    protected:
        /**
         * @brief 全部不保存槽函数
         */
        void onNoSaveAll();
        
        /**
         * @brief 不保存槽函数
         */
        void onNoSave();
        
        /**
         * @brief 保存槽函数
         */
        void onSave();
        
    private:
        Ui::MessageDialog* ui;     ///< UI界面指针
        QString m_docName;         ///< 文档名称
        int m_closeCode{ 0 };      ///< 关闭代码
    };
}