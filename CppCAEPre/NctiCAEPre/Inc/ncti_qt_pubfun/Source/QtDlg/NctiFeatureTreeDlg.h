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
#include "NctiPosition.h"

class QTreeWidget;
class QTreeWidgetItem;
class QPushButton;

/**
 * @brief 项数据结构体
 * @details 存储树形控件项的数据信息
 */
struct ItemData
{
    QString ModelName;                                   ///< 模型名称
    std::vector<Ncti_Long> CellIDVec;                    ///< cellID数组
    std::vector<std::vector<NCTI::NctiPosition>> CellPosVec;   ///< 单元位置列表
};
Q_DECLARE_METATYPE(ItemData);

namespace NCTI
{
    /**
     * @brief 特征树对话框类
     * @details 用于显示特征树结构的对话框
     */
    class NctiFeatureTreeDlg : public QDialog
    {
        Q_OBJECT
    public:
        /**
         * @brief 构造函数
         * @param parent 父窗口指针
         */
        NctiFeatureTreeDlg(QWidget* parent = nullptr);
        
        /**
         * @brief 析构函数
         */
        ~NctiFeatureTreeDlg();
        
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
        
        /**
         * @brief 按钮点击槽函数
         * @param boo 点击状态
         */
        void onBtnClicked(bool boo);
	    
    private:
        /**
         * @brief 更新父项状态
         * @param item 树形控件项指针
         */
        void updateParentState(QTreeWidgetItem* item);
        
        /**
         * @brief 更新树形控件
         */
        void updateTree();
        
    private:
        QTreeWidget* m_TreeWidget;    ///< 树形控件指针
        QPushButton* m_BtnRemove;     ///< 移除按钮指针
        QStringList m_LevelNames;     ///< 层级名称列表
        Ncti_Long m_LevelCount;       ///< 层级计数
        Ncti_Long m_DocID;            ///< 文档ID
    };
}