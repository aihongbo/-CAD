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

#include "PopupBaseDialog.h"

namespace Ui {
    class SaveDocDialogContent;
}

namespace NCTI
{
    /**
     * @brief 保存状态枚举
     */
    enum SaveStatus { 
        Cancel,     ///< 取消
        NoSaveAll,  ///< 全部不保存
        NoSave,     ///< 不保存
        Save        ///< 保存
    };
    
    /**
     * @brief 显示类型枚举
     */
    enum ShowType { 
        SingleDoc,  ///< 单文档
        MultiDoc,   ///< 多文档
        NoDoc       ///< 无文档
    };
    
    /**
     * @brief 保存文档对话框类
     * @details 用于提示用户保存文档的对话框
     */
    class SaveDocDialog : public PopupBaseDialog
    {
        Q_OBJECT
    public:
        /**
         * @brief 构造函数
         * @param parent 父窗口指针
         * @param docName 文档名称
         * @param showType 显示类型
         */
        explicit SaveDocDialog(QWidget* parent, const QString& docName, ShowType = ShowType::SingleDoc);
        
        /**
         * @brief 析构函数
         */
        ~SaveDocDialog();
        
        /**
         * @brief 设置界面
         */
        void setupUi();
        
        /**
         * @brief 获取保存状态
         * @return 保存状态
         */
        SaveStatus GetSaveStatus();
        
        /**
         * @brief 设置保存路径
         * @param path 保存路径
         */
        void SetSavePath(const QString& path);
        
        /**
         * @brief 获取保存路径
         * @return 保存路径
         */
        QString GetSavePath();

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
        Ui::SaveDocDialogContent* ui;  ///< UI界面指针
        QString m_docName;             ///< 文档名称
        QString m_savePath;            ///< 保存路径
        ShowType m_showType{ ShowType::SingleDoc };  ///< 显示类型
        SaveStatus m_saveStatus{ SaveStatus::Cancel };  ///< 保存状态
    };
}