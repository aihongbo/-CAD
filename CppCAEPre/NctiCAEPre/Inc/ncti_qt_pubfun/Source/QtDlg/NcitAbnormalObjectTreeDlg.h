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
#include <QDialog>
#include <ncti_base.h>
#include "CallbackInterfaces.h"

class QTreeWidget;
class QTreeWidgetItem;
class QPushButton;

/**
 * @brief 项单元数据结构
 * @details 存储树形控件项的模型名称和cellID列表
 */
struct ItemCellData
{
    QString ModelName;                     ///< 模型名称
    std::vector<Ncti_Long> CellIDVec;      ///< cellID列表
};
Q_DECLARE_METATYPE(ItemCellData);

namespace NCTI
{
    /**
     * @brief 异常对象树对话框类
     * @details 用于显示和处理异常对象的树形结构对话框
     */
    class NcitAbnormalObjectTreeDlg : public QDialog
    {
        Q_OBJECT
    public:
        /**
         * @brief 构造函数
         * @param parent 父窗口指针
         */
        NcitAbnormalObjectTreeDlg(QWidget* parent = nullptr);
        
        /**
         * @brief 析构函数
         */
        ~NcitAbnormalObjectTreeDlg();
        
        /**
         * @brief 初始化对话框
         * @param i_args Python参数对象指针
         * @return 初始化成功返回true，否则返回false
         */
        bool init(PyObject* i_args);
        
    private Q_SLOTS:
        /**
         * @brief 项点击槽函数
         * @param item 树形控件项指针
         * @param column 列索引
         */
        void onItemClicked(QTreeWidgetItem* item, int column);
	    
    private:
        QTreeWidget* m_TreeWidget;   ///< 树形控件指针
        Ncti_Long m_DocID;           ///< 文档ID
    };
}